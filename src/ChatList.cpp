#include <QString>
#include <QScrollArea>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <sstream>
#include <fstream>

#include "ChatList.h"
#include "ChatDataManager.h"
#include "Utils.h"

ChatList::ChatList(QWidget *parentWidget, ChatDataManager *chatDataManager) : parentWidget(parentWidget), chatDataManager(chatDataManager) {
	scrollArea = new QScrollArea(parentWidget);
	
	scrollArea->setWidgetResizable(true);
	scrollArea->setFrameShape(QFrame::NoFrame);
	QString scrollAreaStyle = loadStyleSheet("assets/scrollArea.qss");
	if (!scrollAreaStyle.isEmpty()) 
		scrollArea->setStyleSheet(scrollAreaStyle);
	
	scrollContent = new QWidget(scrollArea);
	scrollContent->setObjectName("scrollContent");
	scrollContent->setStyleSheet(
		"#scrollContent {"
		"	background-color: #282E33;"
		"}"
	);

	scrollLayout = new QVBoxLayout(scrollContent);
	scrollLayout->setAlignment(Qt::AlignTop);
	scrollLayout->setContentsMargins(0, 0, 0, 0);
	scrollLayout->setSpacing(0);
	
	scrollArea->setWidget(scrollContent);
	
	for (const auto &chatData : chatDataManager->getChatData()) add(chatData);
}

void ChatList::add(const ChatData &chatData) {
	QWidget *chatBoxWidget = new QWidget(scrollContent);
	chatBoxWidget->setMinimumHeight(Utils::noSystemDisplayScale(77));
	chatBoxWidget->setObjectName("chatBoxWidget");
	chatBoxWidget->setStyleSheet(
		"#chatBoxWidget {"
		"	background-color: #282E33;"
		"}"
		"#chatBoxWidget:hover {"
			"background-color: #353C43;"
		"}"
	);

	QPushButton *invisibleButton = new QPushButton(chatBoxWidget);
	invisibleButton->setMinimumHeight(Utils::noSystemDisplayScale(77));
	invisibleButton->setStyleSheet(
		"QPushButton {"
		"	background: transparent;"
		"	border: none;"
		"}"
	);
	
	QObject::connect(invisibleButton, &QPushButton::clicked, chatBoxWidget, 
		[this, id = chatData.id, name = chatData.name]() { 
			handleClickChatBox(id); 
			emit chatBoxSignals.chatBoxSelected(name);
		} 
	);
	
	QVBoxLayout *invisibleButtonLayout = new QVBoxLayout(chatBoxWidget);
	invisibleButtonLayout->setContentsMargins(0, 0, 0, 0);
	invisibleButtonLayout->addWidget(invisibleButton);

	QLabel *titleLabel = new QLabel(chatData.name, chatBoxWidget);
	titleLabel->setStyleSheet(
		"QLabel {"
		"	color: white;"
		"	font-weight: bold;"
		"}"
	);
	
	QHBoxLayout *chatBoxLayout = new QHBoxLayout(invisibleButton);
	chatBoxLayout->addWidget(titleLabel);
	
	scrollLayout->addWidget(chatBoxWidget);
	
	ChatBox chatBox = { .chatBoxWidget = chatBoxWidget, .chatData = &chatData };
	chats.push_back(chatBox);
}

void ChatList::deleteById(const size_t id) {
	for (size_t i = 0; i < chats.size(); i++) {
		if (chats[i].chatData->id == id) {
			delete chats[i].chatBoxWidget;
			chats.erase(chats.begin() + i);
			
			chatDataManager->deleteById(id);
			updateChatsData();
			
			focusedChatId = 0;
			return;
		}
	}
}

void ChatList::clearAll() {
	for (auto &chat : chats) {
		delete chat.chatBoxWidget;
	}
	chats.clear();
	chatDataManager->clearAll();
	updateChatsData();
}

// TODO: This is a relational mess. Storing a part of one vector inside another leads to 
// the need to repopulate the chatBox's vector every time we modify the chatData. 
// The data is stored by reference, but it is still taking the time to update the pointers. 
// Maybe refactor this system to something better instead?
void ChatList::updateChatsData() {
	auto &chatsData = chatDataManager->getChatData();
	for (size_t i = 0; i < chatsData.size(); i++) {
		chats[i].chatData = &chatsData[i];
	}
}

void ChatList::handleClickChatBox(const size_t id) {
	// Reset previous chat box styles
	if (focusedChatId) {
		if (id == focusedChatId) {
			return;
		}
		for (auto &chat : chats) {
			if (chat.chatData->id == focusedChatId) {
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
		if (chat.chatData->id == id) {
			chat.chatBoxWidget->setStyleSheet(
				"#chatBoxWidget {"
				"	background-color: #7154A3;"
				"}"
			);
			focusedChatId = id;
			break;
		}
	}
}

QString ChatList::getNameById(const size_t id) {
	for (const auto &chat : chats) {
		if (chat.chatData->id == id) {
			return chat.chatData->name;
		}
	}
	return "";
}

void ChatList::filterChatList(const QString &query) {
	if (query.isEmpty()) {
		for (auto &chat : chats) {
			chat.chatBoxWidget->setHidden(false);
		}
		return;
	}

	for (auto &chat : chats) {
		if (!chat.chatData->name.contains(query.trimmed(), Qt::CaseInsensitive)) {
			chat.chatBoxWidget->setHidden(true);
		}
	}
}

QString ChatList::loadStyleSheet(const char *filePath) {
	std::ifstream file(filePath);
	if (!file.is_open()) {
		return QString();
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	
	return QString::fromStdString(buffer.str());
}

