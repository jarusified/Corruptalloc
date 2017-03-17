# Memalign : How to make it random

Memory allocators like ptmalloc handle the memory alignment of mmapped chunks by using padding. Worst case padding is provided by \_int\_malloc.
	
	m = (char *) (_int_malloc (av, nb + alignment + MINSIZE));
	if(chunk_is_mmapped()):
		newp->prev_size = p->prev_size + leadsize;
		set_head (newp, newsize | IS_MMAPPED);

IS_MMAPPED bit is set whenever the corresponding memory chunk is mmapped. This helps while we try to free the memory. 

	munmap(mchunkptr p):
		uintptr_t block = (uintptr_t) p - p->prev_size;
		size_t total_size = p->prev_size + size;
		
		if (__builtin_expect (((block | total_size) & (GLRO (dl_pagesize) - 1)) != 0, 0))
			malloc_printerr (check_action, "munmap_chunk(): invalid pointer", chunk2mem (p), NULL)
			return
			
\__builtin\_expect is one of the builtin functions provided by glibc gcc.It does a bit wise OR operation on block and total\_size.

GLRO is a macro defined as 
	
	#define GLRO(x) _##x
	
It concatenates "\_" and x to form "\_x"
