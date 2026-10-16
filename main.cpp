#include "QtVocabTrainer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtVocabTrainer w;
    w.show();
    return a.exec();
}
