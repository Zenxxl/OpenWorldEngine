// SpatialGrid.cpp
#include "SpatialGrid.h"
#include <algorithm>
#include <limits>

using namespace Motor3D::Scene;
using namespace DirectX;

void SpatialGrid::Build(const std::vector<XMFLOAT4X4>& transforms, float cellSize) {
	if (transforms.empty()) return;
	this->cellSize = cellSize;
	float minx = std::numeric_limits<float>::max(), minz = std::numeric_limits<float>::max();
	float maxx = -minx, maxz = -minz;
	std::vector<XMFLOAT3> pts(transforms.size());
	for (size_t i = 0; i < transforms.size(); ++i) {
		pts[i] = { transforms[i]._41, transforms[i]._42, transforms[i]._43 };
		minx = std::min(minx, pts[i].x); maxx = std::max(maxx, pts[i].x);
		minz = std::min(minz, pts[i].z); maxz = std::max(maxz, pts[i].z);
	}
	origin = { minx, minz };
	cols = int((maxx - minx) / cellSize) + 1;
	rows = int((maxz - minz) / cellSize) + 1;
	cells.clear();
	cells.resize(cols * rows);
	for (int r = 0; r < rows; ++r) for (int c = 0; c < cols; ++c) {
		cells[r*cols + c].center = { origin.x + (c+0.5f)*cellSize, 0.0f, origin.y + (r+0.5f)*cellSize };
		cells[r*cols + c].radius = sqrtf(2.0f)*0.5f*cellSize;
	}
	for (size_t i = 0; i < pts.size(); ++i) {
		int c = int((pts[i].x - origin.x) / cellSize);
		int r = int((pts[i].z - origin.y) / cellSize);
		c = std::max(0, std::min(cols-1, c));
		r = std::max(0, std::min(rows-1, r));
		cells[r*cols + c].indices.push_back((int)i);
	}
}

void SpatialGrid::QueryFrustum(const Motor3D::Graphics::Frustum& frustum, std::vector<int>& outIndices) const {
	outIndices.clear();
	for (const auto &cell : cells) {
		if (frustum.IntersectsSphere(cell.center, cell.radius)) {
			outIndices.insert(outIndices.end(), cell.indices.begin(), cell.indices.end());
		}
	}
}
