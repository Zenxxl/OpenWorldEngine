// Material.cpp
#include "Material.h"
#include "GpuResources.h"

using namespace Motor3D::Graphics;

bool Material::LoadFromShaders(const std::wstring& vsPath, const std::wstring& psPath) {
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob, psBlob;
	if (!GpuResources::CompileShaderFromFile(vsPath, "main", "vs_5_0", vsBlob)) return false;
	if (!GpuResources::CompileShaderFromFile(psPath, "main", "ps_5_0", psBlob)) return false;
	vs = GpuResources::CreateVertexShader(vsBlob);
	ps = GpuResources::CreatePixelShader(psBlob);
	// Create input layout matching Vertex { float3 pos; float4 color; }
	D3D11_INPUT_ELEMENT_DESC desc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	inputLayout = GpuResources::CreateInputLayout(desc, 2, vsBlob);
	return true;
}

void Material::Apply(ID3D11DeviceContext* context) {
	context->IASetInputLayout(inputLayout.Get());
	context->VSSetShader(vs.Get(), nullptr, 0);
	context->PSSetShader(ps.Get(), nullptr, 0);
}
