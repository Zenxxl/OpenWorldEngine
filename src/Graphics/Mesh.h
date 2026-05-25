// Mesh.h
#pragma once
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>

namespace Motor3D { namespace Graphics {

struct Vertex {
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT4 color;
};

class Mesh {
public:
	static std::unique_ptr<Mesh> CreateTriangle(ID3D11Device* device);
	~Mesh();
	void Draw(ID3D11DeviceContext* context) const;

	// Instance buffer support
	bool CreateInstanceBuffer(UINT instanceCount);
	void UpdateInstanceData(ID3D11DeviceContext* ctx, const void* data, UINT dataSize);
	void DrawInstanced(ID3D11DeviceContext* context, UINT instanceCount) const;
private:
	Mesh() = default;
	Microsoft::WRL::ComPtr<ID3D11Buffer> vb;
	Microsoft::WRL::ComPtr<ID3D11Buffer> ib;
	Microsoft::WRL::ComPtr<ID3D11Buffer> instanceBuffer;
	UINT vertexStride = 0;
	UINT indexCount = 0;
};

}}
