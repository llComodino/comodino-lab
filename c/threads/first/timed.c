#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define NUM_RUNS 100
#define STRING_LENGTH 10000000

struct ThreadArgs {
  char* str;
  char ch;
  int count;
};

double run_non_threaded(char* str1, char* str2, char ch1, char ch2);
double run_threaded(char* str1, char* str2, char ch1, char ch2);
void* count_char(void* arg);

int main() {
  char *str1 = malloc(STRING_LENGTH + 1);
  char *str2 = malloc(STRING_LENGTH + 1);

  srand(time(NULL));
  for (int i = 0; i < STRING_LENGTH; i++) {
    str1[i] = 'a' + (rand() % 26);
    str2[i] = 'a' + (rand() % 26);
  }
  str1[STRING_LENGTH] = str2[STRING_LENGTH] = '\0';

  double threaded_total = 0, non_threaded_total = 0;

  for (int i = 0; i < NUM_RUNS; i++) {
    threaded_total += run_threaded(str1, str2, 'a', 'b');
    non_threaded_total += run_non_threaded(str1, str2, 'a', 'b');
  }

  printf("Average threaded time: %f seconds\n", threaded_total / NUM_RUNS);
  printf("Average non-threaded time: %f seconds\n", non_threaded_total / NUM_RUNS);

  free(str1);
  free(str2);

  return 0;
}

void* count_char(void* arg) {
  struct ThreadArgs* args = (struct ThreadArgs*)arg;
  for (int i = 0; i < STRING_LENGTH; i++) {
    if (args->str[i] == args->ch) {
      args->count++;
    }
  }
  return NULL;
}

double run_threaded(char* str1, char* str2, char ch1, char ch2) {
  pthread_t thread1, thread2;
  struct ThreadArgs args1 = {str1, ch1, 0};
  struct ThreadArgs args2 = {str2, ch2, 0};

  clock_t start = clock();

  pthread_create(&thread1, NULL, count_char, (void*)&args1);
  pthread_create(&thread2, NULL, count_char, (void*)&args2);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  clock_t end = clock();

  return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double run_non_threaded(char* str1, char* str2, char ch1, char ch2) {
  pthread_t thread1, thread2;
  struct ThreadArgs args1 = {str1, ch1, 0};
  struct ThreadArgs args2 = {str2, ch2, 0};

  clock_t start = clock();

  pthread_create(&thread1, NULL, count_char, (void*)&args1);
  pthread_join(thread1, NULL);

  pthread_create(&thread2, NULL, count_char, (void*)&args2);
  pthread_join(thread2, NULL);

  clock_t end = clock();

  return ((double) (end - start)) / CLOCKS_PER_SEC;
}
