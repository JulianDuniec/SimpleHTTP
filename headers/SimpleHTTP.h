#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "ThreadWrapper.h"
#include "SimpleHTTPRequest.h"

/*
	Callback-signature for listen-method in SimpleHTTP
*/
typedef int (*ListenCallback)(SimpleHTTPRequest&);


class SimpleHTTP : public ThreadWrapper{
	
public:
	void start(int port, int backlog, ListenCallback icallback);
	void stop();
protected:
	void InternalThreadEntry();
private:
	void configureSocket();
	void bindSocket();
	void startListening();int port;
	int sockfd;
	int newsockfd;
	socklen_t clilen;
	ListenCallback callback;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	bool running;
	int backlog;
};