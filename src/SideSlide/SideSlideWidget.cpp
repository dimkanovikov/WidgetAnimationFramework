/*
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * Full license: https://github.com/dimkanovikov/WidgetAnimationFramework/blob/master/LICENSE
 */

#include "SideSlideWidget.h"

#include <QPainter>

using WAF::SideSlideWidget;


namespace {
	/**
	 * @brief Получить урезанную область изображения для отображения
	 */
	static QRect pixmapRect(WAF::ApplicationSide _side, const QSize& _inner, const QSize& _outer) {
		QPoint position(0, 0);
		if (_side == WAF::RightSide) {
			position.setX(_outer.width() - _inner.width());
		}
		else if (_side == WAF::BottomSide) {
			position.setY(_outer.height() - _inner.height());
		}

		return QRect(position, _inner);
	}
}


SideSlideWidget::SideSlideWidget(QWidget* _parent) :
	AbstractAnimationWidget(_parent),
	m_applicationSide(WAF::LeftSide)
{
	grabParentWidget();

	connect(&m_forwardTimeLine, &QTimeLine::frameChanged, this, &SideSlideWidget::updatePixmapWhenSlide);
	connect(&m_backwardTimeLine, &QTimeLine::frameChanged, this, &SideSlideWidget::updatePixmapWhenSlide);
}

WAF::ApplicationSide SideSlideWidget::applicationSide() const
{
	return m_applicationSide;
}

void SideSlideWidget::setApplicationSide(WAF::ApplicationSide _side)
{
	if (m_applicationSide != _side) {
		m_applicationSide = _side;
	}
}

void SideSlideWidget::grabParentWidget()
{
	m_backgroundPixmap = parentWidget()->grab();
}

void SideSlideWidget::slideIn(const QPixmap& _pixmap)
{
	m_targetPixmap = _pixmap;

	//
	// Оставляем непрозрачной, только ту часть над которой будет рисоваться анимация
	//
	const QRect backgroundRect = ::pixmapRect(applicationSide(), _pixmap.size(), size());
	m_backgroundPixmap = m_backgroundPixmap.copy(backgroundRect);

	//
	// Если ещё не завершилась предыдущая анимация, используем её состояние для начальной точки
	//
	int startFrame = 0;
	if (m_backwardTimeLine.state() == QTimeLine::Running) {
		m_backwardTimeLine.stop();
		startFrame = m_backwardTimeLine.currentFrame();
	}
	//
	int endFrame = 0;
	if (applicationSide() == WAF::LeftSide
		|| applicationSide() == WAF::RightSide) {
		endFrame = _pixmap.width();
	} else {
		endFrame = _pixmap.height();
	}
	m_forwardTimeLine.setFrameRange(startFrame, endFrame);

	m_forwardTimeLine.start();
}

void SideSlideWidget::slideOut(const QPixmap& _pixmap)
{
	m_targetPixmap = _pixmap;

	//
	// Делаем прозрачным весь фон
	//
	m_backgroundPixmap = QPixmap();

	int startFrame = 0;
	if (applicationSide() == WAF::LeftSide
		|| applicationSide() == WAF::RightSide) {
		startFrame = _pixmap.width();
	} else {
		startFrame = _pixmap.height();
	}
	//
	// Если ещё не завершилась предыдущая анимация, используем её состояние для начальной точки
	//
	if (m_forwardTimeLine.state() == QTimeLine::Running) {
		m_forwardTimeLine.stop();
		startFrame = m_forwardTimeLine.currentFrame();
	}
	m_backwardTimeLine.setFrameRange(startFrame, 0);

	m_backwardTimeLine.start();
}

void SideSlideWidget::paintEvent(QPaintEvent* _event)
{
	QPainter painter(this);
	painter.fillRect(rect(), Qt::transparent);

	//
	// Рисуем фон в необходимом расположении
	//
	const QRect backgroundRect = ::pixmapRect(applicationSide(), m_backgroundPixmap.size(), size());
	painter.drawPixmap(backgroundRect, m_backgroundPixmap);

	//
	// Рисуем шаг анимации, в зависимости от стороны выезжания
	//
	const QRect targetRect = ::pixmapRect(applicationSide(), m_targetPixmapForPaint.size(), size());
	painter.drawPixmap(targetRect, m_targetPixmapForPaint);

	QWidget::paintEvent(_event);
}

void SideSlideWidget::mousePressEvent(QMouseEvent* _event)
{
	emit clicked();
	QWidget::mousePressEvent(_event);
}

void SideSlideWidget::updatePixmapWhenSlide(int _value)
{
	if (_value > 0) {
		QSize finalSize = m_targetPixmap.size();
		QPoint finalPosition;
		switch (applicationSide()) {
			case WAF::LeftSide: {
				finalPosition = QPoint(m_targetPixmap.width() - _value, 0);
				finalSize.setWidth(_value);
				break;
			}

			case WAF::TopSide: {
				finalPosition = QPoint(0, m_targetPixmap.height() - _value);
				finalSize.setHeight(_value);
				break;
			}

			case WAF::RightSide: {
				finalPosition = QPoint(0, 0);
				finalSize.setWidth(_value);
				break;
			}

			case WAF::BottomSide: {
				finalPosition = QPoint(0, 0);
				finalSize.setHeight(_value);
				break;
			}
		}
		m_targetPixmapForPaint =
			m_targetPixmap.copy(QRect(finalPosition, finalSize));
	} else {
		m_targetPixmapForPaint = QPixmap();
	}
	repaint();
}
