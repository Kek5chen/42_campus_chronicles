#pragma once


#include <exception>
#include <string>

class StackException : public std::runtime_error {
public:
	explicit StackException(const std::string&  message);
	~StackException() override = default;

	std::string get_stack_trace() const;

private:
	std::string _stack_trace;

};
