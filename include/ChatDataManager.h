#pragma once 

#include <vector>

class QString;

struct ChatData {
	size_t id;
	QString name;
};

class ChatDataManager {
public:
	ChatDataManager();
	std::vector<ChatData>& getChatData() { return chatsData; }
	ChatData* getChatData(const size_t id);
	void deleteById(const size_t id);
	void clearAll() { chatsData.clear(); }
private:
	void add(const ChatData &chatData);
	std::vector<ChatData> chatsData;
};