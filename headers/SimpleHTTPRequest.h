#include <string>

class SimpleHTTPRequest {
	std::string body;
public:
	std::string getBody();
	void setBody(std::string);
};
