#pragma once 

#include <QGuiApplication>
#include <QScreen>
#include <cmath>

namespace Utils {
	inline int noSystemDisplayScale(double pixels) {
		double systemDisplayScaleFactor = QGuiApplication::primaryScreen()->devicePixelRatio();
		return std::round(pixels / systemDisplayScaleFactor);
	}
}