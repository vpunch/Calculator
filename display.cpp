#include "display.h"

#include <QDebug>

/*
 * !
 * 9+3-=	-12
 * 9+3=-=	-9
 */

Display::Display(uint n, QWidget* parent)
	: QWidget(parent), m_val("0"), m_finalVal(false), m_overflow(false)
{
	m_valViewer = new QLCDNumber(n);
	m_valViewer->setSmallDecimalPoint(true);
	m_valViewer->display(m_val);
	//m_valViewer->setFrameStyle(QFrame::NoFrame);
	
	m_operations << "+" << "-" << "×" << "÷";
	
	QHBoxLayout* mainLay = new QHBoxLayout;
    mainLay->addLayout(getPanel({"M", "E"}, m_leftIndrs));
    mainLay->addWidget(m_valViewer, 1);
    mainLay->addLayout(getPanel(QStringList(m_operations) << "=", m_rightIndrs));

	setLayout(mainLay);
}

QLayout* Display::getPanel(const QStringList& symbols, IndrList& cont)
{
    QVBoxLayout* panel = new QVBoxLayout;

    foreach (const QString& symbol, symbols) {
        QLabel* indrWid = new QLabel;
        indrWid->setFont(QFont("Gemunu Libre"));

        cont << Indr(indrWid, symbol);
        panel->addWidget(indrWid);
    }

    return panel;
}

bool Display::setIndr(IndrList& indrs, const QString& symbol, bool on)
{
    for (Indr& indr : indrs)
		if (indr.second == symbol) {
			if (on)
				indr.first->setText(indr.second);
			else
				indr.first->clear();

			return true;
		}

	return false;
}

QString Display::getRSymbol(bool take)
{
	QString symbol;

    for (Indr& indr : m_rightIndrs) {
		QLabel* indrWid = indr.first;
		if (!indrWid->text().isEmpty()) {
			symbol = indrWid->text();

			if (take)
				indrWid->clear();

			break;
		}
	}

	return symbol;
}

void Display::processBtn()
{
	const QString& key = ((QPushButton*)sender())->text();	
	static QString prevKey;

	if (modifyVal(key, prevKey)) {
		setIndr(m_rightIndrs, "=", false);

		if (m_val.isEmpty())
			m_val = "0";

		else if (m_val.startsWith("."))
			m_val.prepend("0");
	}
	else if (calcKey(key)) {
		getRSymbol(true);
		setIndr(m_rightIndrs, "=");

		m_finalVal = true;
	}
	else if (m_operations.contains(key)) {
		if (m_calc.hasOperand())
			setResult();

		getRSymbol(true);
		setIndr(m_rightIndrs, key);

		m_finalVal = true;
	}
	else if (key == "ON/C")
		reset();

	m_valViewer->display(m_val);

	if(m_overflow)
		setIndr(m_leftIndrs, "E");

	prevKey = key;
}

QString Display::strVal(double val) const
{
    return QString::number(val, 'g', m_valViewer->digitCount());
}

void Display::reset() {
	m_val = "0";
	m_finalVal = false;
	m_overflow = false;

	getRSymbol(true);

	m_calc.reset();
	m_bgVal.reset();
}

void Display::setResult(bool percent)
{
	if (const QString& symbol = getRSymbol(); m_operations.contains(symbol))
		m_calc.setOperation(symbol);

	m_val = strVal(m_calc.calculate(m_val.toDouble(), percent));
}

bool Display::calcKey(const QString& key)
{
	if (key == "=") {
		setResult();
		return true;
	}
	else if (key == "%") {
		setResult(true);	
		return true;
	}
	else if (key == "M+") {
		setResult();
		m_bgVal.plus(m_val.toDouble());
		return true;
	}
	else if (key == "M-") {
        setResult();
		m_bgVal.plus(-m_val.toDouble());
		return true;
	}

	return false;
}

void Display::fixFinalVal(bool reset)
{
	if (m_finalVal) {
		if (m_operations.contains(getRSymbol()) && !m_calc.hasOperand())
			m_calc.setOperand(m_val.toDouble());
		
		if (reset)
			m_val = "0";

		m_finalVal = false;
	}
}

bool Display::modifyVal(const QString& key, const QString& prevKey)
{
	static const QString& decSep = "."; //decimal separator

	if (key.contains(QRegExp("^([0-9]|00)$"))) {
		fixFinalVal();

		if (prevKey == decSep && !m_val.contains(decSep))
			m_val += decSep;

		m_val += key;
		
		m_val.remove(QRegExp("^0+"));
		
		return true;
	}
	else if (key == decSep) {
		fixFinalVal();

		return true;
	}
	else if (key == "→") {
		int n = 1;
		if (m_val.contains(QRegExp("\\.\\d$")))
			++n;

		m_val.remove(-n, n);
		
		return true;
	}
	else if (key == "√") {
		fixFinalVal(false);

		m_val = strVal(m_calc.sqrt(m_val.toDouble()));
		m_finalVal = true;

		return true;
	}
	else if (key == "MRC") {
		if (prevKey == key) {
			m_bgVal.reset();
			return true;
		}

		fixFinalVal();

		m_val = strVal(m_bgVal.get());
		m_finalVal = true;

		return true;
	}

	return false;
}
