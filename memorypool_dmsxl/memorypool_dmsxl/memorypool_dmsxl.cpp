#include <memory>
#include <iostream>
#include <assert.h>

#include "Memorypool.h"

using namespace std;

class Person {
public:
	int id_;
	std::string name_;
public:
	Person(int id, std::string name) : id_(id), name_(name) {
		//printf("构造函数调用\n");
	}
	~Person() {
		//printf("析构函数调用\n");
	}
};

void test01() {
	mempool::init_MemoryPool();
	shared_ptr<Person> p1(mempool::newElement<Person>(11, "Lawson"), mempool::deleteElement<Person>);
	for (int i = 0; i < 10000; i++) {
		mempool::use_Memory(32);
	}
	
	//printf("sizeof(name_) = %d\n", sizeof(p1->name_));
	printf("sizeof(Person) = %d\n", sizeof(Person));

}

int main() {
	test01();
	return 0;
}
