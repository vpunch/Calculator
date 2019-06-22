#include "calculator.h"

#include <QDebug>

Calculator::Calculator()
{
	reset();
}

double Calculator::modifySecond(const QString& op, const double f, const double s) const
{
    if (op == "×" || op == "÷")
        return s * 0.01;
    else if (op == "+" || op == "-")
        return s * 0.01 * f;
    else
        qFatal("Invalid prime operation");
}

double Calculator::primeCalc(const QString& op, const double f, const double s) const
{
    if (op == "×")
        return f * s;
    else if (op == "÷")
        return f / s;
    else if (op == "+")
        return f + s;
    else if (op == "-")
        return f - s;
    else
        qFatal("Invalid prime operation");
}

double Calculator::relatCalc(
        const QString& op,
        const double val,
        const double specVal,
        bool percent) const
{
    if (percent) {
        if (op == "÷")
            return primeCalc(op, val, modifySecond(op, val, specVal));
        else
            return primeCalc(op, specVal, modifySecond(op, specVal, val));
    }
    return primeCalc(op, val, specVal);
}

double Calculator::directCalc(const QString& op, const double f, const double s, bool percent) const
{
    if (percent)
        return primeCalc(op, f, modifySecond(op, f, s));

    return primeCalc(op, f, s);
}

//f - first, s - second (operand)
double Calculator::getSpecVal(const QString& op, const double f, const double s, bool percent) const
{
    if (percent) {
        if (op != "÷")
            return f;

        return s;
    }

    if (op != "×")
        return s;

    return f;
}

double Calculator::calculate(double val /*X (see README)*/, bool percent)
{
    QString op = m_operations.takeLast(); //previous operation
    double specVal = m_operands.takeLast(); //specific value (see README)

    double res;
    if (m_operations.isEmpty()) { //X =(%)
        res = relatCalc(op, val, specVal, percent);
    }
    else {
        op = m_operations.takeLast();
        double f;
        if (m_operands.isEmpty()) { //X op =(%)
            if (op == "×")
                f = val;
            else if (op == "÷")
                f = 1;
            else if (op == "+" || op == "-")
                f = specVal;
            else
                qFatal("Invalid prime operation");
        }
        else //V op X =(%)
            f = m_operands.takeLast();

        res = directCalc(op, f, val, percent);
        specVal = getSpecVal(op, f, val, percent);
    }

	if (!m_operations.isEmpty() || !m_operands.isEmpty())
		qFatal("Invalid calculate format");

    m_operations.prepend(op);
    m_operands.prepend(specVal);

	return res;
}

double Calculator::sqrt(double val)
{
    if (val < 0) {
        m_illegal = true;
        val = qFabs(val);
    }

    return qSqrt(val);
}

void Calculator::reset()
{
	m_operations.clear();
	m_operands.clear();
	m_operations.prepend("+");
	m_operands.prepend(0);

	m_illegal = false;
}

void Calculator::setOperation(const QString& op)
{
    m_operations.prepend(op);

    if (m_operations.size() != 2)
		qFatal("Invalid calculate format");
}

void Calculator::setOperand(double operand)
{
	m_operands.prepend(operand);

	if (m_operands.size() != 2)
		qFatal("Invalid calculate format");
}

bool Calculator::hasOperand() const
{
	if (m_operands.size() == 2)
		return true;

	return false;
}
