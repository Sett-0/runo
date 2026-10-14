#include <QDebug>
#include <QPainter>
#include <QPaintEvent>

#include "ChatWindowScrollArea.h"
#include "Utils.h"

ChatWindowScrollArea::ChatWindowScrollArea(QWidget* parentWidget) : QScrollArea(parentWidget) {
	const char *bgImagePath = "assets/bg_forest.jpg";
	if (!backgroundPixmap.load(bgImagePath)) {
		qDebug() << "Failed to load chat window's background image from" << bgImagePath;
	}
	
	this->setWidgetResizable(true);
	this->setFrameShape(QFrame::NoFrame);
	
	QString style = Utils::loadStyleSheet("assets/scrollArea.qss");
	if (!style.isEmpty()) this->setStyleSheet(style);
}

void ChatWindowScrollArea::paintEvent(QPaintEvent *event) {
	QPainter painter(this->viewport());
	
	if (backgroundPixmap.isNull()) {
		painter.fillRect(this->viewport()->rect(), QColor("#3d444b"));
		return;
	}
	
	QPixmap scaledBgPixmap = backgroundPixmap.scaled(
		this->viewport()->size(),
		Qt::KeepAspectRatioByExpanding,
		Qt::SmoothTransformation
	);
	
	int xOffset = (scaledBgPixmap.width()  - this->viewport()->width())  / 2;
	int yOffset = (scaledBgPixmap.height() - this->viewport()->height()) / 2;
	
	painter.drawPixmap(-xOffset, -yOffset, scaledBgPixmap);
	QScrollArea::paintEvent(event);
}