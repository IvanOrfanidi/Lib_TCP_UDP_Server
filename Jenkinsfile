// Имя выходного файла
def EXECUTABLE_FILE_NAME = "library"
// Путь куда будет ставиться либа
def INSTALL_PATH = "out"

pipeline {
    agent any
    stages {
        stage('build') {
            steps {
                sh "bash compile.sh ${INSTALL_PATH}"
            }
        }

        stage('cppcheck') {
            steps {
                sh 'cppcheck --enable=all --xml --xml-version=2 -i ext  source include 2> build/cppcheck.xml'
                sh 'cppcheck-htmlreport --source-encoding="iso8859-1" --title="project" --source-dir=. --report-dir=build --file=build/cppcheck.xml'
                publishHTML(
                    target: [
                      allowMissing: true,
                      alwaysLinkToLastBuild: false,
                      keepAll: false,
                      reportDir: 'build',
                      reportFiles: 'index.html',
                      reportName: 'CppCheck Report',
                      reportTitles: ''
                    ]
                )
            }
        }

        stage('archive') {
            steps {
                script {
                    sh "zip -r ${EXECUTABLE_FILE_NAME}.zip ${INSTALL_PATH}"
                }
            }
        }

        stage('artifacts') {
            steps {
                archiveArtifacts artifacts: "${EXECUTABLE_FILE_NAME}.zip", onlyIfSuccessful: true
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
