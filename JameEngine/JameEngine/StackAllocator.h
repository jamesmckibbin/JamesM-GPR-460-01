#pragma once

#include <vector>
#include <iostream>

class StackAllocator
{
public:
	StackAllocator(size_t size = 4096) :
		stack(size, 0),
		stackSize(stack.size()),
		head(stack.data())
		//   ^ std::vector<T>::data() returns the pointer
		//     to the beginning of the vector's buffer.
	{}

	// Allocates from the stack (can fail)
	char* Alloc(size_t size);

	// Type-safe version of Alloc
	template <typename T, typename ...Us>
	T* Alloc(Us ...args);

	// Returns a pointer to an array of length `length`
	// of elements of type T.
	template <typename T>
	T* AllocArray(size_t length);

	// Completely clears the stack.
	void Reset();

	// Can use this to store a checkpoint that can
	// be cleared to later.
	char* GetCurrentHead();

	// Clears a stack frame back to the given point.
	void ClearToFrame(char* frame);

	// // Informational Methods
	// Returns total number of bytes in stack.
	size_t Capacity() { return stack.size(); }
	
	// Returns number of currently used bytes
	size_t BytesInUse() { return head - stack.data(); }

	// Space remaining in stack
	// (NOTE: It's usually better to try to allocate
	//        and see if it worked, rather than checking
	//		  BytesFree() ahead of time.)
	size_t BytesFree() { return Capacity() - BytesInUse(); }

	float PctUsed() { return 100.f * ((float)BytesInUse() / Capacity()); }

private:
	// Our memory, which we can use for allocations
	std::vector<char> stack;

	size_t stackSize;

	// Stack pointer -- where we are in the stack.
	// Points to the next part of the stack that's available
	// for use.
	char* head;
};

template <typename T, typename ...Us>
T* StackAllocator::Alloc(Us... args)
{
	const size_t size = sizeof(T);
	const size_t bytesUsed = head - stack.data();
	const size_t bytesRemaining = stackSize - bytesUsed;
	if (bytesRemaining < size)
	{
		std::cerr << "Stack failed to allocate!\n";
		return nullptr;
	}

	char* ptrToObject = head;
	new (ptrToObject) T(args...);
	head += size;
	return (T*)ptrToObject;
}

template <typename T>
T* StackAllocator::AllocArray(size_t length)
{
	const size_t size = sizeof(T) * length;
	const size_t bytesUsed = head - stack.data();
	const size_t bytesRemaining = stackSize - bytesUsed;
	if (bytesRemaining < size)
	{
		std::cerr << "Stack failed to allocate!\n";
		return nullptr;
	}

	char* ptrToObject = head;
	head += size;
	return (T*)ptrToObject;
}