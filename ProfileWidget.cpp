#include "ProfileWidget.h"

ProfileWidget::ProfileWidget(QWidget* parent) : QWidget(parent) {
	QSettings settings("paket", "QtVocabTrainer");
	QLabel* lbl = new QLabel(
		"username: " + settings.value("user/username").toString() + '\n' +
		"id: " + settings.value("user/id").toString() + '\n' +
		"created_at: " + settings.value("user/created_at").toString(),
		this
	);

	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* panelVbox = new QVBoxLayout(panel);
	panelVbox->addWidget(lbl);

	vbox->addWidget(panel);
}