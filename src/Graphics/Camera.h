// Camera.h
#pragma once
#include <DirectXMath.h>

namespace Motor3D {
namespace Graphics {
class Camera {
public:
    Camera();
    void SetPosition(float x, float y, float z);
    void SetRotation(float pitch, float yaw, float roll);
    void Move(float dx, float dy, float dz);
    void Rotate(float dpitch, float dyaw, float droll);
    DirectX::XMMATRIX GetViewMatrix() const;
    DirectX::XMMATRIX GetProjectionMatrix(float aspect, float fov = 60.0f, float nearZ = 0.1f, float farZ = 1000.0f) const;
private:
    DirectX::XMFLOAT3 position;
    DirectX::XMFLOAT3 rotation;
};
}}
