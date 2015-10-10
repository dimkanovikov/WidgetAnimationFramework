QT       += core gui widgets

TARGET = waf-demo
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp \
    ../src/Animation.cpp \
    ../src/SideSlide/SideSlideAnimator.cpp \
    ../src/SideSlide/BackgroundDecorator.cpp

HEADERS += \
    ../src/Animation.h \
    ../src/AnimationPrivate.h \
    ../src/AbstractAnimator.h \
    ../src/SideSlide/SideSlideAnimator.h \
    ../src/SideSlide/BackgroundDecorator.h

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    ../README.md
