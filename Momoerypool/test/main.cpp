#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#define MAX_MEM_SIZE 0x0100
typedef int* point_len;

typedef struct memblock_s {
    int block_size;
    int free_count;

    void* mem;
    void* ptr;
}memblock_t;

int init_mem(memblock_s* mem_p, size_t block_size = 32) {
    if (mem_p == NULL) {
        return -1;
    }
    if (block_size < sizeof(point_len)) {
        return -1;
    }

    memset(mem_p, 0, sizeof(memblock_s));

    mem_p->mem = malloc(MAX_MEM_SIZE);
    
    mem_p->block_size = block_size;
    mem_p->free_count = MAX_MEM_SIZE / block_size;

    if (mem_p->mem == NULL) {
        return -1;
    }

    mem_p->ptr = mem_p->mem;

    char* ptr = (char*)mem_p->mem;
    for (int i = 0; i < mem_p->free_count; i++) {
        *(char**)ptr = ptr + block_size;
        ptr += block_size;
    }


    return 0;
}

void* _malloc(memblock_s* memp, size_t size) {
    if (!memp || memp->free_count <= 0 || size > memp->block_size) {
        return NULL;
    }

    void* ptr = memp->ptr;
    memp->ptr = *(char**)memp->ptr;

    memp->free_count--;
    printf("_malloc\n");

    return ptr;
}

void _free(memblock_s* mem_p, void *ptr) {
    if (!mem_p || !ptr)return;

    *(char **)ptr = (char *)mem_p->ptr;
    mem_p->ptr = ptr;

    mem_p->free_count++;

    printf("_free\n");
    return;
}

//#define malloc(size) _malloc(size)
//#define free(ptr) _free(ptr)


void test() {
    memblock_t mem;

    init_mem(&mem, 4);
    printf("%d\n", mem.free_count);

    for (int i = 0; i < 65 ; i++) {
        void* p1 = _malloc(&mem, 4);

        if (p1) {
            *(int*)p1 = 0;
        }
        
        printf(" p = %p\n", &mem.ptr);
        printf("第%d次分配 p = %p\n", i, p1);
        
        //_free(&mem, p1);
    }
}
int main(int argc, char** argv)
{
    test();

    return 0;
}