#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>

#include "InputMessage.h"

InputMessage::InputMessage(QWidget *parentWidget) : parentWidget(parentWidget) {
	inputMessageWidget = new QWidget(parentWidget);
	inputMessageWidget->setObjectName("inputMessageWidget");
	inputMessageWidget->setStyleSheet(
		"#inputMessageWidget {"
		"	background-color: #282e33;"
		"}"
	);
	inputMessageWidget->setMinimumHeight(45);
	
	inputMessageWidgetLayout = new QHBoxLayout(inputMessageWidget);
	
	inputMessage = new QLineEdit(inputMessageWidget);
	inputMessage->setPlaceholderText("Write a message...");
	inputMessage->setObjectName("inputMessage");
	inputMessage->setStyleSheet(
		"#inputMessage {"
		"	color: #a0a0a0;"
		"	font-size: 14px;"
		"	background-color: #282e33;"
		"	border: none;"
		"}"
	);
	
	inputMessageWidgetLayout->addWidget(inputMessage);
	inputMessageWidget->setHidden(true);
}