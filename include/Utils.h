#pragma once 

#include <cmath>
#include <QGuiApplication>
#include <QScreen>
#include <QString>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QPainter>
#include <QLabel>
#include <QDebug>

namespace Utils {
	inline int noSystemDisplayScale(double pixels) {
		double systemDisplayScaleFactor = QGuiApplication::primaryScreen()->devicePixelRatio();
		return std::round(pixels / systemDisplayScaleFactor);
	}
	
	inline bool fileExists(const QString &filePath) {
		return QFileInfo::exists(filePath);
	}

	inline QString loadStyleSheet(const QString &filePath) {
		QFile file(filePath);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			qWarning() << "Failed to open the style sheet file:" << file.errorString();
			return QString();
		}
		QTextStream in(&file);
		return in.readAll();
	}
	
	inline void setRoundIcon(QLabel *iconLabel, QString iconPath, const int iconSize) {
		if (!iconLabel) {
			qDebug() << "ERROR: Utils::setRoundIcon: iconLabel: expected QLabel, but got nullptr instead!";
			return;
		}
		if (!fileExists(iconPath)) {
			qWarning() << "WARNING: Utils::setRoundIcon: the icon file does not exist:" 
					   << iconPath << "Using the default icon instead.";
			iconPath = QString("assets/default_avatar.png");
		}
		if (iconSize < 0) {
			qDebug() << "ERROR: Utils::setRoundIcon: iconSize cannot be negative!";
			return;
		}
		
		QPixmap iconPixmap(iconPath);
		iconPixmap = iconPixmap.scaled(
			iconSize, iconSize,
			Qt::KeepAspectRatioByExpanding,
			Qt::SmoothTransformation
		);
		
		QPixmap roundIconPixmap(iconSize, iconSize);
		roundIconPixmap.fill(Qt::transparent);
		
		QPainter painter(&roundIconPixmap);
		
		painter.setRenderHint(QPainter::Antialiasing, true);
		painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
		
		painter.setBrush(Qt::black);
		painter.setPen(Qt::NoPen);
		
		painter.drawEllipse(0, 0, iconSize, iconSize);
		
		painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
		painter.drawPixmap(0, 0, iconPixmap);
		
		painter.end();
		
		iconLabel->setPixmap(roundIconPixmap);
		iconLabel->setFixedSize(iconSize, iconSize);
	}
}