#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent) {
	QPushButton* accountDelBtn = new QPushButton("Delete Account", this);
	accountDelBtn->setStyleSheet("background-color: #e57373; color: white; border: none; padding: 6px;");

	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* pannelVbox = new QVBoxLayout(panel);
	pannelVbox->addStretch();
	pannelVbox->addWidget(accountDelBtn);

	connect(accountDelBtn, &QPushButton::clicked, this, [this]() {
		DeleteAccountDialog dialog;
		connect(&dialog, &DeleteAccountDialog::DeleteAccountRequested, this, [this]() {
			emit DeleteAccountRequested();
		});
		dialog.exec();
	});

	vbox->addWidget(panel);
}