QT       += core gui
QT       += opengl
QT       += openglwidgets

include(qtgifimage/src/gifimage/qtgifimage.pri)

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# Исходные файлы
SOURCES += \
    back/modeltransform/affinetransformations.cc \
    back/modeltransform/parser.cc \
    back/rendering/opengl.cc \
    view/main.cc \
    view/mainwindow/mainwindow.cc \
    view/widget/positionwidget.cc \
    view/widget/settingswidget.cc 
    
# Заголовочные файлы
HEADERS += \
    back/modeltransform/affinetransformations.h \
    back/modeltransform/parser.h \
    back/rendering/opengl.h \
    controller/controller.h \
    view/mainwindow/mainwindow.h \
    view/struct/nodesave.h \
    view/widget/positionwidget.h \
    view/widget/settingswidget.h \
    view/widget/widgetfactory/positionfactory.h \
    view/widget/widgetfactory/settingsfactory.h \
    view/widget/widgetfactory/widgetfactory.h 

# Файлы форм
FORMS += \
    view/mainwindow/mainwindow.ui \
    view/widget/positionwidget.ui \
    view/widget/settingswidget.ui 

RESOURCES +=  \
    img/blender.gif 

ICON = $${PWD}/img/icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
