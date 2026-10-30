#include "ProfileWidget.h"

ProfileWidget::ProfileWidget(QWidget* parent) : QWidget(parent) {
	QSettings settings("paket", "QtVocabTrainer");
	QLabel* lbl = new QLabel(
		"username: " + settings.value("user/username").toString() + '\n' +
		"id: " + settings.value("user/id").toString() + '\n' +
		"created_at: " + settings.value("user/created_at").toDateTime().toString("dd.MM.yyyy HH:mm:ss"),
		this
	);

	QPushButton* logoutBtn = new QPushButton("Log out", this);

	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* panelVbox = new QVBoxLayout(panel);
	panelVbox->addWidget(lbl);
	panelVbox->addStretch();
	panelVbox->addWidget(logoutBtn);

	connect(logoutBtn, &QPushButton::clicked, this, &ProfileWidget::LogoutRequested);

	vbox->addWidget(panel);
}