#include "vector3f.h"
#include <math.h>

const math::Vector3f math::Vector3f::Up = { 0.0f, 1.0f, 0.0f };
const math::Vector3f math::Vector3f::Forward = { 0.0f, 0.0f, -1.0f };
const math::Vector3f math::Vector3f::Left = { -1.0f, 0.0f, 0.0f };

math::Vector3f::Vector3f()
{
	mVec.mX = 0;
	mVec.mY = 0;
	mVec.mZ = 0;
}

math::Vector3f::Vector3f(float x, float y, float z)
{
	mVec.mX = x;
	mVec.mY = y;
	mVec.mZ = z;
}

math::Vector3f& math::Vector3f::operator +=(const math::Vector3f& other)
{
	mVec.mX += other.mVec.mX;
	mVec.mY += other.mVec.mY;
	mVec.mZ += other.mVec.mZ;
	return *this;
}

math::Vector3f& math::Vector3f::operator -=(const math::Vector3f& other)
{
	mVec.mX -= other.mVec.mX;
	mVec.mY -= other.mVec.mY;
	mVec.mZ -= other.mVec.mZ;
	return *this;
}

math::Vector3f math::Vector3f::operator -(const math::Vector3f& other) const
{
	Vector3f vec = *this;
	vec.mVec.mX -= other.mVec.mX;
	vec.mVec.mY -= other.mVec.mY;
	vec.mVec.mZ -= other.mVec.mZ;
	return vec;
}

math::Vector3f math::Vector3f::operator +(const Vector3f& other) const
{
	Vector3f vec = *this;
	vec.mVec.mX += other.mVec.mX;
	vec.mVec.mY += other.mVec.mY;
	vec.mVec.mZ += other.mVec.mZ;
	return vec;
}

math::Vector3f math::Vector3f::operator *(float scalar) const
{
	Vector3f vec = *this;
	vec.mVec.mX *= scalar;
	vec.mVec.mY *= scalar;
	vec.mVec.mZ *= scalar;	
	return vec;
}

void math::Vector3f::Normalize()
{
	const float length = Length();
	mVec.mX /= length;
	mVec.mY /= length;
	mVec.mZ /= length;
}

float math::Vector3f::Dot(const math::Vector3f& other) const
{
	return (mVec.mX * other.mVec.mX) 
		+ (mVec.mY * other.mVec.mY) 
		+ (mVec.mZ + other.mVec.mZ);	
}

math::Vector3f math::Vector3f::Cross(const math::Vector3f& other) const
{
	Vector3f cross;
	cross.mVec.mX = (mVec.mY * other.mVec.mZ) - (mVec.mZ * other.mVec.mY);
	cross.mVec.mY = (mVec.mZ * other.mVec.mX) - (mVec.mX * other.mVec.mZ);
	cross.mVec.mZ = (mVec.mX * other.mVec.mY) - (mVec.mY * other.mVec.mX);	
	return cross;
}

float math::Vector3f::Length() const
{
	return sqrt((double)mVec.mX * (double)mVec.mX +
		(double)mVec.mY * (double)mVec.mY + 
		(double)mVec.mZ * (double)mVec.mZ);
}
