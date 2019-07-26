pipeline {
    agent any
    stages {
        stage('Test woody on Ubuntu') {
            steps {
		sh 'tests/scripts/launch.sh ubuntu'
            }
        }
	stage('Test woody on fedora') {
            steps {
		sh 'tests/scripts/launch.sh fedora'
            }
        }
	stage('Test woody on debian') {
            steps {
		sh 'tests/scripts/launch.sh debian'
            }
        }
	stage('Test woody on archlinux') {
            steps {
		sh 'tests/scripts/launch.sh archlinux'
            }
        }
	stage('Test woody on kalilinux') {
            steps {
		sh 'tests/scripts/launch.sh kalilinux'
            }
        }
    }
}
