#pragma once
#include <QWidget>
#include <QPainter>

class CircleWidget : public QWidget {
public: 
	CircleWidget(QWidget* parent = nullptr);
	void colorCircle(int circleInd, QColor color);
protected:
	void paintEvent(QPaintEvent* event) override;
private:
	QVector<QColor> circlies;
};