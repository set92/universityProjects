// -*-C++-*-

#pragma once

class Vector3 {

public:

	// Class constants
	static const float epsilon;   // minimum length

	static const Vector3 ZERO;    // (0,0,0)
	static const Vector3 UNIT_X;  // (1,0,0)
	static const Vector3 UNIT_Y;  // (0,1,0)
	static const Vector3 UNIT_Z;  // (0,0,1)
	static const Vector3 ONE;     // (1,1,1)

	// Constructors
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const float *ptr);
	Vector3(const Vector3 & vec);
	Vector3 & operator=(const Vector3 & vec);

	// swap two vectors
	void swap(Vector3 & vec);

	// Coordinate access
	float operator[](int idx) const;
	float & operator[](int idx);
	float x () const;
	float & x ();
	float y () const;
	float& y ();
	float z () const;
	float& z ();

	// convert to pointer to 3 flost vector
	const float * to_3fv() const;

	// Arithmetic operations.
	friend Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator-(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& lhs, const Vector3& rhs);
	friend Vector3 operator*(const Vector3& vec, float scalar);
	friend Vector3 operator*(float scalar, const Vector3& vec);
	friend Vector3 operator/(const Vector3& vec, float scalar);
	friend Vector3 operator/(float scalar, const Vector3& vec);

	void operator +=(const Vector3 & rhs);
	void operator -=(const Vector3 & rhs);
	void operator *=(float scalar);
	void operator /=(float scalar);

	float dot(const Vector3& rhs) const;
	// cross product follows right-handed rule
	void cross(const Vector3& rhs); // this = this x rhs
	friend Vector3 crossVectors(const Vector3& lhs, const Vector3& rhs);

	float length() const; // vector module
	float lengthSquare() const; // square of length

	// Set vector to unit length.
	// Returns the old length
	// If zero vector, set to UNIT_Z vector.
	float normalize();
	// Normalize using L1 (so that coords. sum to one)
	float normalizeL1();

	// Whether vector is zero
	bool isZero() const;

	// convert to spherical coordinates
	// See documentation in vector3.cc
	void sphereCoordinates(float & alpha, float & beta) const;
	void print() const;

private:
	float m_v[3];
};
