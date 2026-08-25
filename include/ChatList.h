#pragma once

#include <vector>
#include <QObject>
#include <QString>

class QScrollArea; 
class QWidget; 
class QVBoxLayout; 

struct ChatBox {
	QWidget* chatBoxWidget;
	size_t id;
	QString name;
};

class ChatBoxSignals : public QObject {
	Q_OBJECT
signals:
	void chatBoxSelected(const QString& name);
};

class ChatList {
public:
	ChatList(QWidget *parentWidget);
	QScrollArea* getWidget() const { return scrollArea; };
	ChatBoxSignals* getSignals() { return &chatBoxSignals; };
	size_t getFocusedChatId() const { return focusedChatId; };
	QString getNameById(size_t id) const;
	void add(const QString& title, size_t id);
	void deleteById(size_t id);
	void clearAll();
	void filterChatList(const QString &query);
private:
	void handleClickChatBox(size_t id);
	
	size_t focusedChatId = 0;
	QWidget *parentWidget;
	QScrollArea *scrollArea;
	QWidget *scrollContent;
	QVBoxLayout *scrollLayout;
	// TODO: Factor out the chats' data into a separate class ChatDataManager
	std::vector<ChatBox> chats;
	ChatBoxSignals chatBoxSignals;
};