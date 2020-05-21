#include "LuminanceHistogramPass.h"
#include "../DefaultGPUBuffers/DefaultGPUBuffers.h"

#include "../../Engine/Interface/IModuleManager.h"

INNO_ENGINE_API extern IModuleManager* g_pModuleManager;

using namespace DefaultGPUBuffers;

namespace LuminanceHistogramPass
{
	bool CalculateHistogram(IResourceBinder* input);
	bool CalculateAverage();

	RenderPassDataComponent* m_RPDC_LuminanceHistogram = 0;
	ShaderProgramComponent* m_SPC_LuminanceHistogram = 0;
	RenderPassDataComponent* m_RPDC_LuminanceAverage = 0;
	ShaderProgramComponent* m_SPC_LuminanceAverage = 0;
	SamplerDataComponent* m_SDC = 0;

	GPUBufferDataComponent* m_LuminanceHistogramGBDC = 0;
	GPUBufferDataComponent* m_LuminanceAverageGBDC = 0;
}

bool LuminanceHistogramPass::Setup()
{
	auto l_RenderPassDesc = g_pModuleManager->getRenderingFrontend()->getDefaultRenderPassDesc();

	l_RenderPassDesc.m_RenderTargetCount = 0;
	l_RenderPassDesc.m_RenderPassUsage = RenderPassUsage::Compute;

	m_SPC_LuminanceHistogram = g_pModuleManager->getRenderingServer()->AddShaderProgramComponent("LuminanceHistogramPass/");

	m_SPC_LuminanceHistogram->m_ShaderFilePaths.m_CSPath = "luminanceHistogramPass.comp/";

	m_RPDC_LuminanceHistogram = g_pModuleManager->getRenderingServer()->AddRenderPassDataComponent("LuminanceHistogramPass/");

	m_RPDC_LuminanceHistogram->m_RenderPassDesc = l_RenderPassDesc;

	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs.resize(4);
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_ResourceBinderType = ResourceBinderType::Image;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_DescriptorSetIndex = 1;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_DescriptorIndex = 0;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_BinderAccessibility = Accessibility::ReadOnly;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_ResourceAccessibility = Accessibility::ReadOnly;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[0].m_IndirectBinding = true;

	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[1].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[1].m_DescriptorSetIndex = 1;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[1].m_DescriptorIndex = 1;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[1].m_BinderAccessibility = Accessibility::ReadWrite;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[1].m_ResourceAccessibility = Accessibility::ReadWrite;

	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[2].m_ResourceBinderType = ResourceBinderType::Sampler;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[2].m_DescriptorSetIndex = 2;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[2].m_DescriptorIndex = 0;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[2].m_IndirectBinding = true;

	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[3].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[3].m_DescriptorSetIndex = 0;
	m_RPDC_LuminanceHistogram->m_ResourceBinderLayoutDescs[3].m_DescriptorIndex = 0;

	m_RPDC_LuminanceHistogram->m_ShaderProgram = m_SPC_LuminanceHistogram;

	////
	m_SPC_LuminanceAverage = g_pModuleManager->getRenderingServer()->AddShaderProgramComponent("LuminanceAveragePass/");

	m_SPC_LuminanceAverage->m_ShaderFilePaths.m_CSPath = "luminanceAveragePass.comp/";

	m_RPDC_LuminanceAverage = g_pModuleManager->getRenderingServer()->AddRenderPassDataComponent("LuminanceAveragePass/");

	m_RPDC_LuminanceAverage->m_RenderPassDesc = l_RenderPassDesc;

	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs.resize(3);
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[0].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[0].m_DescriptorSetIndex = 1;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[0].m_DescriptorIndex = 0;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[0].m_BinderAccessibility = Accessibility::ReadWrite;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[0].m_ResourceAccessibility = Accessibility::ReadWrite;

	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[1].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[1].m_DescriptorSetIndex = 1;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[1].m_DescriptorIndex = 1;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[1].m_BinderAccessibility = Accessibility::ReadWrite;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[1].m_ResourceAccessibility = Accessibility::ReadWrite;

	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[2].m_ResourceBinderType = ResourceBinderType::Buffer;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[2].m_DescriptorSetIndex = 0;
	m_RPDC_LuminanceAverage->m_ResourceBinderLayoutDescs[2].m_DescriptorIndex = 0;

	m_RPDC_LuminanceAverage->m_ShaderProgram = m_SPC_LuminanceAverage;

	////
	m_SDC = g_pModuleManager->getRenderingServer()->AddSamplerDataComponent("LuminanceHistogramPass/");

	////
	m_LuminanceHistogramGBDC = g_pModuleManager->getRenderingServer()->AddGPUBufferDataComponent("LuminanceHistogramGPUBuffer/");
	m_LuminanceHistogramGBDC->m_CPUAccessibility = Accessibility::Immutable;
	m_LuminanceHistogramGBDC->m_GPUAccessibility = Accessibility::ReadWrite;
	m_LuminanceHistogramGBDC->m_ElementCount = 256;
	m_LuminanceHistogramGBDC->m_ElementSize = sizeof(uint32_t);

	m_LuminanceAverageGBDC = g_pModuleManager->getRenderingServer()->AddGPUBufferDataComponent("LuminanceAverageGPUBuffer/");
	m_LuminanceAverageGBDC->m_CPUAccessibility = Accessibility::Immutable;
	m_LuminanceAverageGBDC->m_GPUAccessibility = Accessibility::ReadWrite;
	m_LuminanceAverageGBDC->m_ElementCount = 1;
	m_LuminanceAverageGBDC->m_ElementSize = sizeof(float);

	return true;
}

bool LuminanceHistogramPass::Initialize()
{
	g_pModuleManager->getRenderingServer()->InitializeSamplerDataComponent(m_SDC);

	g_pModuleManager->getRenderingServer()->InitializeShaderProgramComponent(m_SPC_LuminanceHistogram);
	g_pModuleManager->getRenderingServer()->InitializeRenderPassDataComponent(m_RPDC_LuminanceHistogram);

	g_pModuleManager->getRenderingServer()->InitializeShaderProgramComponent(m_SPC_LuminanceAverage);
	g_pModuleManager->getRenderingServer()->InitializeRenderPassDataComponent(m_RPDC_LuminanceAverage);

	g_pModuleManager->getRenderingServer()->InitializeGPUBufferDataComponent(m_LuminanceHistogramGBDC);
	g_pModuleManager->getRenderingServer()->InitializeGPUBufferDataComponent(m_LuminanceAverageGBDC);

	return true;
}

bool LuminanceHistogramPass::CalculateHistogram(IResourceBinder* input)
{
	auto l_viewportSize = g_pModuleManager->getRenderingFrontend()->getScreenResolution();

	auto l_numThreadGroupsX = std::ceil(l_viewportSize.x / 16);
	auto l_numThreadGroupsY = std::ceil(l_viewportSize.y / 16);

	auto l_PerFrameCBufferGBDC = GetGPUBufferDataComponent(GPUBufferUsageType::PerFrame);

	g_pModuleManager->getRenderingServer()->CommandListBegin(m_RPDC_LuminanceHistogram, 0);
	g_pModuleManager->getRenderingServer()->BindRenderPassDataComponent(m_RPDC_LuminanceHistogram);
	g_pModuleManager->getRenderingServer()->CleanRenderTargets(m_RPDC_LuminanceHistogram);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, m_SDC->m_ResourceBinder, 2, 0);

	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, input, 0, 0, Accessibility::ReadOnly);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, m_LuminanceHistogramGBDC->m_ResourceBinder, 1, 1, Accessibility::ReadWrite);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, l_PerFrameCBufferGBDC->m_ResourceBinder, 3, 0, Accessibility::ReadOnly);

	g_pModuleManager->getRenderingServer()->DispatchCompute(m_RPDC_LuminanceHistogram, (uint32_t)l_numThreadGroupsX, (uint32_t)l_numThreadGroupsY, 1);

	g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, input, 0, 0, Accessibility::ReadOnly);
	g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC_LuminanceHistogram, ShaderStage::Compute, m_LuminanceHistogramGBDC->m_ResourceBinder, 1, 1, Accessibility::ReadWrite);

	g_pModuleManager->getRenderingServer()->CommandListEnd(m_RPDC_LuminanceHistogram);

	return true;
}

bool LuminanceHistogramPass::CalculateAverage()
{
	auto l_PerFrameCBufferGBDC = GetGPUBufferDataComponent(GPUBufferUsageType::PerFrame);

	g_pModuleManager->getRenderingServer()->CommandListBegin(m_RPDC_LuminanceAverage, 0);
	g_pModuleManager->getRenderingServer()->BindRenderPassDataComponent(m_RPDC_LuminanceAverage);
	g_pModuleManager->getRenderingServer()->CleanRenderTargets(m_RPDC_LuminanceAverage);

	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceAverage, ShaderStage::Compute, m_LuminanceHistogramGBDC->m_ResourceBinder, 0, 0, Accessibility::ReadWrite);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceAverage, ShaderStage::Compute, m_LuminanceAverageGBDC->m_ResourceBinder, 1, 1, Accessibility::ReadWrite);
	g_pModuleManager->getRenderingServer()->ActivateResourceBinder(m_RPDC_LuminanceAverage, ShaderStage::Compute, l_PerFrameCBufferGBDC->m_ResourceBinder, 2, 0, Accessibility::ReadOnly);

	g_pModuleManager->getRenderingServer()->DispatchCompute(m_RPDC_LuminanceAverage, 1, 1, 1);

	g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC_LuminanceAverage, ShaderStage::Compute, m_LuminanceHistogramGBDC->m_ResourceBinder, 0, 0, Accessibility::ReadWrite);
	g_pModuleManager->getRenderingServer()->DeactivateResourceBinder(m_RPDC_LuminanceAverage, ShaderStage::Compute, m_LuminanceAverageGBDC->m_ResourceBinder, 1, 1, Accessibility::ReadWrite);

	g_pModuleManager->getRenderingServer()->CommandListEnd(m_RPDC_LuminanceAverage);

	return true;
}

bool LuminanceHistogramPass::Render(IResourceBinder* input)
{
	CalculateHistogram(input);
	CalculateAverage();

	g_pModuleManager->getRenderingServer()->ExecuteCommandList(m_RPDC_LuminanceHistogram);

	g_pModuleManager->getRenderingServer()->WaitForFrame(m_RPDC_LuminanceHistogram);

	g_pModuleManager->getRenderingServer()->ExecuteCommandList(m_RPDC_LuminanceAverage);

	g_pModuleManager->getRenderingServer()->WaitForFrame(m_RPDC_LuminanceAverage);

	return true;
}

bool LuminanceHistogramPass::Terminate()
{
	g_pModuleManager->getRenderingServer()->DeleteRenderPassDataComponent(m_RPDC_LuminanceHistogram);

	g_pModuleManager->getRenderingServer()->DeleteRenderPassDataComponent(m_RPDC_LuminanceAverage);

	return true;
}

RenderPassDataComponent* LuminanceHistogramPass::GetRPDC()
{
	return m_RPDC_LuminanceHistogram;
}

ShaderProgramComponent* LuminanceHistogramPass::GetSPC()
{
	return m_SPC_LuminanceHistogram;
}

GPUBufferDataComponent* LuminanceHistogramPass::GetAverageLuminance()
{
	return m_LuminanceAverageGBDC;
}