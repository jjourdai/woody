pipeline {
    agent any
    stages {
        stage('ok je recommence a 0') {
            steps {
                echo "On Non-Sequential Stage"
		sh 'echo "test"'
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
