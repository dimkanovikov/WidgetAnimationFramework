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

#ifndef ANIMATION_H
#define ANIMATION_H

class QWidget;


/**
 * Widgets Animation Framework
 */
namespace WAF
{
	/**
	 * @brief Края приложения
	 */
	enum ApplicationSide {
		LeftSide,
		TopSide,
		RightSide,
		BottomSide
	};

	/**
	 * @brief Данные фасада
	 */
	class AnimationPrivate;

	/**
	 * @brief Фасад доступа к анимациям
	 */
	class Animation
	{
	public:
		/**
		 * @brief Выкатить виджет из-за стороны приложения
		 */
		static void sideSlideIn(QWidget* _widget, ApplicationSide _side = LeftSide, bool _asyncCall = true);

		/**
		 * @brief Закатить виджет из-за стороны приложения
		 */
		static void sideSlideOut(QWidget* _widget, ApplicationSide _side = LeftSide, bool _asyncCall = true);

		/**
		 * @brief Закатить/выкатить виджет из-за стороны приложения
		 */
		static void sideSlide(QWidget* _widget, ApplicationSide _side = LeftSide, bool _in = true, bool _asyncCall = true);

	private:
		/**
		 * @brief Данные
		 */
		/** @{ */
		static AnimationPrivate* m_pimpl;
		static AnimationPrivate* pimpl();
		/** @} */
	};
}

#endif // ANIMATION_H
