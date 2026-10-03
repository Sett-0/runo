#pragma once 

#include <QWidget>
#include <QPixmap>

class QPixmap;

class ChatWindowWidget : public QWidget {
	Q_OBJECT 
public:
	ChatWindowWidget(QWidget *parentWidget);
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	QPixmap backgroundPixmap;
};

class QVBoxLayout;
class QLabel;

class ChatWindow {
public:
	ChatWindow(QWidget *parentWidget);
	QWidget* getWidget() { return chatWindowWidget; }
private:
	QWidget *parentWidget;
	ChatWindowWidget *chatWindowWidget;
	QVBoxLayout *chatWindowWidgetLayout;
	QLabel *placeholderLabel;
};