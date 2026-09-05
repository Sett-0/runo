#pragma once

#include <QMainWindow> 

class SearchBar;
class ChatDataManager;
class ChatList;
class ChatWindowHeader;
class QLabel;
class QListWidget;
class QLineEdit;

class MainWindow : public QMainWindow {
public:
	MainWindow();
private:
	SearchBar *searchBar;
	ChatDataManager *chatDataManager;
	ChatList *chatList;
	ChatWindowHeader *chatWindowHeader;
	QListWidget *messages;
	QLineEdit *inputMessage;
};