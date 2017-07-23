#include "tools.h"
#include <cmath>
#include <cstdio>
#include <sstream> // for ostringstream

using std::string;

const float Constants::pi = 3.14159265359f;
const float Constants::distance_epsilon = 1e-05f;
const float Constants::angle_epsilon = 0.00872665f;  // 0.5 degrees

const float Constants::degree_to_rad = 0.0174533f; // 2.0 * 3.1415927 / 360.0
const float Constants::rad_to_degree = 57.2958f;   // 360 / ( 2.0 * 3.1415927 )

const int Constants::gl_texunits::texture = 0;
const int Constants::gl_texunits::bump = 1;
const int Constants::gl_texunits::projective = 2;
const int Constants::gl_texunits::shadow = 3;

bool distance_is_zero(float d) {
	return fabs(d) < Constants::distance_epsilon;
}

std::string getFilename(const std::string &dir, const std::string & fname) {
	string res(dir);
	if (dir[dir.size() - 1] != '/') res.append("/");
	return res + fname;
}

void writeV(const std::vector<float> & v) {
	std::vector<float>::const_iterator it = v.begin();
	std::vector<float>::const_iterator end = v.end();
	printf("(");
	if (it != end) {
		end--;
		for(; it != end; ++it)
			printf("%.2f, ", *it);
		printf("%.2f", *end);
	}
	printf(")");
}

std::string float_to_string(float v) {
	std::ostringstream out;
	out << v;
	return out.str();
}
