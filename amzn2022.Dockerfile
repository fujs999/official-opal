#!docker

# See https://docs.aws.amazon.com/linux/al2022/ug/install-docker.html
FROM amazonlinux:2022 as base

# Add standard tools expected on any development machine
RUN yum install --assumeyes shadow-utils sudo gcc-c++ git libasan-static libtsan-static && yum clean all

# Add tools needed for RPM building and dealing with yum repositories
RUN yum install --assumeyes rpmdevtools yum-utils && yum clean all

# Uncomment if you want to install some local dependencies instead of using Nexus yum repos
#COPY build-deps /tmp/build-deps/
#RUN yum install -y /tmp/build-deps/*.rpm && yum clean all


FROM base AS depsolver

ARG SPECFILE
COPY ${SPECFILE} .

# Install standard dependencies referenced by the spec file
RUN mkdir std-deps \
    && touch std-deps/placeholder \
    && yum-builddep --excludepkgs='collab-*' --skip-unavailable --assumeyes --downloadonly --downloaddir=/tmp/std-deps ${SPECFILE} \
    && ([ -z "$(ls -A /tmp/std-deps/*.rpm)" ] || cp /tmp/std-deps/*.rpm std-deps && yum install --assumeyes std-deps/*.rpm) \
    && yum clean all

# Always configure mcu-release repository
RUN echo "[mcu-release]" > /etc/yum.repos.d/mcu-release.repo && \
    echo "name=mcu-release" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "baseurl=https://citc-artifacts.s3.amazonaws.com/yum/amzn2022/mcu-release/" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "gpgcheck=false" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "cost=2000" >> /etc/yum.repos.d/mcu-release.repo && \
    cat /etc/yum.repos.d/mcu-release.repo
# Maybe configure mcu-develop or ASan/TSan repository
ARG REPO=mcu-release
RUN echo "[${REPO}]" > /etc/yum.repos.d/${REPO}.repo && \
    echo "name=${REPO}" >> /etc/yum.repos.d/${REPO}.repo && \
    echo "baseurl=https://citc-artifacts.s3.amazonaws.com/yum/amzn2022/${REPO}/" >> /etc/yum.repos.d/${REPO}.repo && \
    echo "gpgcheck=false" >> /etc/yum.repos.d/${REPO}.repo && \
    cat /etc/yum.repos.d/${REPO}.repo

# Invalidate Docker cache if our yum repo metadata has changed (don't care about standard repos)
ADD https://citc-artifacts.s3.amazonaws.com/yum/amzn2022/${REPO}/repodata/repomd.xml /tmp/${REPO}.xml

# Download internal dependencies referenced by the spec file
RUN mkdir build-deps \
    && touch build-deps/placeholder \
    && yum-builddep --assumeyes --downloadonly --downloaddir=/tmp/build-deps ${SPECFILE} \
    && cp /tmp/build-deps/*.rpm build-deps \
    && yum clean all


FROM base
# Install standard dependencies
COPY --from=depsolver std-deps/* std-deps/
RUN [ -z "$(ls -A std-deps/*.rpm)" ] || (yum install --assumeyes std-deps/*.rpm && yum clean all)

# Install OpenH264
ADD plugins/install_openh264.sh /tmp/
RUN /tmp/install_openh264.sh /usr/local/lib64

# Install internal dependencies
COPY --from=depsolver build-deps/* build-deps/
RUN [ -z "$(ls -A build-deps/*.rpm)" ] || (yum install --assumeyes build-deps/*.rpm && yum clean all)

# Set up a non-root user for RPM builds
ARG USERID=1000
ARG GROUPID=1000
ARG USERNAME=rpmbuild
RUN groupadd -g ${USERID} ${USERNAME} && useradd -u ${USERID} -g ${GROUPID} ${USERNAME}
WORKDIR /home/${USERNAME}
USER ${USERNAME}
RUN rpmdev-setuptree
