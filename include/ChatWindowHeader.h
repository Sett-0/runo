#pragma once 

class QWidget;
class QString;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;

class ChatWindowHeaderSignals : public QObject {
	Q_OBJECT
signals:
	void deleteChatPressed();
};

class ChatWindowHeader {
public:
	ChatWindowHeader(QWidget *parentWidget);
	QWidget* getWidget() const { return headerWidget; };
	ChatWindowHeaderSignals* getSignals() { return &chatWindowHeaderSignals; };
	void updateChatInfo(const QString &name);
private:
	void handleDeleteChat();

	QWidget *parentWidget;
	QWidget *headerWidget;
	QHBoxLayout *headerWidgetLayout;
	QVBoxLayout *chatInfoLayout;
	QLabel *name;
	QLabel *status;
	QPushButton *deleteChat;
	ChatWindowHeaderSignals chatWindowHeaderSignals;
};