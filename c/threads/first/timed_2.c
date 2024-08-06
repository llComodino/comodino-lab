#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>
#include <immintrin.h>

#define NUM_RUNS 100
#define STRING_LENGTH 100000000
#define NUM_THREADS 2

struct ThreadArgs {
  char* str;
  size_t start;
  size_t end;
  char ch;
  int count;
};

pthread_t threads[NUM_THREADS];
struct ThreadArgs thread_args[NUM_THREADS];

void* count_char_avx(void* arg);
double run_threaded(char* str, char ch);
double run_non_threaded(char* str, char ch);

int main() {
  // Align AVX
  char *str = aligned_alloc(32, STRING_LENGTH + 32);

  srand(time(NULL));
  for (int i = 0; i < STRING_LENGTH; i++) {
    str[i] = 'a' + (rand() % 26);
  }

  double threaded_total = 0, non_threaded_total = 0;

  for (int i = 0; i < NUM_RUNS; i++) {
    threaded_total += run_threaded(str, 'a');
    non_threaded_total += run_non_threaded(str, 'a');
  }

  printf("Average threaded time: %f seconds\n", threaded_total / NUM_RUNS);
  printf("Average non-threaded time: %f seconds\n", non_threaded_total / NUM_RUNS);

  free(str);

  return 0;
}

void* count_char_avx(void* arg) {
  struct ThreadArgs* args = (struct ThreadArgs*)arg;
  __m256i compare = _mm256_set1_epi8(args->ch);
  __m256i count_vec = _mm256_setzero_si256();

  for (size_t i = args->start; i < args->end; i += 32) {
    __m256i data = _mm256_loadu_si256((__m256i*)&args->str[i]);
    __m256i match = _mm256_cmpeq_epi8(data, compare);
    count_vec = _mm256_add_epi8(count_vec, match);
  }

  int counts[32];
  _mm256_storeu_si256((__m256i*)counts, count_vec);

  for (int i = 0; i < 32; i++) {
    args->count += counts[i];
  }

  for (size_t i = args->end - (args->end % 32); i < args->end; i++) {
    if (args->str[i] == args->ch) {
      args->count++;
    }
  }

  return NULL;
}

double run_threaded(char* str, char ch) {
  size_t chunk_size = STRING_LENGTH / NUM_THREADS;

  clock_t start = clock();

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_args[i].str = str;
    thread_args[i].start = i * chunk_size;
    thread_args[i].end = (i == NUM_THREADS - 1) ? STRING_LENGTH : (i + 1) * chunk_size;
    thread_args[i].ch = ch;
    thread_args[i].count = 0;
    pthread_create(&threads[i], NULL, count_char_avx, (void*)&thread_args[i]);
  }

  int total_count = 0;
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    total_count += thread_args[i].count;
  }

  clock_t end = clock();

  return ((double) (end - start)) / CLOCKS_PER_SEC;
}

double run_non_threaded(char* str, char ch) {
  struct ThreadArgs args = {str, 0, STRING_LENGTH, ch, 0};

  clock_t start = clock();
  count_char_avx((void*)&args);
  clock_t end = clock();

  return ((double) (end - start)) / CLOCKS_PER_SEC;
}


