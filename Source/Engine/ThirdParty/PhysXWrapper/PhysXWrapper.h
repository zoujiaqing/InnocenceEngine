#pragma once
#include "../../Common/InnoMathHelper.h"
#include "../../Component/PhysicsDataComponent.h"

class PhysXWrapper
{
public:
	~PhysXWrapper() {};

	static PhysXWrapper& get()
	{
		static PhysXWrapper instance;
		return instance;
	}
	bool setup();
	bool initialize();
	bool update();
	bool terminate();

	bool createPxSphere(PhysicsDataComponent* rhs, float radius, bool isDynamic);
	bool createPxBox(PhysicsDataComponent* rhs, bool isDynamic);
	bool createPxMesh(PhysicsDataComponent* rhs, bool isDynamic, bool isConvex);

	bool addForce(PhysicsDataComponent* rhs, Vec4 force);

private:
	PhysXWrapper() {};
};
