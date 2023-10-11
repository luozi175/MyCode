﻿#pragma once


#include <iostream>
#include <assert.h>

namespace mempool {

	#define BlockSize 4096

	struct Slot {
		Slot* next;
	};

	class MemoryPool {
	public:
		MemoryPool();
		~MemoryPool();

		void init(int size);

		// 分配或收回⼀个元素的内存空间
		Slot* allocate();
		void deAllocate(Slot* p);
	private:
		int slotSize_; // 每个槽所占字节数
		Slot* currentBolck_; // 内存块链表的头指针
		Slot* currentSlot_; // 元素链表的头指针
		Slot* lastSlot_; // 可存放元素的最后指针
		Slot* freeSlot_; // 元素构造后释放掉的内存链表头指针
		//MutexLock mutex_freeSlot_;
		//MutexLock mutex_other_;

		size_t padPointer(char* p, size_t align); // 计算对⻬所需空间
		Slot* allocateBlock(); // 申请内存块放进内存池
		Slot* nofree_solve();
	};


	void init_MemoryPool();			//初始化内存池
	void* use_Memory(size_t size);
	void free_Memory(size_t size, void* p);
	MemoryPool& get_MemoryPool(int id);

	template<typename T, typename... Args>
	T* newElement(Args&&... args);
	// 调⽤p的析构函数，然后将其总内存池中释放
	template<typename T>
	void deleteElement(T* p);

	template<typename T, typename... Args>
	T* newElement(Args&&... args) {
		T* p;
		if ((p = reinterpret_cast<T*>(use_Memory(sizeof(T)))) != nullptr) {
			new(p) T(std::forward<Args>(args)...); // 完美转发
		}
		// new(p) T1(value);
		// placement new:在指针p所指向的内存空间创建⼀个T1类型的对象，类似与realloc
		// 把已有的空间当成⼀个缓冲区来使⽤，减少了分配空间所耗费的时间
		// 因为直接⽤new操作符分配内存的话，在堆中查找⾜够⼤的剩余空间速度是⽐较慢的

		return p;
	}

	// 调⽤p的析构函数，然后将其总内存池中释放
	template<typename T>
	void deleteElement(T* p) {
		if (p) {
			p->~T();
		}
		free_Memory(sizeof(T), reinterpret_cast<void*>(p));
	} 
}