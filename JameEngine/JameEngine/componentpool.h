#pragma once

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
	
	int GetPoolSize() { return pool.size(); }

private:
	T* pool[];
	std::vector<bool> inUse;
};