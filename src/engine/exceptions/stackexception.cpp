#include <memory>
#include <iostream>
#include "engine/exceptions/stackexception.hpp"
#include <sstream>

StackException::StackException(const std::string& message) : std::runtime_error(message) {
#ifdef __linux__
#include <execinfo.h>
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

const std::string& StackException::get_stack_trace() const {
	return this->_stack_trace;
}
