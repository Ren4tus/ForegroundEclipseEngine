//#pragma once
//using namespace std;
//
//class Vector3
//{
//public:
//	double x, y, z;
//
//public:
//	Vector3() {
//		x = 0.0;
//		y = 0.0;
//		z = 0.0;
//	}
//	Vector3(double _x, double _y, double _z)
//		: x(_x), y(_y), z(_z)
//	{
//
//	}
//	void inverse()
//	{
//		x = -x;
//		y = -y;
//		z = -z;
//	}
//
//
//};
#pragma once
#include<iostream>
#include<math.h>
#include<assert.h>
using namespace std;
typedef float f;
class Vector3D
{
public:
	f x, y, z;
	Vector3D()  //constructor
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3D(f x1, f y1, f z1 = 0)     //initializing object with values.
	{
		x = x1;
		y = y1;
		z = z1;
	}
	Vector3D(const Vector3D& vec);    //copy constructor
	Vector3D operator+(const Vector3D& vec);    //addition
	Vector3D& operator+=(const Vector3D& vec);  ////assigning new result to the vector
	Vector3D operator-(const Vector3D& vec);    //substraction
	Vector3D& operator-=(const Vector3D& vec);  //assigning new result to the vector
	Vector3D operator*(f value);    //multiplication
	Vector3D& operator*=(f value);  //assigning new result to the vector.
	Vector3D operator/(f value);    //division
	Vector3D& operator/=(f value);  //assigning new result to the vector
	Vector3D& operator=(const Vector3D& vec);
	f dot_product(const Vector3D& vec); //scalar dot_product
	Vector3D cross_product(const Vector3D& vec);    //cross_product
	f magnitude();  //magnitude of the vector
	Vector3D normalization();   //nor,malized vector
	f square(); //gives square of the vector

	f distance(const Vector3D& vec);    //gives distance between two vectors
	f show_X(); //return x
	f show_Y(); //return y
	f show_Z(); //return z
	void disp();    //display value of vectors
};


