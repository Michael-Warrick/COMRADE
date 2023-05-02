#pragma once

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

// Transform component
class Transform
{
public:
    Transform();
    ~Transform();

    void setPosition(btVector3 position);
    void setRotation(btQuaternion rotation);
    void setScale(btVector3 scale);

    btVector3 getPosition() { return position; }
    btQuaternion getRotation() { return rotation; }
    btVector3 getScale() { return scale; }

    btTransform getTransform() { return transform; }

private:
    btVector3 position;
    btQuaternion rotation;
    btVector3 scale;

    btTransform transform;
};

// Rigidbody component
class Rigidbody
{
public:
    Rigidbody();
    ~Rigidbody();

    void setMass(float mass);
    void setFriction(float friction);
    void setRestitution(float restitution);
    void setLinearVelocity(btVector3 velocity);
    void setAngularVelocity(btVector3 velocity);
    void setLinearFactor(btVector3 factor);
    void setAngularFactor(btVector3 factor);
    void setCollisionShape(btCollisionShape* shape);
    void setCollisionFlags(int flags);
    void setGravity(btVector3 gravity);
    void setKinematic(bool kinematic);
    void setCenterOfMass(btVector3 centerOfMass);

    float getMass() { return mass; }
    float getFriction() { return friction; }
    float getRestitution() { return restitution; }
    btVector3 getLinearVelocity() { return linearVelocity; }
    btVector3 getAngularVelocity() { return angularVelocity; }
    btVector3 getLinearFactor() { return linearFactor; }
    btVector3 getAngularFactor() { return angularFactor; }
    btCollisionShape* getCollisionShape() { return collisionShape; }
    int getCollisionFlags() { return collisionFlags; }
    btVector3 getGravity() { return gravity; }
    bool getKinematic() { return kinematic; }
    btVector3 getCenterOfMass() { return centerOfMass; }

    btRigidBody* getRigidBody() { return rigidBody; }

private:
    float mass;
    float friction;
    float restitution;
    btVector3 linearVelocity;
    btVector3 angularVelocity;
    btVector3 linearFactor;
    btVector3 angularFactor;
    btCollisionShape* collisionShape;
    int collisionFlags;
    btVector3 gravity;
    bool kinematic;
    btVector3 centerOfMass;

    btRigidBody* rigidBody;
};

// Physics engine
class PhysicsEngine
{
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void update(float dt);

    void addRigidBody(btRigidBody* body);
    void removeRigidBody(btRigidBody* body);

    btDiscreteDynamicsWorld* getWorld() { return discreetdynamicsWorld; }

private:
    btBroadphaseInterface* broadphaseInterface;
    btDefaultCollisionConfiguration* collisionConfiguration;
    btCollisionDispatcher* collisionDispatcher;
    btSequentialImpulseConstraintSolver* sequentialImpulseSolver;
    btDiscreteDynamicsWorld* discreetdynamicsWorld;
};