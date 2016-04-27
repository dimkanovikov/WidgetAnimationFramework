#include "CircleFillAnimator.h"
#include "CircleFillDecorator.h"

#include <QPropertyAnimation>

using WAF::CircleFillAnimator;
using WAF::CircleFillDecorator;


CircleFillAnimator::CircleFillAnimator(QWidget* _widgetForFill) :
	AbstractAnimator(_widgetForFill),
	m_decorator(new CircleFillDecorator(_widgetForFill)),
	m_animation(new QPropertyAnimation(m_decorator, "radius"))
{
	Q_ASSERT(_widgetForFill);

	m_animation->setDuration(800);

	m_decorator->hide();

	connect(m_animation, &QPropertyAnimation::finished, [=] {
		setAnimatedStopped();
		if (isAnimatedBackward()) {
			m_decorator->hide();
		}
	});
}

void CircleFillAnimator::setStartPoint(const QPoint& _point)
{
	m_decorator->setStartPoint(_point);
}

void CircleFillAnimator::setFillColor(const QColor& _color)
{
	m_decorator->setFillColor(_color);
}

void CircleFillAnimator::animateForward()
{
	fillIn();
}

void CircleFillAnimator::fillIn()
{
	//
	// Прерываем выполнение, если клиент хочет повторить его
	//
	if (isAnimated() && isAnimatedForward()) return;
	setAnimatedForward();

	//
	// Определим стартовые и финальные позиции для декораций
	//
	int startRadius = 0;
	int finalRadius = widgetForFill()->height() + widgetForFill()->width();

	//
	// Позиционируем декораторы
	//
	m_decorator->resize(widgetForFill()->size());
	m_decorator->move(0, 0);
	m_decorator->show();
	m_decorator->raise();

	//
	// Анимируем виджет
	//
	if (m_animation->state() == QPropertyAnimation::Running) {
		//
		// ... если ещё не закончилась предыдущая анимация реверсируем её
		//
		m_animation->pause();
		m_animation->setDirection(QPropertyAnimation::Backward);
		m_animation->resume();
	} else {
		//
		// ... если предыдущая анимация закончилась, запускаем новую анимацию
		//
		m_animation->setEasingCurve(QEasingCurve::OutQuart);
		m_animation->setDirection(QPropertyAnimation::Forward);
		m_animation->setStartValue(startRadius);
		m_animation->setEndValue(finalRadius);
		m_animation->start();
	}
}

void CircleFillAnimator::animateBackward()
{
	fillOut();
}

void CircleFillAnimator::fillOut()
{
	//
	// Прерываем выполнение, если клиент хочет повторить его
	//
	if (isAnimated() && isAnimatedBackward()) return;
	setAnimatedBackward();

	//
	// Определим стартовые и финальные позиции для декораций
	//
	int startRadius = widgetForFill()->height() + widgetForFill()->width();
	int finalRadius = 0;

	//
	// Позиционируем декораторы
	//
	m_decorator->resize(widgetForFill()->size());
	m_decorator->move(0, 0);
	m_decorator->show();
	m_decorator->raise();

	//
	// Анимируем виджет
	//
	if (m_animation->state() == QPropertyAnimation::Running) {
		//
		// ... если ещё не закончилась предыдущая анимация реверсируем её
		//
		m_animation->pause();
		m_animation->setDirection(QPropertyAnimation::Backward);
		m_animation->resume();
	} else {
		//
		// ... если предыдущая анимация закончилась, запускаем новую анимацию
		//
		m_animation->setEasingCurve(QEasingCurve::OutQuart);
		m_animation->setDirection(QPropertyAnimation::Forward);
		m_animation->setStartValue(startRadius);
		m_animation->setEndValue(finalRadius);
		m_animation->start();
	}
}

QWidget* CircleFillAnimator::widgetForFill() const
{
	return qobject_cast<QWidget*>(parent());
}
