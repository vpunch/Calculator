#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QGridLayout>
#include <QMap>
#include <QPair>
#include <QPushButton>

#include "display.h"

class Keyboard : public QWidget {
	Q_OBJECT

protected:
	QPushButton* createBtn(const QString& key, const Display* receiver) const;

public:	
	Keyboard(const Display* receiver, QWidget* parent = nullptr);
};

#endif
