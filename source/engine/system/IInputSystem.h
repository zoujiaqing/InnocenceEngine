#pragma once
#include "../common/InnoType.h"
#include "../common/InnoMath.h"
#include "../exports/InnoSystem_Export.h"
#include "../common/InnoClassTemplate.h"

struct InputConfig
{
	int totalKeyCodes;
	int totalMouseCodes;
};

INNO_INTERFACE IInputSystem
{
public:
	INNO_CLASS_INTERFACE_NON_COPYABLE(IInputSystem);

	INNO_SYSTEM_EXPORT virtual bool setup() = 0;
	INNO_SYSTEM_EXPORT virtual bool initialize() = 0;
	INNO_SYSTEM_EXPORT virtual bool update() = 0;
	INNO_SYSTEM_EXPORT virtual bool terminate() = 0;

	INNO_SYSTEM_EXPORT virtual InputConfig getInputConfig() = 0;

	INNO_SYSTEM_EXPORT virtual void addButtonStatusCallback(ButtonData boundButton, std::function<void()>* buttonStatusCallbackFunctor) = 0;
	INNO_SYSTEM_EXPORT virtual void addButtonStatusCallback(ButtonData boundButton, std::vector<std::function<void()>*>& buttonStatusCallbackFunctor) = 0;
	INNO_SYSTEM_EXPORT virtual void addButtonStatusCallback(ButtonStatusCallbackMap & buttonStatusCallbackFunctor) = 0;
	INNO_SYSTEM_EXPORT virtual void addMouseMovementCallback(int mouseCode, std::function<void(float)>* mouseMovementCallback) = 0;
	INNO_SYSTEM_EXPORT virtual void addMouseMovementCallback(int mouseCode, std::vector<std::function<void(float)>*>& mouseMovementCallback) = 0;
	INNO_SYSTEM_EXPORT virtual void addMouseMovementCallback(MouseMovementCallbackMap& mouseMovementCallback) = 0;

	INNO_SYSTEM_EXPORT virtual void framebufferSizeCallback(int width, int height) = 0;
	INNO_SYSTEM_EXPORT virtual void mousePositionCallback(float mouseXPos, float mouseYPos) = 0;
	INNO_SYSTEM_EXPORT virtual void scrollCallback(float xoffset, float yoffset) = 0;

	INNO_SYSTEM_EXPORT virtual vec4 getMousePositionInWorldSpace() = 0;
	INNO_SYSTEM_EXPORT virtual vec2 getMousePositionInScreenSpace() = 0;

	INNO_SYSTEM_EXPORT virtual ObjectStatus getStatus() = 0;
};
