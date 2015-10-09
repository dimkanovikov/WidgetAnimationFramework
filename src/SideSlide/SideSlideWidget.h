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
		void updatePixmapWhenSlide(int _value);

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
