#pragma once

#include "rectanglerenderer.h"
#include "rectanglecollider.h"
#include "playercontroller.h"
#include "collidercolorchanger.h"
#include "trianglerenderer.h"

#include <assert.h>
#include <vector>

template <typename T>
class ComponentPool {
public:
	ComponentPool(int size) :
		pool(size),
		inUse(size, false)
	{}
	template <typename ...Us>
	T* New(Us ...args);
	void Delete(T* toDelete);

	bool CanCreateComponent();

	T* GetPoolArrayItem(int index);
	bool GetPoolArrayItemInUse(int index);
	int GetSize();

private:
	std::vector<T> pool;
	std::vector<bool> inUse;
};

template <typename T>
template <typename ...Us>
T* ComponentPool<T>::New(Us ...args)
{
	for (int i = 0; i < pool.size(); i++)
	{
		bool isInUse = inUse[i];
		if (!isInUse)
		{
			inUse[i] = true;
			new (&pool[i]) T(args...);
			return &pool[i];
		}
	}
	assert(false);
}

template <typename T>
void ComponentPool<T>::Delete(T* toDelete)
{
	// First, check that this is actually in use
	for (int i = 0; i < pool.size(); i++)
	{
		T* item = &pool[i];
		if (toDelete == item)
		{
			bool isInUse = inUse[i];
			assert(isInUse);
			inUse[i] = false;
			item->~T();
			return;
		}
	}
  	assert(false);
}

template<typename T>
bool ComponentPool<T>::CanCreateComponent()
{
	for (int i = 0; i < inUse.size(); i++) {
		if (!inUse[i]) {
			return true;
		}
	}
	return false;
}

template<typename T>
int ComponentPool<T>::GetSize() { return pool.size(); }

template<typename T>
T* ComponentPool<T>::GetPoolArrayItem(int index) { return &pool[index]; }

template<typename T>
bool ComponentPool<T>::GetPoolArrayItemInUse(int index) { return inUse[index]; }