// Frustum.h
#pragma once
#include <DirectXMath.h>

namespace Motor3D { namespace Graphics {

class Frustum {
public:
	void CreateFromMatrix(const DirectX::XMMATRIX& m);
	bool IntersectsSphere(const DirectX::XMFLOAT3& center, float radius) const;
private:
	DirectX::XMFLOAT4 planes[6]; // left, right, top, bottom, near, far
};

}}
