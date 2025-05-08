#include "mainwindow.h"
#include <QApplication>
#include "openGlWidget/MyOpenGlWidget.h"
#include <QDebug>
#include <QOpenGLTexture>
#include "entity/Entity.h"
#include "components/components.h"
#include "entitybuilder.h"



void setWinConditionRules(MyOpenGLWidget& widget) {

    Entity winEntity = widget.scene.createEntity(false, false);
    widget.scene.addComponent<WinConditionComponent>(winEntity,
         WinConditionComponent{
             // Победа
             [&widget](ComponentManager& cm) {
                 auto teams = cm.getAllEntitiesWith<TeamComponent>();
                 for (auto e : teams) {
                     if (cm.getComponent<TeamComponent>(e).team == TeamComponent::ENEMY)
                         return false;
                 }
                 return true;
             },
             // Действие при победе
             [&widget]() {
                 qDebug() << "VICTORY!";
                 widget.addLabel("You Win!", {0.5, 0.5}, {"Arial", 32, QFont::Bold}, Qt::green);
             }
         }
         );

    // Поражение
    Entity loseEntity = widget.scene.createEntity(false, false);
    widget.scene.addComponent<WinConditionComponent>(loseEntity,
         WinConditionComponent{
             [&widget](ComponentManager& cm) {
                 auto teams = cm.getAllEntitiesWith<TeamComponent>();
                 for (auto e : teams) {
                     if (cm.getComponent<TeamComponent>(e).team == TeamComponent::ALLY)
                         return false;
                 }
                 return true;
             },
             [&widget]() {
                 qDebug() << "DEFEAT!";
                    widget.addLabel("You Lose!", {0.5, 0.5}, {"Arial", 32, QFont::Bold}, Qt::red);
             }
         }
         );



}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MyOpenGLWidget widget;

    widget.show();

    Entity fort = EntityBuilder(widget.scene)
                      .withTransform({-1.5f, 0.0f})
                      .withHealth(300)
                      .withTeam(TeamComponent::ALLY)
                      .withMesh(":/new/prefix1/texture/fort.png", 1.0f, 1.2f)
                      .withCollidable()
                      .build();
    //widget.scene.addComponent<FortComponent>(fort);

    for (int i = 0; i < 1; ++i) {
        Entity soldier = EntityBuilder(widget.scene)
        .withTransform({-1.3f, i*0.5f})
            .withVelocity()
            .withHealth(100)
            .withTeam(TeamComponent::ALLY)
            .withMesh(":/new/prefix1/texture/ally.png", 0.5f, 0.5f)
            .withAI()
            .withCombat(0.5f, 10)
            .withCollidable()
            .build();
    }

    for (int i = 0; i < 3; ++i) {
        Entity soldier = EntityBuilder(widget.scene)
        .withTransform({2.0f, i*0.5f})
            .withVelocity()
            .withHealth(100)
            .withTeam(TeamComponent::ENEMY)
            .withMesh(":/new/prefix1/texture/enemy.png", 0.5f, 0.5f)
            .withAI()
            .withCombat(0.5f, 10)
            .withCollidable()
            .build();
    }

    setWinConditionRules(widget);
    widget.bindKey(Qt::Key_Y, [&]() {
        EntityBuilder(widget.scene)
        .withTransform({-1.2f, 0})
            .withVelocity()
            .withHealth(100)
            .withTeam(TeamComponent::ALLY)
            .withMesh(":/new/prefix1/texture/ally.png", 0.5f, 0.5f)
            .withAI()
            .withCombat(0.5f, 10)
            .withCollidable()
            .build();
    });

    return app.exec();
}

