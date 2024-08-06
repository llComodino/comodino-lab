#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define LEN 100000000

typedef struct {
  const char *string;
  char c;
  int count;
} ThreadData;

char* random_string(size_t len);
void* occourrences_of_char(void *args);

int main(void) {
  ThreadData *set_1 = NULL;
  if ( (set_1 = (ThreadData*)malloc(sizeof(ThreadData))) == NULL ) {
    fprintf(stderr, "Not enough mem for args");
    exit(1);
  }

  ThreadData *set_2 = NULL;
  if ( (set_2 = (ThreadData*)malloc(sizeof(ThreadData))) == NULL ) {
    fprintf(stderr, "Not enough mem for args");
    exit(1);
  }

  set_1->string = random_string(LEN);
  set_2->string = random_string(LEN);
  set_1->c = 'G';
  set_2->c = 'P';
  set_1->count = 0;
  set_2->count = 0;

  pthread_t thread_1;
  pthread_t thread_2;

  pthread_create(&thread_1, NULL, occourrences_of_char, (void*)set_1);
  pthread_create(&thread_2, NULL, occourrences_of_char, (void*)set_2);

  pthread_join(thread_1, NULL);
  pthread_join(thread_2, NULL);

  puts("THREADED:");
  printf("Thread 1: %d occourrences of %c\n", set_1->count, set_1->c);
  printf("Thread 2: %d occourrences of %c\n", set_2->count, set_2->c);
  return 0;
}

char* random_string(size_t len) {
  char *str = NULL;

  if ( (str = (char*)malloc(sizeof(char) * len)) == NULL ) {
    fprintf(stderr, "Not enough mem for the string");
    exit(1);
  }

  for (size_t i = 0; i < len - 1; i++) {
    *(str + i) = 67 + rand() % 24;
  }

  *(str + len - 1) = '\0';
  return str;
}

void* occourrences_of_char(void *args) {
  ThreadData *data = (ThreadData*)args;

  int counter = 0;
  for (size_t i = 0; *(data->string + i) != '\0'; i++) {
    if (*(data->string + i) == (data->c)) ++counter;
  }

  data->count = counter;
  return NULL;
}
