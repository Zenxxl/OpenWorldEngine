#include "GpuResourcesBridge.h"
#include "GpuResources.h"

using namespace Motor3D::Graphics;

void InitGpuResources(ID3D11Device* device, ID3D11DeviceContext* context) {
	GpuResources::Init(device, context);
}
void ShutdownGpuResources() {
	GpuResources::Shutdown();
}
