#include "DeleteAccountDialog.h"

DeleteAccountDialog::DeleteAccountDialog(QWidget* parent) : QDialog(parent) {
	QLabel* label = new QLabel("To confirm the deletion of your account,\nenter your username below.");

	line = new QLineEdit(this);
	line->setPlaceholderText("enter username here");

	QPushButton* cancelBtn = new QPushButton("Cancel", this);
	QPushButton* deleteBtn = new QPushButton("Delete", this);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget(cancelBtn);
	hbox->addWidget(deleteBtn);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(label);
	vbox->addWidget(line);
	vbox->addLayout(hbox);

	connect(cancelBtn, &QPushButton::clicked, this, [this]() { reject(); });
	connect(deleteBtn, &QPushButton::clicked, this, [this]() {
		QSettings settings("paket", "QtVocabTrainer");
		if (settings.value("user/username").toString() != line->text().trimmed()) {
			QMessageBox::warning(this, "Error", "The entered username must match the\nusername of the account being deleted");
			return;
		}
		if (line->text().trimmed().isEmpty()) {
			QMessageBox::warning(this, "Error", "Field cannot be empty");
			return;
		}

		auto res = QMessageBox::question(this, "Deletion confirmation", "Are you sure you want to delete your account?\nThis action cannot be undone.\nAll data linked to this account will also be deleted.");
		if (res == QMessageBox::Yes) {
			emit DeleteAccountRequested();
			reject();
		}
		else reject();
	});
}