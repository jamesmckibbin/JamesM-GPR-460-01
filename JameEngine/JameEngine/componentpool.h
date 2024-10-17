#pragma once

#include <assert.h>
#include <vector>

#include "rectanglerenderer.h"
#include "rectanglecollider.h"
#include "playercontroller.h"
#include "collidercolorchanger.h"

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

	T* GetPool() { return pool; }

private:
	std::vector<T*> pool;
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
			// We found a free one!
			inUse[i] = true;
			// Use "placement new" to make sure we construct the
			// object properly.
			new (&pool[i]) T(args...);
			return pool[i];
		}
	}

	// We reach here if the pool is empty. There's no way to proceed --
	// this is the same as if new raised an error.
	assert(false);
	return nullptr;
}

template <typename T>
void ComponentPool<T>::Delete(T* toDelete)
{
	// First, check that this is actually in use
	for (int i = 0; i < pool.size(); i++)
	{
		T* item = pool[i];
		if (toDelete == item)
		{
			// We found the relevant item!
			bool isInUse = inUse[i];

			// Make sure caller isn't trying to delete an
			// already-deleted item.
			assert(isInUse);

			// Free the item
			inUse[i] = false;

			// Have to call destructor here because we called
			// the constructor earlier with 'placement new'!
			item->~T();
			return;
		}
	}

	// Reaching this code means the caller tried to delete
	// a toDelete that wasn't given by this pool.
	assert(false);
}

