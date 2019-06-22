#ifndef BGVALUE_H
#define BGVALUE_H

class BgValue {
	double m_val;

public:
	BgValue()
	{
		reset();
	}

	void plus(double val)
	{
		m_val += val;
	}
	double get() const
	{
		return m_val;
	}
	void reset()
	{
		m_val = 0;
	}
};

#endif
