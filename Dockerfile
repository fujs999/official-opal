FROM centos:6
RUN yum groupinstall -y "Development tools" && yum clean all
RUN yum install -y \
    rpmdevtools \
    yum-utils \
    && yum clean all
RUN yum install -y epel-release && yum clean all
RUN groupadd -g 1000 jenkins && useradd -M -u 1000 -g 1000 jenkins
RUN rpm --import http://nexus.bbcollab.net/tarballs/RPM-GPG-KEY.atrpms \
    && yum-config-manager --add-repo="http://nexus.bbcollab.net/tarballs/atrpms.repo" \
    && yum clean all
COPY mcu.repo /etc/yum.repos.d/
COPY bbcollab-libopal.spec .
# Invalidate Docker cache if yum repo metadata has changed
ADD http://nexus.bbcollab.net/yum/mcu-develop/repodata/repomd.xml /tmp/
# Use two-step build dependency installation, so we can cache the RPMs for fingerprinting
RUN yum-builddep -y --downloadonly --downloaddir=/var/cache/jenkins/build-deps bbcollab-libopal.spec \
    && yum install -y /var/cache/jenkins/build-deps/*.rpm \
    && yum clean all
