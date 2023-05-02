// Entity Class

#pragma once

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

struct Transform
{
    Transform();
    ~Transform();

    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    btVector3 getPosition() { return position; }
    btVector3 getRotation() { return rotation; }
    btVector3 getScale() { return scale; }

private:
    btVector3 position;
    btVector3 rotation;
    btVector3 scale;
};

struct MeshRenderer
{
    MeshRenderer();
    ~MeshRenderer();

    void setMesh(const char* mesh);
    void setMaterial(const char* material);

    const char* getMesh() { return mesh; }
    const char* getMaterial() { return material; }  

private:
    const char* mesh;
    const char* material;
};

struct RigidBody
{
    RigidBody();
    ~RigidBody();

    void setMass(float mass);
    void setFriction(float friction);
    void setRestitution(float restitution);

    float getMass() { return mass; }
    float getFriction() { return friction; }
    float getRestitution() { return restitution; }

private:
    float mass;
    float friction;
    float restitution;
};