#include "CircleWidget.h"

CircleWidget::CircleWidget(QWidget* parent) : QWidget(parent) {
	for (int i = 0; i < 10; ++i)
		circlies.append(Qt::lightGray);

	setMinimumSize(400, 30);
}

void CircleWidget::paintEvent(QPaintEvent* event) {
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(Qt::gray, 1));

	double cellWidth = static_cast<double>(width()) / circlies.size();
	double cellHeight = height();

	double diameter = qMin(cellWidth, cellHeight) * 0.8;
	double radius = diameter / 2.0;

	for (int i = 0; i < circlies.size(); ++i) {
		double centerX = (i * cellWidth) + (cellWidth / 2.0);
		double centerY = cellHeight / 2.0;

		painter.setBrush(circlies[i]);
		painter.drawEllipse(QPointF(centerX, centerY), radius, radius);
	}
}

void CircleWidget::colorCircle(int circleInd, QColor color) {
	circlies[circleInd] = color;
	update();
}