#pragma once
#include "../../Engine/RenderingServer/IRenderingServer.h"

namespace SkyPass
{
	bool Setup();
	bool Initialize();
	bool PrepareCommandList();
	bool Terminate();

	RenderPassDataComponent* GetRPDC();
	ShaderProgramComponent* GetSPC();
	IResourceBinder* GetResult();
};
