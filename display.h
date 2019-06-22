#ifndef DISPLAY_H
#define DISPLAY_H

#include <QWidget>
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "calculator.h"
#include "bgvalue.h"

class Display : public QWidget {
	Q_OBJECT

	QLCDNumber* m_valViewer; //processBtn

	QString m_val; //modifyVal
	bool m_finalVal; //fixFinalVal
	bool m_overflow;

	using Indr = QPair<QLabel*, QString>; //indicator type
	using IndrList = QList<Indr>;
	//setIndr
	IndrList m_rightIndrs; //getRSymbol
	IndrList m_leftIndrs;

	QStringList m_operations;

	Calculator m_calc;
	BgValue m_bgVal;

protected:
	QLayout* getPanel(const QStringList& symbols, IndrList& cont);
    bool setIndr(IndrList& indrs, const QString& symbol, bool on = true);
	QString getRSymbol(bool take = false); //get right symbol

	bool modifyVal(const QString& key, const QString& prevKey);
	void fixFinalVal(bool reset = true);

	bool calcKey(const QString& key);

	void setResult(bool percent = false);
	QString strVal(double val) const;
	void reset();

public:
    Display(uint n, QWidget* parent = nullptr);

private slots:
	void processBtn();
};

#endif
