#include "MemorySystem.h"
#include "InnoMemory.h"

#include "../ICoreSystem.h"

extern ICoreSystem* g_pCoreSystem;

INNO_PRIVATE_SCOPE InnoMemorySystemNS
{
	ObjectStatus m_objectStatus = ObjectStatus::Terminated;
}

bool InnoMemorySystem::setup()
{
	InnoMemorySystemNS::m_objectStatus = ObjectStatus::Created;
	return true;
}

bool InnoMemorySystem::initialize()
{
	if (InnoMemorySystemNS::m_objectStatus == ObjectStatus::Created)
	{
		InnoMemorySystemNS::m_objectStatus = ObjectStatus::Activated;
		g_pCoreSystem->getLogSystem()->printLog(LogType::INNO_DEV_SUCCESS, "MemorySystem has been initialized.");
		return true;
	}
	else
	{
		g_pCoreSystem->getLogSystem()->printLog(LogType::INNO_ERROR, "MemorySystem: Object is not created!");
		return false;
	}
}

bool InnoMemorySystem::update()
{
	if (InnoMemorySystemNS::m_objectStatus == ObjectStatus::Activated)
	{
		return true;
	}
	else
	{
		InnoMemorySystemNS::m_objectStatus = ObjectStatus::Suspended;
		return false;
	}
}

bool InnoMemorySystem::terminate()
{
	InnoMemorySystemNS::m_objectStatus = ObjectStatus::Terminated;
	g_pCoreSystem->getLogSystem()->printLog(LogType::INNO_DEV_SUCCESS, "MemorySystem has been terminated.");
	return true;
}
ObjectStatus InnoMemorySystem::getStatus()
{
	return InnoMemorySystemNS::m_objectStatus;
}

void* InnoMemorySystem::allocateMemoryPool(size_t objectSize, unsigned int poolCapability)
{
	return InnoMemory::CreateObjectPool(objectSize, poolCapability);
}

void * InnoMemorySystem::allocateRawMemory(size_t size)
{
	return InnoMemory::Allocate(size);
}

bool InnoMemorySystem::deallocateRawMemory(void * ptr)
{
	InnoMemory::Deallocate(ptr);
	return true;
}

void * InnoMemorySystem::spawnObject(void * memoryPool, size_t objectSize)
{
	return reinterpret_cast<IObjectPool*>(memoryPool)->Spawn();
}

bool InnoMemorySystem::destroyObject(void * memoryPool, size_t objectSize, void * object)
{
	reinterpret_cast<IObjectPool*>(memoryPool)->Destroy(object);
	return true;
}