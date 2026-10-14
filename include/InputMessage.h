#pragma once 

class QWidget;
class QHBoxLayout;
class QLineEdit;

class InputMessage {
public:
	InputMessage(QWidget *parentWidget);
	QWidget* getWidget() { return inputMessageWidget; }
	void showWidget(const size_t id);
	void hideWidget();
private:
	QWidget *parentWidget;
	size_t chatId = 0;
	QWidget *inputMessageWidget;
	QHBoxLayout *inputMessageWidgetLayout;
	QLineEdit *inputMessage;
};