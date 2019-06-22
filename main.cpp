#include <QApplication>
#include <QFontDatabase>
#include <QWidget>
#include <QVBoxLayout>

#include "keyboard.h"
#include "display.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

	QFontDatabase::addApplicationFont(":/gemunu-libre.bold.otf");


	Display* disp = new Display(12);

	Keyboard* kb = new Keyboard(disp);

	QVBoxLayout* mainLay = new QVBoxLayout;
	mainLay->addWidget(disp);
	mainLay->addWidget(kb);

	QWidget wid;
	wid.setLayout(mainLay);
    wid.setWindowTitle("Calculator");
    wid.show();


    return a.exec();
}
