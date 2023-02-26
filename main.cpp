#include <QApplication>
#include <QtWidgets>
#include <QtWebKitWidgets>

#include "window.hpp"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	Window window(1500, 1000, "Kmk Browser");
	window.show();

	return app.exec();

}
