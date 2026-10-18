#include "HomeWidget.h"

HomeWidget::HomeWidget(QWidget* parent) : QWidget(parent) {
	QLabel* label = new QLabel("Home Widget", this);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addWidget(label);
}