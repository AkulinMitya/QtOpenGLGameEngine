#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <set>
#include <queue>
#include <cstdint>
#include "Entity.h"


class EntityManager {
private:
    std::queue<Entity> availableEntities;
    std::set<Entity> aliveEntities;
    Entity livingEntityCount = 0;

public:
    EntityManager() {
        for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
            availableEntities.push(entity);
        }
    }

    Entity createEntity() {
        Entity id = availableEntities.front();
        availableEntities.pop();
        aliveEntities.insert(id);
        ++livingEntityCount;
        return id;
    }

    void destroyEntity(Entity entity) {
        aliveEntities.erase(entity);
        availableEntities.push(entity);
        --livingEntityCount;
    }

    const std::set<Entity>& getAliveEntities() const {
        return aliveEntities;
    }
};

#endif // ENTITYMANAGER_H
