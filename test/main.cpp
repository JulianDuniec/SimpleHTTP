#include <iostream>
#include "../headers/SimpleHTTP.h"
using namespace std;

#define PORT 8010
#define BACKLOG 10

SimpleHTTP * server;

void test_create_instance();

void test_listen();

int main()
{
	test_create_instance();
	test_listen();
    return 0;
}


void test_create_instance() {
	cout << "Test create instance" << endl;
	server = new SimpleHTTP;
}

int callback(SimpleHTTPRequest& req) {
	cout << "Callback-listener got: " << req.getBody() << endl;
	return 0;
}

void test_listen() {
	cout << "Test listen" << endl;
	server->start(PORT, BACKLOG, &callback);
	//Execute some http-requests
	system("/bin/sh test/curl.sh");
	//Wait for thread to stop.
	server->stop();
}