#include <QScrollArea>
#include <QString>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

#include "ChatList.h"

ChatList::ChatList(QWidget *parentWidget) : parentWidget(parentWidget) {
	scrollArea = new QScrollArea(parentWidget);
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	
	scrollContent = new QWidget(scrollArea);
	scrollLayout = new QVBoxLayout(scrollContent);
	
	scrollLayout->setAlignment(Qt::AlignTop);
	scrollLayout->setSpacing(10);
	
	scrollArea->setWidget(scrollContent);
}

void ChatList::add(const QString& title, unsigned int id) {
	QWidget *chatBoxWidget = new QWidget(scrollContent);
	chatBoxWidget->setMinimumHeight(75);
	chatBoxWidget->setStyleSheet("background-color: #181818;");

	QLabel *titleLabel = new QLabel(title, chatBoxWidget);
	titleLabel->setStyleSheet("color: white; font-weight: bold;");
	
	QHBoxLayout *chatBoxLayout = new QHBoxLayout(chatBoxWidget);
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