#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QString>
#include <QList>
#include <QtMath>

class Calculator {
	QList<QString> m_operations;
	QList<double> m_operands;

	bool m_illegal; //negative sqrt and etc
	operator bool() const
	{
		return m_illegal;
	}

protected:
	double modifySecond(const QString& op, const double f, const double s) const;
	double primeCalc(const QString& op, const double f, const double s) const;
	double relatCalc(const QString& op, const double val, const double specVal, bool percent) const;
	double directCalc(const QString& op, const double f, const double s, bool percent) const;
	double getSpecVal(const QString& op, const double f, const double s, bool percent) const;

public:
	Calculator();

	void reset();

	double calculate(double val, bool percent /*second operand modifier*/);

    void setOperation(const QString& op);
	void setOperand(double operand);
	bool hasOperand() const;

	double sqrt(double val);
};

#endif
