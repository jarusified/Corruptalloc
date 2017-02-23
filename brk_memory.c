#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
  void *current_brk, *tmp_brk = NULL;
  printf("pid : %d ", getpid());
  tmp_brk = current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();

  if(sbrk(40960)<0){
    perror("sbrk 1");
  }
  
  current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();


  if(sbrk(40960)<0){
    perror("sbrk 2");
  }


  current_brk = sbrk(0);
  printf("current location :%p\n",  current_brk);
  getchar();

  return 0;
}
