#include <QWidget>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "ChatWindowHeader.h"

ChatWindowHeader::ChatWindowHeader(QWidget* parentWidget) : parentWidget(parentWidget) {
	headerWidget = new QWidget(parentWidget);
	headerWidget->setMinimumHeight(55);
	headerWidget->setObjectName("headerWidget");
	headerWidget->setStyleSheet(
		"#headerWidget {"
		"	background-color: #282E33;"
		"}"
	);

	headerWidgetLayout = new QHBoxLayout(headerWidget);
	headerWidgetLayout->setContentsMargins(10, 5, 10, 5);
	
	chatInfoLayout = new QVBoxLayout();
	chatInfoLayout->setContentsMargins(0, 0, 0, 0);
	chatInfoLayout->setSpacing(0);
	
	headerWidgetLayout->addLayout(chatInfoLayout);
	
	name = new QLabel("#Name", headerWidget);
	name->setStyleSheet(
		"QLabel {"
		"	color: #E9E9E9;"
		"	font-size: 14px;"
		"	font-weight: bold;"
		"}"
	);
	chatInfoLayout->addWidget(name);
	
	status = new QLabel("#Status", headerWidget);
	status->setObjectName("status");
	status->setStyleSheet(
		"#status {"
		"	color: #B29EE9;"
		"	font-size: 14px;"
		"}"
	);
	chatInfoLayout->addWidget(status);
	
	
	deleteChat = new QPushButton("Delete chat", headerWidget);
	deleteChat->setStyleSheet(
		"background-color: #E90000;"
		"border: 1px solid #E9E9E9;"
		"border-radius: 6px;"
		"font-size: 14px;"
		"font-weight: bold;"
		"color: white;"
	);
	deleteChat->setMinimumSize(100, 35);
	headerWidgetLayout->addWidget(deleteChat, 0, Qt::AlignRight);
	QObject::connect(deleteChat, &QPushButton::clicked, headerWidget, [this]() { handleDeleteChat(); });
	
	headerWidget->setHidden(true);
};

void ChatWindowHeader::updateChatInfo(const QString &name) {
	headerWidget->setHidden(false);
	this->name->setText(name);
	this->status->setText("online");
}

void ChatWindowHeader::handleDeleteChat() {
	int answer = QMessageBox::question(
		headerWidget,
		"Delete chat",
		QString(
			"Are you sure you want to delete all message history with %1?"
			"\n\n"
			"This action cannot be undone."
		).arg(name->text()),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No
	);
	
	if (answer == QMessageBox::Yes) {
		headerWidget->setHidden(true);
		emit chatWindowHeaderSignals.deleteChatPressed();
	}
}