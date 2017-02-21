# Malloc Library analysis

[Curation of malloc implementations](https://github.com/emeryberger/Malloc-Implementations/)
[Allocators](https://github.com/emeryberger/Malloc-Implementations/tree/master/allocators)

## Coding a Malloc - How to ?? [1] 
Lea allocator : best uniprocessor allocator.

Point of paper :

	* HeapLayer, An infrastructure to build custom allocators. [Based on C++ templates and inheritance called mixins].
	* Discusses two allocator implementations based on HeapLayer. [Lea allocator and Kingsley allocator].

Common practice : To attain high performance, programmers often write their own ad hoc custom
allocators as macros or monolithic functions in order to avoid function call overhead.

**Kingsley allocator**: 

The Kingsley allocator is a power-of-two segregated fits allocator: all allocation requests are rounded
up to the next power of two.

**Lea allocator**:

The Lea allocator is an approximate best-fit allocator that provides both high speed and low memory consumption.


**Problem**: 

Internal fragmentation (at worst case, it can allow twice the memory to be allocated). The
allocator performs no splitting (breaking large objects into smallerones) or coalescing (combining
adjacent free objects).

Previous Architectures: vmalloc and CMM

**vnalloc**: 

Vmalloc lets the programmer define multiple regions (distinct heaps) with different disciplines for each.
The programmer performs customization by supplying user-defined functions and structs that manage memory. By chaining 
these together, vmalloc does provide the possibility of composing heaps.

**CMM**: 

A programmer can create separate regions by subclassing the abstract class CmmHeap, which uses virtual methods to obtain
and reclaim memory. For every memory allocation, deallocation, and crossing of an abstraction boundary, the programmer must thus
pay the cost of one virtual method call, while in heap layers, there is no such penalty. 

The Lea allocator uses one algorithm for small objects, another for medium-sized objects, and yet another for large objects.

**Mixins**: 

Mixins overcome the limitation of a single class hierarchy, enabling the reuse of classes in different hierarchies. For instance,
we can use A in two different hierarchies, A → B and A → C (where the arrow means “inherits from”), by defining A as a mixin and
composing the classes as follows:

	class Composition1 : public A<B> {};
	class Composition2 : public A<C> {};

**Obstacks**
GCC uses obstacks as a customary memory allocation library. They are designed to take advantage of stack-like behaviour. 

## How to heap, A collection of attacks on heaps

[link](https://github.com/shellphish/how2heap)

[House of einherjar](https://github.com/shellphish/how2heap/blob/master/house_of_einherjar.c)
[House of einherjar slides](http://www.slideshare.net/codeblue_jp/cb16-matsukuma-en-68459606)]

[Breaking the heap](http://www.blackhat.com/presentations/bh-usa-07/Ferguson/Whitepaper/bh-usa-07-ferguson-WP.pdf)

## Boundary tags

## Binning


### Hoard allocator
Emery D Berger: Paper of **Reconsidering memory allocation**
The author of this memory library has written a browser named browsix which can essentially execute unix commands on the browser. 
[Browsix paper](https://arxiv.org/pdf/1611.07862.pdf)
[Browsix github](https://github.com/plasma-umass/browsix)

[Diehard](https://emeryberger.com/research/diehard/) - A library to prevent memory corruption like dangling pointers, 
buffer overflows, heap overflows, invalid frees, double frees. 
[Diehard paper](https://emeryberger.com/research/diehard/)

Conservative garbage collectors try to remove these multiple memory errors but the operation is time costly. Or one uses a more strict
C compiler and there by eliminating such errors at the code level. 
Tools like purify, valgrind only provide the location of the memory corruption, whereas diehard tries to prevent by using an 


## Glibc allocator

* Malloc uses syscalls to obtain memory from OS. 
* There are two invoking a syscall to allocate memory
	* [brk](http://man7.org/linux/man-pages/man2/sbrk.2.html)
		* change the location of program break, defines the end of process's data segment. 
		* Brk obtains memory from kernel by increasing break location. 
		* When ASLR is turned off, start_brk and brk would point to the end of data segment.
		* When ASLR is turned on, start_brk and brk would point equal to end of data segment plus a random offset.
		

## DL-Malloc 

### Malloc functions:

malloc(size_t t) -
	
	* Allocates "t" bytes and returns a pointer to the allocated memory.
	* memory is not cleared.

free(void *p) - 
	
	* frees the memory space referenced by p.
	* calling free(p) before pointer "p" is initialised leads to undefined behaviour.

realloc(void *p, size_t t) -
	
	* resizes the size of the memory pointer by p.
	* if p = NULL , it is same as malloc(t);
	* if t = 0 , it is same as free.
	
calloc(size_t nmemb, size_t t) -

	* allocates memory for an array of nmemb and returns a pointer to the allocated memory.
	* memory is set to 0.

	void calloc(size_t nmemb, size_t t){
		size_t tot = t*nmemb;
		void *mem = malloc(
	}
If the operating system did not zero out contents of physical RAM it might be possible for one process to learn about the 
memory of another process that had previously used the memory. This would be a security leak. This is the reason why sbrk 
makes the memory as 0 when it is returned for the first time. 

#### Memory allocator

* When memory cannot be allocated, a consistent recovery plan is required. Phkalloc provides "X" option that instructs the 
allocator to abort the program. (fancy return).

	extern char *malloc_options;
	malloc_options ="X";


### Security in dlmalloc :

#### What's there already:
* It doesnt allow to modify any memory locations below the base of heap. ie: static variables 
* detects most improper frees and reallocs. 

#### What's not there:
* malloc can be corrupted by corrupting static bookkeeping itself. 

Buddy allocation for memory, 
	* satisfy a memory request by split the memory into partitions.
	* seggregated allocator: divides the heap into various areas and sub-allocators parse the allocation request
	* sizes are group into classes based on powers of 2, each size is handled by a sub-allocator and has a free
	  list
	* buddy memory allocation suffer internal fragmentation because a smaller size buffer like 66 bytes would 
	  need a 128 byte buffer.
	  
C++ containers leaking:
	Some Containers leak memory, because they contain a pointer which donot delete the objects it is referring to. So we need
to release them from memory. 

	template <class T>
	void releaseitems(T &data){
		typename T::iterator i;
		for(i = c.begin(); i!=c.end(); ++i){
			delete *i;
		}
	}

#### shared_ptr (smart pointers)
std::shared_ptr is a smart pointer that retains the ownership of an object through a pointer. It overlaods the * and -> to act like 
pointers 

## References

### Papers
* [Composing High-Performance Memory Allocators](https://people.cs.umass.edu/~emery/pubs/berger-pldi2001.pdf)
* 

### Dissertations:
* [Memory Management with Explicit Regions](https://theory.stanford.edu/~aiken/publications/theses/gay.pdf)

### Books:
* [Effective C++](https://www.epiportal.com/Ebooks/Addison.Wesley.Effective.CPP.3rd.Edition.May.2005.pdf)
