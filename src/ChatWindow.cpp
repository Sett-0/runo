#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QLabel>

#include "ChatWindow.h"

ChatWindowWidget::ChatWindowWidget(QWidget* parentWidget) : QWidget(parentWidget) {
	const char *bgImagePath = "assets/bg_forest.jpg";
	if (!backgroundPixmap.load(bgImagePath)) {
		qDebug() << "Failed to load chat window's background image from" << bgImagePath;
	}
}

void ChatWindowWidget::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	
	if (backgroundPixmap.isNull()) {
		painter.fillRect(rect(), QColor("#3d444b"));
		return;
	}
	
	QPixmap scaledBgPixmap = backgroundPixmap.scaled(
		this->size(),
		Qt::KeepAspectRatioByExpanding,
		Qt::SmoothTransformation
	);
	
	int xOffset = (scaledBgPixmap.width()  - this->width())  / 2;
	int yOffset = (scaledBgPixmap.height() - this->height()) / 2;
	
	painter.drawPixmap(-xOffset, -yOffset, scaledBgPixmap);
	QWidget::paintEvent(event);
}

ChatWindow::ChatWindow(QWidget *parentWidget) : parentWidget(parentWidget) {
	chatWindowWidget = new ChatWindowWidget(parentWidget);
	chatWindowWidget->setObjectName("chatWindowWidget");
	
	chatWindowWidgetLayout = new QVBoxLayout(chatWindowWidget);
	
	placeholderLabel = new QLabel("Select a chat to start messaging", chatWindowWidget);
	placeholderLabel->setObjectName("placeholderLabel");
	placeholderLabel->setStyleSheet(
		"#placeholderLabel {"
		"	color: #e9e9e9;"
		"	font-size: 14px;"
		"	border-radius: 14px;"
		"	background-color: #bf3a4047;"
		"	padding: 5px;"
		"}"
	);
	
	chatWindowWidgetLayout->addWidget(placeholderLabel, Qt::AlignCenter, Qt::AlignCenter);
}