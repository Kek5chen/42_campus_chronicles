#include <iostream>
#include <memory>
#include <sstream>
#include <csignal>
#include "engine/error_handler.hpp"
#include "SDL_messagebox.h"

#if defined(__linux__) || defined(__APPLE__)
#include <execinfo.h>
static void print_stack_trace() {
	std::ostringstream oss;
	void *array[128];
	int size = backtrace(array, 128);
	std::unique_ptr<char*, decltype(&std::free)> strings(backtrace_symbols(array, size), &std::free);
	oss << "--- An uncaught exception caused the program to crash --- \n\nStack trace:\n";
	if (size) {
		for (int i = 0; i < size; i++)
			oss << strings.get()[i] << '\n';
	} else
		oss << "Stack trace not available" << std::endl;
	std::cerr << oss.str() << std::endl;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", oss.str().c_str(), nullptr);
}
#else
#ifdef __WINDOWS__
// TODO: some windows user please implement this
static void print_stack_trace() {
	std::ostringstream oss;
	oss << "--- An uncaught exception caused the program to crash --- \n\nStack trace not available on this platform" << std::endl;
	std::cerr << oss.str() << std::endl;
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", oss.str().c_str(), nullptr);
}
#endif
#endif

static void signal_handler(int signal) {
	std::cerr << "Signal " << signal << " caught" << std::endl;
	print_stack_trace();
	exit(1);
}

void register_signal_handler() {
	signal(SIGSEGV, signal_handler);
	signal(SIGABRT, signal_handler);
	signal(SIGFPE, signal_handler);
	signal(SIGILL, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}
