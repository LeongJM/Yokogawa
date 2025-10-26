/**
* Author:           Leong Jun Ming
* Date:             24/10/25
* Description:      Exception Class
**/

#ifndef BC_ERRORHANDLING_H
#define BC_ERRORHANDLING_H

#include <stdexcept> 
#include <string>

enum ErrorType: size_t
{
	InvalidArg = 0,
	OutOfRange,
	DivideByZero,
};

class BC_Exception: public std::exception
{
	ErrorType _type;
	std::string _msg;
public:
	BC_Exception(ErrorType type, const std::string& msg) noexcept : _type(type), _msg(msg) {};
	const char* what() const noexcept { return _msg.c_str(); }
	const char* type() const noexcept 
	{ 
		switch (_type)
		{
		case InvalidArg:
			return "Invalid Argument";
			break;
		case OutOfRange:
			return "Out Of Range";
			break;
		case DivideByZero:
			return "Divide By Zero";
			break;
		default:
			return "Undefined";
			break;
		}
	}
};

#endif