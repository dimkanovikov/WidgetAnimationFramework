#ifndef ABSTRACTANIMATOR
#define ABSTRACTANIMATOR

#include <QTimeLine>
#include <QObject>

#include "AbstractAnimationWidget.h"

/**
 * Widgets Animation Framework
 */
namespace WAF
{
	/**
	 * @brief Абстрактный класс аниматора
	 */
	class AbstractAnimator : public QObject
	{
		Q_OBJECT

	public:
		explicit AbstractAnimator(QObject* _parent = 0) :
			QObject(_parent), m_animationWidget(0) {}

		/**
		 * @brief Выполнить прямую анимацию
		 */
		virtual void animateForward(bool _blockingMode = true) = 0;

		/**
		 * @brief Выполнить обратную анимацию
		 */
		virtual void animateBackward(bool _blockingMode = true) = 0;

		/**
		 * @brief Настроить параметры прямой анимации
		 */
		void setForwardAnimationProperties(QTimeLine::CurveShape _easingCurve, int _duration) {
			animationWidget()->setForwardAnimationProperties(_easingCurve, _duration);
		}

		/**
		 * @brief Настроить параметры обратной анимации
		 */
		void setBackwardAnimationProperties(QTimeLine::CurveShape _easingCurve, int _duration) {
			animationWidget()->setBackwardAnimationProperties(_easingCurve, _duration);
		}

	protected:
		/**
		 * @brief Виртуальный метод для создания собственного виджета анимации в наследниках
		 */
		virtual AbstractAnimationWidget* createAnimationWidget() const = 0;

		/**
		 * @brief Получить виджет рисующий анимацию
		 */
		AbstractAnimationWidget* animationWidget()  {
			if (m_animationWidget == 0) {
				m_animationWidget = createAnimationWidget();
			}

			return m_animationWidget;
		}

	private:
		/**
		 * @brief Виджет рисующий анимацию
		 */
		AbstractAnimationWidget* m_animationWidget;
	};
}

#endif // ABSTRACTANIMATOR

