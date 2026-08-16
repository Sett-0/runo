#include <QApplication>
#include <QMainWindow> 
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel> 

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	
	QMainWindow mainWindow;
	mainWindow.setWindowTitle("Runo");
	mainWindow.resize(800, 600);
	
	QWidget *centralWidget = new QWidget(&mainWindow);
	QVBoxLayout *layout = new QVBoxLayout(centralWidget);
	
	QLabel *placeholder = new QLabel("Some sort of label idk", centralWidget);
	placeholder->setAlignment(Qt::AlignCenter);
	layout->addWidget(placeholder);
	
	mainWindow.setCentralWidget(centralWidget);
	mainWindow.show();
	
	return app.exec();
}