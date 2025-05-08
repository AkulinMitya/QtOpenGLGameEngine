#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "camera/camera2d.h"
#include "systems/Systems.h"
#include "entity/EntityManager.h"
#include "components/ComponentManager.h"
#include "components/components.h"
#include "entity/Entity.h"

class Scene {

private:
    EntityManager entityManager;
    ComponentManager componentManager;
    SystemManager systemManager;

    Camera2D camera;

    Entity controllableEntity = MAX_ENTITIES + 1;
    Entity cameraFocusEntity = MAX_ENTITIES + 1;

public:
    Scene();
    Entity createEntity(bool isControllable, bool isCameraFocus) {
        Entity entity = entityManager.createEntity();
        if (isControllable) {
            controllableEntity = entity;
        }
        if (isCameraFocus) {
            cameraFocusEntity = entity;
        }
        return entity;
    }
    void destroyEntity(Entity entity);

    template<typename T, typename... Args>
    T& addComponent(Entity entity, Args&&... args) {
        T component(std::forward<Args>(args)...);
        componentManager.addComponent<T>(entity, component);
        updateSystemSubscriptions(entity);
        return componentManager.getComponent<T>(entity);
    }

    template<typename T>
    void removeComponent(Entity entity);

    template<typename T>
    T& getComponent(Entity entity) { return componentManager.getComponent<T>(entity); }

    template<typename T>
    bool hasComponent(Entity entity) { return componentManager.hasComponent<T>(entity); }

    void render();
    void update();
    bool isEmptyScene();
    Camera2D& getCamera() { return camera; }

    Entity getFocusEntity() { return cameraFocusEntity; }
    Entity getControllableEntity() { return controllableEntity; }
    void updateSystemSubscriptions(Entity entity);
};

#endif // SCENE_H
