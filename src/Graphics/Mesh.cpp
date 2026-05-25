// Mesh.cpp
#include "Mesh.h"
#include "GpuResources.h"

using namespace Motor3D::Graphics;

std::unique_ptr<Mesh> Mesh::CreateTriangle(ID3D11Device* device) {
	auto m = std::unique_ptr<Mesh>(new Mesh());
	Vertex verts[3] = {
		{{0.0f, 0.5f, 0.0f}, {1,0,0,1}},
		{{0.5f, -0.5f, 0.0f}, {0,1,0,1}},
		{{-0.5f, -0.5f, 0.0f}, {0,0,1,1}},
	};
	uint16_t indices[3] = {0,1,2};
	m->vertexStride = sizeof(Vertex);
	m->vb = GpuResources::CreateVertexBuffer(verts, sizeof(verts), m->vertexStride);
	m->ib = GpuResources::CreateIndexBuffer(indices, sizeof(indices));
	m->indexCount = 3;
	return m;
}

Mesh::~Mesh() {}

void Mesh::Draw(ID3D11DeviceContext* context) const {
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, vb.GetAddressOf(), &vertexStride, &offset);
	context->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexed(indexCount, 0, 0);
}

bool Mesh::CreateInstanceBuffer(UINT instanceCount) {
	if (!GpuResources::GetDevice()) return false;
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = instanceCount * sizeof(DirectX::XMFLOAT4X4);
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	HRESULT hr = GpuResources::GetDevice()->CreateBuffer(&bd, nullptr, &instanceBuffer);
	return SUCCEEDED(hr);
}

void Mesh::UpdateInstanceData(ID3D11DeviceContext* ctx, const void* data, UINT dataSize) {
	if (!instanceBuffer) return;
	D3D11_MAPPED_SUBRESOURCE ms = {};
	ctx->Map(instanceBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
	memcpy(ms.pData, data, dataSize);
	ctx->Unmap(instanceBuffer.Get(), 0);
}

void Mesh::DrawInstanced(ID3D11DeviceContext* context, UINT instanceCount) const {
	UINT offsets[2] = {0,0};
	UINT strides[2] = { vertexStride, sizeof(DirectX::XMFLOAT4X4) };
	ID3D11Buffer* buffers[2] = { vb.Get(), instanceBuffer.Get() };
	context->IASetVertexBuffers(0, 2, buffers, strides, offsets);
	context->IASetIndexBuffer(ib.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->DrawIndexedInstanced(indexCount, instanceCount, 0, 0, 0);
}
