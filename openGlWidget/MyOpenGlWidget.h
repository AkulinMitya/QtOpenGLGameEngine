#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include "scene/scene.h"
#include <QTimer>
#include <QOpenGLTexture>
#include "labels.h"
#include "InputManager.h"


class MyOpenGLWidget : public QOpenGLWidget {

private:
    QTimer timer;
    QOpenGLTexture* backgroundTexture = nullptr;
    UILabelManager uiLabelManager;
    InputManager inputManager;
protected:
    void initializeGL() override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;

public:
    void bindKey(int key, std::function<void()> action) {
        inputManager.bindKey(key, action);
    }
    void addLabel(const QString& text, const QPointF& pos, const QFont& font = QFont(), const QColor& color = Qt::white) {
        uiLabelManager.addLabel(text, pos, font, color);
    }
    QOpenGLTexture* brickTexture = nullptr;
    Scene scene;
    explicit MyOpenGLWidget(QWidget *parent = nullptr);

private slots:
    void updateScene();
};

#endif // MYOPENGLWIDGET_H
