#include <QString>

#include <QDebug>

#include "ChatDataManager.h"

ChatDataManager::ChatDataManager() {
	for (size_t i = 1; i <= 15; i++) {
		size_t id = i + 100;
		QString name = QString("Friend %1").arg(i);
		ChatData chatData = { id, name };
		add(chatData);
	}
}

void ChatDataManager::add(const ChatData &chatData) {
	chatsData.push_back(chatData);
}

ChatData* ChatDataManager::getChatData(const size_t id) {
	for (auto &chatData : chatsData) {
		if (chatData.id == id) return &chatData;
	}
	return nullptr;
}

void ChatDataManager::deleteById(const size_t id) {
	for (size_t i = 0; i < chatsData.size(); i++) {
		if (chatsData[i].id == id) {
			chatsData.erase(chatsData.begin() + i);
			return;
		}
	}
}