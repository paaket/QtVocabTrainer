#include "RegistrationWindow.h"

RegistrationWindow::RegistrationWindow(DatabaseManager& dbManager, QWidget* parent) : QDialog(parent), dbManager(dbManager) {
	QLabel* loginLbl = new QLabel("Login:", this);
	QLabel* passwordLbl = new QLabel("Password:", this);
	QLabel* repPasswordLbl = new QLabel("Repeat password:", this);
	QLabel* hidePasswordLbl = new QLabel("Hide password:", this);

	loginLine = new QLineEdit(this);
	loginLine->setPlaceholderText("enter login here:");
	passwordLine = new QLineEdit(this);
	passwordLine->setPlaceholderText("enter password here:");
	repPasswordLine = new QLineEdit(this);
	repPasswordLine->setPlaceholderText("enter password here:");
	QCheckBox* checkBox = new QCheckBox(this);

	QPushButton* registerBtn = new QPushButton("Register", this);
	QPushButton* cancelBtn = new QPushButton("Cancel", this);

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(loginLbl, 0, 0);
	grid->addWidget(loginLine, 0, 1);
	grid->addWidget(passwordLbl, 1, 0);
	grid->addWidget(passwordLine, 1, 1);
	grid->addWidget(repPasswordLbl, 2, 0);
	grid->addWidget(repPasswordLine, 2, 1);
	grid->addWidget(hidePasswordLbl, 3, 0);
	grid->addWidget(checkBox, 3, 1);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget(registerBtn);
	hbox->addWidget(cancelBtn);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addLayout(grid);
	vbox->addLayout(hbox);

	connect(checkBox, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state) {
		if (state == Qt::Checked) repPasswordLine->setEchoMode(QLineEdit::Password);
		else repPasswordLine->setEchoMode(QLineEdit::Normal);
	});
	connect(cancelBtn, &QPushButton::clicked, this, [this]() { reject(); });
	connect(registerBtn, &QPushButton::clicked, this, [this]() {
		QString username = loginLine->text().trimmed();
		QString password = passwordLine->text().trimmed();
		QString repPassword = repPasswordLine->text().trimmed();
		if (username.isEmpty() or password.isEmpty()) {
			QMessageBox::warning(this, "Error", "Fill in all the fields");
			return;
		}
		if (password != repPassword) {
			QMessageBox::warning(this, "Error", "Passwords must match");
			return;
		}
		if (password.size() < 9) {
			QMessageBox::warning(this, "Error", "The password cannot be shorter than 9 characters");
			return;
		}

		auto res = this->dbManager.registerUser(username, password);
		if (!res.isSuccess) {
			QMessageBox::critical(this, "Critical error", res.error);
			return;
		}
		accept();
	});

	checkBox->setCheckState(Qt::Checked);
	resize(300, 200);
}