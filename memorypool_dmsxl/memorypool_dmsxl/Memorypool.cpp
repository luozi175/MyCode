#include"Memorypool.h"


using namespace mempool;
using std::cout;
using std::endl;

MemoryPool::MemoryPool() {}
MemoryPool::~MemoryPool() {
	Slot* cur = currentBolck_;
	while (cur) {
		Slot* next = cur->next;
		// free(reinterpret_cast<void *>(cur));
		// 转化为 void 指针，是因为 void 类型不需要调⽤析构函数,只释放空间
		operator delete(reinterpret_cast<void*>(cur));
		cur = next;
	}
}

void MemoryPool::init(int size) {
	assert(size > 0);
	slotSize_ = size;
	currentBolck_ = NULL;
	currentSlot_ = NULL;
	lastSlot_ = NULL;
	freeSlot_ = NULL;
}

// 计算对齐所需补的空间
inline size_t MemoryPool::padPointer(char* p, size_t align) {
	//如果没有调用内存池初始化会报错
	if (align == 0) {
		return 0;
	}

	size_t result = reinterpret_cast<size_t>(p);

	//cout << result << endl;
	//cout << align << endl;
	//cout << ((align - result) % align) << endl;

	return ((align - result) % align);
}
Slot* MemoryPool::allocateBlock() {
	char* newBlock = reinterpret_cast<char*>(operator new(BlockSize));
	char* body = newBlock + sizeof(Slot*);
	// 计算为了对⻬需要空出多少位置
	size_t bodyPadding = padPointer(body, static_cast<size_t>(slotSize_));
	std::cout << bodyPadding <<"padPointer(body, static_cast<size_t>(slotSize_));"  << endl;

	// 注意：多个线程（eventLoop 共⽤⼀个MemoryPool）
	Slot* useSlot;
	{
		//MutexLockGuard lock(mutex_other_);
		// newBlock接到Block链表的头部
		reinterpret_cast<Slot*>(newBlock)->next = currentBolck_;
		currentBolck_ = reinterpret_cast<Slot*>(newBlock);

		// 为该Block开始的地⽅加上bodyPadding个char* 空间
		currentSlot_ = reinterpret_cast<Slot*>(body + bodyPadding);
		lastSlot_ = reinterpret_cast<Slot*>(newBlock + BlockSize - slotSize_ + 1);
		useSlot = currentSlot_;

		// slot指针⼀次移动8个字节
		currentSlot_ += (slotSize_ >> 3);
	}
	return useSlot;
}

//如果内存池分配时没有空闲空间
Slot* MemoryPool::nofree_solve() {
	if (currentSlot_ >= lastSlot_)
		return allocateBlock();
	Slot* useSlot;
	{
		//MutexLockGuard lock(mutex_other_);
		useSlot = currentSlot_;
		currentSlot_ += (slotSize_ >> 3);
	}
	return useSlot;
}

//内存池分配空间优先从空闲空间找
Slot* MemoryPool::allocate() {
	if (freeSlot_) {
		{
			//MutexLockGuard lock(mutex_freeSlot_);
			if (freeSlot_) {
				Slot* result = freeSlot_;
				freeSlot_ = freeSlot_->next;
				return result;
			}
		}
	}
	return nofree_solve();
}

//释放内存块
inline void MemoryPool::deAllocate(Slot* p) {
	if (p) {
		// 将slot加⼊释放队列
		//MutexLockGuard lock(mutex_freeSlot_);
		p->next = freeSlot_;
		freeSlot_ = p;
	}
}

//获取一个内存池
MemoryPool& mempool::get_MemoryPool(int id) {
	static MemoryPool memorypool_[64];
	return memorypool_[id];
}

//获取内存块
void* mempool::use_Memory(size_t size) {
	if (!size)
		return nullptr;

	// 超过512字节就直接new
	if (size > 512)
		return operator new(size);

	// 相当于(size / 8)向上取整
	return reinterpret_cast<void*>(get_MemoryPool(((size + 7) >> 3) - 1).allocate());
}

//释放内存块
void mempool::free_Memory(size_t size, void* p) {
	if (!p) return;
	if (size > 512) {
		operator delete (p);
		return;
	}
	get_MemoryPool(((size + 7) >> 3) - 1).deAllocate(reinterpret_cast<Slot*>(p));
}

// 数组中分别存放Slot⼤⼩为8，16，...，512字节的BLock链表
void mempool::init_MemoryPool() {

	cout << "init_MemoryPool" << endl;

	for (int i = 0; i < 64; ++i) {
		get_MemoryPool(i).init((i + 1) << 3);
	}
}