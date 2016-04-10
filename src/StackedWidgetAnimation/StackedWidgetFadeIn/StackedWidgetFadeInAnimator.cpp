/*
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * Full license: https://github.com/dimkanovikov/WidgetAnimationFramework/blob/master/LICENSE
 */

#include "StackedWidgetFadeInAnimator.h"
#include "StackedWidgetFadeInDecorator.h"

#include <QEvent>
#include <QPropertyAnimation>
#include <QStackedWidget>

using WAF::StackedWidgetFadeInAnimator;
using WAF::StackedWidgetFadeInDecorator;


StackedWidgetFadeInAnimator::StackedWidgetFadeInAnimator(QStackedWidget* _container, QWidget* _widgetForSlide) :
	AbstractAnimator(_container),
	m_containerDecorator(new StackedWidgetFadeInDecorator(_container, _container->currentWidget())),
	m_widgetDecorator(new StackedWidgetFadeInDecorator(_container, _widgetForSlide)),
	m_containerAnimation(new QPropertyAnimation(m_containerDecorator, "opacity")),
	m_widgetAnimation(new QPropertyAnimation(m_widgetDecorator, "opacity"))
{
	Q_ASSERT(_container);
	Q_ASSERT(_widgetForSlide);

	_container->installEventFilter(this);

	m_containerAnimation->setDuration(200);
	m_widgetAnimation->setDuration(200);

	m_containerDecorator->hide();
	m_widgetDecorator->hide();

	connect(m_containerAnimation, &QPropertyAnimation::finished, [=] {
		m_widgetDecorator->move(0, 0);
		m_widgetDecorator->show();
		m_widgetDecorator->raise();
		m_widgetAnimation->start();
	});
	connect(m_widgetAnimation, &QPropertyAnimation::finished, [=] {
		setAnimatedStopped();

		_container->setCurrentWidget(_widgetForSlide);
		m_containerDecorator->hide();
		m_widgetDecorator->hide();
	});
}

void StackedWidgetFadeInAnimator::setFadeInColor(const QColor& _fadeInColor)
{
	m_containerDecorator->setFadeInColor(_fadeInColor);
	m_widgetDecorator->setFadeInColor(_fadeInColor);
}

void StackedWidgetFadeInAnimator::animateForward()
{
	fadeIn();
}

void StackedWidgetFadeInAnimator::fadeIn()
{
	//
	// Прерываем выполнение, если клиент хочет повторить его
	//
	if (isAnimated() && isAnimatedForward()) return;
	setAnimatedForward();

	//
	// Обновляем изображения виджетов в декораторах
	//
	m_containerDecorator->grabContainer();
	m_widgetDecorator->grabWidget();

	//
	// Определим стартовые и финальные позиции для декораций
	//
	qreal containerStartOpacity = 1;
	qreal containerEndOpacity = 0;
	qreal widgetStartOpacity = 0;
	qreal widgetEndOpacity = 1;

	//
	// Позиционируем декораторы
	//
	m_containerDecorator->setOpacity(containerStartOpacity);
	m_containerDecorator->move(0, 0);
	m_containerDecorator->show();
	m_containerDecorator->raise();

	//
	// Анимируем виджет
	//
	if (m_widgetAnimation->state() == QPropertyAnimation::Running) {
		//
		// ... если ещё не закончилась предыдущая анимация реверсируем её ничего не делаем
		//
	} else {
		//
		// ... если предыдущая анимация закончилась, запускаем новую анимацию
		//
		m_containerAnimation->setEasingCurve(QEasingCurve::InQuad);
		m_containerAnimation->setDirection(QPropertyAnimation::Forward);
		m_containerAnimation->setStartValue(containerStartOpacity);
		m_containerAnimation->setEndValue(containerEndOpacity);
		m_widgetAnimation->setEasingCurve(QEasingCurve::OutQuad);
		m_widgetAnimation->setDirection(QPropertyAnimation::Forward);
		m_widgetAnimation->setStartValue(widgetStartOpacity);
		m_widgetAnimation->setEndValue(widgetEndOpacity);

		m_containerAnimation->start();
	}
}

bool StackedWidgetFadeInAnimator::eventFilter(QObject* _object, QEvent* _event)
{
	if (_object == widgetForSlide()
		&& _event->type() == QEvent::Resize) {
		m_containerDecorator->grabWidget();
		m_widgetDecorator->grabWidget();
	}

	return QObject::eventFilter(_object, _event);
}

QWidget* StackedWidgetFadeInAnimator::widgetForSlide() const
{
	return qobject_cast<QWidget*>(parent());
}
