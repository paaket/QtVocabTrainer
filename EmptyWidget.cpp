#include "EmptyWidget.h"

EmptyWidget::EmptyWidget(QWidget* parent) : QWidget(parent) {
	QVBoxLayout* vbox = new QVBoxLayout(this);

	QFrame* panel = new QFrame(this);
	panel->setFrameShape(QFrame::StyledPanel);
	panel->setFrameShadow(QFrame::Sunken);

	QVBoxLayout* panelVbox = new QVBoxLayout(panel);

	vbox->addWidget(panel);
}