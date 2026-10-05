#pragma once 

class QWidget;
class QHBoxLayout;
class QLineEdit;

class InputMessage {
public:
	InputMessage(QWidget *parentWidget);
	QWidget* getWidget() { return inputMessageWidget; }
	void showWidget() { inputMessageWidget->setHidden(false); }
	void hideWidget() { inputMessageWidget->setHidden(true); }
private:
	QWidget *parentWidget;
	QWidget *inputMessageWidget;
	QHBoxLayout *inputMessageWidgetLayout;
	QLineEdit *inputMessage;
};