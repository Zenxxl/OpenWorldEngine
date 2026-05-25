// Renderer.h
#pragma once
#include <windows.h>
#include <d3d11.h>

class Renderer {
public:
    Renderer();
    ~Renderer();
    bool Initialize(HWND hWnd, int width, int height);
    void BeginFrame();
    void EndFrame();
    void Shutdown();

    // Expose device/context for other subsystems (read-only)
    ID3D11Device* GetDevice() const { return device; }
    ID3D11DeviceContext* GetContext() const { return context; }

private:
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapChain = nullptr;
    ID3D11RenderTargetView* rtv = nullptr;
    D3D_FEATURE_LEVEL featureLevel;
    int width = 0, height = 0;
};
