all: server.o static_file.o request.o Router.o
	g++ -o server -pthread server.o static_file.o request.o Router.o -lboost_filesystem -lboost_system
	
server.o: server.cpp static_file.h request.h
	g++ -c server.cpp

static_file.o: static_file.cpp static_file.h
	g++ -c static_file.cpp

request.o: request.cpp request.h
	g++ -c request.cpp

Router.o: Router.cpp Router.h static_file.h request.h
	g++ -c Router.cpp

run:
	./server
