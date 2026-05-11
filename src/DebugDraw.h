// DebugDraw.h
#pragma once
#include <DirectXMath.h>
#include <vector>

namespace Motor3D {
namespace Debug {
struct DebugLine {
    DirectX::XMFLOAT3 start;
    DirectX::XMFLOAT3 end;
    DirectX::XMFLOAT4 color;
};

class DebugDraw {
public:
    void AddLine(const DirectX::XMFLOAT3& start, const DirectX::XMFLOAT3& end, const DirectX::XMFLOAT4& color);
    void Clear();
    const std::vector<DebugLine>& GetLines() const;
private:
    std::vector<DebugLine> lines;
};
}}
