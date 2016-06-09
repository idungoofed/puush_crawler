#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main() {
  printf("Code: %d\n", system("wget -q puu.sh/0000t5.jpg"));
  printf("Size of pthread: %lu\n", sizeof(pthread_t));
  return 0;
}
