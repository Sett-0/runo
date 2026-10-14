#pragma once 

#include <QPixmap>
#include <QScrollArea>

class QWidget;
class QPaintEvent;

class ChatWindowScrollArea : public QScrollArea {
	Q_OBJECT 
public:
	ChatWindowScrollArea(QWidget *parentWidget);
protected:
	void paintEvent(QPaintEvent *event) override;
private:
	QPixmap backgroundPixmap;
};