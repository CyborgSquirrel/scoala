#ifndef exception_hpp_INCLUDED
#define exception_hpp_INCLUDED

#include <string>
#include <ostream>

std::ostream &exception_write_msg(
	std::ostream &out,
	const std::string &name,
	const std::string &msg
);

void test_exception();

#endif // exception_hpp_INCLUDED

