#ifndef __ObjectPool_H__
#define __ObjectPool_H__

template <class POOL_OBJECT_TYPE>

class ObjectPool
{
public:
	ObjectPool(std::vector<POOL_OBJECT_TYPE> objects);
	ObjectPool();
	~ObjectPool();

	std::vector<POOL_OBJECT_TYPE> m_Objects;
	
	void ReturnObjectToPool(POOL_OBJECT_TYPE);
	void AddItemToPool(POOL_OBJECT_TYPE);
	POOL_OBJECT_TYPE GetItemFromPool();

	int GetInactivePoolSize(); // how many objects are still in the pool?
	unsigned int GetTotalPoolSize() { return m_Objects.size(); }; // how many objects can the pool hold?
};

template <class POOL_OBJECT_TYPE>
ObjectPool<POOL_OBJECT_TYPE>::ObjectPool(std::vector<POOL_OBJECT_TYPE> objects)
{
	for (int i = 0; i < objects.size(); i++)
	{
		m_Objects.push_back(objects.at(i));
	}
}

template <class POOL_OBJECT_TYPE>
ObjectPool<POOL_OBJECT_TYPE>::ObjectPool()
{

}

template <class POOL_OBJECT_TYPE>
ObjectPool<POOL_OBJECT_TYPE>::~ObjectPool()
{

}

template <class POOL_OBJECT_TYPE>
void ObjectPool<POOL_OBJECT_TYPE>::AddItemToPool(POOL_OBJECT_TYPE object)
{
	m_Objects.push_back(object);
}

template <class POOL_OBJECT_TYPE>
void ObjectPool<POOL_OBJECT_TYPE>::ReturnObjectToPool(POOL_OBJECT_TYPE object)
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects.at(i) == NULL)
		{
			m_Objects.at(i) = object;
			return;
		}
	}
}

template <class POOL_OBJECT_TYPE>
POOL_OBJECT_TYPE ObjectPool<POOL_OBJECT_TYPE>::GetItemFromPool()
{
	for (int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects.at(i) != NULL)
		{
			POOL_OBJECT_TYPE returnObject = m_Objects.at(i);
			m_Objects.at(i) = NULL;
			return returnObject;
		}
	}
	return nullptr;
}

template <class POOL_OBJECT_TYPE>
int ObjectPool<POOL_OBJECT_TYPE>::GetInactivePoolSize()
{
	int counter = 0;
	for (unsigned int i = 0; i < m_Objects.size(); i++)
	{
		if (m_Objects.at(i) != NULL)
		{
			counter++;
		}
	}
	return counter;
}

#endif //__ObjectPool_H__