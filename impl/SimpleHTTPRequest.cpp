#include "../headers/SimpleHTTPRequest.h"

void SimpleHTTPRequest::setBody(std::string ibody) {
	body = ibody;
}

std::string SimpleHTTPRequest::getBody()
{
	return body;
}