#ifndef _RangedValue_H_
#define _RangedValue_H_

template <class t>
class RangedValue
{
public:
	RangedValue();
	~RangedValue();

	void SetValue(t newValue) { m_Value = newValue; }
	void AddToValue(t increment)
	{
		// TODO: Range check
		m_Value += increment;
	}
	void SubtractFromValue(t increment)
	{
		// TODO: Range check
		m_Value -= increment;
	}

private:
	t m_Value;

	t m_MinValue;
	t m_MaxValue;
};

template <class t>
RangedValue::RangedValue()
{
}

template <class t>
RangedValue::~RangedValue()
{
}

#endif // !_RangedValue_H_
