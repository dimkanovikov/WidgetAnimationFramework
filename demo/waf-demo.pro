QT       += core gui widgets

TARGET = waf-demo
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp \
    ../src/Animation.cpp \
    ../src/SideSlide/SideSlideAnimator.cpp \
    ../src/SideSlide/SideSlideWidget.cpp

HEADERS += \
    ../src/Animation.h \
    ../src/AnimationPrivate.h \
    ../src/AbstractAnimator.h \
    ../src/SideSlide/SideSlideAnimator.h \
    ../src/SideSlide/SideSlideWidget.h \
    ../src/AbstractAnimationWidget.h

RESOURCES += \
    resources/resources.qrc
