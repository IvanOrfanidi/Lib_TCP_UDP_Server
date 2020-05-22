// Имя выходного файла
def EXECUTABLE_FILE_NAME = "lib_tcp_udp_server"

pipeline {
    agent any
    stages {
        stage('build') {
            steps {
                sh 'bash compile.sh'
            }
        }

        stage('artifacts') {
            steps {
                archiveArtifacts artifacts: "build/${EXECUTABLE_FILE_NAME}.a", onlyIfSuccessful: true
            }
        }

        stage('clean') {
            steps {
                cleanWs()
            }
        }
    }
    options {
        buildDiscarder(logRotator(numToKeepStr: '1'))
    }
}
