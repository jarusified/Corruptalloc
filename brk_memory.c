#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
  void *current_brk, *tmp_brk = NULL;
  printf("pid : %d ", getpid());
  tmp_brk = current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();

  brk(current_brk+4096);

  current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();

  brk(current_brk+4096);

  current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();

  return 0;
}
