#include <memory>
#include <iostream>
#include "engine/exceptions/stackexception.hpp"
#include <execinfo.h>
#include <sstream>
#include <utility>

StackException::StackException(std::string message) : _message(std::move(message)) {
#ifdef __linux__
	void *array[128];
	int size = backtrace(array, 128);
	std::unique_ptr<char*, decltype(&std::free)> strings(backtrace_symbols(array, size), &std::free);
	if (!size) {
		_stack_trace = "Stack trace not available";
		return;
	}

	std::ostringstream oss;
	for (int i = 1; i < size; i++)
		oss << strings.get()[i] << '\n';
	_stack_trace = oss.str();
#else
	_stack_trace = "Stack trace not available on this platform";
#endif
}

std::string StackException::get_stack_trace() const {
	return this->_stack_trace;
}

const char *StackException::what() const noexcept {
	return this->_message.c_str();
}