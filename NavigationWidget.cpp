#include "NavigationWidget.h"

NavigationWidget::NavigationWidget(QWidget* parent) : QWidget(parent) {
	QPushButton* homeBtn = new QPushButton("Home", this);
	QPushButton* packsBtn = new QPushButton("My Packs", this);
	QPushButton* profileBtn = new QPushButton("Profile", this);
	QPushButton* statisticBtn = new QPushButton("Statistic", this);
	QPushButton* settingsBtn = new QPushButton("Settings", this);

	homeBtn->setMinimumSize(btnHeight, btnWidth);
	packsBtn->setMinimumSize(btnHeight, btnWidth);
	profileBtn->setMinimumSize(btnHeight, btnWidth);
	statisticBtn->setMinimumSize(btnHeight, btnWidth);
	settingsBtn->setMinimumSize(btnHeight, btnWidth);

	QVBoxLayout* btnVBox = new QVBoxLayout(this);
	btnVBox->addWidget(homeBtn);
	btnVBox->addWidget(packsBtn);
	btnVBox->addWidget(profileBtn);
	btnVBox->addWidget(statisticBtn);
	btnVBox->addWidget(settingsBtn);
	btnVBox->addStretch();

	connect(homeBtn, &QPushButton::clicked, this, &NavigationWidget::homeRequested);
	connect(packsBtn, &QPushButton::clicked, this, &NavigationWidget::packsRequested);
	connect(profileBtn, &QPushButton::clicked, this, &NavigationWidget::profileRequested);
	connect(statisticBtn, &QPushButton::clicked, this, &NavigationWidget::statisticRequested);
	connect(settingsBtn, &QPushButton::clicked, this, &NavigationWidget::settingsRequested);
}