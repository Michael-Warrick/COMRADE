// Implimentation of the physics engine
#include "physics.hpp"

// Physics engine
PhysicsEngine::PhysicsEngine()
{
    broadphaseInterface = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    collisionDispatcher = new btCollisionDispatcher(collisionConfiguration);
    sequentialImpulseSolver = new btSequentialImpulseConstraintSolver();
    discreetdynamicsWorld = new btDiscreteDynamicsWorld(collisionDispatcher, broadphaseInterface, sequentialImpulseSolver, collisionConfiguration);
    discreetdynamicsWorld->setGravity(btVector3(0, -9.81, 0));
}

void PhysicsEngine::update(float dt)
{
    discreetdynamicsWorld->stepSimulation(dt, 10);
}

void PhysicsEngine::addRigidBody(btRigidBody* body)
{
    discreetdynamicsWorld->addRigidBody(body);
}

void PhysicsEngine::removeRigidBody(btRigidBody* body)
{
    discreetdynamicsWorld->removeRigidBody(body);
}

PhysicsEngine::~PhysicsEngine()
{
    delete discreetdynamicsWorld;
    delete sequentialImpulseSolver;
    delete collisionDispatcher;
    delete collisionConfiguration;
    delete broadphaseInterface;
}