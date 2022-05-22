all: server/server.o server/iostream_server.o server/static_file.o server/request.o server/Router.o server/LobbyController.o server/Lobby.o
	cd server; g++ -o server -pthread server.o iostream_server.o static_file.o request.o Router.o LobbyController.o Lobby.o -lboost_filesystem -lboost_system 
	
server.o: server.cpp static_file.h request.h
	cd server; g++ -c server.cpp

iostream_server.o: iostream_server.cpp iostream_server.h LobbyController.h
	cd server; g++ -c iostream_server.cpp

static_file.o: static_file.cpp static_file.h
	cd server; g++ -c static_file.cpp

request.o: request.cpp request.h
	cd server; g++ -c request.cpp

Router.o: Router.cpp Router.h static_file.h request.h
	cd server; g++ -c Router.cpp

LobbyController.o: LobbyController.cpp LobbyController.h Lobby.h
	cd server; g++ -c LobbyController.cpp

Lobby.o: Lobby.cpp Lobby.h
	cd server; g++ -c Lobby.cpp

run:
	 cd server; ./server
