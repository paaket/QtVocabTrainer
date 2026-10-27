#include "HomeWidget.h"

HomeWidget::HomeWidget(QWidget* parent) : QWidget(parent) {
	QLabel* label = new QLabel("Home Widget", this);

	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* panelVbox = new QVBoxLayout(panel);
	panelVbox->addWidget(label);

	vbox->addWidget(panel);
}