#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include <stddef.h>

//minimal tagged memory allocation with tag checking
//each allocated block has a tag in its header
//all memory pages are non-executable to prevent code injection
//tag is verified on each read/write operation 
typedef struct {
    uint8_t tag;
    size_t size;
    uint8_t data[];
} tagged_block_t;

tagged_block_t* tagged_alloc(size_t size, uint8_t tag) {
    //allocate memory page with mmap
    size_t pagesize = (size_t)sysconf(_SC_PAGESIZE);
    if (pagesize == (size_t)-1) {
        //sysconf failed
        return NULL;
    }

    //ensure enough space for header + data
    size_t header_size = offsetof(tagged_block_t, data);
    if (header_size + size > pagesize) {
        return NULL;
    }
    //allocate a full page
    void *mem = mmap(NULL, pagesize, PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }
    //set up header
    tagged_block_t *block = (tagged_block_t *)mem;
    block->tag = tag;
    block->size = size;

    //initialize data to zero
    memset(block->data, 0, size);
    return block;
}

void tagged_free(tagged_block_t *block) {
    if (!block) return;
    size_t pagesize = (size_t)sysconf(_SC_PAGESIZE);
    munmap((void *)block, pagesize);
}

int tagged_write(tagged_block_t *block,  uint8_t expected_tag, size_t offset, const void *src, size_t n) {
    if (!block) return -1;

    //check tag and bounds
    //if tag mismatch, block the write
    if (block->tag != expected_tag) return -2;

    //if write exceeds allocated size, block it
    if (offset + n > block->size) return -3;

    //perform the write
    memcpy(&block->data[offset],src,n);
    return 0;
}

int tagged_read(tagged_block_t *block, uint8_t expected_tag, size_t offset, void *dest, size_t n) {
    if (!block) return -1;

    //check tag and bounds

    //if tag mismatch, block the read
    if (block->tag != expected_tag) return -2;

    //if read exceeds allocated size block it
    if (offset + n > block->size) return -3;

    memcpy(dest, &block->data[offset], n);
    return 0;
}

void corrupt_tag(tagged_block_t *block, uint8_t new_tag) {
    //simulate tag corruption by attacker
    if (!block) return;
    block->tag = new_tag;
}

int main(void) {
    const uint8_t TAG = 0xAB; //expected tag value fixed for unexecutable pages
    const size_t SIZE = 64; //size of allocated block

    tagged_block_t *block = tagged_alloc(SIZE, TAG);

    if (!block) {
        perror("tagged_alloc failed");
        return 1;
    }

    const char *message =  "Hello, World!";
    //try writing a message to the tagged block
    if (tagged_write(block, TAG,0, message, strlen(message)+1) == 0) {
        //normal write succeeded
        char out[128];
        //try reading it back
        if (tagged_read(block, TAG, 0, out, strlen(message)+1) == 0) {
            printf("Normal write/read succeeded: \"%s\"\n", out);
        }
    } else {
        printf("Normal write failed.\n");
    }

    corrupt_tag(block, 0xAC); //simulate tag corruption by an attacker

    const char *malicious_message = "Malicious Data";
    if (tagged_write(block, TAG, 0, malicious_message, strlen(malicious_message)+1) != 0) {
        //tag mismatch detected
        printf("Tag mismatch detected on write. Operation blocked.\n");
    }
    else {
        printf("Vulnerability!\n");
    }

    tagged_free(block);
    return 0;

}