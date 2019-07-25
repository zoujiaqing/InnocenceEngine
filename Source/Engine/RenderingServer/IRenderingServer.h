#pragma once
#include "../Common/InnoType.h"
#include "../Common/InnoClassTemplate.h"

#include "../Component/MeshDataComponent.h"
#include "../Component/TextureDataComponent.h"
#include "../Component/MaterialDataComponent.h"
#include "../Component/RenderPassDataComponent.h"
#include "../Component/ShaderProgramComponent.h"

enum class GPUBufferAccessibility { ReadOnly = 1, WriteOnly = 2, ReadWrite = ReadOnly | WriteOnly };

struct GPUBufferDataComponent
{
	GPUBufferAccessibility m_GPUBufferAccessibility = GPUBufferAccessibility::ReadOnly;
	size_t m_Size = 0;
	size_t m_BindingPoint = 0;
};

class IRenderingServer
{
public:
	INNO_CLASS_INTERFACE_NON_COPYABLE(IRenderingServer);

	virtual bool Setup() = 0;
	virtual bool Initialize() = 0;
	virtual bool Terminate() = 0;

	virtual ObjectStatus GetStatus() = 0;

	virtual MeshDataComponent* AddMeshDataComponent(const char* name = "") = 0;
	virtual TextureDataComponent* AddTextureDataComponent(const char* name = "") = 0;
	virtual MaterialDataComponent* AddMaterialDataComponent(const char* name = "") = 0;
	virtual RenderPassDataComponent* AddRenderPassDataComponent(const char* name = "") = 0;
	virtual ShaderProgramComponent* AddShaderProgramComponent(const char* name = "") = 0;
	virtual GPUBufferDataComponent* AddGPUBufferDataComponent(const char* name = "") = 0;

	virtual bool InitializeMeshDataComponent(MeshDataComponent* rhs) = 0;
	virtual bool InitializeTextureDataComponent(TextureDataComponent* rhs) = 0;
	virtual bool InitializeMaterialDataComponent(MaterialDataComponent* rhs) = 0;
	virtual bool InitializeRenderPassDataComponent(RenderPassDataComponent* rhs) = 0;
	virtual	bool InitializeShaderProgramComponent(ShaderProgramComponent* rhs) = 0;
	virtual bool InitializeGPUBufferDataComponent(GPUBufferDataComponent* rhs) = 0;

	virtual	bool DeleteMeshDataComponent(MeshDataComponent* rhs) = 0;
	virtual	bool DeleteTextureDataComponent(TextureDataComponent* rhs) = 0;
	virtual	bool DeleteMaterialDataComponent(MaterialDataComponent* rhs) = 0;
	virtual	bool DeleteRenderPassDataComponent(RenderPassDataComponent* rhs) = 0;
	virtual	bool DeleteShaderProgramComponent(ShaderProgramComponent* rhs) = 0;

	virtual void RegisterMeshDataComponent(MeshDataComponent* rhs) = 0;
	virtual void RegisterMaterialDataComponent(MaterialDataComponent* rhs) = 0;

	virtual MeshDataComponent* GetMeshDataComponent(MeshShapeType meshShapeType) = 0;
	virtual TextureDataComponent* GetTextureDataComponent(TextureUsageType textureUsageType) = 0;
	virtual TextureDataComponent* GetTextureDataComponent(WorldEditorIconType iconType) = 0;

	virtual bool UploadGPUBufferDataComponentImpl(GPUBufferDataComponent* rhs, const void* GPUBufferValue) = 0;

	template<typename T>
	void UploadGPUBufferDataComponent(GPUBufferDataComponent* rhs, const T* GPUBufferValue)
	{
		UploadGPUBufferDataComponentImpl(rhs, GPUBufferValue);
	}

	template<typename T>
	void UploadGPUBufferDataComponent(GPUBufferDataComponent* rhs, const std::vector<T>& GPUBufferValue)
	{
		UploadGPUBufferDataComponentImpl(rhs, &GPUBufferValue[0]);
	}

	virtual bool CommandListBegin(RenderPassDataComponent* rhs, size_t frameIndex) = 0;
	virtual bool BindRenderPassDataComponent(RenderPassDataComponent * rhs) = 0;
	virtual bool CleanRenderTargets(RenderPassDataComponent * rhs) = 0;
	virtual bool BindGPUBuffer(ShaderType shaderType, GPUBufferAccessibility accessibility, GPUBufferDataComponent* GPUBufferDataComponent, size_t startOffset, size_t range) = 0;
	virtual bool BindShaderProgramComponent(ShaderProgramComponent* rhs) = 0;
	virtual bool BindMaterialDataComponent(MaterialDataComponent* rhs) = 0;
	virtual bool DispatchDrawCall(MeshDataComponent* rhs) = 0;
	virtual bool UnbindMaterialDataComponent(RenderPassDataComponent* rhs) = 0;
	virtual bool CommandListEnd(RenderPassDataComponent* rhs, size_t frameIndex) = 0;
	virtual bool ExecuteCommandList(RenderPassDataComponent* rhs, size_t frameIndex) = 0;
	virtual bool WaitForFrame(RenderPassDataComponent* rhs, size_t frameIndex) = 0;
	virtual bool Present() = 0;

	virtual bool CopyDepthBuffer(RenderPassDataComponent* src, RenderPassDataComponent* dest) = 0;
	virtual bool CopyStencilBuffer(RenderPassDataComponent* src, RenderPassDataComponent* dest) = 0;
	virtual bool CopyColorBuffer(RenderPassDataComponent* src, size_t srcIndex, RenderPassDataComponent* dest, size_t destIndex) = 0;

	virtual vec4 ReadRenderTargetSample(RenderPassDataComponent* rhs, size_t renderTargetIndex, size_t x, size_t y) = 0;
	virtual std::vector<vec4> ReadTextureBackToCPU(RenderPassDataComponent* canvas, TextureDataComponent* TDC) = 0;

	virtual bool Resize() = 0;

	virtual bool ReloadShader(RenderPassType renderPassType) = 0;
	virtual bool BakeGIData() = 0;
};