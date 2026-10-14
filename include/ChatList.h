#pragma once

#include <vector>
#include <QObject>
#include <QString>

class QScrollArea; 
class QWidget; 
class QVBoxLayout; 
class ChatDataManager; 
class ChatData; 

struct ChatBox {
	QWidget *chatBoxWidget;
	const ChatData *chatData;
};

class ChatBoxSignals : public QObject {
	Q_OBJECT
signals:
	void chatBoxSelected(const size_t id, const QString &name);
};

class ChatList {
public:
	ChatList(QWidget *parentWidget, ChatDataManager *chatDataManager);
	QScrollArea* getWidget() const { return scrollArea; };
	ChatBoxSignals* getSignals() { return &chatBoxSignals; };
	size_t getFocusedChatId() const { return focusedChatId; };
	const QString getNameById(const size_t id);
	void add(const ChatData &chatData);
	void deleteChat(const size_t id);
	void deleteChat() { deleteChat(focusedChatId); }
	void clearAll();
	void filterChatList(const QString &query);
private:
	void updateChatsData();
	void handleClickChatBox(const size_t id);
	
	size_t focusedChatId = 0;
	QWidget *parentWidget;
	QScrollArea *scrollArea;
	QWidget *scrollContent;
	QVBoxLayout *scrollLayout;
	ChatDataManager *chatDataManager;
	std::vector<ChatBox> chats;
	ChatBoxSignals chatBoxSignals;
};