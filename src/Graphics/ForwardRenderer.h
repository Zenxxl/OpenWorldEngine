// ForwardRenderer.h
#pragma once
#include "GpuResources.h"
#include "../Graphics/Camera.h"
#include <wrl.h>
#include <memory>
#include <vector>
#include <DirectXMath.h>
#include "Frustum.h"
#include "Mesh.h"
#include "Material.h"
#include "../Core/ThreadPool.h"
#include "../Scene/SpatialGrid.h"
#include <thread>

namespace Motor3D { namespace Graphics {

// Forward declarations
class Mesh;
class Material;

class ForwardRenderer {
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, int width, int height);
	void Render(Camera& camera);
	void Shutdown();
private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	int width = 0, height = 0;

	// Test rendering
	std::unique_ptr<Mesh> testMesh;
	std::unique_ptr<Material> testMat;
	UINT instanceCount = 0;
	std::vector<DirectX::XMFLOAT4X4> instanceTransforms;
	Frustum frustum;
	Motor3D::Scene::SpatialGrid spatialGrid;
	std::unique_ptr<Motor3D::Core::ThreadPool> pool;

	// Rebuild spatial grid only when instances change
	std::atomic<bool> instancesDirty{false};
	void RebuildSpatialGridIfNeeded();
public:
	// Mark instances as modified so the grid will be rebuilt before next render
	void MarkInstancesDirty() { instancesDirty.store(true, std::memory_order_relaxed); }
};

}}
