#pragma once
#include "../Common/InnoType.h"
#include "../RenderingServer/DX12/DX12Headers.h"
#include "MeshDataComponent.h"

class DX12MeshDataComponent : public MeshDataComponent
{
public:
	ComPtr<ID3D12Resource> m_vertexBuffer = 0;
	ComPtr<ID3D12Resource> m_indexBuffer = 0;
	D3D12_VERTEX_BUFFER_VIEW m_VBV;
	D3D12_INDEX_BUFFER_VIEW m_IBV;
};
