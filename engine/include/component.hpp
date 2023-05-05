#pragma once

#include <memory>

#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include "shader.hpp"
#include "model.hpp"

enum class ComponentType
{
    UNKNOWN,
    Transform,
    Rigidbody,
    MeshRenderer,
    Camera,
    DirectionalLight,
    Script
};

class Component
{
public:
    Component(const std::string& name, ComponentType type) : name(name), type(type) {}
    virtual ~Component() {}

    std::string GetName() { return name; }
    ComponentType GetType() { return type; }

protected:
    std::string name;
    ComponentType type;
};

// Transform component
struct Transform : public Component
{
    Transform(const glm::vec3 &pos, const glm::vec3 &rot, const glm::vec3 &scl);

    void SetPosition(float x, float y, float z);
    void SetRotation(float x, float y, float z);
    void SetScale(float x, float y, float z);

    btVector3 GetPosition() { return position; }
    btVector3 GetRotation() { return rotation; }
    btVector3 GetScale() { return scale; }
    glm::mat4 GetModelMatrix() { return modelMatrix; }

private:
    btVector3 position;
    btVector3 rotation;
    btVector3 scale;
    glm::mat4 modelMatrix = glm::mat4(1.0f);

    void updateModelMatrix();
};

// Rigidbody component
struct Rigidbody : public Component
{
    void setMass(float mass);
    void setFriction(float friction);
    void setRestitution(float restitution);
    void setLinearVelocity(btVector3 velocity);
    void setAngularVelocity(btVector3 velocity);
    void setLinearFactor(btVector3 factor);
    void setAngularFactor(btVector3 factor);
    void setCollisionShape(btCollisionShape *shape);
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
    btCollisionShape *getCollisionShape() { return collisionShape; }
    int getCollisionFlags() { return collisionFlags; }

protected:
    std::string name = "Rigidbody";
    ComponentType type = ComponentType::Rigidbody;

private:
    float mass;
    float friction;
    float restitution;
    btVector3 linearVelocity;
    btVector3 angularVelocity;
    btVector3 linearFactor;
    btVector3 angularFactor;
    btCollisionShape *collisionShape;
    int collisionFlags;
    btVector3 gravity;
    bool kinematic;
    btVector3 centerOfMass;
};

// MeshRenderer component
struct MeshRenderer : public Component
{
    MeshRenderer(std::shared_ptr<Model> model, std::shared_ptr<Shader> shader);

    void SetModel(std::shared_ptr<Model> model);
    void SetShader(std::shared_ptr<Shader> shader);

    std::shared_ptr<Model> GetModel() { return model; }
    std::shared_ptr<Shader> GetShader() { return shader; }

private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
};

struct DirectionalLight : Component
{
    DirectionalLight(const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular);

    void SetDirection(glm::vec3 direction);
    void SetAmbient(glm::vec3 ambient);
    void SetDiffuse(glm::vec3 diffuse);
    void SetSpecular(glm::vec3 specular);

    glm::vec3 GetDirection() { return direction; }
    glm::vec3 GetAmbient() { return ambient; }
    glm::vec3 GetDiffuse() { return diffuse; }
    glm::vec3 GetSpecular() { return specular; }

private:
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct PointLight : Component
{
    PointLight(const glm::vec3 &position, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic);

    void SetPosition(float x, float y, float z);
    void SetAmbient(float x, float y, float z);
    void SetDiffuse(float x, float y, float z);
    void SetSpecular(float x, float y, float z);
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);

    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetAmbient() { return ambient; }
    glm::vec3 GetDiffuse() { return diffuse; }
    glm::vec3 GetSpecular() { return specular; }
    float GetConstant() { return constant; }
    float GetLinear() { return linear; }
    float GetQuadratic() { return quadratic; }

private:
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight : Component 
{
    SpotLight(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &ambient, const glm::vec3 &diffuse, const glm::vec3 &specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff);

    void SetPosition(float x, float y, float z);
    void SetDirection(float x, float y, float z);
    void SetAmbient(float x, float y, float z);
    void SetDiffuse(float x, float y, float z);
    void SetSpecular(float x, float y, float z);
    void SetConstant(float constant);
    void SetLinear(float linear);
    void SetQuadratic(float quadratic);
    void SetCutOff(float cutOff);
    void SetOuterCutOff(float outerCutOff);

    glm::vec3 GetPosition() { return position; }
    glm::vec3 GetDirection() { return direction; }
    glm::vec3 GetAmbient() { return ambient; }
    glm::vec3 GetDiffuse() { return diffuse; }
    glm::vec3 GetSpecular() { return specular; }
    float GetConstant() { return constant; }
    float GetLinear() { return linear; }
    float GetQuadratic() { return quadratic; }
    float GetCutOff() { return cutOff; }
    float GetOuterCutOff() { return outerCutOff; }

private:
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutOff;
    float outerCutOff;
};

struct Script : Component
{
    enum class Language
    {
        Native,
        CSharp,
        Python
    };

    Script(std::string name);

    void SetScriptName(std::string name) { this->scriptName = name; }
    std::string GetScriptName() { return scriptName; }

    void SetPath(std::string path) { this->path = path; }
    std::string GetPath() { return path; }

    Language GetLanguage() { return language; }
    void SetLanguage(Language language) { this->language = language; }

private:
    std::string scriptName;
    std::string path;
    Language language;
};