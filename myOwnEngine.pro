QT       += core gui openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    entitybuilder.cpp \
    meshUtils.cpp \
    openGlWidget/MyOpenGLWIdget.cpp \
    camera/camera2d.cpp \
    main.cpp \
    mainwindow.cpp \
    point/point.cpp \
    scene/scene.cpp \

HEADERS += \
    InputManager.h \
    components/ComponentManager.h \
    entity/Entity.h \
    entity/EntityManager.h \
    entitybuilder.h \
    labels.h \
    meshUtils.h \
    systems/Systems.h \
    components/components.h \
    openGlWidget/MyOpenGlWidget.h \
    camera/camera2d.h \
    mainwindow.h \
    point/point.h \
    scene/scene.h \

LIBS += -lopengl32

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
