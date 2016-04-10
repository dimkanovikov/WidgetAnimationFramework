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

#include "StackedWidgetFadeInDecorator.h"

#include <QPainter>
#include <QStackedWidget>

using WAF::StackedWidgetFadeInDecorator;


StackedWidgetFadeInDecorator::StackedWidgetFadeInDecorator(QWidget* _parent, QWidget* _widgetForGrab, const QColor& _fadeInColor) :
	QWidget(_parent),
	m_opacity(1),
	m_widgetForGrab(_widgetForGrab),
	m_fadeInColor(_fadeInColor)
{
	grabWidget();
}

qreal StackedWidgetFadeInDecorator::opacity() const
{
	return m_opacity;
}

void StackedWidgetFadeInDecorator::setOpacity(qreal _opacity)
{
	if (m_opacity != _opacity) {
		m_opacity = _opacity;

		repaint();
	}
}

void StackedWidgetFadeInDecorator::setFadeInColor(const QColor& _fadeInColor)
{
	if (m_fadeInColor != _fadeInColor) {
		m_fadeInColor = _fadeInColor;
	}
}

void StackedWidgetFadeInDecorator::grabContainer()
{
	if (QStackedWidget* container = qobject_cast<QStackedWidget*>(parentWidget())) {
		m_widgetForGrab = container->currentWidget();
		grabWidget();
	}
}

void StackedWidgetFadeInDecorator::grabWidget()
{
	const QSize size = parentWidget()->size();
	m_widgetForGrab->resize(size);
	resize(size);
	m_foreground = QPixmap(size);
	m_widgetForGrab->render(&m_foreground, QPoint(), QRegion(QRect(QPoint(), size)));
}

void StackedWidgetFadeInDecorator::paintEvent(QPaintEvent* _event)
{
	QPainter painter(this);
	painter.fillRect(rect(), m_fadeInColor);
	painter.setOpacity(m_opacity);
	painter.drawPixmap(0, 0, m_foreground);

	QWidget::paintEvent(_event);
}

