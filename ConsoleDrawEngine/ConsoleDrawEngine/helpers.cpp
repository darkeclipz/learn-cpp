#include <string>
#include <sstream>
#include <iomanip>

std::string FormatFloat(double x, int precision = 2) {
	std::ostringstream ss;
	ss << std::fixed << std::setprecision(precision) << x;
	return ss.str();
}