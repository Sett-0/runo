#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <fstream>
#include <sstream>

#include "TopControl.h"

TopControl::TopControl(QWidget *parentWidget) : parentWidget(parentWidget) {
	topControlWidget = new QWidget(parentWidget);
	topControlWidget->setFixedHeight(30);
	topControlWidget->setObjectName("topControlWidget");
	QString topControlWidgetStyle = loadStyleSheet("assets/topControl.qss");
	if (!topControlWidgetStyle.isEmpty()) 
		topControlWidget->setStyleSheet(topControlWidgetStyle);
	
	topControlWidgetLayout = new QHBoxLayout(topControlWidget);
	topControlWidgetLayout->setContentsMargins(10, 0, 0, 0);
	topControlWidgetLayout->setSpacing(0);
	
	windowTitle = new QLabel("Runo", topControlWidget);
	windowTitle->setObjectName("windowTitle");
	windowTitle->setFixedHeight(30);
	topControlWidgetLayout->addWidget(windowTitle);
	
	//topControlWidgetLayout->addStretch();
	
	minimizeWindowButton = new QPushButton("—", topControlWidget);
	maximizeWindowButton = new QPushButton("⬜", topControlWidget);
	closeWindowButton    = new QPushButton("✕", topControlWidget);
	
	minimizeWindowButton->setObjectName("minimizeWindowButton");
	maximizeWindowButton->setObjectName("maximizeWindowButton");
	closeWindowButton   ->setObjectName("closeWindowButton");
	
	minimizeWindowButton->setFixedSize(45, 30);
	maximizeWindowButton->setFixedSize(45, 30);
	closeWindowButton   ->setFixedSize(45, 30);
	
	QObject::connect(minimizeWindowButton, &QPushButton::clicked, topControlWidget, 
		[this]() { emit topControlSignals.minimizeWindow(); });
	QObject::connect(maximizeWindowButton, &QPushButton::clicked, topControlWidget, 
		[this]() { emit topControlSignals.maximizeWindow(); });
	QObject::connect(closeWindowButton, &QPushButton::clicked, topControlWidget, 
		[this]() { emit topControlSignals.closeWindow(); });

	topControlWidgetLayout->addWidget(minimizeWindowButton);
	topControlWidgetLayout->addWidget(maximizeWindowButton);
	topControlWidgetLayout->addWidget(closeWindowButton);
}

QString TopControl::loadStyleSheet(const char *filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		return QString();
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	
	return QString::fromStdString(buffer.str());
}