#include "openGlWidget/MyOpenGLWidget.h"
#include <QDebug>
#include <QKeyEvent>



MyOpenGLWidget::MyOpenGLWidget(QWidget *parent) : QOpenGLWidget(parent) {}

void MyOpenGLWidget::initializeGL() {
    glEnable(GL_TEXTURE_2D);

    QImage img(":/new/prefix1/texture/background.jpg"); // Загружаем картинку
    if (!img.isNull()) {
        // Конвертируем в формат, который понимает OpenGL
        QImage glImage = img.mirrored(false, true).convertToFormat(QImage::Format_RGBA8888);

        backgroundTexture = new QOpenGLTexture(glImage);
        backgroundTexture->setMinificationFilter(QOpenGLTexture::Linear);
        backgroundTexture->setMagnificationFilter(QOpenGLTexture::Linear);
    }

    // QImage wallImg(":/new/prefix1/brick_wall.jpg");
    // if (!wallImg.isNull()) {
    //     brickTexture = new QOpenGLTexture(wallImg);
    // }

    connect(&timer, &QTimer::timeout, this, &MyOpenGLWidget::updateScene);
    timer.start(16); // 60 FPS
}



void MyOpenGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (backgroundTexture) {
        glEnable(GL_TEXTURE_2D);
        backgroundTexture->bind();

        glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1, -1);  // Низ-лево
        glTexCoord2f(1, 0); glVertex2f( 1, -1);  // Низ-право
        glTexCoord2f(1, 1); glVertex2f( 1,  1);  // Верх-право
        glTexCoord2f(0, 1); glVertex2f(-1,  1);  // Верх-лево
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }

    scene.render();

    QPainter painter(this);
    uiLabelManager.render(painter, size());
    painter.end();

    update();
}


void MyOpenGLWidget::updateScene() {
    scene.update();

    if (auto focus = scene.getFocusEntity(); focus != MAX_ENTITIES) {
        if (scene.hasComponent<TransformComponent>(focus)) {
            auto& transform = scene.getComponent<TransformComponent>(focus);
            scene.getCamera().setPosition(transform.position);
        }
    }

    update();
}

void MyOpenGLWidget::keyPressEvent(QKeyEvent* event) {

    // обработка камеры всегда
    switch (event->key()) {
    case Qt::Key_PageUp:
        qDebug() << "pageUp" << '\n';
        scene.getCamera().zoom *= 1.1f;
        break;

    case Qt::Key_PageDown:
        qDebug() << "pageDown" << '\n';
        scene.getCamera().zoom *= 0.9f;
        break;
    }
    inputManager.handleKeyPress(event->key());
    update();
    //    Entity controllable = scene.getControllableEntity();
    //  qDebug() << controllable;

    // // обработка сущности — только если она есть
    // if (controllable == MAX_ENTITIES) {
    //     update();
    //     return;
    // }

    // if (scene.hasComponent<VelocityComponent>(controllable)) {
    //     auto& vel = scene.getComponent<VelocityComponent>(controllable);

    //     switch (event->key()) {
    //     case Qt::Key_W:
    //         vel.velocity.y += 0.05f;
    //         qDebug() << controllable << " W" << '\n';
    //         break;
    //     case Qt::Key_S:
    //         vel.velocity.y -= 0.05f;
    //         qDebug() << controllable << " S" << '\n';
    //         break;
    //     case Qt::Key_A:
    //         vel.velocity.x -= 0.05f;
    //         break;
    //     case Qt::Key_D:
    //         vel.velocity.x += 0.05f;
    //         break;
    //     }
    // }

    // if (scene.hasComponent<TransformComponent>(controllable)) {
    //     auto& tr = scene.getComponent<TransformComponent>(controllable);

    //     switch (event->key()) {
    //     case Qt::Key_Q:
    //         qDebug() << controllable << " Q" << '\n';
    //         tr.rotation -= 10;
    //         break;

    //     case Qt::Key_E:
    //         qDebug() << controllable << " E" << '\n';
    //         tr.rotation += 10;
    //         break;

    //     case Qt::Key_Plus:
    //         qDebug() << controllable << " +" << '\n';
    //         tr.scale += 0.1f;
    //         break;

    //     case Qt::Key_Minus:
    //         qDebug() << controllable << " -" << '\n';
    //         tr.scale -= 0.1f;
    //         break;
    //     }
    // }
}

