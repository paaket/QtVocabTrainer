#include "AddPackDialog.h"

AddPackDialog::AddPackDialog(QWidget* parent) : QDialog(parent) {
	setWindowTitle("Add a pack");

	QLabel* titleLbl = new QLabel("Title:", this);

	titleLine = new QLineEdit(this);
	titleLine->setPlaceholderText("enter title here");

	QPushButton* addBtn = new QPushButton("Add", this);
	QPushButton* cancelBtn = new QPushButton("Cancel", this);

	QGridLayout* grid = new QGridLayout();
	grid->addWidget(titleLbl, 0, 0);
	grid->addWidget(titleLine, 0, 1);

	QHBoxLayout* hbox = new QHBoxLayout();
	hbox->addWidget(addBtn);
	hbox->addWidget(cancelBtn);

	QVBoxLayout* vbox = new QVBoxLayout(this);
	vbox->addLayout(grid);
	vbox->addLayout(hbox);

	connect(cancelBtn, &QPushButton::clicked, this, [this]() { reject(); });
	connect(addBtn, &QPushButton::clicked, this, [this]() {
		const QString title = titleLine->text().trimmed();
		if (title.isEmpty()) {
			QMessageBox::warning(this, "Error", "Fill in the fields");
			return;
		}
		emit packSubmitted(title);
		accept();
	});
}