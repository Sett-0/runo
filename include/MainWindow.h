#pragma once

#include <QMainWindow> 

class QLineEdit;
class ChatList;
class ChatWindowHeader;
class QLabel;
class QListWidget;

class MainWindow : public QMainWindow {
public:
	MainWindow();
private:
	// void handleAddTask();
	// void handleFilterText(const QString &pattern);
	// void handleDeleteSelected();
	// void handleClearAll();
	// void updateStatusCount();
	
	QLineEdit *searchBar;
	ChatList *chatList;
	ChatWindowHeader *chatWindowHeader;
	QListWidget *messages;
	QLineEdit *inputMessage;
};