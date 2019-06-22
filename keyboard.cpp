#include "keyboard.h"

Keyboard::Keyboard(const Display* receiver, QWidget* parent)
	: QWidget(parent)
{
	QGridLayout* mainLay = new QGridLayout;
	const int rowLen = 5, rowCount = 5;

	QString keys[rowCount][rowLen] = {
			{"MRC",	"M-",	"M+",	"→",	"ON/C"},
			{"7",	"8",	"9",	"%",	"√"},
			{"4",	"5",	"6",	"×",	"÷"},
			{"1",	"2",	"3",	"+",	"-"},
			{"0",	"00",	".",	"",		"="}};

	QMap<QPair<int, int>, QPair<int, int>> spans;
	spans.insert({3, 3}, {2, 1});

    for (int i = 0; i < rowCount; ++i)
        for (int j = 0; j < rowLen; ++j) {
			QPair<int, int> span {1, 1};
			if (auto it = spans.find({i, j}); it != spans.end())
				span = *it;

			const QString& key = keys[i][j];
			if (key.isEmpty())
				continue;

            mainLay->addWidget(createBtn(key, receiver), i, j, span.first, span.second);
		}
	
    this->setLayout(mainLay);
}

QPushButton* Keyboard::createBtn(const QString& key, const Display* receiver) const
{
    QPushButton* btn = new QPushButton(key);
	btn->setFont(QFont("Gemunu Libre"));

	//error: ‘void Display::processBtn()’ is private within this context
	//QObject::connect(btn, &QPushButton::clicked, receiver, &Display::processBtn);

	QObject::connect(btn, SIGNAL(clicked()), receiver, SLOT(processBtn()));

    return btn;
}
