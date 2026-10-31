#include "AddWordDialog.h"

AddWordDialog::AddWordDialog(int packId, QWidget* parent) : QDialog(parent), packId(packId) {
	setWindowTitle("Add a word");

	QLabel* wordLbl = new QLabel("English word:", this);

	wordLine = new QLineEdit(this);
	wordLine->setPlaceholderText("enter word here");

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(wordLbl, 0, 0);
	grid->addWidget(wordLine, 0, 1);

	QPushButton* addBtn = new QPushButton("Add", this);
	QPushButton* cnclBtn = new QPushButton("Cancel", this);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget(addBtn);
	hbox->addWidget(cnclBtn);
	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addLayout(grid);
	vbox->addLayout(hbox);

	connect(cnclBtn, &QPushButton::clicked, this, [this]() { reject(); });
	connect(addBtn, &QPushButton::clicked, this, [packId, this]() {
			const QString word = wordLine->text().trimmed();
			if (word.isEmpty()) {
				QMessageBox::warning(this, "Error", "Fill in the fields");
				return;
			}
			emit wordSubmitted(packId, word);
			accept();
		}
	);
}