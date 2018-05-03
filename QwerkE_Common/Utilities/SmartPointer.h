#ifndef __SmartPointer_H__
#define __SmartPointer_H__

// TODO: Improve SmartPointer()

// TODO: Think of making Protected vs Shared value pointers
// to allow multiple references, or force single reference.

template <class PTR_VALUE_TYPE>
class SmartPointer
{
public:
	SmartPointer(); // Allow empty pointer?
	SmartPointer(PTR_VALUE_TYPE value) { m_Value = value; };
	~SmartPointer();

	void Delete() { delete m_Value; m_Value = nullptr; } // Cleanup

	////

	PTR_VALUE_TYPE operator->() { return m_Value; }
	void operator=(PTR_VALUE_TYPE valueAddress);
	void operator delete(void* p) { free(p); }

	/* Pointer Duplication */
	PTR_VALUE_TYPE Copy() { return m_Value; }

private:
	PTR_VALUE_TYPE m_Value = nullptr;
};

template <class PTR_VALUE_TYPE>
SmartPointer<PTR_VALUE_TYPE>::SmartPointer()
{
}

template <class PTR_VALUE_TYPE>
SmartPointer<PTR_VALUE_TYPE>::~SmartPointer()
{
	// TODO: Fix deltion errors
	// Delete(); // Cleanup
}

template <class PTR_VALUE_TYPE>
void SmartPointer<PTR_VALUE_TYPE>::operator=(PTR_VALUE_TYPE valueAddress)
{
	if (m_Value == nullptr) { delete m_Value; } // Free previously allocated memory
	m_Value = valueAddress;
}

#endif //!__SmartPointer_H__
