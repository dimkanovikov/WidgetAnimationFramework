#ifndef ANIMATIONPRIVATE
#define ANIMATIONPRIVATE

#include <QMap>

class QWidget;


/**
 * Widgets Animation Framework
 */
namespace WAF
{
	class AbstractAnimator;


	/**
	 * @brief Данные фасада анимаций
	 */
	class AnimationPrivate
	{
	public:
		/**
		 * @brief Есть ли аниматор выкатывания для заданного виджета
		 */
		bool hasSideSlideAnimator(QWidget* _widget) const {
			return m_sideSlideAnimators.contains(_widget);
		}

		/**
		 * @brief Получить аниматор выкатывания для заданного виджета
		 */
		AbstractAnimator* sideSlideAnimator(QWidget* _widget) const {
			return m_sideSlideAnimators.value(_widget, 0);
		}

		/**
		 * @brief Сохранить аниматор выкатывания для заданного виджета
		 */
		void saveSideSlideAnimator(QWidget* _widget, AbstractAnimator* _animator) {
			if (!hasSideSlideAnimator(_widget)) {
				m_sideSlideAnimators.insert(_widget, _animator);
			}
		}

	private:
		/**
		 * @brief Карта аниматоров, связанных с управляемыми видежатами
		 */
		QMap<QWidget*, AbstractAnimator*> m_sideSlideAnimators;
	};
}

#endif // ANIMATIONPRIVATE

