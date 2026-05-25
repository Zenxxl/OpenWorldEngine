// ForwardRenderer.h
#pragma once
#include "GpuResources.h"
#include "../Graphics/Camera.h"
#include <wrl.h>

namespace Motor3D { namespace Graphics {

class ForwardRenderer {
public:
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* context, int width, int height);
	void Render(Camera& camera);
	void Shutdown();
private:
	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthTex;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> dsv;
	int width = 0, height = 0;
};

}}
