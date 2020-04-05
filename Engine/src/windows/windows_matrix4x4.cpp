#include <cmath>
#include "matrix4x4.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/transform.hpp"

math::Matrix4x4::Matrix4x4(bool zero)
{
    if (zero)
    {
        SetZero();
    }
	else
	{
		SetIdentity();
	}
}

math::Matrix4x4::Matrix4x4(float matrix[4][4])
{
    for (uint32_t row = 0; row < 4; ++row)
    {
        for (uint32_t column = 0; column < 4; ++column)
        {
            mMatrix[row][column] = matrix[row][column];
        }
    }
}

math::Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03,
                           float m10, float m11, float m12, float m13,
                           float m20, float m21, float m22, float m23,
                           float m30, float m31, float m32, float m33)
{
    mMatrix[0][0] = m00; mMatrix[0][1] = m01;  mMatrix[0][2] = m02;  mMatrix[0][3] = m03;
    mMatrix[1][0] = m10; mMatrix[1][1] = m11;  mMatrix[1][2] = m12;  mMatrix[1][3] = m13;
    mMatrix[2][0] = m20; mMatrix[2][1] = m21;  mMatrix[2][2] = m22;  mMatrix[2][3] = m23;
    mMatrix[3][0] = m30; mMatrix[3][1] = m31;  mMatrix[3][2] = m32;  mMatrix[3][3] = m33;
}

math::Matrix4x4 math::Matrix4x4::Inverse() const
{
    float a0 = mMatrix[0][0] * mMatrix[1][1] - mMatrix[0][1] * mMatrix[1][0];
    float a1 = mMatrix[0][0] * mMatrix[1][2] - mMatrix[0][2] * mMatrix[1][0];
    float a2 = mMatrix[0][0] * mMatrix[1][3] - mMatrix[0][3] * mMatrix[1][0];
    float a3 = mMatrix[0][1] *  mMatrix[1][2] - mMatrix[0][2] * mMatrix[1][1];
    float a4 = mMatrix[0][1] * mMatrix[1][3] - mMatrix[0][3] * mMatrix[1][1];
    float a5 = mMatrix[0][2] * mMatrix[1][3] - mMatrix[0][3] *  mMatrix[1][2];
    float b0 = mMatrix[2][0] * mMatrix[3][1] - mMatrix[2][1] * mMatrix[3][0];
    float b1 = mMatrix[2][0] * mMatrix[3][2] - mMatrix[2][2] * mMatrix[3][0];
    float b2 = mMatrix[2][0] * mMatrix[3][3] - mMatrix[2][3] * mMatrix[3][0];
    float b3 = mMatrix[2][1] * mMatrix[3][2] - mMatrix[2][2] * mMatrix[3][1];
    float b4 = mMatrix[2][1] * mMatrix[3][3] - mMatrix[2][3] * mMatrix[3][1];
    float b5 = mMatrix[2][2] * mMatrix[3][3] - mMatrix[2][3] * mMatrix[3][2];

    float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
    if (std::abs(det) <= 0.00000f)
    {
        ASSERT(false);
        return math::Matrix4x4(true);
    }

    math::Matrix4x4 inv;
    inv.mMatrix[0][0] = + mMatrix[1][1] * b5 - mMatrix[1][2] * b4 + mMatrix[1][3] * b3;
    inv.mMatrix[1][0] = - mMatrix[1][0] * b5 + mMatrix[1][2] * b2 - mMatrix[1][3] * b1;
    inv.mMatrix[2][0] = + mMatrix[1][0] * b4 - mMatrix[1][1] * b2 + mMatrix[1][3] * b0;
    inv.mMatrix[3][0] = - mMatrix[1][0] * b3 + mMatrix[1][1] * b1 - mMatrix[1][2] * b0;
    inv.mMatrix[0][1] = - mMatrix[0][1] * b5 + mMatrix[0][2] * b4 - mMatrix[0][3] * b3;
    inv.mMatrix[1][1] = + mMatrix[0][0] * b5 - mMatrix[0][2] * b2 + mMatrix[0][3] * b1;
    inv.mMatrix[2][1] = - mMatrix[0][0] * b4 + mMatrix[0][1] * b2 - mMatrix[0][3] * b0;
    inv.mMatrix[3][1] = + mMatrix[0][0] * b3 - mMatrix[0][1] * b1 + mMatrix[0][2] * b0;
    inv.mMatrix[0][2] = + mMatrix[3][1] * a5 - mMatrix[3][2] * a4 + mMatrix[3][3] * a3;
    inv.mMatrix[1][2] = - mMatrix[3][0] * a5 + mMatrix[3][2] * a2 - mMatrix[3][3] * a1;
    inv.mMatrix[2][2] = + mMatrix[3][0] * a4 - mMatrix[3][1] * a2 + mMatrix[3][3] * a0;
    inv.mMatrix[3][2] = - mMatrix[3][0] * a3 + mMatrix[3][1] * a1 - mMatrix[3][2] * a0;
    inv.mMatrix[0][3] = - mMatrix[2][1] * a5 + mMatrix[2][2] * a4 - mMatrix[2][3] * a3;
    inv.mMatrix[1][3] = + mMatrix[2][0] * a5 - mMatrix[2][2] * a2 + mMatrix[2][3] * a1;
    inv.mMatrix[2][3] = - mMatrix[2][0] * a4 + mMatrix[2][1] * a2 - mMatrix[2][3] * a0;
    inv.mMatrix[3][3] = + mMatrix[2][0] * a3 - mMatrix[2][1] * a1 + mMatrix[2][2] * a0;

    float invDet = 1.0f / det;
    inv.mMatrix[0][0] *= invDet;
    inv.mMatrix[0][1] *= invDet;
    inv.mMatrix[0][2] *= invDet;
    inv.mMatrix[0][3] *= invDet;

    inv.mMatrix[1][0] *= invDet;
    inv.mMatrix[1][1] *= invDet;
    inv.mMatrix[1][2] *= invDet;
    inv.mMatrix[1][3] *= invDet;

    inv.mMatrix[2][0] *= invDet;
    inv.mMatrix[2][1] *= invDet;
    inv.mMatrix[2][2] *= invDet;
    inv.mMatrix[2][3] *= invDet;

    inv.mMatrix[3][0] *= invDet;
    inv.mMatrix[3][1] *= invDet;
    inv.mMatrix[3][2] *= invDet;
    inv.mMatrix[3][3] *= invDet;

    return inv;
}

math::Matrix4x4 math::Matrix4x4::Transpose() const
{
	return Matrix4x4 
	{
			mMatrix[0][0], mMatrix[1][0], mMatrix[2][0], mMatrix[3][0],
			mMatrix[0][1], mMatrix[1][1], mMatrix[2][1], mMatrix[3][1],
			mMatrix[0][2], mMatrix[1][2], mMatrix[2][2], mMatrix[3][2],
			mMatrix[0][3], mMatrix[1][3], mMatrix[2][3], mMatrix[3][3]
	};
}

void math::Matrix4x4::Translate(const math::Vector3f& value)
{
	mMatrix[0][3] += value.X();
	mMatrix[1][3] += value.Y();
	mMatrix[2][3] += value.Z();
	mMatrix[3][3] = 1;
}

void math::Matrix4x4::Translate(float x, float y, float z)
{
	mMatrix[0][3] += x;
	mMatrix[1][3] += y;
	mMatrix[2][3] += z;
	mMatrix[3][3] = 1;
}

void math::Matrix4x4::Scale(float x, float y, float z)
{
	mMatrix[0][0] *= x;
	mMatrix[1][1] *= y;
	mMatrix[2][2] *= z;
	mMatrix[3][3] = 1;
}

void math::Matrix4x4::Rotate(const char axis, float degree)
{
	// TODO Implement without glm!
	float leftHandDegree = -degree; // OpenGL uses righthanded system but the engine uses lefthand
	glm::mat4 mtx;	
	switch (axis)
	{
	case 'X':
		mtx = glm::rotate(glm::radians(leftHandDegree), glm::vec3{1.0f, 0.0f, 0.f});
		break;
	case 'Y':
		mtx = glm::rotate(glm::radians(leftHandDegree), glm::vec3(0.0f, 1.0f, 0.f));
		break;
	case 'Z':
		mtx = glm::rotate(glm::radians(leftHandDegree), glm::vec3(0.0f, 0.0f, 1.0f));
		break;	
	}

	Matrix4x4 rotationMatrix = {
		mtx[0][0], mtx[0][1], mtx[0][2], mtx[0][3],
		mtx[1][0], mtx[1][1], mtx[1][2], mtx[1][3],
		mtx[2][0], mtx[2][1], mtx[2][2], mtx[2][3],
		mtx[3][0], mtx[3][1], mtx[3][2], mtx[3][3],
	};
	
	*this = *this * rotationMatrix;
}

math::Matrix4x4 math::Matrix4x4::Identity()
{
	math::Matrix4x4 mtx;
	mtx.SetIdentity();
	return mtx;
}

math::Matrix4x4 math::Matrix4x4::CreateViewMatrix(const math::Vector3f& pos, const math::Vector3f& up, const math::Vector3f& lookAt)
{
	glm::vec3 vecPos = { (float)pos.X(), (float)pos.Y(), (float)pos.Z() };
	glm::vec3 vecCamUp = { (float)up.X(), (float)up.Y(), (float)up.Z() };
	glm::vec3 vecLookAt = { (float)pos.X() + lookAt.X(),
						  (float)pos.Y() + lookAt.Y(),
						  (float)pos.Z() + lookAt.Z() };

	glm::mat4x4 mtx = glm::lookAt(vecPos, vecLookAt, vecCamUp);
	const auto matrix = math::Matrix4x4{
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3],
	};
	return matrix;
}

math::Matrix4x4 math::Matrix4x4::CreatePerspectiveProjectionMatrix(float frustrumNear, float frustrumFar,
	float frustrumTop, float frustrumBottom,
	float frustrumLeft, float frustrumRight)
{

	glm::mat4x4 mtx;
	mtx = glm::frustum((float)frustrumLeft, (float)frustrumRight, (float)frustrumBottom, (float)frustrumTop, 
		(float)frustrumNear, (float)frustrumFar);

	return math::Matrix4x4{
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3],
	};	
}

math::Matrix4x4 math::Matrix4x4::CreateOrthographicProjectionMatrix(float frustrumNear, float frustrumFar,
	float frustrumTop, float frustrumBottom,
	float frustrumLeft, float frustrumRight)
{
	glm::mat4x4 mtx;
	mtx = glm::ortho((float)frustrumLeft, (float)frustrumRight, (float)frustrumBottom, (float)frustrumTop, 
		(float)frustrumNear, (float)frustrumFar);

	return math::Matrix4x4{
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3],
	};
}
