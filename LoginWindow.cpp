#include "LoginWindow.h"

LoginWindow::LoginWindow(QWidget* parent) : QDialog(parent) {
	QLabel* loginLbl = new QLabel("Login:", this);
	QLabel* passwordLbl = new QLabel("Password:", this);

	QLineEdit* loginLine = new QLineEdit(this);
	loginLine->setPlaceholderText("enter login here:");
	QLineEdit* passwordLine = new QLineEdit(this);
	passwordLine->setPlaceholderText("enter password here:");

	QPushButton* loginBtn = new QPushButton("Log in", this);
	QPushButton* registerBtn = new QPushButton("Registration", this);

	QGridLayout* grid = new QGridLayout(this);
	grid->addWidget(loginLbl, 0, 0);
	grid->addWidget(loginLine, 0, 1);
	grid->addWidget(passwordLbl, 1, 0);
	grid->addWidget(passwordLine, 1, 1);
	grid->addWidget(loginBtn, 2, 0);
	grid->addWidget(registerBtn, 2, 1);

	resize(300, 200);
}