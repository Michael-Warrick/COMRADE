#pragma once

#include <string>
#include <vector>
#include <memory>
#include <shared_mutex>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "definitions.hpp"

#include "component.hpp"

class GameObject
{
public:
    GameObject();
    GameObject(std::string name);
    ~GameObject();

    void SetName(std::string name);
    std::string GetName();

    void AddComponent(std::shared_ptr<Component> component);
    void RemoveComponent(ComponentType type);

    template <typename T>
    std::shared_ptr<T> GetComponent()
    {
        for (auto &component : components)
        {
            std::shared_ptr<T> derived = std::dynamic_pointer_cast<T>(component);
            if (derived)
                return derived;
        }
        return nullptr;
    }

    std::shared_ptr<Component> GetComponent(std::string componentName);

    std::vector<std::shared_ptr<Component>> GetComponents();
    void SetComponents(std::vector<std::shared_ptr<Component>> components);

    void SetParent(std::shared_ptr<GameObject> parent);
    std::shared_ptr<GameObject> GetParent();

    void AddChild(std::shared_ptr<GameObject> child);
    void RemoveChild(std::shared_ptr<GameObject> child);

    std::vector<std::shared_ptr<GameObject>> GetChildren();

    bool IsSelected();
    void SetSelected(bool selected);

    bool IsActive();
    void SetActive(bool active);

private:
    std::string name;
    std::vector<std::shared_ptr<Component>> components;
    std::shared_ptr<GameObject> parent;
    std::vector<std::shared_ptr<GameObject>> children;

    std::shared_ptr<Transform> transform;

    bool selected = false;
    bool active = true;
};