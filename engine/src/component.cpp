#include "component.hpp"

// TRANSFORM //

Transform::Transform(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scl)
    : position(pos.x, pos.y, pos.z), rotation(rot.x, rot.y, rot.z), scale(scl.x, scl.y, scl.z)
    , Component("Transform", ComponentType::Transform)
{
    updateModelMatrix();
}

void Transform::SetPosition(float x, float y, float z)
{
    position.setX(x);
    position.setY(y);
    position.setZ(z);

    updateModelMatrix();
}

void Transform::SetRotation(float x, float y, float z)
{
    rotation.setX(x);
    rotation.setY(y);
    rotation.setZ(z);

    updateModelMatrix();
}

void Transform::SetScale(float x, float y, float z)
{
    scale.setX(x);
    scale.setY(y);
    scale.setZ(z);

    updateModelMatrix();
}

void Transform::updateModelMatrix()
{
    modelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x(), position.y(), position.z())) *
                  glm::toMat4(glm::quat(glm::radians(glm::vec3(rotation.x(), rotation.y(), rotation.z())))) *
                  glm::scale(glm::mat4(1.0f), glm::vec3(scale.x(), scale.y(), scale.z()));
}

// RIGIDBODY //
void Rigidbody::setMass(float mass)
{
    this->mass = mass;
}

void Rigidbody::setFriction(float friction)
{
    this->friction = friction;
}

void Rigidbody::setRestitution(float restitution)
{
    this->restitution = restitution;
}

void Rigidbody::setLinearVelocity(btVector3 velocity)
{
    linearVelocity = velocity;
}

void Rigidbody::setAngularVelocity(btVector3 velocity)
{
    angularVelocity = velocity;
}

void Rigidbody::setLinearFactor(btVector3 factor)
{
    linearFactor = factor;
}

void Rigidbody::setAngularFactor(btVector3 factor)
{
    angularFactor = factor;
}

void Rigidbody::setCollisionShape(btCollisionShape *shape)
{
    collisionShape = shape;
}

void Rigidbody::setCollisionFlags(int flags)
{
    collisionFlags = flags;
}

void Rigidbody::setGravity(btVector3 gravity)
{
    this->gravity = gravity;
}

void Rigidbody::setKinematic(bool kinematic)
{
    this->kinematic = kinematic;
}

void Rigidbody::setCenterOfMass(btVector3 centerOfMass)
{
    this->centerOfMass = centerOfMass;
}

// MESH_RENDERER //

MeshRenderer::MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader) : model(model), shader(shader)
, Component("MeshRenderer", ComponentType::MeshRenderer)
{

}

void MeshRenderer::SetModel(std::shared_ptr<Model> model)
{
    this->model = model;
}

void MeshRenderer::SetShader(std::shared_ptr<Shader> shader)
{
    this->shader = shader;
}

// DIRECTIONAL LIGHT //

DirectionalLight::DirectionalLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular)
    : direction(direction), ambient(ambient), diffuse(diffuse), specular(specular)
    , Component("DirectionalLight", ComponentType::DirectionalLight)
{

}

void DirectionalLight::SetDirection(glm::vec3 direction)
{
    this->direction = direction;
}

void DirectionalLight::SetAmbient(glm::vec3 ambient)
{
    this->ambient = ambient;
}

void DirectionalLight::SetDiffuse(glm::vec3 diffuse)
{
    this->diffuse = diffuse;
}

void DirectionalLight::SetSpecular(glm::vec3 specular)
{
    this->specular = specular;
}

// Script //
Script::Script(std::string name) : scriptName(name), Component("Script", ComponentType::Script)
{

}