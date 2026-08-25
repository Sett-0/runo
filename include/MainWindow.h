#pragma once

#include <QMainWindow> 

class SearchBar;
class ChatList;
class ChatWindowHeader;
class QLabel;
class QListWidget;
class QLineEdit;

class MainWindow : public QMainWindow {
public:
	MainWindow();
private:
	// void handleAddTask();
	// void handleFilterText(const QString &pattern);
	// void handleDeleteSelected();
	// void handleClearAll();
	// void updateStatusCount();
	
	SearchBar *searchBar;
	ChatList *chatList;
	ChatWindowHeader *chatWindowHeader;
	QListWidget *messages;
	QLineEdit *inputMessage;
};