#include <cmath>
#include "mathhelper.h"
#include "camera.h"
#include "glm/glm.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

std::shared_ptr<renderer::Camera> renderer::Camera::Create(
	const math::Vector3f& position,
	const math::Vector3f& worldUp,
	const math::Vector3f& lookAt,
	bool isPerspective) 
{
	return std::make_shared<Camera>(position, worldUp, lookAt, isPerspective);
}

renderer::Camera::Camera(const math::Vector3f& position,
	const math::Vector3f& worldUp,
	const math::Vector3f& lookAt,
	bool isPerspective)
	: mPosition(position),
	mWorldUp(worldUp),
	mLookAt(lookAt),
	mYaw(-90.0f),
	mPitch(0.0f),
	mIsPerspective(isPerspective)
{
	UpdateCameraVectors();
}

void renderer::Camera::SetFrustrum(float minDist, float maxDist, float fov, float aspectRatio)
{
	mFrustrumTop = minDist * std::tan(math::DegToRadians(fov) / 2.0f);
	mFrustrumRight = mFrustrumTop * aspectRatio;
	mFrustrumBottom = -mFrustrumTop;
	mFrustrumLeft = -mFrustrumRight;
	mFrustrumNear = minDist;
	mFrustrumFar = maxDist;
}

void renderer::Camera::SetFrustrum(float top, float bottom, float left, float right, float near, float far)
{
	mFrustrumTop = top;
	mFrustrumBottom = bottom;
	mFrustrumLeft = left;
	mFrustrumRight = right;
	mFrustrumNear = near;
	mFrustrumFar = far;
}

math::Vector3f renderer::Camera::ScreenSpaceToWorldSpace(float posX, float posY, float screenWidth, float screenHeight) const
{
	float x = 2.0f * posX / screenWidth - 1;
	float y = 2.0f * posY / screenHeight - 1;

	math::Vector4f screenPosition(x, -y, -1.0f, 1.0f);
	const math::Matrix4x4& viewProjectionInverse = (GetProjectionMatrix4x4() * GetViewMatrix4x4()).Inverse();
	math::Vector4f worldPosition = viewProjectionInverse * screenPosition;
	return { worldPosition.X() / worldPosition.W(), worldPosition.Y() / worldPosition.W(), worldPosition.Z() / worldPosition.W() };
}

void renderer::Camera::GenerateFrustrumPlanes(bool normalize)
{
	mFrustrum.ExtractPlanes(*this, normalize);
}

bool renderer::Camera::IsVisible(const math::Vector3f& point) const
{
	return mFrustrum.IsVisible(point);
}

bool renderer::Camera::IsVisible(const core::Box& box) const
{
	return mFrustrum.IsVisible(box);
}

bool renderer::Camera::IsVisible(const core::AABB& aabb) const
{
	return mFrustrum.IsVisible(aabb);
}

math::Matrix4x4 renderer::Camera::GetViewMatrix4x4() const
{
	glm::vec3 vecPos = { (float)mPosition.X(), (float)mPosition.Y(), (float)mPosition.Z() };
	glm::vec3 vecCamUp = { (float)mUp.X(), (float)mUp.Y(), (float)mUp.Z() };
	glm::vec3 vecLookAt = { (float)mPosition.X() + mLookAt.X(),
						  (float)mPosition.Y() + mLookAt.Y(),
						  (float)mPosition.Z() + mLookAt.Z() };

	glm::mat4x4 mtx = glm::lookAt(vecPos, vecLookAt, vecCamUp);
	const auto matrix = math::Matrix4x4{
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3],
	};
	return matrix;
}

math::Matrix4x4 renderer::Camera::GetProjectionMatrix4x4() const
{
	glm::mat4x4 mtx;
	if (mIsPerspective)
	{
		mtx = glm::frustum((float)mFrustrumLeft, (float)mFrustrumRight, (float)mFrustrumBottom, (float)mFrustrumTop, (float)mFrustrumNear, (float)mFrustrumFar);
	}
	else
	{		
		mtx = glm::ortho((float)mFrustrumLeft, (float) mFrustrumRight,(float) mFrustrumBottom, (float) mFrustrumTop, (float) mFrustrumNear, (float) mFrustrumFar);
	}	
	return math::Matrix4x4{
		mtx[0][0], mtx[1][0], mtx[2][0], mtx[3][0],
		mtx[0][1], mtx[1][1], mtx[2][1], mtx[3][1],
		mtx[0][2], mtx[1][2], mtx[2][2], mtx[3][2],
		mtx[0][3], mtx[1][3], mtx[2][3], mtx[3][3],
	};
}

void renderer::Camera::Move(const CameraMovementDirection& direction, float scale)
{
	switch (direction)
	{
	case CameraMovementDirection::FORWARD:
		mPosition += mLookAt * scale;
		break;
	case CameraMovementDirection::BACKWARD:
		mPosition -= mLookAt * scale;
		break;
	case CameraMovementDirection::LEFT:
		mPosition -= mRight * scale;
		break;
	case CameraMovementDirection::RIGHT:
		mPosition += mRight * scale;
		break;
	default:
		ASSERT(false);
		break;
	}
}

void renderer::Camera::Rotate(float x, float y)
{
	mYaw += x;
	mPitch += y;
	mPitch = math::Clamp(mPitch, -89.0f, 89.0f);

	UpdateCameraVectors();
}

void renderer::Camera::SetYaw(float yaw)
{
	mYaw = yaw;
	UpdateCameraVectors();
}

void renderer::Camera::SetPitch(float pitch)
{
	mPitch = pitch;
	mPitch = math::Clamp(mPitch, -89.0f, 89.0f);
	UpdateCameraVectors();
}

void renderer::Camera::UpdateCameraVectors()
{
	mLookAt.SetX(cos(math::DegToRadians(mYaw)) * cos(math::DegToRadians(mPitch)));
	mLookAt.SetY(sin(math::DegToRadians(mPitch)));
	mLookAt.SetZ(sin(math::DegToRadians(mYaw)) * cos(math::DegToRadians(mPitch)));
	mLookAt.Normalize();

	mRight = mLookAt.Cross(mWorldUp);
	mRight.Normalize();
	mUp = mRight.Cross(mLookAt);
	mUp.Normalize();
}

