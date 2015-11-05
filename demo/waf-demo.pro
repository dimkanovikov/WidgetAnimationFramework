QT       += core gui widgets

TARGET = waf-demo
TEMPLATE = app

CONFIG += c++11


SOURCES += main.cpp \
    ../src/Animation.cpp \
    ../src/SideSlide/SideSlideAnimator.cpp \
    ../src/Slide/SlideAnimator.cpp \
    ../src/Slide/SlideBackgroundDecorator.cpp \
    ../src/SideSlide/SideSlideBackgroundDecorator.cpp

HEADERS += \
    ../src/Animation.h \
    ../src/AnimationPrivate.h \
    ../src/AbstractAnimator.h \
    ../src/SideSlide/SideSlideAnimator.h \
    ../src/Slide/SlideAnimator.h \
    ../src/Slide/SlideBackgroundDecorator.h \
    ../src/SideSlide/SideSlideBackgroundDecorator.h

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    ../README.md
