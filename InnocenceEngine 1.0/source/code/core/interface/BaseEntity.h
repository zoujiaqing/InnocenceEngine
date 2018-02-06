#pragma once

#include "IEntity.h"
#include "../data/InnoMath.h"
#include "../manager/MemoryManager.hpp"

class Transform
{
public:
	Transform();
	~Transform();

	enum direction { FORWARD, BACKWARD, UP, DOWN, RIGHT, LEFT };
	void update();
	void rotate(const vec3 & axis, float angle);

	vec3& getPos();
	quat& getRot();
	vec3& getScale();

	void setPos(const vec3& pos);
	void setRot(const quat& rot);
	void setScale(const vec3& scale);

	vec3& getOldPos();
	quat& getOldRot();
	vec3& getOldScale();

	vec3 getDirection(direction direction) const;

private:
	vec3 m_pos;
	quat m_rot;
	vec3 m_scale;

	vec3 m_oldPos;
	quat m_oldRot;
	vec3 m_oldScale;
};

class BaseComponent;
class BaseActor : public IEntity
{
public:
	BaseActor();
	virtual ~BaseActor();

	void setup() override;
	void initialize() override;
	void update() override;
	void shutdown() override;

	void addChildActor(BaseActor* childActor);
	const std::vector<BaseActor*>& getChildrenActors() const;
	BaseActor* getParentActor() const;
	void setParentActor(BaseActor* parentActor);

	void addChildComponent(BaseComponent* childComponent);
	const std::vector<BaseComponent*>& getChildrenComponents() const;

	Transform* getTransform();
	bool hasTransformChanged();

	mat4 caclLocalPosMatrix();
	mat4 caclLocalRotMatrix();
	mat4 caclLocalScaleMatrix();

	vec3 caclWorldPos();
	quat caclWorldRot();
	vec3 caclWorldScale();

	mat4 caclWorldPosMatrix();
	mat4 caclWorldRotMatrix();
	mat4 caclWorldScaleMatrix();

	mat4 caclTransformationMatrix();

private:
	std::vector<BaseActor*> m_childActors;
	BaseActor* m_parentActor;
	std::vector<BaseComponent*> m_childComponents;
	Transform m_transform;
};

class BaseComponent : public IEntity
{
public:
	BaseComponent();
	virtual ~BaseComponent();

	BaseActor* getParentActor() const;
	void setParentActor(BaseActor* parentActor);
	Transform* getTransform();
private:
	BaseActor* m_parentActor;
};