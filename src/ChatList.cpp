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

void ChatList::add(const QString& title, unsigned int id) {
	QWidget *chatBoxWidget = new QWidget(scrollContent);
	chatBoxWidget->setMinimumHeight(75);
	chatBoxWidget->setObjectName("chatBoxWidget");
	chatBoxWidget->setStyleSheet(
		"#chatBoxWidget {"
		"	background-color: #181818;"
		"}"
		"#chatBoxWidget:hover {"
			"background-color: #656565;"
		"}"
	);

	QPushButton* invisibleButton = new QPushButton(chatBoxWidget);
	invisibleButton->setMinimumHeight(75);
	invisibleButton->setStyleSheet(
		"QPushButton {"
		"	background: transparent;"
		"	border: none;"
		"}"
		// ":hover {"
			// "background-color: #656565;"
		// "}"
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

void ChatList::deleteById(unsigned int id) {
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

void ChatList::handleClickChatBox(unsigned int id) {
	qDebug() << "Clicked chat with id" << id;
}
