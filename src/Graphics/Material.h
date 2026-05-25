// Material.h
#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <string>

namespace Motor3D { namespace Graphics {

class Material {
public:
	bool LoadFromShaders(const std::wstring& vsPath, const std::wstring& psPath);
	void Apply(ID3D11DeviceContext* context);
private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vs;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> ps;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

}}
