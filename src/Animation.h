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
		static void sideSlideIn(QWidget* _widget, ApplicationSide _side = LeftSide, bool _blockingMode = false);

		/**
		 * @brief Закатить виджет из-за стороны приложения
		 */
		static void sideSlideOut(QWidget* _widget, ApplicationSide _side = LeftSide, bool _blockingMode = false);

		/**
		 * @brief Закатить/выкатить виджет из-за стороны приложения
		 */
		static void sideSlide(QWidget* _widget, ApplicationSide _side = LeftSide, bool _in = true, bool _blockingMode = false);

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
