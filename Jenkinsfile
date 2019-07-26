pipeline {
    agent none 
    stages {
        stage('Test on Woody') {
            steps {
                echo 'Hello, Je lance les tests sur woody'
                sh 'make -f test.mk'
            }
        }
    }
}
