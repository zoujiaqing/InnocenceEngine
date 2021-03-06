#pragma once
#include "../Common/InnoType.h"
#include "../Common/InnoClassTemplate.h"
#include "../Export/InnoEngine_Export.h"
#include "ITimeSystem.h"
#include "ILogSystem.h"
#include "IMemorySystem.h"
#include "ITaskSystem.h"
#include "ITestSystem.h"
#include "IFileSystem.h"
#include "../EntityManager/IEntityManager.h"
#include "../ComponentManager/IComponentManager.h"
#include "../SceneHierarchyManager/ISceneHierarchyManager.h"
#include "IAssetSystem.h"
#include "IPhysicsSystem.h"
#include "IEventSystem.h"
#include "IWindowSystem.h"
#include "../RenderingFrontend/IRenderingFrontend.h"
#include "../RenderingFrontend/IGUISystem.h"
#include "../RenderingServer/IRenderingServer.h"

#include "IRenderingClient.h"
#include "ILogicClient.h"

enum EngineMode { Host, Slave };

enum RenderingServer { GL, DX11, DX12, VK, MT };

struct InitConfig
{
	EngineMode engineMode = EngineMode::Host;
	RenderingServer renderingServer = RenderingServer::GL;
	LogLevel logLevel = LogLevel::Success;
};

class IModuleManager
{
public:
	INNO_CLASS_INTERFACE_NON_COPYABLE(IModuleManager);

	INNO_ENGINE_API virtual bool setup(void* appHook, void* extraHook, char* pScmdline, IRenderingClient* renderingClient, ILogicClient* logicClient) = 0;
	INNO_ENGINE_API virtual bool initialize() = 0;
	INNO_ENGINE_API virtual bool run() = 0;
	INNO_ENGINE_API virtual bool terminate() = 0;

	INNO_ENGINE_API virtual ObjectStatus getStatus() = 0;

	INNO_ENGINE_API virtual ITimeSystem* getTimeSystem() = 0;
	INNO_ENGINE_API virtual ILogSystem* getLogSystem() = 0;
	INNO_ENGINE_API virtual IMemorySystem* getMemorySystem() = 0;
	INNO_ENGINE_API virtual ITaskSystem* getTaskSystem() = 0;
	INNO_ENGINE_API virtual ITestSystem* getTestSystem() = 0;
	INNO_ENGINE_API virtual IFileSystem* getFileSystem() = 0;
	INNO_ENGINE_API virtual IEntityManager* getEntityManager() = 0;
	INNO_ENGINE_API virtual IComponentManager* getComponentManager(uint32_t componentTypeID) = 0;
	INNO_ENGINE_API virtual ISceneHierarchyManager* getSceneHierarchyManager() = 0;
	INNO_ENGINE_API virtual IAssetSystem* getAssetSystem() = 0;
	INNO_ENGINE_API virtual IPhysicsSystem* getPhysicsSystem() = 0;
	INNO_ENGINE_API virtual IEventSystem* getEventSystem() = 0;
	INNO_ENGINE_API virtual IWindowSystem* getWindowSystem() = 0;
	INNO_ENGINE_API virtual IRenderingFrontend* getRenderingFrontend() = 0;
	INNO_ENGINE_API virtual IGUISystem* getGUISystem() = 0;
	INNO_ENGINE_API virtual IRenderingServer* getRenderingServer() = 0;

	INNO_ENGINE_API virtual InitConfig getInitConfig() = 0;

	INNO_ENGINE_API virtual float getTickTime() = 0;

	INNO_ENGINE_API virtual const FixedSizeString<128>& getApplicationName() = 0;
};
