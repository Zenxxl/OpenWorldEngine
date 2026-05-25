// ForwardRenderer.cpp
#include "ForwardRenderer.h"
#include "GpuResources.h"
#include "Mesh.h"
#include "Material.h"
#include <d3d11.h>
#include <memory>
#include <future>
#include <thread>
#include <algorithm>

using namespace Motor3D::Graphics;
using std::unique_ptr;

bool ForwardRenderer::Initialize(ID3D11Device* device, ID3D11DeviceContext* context, int width, int height) {
	this->width = width; this->height = height;
	// Create depth buffer
	D3D11_TEXTURE2D_DESC desc = {};
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> tex;
	HRESULT hr = device->CreateTexture2D(&desc, nullptr, &tex);
	if (FAILED(hr)) return false;
	// Keep a reference to the texture to ensure lifetime
	depthTex = tex;
	hr = device->CreateDepthStencilView(depthTex.Get(), nullptr, &dsv);
	if (FAILED(hr)) return false;

	// Create test mesh/material
	testMesh = Mesh::CreateTriangle(device);
	testMat = std::unique_ptr<Material>(new Material());
	if (!testMat->LoadFromShaders(L"shaders/basic_vs.hlsl", L"shaders/basic_ps.hlsl")) return false;

	// create instances
	instanceCount = 1000;
	instanceTransforms.resize(instanceCount);
	for (UINT i = 0; i < instanceCount; ++i) {
		float x = (float)(i % 20) - 10.0f;
		float y = (float)((i / 20) % 20) - 10.0f;
		float z = (float)(i / 400) * 2.0f;
		DirectX::XMMATRIX t = DirectX::XMMatrixTranslation(x, y, z);
		DirectX::XMStoreFloat4x4(&instanceTransforms[i], t);
	}
	if (!testMesh->CreateInstanceBuffer(instanceCount)) return false;
	// Initialize with full transforms
	testMesh->UpdateInstanceData(GpuResources::GetContext(), instanceTransforms.data(), instanceCount * sizeof(DirectX::XMFLOAT4X4));

	// Build spatial grid once
	spatialGrid.Build(instanceTransforms, 2.0f);
	instancesDirty.store(false, std::memory_order_relaxed);

	// Create thread pool
	unsigned int hw = std::thread::hardware_concurrency();
	if (hw == 0) hw = 4;
	pool = std::make_unique<Motor3D::Core::ThreadPool>(hw);

	return true;
}

void ForwardRenderer::RebuildSpatialGridIfNeeded() {
	// Rebuild the spatial grid only when instances were modified
	if (instancesDirty.exchange(false)) {
		spatialGrid.Build(instanceTransforms, 2.0f);
	}
}

void ForwardRenderer::Render(Camera& camera) {
	auto ctx = GpuResources::GetContext();
	if (!ctx) return; // guard in case GpuResources not initialized
	RebuildSpatialGridIfNeeded();
	// Bind RTV and DSV
	ctx->OMSetRenderTargets(0, nullptr, dsv.Get());
	// Clear depth
	ctx->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

	// Build frustum
	DirectX::XMMATRIX view = camera.GetViewMatrix();
	DirectX::XMMATRIX proj = camera.GetProjectionMatrix((float)width / (float)height);
	DirectX::XMMATRIX vp = DirectX::XMMatrixMultiply(view, proj);
	frustum.CreateFromMatrix(vp);

	// Use spatial grid to get candidate indices
	std::vector<int> candidates;
	spatialGrid.QueryFrustum(frustum, candidates);

	// Cull candidates using threads
	std::vector<DirectX::XMFLOAT4X4> visible;
	visible.reserve(candidates.size());

	unsigned int hw = std::thread::hardware_concurrency();
	if (hw == 0) hw = 4;
	unsigned int chunk = (candidates.size() + hw - 1) / hw;

	// per-thread reusable buffers
	std::vector<std::vector<DirectX::XMFLOAT4X4>> threadBuffers(hw);
	for (unsigned int t = 0; t < hw; ++t) threadBuffers[t].reserve(chunk);

	std::vector<std::future<void>> futures;
	for (unsigned int t = 0; t < hw; ++t) {
		unsigned int start = t * chunk;
		unsigned int end = std::min<unsigned int>(start + chunk, (unsigned int)candidates.size());
		futures.push_back(pool->Submit([this, start, end, &threadBuffers, t, &candidates]() {
			auto &local = threadBuffers[t];
			local.clear();
			for (unsigned int k = start; k < end; ++k) {
				unsigned int i = candidates[k];
				DirectX::XMFLOAT3 center = { instanceTransforms[i]._41, instanceTransforms[i]._42, instanceTransforms[i]._43 };
				if (frustum.IntersectsSphere(center, 1.0f)) local.push_back(instanceTransforms[i]);
			}
		}));
	}
	for (auto &f : futures) f.get();

	for (unsigned int t = 0; t < hw; ++t) {
		auto &vec = threadBuffers[t];
		visible.insert(visible.end(), vec.begin(), vec.end());
	}

	// Update instance buffer with visible transforms
	if (!visible.empty())
		testMesh->UpdateInstanceData(ctx, visible.data(), (UINT)(visible.size() * sizeof(DirectX::XMFLOAT4X4)));

	// Draw instanced
	testMat->Apply(ctx);
	if (!visible.empty()) testMesh->DrawInstanced(ctx, (UINT)visible.size());
}

void ForwardRenderer::Shutdown() {
	dsv.Reset();
	depthTex.Reset();
	testMat.reset();
	testMesh.reset();
	pool.reset();
}
