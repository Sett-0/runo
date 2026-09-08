#pragma once 

#include <QObject>

class QString;
class QWidget;
class QHBoxLayout;
class QLabel;

class TopControlSignals : public QObject {
	Q_OBJECT
signals:
	void minimizeWindow();
	void maximizeWindow();
	void closeWindow();
};

class TopControl {
public:
	TopControl(QWidget *parentWidget);
	QWidget* getWidget() { return topControlWidget; };
	TopControlSignals* getSignals() { return &topControlSignals; };
private:
	QString loadStyleSheet(const char *filePath);

	QWidget *parentWidget;
	QWidget *topControlWidget;
	QHBoxLayout *topControlWidgetLayout;
	QLabel *windowTitle;
	QPushButton *minimizeWindowButton;
	QPushButton *maximizeWindowButton;
	QPushButton *closeWindowButton;
	TopControlSignals topControlSignals;
};