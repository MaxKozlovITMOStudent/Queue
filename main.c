#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct quque {
  int *elements;
  int head;
  int tail;
  int size;
  int capacity;
} quque;

quque *createQueue(int capacity) {
  quque *q = malloc(sizeof(quque));
  if (!q) {
    return NULL;
  }
  q->elements = malloc(sizeof(int) * capacity);
  if (!q->elements) {
    free(q);
    return NULL;
  }
  q->head = 0;
  q->tail = 0;
  q->capacity = capacity;
  q->size = 0;
  return q;
}

int isEmpty(quque *q) { return q->size == 0; }
int enquque(quque *q, int value) {
  if (q->size == q->capacity) {
    return 0;
  }
  q->elements[q->tail] = value;
  q->tail = (q->tail + 1) % q->capacity;
  q->size++;
  return 1;
}
int dequque(quque *q, int *value) {
  if (q->size == 0) {
    return 0;
  }
  *value = q->elements[q->head];
  q->head = (q->head + 1) % q->capacity;
  q->size--;
  return 1;
}
int element(quque *q) {
  if (isEmpty(q)) {
    printf("We havent first element");
    return 0;
  }
  return q->elements[q->head];
}
int size(quque *q) { return q->size; }
void clean(quque *q) {
  free(q->elements);
  free(q);
}
void clear(quque *q) {
  q->head = 0;
  q->tail = 0;
  q->size = 0;
}
void printQueue(quque *q) {
  printf("Queue [size=%d, capacity=%d]: ", q->size, q->capacity);
  for (int i = 0; i < q->size; i++) {
    int index = (q->head + i) % q->capacity;
    printf("%d ", q->elements[index]);
  }
  printf("\n");
}
int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s <test_file>\n", argv[0]);
    return 1;
  }
  FILE *file = fopen(argv[1], "r");
  if (!file) {
    fprintf(stderr, "Cannot open file: %s\n", argv[1]);
    return 1;
  }
  int capacity;
  fscanf(file, "%d", &capacity);
  quque *q = createQueue(capacity);
  if (!q) {
    fprintf(stderr, "Memory allocation failed\n");
    fclose(file);
    return 1;
  }
  char operation[20];
  int value;
  while (fscanf(file, "%s", operation) != EOF) {
    if (strcmp(operation, "enquque") == 0) {
      fscanf(file, "%d", &value);
      if (enquque(q, value)) {
      } else {
        printf("Queue full, cannot enqueue: %d\n", value);
      }
    } else if (strcmp(operation, "dequque") == 0) {
      if (dequque(q, &value)) {

      } else {
        printf("Queue empty, cannot dequeue\n");
      }
    } else if (strcmp(operation, "element") == 0) {
      printf("Front element: %d\n", element(q));
    } else if (strcmp(operation, "size") == 0) {
      printf("Size: %d\n", size(q));
    } else if (strcmp(operation, "isEmpty") == 0) {
      if (isEmpty(q)) {
        printf("%s", "Empty\n");
      } else {
        printf("%s", "NO empty\n");
      }
    } else if (strcmp(operation, "print") == 0) {
      printQueue(q);
    } else if (strcmp(operation, "clear") == 0) {
      clear(q);
      printf("Queue cleared\n");
    } else {
      printf("other operation\n");
    }
  }
  fclose(file);
  clean(q);
  return 0;
}
