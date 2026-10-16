#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtVocabTrainer.h"

class QtVocabTrainer : public QMainWindow
{
    Q_OBJECT

public:
    QtVocabTrainer(QWidget *parent = nullptr);
    ~QtVocabTrainer();

private:
    Ui::QtVocabTrainerClass ui;
};
