// -*-C++-*-

#pragma once

#include <string>
#include <vector>

struct Constants {
	static const float pi;               // pi value
	static const float distance_epsilon; // Minimum distance
	static const float angle_epsilon;    // Minimun angle

	static const float degree_to_rad;
	static const float rad_to_degree;

	struct gl_texunits {
		static const int texture;    // Texture unit 0
		static const int bump;       // Texture unit 1
		static const int projective; // Texture unit 2
		static const int shadow;     // Texture unit 3
	};
};

bool distance_is_zero(float d);

std::string getFilename(const std::string &dir, const std::string & fname);

// print a vector
void writeV(const std::vector<float> & v);

// float 2 string
std::string float_to_string(float v);
