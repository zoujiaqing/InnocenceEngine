#pragma once
#include "../Common/InnoType.h"

#include "../Common/InnoClassTemplate.h"
#include "../Component/MeshDataComponent.h"
#include "../Component/MaterialDataComponent.h"
#include "../Component/TextureDataComponent.h"
#include "../Component/SkeletonDataComponent.h"
#include "../Component/AnimationDataComponent.h"

#include "../Component/VisibleComponent.h"

class IAssetSystem
{
public:
	INNO_CLASS_INTERFACE_NON_COPYABLE(IAssetSystem);

	virtual bool setup() = 0;
	virtual bool initialize() = 0;
	virtual bool update() = 0;
	virtual bool terminate() = 0;

	virtual ObjectStatus getStatus() = 0;

	virtual bool recordLoadedMeshMaterialPair(const char* fileName, const MeshMaterialPair& pair) = 0;
	virtual bool findLoadedMeshMaterialPair(const char* fileName, MeshMaterialPair& pair) = 0;

	virtual bool recordLoadedModel(const char* fileName, const ModelIndex& modelIndex) = 0;
	virtual bool findLoadedModel(const char* fileName, ModelIndex& modelIndex) = 0;

	virtual bool recordLoadedTexture(const char* fileName, TextureDataComponent* texture) = 0;
	virtual bool findLoadedTexture(const char* fileName, TextureDataComponent*& texture) = 0;

	virtual bool recordLoadedSkeleton(const char* fileName, SkeletonDataComponent* skeleton) = 0;
	virtual bool findLoadedSkeleton(const char* fileName, SkeletonDataComponent*& skeleton) = 0;

	virtual bool recordLoadedAnimation(const char* fileName, AnimationDataComponent* animation) = 0;
	virtual bool findLoadedAnimation(const char* fileName, AnimationDataComponent*& animation) = 0;

	virtual uint64_t getCurrentMeshMaterialPairOffset() = 0;
	virtual uint64_t addMeshMaterialPair(const MeshMaterialPair& pair) = 0;
	virtual const MeshMaterialPair& getMeshMaterialPair(uint64_t index) = 0;

	virtual ModelIndex addUnitModel(MeshShapeType meshShapeType) = 0;
	virtual void addUnitCube(MeshDataComponent& meshDataComponent) = 0;
	virtual void addUnitSphere(MeshDataComponent& meshDataComponent) = 0;
	virtual void addUnitQuad(MeshDataComponent& meshDataComponent) = 0;
	virtual void addUnitLine(MeshDataComponent& meshDataComponent) = 0;
	virtual void addTerrain(MeshDataComponent& meshDataComponent) = 0;
};
