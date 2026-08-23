#pragma once

#include <vector>

class QString;
class QScrollArea; 
class QWidget; 
class QVBoxLayout; 

struct ChatBox {
	QWidget* chatBoxWidget;
	unsigned int id;
};

class ChatList {
public:
	ChatList(QWidget *parentWidget);
	QScrollArea* getWidget() const { return scrollArea; };
	void add(const QString& title, unsigned int id);
	void deleteById(unsigned int id);
	void clearAll();
private:
	QWidget *parentWidget;
	QScrollArea *scrollArea;
	QWidget *scrollContent;
	QVBoxLayout *scrollLayout;
	std::vector<ChatBox> chats;
};