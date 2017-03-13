## [Understanding the heap by breaking it](http://www.blackhat.com/presentations/bh-usa-07/Ferguson/Whitepaper/bh-usa-07-ferguson-WP.pdf)

The paper focuses on dynamic memory management by ptmalloc2. Heap is a global data structure that provides 'exists until free' scope. 

Difference between ptmalloc and dlmalloc?
* multiple areans or heaps are provided.
* supports multi-threaded applications.

Heap is a section of linear memory that is obtained through sbrk() or mmap(). The memory chunks start from a chunk known as 'top chunk'(The only memory chunk that can grow by requesting more memory from the system). 

Bin : The free list which represents the free memory chunk present in the linked list or doubly linked list. 

The allocated memory have the characteristic that they may not directly border another allocated chunk, (they border the top chunk or the free chunk).

Writing a heap under invalid circumstances can overwrite meta-data in a de-allocated chunk of memory, or a write occurs to a dangling pointer or to an allocated chunk of memory.

'''
	typedef struct-heap-info{
		mstate ar_ptr;
		struct-heap-info *ptr;
		size\_t size;
		char pad[]
}
'''

The above structure is pretty straightforward except mstate, it initialises an arena (mstate) with a pointer pointing to the previous arena in the memory. 

Lets look into mstate:

'''
	struct malloc\_state{
		mutex\_t mutex; // Ensures synchronized access to various data structures used by ptmalloc
		int flags; // represents various characteristics of current arena.
		mfastbinptr fastbins[NFASTBINS]; // used for housing chunks that are allocated and free'd
		long stat\_lock\_direct, stat\_lock\_loop, stat\_lock\_wait;
		mchunkptr top; // special chunk of memory that borders the end of available memory. 
		mchunkptr last_remainder;
		mchunkptr bins[NBINS*2];
		unsigned int binmap[BINMAPSIZE];
		struct malloc\_state *next;
		INTERNAL\_SIZE\_T system\_mem;
		INTERNAL\_SIZE\_T max\_system\_mem;
	}
'''

There are like 2 bins, Fastbin and mchunkptr bins[]. bins array operates as a list of free chunks of memory. 

### Chunks of memory

The chunks that are allocated by ptmalloc2 are of the same physical structure regardless of whether they are a fast chunk or a normal chunk. However the representation is different depending on the stateof the chunk. 

''' 
	struct malloc\_chunk {
		INTERNAL\_SIZE\_T prev\_size;
		INTERNAL\_SIZE\_T size;
		struct malloc\_chunk* fd; // pointer to the next chunk 
		struct malloc\_chunk* bk; // pointer to the prev chunk
	}
'''

Regardless of how much memory is requested to be allocated, there will be extra bytes allocated for metadata, two variables (prev\_size and size) and two pointers to prev memory and the next memory (which sums up a 16,24 or 32 bytes of overhead per chunk). Also we have alignment issues, a malloc chunk must fall on a boundary of power of two at least as large as 2 times the sizeof(INTERNAL\_SIZE\_T). 

'''

	chunk -> ----------------------------
             Size of previous chunk
			 ----------------------------
			 Size of this chunk |A|M|P
	mem   -> ----------------------------
              DATA
		     ----------------------------
			 
'''
