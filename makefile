all: server/server.o server/static_file.o server/request.o server/Router.o
	cd client; npm install; npm run build;\
  cd ../server; g++ -o server server.o static_file.o request.o Router.o
	
server.o: server.cpp static_file.h request.h
	cd server; g++ -c server.cpp

static_file.o: static_file.cpp static_file.h
	cd server; g++ -c static_file.cpp

request.o: request.cpp request.h
	cd server; g++ -c request.cpp

Router.o: Router.cpp Router.h static_file.h request.h
	cd server; g++ -c Router.cpp

run:
	 cd server; ./server
