#include "FreeCamera.hpp"

#include <Utilities/GeneralMath.hpp>

FreeCamera::FreeCamera(float px, float py, float pz,
                       float rx, float ry, float rz,
                       float fov, float aspect, float near, float far)
    : mPosition(px, py, pz),
      mRotation(rx, ry, rz),
      mSettings(fov, aspect, near, far)
{
    UpdateViewMatrix();
    UpdateProjMatrix();
}

auto FreeCamera::Move(float dx, float dy, float dz) -> glm::vec3 &
{
    //float sp = sin(glm::radians(mRotation.x));
    //float cp = cos(glm::radians(mRotation.x));
    float sy = sin(glm::radians(mRotation.y));
    float cy = cos(glm::radians(mRotation.y));

    float fxdx = dx * cy;
    float fzdx = dx * sy;
    float fxdz = dz * sy;
    float fzdz = dz * cy;

    mPosition.x += fxdz - fxdx;
    mPosition.y += dy;
    mPosition.z += -(fzdz + fzdx);
    return mPosition;
}

auto FreeCamera::Rotate(float dx, float dy, float dz) -> glm::vec3 &
{
    mRotation.x += dx;
    mRotation.y += dy;
    mRotation.z += dz;
    return mRotation;
}

auto FreeCamera::SetPosition(float px, float py, float pz) -> glm::vec3 &
{
    mPosition.x = px;
    mPosition.y = py;
    mPosition.z = pz;
    return mPosition;
}

auto FreeCamera::SetRotation(float px, float py, float pz) -> glm::vec3 &
{
    mRotation.x = px;
    mRotation.y = py;
    mRotation.z = pz;
    return mRotation;
}

auto FreeCamera::UpdateViewMatrix() -> glm::mat4 &
{
    const auto translation = glm::translate(glm::mat4(1.0f), -mPosition);
    const auto rotation = gm::Rotate(mRotation);
    mViewMatrix = rotation * translation;
    return mViewMatrix;
}

auto FreeCamera::UpdateProjMatrix() -> glm::mat4 &
{
    auto fov = mSettings.mFOV;
    auto aspect = mSettings.mAspect;
    auto near = mSettings.mNear;
    auto far = mSettings.mFar;
    mProjMatrix = glm::perspective(fov, aspect, near, far);

    return mProjMatrix;
}