// Calloc - a function which initialises the memory to 0 as well as allocate like malloc

void *calloc(size_t size, size_t n){
  size_t total = n * size;
  void *mem = malloc(total);
  if(!mem){
    return NULL;
  }
  return memset(p, 0, total);
}


/* 2 security problems:

1. Multiplication over-flow when we multiply n and size.
2. Malloc can allocate 0 sometimes when memory is being fetched from the system directly. This
   can lead to unnecessary computation complexity.
*/

size_t safemul(size_t n, size_t size)
{
	unsigned lz_n = nlz(n);
	unsigned lz_size = nlz(size);
	size_t t;

	if (lz_n + lz_size <= 62) goto overflow;
	t = n * (size/2);
	
	if ((s_size_t)t < 0) goto overflow;

	t += t;
	
      	if (size & 1)
	{
		t += n;
		if (t < n) goto overflow;
	}
	
	return t;
	
overflow:
	return ~0ULL;	
}


/* another safe multiplication implementation - Uses 128 bit to check for overflow, Doesnt work with all 
   compilers. */

static size_t safemul(size_t n, size_t size)
{
	__uint128_t dn = n;
	__uint128_t dsize = size;
	__uint128_t drsize = dn*dsize;
	
	if (drsize >> 64) return ~0ULL;

	return drsize;
}
