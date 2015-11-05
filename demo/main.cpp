/*
 * Copyright (C) 2015  Dimka Novikov, to@dimkanovikov.pro
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * Full license: https://github.com/dimkanovikov/WidgetAnimationFramework/blob/master/LICENSE
 */

#include <QApplication>

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollBar>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>

#include "../src/Animation.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QWidget w;

	//
	// Настроим главную панель
	//
	QFrame* mainToolbar = new QFrame(&w);
	mainToolbar->setProperty("toolbar", true);
	mainToolbar->setFrameShape(QFrame::StyledPanel);
	QToolButton* mainToolbarMenuButton = new QToolButton(mainToolbar);
	mainToolbarMenuButton->setIcon(QIcon(":/menu.png"));
	QLabel* mainToolbarTitle = new QLabel("<b>Widgets Animation Framework demo</b>", mainToolbar);
	QHBoxLayout* mainToolbarLayout = new QHBoxLayout(mainToolbar);
	mainToolbarLayout->setContentsMargins(QMargins());
	mainToolbarLayout->setSpacing(10);
	mainToolbarLayout->addWidget(mainToolbarMenuButton);
	mainToolbarLayout->addWidget(mainToolbarTitle);

	//
	// Настроим главный виджет
	//
	QTextEdit* textEdit = new QTextEdit(&w);
	textEdit->document()->setDocumentMargin(20);
	textEdit->setHtml(
		"<h1>WAF</h1>"
		"<h2>Widgets Animation Framework</h2>"
		"<p>Let you implement rich user interface interactions "
		"for applications based on Qt Widgets.</p>"
		"<h3>Side Sliding Animation</h3>"
		"<p>Slide widget from side of application and make background little darker for accent attension to slided widget. To do it just call</p>"
		"<p><pre>WAF::Animation::sideSlide</pre></p>"
		"<p>with your cool widget for slide and set application side from which their must slide.</p>"
		"<h3>Sliding Animation</h3>"
		"<p>Expand or collapse widgets in it's layout. Just call</p>"
		"<p><pre>WAF::Animation::slide</pre></p>"
		"<p>and set sliding direction."
        "<p></p>"
		);
	QVBoxLayout* mainLayout = new QVBoxLayout(&w);
	mainLayout->setContentsMargins(QMargins());
	mainLayout->setSpacing(0);
	mainLayout->addWidget(mainToolbar);
	mainLayout->addWidget(textEdit);

	//
	// Настроим меню
	//
	QFrame* menu = new QFrame(&w);
	menu->setProperty("menu", true);
	menu->setFixedWidth(300);
	//
	// ... панель меню
	//
	QFrame* menuToolbar = new QFrame(menu);
	menuToolbar->setFrameShape(QFrame::StyledPanel);
	QToolButton* menuToolbarBackButton = new QToolButton(menuToolbar);
	menuToolbarBackButton->setIcon(QIcon(":/arrow-left.png"));
	QLabel* menuToolbarTitle = new QLabel("<b>Menu</b>", menuToolbar);
	QHBoxLayout* menuToolbarLayout = new QHBoxLayout(menuToolbar);
	menuToolbarLayout->setContentsMargins(QMargins());
	menuToolbarLayout->setSpacing(10);
	menuToolbarLayout->addWidget(menuToolbarBackButton);
	menuToolbarLayout->addWidget(menuToolbarTitle);
	//
	QPushButton* menuButtonLogin = new QPushButton("Login", menu);
	menuButtonLogin->setProperty("menu", true);
	QPushButton* menuButtonExit = new QPushButton("Exit", menu);
	menuButtonExit->setProperty("menu", true);
	QVBoxLayout* menuLayout = new QVBoxLayout(menu);
	menuLayout->setContentsMargins(QMargins());
	menuLayout->setSpacing(0);
	menuLayout->addWidget(menuToolbar);
	menuLayout->addWidget(menuButtonLogin);
	menuLayout->addWidget(menuButtonExit);
	menuLayout->addStretch();
	menu->hide();

	//
	// Панель авторизации
	//
	QFrame* auth = new QFrame(&w);
	auth->setProperty("menu", false);
	auth->setFrameShape(QFrame::StyledPanel);
	QLineEdit* authUserName = new QLineEdit(auth);
	authUserName->setPlaceholderText("User Name");
	QLineEdit* authPassword = new QLineEdit(auth);
	authPassword->setPlaceholderText("Password");
	authPassword->setEchoMode(QLineEdit::Password);
	QPushButton* authLoginButton = new QPushButton("Login", auth);
	QPushButton* authCancelButton = new QPushButton("Cancel", auth);
	QVBoxLayout* authLayout = new QVBoxLayout(auth);
	authLayout->addWidget(authUserName);
	authLayout->addWidget(authPassword);
	QHBoxLayout* authButtonsLayout = new QHBoxLayout;
	authButtonsLayout->addWidget(authLoginButton);
	authButtonsLayout->addWidget(authCancelButton);
	authLayout->addLayout(authButtonsLayout);
	auth->hide();

	//
	// Настроим соединения
	//
	QObject::connect(mainToolbarMenuButton, &QToolButton::clicked, [=](){
		WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
	});
	QObject::connect(menuToolbarBackButton, &QToolButton::clicked, [=](){
		WAF::Animation::sideSlideOut(menu, WAF::LeftSide);
	});
	QObject::connect(menuButtonLogin, &QPushButton::clicked, [=](){
		WAF::Animation::sideSlideIn(auth, WAF::TopSide);
		authUserName->setFocus();
	});
	QObject::connect(authLoginButton, &QPushButton::clicked, [=](){
		WAF::Animation::sideSlideOut(auth, WAF::TopSide);
		QString userName = authUserName->text();
		if (userName.isEmpty()) {
			userName = "Noname";
		}
		menuButtonLogin->setText("Logged as " + userName);
		menuButtonLogin->setEnabled(false);
	});
	QObject::connect(authCancelButton, &QPushButton::clicked, [=](){
		WAF::Animation::sideSlideOut(auth, WAF::TopSide);
	});
	QObject::connect(menuButtonExit, &QPushButton::clicked, &QApplication::quit);

	//
	// Скрываем или показываем тулбар, в зависимости от направления прокрутки текстового редактора
	//
	QObject::connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged, [=](int _currentScrollPosition){
		static int lastScrollPosition = 0;
        static int lastScrollMaximum = textEdit->verticalScrollBar()->maximum();
        if (lastScrollMaximum == textEdit->verticalScrollBar()->maximum()) {
			//
			// Прокрутка вниз
			//
			if (lastScrollPosition < _currentScrollPosition) {
				if (mainToolbar->height() > 0) {
                    WAF::Animation::slideOut(mainToolbar, WAF::FromTopToBottom);
				}
			}
			//
			// Прокрутка вверх
			//
			else {
				if (mainToolbar->height() == 0) {
                    WAF::Animation::slideIn(mainToolbar, WAF::FromTopToBottom);
				}
            }
		}
        lastScrollPosition = _currentScrollPosition;
        lastScrollMaximum = textEdit->verticalScrollBar()->maximum();
	});

	//
	// Настроим и покажем приложение
	//
	w.setStyleSheet(
		"QToolButton { border: none; min-width: 40px; min-height: 40px; icon-size: 24px; }"
		"QTextEdit { border: none; }"
		"QPushButton[menu=true] { text-align: left; background-color: white; border: none; border-bottom: 1px solid palette(dark); padding: 8px; }"
		"QFrame[toolbar=true] { background-color: #66C966; }"
		"QFrame[menu=false] { background-color: palette(window); }"
		"QFrame[menu=true] { background-color: white; border: none; border-right: 1px solid palette(dark); }"
		);
	w.resize(400, 400);
	w.show();

	return a.exec();
}
