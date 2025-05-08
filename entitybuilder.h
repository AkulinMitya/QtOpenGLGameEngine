#ifndef ENTITYBUILDER_H
#define ENTITYBUILDER_H

#include "scene/Scene.h"
#include "components/components.h"
#include "meshUtils.h"

class EntityBuilder
{
public:
    explicit EntityBuilder(Scene& scene);

    EntityBuilder& withTransform(Point position);
    EntityBuilder& withVelocity();
    EntityBuilder& withHealth(int hp);
    EntityBuilder& withTeam(TeamComponent::Team team);
    EntityBuilder& withMesh(const QString& texturePath, float w, float h);
    EntityBuilder& withAI();
    EntityBuilder& withCombat(float range, int damage);
    EntityBuilder& withCollidable();

    Entity build();

private:
    Scene& scene;
    Entity entity;
};

#endif // ENTITYBUILDER_H
