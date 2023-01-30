#ifndef exceptions_h
#define exceptions_h
#include <stdexcept>
#include <string>
using std::string;

class InvalidFile : public std::exception {
	string message;
public:
	InvalidFile(const std::string& message) : message(message) {}
	const char* what() const noexcept override {
		return message.c_str();
	}
};

class InvalidBus : public std::exception {
	string message;
public:
	InvalidBus(const std::string& message) : message(message) {}
	const char* what() const noexcept override { return message.c_str(); }
};

class InvalidBusStation : public std::exception {
	string message;
public:
	InvalidBusStation(const std::string& message) : message(message) {}
	const char* what() const noexcept override { return message.c_str(); }
};

class InvalidRoute : public std::exception {
	string message;
public:
	InvalidRoute(const std::string& message) : message(message) {}
	const char* what() const noexcept override { return message.c_str(); }
};


#endif