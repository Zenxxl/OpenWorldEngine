// main.cpp
// Motor 3D base: inicialización de ventana y DirectX 11
#include <windows.h>
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")

#include "Renderer.h"
#include "PhysicsSystem.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
    // Registrar clase de ventana
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, hInstance, nullptr, nullptr, nullptr, nullptr, L"DX11WndClass", nullptr };
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(wc.lpszClassName, L"Motor3D DX11", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 720, nullptr, nullptr, wc.hInstance, nullptr);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    Renderer renderer;
    if (!renderer.Initialize(hWnd, 1280, 720)) {
        return 0;
    }
    PhysicsSystem physics;
    if (!physics.Initialize()) {
        return 0;
    }

	OutputDebugStringA("Motor3D iniciado correctamente.\n");

    // Loop principal
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        } else {
            renderer.BeginFrame();
            // Aquí irá el renderizado de la escena y la simulación física
            renderer.EndFrame();
        }
    }
    physics.Shutdown();
    renderer.Shutdown();
    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_DESTROY) { PostQuitMessage(0); return 0; }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
