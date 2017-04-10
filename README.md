# zsdk-ptlib: Portable Tools Library

## Building

### Local build

The local build process has not changed, see [ReadMe.txt](ReadMe.txt) for details.

### Local RPM build

The local build is performed using `mock`, which ensures a consistent build
environment by setting up a chroot. It uses `yum` to install essential packages
within the chroot, plus any packages listed as build dependenciesin the spec
file.

    ./mockbuild.sh

The provided mock config file, `mcu-epel-6-x86_64.cfg`, adds MCU yum
repository definitions. If you need to build against an RPM that is not
available from Nexus, use the following steps to set up an `mcu-local` repo:

    mkdir /tmp/mcu-local
    cp some.rpm /tmp/mcu-local
    createrepo /tmp/mcu-local
    ./mockbuild.sh --enablerepo=mcu-local

If any of your RPMs in mcu-local are older versions of ones available from
Nexus, you will either need to specify explicit versions in the spec file, or
disable the Nexus repos and provide all MCU RPMs in the local repo:

    ./mockbuild.sh --enablerepo=mcu-local --disablerepo=mcu-release --disablerepo=mcu-develop

### Jenkins build

The [Jenkins build][1] uses Docker to ensure a consistent build environment. The
build process is configured by the `Jenkinsfile`, which delegates Docker
container setup to the `Dockerfile`. The `Jenkinsfile` also handles publishing
certain branches to yum repostitories on Nexus, and notifying HipChat of build
results.

## Versioning

The first three components of the PTLib package version number should always
match the version number of the open source release it is based on. A fourth
component has been added to reflect our own patches to the open source code. The
fourth component should be incremented each time we merge a new patch into the
integration branch.

To ensure consistency, the spec file is now considered the master copy of the
version number, so the RPM build process will use this in favour of version
numbers elsewhere in the code. However, if you perform a local (non-RPM) build,
you may need to adjust any built-in version manually.

The RPM release tag should always remain at 1 on the integration branch, and be
incremented to 2 in the first commit on a release branch. This provides an easy
way to distinguish a development RPM from a release RPM of the same verison.

Note that Jenkins appends its build number to the release number, so it should
be easy to distinguish RPMs that contain functional changes vs RPMs that are
different builds of the same code. If an RPM has been built outside of Jenkins
the build number component should be missing.

For example:

    bbcollab-ptlib-2.17.4.13-2.55.el6.x86_64.rpm
    package        ver       rel      arch

* Package: bbcollab-ptlib
* Version: 2.17.4.13 (Open source 2.17.4, plus 13 patches)
* Release: 2.55.el6 (Release branch build, Jenkins build number: 55, Dist tag: el6)
* Arch: x86_64

## Branching

Loosely follow the [GitFlow][3] model, but with the following modifications:
* There is no "production" branch (normally `master` in Git Flow)
* The integration branch is named `staging` instead of `develop`
* `master` and `develop` branches do exist, but are lost in history somewhere
  and should be ignored
* The `trunk` branch is used for changes being pushed to/pulled from the public
  PTLib repository

Once we have fully switched to the new Jenkins we should look at cleaning up our
branches and agree the model/naming to use. For now, we don't want to break the
builds on the existing Jenkins by changing everything.

## Releasing

1. Create a new release branch named `release/<YYYY-MM>` from an appropriate
   position on the integration branch.
1. Increment the Release tag in the RPM spec file to 2 (should always be 1 on
   the integration branch).
1. Update the build dependencies in the RPM spec file to require exact versions
   (including the full release tag of the target RPM).
   This makes it easier to go back and recreate a specific release build at a
   later date, even if newer versions of the build dependencies have been
   released.
1. Commit and push the spec file changes. Jenkins will be notified of the
   change, build the new release branch, and publish the output RPM to the
   `mcu-release` yum repository on Nexus.
1. Perform appropriate testing of the release candidate, and apply additional
   commits to the branch as needed. Non-trivial fixes should be performed on an
   additional `bugfix/` branch (with an increment to the Release tag in the
   spec file) to allow for code review. Note that Jenkins will build commits to
   the bugfix branch, but will not publish the output to Nexus.
1. When testing has completed, tag the final release commit.
1. Once the release is tagged, merge it back into the integration branch as
   follows:

       git checkout staging
       git pull
       git merge --no-ff --no-commit release/2016-12

   This allows you to make some changes before committing and pushing the merge,
   effectively reverting the first commit on the release branch:
   * Increment the version number for the next release
   * Reset the Release tag to 1
   * Restore the normal build dependency version requirements (not exact, but
     may have minimum required version)

[1]: http://collab-jenkins.bbpd.io/job/zsdk-ptlib/
[2]: http://semver.org/
[3]: http://nvie.com/posts/a-successful-git-branching-model/
