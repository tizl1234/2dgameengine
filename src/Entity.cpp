#include "./Entity.h"
#include <iostream>

Entity::Entity(EntityManager& manager): manager(manager) {
    isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name): manager(manager), name(name) {
    isActive = true;
}

void Entity::Update(float deltaTime) {
    for(auto& component: components) {
        component->Update(deltaTime);
    }
}

void Entity::Render() {
    for(auto& component: components) {
        component->Render();
    }
}

void Entity::Destroy() {
    isActive = false;
}

bool Entity::IsActive() const {
    return isActive;
}

void Entity::ListAllComponents() const {
    for (const auto &component : componentTypeMap) {
        std::cout << component.first->name() << std::endl;
    }
}
