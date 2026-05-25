// GpuResources.cpp
#include "GpuResources.h"
#include <d3dcompiler.h>
#include <wrl.h>
#include <stdexcept>

#pragma comment(lib, "d3dcompiler.lib")

using namespace Microsoft::WRL;
using namespace Motor3D::Graphics;

ID3D11Device* GpuResources::device = nullptr;
ID3D11DeviceContext* GpuResources::context = nullptr;

void GpuResources::Init(ID3D11Device* dev, ID3D11DeviceContext* ctx) {
	device = dev;
	context = ctx;
}
void GpuResources::Shutdown() {
	device = nullptr;
	context = nullptr;
}

bool GpuResources::CompileShaderFromFile(const std::wstring& filePath, const std::string& entryPoint, const std::string& target, ComPtr<ID3DBlob>& outBlob) {
	UINT compileFlags = 0;
#if defined(_DEBUG)
	compileFlags |= D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	ComPtr<ID3DBlob> errorBlob;
	HRESULT hr = D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPoint.c_str(), target.c_str(), compileFlags, 0, &outBlob, &errorBlob);
		if (FAILED(hr) && errorBlob) {
			// If FXC is configured to precompile shaders in the project it may produce conflicting errors.
			// Print the error then continue returning false to the caller.
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
	if (FAILED(hr)) {
		if (errorBlob) {
			OutputDebugStringA((char*)errorBlob->GetBufferPointer());
		}
		return false;
	}
	return true;
}

ComPtr<ID3D11VertexShader> GpuResources::CreateVertexShader(const ComPtr<ID3DBlob>& blob) {
	ComPtr<ID3D11VertexShader> vs;
	HRESULT hr = device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vs);
	if (FAILED(hr)) throw std::runtime_error("Failed to create vertex shader");
	return vs;
}
ComPtr<ID3D11PixelShader> GpuResources::CreatePixelShader(const ComPtr<ID3DBlob>& blob) {
	ComPtr<ID3D11PixelShader> ps;
	HRESULT hr = device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &ps);
	if (FAILED(hr)) throw std::runtime_error("Failed to create pixel shader");
	return ps;
}

ComPtr<ID3D11InputLayout> GpuResources::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* desc, UINT numElements, const ComPtr<ID3DBlob>& vsBlob) {
	ComPtr<ID3D11InputLayout> layout;
	HRESULT hr = device->CreateInputLayout(desc, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &layout);
	if (FAILED(hr)) throw std::runtime_error("Failed to create input layout");
	return layout;
}

ComPtr<ID3D11Buffer> GpuResources::CreateVertexBuffer(const void* data, UINT size, UINT stride) {
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	ComPtr<ID3D11Buffer> buffer;
	HRESULT hr = device->CreateBuffer(&bd, &initData, &buffer);
	if (FAILED(hr)) throw std::runtime_error("Failed to create vertex buffer");
	return buffer;
}

ComPtr<ID3D11Buffer> GpuResources::CreateIndexBuffer(const void* data, UINT size) {
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = size;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA initData = {};
	initData.pSysMem = data;
	ComPtr<ID3D11Buffer> buffer;
	HRESULT hr = device->CreateBuffer(&bd, &initData, &buffer);
	if (FAILED(hr)) throw std::runtime_error("Failed to create index buffer");
	return buffer;
}


