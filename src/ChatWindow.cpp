#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

#include "ChatDataManager.h"
#include "ChatWindowScrollArea.h"
#include "ChatWindow.h"

ChatWindow::ChatWindow(QWidget *parentWidget, ChatDataManager *chatDataManager) : parentWidget(parentWidget), chatDataManager(chatDataManager) {
	chatWindowScrollArea = new ChatWindowScrollArea(parentWidget);
	chatWindowScrollArea->setObjectName("chatWindowScrollArea");
	
	chatWindowPlaceholder = new QWidget(chatWindowScrollArea);
	chatWindowPlaceholder->setObjectName("chatWindowPlaceholder");
	chatWindowPlaceholder->setStyleSheet(
		"#chatWindowPlaceholder {"
		"	border: none;"
		"	background: transparent;"
		"}"
	);
	chatWindowScrollArea->setWidget(chatWindowPlaceholder);
	
	placeholderLabel = new QLabel("Select a chat to start messaging", chatWindowScrollArea);
	placeholderLabel->setObjectName("placeholderLabel");
	placeholderLabel->setStyleSheet(
		"#placeholderLabel {"
		"	color: #e9e9e9;"
		"	font-size: 14px;"
		"	border-radius: 14px;"
		"	background-color: #bf3a4047;"
		"	padding: 5px;"
		"}"
	);
	
	chatWindowPlaceholderLayout = new QVBoxLayout(chatWindowPlaceholder);
	chatWindowPlaceholderLayout->addWidget(placeholderLabel, Qt::AlignCenter, Qt::AlignCenter);
	
	chatWindowScrollContent = new QWidget(chatWindowScrollArea);
	chatWindowScrollContent->setObjectName("chatWindowScrollContent");
	chatWindowScrollContent->setStyleSheet(
		"#chatWindowScrollContent {"
		"	border: none;"
		"	background: transparent;"
		"}"
	);
	chatWindowScrollContent->setHidden(true);

	chatWindowScrollContentLayout = new QVBoxLayout(chatWindowScrollContent);
	chatWindowScrollContentLayout->setContentsMargins(10, 10, 10, 10);
	chatWindowScrollContentLayout->setSpacing(10);
}

void ChatWindow::showChat(const size_t id) {
	if (chatId == 0) {
		chatWindowPlaceholder = chatWindowScrollArea->takeWidget();
		chatWindowPlaceholder->setParent(chatWindowScrollArea);
		chatWindowPlaceholder->setHidden(true);
		chatWindowScrollArea->setWidget(chatWindowScrollContent);
		chatWindowScrollContent->setHidden(false);
	} else {
		clearMessages();
	}
	
	chatId = id;
	if (auto *messages = chatDataManager->getChatMessages(chatId)) {
		for (const QString &message : *messages) addMessage(message);
	} else {
		qDebug() << "ERROR: Failed to get the chat's messages! chatDataManager->getChatMessages(chatId) returned nullptr.";
	}
}

void ChatWindow::addMessage(const QString &message) {
	QLabel *messageLabel = new QLabel(message, chatWindowScrollContent);
	messageLabel->setObjectName("messageLabel");
	messageLabel->setStyleSheet(
		"#messageLabel {"
		"	color: #e9e9e9;"
		"	font-size: 14px;"
		"	border-radius: 14px;"
		"	background-color: #bf3a4047;"
		"	padding: 5px;"
		"}"
	);
	chatWindowScrollContentLayout->addWidget(messageLabel);
	messages.push_back(messageLabel);
}

void ChatWindow::handleDeleteChat() {
	chatId = 0;
	clearMessages();
	
	chatWindowScrollContent = chatWindowScrollArea->takeWidget();
	chatWindowScrollContent->setParent(chatWindowScrollArea);
	chatWindowScrollContent->setHidden(true);	
	chatWindowScrollArea->setWidget(chatWindowPlaceholder);
	chatWindowPlaceholder->setHidden(false);
}

void ChatWindow::clearMessages() {
	for (QLabel *message: messages) {
		delete message;
	}
	messages.clear();
}
