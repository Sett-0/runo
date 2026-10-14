#pragma once 

#include <vector>

class QWidget;
class ChatWindowScrollArea;
class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class ChatDataManager;

class ChatWindow {
public:
	ChatWindow(QWidget *parentWidget, ChatDataManager *chatDataManager);
	ChatWindowScrollArea* getWidget() { return chatWindowScrollArea; }
	void showChat(const size_t id);
	void handleDeleteChat();
private:
	void addMessage(const QString &message);
	void clearMessages();

	QWidget *parentWidget;
	size_t chatId = 0;
	ChatWindowScrollArea *chatWindowScrollArea;
	QWidget *chatWindowPlaceholder;
	QVBoxLayout *chatWindowPlaceholderLayout;
	QWidget *chatWindowScrollContent;
	QVBoxLayout *chatWindowScrollContentLayout;
	QLabel *placeholderLabel;
	ChatDataManager *chatDataManager;
	std::vector<QLabel*> messages;
};