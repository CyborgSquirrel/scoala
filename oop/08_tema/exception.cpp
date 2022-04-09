#include <gsl/gsl_assert>
#include <sstream>

#include "./exception.hpp"

AppException::AppException(const std::string &msg) : msg(msg) { }

std::ostream &operator<<(std::ostream &out, const AppException &ex) {
	out << ex.get_type() << ": " << ex.msg;
	return out;
}

std::string AppException::as_string() const {
	std::stringstream sstream;
	sstream << (*this);
	return sstream.str();
}
