#pragma once
#include <exception>
#include "String.h"

class MessageException : public std::exception
{
public:
	std::string m_msg;

	MessageException(const std::string msg) : m_msg(msg) {}
	~MessageException() {}

	virtual const char* what() const throw() {
		return m_msg.c_str();
	}
};

