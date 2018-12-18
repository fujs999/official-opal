FROM centos:7
RUN yum groupinstall -y "Development tools" && yum clean all
RUN yum install -y rpmdevtools yum-utils && yum clean all
# Fix CentOS7 dist tag macro (defaults to .el7.centos)
RUN sed -i s/\.centos// /etc/rpm/macros.dist
RUN yum install -y epel-release && yum clean all
COPY mcu-el7.repo /etc/yum.repos.d/

ARG USERID=1000
ARG GROUPID=1000
RUN groupadd -g ${USERID} rpmbuild && useradd -u ${USERID} -g ${GROUPID} rpmbuild
WORKDIR /home/rpmbuild

# Install devtoolset-7 (with workaround for https://bugs.centos.org/view.php?id=15606)
RUN yum install -y centos-release-scl-rh && \
    sed -i 's|centos/7|centos/7.5.1804|' /etc/yum.repos.d/CentOS-SCLo-scl-rh.repo && \
    yum install -y --setopt=tsflags=nodocs devtoolset-7-gcc devtoolset-7-gcc-c++ devtoolset-7-gcc-gfortran devtoolset-7-gdb && \
    yum clean all

# Install dependencies referenced by the spec file, but cache the installed RPMs so they can be fingerprinted later
ARG SPECFILE
COPY ${SPECFILE} .
# Invalidate Docker cache if yum repo metadata has changed
ADD http://nexus.bbcollab.net/yum/el7/mcu-develop/repodata/repomd.xml /tmp/
RUN yum-builddep -y --downloadonly --downloaddir=/tmp/build-deps ${SPECFILE}; \
    if [ -n "$(ls -A /tmp/build-deps/*.rpm)" ]; then yum install -y /tmp/build-deps/*.rpm; fi; \
    yum clean all

USER rpmbuild
