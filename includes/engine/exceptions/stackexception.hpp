#pragma once


#include <exception>
#include <string>

class StackException : public std::exception {
public:
	explicit StackException(const char* message);
	~StackException() override = default;

	std::string get_stack_trace() const;
	const char* what() const noexcept override;

private:
	std::string _stack_trace;
	std::string _message;

};
