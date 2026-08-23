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

#include "MainWindow.h"
#include "ChatList.h"

MainWindow::MainWindow() {
	setWindowTitle("Runo");
	resize(800, 600);
	
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	
	QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget); // A memory ownership [a layout belongs to a widget]
	
	QVBoxLayout *leftPanel = new QVBoxLayout();
	mainLayout->addLayout(leftPanel, 1);
	
	searchBar = new QLineEdit(centralWidget); // A memory ownership [a widget belongs to a widget]
	searchBar->setPlaceholderText("Search");
	leftPanel->addWidget(searchBar); // A visual ownership [a widget belongs to a layout]
	
	chatList = new ChatList(centralWidget);
	for (size_t i = 1; i <= 12; i++) chatList->add(QString("Friend %1").arg(i), i+100); 
	leftPanel->addWidget(chatList->getWidget());
	
	QVBoxLayout *rightPanel = new QVBoxLayout();
	mainLayout->addLayout(rightPanel, 3);
	
	statusBar = new QLabel("#Name, #Status", centralWidget);
	rightPanel->addWidget(statusBar);
	
	messages = new QListWidget(centralWidget);
	rightPanel->addWidget(messages);
	
	inputMessage = new QLineEdit(centralWidget);
	inputMessage->setPlaceholderText("Write a message...");
	rightPanel->addWidget(inputMessage);
	
	
	/*
	QVBoxLayout *mainLayout  = new QVBoxLayout(centralWidget);
	QHBoxLayout *inputLayout = new QHBoxLayout();
	
	QHBoxLayout *controlLayout = new QHBoxLayout();
	QVBoxLayout *controlButtonsLayout = new QVBoxLayout();
	controlButtonsLayout->setAlignment(Qt::AlignTop);
	
	taskInput = new QLineEdit(centralWidget);
	taskInput->setPlaceholderText("Enter a new task tracking description...");
	
	priorityDropdown = new QComboBox(centralWidget);
	priorityDropdown->addItem("Low");
	priorityDropdown->addItem("Medium");
	priorityDropdown->addItem("High");
	priorityDropdown->setCurrentIndex(1);
	
	addButton = new QPushButton("Add Task", centralWidget);
	
	inputLayout->addWidget(taskInput, 4);
	inputLayout->addWidget(priorityDropdown, 1);
	inputLayout->addWidget(addButton, 1);
	
	mainLayout->addLayout(inputLayout);
	
	searchBar = new QLineEdit(centralWidget);
	searchBar->setPlaceholderText("Search for task...");
	mainLayout->addWidget(searchBar);
	
	taskList = new QListWidget(centralWidget);
	deleteButton = new QPushButton("Delete Selected", centralWidget);
	clearButton = new QPushButton("Clear Tasks", centralWidget);
	
	controlLayout->addWidget(taskList, 4);
	controlLayout->addLayout(controlButtonsLayout, 1);
	controlButtonsLayout->addWidget(deleteButton, 1);
	controlButtonsLayout->addWidget(clearButton, 1);
	mainLayout->addLayout(controlLayout);
	
	statusLabel = new QLabel("Total Tasks: 0", centralWidget);
	mainLayout->addWidget(statusLabel);
	
	connect(addButton,    &QPushButton::clicked,     this, &MainWindow::handleAddTask);
	connect(taskInput,    &QLineEdit::returnPressed, this, &MainWindow::handleAddTask);
	connect(searchBar,    &QLineEdit::textChanged,   this, &MainWindow::handleFilterText);
	connect(deleteButton, &QPushButton::clicked,     this, &MainWindow::handleDeleteSelected);
	connect(clearButton,  &QPushButton::clicked,     this, &MainWindow::handleClearAll);
	*/
}

/*
void MainWindow::handleAddTask() {
	QString text = taskInput->text().trimmed();
	if (text.isEmpty()) {
		QMessageBox::warning(this, "Empty Input", "Task description cannot be left blank");
		return;
	}
	QString priority = priorityDropdown->currentText();
	QString task = QString("[%1] %2").arg(priority).arg(text);

	taskList->addItem(task);
	taskInput->clear();
	updateStatusCount();
}

void MainWindow::handleFilterText(const QString &pattern) {
	for (int i = 0; i < taskList->count(); i++) {
		QListWidgetItem *item = taskList->item(i);
		bool matched = item->text().contains(pattern, Qt::CaseInsensitive);
		item->setHidden(!matched);
	}
}

void MainWindow::handleDeleteSelected() {
	int currentRow = taskList->currentRow();
	if (currentRow == -1) {
		QMessageBox::information(this, "No Selection", "Select a task to delete");
		return;
	}
	QListWidgetItem *item = taskList->takeItem(currentRow);
	delete item;
	updateStatusCount();
}

void MainWindow::handleClearAll() {
	if (!taskList->count()) return;
	taskList->clear();
	updateStatusCount();
}

void MainWindow::updateStatusCount() {
	statusLabel->setText(QString("Total Tasks: %1").arg(taskList->count()));
}
*/