#ifndef ABSTRACTANIMATIONWIDGET
#define ABSTRACTANIMATIONWIDGET

#include <QWidget>

#include <QTimeLine>


/**
 * Widgets Animation Framework
 */
namespace WAF
{
	/**
	 * @brief Абстрактный класс виджета рисующего анимацию
	 */
	class AbstractAnimationWidget : public QWidget
	{
		Q_OBJECT

	public:
		explicit AbstractAnimationWidget(QWidget* _parent = 0) : QWidget(_parent) {
			//
			// Настроим исходные параметры таймлайнов
			//
			const int DEFAULT_DURATION = 300;
			m_forwardTimeLine.setDuration(DEFAULT_DURATION);
			m_backwardTimeLine.setDuration(DEFAULT_DURATION);
			//
			m_forwardTimeLine.setCurveShape(QTimeLine::EaseOutCurve);
			m_backwardTimeLine.setCurveShape(QTimeLine::EaseInCurve);
			//
			const int DEFAULT_UPDATE_INTERVAL = 20;
			m_forwardTimeLine.setUpdateInterval(DEFAULT_UPDATE_INTERVAL);
			m_backwardTimeLine.setUpdateInterval(DEFAULT_UPDATE_INTERVAL);
			//
			// Настроим сигнал о завершении анимации
			//
			connect(&m_forwardTimeLine, &QTimeLine::finished, this, &AbstractAnimationWidget::finished);
			connect(&m_backwardTimeLine, &QTimeLine::finished, this, &AbstractAnimationWidget::finished);
		}

		/**
		 * @brief Настроить параметры прямой анимации
		 */
		void setForwardAnimationProperties(QTimeLine::CurveShape _easingCurve, int _duration)
		{
			m_forwardTimeLine.setCurveShape(_easingCurve);
			m_forwardTimeLine.setDuration(_duration);
		}

		/**
		 * @brief Настроить параметры обратной анимации
		 */
		void setBackwardAnimationProperties(QTimeLine::CurveShape _easingCurve, int _duration)
		{
			m_backwardTimeLine.setCurveShape(_easingCurve);
			m_backwardTimeLine.setDuration(_duration);
		}

	signals:
		/**
		 * @brief Анимация закончена
		 */
		void finished();

	protected:
		/**
		 * @brief Таймлайн для анимации прямого действия
		 */
		QTimeLine m_forwardTimeLine;

		/**
		 * @brief Таймлайн для анимации обратного действия
		 */
		QTimeLine m_backwardTimeLine;
	};
}

#endif // ABSTRACTANIMATIONWIDGET

