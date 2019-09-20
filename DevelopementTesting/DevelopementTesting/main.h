#ifndef MAIN_H
#define MAIN_H


#include <iostream>
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

	vec3(Type& xVal, Type& yVal) {
		x = xVal;
		y = yVal;
		z = 0;
	};

	Type getX();
	Type getY();
	Type getZ();

	Type sumValuesMagi();
	void augmentX();

	Type normalize();
	void zero();
	bool is_zero();
	Type distance_to(vec3);


};


template<class Type>
Type vec3 <Type>::getX() {


	return x;


}

template<class Type>
Type vec3 <Type>::getY() {


	return y;


}template<class Type>
Type vec3 <Type>::getZ() {


	return z;


}

template<class Type>
Type vec3 <Type>::sumValuesMagi() {


	return this->x + this->y + this->z;


}

template<class Type>
void vec3 <Type>::augmentX() {

	x += y;


}

template<class Type>
Type vec3 <Type>::normalize() {


	Type moduleVec = squareroot(x * x, y * y, z * z);

		return(x / moduleVec, y / moduleVec, z / moduleVec);

}

template<class Type>
void vec3 <Type>::zero() {

	x = 0;
	y = 0;
	z = 0;

}


template<class Type>
bool vec3 <Type>::is_zero() {

	if ((x + y + z) == 0)
		return true;
	else
		return false;
}

template<class Type>
Type vec3 <Type>::distance_to(vec3 secondVector) {


	Type moduleVec1 = squareroot(x * x, y * y, z * z);
	Type moduleVec2 = squareroot(x * x, y * y, z * z);


		return(x / moduleVec1, y / moduleVec1, z / moduleVec1);

}
#endif