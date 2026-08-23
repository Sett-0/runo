#include <QScrollArea>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

#include "ChatList.h"

ChatList::ChatList(QWidget *parentWidget) : parentWidget(parentWidget) {
	scrollArea = new QScrollArea(parentWidget);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	
	scrollContent = new QWidget(scrollArea);
	scrollLayout = new QVBoxLayout(scrollContent);
	
	scrollLayout->setAlignment(Qt::AlignTop);
	scrollLayout->setSpacing(0);
	
	scrollArea->setWidget(scrollContent);
}

void ChatList::add(const QString& title, size_t id) {
	QWidget *chatBoxWidget = new QWidget(scrollContent);
	chatBoxWidget->setMinimumHeight(75);
	chatBoxWidget->setObjectName("chatBoxWidget");
	chatBoxWidget->setStyleSheet(
		"#chatBoxWidget {"
		"	background-color: #282E33;"
		"}"
		"#chatBoxWidget:hover {"
			"background-color: #353C43;"
		"}"
	);

	QPushButton* invisibleButton = new QPushButton(chatBoxWidget);
	invisibleButton->setMinimumHeight(75);
	invisibleButton->setStyleSheet(
		"QPushButton {"
		"	background: transparent;"
		"	border: none;"
		"}"
	);
	
	QObject::connect(invisibleButton, &QPushButton::clicked, parentWidget, 
		[this, id]() { this->handleClickChatBox(id); } // "this->" in this case is "this" we captured with lambda. Can also skip writing it.
	);
	
	QVBoxLayout *invisibleButtonLayout = new QVBoxLayout(chatBoxWidget);
	invisibleButtonLayout->setContentsMargins(0, 0, 0, 0);
	invisibleButtonLayout->addWidget(invisibleButton);

	QLabel *titleLabel = new QLabel(title, chatBoxWidget);
	titleLabel->setStyleSheet(
		"QLabel {"
		"	color: white;"
		"	font-weight: bold;"
		"}"
	);
	
	QHBoxLayout *chatBoxLayout = new QHBoxLayout(invisibleButton);
	chatBoxLayout->addWidget(titleLabel);
	
	scrollLayout->addWidget(chatBoxWidget);
	
	ChatBox chatBox = { .chatBoxWidget = chatBoxWidget, .id = id };
	chats.push_back(chatBox);
}

void ChatList::deleteById(size_t id) {
	for (size_t i = 0; i < chats.size(); i++) {
		if (chats[i].id == id) {
			delete chats[i].chatBoxWidget;
			chats.erase(chats.begin() + i);
			return;
		}
	}
}

void ChatList::clearAll() {
	for (auto &chat : chats) {
		delete chat.chatBoxWidget;
	}
	chats.clear();
}

void ChatList::handleClickChatBox(size_t id) {
	// Reset previous chat box styles
	if (focusedChatId) {
		if (id == focusedChatId) {
			return;
		}
		for (auto &chat : chats) {
			if (chat.id == focusedChatId) {
				chat.chatBoxWidget->setStyleSheet(
					"#chatBoxWidget {"
					"	background-color: #282E33;"
					"}"
					"#chatBoxWidget:hover {"
						"background-color: #353C43;"
					"}"
				);
				break;
			}
		}
	}
	// Visually focus selected chat box
	for (auto &chat : chats) {
		if (chat.id == id) {
			chat.chatBoxWidget->setStyleSheet(
				"#chatBoxWidget {"
				"	background-color: #7154A3;"
				"}"
			);
			focusedChatId = id;
			break;
		}
	}
	qDebug() << "Clicked chat with id" << id;
}
