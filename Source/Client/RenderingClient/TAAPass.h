#pragma once
#include "../../Engine/RenderingServer/IRenderingServer.h"

namespace TAAPass
{
	bool Setup();
	bool Initialize();
	bool Render(IResourceBinder* input);
	bool Terminate();

	RenderPassDataComponent* GetRPDC();
	ShaderProgramComponent* GetSPC();
	IResourceBinder* GetResult();
};
