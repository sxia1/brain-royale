to run:
in the client folder run the following commands:

$ npm install
$ npm run build


IMPORTANT:
- edit server.cpp and replace the file names accordingly
- This is just a temporary thing for the proof of concept
- it will be cleaned up once the router is done


in the server folder run the following command:

g++ -o server server.cpp static_file.cpp static_file.h


open localhost:8080 in your browser of choice!
