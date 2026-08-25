#pragma once 

#include <QObject>

class QWidget;
class QString;
class QLineEdit;
class QHBoxLayout;

class SearchBarSignals : public QObject {
	Q_OBJECT
signals:
	void textChanged(const QString &query);
};

class SearchBar {
public:
	SearchBar(QWidget *parentWidget);
	QWidget* getWidget() { return searchBarWidget; };
	SearchBarSignals* getSignals() { return &searchBarSignals; };
private:
	QWidget* parentWidget;
	QWidget* searchBarWidget;
	QHBoxLayout *searchBarWidgetLayout;
	QLineEdit *searchBar;
	SearchBarSignals searchBarSignals;
};