#include "LoginWindow.h"

LoginWindow::LoginWindow(DatabaseManager& dbManager, QWidget* parent) : QDialog(parent), dbManager(dbManager) {
	QLabel* loginLbl = new QLabel("Login:", this);
	QLabel* passwordLbl = new QLabel("Password:", this);
	QLabel* hidePasswordLbl = new QLabel("Hide password:", this);
	QLabel* rememberLbl = new QLabel("Remember me:", this);

	loginLine = new QLineEdit(this);
	loginLine->setPlaceholderText("enter login here:");
	passwordLine = new QLineEdit(this);
	passwordLine->setPlaceholderText("enter password here:");

	QPushButton* loginBtn = new QPushButton("Log in", this);
	QPushButton* registerBtn = new QPushButton("Registration", this);

	QCheckBox* hidePasswordChk = new QCheckBox(this);
	QCheckBox* rememberChk = new QCheckBox(this);

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(loginLbl, 0, 0);
	grid->addWidget(loginLine, 0, 1);
	grid->addWidget(passwordLbl, 1, 0);
	grid->addWidget(passwordLine, 1, 1);
	grid->addWidget(hidePasswordLbl, 2, 0);
	grid->addWidget(hidePasswordChk, 2, 1);
	grid->addWidget(rememberLbl, 3, 0);
	grid->addWidget(rememberChk, 3, 1);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget(loginBtn);
	hbox->addWidget(registerBtn);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addLayout(grid);
	vbox->addLayout(hbox);

	connect(registerBtn, &QPushButton::clicked, this, [this]() {
		RegistrationWindow window(this->dbManager);
		if (window.exec() == QDialog::Accepted)
			QMessageBox::information(this, "Information", "You have successfully registered\nReturn to the login screen and sign in to the account you created.");
	});
	connect(hidePasswordChk, &QCheckBox::checkStateChanged, this, [this](Qt::CheckState state) {
		if (state == Qt::Checked) passwordLine->setEchoMode(QLineEdit::Password);
		else passwordLine->setEchoMode(QLineEdit::Normal);
	});
	connect(loginBtn, &QPushButton::clicked, this, [rememberChk, this]() {
		QString username = loginLine->text().trimmed();
		QString password = passwordLine->text().trimmed();
		if (username.isEmpty() or password.isEmpty()) {
			QMessageBox::warning(this, "Error", "Fill in all the fields");
			return;
		}
		if (password.size() < 9) {
			QMessageBox::warning(this, "Error", "The password cannot be shorter than 9 characters");
			return;
		}
		auto res = this->dbManager.loginUser(username, password);
		if (!res.isSuccess) {
			QMessageBox::warning(this, "Error", res.error);
			return;
		}

		QSettings settings("paket", "QtVocabTrainer");

		if (rememberChk->isChecked()) settings.setValue("auth/remember", true);
		else settings.setValue("auth/remember", false);

		settings.setValue("user/id", res.data.toMap()["id"]);
		settings.setValue("user/username", res.data.toMap()["username"]);
		settings.setValue("user/created_at", res.data.toMap()["created_at"]);

		accept();
	});

	hidePasswordChk->setCheckState(Qt::Checked);
	resize(300, 200);
}