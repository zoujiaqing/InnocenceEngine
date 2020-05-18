#include "OpaquePass.h"

#include "../DefaultGPUBuffers/DefaultGPUBuffers.h"

#include "../../Engine/Interface/IModuleManager.h"

INNO_ENGINE_API extern IModuleManager* g_pModuleManager;

using namespace DefaultGPUBuffers;

namespace OpaquePass
{
	RenderPassDataComponent* m_RPDC;
	ShaderProgramComponent* m_SPC;
	SamplerDataComponent* m_SDC;
}

bool OpaquePass::Setup()
{
	m_SPC = g_pModuleManager->getRenderingServer()->AddShaderProgramComponent("OpaquePass/");

	m_SPC->m_ShaderFilePaths.m_VSPath = "opaqueGeometryProcessPass.vert/";
	m_SPC->m_ShaderFilePaths.m_PSPath = "opaqueGeometryProcessPass.frag/";

	m_RPDC = g_pModuleManager->getRenderingServer()->AddRenderPassDataComponent("OpaquePass/");

	auto l_RenderPassDesc = g_pModuleManager->getRenderingFrontend()->getDefaultRenderPassDesc();

	l_RenderPassDesc.m_RenderTargetCount = 4;
	l_RenderPassDesc.m_UseDepthBuffer = true;

	l_RenderPassDesc.m_GraphicsPipelineDesc.m_DepthStencilDesc.m_DepthEnable = true;
	l_RenderPassDesc.m_GraphicsPipelineDesc.m_DepthStencilDesc.m_AllowDepthWrite = true;
	l_RenderPassDesc.m_GraphicsPipelineDesc.m_DepthStencilDesc.m_DepthComparisionFunction = ComparisionFunction::LessEqual;
	l_RenderPassDesc.m_GraphicsPipelineDesc.m_DepthStencilDesc.m_AllowDepthClamp = true;

	l_RenderPassDesc.m_GraphicsPipelineDesc.m_RasterizerDesc.m_UseCulling = true;

	m_RPDC->m_RenderPassDesc = l_RenderPassDesc;

	m_RPDC->m_ResourceBinderLayoutDescs.resize(9);
	m_RPDC->m_ResourceBinderLayoutDescs[0].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC->m_ResourceBinderLayoutDescs[0].m_DescriptorSetIndex = 0;
	m_RPDC->m_ResourceBinderLayoutDescs[0].m_DescriptorIndex = 0;

	m_RPDC->m_ResourceBinderLayoutDescs[1].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC->m_ResourceBinderLayoutDescs[1].m_DescriptorSetIndex = 0;
	m_RPDC->m_ResourceBinderLayoutDescs[1].m_DescriptorIndex = 1;

	m_RPDC->m_ResourceBinderLayoutDescs[2].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC->m_ResourceBinderLayoutDescs[2].m_DescriptorSetIndex = 0;
	m_RPDC->m_ResourceBinderLayoutDescs[2].m_DescriptorIndex = 2;

	m_RPDC->m_ResourceBinderLayoutDescs[3].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC->m_ResourceBinderLayoutDescs[3].m_DescriptorSetIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[3].m_DescriptorIndex = 0;
	m_RPDC->m_ResourceBinderLayoutDescs[3].m_ResourceCount = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[3].m_IndirectBinding = true;

	m_RPDC->m_ResourceBinderLayoutDescs[4].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC->m_ResourceBinderLayoutDescs[4].m_DescriptorSetIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[4].m_DescriptorIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[4].m_ResourceCount = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[4].m_IndirectBinding = true;

	m_RPDC->m_ResourceBinderLayoutDescs[5].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC->m_ResourceBinderLayoutDescs[5].m_DescriptorSetIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[5].m_DescriptorIndex = 2;
	m_RPDC->m_ResourceBinderLayoutDescs[5].m_ResourceCount = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[5].m_IndirectBinding = true;

	m_RPDC->m_ResourceBinderLayoutDescs[6].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC->m_ResourceBinderLayoutDescs[6].m_DescriptorSetIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[6].m_DescriptorIndex = 3;
	m_RPDC->m_ResourceBinderLayoutDescs[6].m_ResourceCount = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[6].m_IndirectBinding = true;

	m_RPDC->m_ResourceBinderLayoutDescs[7].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC->m_ResourceBinderLayoutDescs[7].m_DescriptorSetIndex = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[7].m_DescriptorIndex = 4;
	m_RPDC->m_ResourceBinderLayoutDescs[7].m_ResourceCount = 1;
	m_RPDC->m_ResourceBinderLayoutDescs[7].m_IndirectBinding = true;

	m_RPDC->m_ResourceBinderLayoutDescs[8].m_ResourceBinderType = ResourceBinderType::Sampler;
	m_RPDC->m_ResourceBinderLayoutDescs[8].m_DescriptorSetIndex = 2;
	m_RPDC->m_ResourceBinderLayoutDescs[8].m_DescriptorIndex = 0;
	m_RPDC->m_ResourceBinderLayoutDescs[8].m_IndirectBinding = true;

	m_RPDC->m_ShaderProgram = m_SPC;

	m_SDC = g_pModuleManager->getRenderingServer()->AddSamplerDataComponent("OpaquePass/");

	m_SDC->m_SamplerDesc.m_WrapMethodU = TextureWrapMethod::Repeat;
	m_SDC->m_SamplerDesc.m_WrapMethodV = TextureWrapMethod::Repeat;

	return true;
}

bool OpaquePass::Initialize()
{
	g_pModuleManager->getRenderingServer()->InitializeShaderProgramComponent(m_SPC);
	g_pModuleManager->getRenderingServer()->InitializeRenderPassDataComponent(m_RPDC);
	g_pModuleManager->getRenderingServer()->InitializeSamplerDataComponent(m_SDC);

	return true;
}

bool OpaquePass::PrepareCommandList()
{
	auto l_PerFrameCBufferGBDC = GetGPUBufferDataComponent(GPUBufferUsageType::PerFrame);
	auto l_MeshGBDC = GetGPUBufferDataComponent(GPUBufferUsageType::Mesh);
	auto l_MaterialGBDC = GetGPUBufferDataComponent(GPUBufferUsageType::Material);

	g_pModuleManager->getRenderingServer()->CommandListBegin(m_RPDC, 0);
	g_pModuleManager->getRenderingServer()->BindRenderPassDataComponent(m_RPDC);
	g_pModuleManager->getRenderingServer()->CleanRenderTargets(m_RPDC);

	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, m_SDC->m_ResourceBinder, 8, 0);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Vertex, l_PerFrameCBufferGBDC->m_ResourceBinder, 0, 0, Accessibility::ReadOnly);

	auto& l_drawCallInfo = g_pModuleManager->getRenderingFrontend()->getDrawCallInfo();
	auto l_drawCallCount = l_drawCallInfo.size();

	for (uint32_t i = 0; i < l_drawCallCount; i++)
	{
		auto l_drawCallData = l_drawCallInfo[i];
		auto l_visible = static_cast<uint32_t>(l_drawCallData.visibilityMask & VisibilityMask::MainCamera);

		if (l_visible && l_drawCallData.material->m_ObjectStatus == ObjectStatus::Activated)
		{
			if (l_drawCallData.material->m_ShaderModel == ShaderModel::Opaque)
			{
				if (l_drawCallData.mesh->m_ObjectStatus == ObjectStatus::Activated)
				{
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Vertex, l_MeshGBDC->m_ResourceBinder, 1, 1, Accessibility::ReadOnly, l_drawCallData.meshConstantBufferIndex, 1);
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_MaterialGBDC->m_ResourceBinder, 2, 2, Accessibility::ReadOnly, l_drawCallData.materialConstantBufferIndex, 1);

					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[0].m_Texture->m_ResourceBinder, 3, 0);
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[1].m_Texture->m_ResourceBinder, 4, 1);
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[2].m_Texture->m_ResourceBinder, 5, 2);
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[3].m_Texture->m_ResourceBinder, 6, 3);
					g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[4].m_Texture->m_ResourceBinder, 7, 4);

					g_pModuleManager->getRenderingServer()->DispatchDrawCall(m_RPDC, l_drawCallData.mesh);

					g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[0].m_Texture->m_ResourceBinder, 3, 0);
					g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[1].m_Texture->m_ResourceBinder, 4, 1);
					g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[2].m_Texture->m_ResourceBinder, 5, 2);
					g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[3].m_Texture->m_ResourceBinder, 6, 3);
					g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC, ShaderStage::Pixel, l_drawCallData.material->m_TextureSlots[4].m_Texture->m_ResourceBinder, 7, 4);
				}
			}
		}
	}

	g_pModuleManager->getRenderingServer()->CommandListEnd(m_RPDC);

	return true;
}

bool OpaquePass::Terminate()
{
	g_pModuleManager->getRenderingServer()->DeleteRenderPassDataComponent(m_RPDC);

	return true;
}

RenderPassDataComponent* OpaquePass::GetRPDC()
{
	return m_RPDC;
}

ShaderProgramComponent* OpaquePass::GetSPC()
{
	return m_SPC;
}