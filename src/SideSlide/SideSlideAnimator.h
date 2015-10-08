#ifndef SIDESLIDEANIMATOR_H
#define SIDESLIDEANIMATOR_H

#include "../AbstractAnimator.h"
#include "../Animation.h"


/**
 * Widgets Animation Framework
 */
namespace WAF
{
	class SideSlideWidget;


	/**
	 * @brief Аниматор выдвижения виджета из-за стороны приложения
	 */
	class SideSlideAnimator : public AbstractAnimator
	{
	public:
		explicit SideSlideAnimator(QWidget* _widgetForSlide);

		/**
		 * @brief Установить сторону, откуда выдвигать виджет
		 */
		void setApplicationSide(ApplicationSide _side);

		/**
		 * @brief Выдвинуть виджет
		 */
		/** @{ */
		void animateForward(bool _blockingMode = true);
		void slideIn();
		/** @} */

		/**
		 * @brief Задвинуть виджет
		 */
		/** @{ */
		void animateBackward(bool _blockingMode = true);
		void slideOut();
		/** @} */

	private:
		/**
		 * @brief Определяем метод создающий необходимый виджет
		 */
		AbstractAnimationWidget* createAnimationWidget() const;

		/**
		 * @brief Получить виджет анимации
		 */
		SideSlideWidget* sideSlideWidget();

		/**
		 * @brief Получить виджет, который нужно анимировать
		 */
		QWidget* widgetForSlide() const;
	};
}

#endif // SIDESLIDEANIMATOR_H
