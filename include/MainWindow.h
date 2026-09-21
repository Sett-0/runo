#pragma once

#include <QMainWindow> 

class TopControl;
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
protected:
	void mousePressEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void changeEvent(QEvent *event) override;
private:
	QRect normalGeometry;
	QPoint dragPosition;
	TopControl *topControl;
	SearchBar *searchBar;
	ChatDataManager *chatDataManager;
	ChatList *chatList;
	ChatWindowHeader *chatWindowHeader;
	QListWidget *messages;
	QLineEdit *inputMessage;
};