pipeline {
    agent any
    stages {
        stage('ok je recommence a 0') {
            steps {
                echo "On Non-Sequential Stage"
		sh 'echo "test"'
            }
	    steps {
                echo "On Non-Sequential Stage"
		sh 'echo "test"'
            }
        }
    }
}
