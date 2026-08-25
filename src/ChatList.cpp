#include <QScrollArea>
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
	scrollArea->setStyleSheet(
		"QScrollArea {"
		"	background-color: #282E33;"
		"}"
		
		// The vertical track
		"QScrollBar:vertical {"
		"    border: none;"
		"    background: #3B4145;"
		"    width: 4px;"
		"    margin: 0px 0px 0px 0px;"
		"    border-radius: 2px;"
		"}"

		// The slider handle
		"QScrollBar::handle:vertical {"
		"    background: #73777A;"
		"    min-height: 30px;"
		"    border-radius: 2px;"
		"}"
		"QScrollBar::handle:vertical:hover {"
		"    background: #A2A5A7;"
		"}"
		"QScrollBar::handle:vertical:pressed {"
		"    background: #A2A5A7;"
		"}"

		// The arrow buttons
		"QScrollBar::sub-line:vertical,"
		"QScrollBar::add-line:vertical {"
		"    border: none;"
		"    background: none;"
		"    height: 0px;" 
		"}"
		"QScrollBar::up-arrow:vertical,"
		"QScrollBar::down-arrow:vertical {"
		"    border: none;"
		"    background: none;"
		"}"

		// The track extensions
		"QScrollBar::add-page:vertical,"
		"QScrollBar::sub-page:vertical {"
		"    background: none;"
		"}"
	);
	
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
}

void ChatList::add(const QString& title, size_t id) {
	QWidget *chatBoxWidget = new QWidget(scrollContent);
	chatBoxWidget->setMinimumHeight(65);
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
	invisibleButton->setMinimumHeight(65);
	invisibleButton->setStyleSheet(
		"QPushButton {"
		"	background: transparent;"
		"	border: none;"
		"}"
	);
	
	QObject::connect(invisibleButton, &QPushButton::clicked, scrollArea, 
		[this, id, title]() { 
			// "this->" in this case is "this" we captured with lambda. Can also skip writing it.
			this->handleClickChatBox(id); 
			emit chatBoxSignals.chatBoxSelected(title);
		} 
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
	
	ChatBox chatBox = { .chatBoxWidget = chatBoxWidget, .id = id, .name = title };
	chats.push_back(chatBox);
}

void ChatList::deleteById(size_t id) {
	for (size_t i = 0; i < chats.size(); i++) {
		if (chats[i].id == id) {
			delete chats[i].chatBoxWidget;
			chats.erase(chats.begin() + i);
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
}

QString ChatList::getNameById(size_t id) const {
	for (const auto &chat : chats) {
		if (chat.id == id) {
			return chat.name;
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
		if (!chat.name.contains(query.trimmed(), Qt::CaseInsensitive)) {
			chat.chatBoxWidget->setHidden(true);
		}
	}
}
