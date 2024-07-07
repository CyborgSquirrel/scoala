#include <gsl/gsl_assert>
#include <iostream>
#include <algorithm>
#include <memory>

#include "./vec.hpp"

VecException::VecException(const std::string &msg) : msg(msg) { }
