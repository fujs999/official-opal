#!docker

FROM centos:7 AS base

# Add yum repositories needed for our builds
RUN yum install --assumeyes epel-release centos-release-scl-rh && yum clean all

# Add standard tools expected on any development machine
RUN yum groupinstall --assumeyes "Development tools" && yum clean all

# Install large/common dependencies (to avoid delays upon later cache invalidation)
RUN yum install --assumeyes --setopt=tsflags=nodocs \
        devtoolset-9-gcc \
        devtoolset-9-gcc-c++ \
        devtoolset-9-libtsan-devel \
        devtoolset-9-libasan-devel && \
    yum clean all

# Add tools needed for RPM building and dealing with yum repositories
RUN yum install --assumeyes rpmdevtools yum-utils && yum clean all

# Uncomment if you want to install some local dependencies instead of using Nexus yum repos
#COPY build-deps /tmp/build-deps/
#RUN yum install -y /tmp/build-deps/*.rpm && yum clean all


FROM base AS depsolver
# Temporary fix for broken centos repo
RUN sed --in-place 's/centos\/7\//centos\/7.8.2003\//'            /etc/yum.repos.d/CentOS-SCLo-scl-rh.repo && \
    sed --in-place 's/centos\/\$releasever\//centos\/7.8.2003\//' /etc/yum.repos.d/CentOS-Sources.repo

ARG SPECFILE
COPY ${SPECFILE} .

# Install standard dependencies referenced by the spec file
RUN mkdir /tmp/std-deps \
    && touch /tmp/std-deps/placeholder \
    && yum-builddep --exclude='collab-*' --tolerant --assumeyes --downloadonly --downloaddir=/tmp/std-deps ${SPECFILE} \
    && ([ -z "$(ls -A /tmp/std-deps/*.rpm)" ] || yum install --assumeyes /tmp/std-deps/*.rpm) \
    && yum clean all

# Always configure mcu-release repository
RUN echo "[mcu-release]" > /etc/yum.repos.d/mcu-release.repo && \
    echo "name=mcu-release" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "baseurl=https://citc-artifacts.s3.amazonaws.com/yum/el7/mcu-release/" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "gpgcheck=false" >> /etc/yum.repos.d/mcu-release.repo && \
    echo "cost=2000" >> /etc/yum.repos.d/mcu-release.repo && \
    cat /etc/yum.repos.d/mcu-release.repo
# Maybe configure mcu-develop or ASan/TSan repository
ARG REPO=mcu-release
RUN echo "[${REPO}]" > /etc/yum.repos.d/${REPO}.repo && \
    echo "name=${REPO}" >> /etc/yum.repos.d/${REPO}.repo && \
    echo "baseurl=https://citc-artifacts.s3.amazonaws.com/yum/el7/${REPO}/" >> /etc/yum.repos.d/${REPO}.repo && \
    echo "gpgcheck=false" >> /etc/yum.repos.d/${REPO}.repo && \
    cat /etc/yum.repos.d/${REPO}.repo

# Invalidate Docker cache if our yum repo metadata has changed (don't care about standard repos)
ADD https://citc-artifacts.s3.amazonaws.com/yum/el7/${REPO}/repodata/repomd.xml /tmp/${REPO}.xml

# Download internal dependencies referenced by the spec file
RUN mkdir /tmp/build-deps \
    && touch /tmp/build-deps/placeholder \
    && yum-builddep --assumeyes --downloadonly --downloaddir=/tmp/build-deps ${SPECFILE} \
    && yum clean all


FROM base
# Install standard dependencies
COPY --from=depsolver /tmp/std-deps/* /tmp/std-deps/
RUN [ -z "$(ls -A /tmp/std-deps/*.rpm)" ] || (yum install --assumeyes /tmp/std-deps/*.rpm && yum clean all)

# Install OpenH264
ADD plugins/install_openh264.sh /tmp/
RUN /tmp/install_openh264.sh /usr/local/lib64

# Install internal dependencies
COPY --from=depsolver /tmp/build-deps/* /tmp/build-deps/
RUN [ -z "$(ls -A /tmp/build-deps/*.rpm)" ] || (yum install --assumeyes /tmp/build-deps/*.rpm && yum clean all)

# Set up a non-root user for RPM builds
ARG USERID=1000
ARG GROUPID=1000
ARG USERNAME=rpmbuild
RUN groupadd -g ${USERID} ${USERNAME} && useradd -u ${USERID} -g ${GROUPID} ${USERNAME}
WORKDIR /home/${USERNAME}
USER ${USERNAME}
RUN rpmdev-setuptree
