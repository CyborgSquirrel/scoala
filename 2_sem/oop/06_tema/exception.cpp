#include <cassert>

#include "./exception.hpp"

std::ostream &exception_write_msg(
	std::ostream &out,
	const std::string &name,
	const std::string &msg
) {
	out << name << ": " << msg;
	return out;
}

#include <sstream>
void test_exception() {
	std::stringstream sstream;
	exception_write_msg(sstream, "ex", "oopsie");
	assert(sstream.str() == "ex: oopsie");
}
