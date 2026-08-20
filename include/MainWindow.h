#pragma once

#include <QMainWindow> 
#include <QString>

class QLineEdit;
class QComboBox;
class QPushButton;
class QListWidget;
class QLabel;

class MainWindow : public QMainWindow {
public:
	MainWindow();
private:
	void handleAddTask();
	void handleFilterText(const QString &pattern);
	void handleDeleteSelected();
	void handleClearAll();
	void updateStatusCount();
	
	QLineEdit   *taskInput;
	QComboBox   *priorityDropdown;
	QLineEdit   *searchBar;
	QPushButton *addButton;
	QPushButton *deleteButton;
	QPushButton *clearButton;
	QListWidget *taskList;
	QLabel      *statusLabel;
};