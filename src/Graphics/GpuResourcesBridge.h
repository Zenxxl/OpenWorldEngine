// Bridge to initialize GpuResources from Renderer without adding a dependency cycle
#pragma once
#include <d3d11.h>

void InitGpuResources(ID3D11Device* device, ID3D11DeviceContext* context);
void ShutdownGpuResources();
