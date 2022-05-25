# brain-royale

# To Run
* $ docker build -t <tagname> .
* $ docker run -dp 8080:8080 <tagname>

# To See Containers
* $ docker container ls -al

# To Stop Container
* $ docker stop <containerID>

# Installing Required Libraries

* sudo apt install libwebsocketpp-dev
* sudo apt install libasio-dev
* sudo apt install libboost-all-dev

# To Run (Stay in the projects root directory)
* npm install
* npm run build
* export PORT=8080
* make all
* make run
