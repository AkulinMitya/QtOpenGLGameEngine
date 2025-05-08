#ifndef COMPONENTMANAGER_H
#define COMPONENTMANAGER_H

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <cassert>
#include "entity/Entity.h"

class IComponentArray {
public:
    virtual ~IComponentArray() = default;
    virtual void insertData(Entity entity) = 0;  // Основной метод
    virtual void removeEntity(Entity entity) = 0;
    virtual bool hasData(Entity entity) const = 0;
    virtual void* getDataPtr(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
private:
    std::unordered_map<Entity, T> componentMap;

public:
    // Основной виртуальный метод (без параметра компонента)
    void insertData(Entity entity) override {
        componentMap[entity] = T{};  // Создаем компонент по умолчанию
    }

    // Дополнительный метод (не виртуальный) с параметром компонента
    void insertData(Entity entity, T component) {
        componentMap[entity] = component;
    }

    void removeEntity(Entity entity) override {
        componentMap.erase(entity);
    }

    bool hasData(Entity entity) const override {
        return componentMap.count(entity) > 0;
    }

    void* getDataPtr(Entity entity) override {
        return &componentMap.at(entity);
    }

    T& getData(Entity entity) {
        assert(hasData(entity) && "Component not found for entity.");
        return componentMap[entity];
    }

    const T& getData(Entity entity) const {
        assert(hasData(entity) && "Component not found for entity.");
        return componentMap.at(entity);
    }
    std::vector<Entity> getAllEntities() const {
        std::vector<Entity> entities;
        for (const auto& pair : componentMap) {
            entities.push_back(pair.first);
        }
        return entities;
    }
};

class ComponentManager {
private:
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> componentArrays;

    template<typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray() {
        std::type_index typeName(typeid(T));
        if (componentArrays.find(typeName) == componentArrays.end()) {
            auto array = std::make_shared<ComponentArray<T>>();
            componentArrays[typeName] = array;
            return array;
        }
        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }

public:
    template<typename T>
    void addComponent(Entity entity, T component) {
        getComponentArray<T>()->insertData(entity, component);
    }

    template<typename T>
    void addComponent(Entity entity) {
        getComponentArray<T>()->insertData(entity);
    }

    template<typename T>
    void removeComponent(Entity entity) {
        if (auto array = getComponentArray<T>()) {
            array->removeEntity(entity);
        }
    }

    template<typename T>
    T& getComponent(Entity entity) {
        return getComponentArray<T>()->getData(entity);
    }

    template<typename T>
    const T& getComponent(Entity entity) const {
        return getComponentArray<T>()->getData(entity);
    }
    template<typename T>
    std::type_index getComponentType() const {
        return std::type_index(typeid(T));
    }
    bool hasComponent(Entity entity, std::type_index type) const {
        auto it = componentArrays.find(type);
        return it != componentArrays.end() && it->second->hasData(entity);
    }

    template<typename T>
    bool hasComponent(Entity entity) const {
        return hasComponent(entity, std::type_index(typeid(T)));
    }

    void removeAllComponents(Entity entity) {
        for (auto& pair : componentArrays) {
            pair.second->removeEntity(entity);
        }
    }
    void removeEntity(Entity entity) {
        for (auto& [_, componentArray] : componentArrays) {
            componentArray->removeEntity(entity);
        }
    }
    template<typename T>
    std::vector<Entity> getAllEntitiesWith() const {
        std::type_index typeName(typeid(T));
        auto it = componentArrays.find(typeName);
        if (it != componentArrays.end()) {
            auto componentArray = std::static_pointer_cast<ComponentArray<T>>(it->second);
            return componentArray->getAllEntities();
        }
        return {};
    }
};

#endif // COMPONENTMANAGER_H
