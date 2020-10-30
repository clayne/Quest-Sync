#pragma once

#if !_DEBUG
#include "MemoryPool.h"
#endif
#include "common/ICriticalSection.h"


namespace SmallObjectsAllocator
{
	template <class T, std::size_t C>
	class Allocator
	{
#if _DEBUG
		std::size_t count_ = 0;
#else
		MemoryPool<T, sizeof(T)* C> pool_;
#endif
		ICriticalSection criticalSection_;

		void Free(T* ptr)
		{
#if _DEBUG
			::operator delete(ptr);
#else
			pool_.deallocate(ptr);
#endif
		}
		
	public:
		T* Allocate()
		{
			ScopedLock lock(criticalSection_);
#if _DEBUG
			++count_;
			if (count_ > C)
			{
				_MESSAGE("Warning, possible memory leak");
			}

			return static_cast<T*>(operator new(sizeof(T)));
#else
			return pool_.allocate();

#endif

		}

		void Free(void* ptr)
		{
			ScopedLock lock(criticalSection_);
			Free(static_cast<T*>(ptr));
#if _DEBUG
			--count_;
#endif
		}
	};
}
