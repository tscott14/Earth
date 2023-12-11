#include "OrbitalCamera.hpp"

#include <Utilities/GeneralMath.hpp>

OrbitalCamera::OrbitalCamera(float px, float py, float pz, float fov, float aspect, float near, float far)
    : mPosition(0, 0, 0),
      mPhysics(1, 2.0f, SphericalPosition(0, 0, 0), SphericalPosition(0, 0, 0)),
      mSettings(fov, aspect, near, far)
{
    SetCartesPosition(px, py, pz);
    UpdateViewMatrix();
    UpdateProjMatrix();
}

auto OrbitalCamera::Update(Timestep timestep) -> void
{
    static const float MIN_ALTITUDE = 1.5;
    static const float MAX_ALTITUDE = 100;
    static const float MIN_THETA = 15;
    static const float MAX_THETA = 180 - MIN_THETA;

    SphericalPosition &vel = mPhysics.mVelocity;
    SphericalPosition &accel = mPhysics.mAcceleration;

    vel.mAltitude += accel.mAltitude * timestep;
    vel.mTheta += accel.mTheta * timestep;
    vel.mPhi += accel.mPhi * timestep;

    float acceleration_damper = 4;
    accel.mAltitude -= acceleration_damper * accel.mAltitude * timestep;
    accel.mTheta -= acceleration_damper * accel.mTheta * timestep;
    accel.mPhi -= acceleration_damper * accel.mPhi * timestep;

    vel.mAltitude -= vel.mAltitude * mPhysics.mDrag * timestep;
    vel.mTheta -= vel.mTheta * mPhysics.mDrag * timestep;
    vel.mPhi -= vel.mPhi * mPhysics.mDrag * timestep;

    mPosition.mAltitude += vel.mAltitude * timestep;
    mPosition.mTheta += vel.mTheta * timestep;
    mPosition.mPhi += vel.mPhi * timestep;

    if (mPosition.mAltitude < MIN_ALTITUDE)
    {
        mPosition.mAltitude = MIN_ALTITUDE;
        accel.mAltitude = 0;
        vel.mAltitude = 0;
    }
    if (mPosition.mAltitude > MAX_ALTITUDE)
    {
        mPosition.mAltitude = MAX_ALTITUDE;
        accel.mAltitude = 0;
        vel.mAltitude = 0;
    }

    if (mPosition.mTheta < MIN_THETA)
        mPosition.mTheta = MIN_THETA;
    if (mPosition.mTheta > MAX_THETA)
        mPosition.mTheta = MAX_THETA;

    while (mPosition.mPhi < 0)
        mPosition.mPhi += 360;
    while (mPosition.mPhi > 360)
        mPosition.mPhi -= 360;
}

auto OrbitalCamera::ChangeAcceleration(float d_altitude,
                                       float d_theta,
                                       float d_phi)
    -> const SphericalPosition &
{
    SphericalPosition &sp = mPhysics.mAcceleration;
    sp.mAltitude += d_altitude;
    sp.mTheta += d_theta;
    sp.mPhi += d_phi;

    return sp;
}

auto OrbitalCamera::ChangePhysicalAcceleration(float d_altitude_force,
                                               float d_theta_force,
                                               float d_phi_force)
    -> const SphericalPosition &
{
    SphericalPosition &sp = mPhysics.mAcceleration;
    sp.mAltitude += d_altitude_force / mPhysics.mMass;
    sp.mTheta += d_theta_force / mPhysics.mMass;
    sp.mPhi += d_phi_force / mPhysics.mMass;

    return sp;
}

auto OrbitalCamera::ChangeVelocity(float d_altitude,
                                   float d_theta,
                                   float d_phi)
    -> const SphericalPosition &
{
    SphericalPosition &sp = mPhysics.mVelocity;
    sp.mAltitude += d_altitude;
    sp.mTheta += d_theta;
    sp.mPhi += d_phi;

    return sp;
}

auto OrbitalCamera::SetAcceleration(float altitude,
                                    float theta,
                                    float phi)
    -> const SphericalPosition &
{
    SphericalPosition &sp = mPhysics.mAcceleration;
    sp.mAltitude = altitude;
    sp.mTheta = theta;
    sp.mPhi = phi;

    return sp;
}

auto OrbitalCamera::SetPhysicalAcceleration(float altitude_force,
                                            float theta_force,
                                            float phi_force)
    -> const SphericalPosition &
{
    SphericalPosition &sp = mPhysics.mAcceleration;
    sp.mAltitude = altitude_force / mPhysics.mMass;
    sp.mTheta = theta_force / mPhysics.mMass;
    sp.mPhi = phi_force / mPhysics.mMass;

    return sp;
}

auto OrbitalCamera::SetVelocity(float altitude,
                                float theta,
                                float phi)
    -> const SphericalPosition &
{
    SetAcceleration(0, 0, 0);
    SphericalPosition &sp = mPhysics.mVelocity;
    sp.mAltitude = altitude;
    sp.mTheta = theta;
    sp.mPhi = phi;
    return sp;
}

auto OrbitalCamera::Move(float du,
                         float dv,
                         float dz)
    -> glm::vec3
{
    static const float MIN_ALTITUDE = 1.5;
    static const float MAX_ALTITUDE = 100;
    static const float MIN_THETA = 15;
    static const float MAX_THETA = 180 - MIN_THETA;

    mPosition.mAltitude += dz;
    mPosition.mTheta += dv;
    mPosition.mPhi += du;

    if (mPosition.mAltitude < MIN_ALTITUDE)
        mPosition.mAltitude = MIN_ALTITUDE;
    if (mPosition.mAltitude > MAX_ALTITUDE)
        mPosition.mAltitude = MAX_ALTITUDE;

    if (mPosition.mTheta < MIN_THETA)
        mPosition.mTheta = MIN_THETA;
    if (mPosition.mTheta > MAX_THETA)
        mPosition.mTheta = MAX_THETA;

    while (mPosition.mPhi < 0)
        mPosition.mPhi += 360;
    while (mPosition.mPhi > 360)
        mPosition.mPhi -= 360;

    return GenerateCartesianPosition();
}

auto OrbitalCamera::SetCartesPosition(float x,
                                      float y,
                                      float z)
    -> glm::vec3
{
    float altitude = glm::vec3(x, y, z).length();
    float theta = acos(y / altitude);
    float phi = atan2(z, x);

    mPosition.mAltitude = altitude;
    mPosition.mTheta = theta;
    mPosition.mPhi = phi;

    return glm::vec3(x, y, z);
}

auto OrbitalCamera::SetSpherePosition(float a,
                                      float t,
                                      float p)
    -> const SphericalPosition &
{
    mPosition.mAltitude = a;
    mPosition.mTheta = t;
    mPosition.mPhi = p;
    return mPosition;
}

auto OrbitalCamera::SetCameraSettings(float fov,
                                      float aspect,
                                      float near,
                                      float far)
    -> const CameraSettings &
{
    mSettings.mFOV = fov;
    mSettings.mAspect = aspect;
    mSettings.mNear = near;
    mSettings.mFar = far;
    return mSettings;
}

auto OrbitalCamera::UpdateViewMatrix(const glm::vec3 &target) -> glm::mat4 &
{
    static const glm::vec3 UP(0, 1, 0);
    mViewMatrix = glm::lookAt(GenerateCartesianPosition(), target, UP);
    return mViewMatrix;
}

auto OrbitalCamera::UpdateProjMatrix() -> glm::mat4 &
{
    auto fov = mSettings.mFOV;
    auto aspect = mSettings.mAspect;
    auto near = mSettings.mNear;
    auto far = mSettings.mFar;
    mProjMatrix = glm::perspective(fov, aspect, near, far);

    return mProjMatrix;
}

auto OrbitalCamera::GenerateCartesianPosition() const -> glm::vec3
{
    float altitude = mPosition.mAltitude;
    float theta = glm::radians(mPosition.mTheta);
    float phi = glm::radians(mPosition.mPhi);

    float sin_theta = sin(theta);
    float x = altitude * cos(phi) * sin_theta;
    float y = altitude * cos(theta);
    float z = altitude * sin(phi) * sin_theta;
    return glm::vec3(x, y, z);
}