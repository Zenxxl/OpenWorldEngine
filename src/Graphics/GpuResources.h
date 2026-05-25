// GpuResources.h
#pragma once
#include <d3d11.h>
#include <wrl.h>
#include <string>

namespace Motor3D {
namespace Graphics {

class GpuResources {
public:
	static void Init(ID3D11Device* dev, ID3D11DeviceContext* ctx);
	static void Shutdown();

	static bool CompileShaderFromFile(const std::wstring& filePath, const std::string& entryPoint, const std::string& target, Microsoft::WRL::ComPtr<ID3DBlob>& outBlob);

	static Microsoft::WRL::ComPtr<ID3D11VertexShader> CreateVertexShader(const Microsoft::WRL::ComPtr<ID3DBlob>& blob);
	static Microsoft::WRL::ComPtr<ID3D11PixelShader> CreatePixelShader(const Microsoft::WRL::ComPtr<ID3DBlob>& blob);

	static Microsoft::WRL::ComPtr<ID3D11InputLayout> CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* desc, UINT numElements, const Microsoft::WRL::ComPtr<ID3DBlob>& vsBlob);

	static Microsoft::WRL::ComPtr<ID3D11Buffer> CreateVertexBuffer(const void* data, UINT size, UINT stride);
	static Microsoft::WRL::ComPtr<ID3D11Buffer> CreateIndexBuffer(const void* data, UINT size);

	template<typename T>
	static Microsoft::WRL::ComPtr<ID3D11Buffer> CreateConstantBuffer() {
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC bd = {};
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = static_cast<UINT>(sizeof(T) + (16 - (sizeof(T) % 16)) % 16); // 16-byte aligned
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;
		if (device == nullptr) return nullptr;
		HRESULT hr = device->CreateBuffer(&bd, nullptr, &buffer);
		if (FAILED(hr)) return nullptr;
		return buffer;
	}

	static ID3D11Device* GetDevice() { return device; }
	static ID3D11DeviceContext* GetContext() { return context; }
private:
	static ID3D11Device* device;
	static ID3D11DeviceContext* context;
};

}
}
