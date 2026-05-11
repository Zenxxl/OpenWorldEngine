// Renderer.cpp
#include "Renderer.h"

Renderer::Renderer() {}
Renderer::~Renderer() { Shutdown(); }

bool Renderer::Initialize(HWND hWnd, int width, int height) {
    this->width = width;
    this->height = height;
    DXGI_SWAP_CHAIN_DESC scd = {};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, nullptr, 0,
        D3D11_SDK_VERSION, &scd, &swapChain, &device, &featureLevel, &context);
    if (FAILED(hr)) return false;
    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
    device->CreateRenderTargetView(backBuffer, nullptr, &rtv);
    backBuffer->Release();
    context->OMSetRenderTargets(1, &rtv, nullptr);
    D3D11_VIEWPORT vp = { 0, 0, (float)width, (float)height, 0.0f, 1.0f };
    context->RSSetViewports(1, &vp);
	OutputDebugStringA("Renderer inicializado correctamente.\n");
    return true;
}

void Renderer::BeginFrame() {
    float clearColor[4] = { 0.1f, 0.1f, 0.3f, 1.0f };
    context->ClearRenderTargetView(rtv, clearColor);
}

void Renderer::EndFrame() {
    swapChain->Present(1, 0);
}

void Renderer::Shutdown() {
    if (rtv) { rtv->Release(); rtv = nullptr; }
    if (swapChain) { swapChain->Release(); swapChain = nullptr; }
    if (context) { context->Release(); context = nullptr; }
    if (device) { device->Release(); device = nullptr; }
}
