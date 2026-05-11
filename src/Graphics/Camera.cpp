// Camera.cpp
#include "Camera.h"
#include <DirectXMath.h>
#include <cmath>

using namespace DirectX;

namespace Motor3D {
namespace Graphics {

Camera::Camera() : position{0,0,0}, rotation{0,0,0} {}

void Camera::SetPosition(float x, float y, float z) {
    position = {x, y, z};
}
void Camera::SetRotation(float pitch, float yaw, float roll) {
    rotation = {pitch, yaw, roll};
}
void Camera::Move(float dx, float dy, float dz) {
    position.x += dx; position.y += dy; position.z += dz;
}
void Camera::Rotate(float dpitch, float dyaw, float droll) {
    rotation.x += dpitch; rotation.y += dyaw; rotation.z += droll;
}
XMMATRIX Camera::GetViewMatrix() const {
    XMVECTOR pos = XMLoadFloat3(&position);
    XMVECTOR rot = XMLoadFloat3(&rotation);
    XMVECTOR forward = XMVectorSet(0, 0, 1, 0);
    XMMATRIX rotMat = XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z);
    forward = XMVector3TransformCoord(forward, rotMat);
    XMVECTOR up = XMVectorSet(0, 1, 0, 0);
    up = XMVector3TransformCoord(up, rotMat);
    return XMMatrixLookToLH(pos, forward, up);
}
XMMATRIX Camera::GetProjectionMatrix(float aspect, float fov, float nearZ, float farZ) const {
    return XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspect, nearZ, farZ);
}

}}
