#ifndef _Vector_H_
#define _Vector_H_

//////////////////////////////
// Vector.h
// A simple vector class for storing game entity transform data
// with helper and utility methods.
//////////////////////////////

// TODO: Minor efficiency improvement. in operator+=, should I change to use
// { x += value; } or keep { x = x + value; } ? What is more register efficient?

// TODO: Look at operator== for float value comparison
// TODO: inline?
// TODO: fequal
#include "Math/MathHelpers.h"

#include <cmath> // sqrt

struct Vector2
{
	// values
	float x = 0.0f;
	float y = 0.0f;

	// constructors + destructors
	Vector2() {}
	Vector2(const float value) { x = value; y = value; }
	Vector2(const float valueX, const float valueY) { x = valueX; y = valueY; }
	Vector2(const int value) { x = (float)value; y = (float)value; }
	Vector2(const int valueX, const int valueY) { x = (float)valueX; y = (float)valueY; }

	~Vector2() {}

	// operator overloads
	Vector2 operator +(const float value) const { return Vector2(x + value, y + value); }
	Vector2 operator +(const Vector2& value) const { return Vector2(x + value.x, y + value.y); }

	Vector2 operator -(const float value) const { return Vector2(x - value, y - value); }
	Vector2 operator -(const Vector2& value) const { return Vector2(x - value.x, y - value.y); }

	Vector2 operator *(const float value) const { return Vector2(x * value, y * value); }
	Vector2 operator *(const Vector2& value) const { return Vector2(x * value.x, y * value.y); }

	Vector2 operator /(const float value) const { return Vector2(x / value, y / value); }
	Vector2 operator /(const Vector2& value) const { return Vector2(x / value.x, y / value.y); }

	void operator +=(const float value) { x = x + value; y = y + value; }
	void operator +=(const Vector2& value) { x = x + value.x; y = y + value.y; }

	void operator -=(const float value) { x = x - value; y = y - value; }
	void operator -=(const Vector2& value) { x = x - value.x; y = y - value.y; }

	void operator *=(const float value) { x = x * value; y = y * value; }
	void operator *=(const Vector2& value) { x = x * value.x; y = y * value.y; }

	void operator /=(const float value) { x = x / value; y = y / value; }
	void operator /=(const Vector2& value) { x = x / value.x; y = y / value.y; }

	bool operator ==(const float value) { return x == value && y == value; }
	bool operator ==(const Vector2& value) { return x == value.x && y == value.y; }

	bool operator !=(const float value) { return x != value || y != value; }
	bool operator !=(const Vector2& value) { return x != value.x || y != value.y; }

	// helper + utility functions
	// TODO: Rewrite
	float LengthSquared() const { return x * x + y * y; }
	float Length() const { return sqrtf(x*x + y * y); }
	Vector2 GetNormalized() const { float len = Length(); if (fequal(len, 0)) return Vector2(x, y); len = 1.0f / len; return Vector2(x*len, y*len); }
	Vector2 Normalize() { float len = Length(); if (!fequal(len, 0)) { x /= len; y /= len; } return *this; }
	// TODO: write... add, set, scale, cross, dot methods
};

struct Vector3
{
	// values
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	// constructors + destructors
	Vector3() {}
	Vector3(const float value) { x = value; y = value; z = value; }
	Vector3(const float valueX, float valueY, float valueZ) { x = valueX; y = valueY; z = valueZ; }
	Vector3(const int value) { x = (float)value; y = (float)value; z = (float)value; }
	Vector3(const int valueX, int valueY, int valueZ) { x = (float)valueX; y = (float)valueY; z = valueZ; }

	~Vector3() {}

	// operator overloads
	Vector3 operator +(const float value) const { return Vector3(x - value, y - value, z - value); }
	Vector3 operator +(const Vector3& value) const { return Vector3(x + value.x, y + value.y, z + value.z); }

	Vector3 operator -(const float value) const { return Vector3(x - value, y - value, z - value); }
	Vector3 operator -(const Vector3& value) const { return Vector3(x - value.x, y - value.y, z - value.z); }

	Vector3 operator *(const float value) const  { return Vector3(x * value, y * value, z * value); }
	Vector3 operator *(const Vector3& value) const { return Vector3(x * value.x, y * value.y, z * value.z); }

	Vector3 operator /(const float value) const  { return Vector3(x / value, y / value, z / value); }
	Vector3 operator /(const Vector3& value) const  { return Vector3(x / value.x, y / value.y, z / value.z); }

	void operator +=(const float value) { x = x + value; y = y + value; z = z + value; }
	void operator +=(const Vector3& value) { x = x + value.x; y = y + value.y; z = z + value.z; }

	void operator -=(const float value) { x = x - value; y = y - value; z = z - value; }
	void operator -=(const Vector3& value) { x = x - value.x; y = y - value.y; z = z - value.z; }

	void operator *=(const float value) { x = x * value; y = y * value; z = z * value; }
	void operator *=(const Vector3& value) { x = x * value.x; y = y * value.y; z = z * value.z;}

	void operator /=(const float value) { x = x / value; y = y / value; z = z / value; }
	void operator /=(const Vector3& value) { x = x / value.x; y = y / value.y; z = z / value.z; }

	bool operator ==(const float value) { return x == value && y == value && z == value; }
	bool operator ==(const Vector3& value) { return x == value.x && y == value.y && z == value.z; }

	bool operator !=(const float value) { return x != value || y != value || z != value; }
	bool operator !=(const Vector3& value) { return x != value.x || y != value.y || z != value.z; }

	// helper + utility functions
	// TODO: Rewrite
	float LengthSquared() const { return x*x + y*y + z*z; }
	float Length() const { return sqrtf(x*x + y * y + z * z); }
	Vector3 GetNormalized() const { float len = Length(); if( fequal(len,0) ) return Vector3(x,y,z); len = 1.0f/len; return Vector3(x*len, y*len, z*len);}
	Vector3 Normalize() { float len = Length(); if (!fequal(len, 0)) { x /= len; y /= len; z /= len; } return *this; }
	Vector3 Cross(const Vector3& o) const { return Vector3((y*o.z - z * o.y), (z*o.x - x * o.z), (x*o.y - y * o.x)); }
	float Dot(const Vector3 &o) const { return x * o.x + y * o.y + z * o.z; }
};

struct Vector4
{
	// values
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	// constructors + destructors
	Vector4() {}
	Vector4(const float value) { x = value; y = value; }
	Vector4(const float valueX, const float valueY, float valueZ, float valueW) { x = valueX; y = valueY; z = valueZ; w = valueW; }
	Vector4(const int value) { x = (float)value; y = (float)value; z = (float)value; w = (float)value; }
	Vector4(const int valueX, const int valueY, const int valueZ, const int valueW) { x = (float)valueX; y = (float)valueY; z = (float)valueZ; w = valueW; }

	~Vector4() {}

	// operator overloads

	// helper + utility functions
};

// convenient typedefs
typedef Vector2 vec2;
typedef Vector3 vec3;
typedef Vector4 vec4;

#endif // !_Vector_H_
