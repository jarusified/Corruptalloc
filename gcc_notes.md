# GCC cheat sheet

* -pg : Creates extra code in the final binary that outputs profile information for GNU code profiler, gprof.
* -p -g : Generates exra code in the resulting binary that produces profiling information and causes gcc to generate debugging information.
* -I : specifies the directory to search the include files.
* -o : Output file.
* -c : incrementally compile and link into binary
	
		gcc -c a.c
		gcc -c b.c
		gcc -o output a.o b.o
		
* -traditional : enables the use of features of pre-ISO C.
* -fno-asm : Disables use of inline and typeof keywords.
* -fno-builtin : Disables the recognition of built-in functions that dont begin with __builtin__ prefix
	
	Built-in functions are versions of functions in Standard-C that are implemented internally by gcc. This prevent gcc from using its own versions of alloca() and memcpy().

* -ansi or -std :
	  * Disabling asm and typeof keywords.
	  * Enabling trigraphs and digraphs
	  * Disabling predefined macros
	  * Disabling the used of single line comments in C code.
	  * Disabling built-in functions that conflict with the ISO standard
	  * Disabling all GNU extensions that conflict with the standard. 
	  
* -Wformat : GCC checks all calls to the printf, scanf and other functions which use format strings. 
* -Werror : Convert warnings to hard errors. 
* -Wformat-security : Displays warnings about format string vulnerabilites.
* C++ doesn't support nested functions.
* Trampolines are used to take addresses of a nested function. 
* __builtin_apply_args() : returns a pointer to data describing how to performa a call with the same arguments as were passed to the current function. 
* __builtin_apply() : calls the function with a copy of the parameters described by args and size.
* __builtin_return() : returns the value described by retval from the containing function. 
* Optimisation techniques:
	
	* Code motion : Removes common sub-expression in the program.
		  
		  for(int i=0;i<1000;i++){
			  a *= 2;
		  }
	* Constant folding : Eliminates expressiosn that calculate a value that can already be determined when the program is compiled.
	
	
