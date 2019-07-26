pipeline {
    agent any
    stages {
        stage('ok je recommence a 0') {
            steps {
                echo "On Non-Sequential Stage"
		bash 'echo "test"'
            }
        }
	stage('stage 2') {
            steps {
                echo "stage 2"
		bash 'echo "stage 2"'
            }
        }
    }
}
