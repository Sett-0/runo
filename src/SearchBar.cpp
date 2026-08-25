#include <QWidget>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QString>

#include "SearchBar.h"

SearchBar::SearchBar(QWidget *parentWidget) : parentWidget(parentWidget) {
	searchBarWidget = new QWidget(parentWidget);
	searchBarWidget->setMinimumHeight(55);
	searchBarWidget->setObjectName("searchBarWidget");
	searchBarWidget->setStyleSheet(
		"#searchBarWidget {"
		"	background-color: #282E33;"
		"}"
	);
	
	searchBarWidgetLayout = new QHBoxLayout(searchBarWidget);
	
	searchBar = new QLineEdit(parentWidget);
	searchBar->setPlaceholderText("Search");
	searchBar->setObjectName("searchBar");
	searchBar->setStyleSheet(
		"#searchBar {"
		"	background-color: #3D444B;"
		"	color: #C8C8C8;"
		"	font-size: 14px;"
		"	font-weight: 500;"
		"	border-radius: 16px;"
		"	padding-left: 12px;"
		"	padding-right: 12px;"
		"}"
	);
	searchBar->setMinimumHeight(35);
	searchBarWidgetLayout->addWidget(searchBar);
	
	QObject::connect(searchBar, &QLineEdit::textChanged, searchBarWidget, 
		[this](const QString &query) { emit searchBarSignals.textChanged(query); });
}
