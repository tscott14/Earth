#ifndef ORBITAL_CAMERA_HPP
#define ORBITAL_CAMERA_HPP

#include <glm/glm.hpp>
#include "Scene/Environment/Camera/Camera.hpp"

struct SphericalPosition
{
    float mAltitude{};
    float mTheta{};
    float mPhi{};

    SphericalPosition() = default;
    SphericalPosition(float altitude, float theta, float phi)
        : mAltitude(altitude), mTheta(theta), mPhi(phi)
    {
    }
};

struct CameraPhysics
{
    float mMass{};
    float mDrag{};
    SphericalPosition mAcceleration{};
    SphericalPosition mVelocity{};

    CameraPhysics() = default;
    CameraPhysics(float mass, float drag, SphericalPosition accel, SphericalPosition velocity)
        : mMass(mass),
          mDrag(drag),
          mAcceleration(accel),
          mVelocity(velocity)
    {
    }
};

class OrbitalCamera : public Camera
{
private:
    SphericalPosition mPosition{};
    CameraPhysics mPhysics{};

    CameraSettings mSettings{};

    glm::mat4 mViewMatrix{};
    glm::mat4 mProjMatrix{};

public:
    OrbitalCamera() = default;
    OrbitalCamera(float, float, float,
                  float = 70, float = 1, float = 0.01, float = 1000);

    auto Update(Timestep) -> void;

    auto ChangeAcceleration(float, float, float) -> const SphericalPosition &;
    auto ChangePhysicalAcceleration(float, float, float) -> const SphericalPosition &;
    auto ChangeVelocity(float, float, float) -> const SphericalPosition &;
    auto SetAcceleration(float, float, float) -> const SphericalPosition &;
    auto SetPhysicalAcceleration(float, float, float) -> const SphericalPosition &;
    auto SetVelocity(float, float, float) -> const SphericalPosition &;

    auto Move(float, float, float) -> glm::vec3;
    auto SetCartesPosition(float, float, float) -> glm::vec3;
    auto SetSpherePosition(float, float, float) -> const SphericalPosition &;
    auto SetCameraSettings(float, float, float, float) -> const CameraSettings &;

    auto UpdateViewMatrix(const glm::vec3 & = glm::vec3(0, 0, 0)) -> glm::mat4 &;
    auto UpdateProjMatrix() -> glm::mat4 &;

    auto GenerateCartesianPosition() const -> glm::vec3;

    auto GetSphericalPosition() const -> const SphericalPosition & { return mPosition; }
    auto GetCameraSettings() const -> const CameraSettings & { return mSettings; }
    auto GetViewMatrix() const -> const glm::mat4 & { return mViewMatrix; }
    auto GetProjMatrix() const -> const glm::mat4 & { return mProjMatrix; }
};

#endif