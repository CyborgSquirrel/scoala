#ifndef exception_hpp_INCLUDED
#define exception_hpp_INCLUDED

#include <string>
#include <ostream>

class AppException {
private:
	std::string msg;
	virtual std::string get_type() const = 0;
public:
	AppException(const std::string &msg);
	friend std::ostream &operator<<(std::ostream &out, const AppException &ex);
	std::string as_string() const;
};
std::ostream &operator<<(std::ostream &out, const AppException &ex);

#endif // exception_hpp_INCLUDED

