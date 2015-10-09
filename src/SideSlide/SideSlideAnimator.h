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
		void animateForward(bool _asyncCall = true);
		void slideIn();
		/** @} */

		/**
		 * @brief Задвинуть виджет
		 */
		/** @{ */
		void animateBackward(bool _asyncCall = true);
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
