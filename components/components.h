#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "point/Point.h"
#include <vector>
#include <GL/gl.h>
#include <QOpenGLTexture>
#include "components/ComponentManager.h"

struct TransformComponent {
    Point position;
    float rotation;
    float scale;


    TransformComponent() : position({0, 0}), rotation(0), scale(1) {}


    TransformComponent(Point pos, float rot = 0, float scl = 1)
        : position(pos), rotation(rot), scale(scl) {}

    Point applyTransform(const Point& p) const {
        float rad = rotation * M_PI / 180.0f;
        return {
            (p.x * cos(rad) - p.y * sin(rad)) * scale + position.x,
            (p.x * sin(rad) + p.y * cos(rad)) * scale + position.y
        };
    }
};

struct VelocityComponent {
    Point velocity;
    VelocityComponent() = default;
    VelocityComponent(Point vel) : velocity(vel) {}
    VelocityComponent(float x, float y) : velocity{x, y} {}
};

struct MeshComponent {
    std::vector<Point> vertices;
    GLenum primitiveType = GL_POLYGON;
    QOpenGLTexture* texture = nullptr;
    float width = 0.5f;
    float height = 0.5f;
    MeshComponent() = default;
    MeshComponent(std::vector<Point> verts, GLenum primType = GL_TRIANGLES)
        : vertices(std::move(verts)), primitiveType(primType) {}
};

struct CollidableComponent {
    // Для пустых компонентов можно оставить только конструктор по умолчанию
    CollidableComponent() = default;

    // В будущем можно добавить параметры:
    // float radius = 0;
    // bool isTrigger = false;
};

struct TeamComponent {
    enum Team { ALLY, ENEMY } team;
    TeamComponent() = default;
    TeamComponent(Team t) : team(t) {}
};
struct HealthComponent {
    float health;
    HealthComponent(float h = 100.f) : health(h) {}
};

struct CombatComponent {
    float attackRange;
    int attackCooldownTicks = 120;   // сколько апдейтов между ударами (например, 30 апдейтов = 0.5 секунды при 60 FPS)
    int ticksSinceLastAttack = 0;   // сколько апдейтов прошло с последней атаки
    int damage;
    Entity target = MAX_ENTITIES;
};


struct AIComponent {
    enum State { MOVING, ATTACKING, RELOADING  } state = MOVING;
};


struct WinConditionComponent {
    std::function<bool(ComponentManager& cm)> condition;
    std::function<void()> onWin;
};


#endif // COMPONENTS_H
