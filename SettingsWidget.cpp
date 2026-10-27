#include "SettingsWidget.h"

SettingsWidget::SettingsWidget(QWidget* parent) : QWidget(parent) {
	QPushButton* logoutBtn = new QPushButton("Log out", this);

	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* pannelVbox = new QVBoxLayout(panel);
	pannelVbox->addStretch();
	pannelVbox->addWidget(logoutBtn);

	connect(logoutBtn, &QPushButton::clicked, this, &SettingsWidget::LogoutRequested);

	vbox->addWidget(panel);
}