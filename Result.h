#pragma once
#include <QString>
#include <QVariant>

struct Result {
	bool isSuccess = false;
	QString error;
	QVariant data;
};