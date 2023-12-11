#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "PDH.hpp"

struct CameraSettings
{
    float mFOV{};
    float mAspect{};
    float mNear{};
    float mFar{};

    CameraSettings() = default;
    CameraSettings(float fov, float aspect, float near, float far)
        : mFOV(fov),
          mAspect(aspect),
          mNear(near),
          mFar(far)
    {
    }
};

class Camera {
    private:
    public:
};

#endif