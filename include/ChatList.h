#pragma once

#include <vector>

class QString;
class QScrollArea; 
class QWidget; 
class QVBoxLayout; 

struct ChatBox {
	QWidget* chatBoxWidget;
	size_t id;
};

class ChatList {
public:
	ChatList(QWidget *parentWidget);
	QScrollArea* getWidget() const { return scrollArea; };
	void add(const QString& title, size_t id);
	void deleteById(size_t id);
	void clearAll();
private:
	void handleClickChatBox(size_t id);
	
	size_t focusedChatId = 0;
	QWidget *parentWidget;
	QScrollArea *scrollArea;
	QWidget *scrollContent;
	QVBoxLayout *scrollLayout;
	std::vector<ChatBox> chats;
};