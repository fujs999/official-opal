#!groovy

@Library('collab-jenkins-library') _

env.SPECFILE = 'libopal.spec'
def job_name = "${JOB_NAME.replaceAll('%2F', '_')}"
def build_name = "${job_name}/${BUILD_NUMBER}"

pipeline {
  agent none
  stages {
    stage('matrix') {
      failFast true
      matrix {
        axes {
          axis {
            name 'DIST'
            values 'el7', 'amzn2'
          }
          axis {
            name 'REPO'
            values 'mcu-develop', 'mcu-release', 'mcu-release-tsan'
          }
          axis {
            name 'ARCH'
            values 'x86_64', 'aarch64'
          }
        }
        when {
          anyOf {
            allOf {
              branch 'develop'
              expression { return REPO == 'mcu-develop' }
            }
            allOf {
              branch 'release/*'
              expression { return REPO != 'mcu-develop' }
            }
          }
        }
        excludes {
          exclude {
            axis {
              name 'DIST'
              values 'el7'
            }
            axis {
              name 'ARCH'
              values 'aarch64'
            }
          }
          exclude {
            axis {
              name 'DIST'
              values 'amzn2'
            }
            axis {
              name 'REPO'
              values 'mcu-release-tsan'
            }
          }
        }
        stages {
          stage('package') {
            agent {
              dockerfile {
                additionalBuildArgs "--build-arg SPECFILE=${env.SPECFILE}"
              }
            }
            environment {
              HOME = "${WORKSPACE}/${DIST}-${REPO}"
            }
            steps {
              script {
                sh 'mkdir -p $HOME'
                if (DIST == 'el7') {
                  sh " ./rpmbuild.sh --with=${REPO.replace('mcu-release-','')}"
                }
                else {
                  awsCodeBuild \
                      region: env.AWS_REGION, sourceControlType: 'jenkins', \
                      credentialsId: 'aws-codebuild', credentialsType: 'jenkins', sseAlgorithm: 'AES256', \
                      cloudWatchLogsStatusOverride: 'ENABLED', cloudWatchLogsGroupNameOverride: 'bbrtc-codebuild', \
                      cloudWatchLogsStreamNameOverride: "${job_name}/${ARCH}", \
                      artifactTypeOverride: 'S3', artifactLocationOverride: 'bbrtc-codebuild', \
                      artifactNameOverride: 'rpmbuild', artifactPathOverride: build_name, \
                      downloadArtifacts: 'true', downloadArtifactsRelativePath: '.', \
                      envVariables: "[ { BUILD_NUMBER, ${BUILD_NUMBER} }, { BRANCH_NAME, ${BRANCH_NAME} }, { SPECFILE, ${env.SPECFILE} } ]", \
                      projectName: "BbRTC-${ARCH}"
                  sh "mv ${build_name}/rpmbuild ${HOME}/"
                }
              }
            }
            post {
              success {
                archiveArtifacts artifacts: "${DIST}-${REPO}/rpmbuild/RPMS/**/*", fingerprint: true
              }
            }
          }
          stage('publish') {
            agent { label 'master' }
            steps {
              unarchive mapping:["${DIST}-${REPO}/rpmbuild/RPMS/" : '.']
              script {
                stageYumPublish rpms: "${DIST}-${REPO}/rpmbuild/RPMS/", dist: DIST, repo: REPO, arch: ARCH
              }
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
      slackSend color: "danger", message: "@channel FAILURE: <${currentBuild.absoluteUrl}|${currentBuild.fullDisplayName}>"
    }
    unstable {
      slackSend color: "warning", message: "@channel UNSTABLE: <${currentBuild.absoluteUrl}|${currentBuild.fullDisplayName}>"
    }
  }
}
