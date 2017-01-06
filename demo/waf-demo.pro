QT       += core gui widgets

TARGET = waf-demo
TEMPLATE = app

QMAKE_MAC_SDK = macosx10.11

CONFIG += c++11

INCLUDEPATH += ../src

HEADERS += \
    ../src/AbstractAnimator.h \
    ../src/Animation/Animation.h \
    ../src/Animation/AnimationPrivate.h \
    ../src/Animation/SideSlide/SideSlideAnimator.h \
    ../src/Animation/SideSlide/SideSlideBackgroundDecorator.h \
    ../src/Animation/Slide/SlideAnimator.h \
    ../src/Animation/Slide/SlideForegroundDecorator.h \
    ../src/StackedWidgetAnimation/StackedWidgetAnimation.h \
    ../src/StackedWidgetAnimation/StackedWidgetAnimationPrivate.h \
    ../src/WAF.h \
    ../src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.h \
    ../src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.h \
    ../src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.h \
    ../src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.h \
    ../src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.h \
    ../src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.h \
    ../src/Animation/CircleFill/CircleFillAnimator.h \
    ../src/Animation/CircleFill/CircleFillDecorator.h \
    ../src/Animation/Expand/ExpandAnimator.h \
    ../src/Animation/Expand/ExpandDecorator.h

SOURCES += main.cpp \
    ../src/Animation/Animation.cpp \
    ../src/Animation/SideSlide/SideSlideAnimator.cpp \
    ../src/Animation/SideSlide/SideSlideBackgroundDecorator.cpp \
    ../src/Animation/Slide/SlideAnimator.cpp \
    ../src/Animation/Slide/SlideForegroundDecorator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetAnimation.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.cpp \
    ../src/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.cpp \
    ../src/Animation/CircleFill/CircleFillAnimator.cpp \
    ../src/Animation/CircleFill/CircleFillDecorator.cpp \
    ../src/Animation/Expand/ExpandAnimator.cpp \
    ../src/Animation/Expand/ExpandDecorator.cpp

RESOURCES += \
    resources/resources.qrc

DISTFILES += \
    ../README.md
