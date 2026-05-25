// ForwardRenderer.cpp
#include "ForwardRenderer.h"
#include "GpuResources.h"
#include <d3d11.h>

using namespace Motor3D::Graphics;

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
	hr = device->CreateDepthStencilView(tex.Get(), nullptr, &dsv);
	if (FAILED(hr)) return false;
	return true;
}

void ForwardRenderer::Render(Camera& camera) {
	auto ctx = GpuResources::GetContext();
	// Bind DSV
	ctx->OMSetRenderTargets(1, nullptr, dsv.Get());
	// Clear depth
	ctx->ClearDepthStencilView(dsv.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
	// TODO: draw scene, debug lines, etc.
}

void ForwardRenderer::Shutdown() {
	dsv.Reset();
	depthTex.Reset();
}
