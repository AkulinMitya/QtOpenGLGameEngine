#include "QDebug"
#include "Scene.h"
#include <algorithm>
#include <limits>
#include "meshUtils.h"


void Scene::render() {
    auto renderSystem = systemManager.getSystem<RenderSystem>();
    renderSystem->camera = &camera;
    renderSystem->update(componentManager);
}

void Scene::update() {
    auto aiSystem = systemManager.getSystem<AISystem>();
    aiSystem->update(componentManager, systemManager, entityManager);

    auto movementSystem = systemManager.getSystem<MovementSystem>();
    movementSystem->update(componentManager);

    auto collisionSystem = systemManager.getSystem<CollisionSystem>();
    collisionSystem->update(componentManager);

    auto winConditionSystem = systemManager.getSystem<WinConditionSystem>();
    winConditionSystem->update(componentManager);
}

void Scene::destroyEntity(Entity entity)
{
    componentManager.removeAllComponents(entity);
    systemManager.removeEntityFromAllSystems(entity);
    entityManager.destroyEntity(entity);
}


void Scene::updateSystemSubscriptions(Entity entity)
{
    for (auto& [type, system] : systemManager.getSystems()) {
        auto signature = systemManager.getSystemSignature(type);
        bool matches = true;

        for (auto& componentType : signature) {
            if (!componentManager.hasComponent(entity, componentType)) {
                matches = false;
                break;
            }
        }

        if (matches) {
            systemManager.addEntityToSystem(type, entity);
        } else {
            systemManager.removeEntityFromSystem(type, entity);
        }
    }
}


template<typename T>
void Scene::removeComponent(Entity entity)
{

    componentManager.removeComponent<T>(entity);
    updateSystemSubscriptions(entity);
}


Scene::Scene() {
    auto renderSystem = systemManager.registerSystem<RenderSystem>();
    auto movementSystem = systemManager.registerSystem<MovementSystem>();
    auto collisionSystem = systemManager.registerSystem<CollisionSystem>();
    auto aiSystem = systemManager.registerSystem<AISystem>();
    auto winConditionSystem = systemManager.registerSystem<WinConditionSystem>();

    // AISystem требует Transform + Velocity + AIComponent
    Signature aiSignature;
    aiSignature.insert(typeid(TransformComponent));
    aiSignature.insert(typeid(VelocityComponent));
    aiSignature.insert(typeid(AIComponent));
    systemManager.setSystemSignature<AISystem>(aiSignature);

    // RenderSystem требует Transform + Mesh
    Signature renderSignature;
    renderSignature.insert(typeid(TransformComponent));
    renderSignature.insert(typeid(MeshComponent));
    systemManager.setSystemSignature<RenderSystem>(renderSignature);

    // MovementSystem требует Transform + Velocity
    Signature movementSignature;
    movementSignature.insert(typeid(TransformComponent));
    movementSignature.insert(typeid(VelocityComponent));
    systemManager.setSystemSignature<MovementSystem>(movementSignature);

    // CollisionSystem требует Transform + Mesh + Collidable
    Signature collisionSignature;
    collisionSignature.insert(typeid(TransformComponent));
    collisionSignature.insert(typeid(MeshComponent));
    collisionSignature.insert(typeid(CollidableComponent));
    systemManager.setSystemSignature<CollisionSystem>(collisionSignature);

    Signature winConditionSignature;
    systemManager.setSystemSignature<WinConditionSystem>(winConditionSignature);

}
