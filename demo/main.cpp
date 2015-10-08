#include <QApplication>

#include <QFrame>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
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
	mainToolbar->setFrameShape(QFrame::StyledPanel);
	QToolButton* mainToolbarMenuButton = new QToolButton(mainToolbar);
	mainToolbarMenuButton->setIcon(QIcon(":/menu.png"));
	QLabel* mainToolbarTitle = new QLabel("<b>Widgets Animation Framework demo</b>", mainToolbar);
	QHBoxLayout* mainToolbarLayout = new QHBoxLayout(mainToolbar);
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
	menu->setFixedWidth(200);
	//
	// ... панель меню
	//
	QFrame* menuToolbar = new QFrame(menu);
	menuToolbar->setFrameShape(QFrame::StyledPanel);
	QToolButton* menuToolbarBackButton = new QToolButton(menuToolbar);
	menuToolbarBackButton->setIcon(QIcon(":/arrow-left.png"));
	QLabel* menuToolbarTitle = new QLabel("<b>Menu</b>", menuToolbar);
	QHBoxLayout* menuToolbarLayout = new QHBoxLayout(menuToolbar);
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
	// Настроим и покажем приложение
	//
	w.setStyleSheet(
		"QToolButton { border: none; min-width: 24px; min-height: 24px; }"
		"QTextEdit { border: none; }"
		"QPushButton[menu=true] { text-align: left; background-color: white; border: none; border-bottom: 1px solid palette(dark); padding: 8px; }"
		"QFrame[menu=true] { background-color: white; border: none; border-right: 1px solid palette(dark); }"
		);
	w.resize(600, 400);
	w.show();

	return a.exec();
}
