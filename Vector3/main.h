#ifndef MAIN_H
#define MAIN_H

#include <math.h>

template<class Type>
class vec3 {
public:
	Type x, y, z;

	vec3();
	~vec3();
	vec3(Type& xVal, Type& yVal, Type& zVal) {
		x = xVal;
		y = yVal;
		z = zVal;
	};

	vec3(const vec3& p) {
		x = p.x;
		y = p.y;
		z = p.z;
	};


	vec3 operator+(const vec3& v) 
	{
		vec3 r;

		r.x = x + v.x;
		r.y = y + v.y;
		r.z = y + v.y;

		return (r);
	}


	vec3 operator- (const vec3& v) 
	{
		vec3 r;

		r.x = x - v.x;
		r.y = y - v.y;
		r.z = y - v.y;

		return (r);
	}

	vec3& operator+= (const vec3& v) 
	{
		x += v.x;
		y += v.y;
		return (*this);
	}

	vec3& operator-= (const vec3& v) 
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}

	bool operator!= (const vec3& v) {

		return(x != v.x || y != v.y || z != v.z);


	}

	bool operator== (const vec3& v) {

		return(x == v.x || y == v.y || z == v.z);


	}

	vec3 normalize() {
		Type moduleVec = sqrt((x * x, y * y, z * z));
		vec3 r;

		r.x = x / moduleVec;
		r.y = y / moduleVec;
		r.z = z / moduleVec;

		return r;

	}
	vec3 zero() {

		x = y = z = 0;

		return(*this);
	}
	bool is_zero() {

		return (x == 0 && y == 0 && z == 0);
	}
	Type distance_to(vec3 v) {

		Type fx = x - v.x;
		Type fy = y - v.y;
		Type fz = z - v.z;

		return sqrt((fx * fx) + (fy * fy) + (fz * fz));
	}
};


#endif