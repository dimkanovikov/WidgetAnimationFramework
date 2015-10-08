#include "SideSlideAnimator.h"
#include "SideSlideWidget.h"

#include <QEventLoop>
#include <QTimer>

using WAF::SideSlideAnimator;
using WAF::SideSlideWidget;


SideSlideAnimator::SideSlideAnimator(QWidget* _widgetForSlide) :
	AbstractAnimator(_widgetForSlide)
{
	Q_ASSERT(_widgetForSlide);
}

void SideSlideAnimator::setApplicationSide(WAF::ApplicationSide _side)
{
	sideSlideWidget()->setApplicationSide(_side);
}

void SideSlideAnimator::animateForward(bool _blockingMode)
{
	if (_blockingMode) {
		slideIn();
	} else {
		QTimer::singleShot(0, this, &SideSlideAnimator::slideIn);
	}
}

void SideSlideAnimator::slideIn()
{
	if (widgetForSlide()->isHidden()) {
		//
		// Определяем самый верхний виджет приложения
		//
		QWidget* topWidget = widgetForSlide()->parentWidget();
		while (topWidget->parentWidget() != 0) {
			topWidget = topWidget->parentWidget();
		}

		//
		// Покрываем приложение виджетом, который будет рисовать анимацию,
		// а также "съедать" клики и задвигать виджет обратно
		//
		sideSlideWidget()->setParent(topWidget);
		sideSlideWidget()->resize(topWidget->size());
		sideSlideWidget()->grabParentWidget();
		sideSlideWidget()->raise();
		sideSlideWidget()->show();

		//
		// Определим финальный размер и положение выезжающего виджета
		//
		// TODO: скорректировать размер, если конфликтует с размером приложения
		//
		QSize finalSize = widgetForSlide()->sizeHint();
		QPoint finalPosition;
		switch (sideSlideWidget()->applicationSide()) {
			case WAF::LeftSide: {
				finalPosition = QPoint(0, 0);
				finalSize.setHeight(topWidget->height());
				break;
			}

			case WAF::TopSide: {
				finalPosition = QPoint(0, 0);
				finalSize.setWidth(topWidget->width());
				break;
			}

			case WAF::RightSide: {
				finalPosition = QPoint(topWidget->width() - finalSize.width(), 0);
				finalSize.setHeight(topWidget->height());
				break;
			}

			case WAF::BottomSide: {
				finalPosition = QPoint(0, topWidget->height() - finalSize.height());
				finalSize.setWidth(topWidget->width());
				break;
			}
		}

		//
		// Кладём виджет для анимации под рисовальщика и настраиваем его размер и положение
		//
		widgetForSlide()->show();
		widgetForSlide()->move(finalPosition);
		widgetForSlide()->resize(finalSize);

		//
		// Рисуем анимацию
		//
		sideSlideWidget()->slideIn(widgetForSlide()->grab());
		QEventLoop eventloop;
		connect(sideSlideWidget(), &SideSlideWidget::finished, &eventloop, &QEventLoop::quit);
		eventloop.exec();

		//
		// Помещаем реальный виджет поверх нарисованного
		//
		widgetForSlide()->raise();
	}
}

void SideSlideAnimator::animateBackward(bool _blockingMode)
{
	if (_blockingMode) {
		slideOut();
	} else {
		QTimer::singleShot(0, this, &SideSlideAnimator::slideOut);
	}
}

void SideSlideAnimator::slideOut()
{
	if (widgetForSlide()->isVisible()) {
		//
		// Получим картинку виджета
		//
		QPixmap widgetPixmap = widgetForSlide()->grab();
		widgetForSlide()->hide();

		//
		// Скрываем виджет
		//
		sideSlideWidget()->slideOut(widgetPixmap);
		sideSlideWidget()->raise();
		QEventLoop eventloop;
		connect(sideSlideWidget(), &SideSlideWidget::finished, &eventloop, &QEventLoop::quit);
		eventloop.exec();

		//
		// Скрываем обложку
		//
		sideSlideWidget()->hide();
	}
}

WAF::AbstractAnimationWidget* SideSlideAnimator::createAnimationWidget() const
{
	SideSlideWidget* slideWidget = new SideSlideWidget(widgetForSlide()->parentWidget());

	slideWidget->hide();
	connect(slideWidget, &SideSlideWidget::clicked, this, &SideSlideAnimator::slideOut);

	return slideWidget;
}

SideSlideWidget* SideSlideAnimator::sideSlideWidget()
{
	return qobject_cast<SideSlideWidget*>(animationWidget());
}

QWidget* SideSlideAnimator::widgetForSlide() const
{
	return qobject_cast<QWidget*>(parent());
}
