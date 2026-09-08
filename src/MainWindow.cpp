#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QLabel> 
#include <QComboBox> 
#include <QScrollArea>
#include <QMouseEvent>

#include "MainWindow.h"
#include "TopControl.h"
#include "SearchBar.h"
#include "ChatDataManager.h"
#include "ChatList.h"
#include "ChatWindowHeader.h"

MainWindow::MainWindow() {
	setWindowTitle("Runo");
	resize(1280, 720);
	setWindowFlag(Qt::FramelessWindowHint);
	
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	
	QVBoxLayout *rootLayout = new QVBoxLayout(centralWidget);
	rootLayout->setContentsMargins(0, 0, 0, 0);
	rootLayout->setSpacing(0);
	
	topControl = new TopControl(centralWidget);
	rootLayout->addWidget(topControl->getWidget());
	
	connect(topControl->getSignals(), &TopControlSignals::minimizeWindow, this, &QMainWindow::showMinimized);
	connect(topControl->getSignals(), &TopControlSignals::maximizeWindow, this, [this]() {
		isMaximized() ? showNormal() : showMaximized();
	});
	connect(topControl->getSignals(), &TopControlSignals::closeWindow, this, &QMainWindow::close);
	
	QHBoxLayout *mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setSpacing(0);
	rootLayout->addLayout(mainLayout);
	
	QVBoxLayout *leftPanel = new QVBoxLayout();
	mainLayout->addLayout(leftPanel, 1);
	
	searchBar = new SearchBar(centralWidget);
	leftPanel->addWidget(searchBar->getWidget());
	
	chatDataManager = new ChatDataManager();
	
	chatList = new ChatList(centralWidget, chatDataManager);
	leftPanel->addWidget(chatList->getWidget());
	
	connect(searchBar->getSignals(), &SearchBarSignals::textChanged, this, 
		[this](const QString &query) { chatList->filterChatList(query); });
	
	QVBoxLayout *rightPanel = new QVBoxLayout();
	mainLayout->addLayout(rightPanel, 3);
	
	chatWindowHeader = new ChatWindowHeader(centralWidget);
	rightPanel->addWidget(chatWindowHeader->getWidget());
	
	connect(chatList->getSignals(), &ChatBoxSignals::chatBoxSelected, this, 
		[this](const QString &name) { chatWindowHeader->updateChatInfo(name); });
	
	connect(chatWindowHeader->getSignals(), &ChatWindowHeaderSignals::deleteChatPressed, this, 
		[this]() { chatList->deleteById(chatList->getFocusedChatId()); });
	
	messages = new QListWidget(centralWidget);
	rightPanel->addWidget(messages);
	
	inputMessage = new QLineEdit(centralWidget);
	inputMessage->setPlaceholderText("Write a message...");
	rightPanel->addWidget(inputMessage);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton && event->position().y() < 30) {
		dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
		event->accept();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	if (event->buttons() & Qt::LeftButton && event->position().y() < 30) {
		move(event->globalPosition().toPoint() - dragPosition);
		event->accept();
	}
}