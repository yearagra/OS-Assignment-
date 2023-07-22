#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>

#define kernel_2d_memcpy 448

int main(int argc, char **argv){

  float originalMatrix[3][3] = {
      {6.34, 2.56, 3.67},
      {5.45, 6.47, 7.25},
      {9.59, 1.61, 0.89}
      
  };
  float copyMatrix[3][3];

  int sys = syscall(kernel_2d_memcpy,copyMatrix,originalMatrix,3,3);

  if(sys == 0){
    printf("System call was Successful.\n");
  }else{
    perror("kernel_2d_memcpy");
    return -1;
  }
  printf("\nThe Copied Matrix is :\n");
  for(int i=0;i<3;++i){
    for(int j=0;j<3;++j){
      printf("%f ",copyMatrix[i][j]);
    }
    printf("\n");
  }
  return 0;
}