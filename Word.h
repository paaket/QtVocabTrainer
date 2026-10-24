#pragma once
#include <QString>
#include <QDateTime>

struct Word {
	int id;
	int packId;
	QString english;
	QString translation;
	QDateTime created_at;
};