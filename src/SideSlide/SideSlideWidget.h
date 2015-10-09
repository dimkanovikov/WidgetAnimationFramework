#ifndef SIDESLIDEWIDGET_H
#define SIDESLIDEWIDGET_H

#include "../AbstractAnimationWidget.h"
#include "../Animation.h"


/**
 * Widgets Animation Framework
 */
namespace WAF
{
	/**
	 * @brief Виджет рисующий выдвижение реального виджета
	 */
	class SideSlideWidget : public AbstractAnimationWidget
	{
		Q_OBJECT

	public:
		explicit SideSlideWidget(QWidget* _parent);

		/**
		 * @brief Сторона приложения из-за которой будет выдвигаться виджет
		 */
		ApplicationSide applicationSide() const;

		/**
		 * @brief Установить сторону из-за которой будет выдвигаться виджет
		 */
		void setApplicationSide(ApplicationSide _side);

		/**
		 * @brief Сохранить картинку с изображением виджета, который перекрывается анимацией
		 */
		void grabParentWidget();

		/**
		 * @brief Анимировать выдвижение заданной картинки
		 */
		void slideIn(const QPixmap& _pixmap);

		/**
		 * @brief Анимировать задвижение заданной картинки
		 */
		void slideOut(const QPixmap& _pixmap);

	signals:
		/**
		 * @brief На виджете выполнен щелчок мышью
		 */
		void clicked();

	protected:
		/**
		 * @brief Переопределяем, для отрисовки анимации
		 */
		void paintEvent(QPaintEvent* _event);

		/**
		 * @brief Переопределяем, для отлавливания щелчка мышью
		 */
		void mousePressEvent(QMouseEvent* _event);

	private:
		/**
		 * @brief Обновить отображаемое изображение анимированного виджета
		 */
		/** @{ */
//		void slideInUpdatePixmap(int _value);
//		void slideOutUpdatePixmap(int _value);
		void updatePixmapWhenSlide(int _value);
		/** @} */

	private:
		/**
		 * @brief Сторона из-за которой будет выдвигаться виджет
		 */
		ApplicationSide m_applicationSide;

		/**
		 * @brief Изображением виджета, который перекрывается анимацией
		 */
		QPixmap m_backgroundPixmap;

		/**
		 * @brief Изображение виджета, который необходимо анимировать
		 */
		QPixmap m_targetPixmap;

		/**
		 * @brief Изображение виждета в процессе анимации
		 */
		QPixmap m_targetPixmapForPaint;
	};
}

#endif // SIDESLIDEWIDGET_H
