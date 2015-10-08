#include "SideSlideWidget.h"

#include <QPainter>

using WAF::SideSlideWidget;


SideSlideWidget::SideSlideWidget(QWidget* _parent) :
	AbstractAnimationWidget(_parent),
	m_applicationSide(WAF::LeftSide)
{
	grabParentWidget();

	connect(&m_forwardTimeLine, &QTimeLine::frameChanged, this, &SideSlideWidget::slideInUpdatePixmap);
	connect(&m_backwardTimeLine, &QTimeLine::frameChanged, this, &SideSlideWidget::slideOutUpdatePixmap);
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
	int x = 0;
	int y = 0;
	if (applicationSide() == WAF::RightSide) {
		x = width() - _pixmap.width();
	}
	else if (applicationSide() == WAF::BottomSide) {
		y = height() - _pixmap.height();
	}
	m_backgroundPixmap = m_backgroundPixmap.copy(x, y, _pixmap.width(), _pixmap.height());

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
	int backgroundX = 0;
	int backgroundY = 0;
	if (applicationSide() == WAF::RightSide) {
		backgroundX = width() - m_backgroundPixmap.width();
	}
	else if (applicationSide() == WAF::BottomSide) {
		backgroundY = height() - m_backgroundPixmap.height();
	}
	painter.drawPixmap(backgroundX, backgroundY, m_backgroundPixmap);

	//
	// Рисуем шаг анимации, в зависимости от стороны выезжания
	//
	int targetX = 0;
	int targetY = 0;
	if (applicationSide() == WAF::RightSide) {
		targetX = width() - m_targetPixmapForPaint.width();
	}
	else if (applicationSide() == WAF::BottomSide) {
		targetY = height() - m_targetPixmapForPaint.height();
	}
	painter.drawPixmap(targetX, targetY, m_targetPixmapForPaint);

	QWidget::paintEvent(_event);
}

void SideSlideWidget::mousePressEvent(QMouseEvent* _event)
{
	emit clicked();
	QWidget::mousePressEvent(_event);
}

void SideSlideWidget::slideInUpdatePixmap(int _value)
{
	if (_value == 0) {
		m_targetPixmapForPaint = QPixmap();
	} else {
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
	}
	repaint();
}

void SideSlideWidget::slideOutUpdatePixmap(int _value)
{
	if (_value != 0) {
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
