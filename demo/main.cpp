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

#include <QDebug>
#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QResizeEvent>
#include <QScrollBar>
#include <QStackedWidget>
#include <QTabBar>
#include <QTextEdit>
#include <QTimer>
#include <QToolButton>
#include <QVBoxLayout>

#include <Animation/Animation.h>
#include <StackedWidgetAnimation/StackedWidgetAnimation.h>

class NotifyMessage : public QFrame
{
public:
	explicit NotifyMessage(const QString& _message, QWidget* _parent = 0) : QFrame(_parent) {
		setProperty("notifyMessage", true);

		QLabel* message = new QLabel(_message, this);
		message->setProperty("notifyMessage", true);
		message->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		message->setWordWrap(true);
		QToolButton* close = new QToolButton(this);
		close->setIcon(QIcon(":/close.png"));

		QHBoxLayout* layout = new QHBoxLayout(this);
		layout->addWidget(message);
		layout->addWidget(close);

		QObject::connect(close, &QToolButton::clicked, this, &NotifyMessage::hideMessage);

		setMaximumHeight(0);
		m_lastHeight = 0;

		QTimer* timer = new QTimer(this);
		QObject::connect(timer, &QTimer::timeout, [=] {
			if (m_lastHeight != maximumHeight()) {
				int delta = maximumHeight() - m_lastHeight;
				m_lastHeight = maximumHeight();
				parentWidget()->resize(parentWidget()->width(), parentWidget()->height() + delta);
				parentWidget()->move(parentWidget()->pos().x(), parentWidget()->pos().y() - delta);
			}
		});
		timer->start(10);
	}

	void showMessage() {
		WAF::Animation::slideIn(this, WAF::FromBottomToTop, false);
		QTimer::singleShot(5000, this, &NotifyMessage::hideMessage);
	}

	void hideMessage() {
		WAF::Animation::slideOut(this, WAF::FromBottomToTop, false);
	}

private:
	int m_lastHeight;
};

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
	// Настроим вкладки
	//
	QTabBar* tabs = new QTabBar(&w);
	tabs->addTab("TEXT");
	tabs->addTab("CREDITS");

	//
	// Настроим главный виджет
	//
	QStackedWidget* pages = new QStackedWidget(&w);
	//
	// ... настроим страницу с текстом
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
	pages->addWidget(textEdit);
	//
	// ... настроим страницу о программе
	//
	QLabel* creditsInfo = new QLabel(&w);
	creditsInfo->setText(
			"DimkaNovikov labs."
			);
	creditsInfo->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	pages->addWidget(creditsInfo);
	//
	// Настроим компоновку
	//
	QVBoxLayout* mainLayout = new QVBoxLayout(&w);
	mainLayout->setContentsMargins(QMargins());
	mainLayout->setSpacing(0);
	mainLayout->addWidget(mainToolbar);
	mainLayout->addWidget(tabs);
	mainLayout->addWidget(pages);

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
	QPushButton* menuButtonNotify = new QPushButton("Notify", menu);
	menuButtonNotify->setProperty("menu", true);
	QPushButton* menuButtonExit = new QPushButton("Exit", menu);
	menuButtonExit->setProperty("menu", true);
	QVBoxLayout* menuLayout = new QVBoxLayout(menu);
	menuLayout->setContentsMargins(QMargins());
	menuLayout->setSpacing(0);
	menuLayout->addWidget(menuToolbar);
	menuLayout->addWidget(menuButtonLogin);
	menuLayout->addWidget(menuButtonNotify);
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
	// Панель уведомлений
	//
	QFrame* notify = new QFrame(&w);
	notify->setProperty("notifyArea", true);
	notify->setFrameShape(QFrame::NoFrame);
	NotifyMessage* connectionMessage = new NotifyMessage("Connections estabilished", notify);
	NotifyMessage* subscriptionMessage = new NotifyMessage("Subscribe to <b>pro</b> account and get more available features.<br/><br/><a href=\"http://dimkanovikov.pro\">Read more</a>", notify);
	QVBoxLayout* notifyLayout = new QVBoxLayout(notify);
	notifyLayout->setContentsMargins(QMargins());
	notifyLayout->setSpacing(1);
	notifyLayout->addWidget(connectionMessage);
	notifyLayout->addWidget(subscriptionMessage);
	notify->hide();

	//
	// Настроим соединения
	//
	QObject::connect(mainToolbarMenuButton, &QToolButton::clicked, [=] {
		WAF::Animation::sideSlideIn(menu, WAF::LeftSide);
	});
	QObject::connect(menuToolbarBackButton, &QToolButton::clicked, [=] {
		WAF::Animation::sideSlideOut(menu, WAF::LeftSide);
	});
	QObject::connect(menuButtonLogin, &QPushButton::clicked, [=] {
		WAF::Animation::sideSlideIn(auth, WAF::TopSide);
		authUserName->setFocus();
	});
	QObject::connect(authLoginButton, &QPushButton::clicked, [=] {
		WAF::Animation::sideSlideOut(auth, WAF::TopSide);
		QString userName = authUserName->text();
		if (userName.isEmpty()) {
			userName = "Noname";
		}
		menuButtonLogin->setText("Logged as " + userName);
		menuButtonLogin->setEnabled(false);
	});
	QObject::connect(authCancelButton, &QPushButton::clicked, [=] {
		WAF::Animation::sideSlideOut(auth, WAF::TopSide);
	});
	QObject::connect(menuButtonNotify, &QPushButton::clicked, [=] {
		WAF::Animation::sideSlideOut(menu, WAF::LeftSide);
		WAF::Animation::sideSlideIn(notify, WAF::BottomSide, false);
		QTimer::singleShot(420, Qt::PreciseTimer, [=] {
			connectionMessage->showMessage();
			QTimer::singleShot(300, subscriptionMessage, &NotifyMessage::showMessage);
		});
	});
	QObject::connect(menuButtonExit, &QPushButton::clicked, &QApplication::quit);

	//
	// Соединяем вкладки со страницами
	//
	QObject::connect(tabs, &QTabBar::currentChanged, [=] (int _showWidgetIndex) {
		WAF::StackedWidgetAnimation::fadeIn(pages, pages->widget(_showWidgetIndex), pages->palette().window().color());
	});

	//
	// Скрываем или показываем тулбар и вкладки, в зависимости от направления прокрутки текстового редактора
	//
	QObject::connect(textEdit->verticalScrollBar(), &QScrollBar::valueChanged, [=] (int _currentScrollPosition) {
		static int lastScrollPosition = 0;
		static int lastScrollMaximum = textEdit->verticalScrollBar()->maximum();
		if (lastScrollMaximum == textEdit->verticalScrollBar()->maximum()) {
			//
			// Прокрутка вниз
			//
			if (lastScrollPosition < _currentScrollPosition) {
				if (mainToolbar->height() > 0) {
					WAF::Animation::slideOut(mainToolbar, WAF::FromTopToBottom);
					WAF::Animation::slideOut(tabs, WAF::FromTopToBottom);
				}
			}
			//
			// Прокрутка вверх
			//
			else {
				if (mainToolbar->height() == 0) {
					WAF::Animation::slideIn(mainToolbar, WAF::FromTopToBottom);
					WAF::Animation::slideIn(tabs, WAF::FromTopToBottom);
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
		"QAbstractButton { outline: none; }"
		"QToolButton { border: none; min-width: 40px; min-height: 40px; icon-size: 24px; }"
		"QTextEdit { border: none; }"
		"QPushButton[menu=true] { text-align: left; background-color: white; border: none; border-bottom: 1px solid palette(dark); padding: 8px; }"
		"QFrame[toolbar=true] { background-color: #66C966; }"
		"QFrame[menu=false] { background-color: palette(window); }"
		"QFrame[menu=true] { background-color: white; border: none; border-right: 1px solid palette(dark); }"
		"QFrame[notifyArea=true] { background-color: white; }"
		"QFrame[notifyMessage=true] { background-color: #232323; color: white; }"
		"QLabel[notifyMessage=true] { background-color: #232323; color: white; }"
		);
	w.resize(400, 400);
	w.show();

	return a.exec();
}
