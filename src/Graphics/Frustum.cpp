// Frustum.cpp
#include "Frustum.h"
using namespace DirectX;
using namespace Motor3D::Graphics;

void Frustum::CreateFromMatrix(const XMMATRIX& m) {
	// Extract planes in row-major order
	XMFLOAT4X4 mat;
	XMStoreFloat4x4(&mat, m);
	// Left
	planes[0].x = mat._14 + mat._11;
	planes[0].y = mat._24 + mat._21;
	planes[0].z = mat._34 + mat._31;
	planes[0].w = mat._44 + mat._41;
	// Right
	planes[1].x = mat._14 - mat._11;
	planes[1].y = mat._24 - mat._21;
	planes[1].z = mat._34 - mat._31;
	planes[1].w = mat._44 - mat._41;
	// Top
	planes[2].x = mat._14 - mat._12;
	planes[2].y = mat._24 - mat._22;
	planes[2].z = mat._34 - mat._32;
	planes[2].w = mat._44 - mat._42;
	// Bottom
	planes[3].x = mat._14 + mat._12;
	planes[3].y = mat._24 + mat._22;
	planes[3].z = mat._34 + mat._32;
	planes[3].w = mat._44 + mat._42;
	// Near
	planes[4].x = mat._13;
	planes[4].y = mat._23;
	planes[4].z = mat._33;
	planes[4].w = mat._43;
	// Far
	planes[5].x = mat._14 - mat._13;
	planes[5].y = mat._24 - mat._23;
	planes[5].z = mat._34 - mat._33;
	planes[5].w = mat._44 - mat._43;
	// Normalize
	for (int i = 0; i < 6; ++i) {
		XMVECTOR p = XMLoadFloat4(&planes[i]);
		float mag = XMVectorGetX(XMVector3Length(XMLoadFloat3(reinterpret_cast<XMFLOAT3*>(&planes[i]))));
		if (mag > 0.0f) {
			planes[i].x /= mag; planes[i].y /= mag; planes[i].z /= mag; planes[i].w /= mag;
		}
	}
}

bool Frustum::IntersectsSphere(const XMFLOAT3& center, float radius) const {
	for (int i = 0; i < 6; ++i) {
		float d = planes[i].x * center.x + planes[i].y * center.y + planes[i].z * center.z + planes[i].w;
		if (d < -radius) return false;
	}
	return true;
}
