#pragma once
#include "../../Engine/RenderingServer/IRenderingServer.h"

namespace PreTAAPass
{
	bool Setup();
	bool Initialize();
	bool PrepareCommandList();
	bool Terminate();

	RenderPassDataComponent* GetRPDC();
	ShaderProgramComponent* GetSPC();
	IResourceBinder* GetResult();
};
