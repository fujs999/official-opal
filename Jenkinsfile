pipeline {
  agent none

  options {
    buildDiscarder logRotator(artifactDaysToKeepStr: '', artifactNumToKeepStr: '', daysToKeepStr: '200', numToKeepStr: '200')
  }

  stages {
    stage('package-el6') {
      // Build environment is defined by the Dockerfile
      agent {
        dockerfile {
          filename 'el6.Dockerfile'
          additionalBuildArgs  '--build-arg SPECFILE=bbcollab-ptlib.spec'
          customWorkspace "${JOB_NAME.replaceAll('%2F', '_')}"
        }
      }
      steps {
        // Copy RPM dependencies to the workspace for fingerprinting (see Dockerfile)
        sh 'cp -r /tmp/build-deps .'
        sh './rpmbuild.sh'
      }
      post {
        success {
          fingerprint 'build-deps/*.rpm'
          archiveArtifacts artifacts: 'rpmbuild/**/*', fingerprint: true
          stash name: 'el6_rpms', includes: 'rpmbuild/RPMS/**/*'
        }
      }
    }
    stage('package-el7') {
      // Build environment is defined by the Dockerfile
      agent {
        dockerfile {
          filename 'el7.Dockerfile'
          additionalBuildArgs  '--build-arg SPECFILE=bbcollab-ptlib.spec'
          customWorkspace "${JOB_NAME.replaceAll('%2F', '_')}"
        }
      }
      steps {
        // Copy RPM dependencies to the workspace for fingerprinting (see Dockerfile)
        sh 'cp -r /tmp/build-deps .'
        sh './rpmbuild.sh'
      }
      post {
        success {
          fingerprint 'build-deps/*.rpm'
          archiveArtifacts artifacts: 'rpmbuild/**/*', fingerprint: true
          stash name: 'el7_rpms', includes: 'rpmbuild/RPMS/**/*'
        }
      }
    }
    stage('publish') {
      when {
        beforeAgent true
        anyOf {
          branch 'develop'
          branch 'release/*'
        }
      }
      agent { label 'Nexus' }
      options { skipDefaultCheckout() }
      environment {
        BASE_PATH = '/var/www/html/yum'
      }
      steps {
        script {
          def dists = ['el6', 'el7']
          for (int i = 0; i < dists.size(); ++i) {
            if (dists[i] == 'el6') {
              env.REPO = ''
            } else {
              env.REPO = "${dists[i]}/"
            }

            if (env.BRANCH_NAME == 'develop') {
              env.REPO += 'mcu-develop'
            } else {
              env.REPO += 'mcu-release'
            }

            sh "rm -rf rpmbuild"
            unstash "${dists[i]}_rpms"
            sh "aws s3 sync --acl public-read rpmbuild/RPMS/x86_64 s3://citc-artifacts/yum/$REPO/base/"
            sh "mv rpmbuild/RPMS/x86_64/* $BASE_PATH/$REPO/base/"
            // Update Nexus repository metadata
            sh "createrepo --update $BASE_PATH/$REPO"
            sh "aws s3 sync --acl public-read --delete $BASE_PATH/$REPO/repodata s3://citc-artifacts/yum/$REPO/repodata/"
          }
        }
      }
      post {
        success {
          script {
            if (env.BRANCH_NAME == 'develop') {
              build job: "/zsdk-opal/develop", quietPeriod: 60, wait: false
            }
          }
        }
      }
    }
  }
  post {
    success {
      slackSend color: "good", message: "SUCCESS: <${currentBuild.absoluteUrl}|${currentBuild.fullDisplayName}>"
    }
    failure {
      slackSend color: "danger", message: "FAILURE: <${currentBuild.absoluteUrl}|${currentBuild.fullDisplayName}>"
    }
    unstable {
      slackSend color: "warning", message: "UNSTABLE: <${currentBuild.absoluteUrl}|${currentBuild.fullDisplayName}>"
    }
  }
}