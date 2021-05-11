QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += inc/gui
INCLUDEPATH += inc/facade
INCLUDEPATH += inc/controller
INCLUDEPATH += inc/object
INCLUDEPATH += inc/scene
INCLUDEPATH += inc/managers
INCLUDEPATH += "inc/load"
INCLUDEPATH += inc/commands
INCLUDEPATH += inc/exceptions
INCLUDEPATH += inc/visitor

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    "src/load/file_loader.cpp" \
    src/commands/commands.cpp \
    src/controller/controller_creator.cpp \
    src/gui/abstract_factory.cpp \
    src/gui/qt_factory.cpp \
    src/load/builder.cpp \
    src/managers/reform_manager.cpp \
    src/controller/controller.cpp \
    src/facade/facade.cpp \
    src/gui/qt_drawer.cpp \
    src/main.cpp \
    src/gui/mainwindow.cpp \
    src/managers/draw_manager.cpp \
    src/managers/scene_manager.cpp \
    src/object/camera.cpp \
    src/object/composite.cpp \
    src/object/edge.cpp \
    src/object/model.cpp \
    src/object/object.cpp \
    src/object/point.cpp \
    src/object/units.cpp \
    src/scene/scene.cpp

HEADERS += \
    inc/commands/commands.h \
    inc/controller/base_controller.h \
    inc/controller/controller.h \
    inc/controller/controller_creator.h \
    inc/exceptions/base_exception.h \
    inc/exceptions/load_exceptions.h \
    inc/exceptions/model_exceptions.h \
    inc/exceptions/ui_exceptions.h \
    inc/facade/facade.h \
    inc/gui/abstract_factory.h \
    inc/gui/base_drawer.h \
    inc/gui/mainwindow.h \
    inc/gui/qt_drawer.h \
    inc/gui/qt_factory.h \
    inc/load/base_loader.h \
    inc/load/builder.h \
    inc/load/file_loader.h \
    inc/managers/base_manager.h \
    inc/managers/draw_manager.h \
    inc/managers/reform_manager.h \
    inc/managers/scene_manager.h \
    inc/object/camera.h \
    inc/object/composite.h \
    inc/object/edge.h \
    inc/object/model.h \
    inc/object/object.h \
    inc/object/point.h \
    inc/object/units.h \
    inc/scene/scene.h \
    inc/visitor/visitor.h

FORMS += \
    ui/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    data/cube.txt \
    data/dodecahedron.txt \
    data/icosahedron.txt \
    data/octahedron.txt \
    data/tetrahedron.txt
