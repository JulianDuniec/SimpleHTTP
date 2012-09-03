#include "../headers/SimpleHTTP.h"
#include <iostream>

using namespace std;

void error(std::string msg) {
  cout << msg << endl;
  exit(1);
}

void SimpleHTTP::stop() {
	running = false;
	WaitForInternalThreadToExit();
}

void SimpleHTTP::start(int iport, int ibacklog, ListenCallback icallback) {
	//the port-number to listen too
	port = iport;

	backlog = ibacklog;
	//Bind the callback for when a request occurs.
	callback = icallback;

	running = true;

	configureSocket();
	
	bindSocket();
	
	startListening();
	
}

void SimpleHTTP::startListening() {
	StartInternalThread();
}

void SimpleHTTP::InternalThreadEntry() {
	
	listen(sockfd, backlog);
		
	while(running) {
		char buffer[256];
		int n;
		clilen = sizeof(cli_addr);
		newsockfd = accept(sockfd,  (struct sockaddr *) &cli_addr,  &clilen);
		if (newsockfd < 0) 
			error("ERROR on accept");
		
		bzero(buffer,256);
		n = read(newsockfd,buffer,sizeof(buffer));
		if (n < 0) error("ERROR reading from socket");
		SimpleHTTPRequest req;
		req.setBody(buffer);
		callback(req);
		n = write(newsockfd,"I got your message",18);
		if (n < 0) error("ERROR writing to socket");
	}
	
	close(newsockfd);
	close(sockfd); 
}

void SimpleHTTP::bindSocket() {
	/*
		The bind() system call binds a socket to an address, 
		in this case the address of the current host and port number on which the server will run. 
		It takes three arguments, the socket file descriptor, the address to which is bound, 
		and the size of the address to which it is bound. 

		The second argument is a pointer to a structure of type sockaddr,
		but what is passed in is a structure of type sockaddr_in, and so this must be cast to the correct type. 
		This can fail for a number of reasons, the most obvious being that this socket is already in use on 
		this machine. The bind() manual has more information.
	*/
	int result = bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	if (result < 0) 
		error("ERROR on binding");
}

void SimpleHTTP::configureSocket() {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);
}

