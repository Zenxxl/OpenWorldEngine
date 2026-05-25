// SpatialGrid.h
#pragma once
#include <DirectXMath.h>
#include <vector>
#include "../Graphics/Frustum.h"

namespace Motor3D { namespace Scene {

// Simple 2D uniform grid on XZ plane for broad-phase spatial queries
class SpatialGrid {
public:
	SpatialGrid() = default;
	// Build grid for given points (centers). cellSize must be > 0
	void Build(const std::vector<DirectX::XMFLOAT4X4>& transforms, float cellSize);
	// Query indices of points whose cell AABB intersects the frustum
	void QueryFrustum(const Motor3D::Graphics::Frustum& frustum, std::vector<int>& outIndices) const;

private:
	struct Cell { std::vector<int> indices; DirectX::XMFLOAT3 center; float radius; };
	std::vector<Cell> cells;
	int cols = 0, rows = 0;
	DirectX::XMFLOAT2 origin; // min x,z
	float cellSize = 1.0f;
};

}}
