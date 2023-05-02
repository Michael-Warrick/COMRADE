#include "gameObject.hpp"

GameObject::GameObject()
{
    name = "GameObject";
}

GameObject::GameObject(std::string name)
{
    this->name = name;
}

GameObject::~GameObject()
{
}

void GameObject::SetName(std::string name)
{
    this->name = name;
}

std::string GameObject::GetName()
{
    return name;
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
    components.push_back(component);
}

void GameObject::RemoveComponent(ComponentType type)
{
    // Iterate through the entity's list of components
    for (auto it = components.begin(); it != components.end(); ++it)
    {
        // Check if the current component matches the type to remove
        if ((*it)->GetType() == type)
        {
            // Remove the component from the list
            it = components.erase(it);

            // Exit the loop if the component was found and removed
            break;
        }
    }
}

std::shared_ptr<Component> GameObject::GetComponent(std::string componentName)
{
    for (int i = 0; i < components.size(); i++)
    {
        if (components[i]->GetName() == componentName)
        {
            return components[i];
        }
    }

    return nullptr;
}

std::vector<std::shared_ptr<Component>> GameObject::GetComponents()
{
    return components;
}

void GameObject::SetComponents(std::vector<std::shared_ptr<Component>> components)
{
    this->components = components;
}

void GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
    this->parent = parent;
}

std::shared_ptr<GameObject> GameObject::GetParent()
{
    return parent;
}

void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
    children.push_back(child);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
    for (int i = 0; i < children.size(); i++)
    {
        if (children[i] == child)
        {
            children.erase(children.begin() + i);
            break;
        }
    }
}

std::vector<std::shared_ptr<GameObject>> GameObject::GetChildren()
{
    return children;
}

bool GameObject::IsSelected()
{
    return selected;
}

void GameObject::SetSelected(bool selected)
{
    this->selected = selected;
}

bool GameObject::IsActive()
{
    return active;
}

void GameObject::SetActive(bool active)
{
    this->active = active;
}