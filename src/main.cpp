#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	app.setStyleSheet(
		"QMainWindow {"
		"	background-color: #3A4047;"
		"}"
	);
	
	MainWindow mainWindow;
	mainWindow.show();
	
	return app.exec();
}