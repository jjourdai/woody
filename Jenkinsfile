pipeline {
    agent any
    stages {
        stage('Test woody on Ubuntu') {
            steps {
		sh 'tests/scripts/launch.sh fedora'
            }
        }
	stage('stage 2') {
            steps {
                echo "stage 2"
		sh 'echo "stage 2"'
            }
        }
    }
}
