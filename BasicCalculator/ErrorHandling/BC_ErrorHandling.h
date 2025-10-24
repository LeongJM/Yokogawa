#ifndef BC_ERRORHANDLING_H
#define BC_ERRORHANDLING_H

#include <exception>
#include <string>

class BC_Exception: public std::exception
{
	std::string _msg;
public:
	BC_Exception(const std::string& msg) : _msg(msg) {};
	const char* what() const throw() { return _msg.c_str(); }
};

#endif