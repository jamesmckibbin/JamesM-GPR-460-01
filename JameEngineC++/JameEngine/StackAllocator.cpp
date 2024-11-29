#include "StackAllocator.h"

#include <iostream>

char* StackAllocator::Alloc(size_t size)
{
	const size_t bytesUsed = head - stack.data();
	const size_t bytesRemaining = stackSize - bytesUsed;
	if (bytesRemaining < size)
	{
		std::cerr << "Stack failed to allocate!\n";
		return nullptr;
	}

	char* ptrToObject = head;
	head += size;
	return ptrToObject;
}

void StackAllocator::Reset()
{
	head = stack.data();
}

char* StackAllocator::GetCurrentHead()
{
	return head;
}

void StackAllocator::ClearToFrame(char* frame)
{
	// Check to make sure this is legal (might strip this out after
	// debugging)
	if (frame < stack.data() || frame > (stack.data() + stack.size()))
	{
		std::cerr << "Tried to clear to frame pointer " << frame << ", but it's not"
			<< " within stack " << stack.data() << "!\n";
		return;
	}

	head = frame;
}