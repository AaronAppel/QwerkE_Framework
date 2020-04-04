#include "Memory.h"

// TODO: Look into realloc()

//static const int size = 4096;
//static void* pool;
//static char* next;
//static bool initialized = false;

//void Init()
//{
//	pool = malloc(size);
//
//	if (!pool)
//		throw std::bad_alloc{};
//
//	next = (char*)pool;
//	initialized = true;
//}

// void* operator new(std::size_t size)
// {
// 	if (initialized == false)
// 	{
// 		Init();
// 	}
//
// 	void* retValue = next;
// 	next = next + size;
// 	return retValue;
// 	// return malloc(size);
// }

// void operator delete(void* object)
// {
// 	free(object);
// }

// TODO: Handle array allocations
// void* operator new[](std::size_t size)
// {
// 	return malloc(size);
// }

// void operator delete[](void* object)
// {
// 	free(object);
// }

namespace QwerkE {



}