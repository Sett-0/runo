#pragma once 

#include <vector>
#include <QString>

struct ChatData {
	size_t id;
	QString name;
	QString iconPath;
	std::vector<QString> messages;
};

class ChatDataManager {
public:
	ChatDataManager();
	std::vector<ChatData>& getChatsData() { return chatsData; }
	ChatData* getChatData(const size_t id);
	std::vector<QString>* getChatMessages(const size_t id);
	void deleteById(const size_t id);
	void clearAll() { chatsData.clear(); }
private:
	void add(const ChatData &chatData);
	std::vector<ChatData> chatsData;
};