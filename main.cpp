#include <iostream>

#include <QApplication>

#include "src/Window.hpp"

using namespace std;

int main (int argc, char ** argv) {

    if (argc == 2) {
	QApplication app (argc, argv);
	Window win (argv[1]);
	win.show ();
	return app.exec ();
    } else {
	cout << "Usage : " << endl;
	cout << " niftireader file_name" << endl;
    }

    return 0;
}
