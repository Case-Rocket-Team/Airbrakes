#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int front, rear;
    int *arr;
    int max_size;
} CircularQueue;

void init(CircularQueue *q, int size) {
    q->front = q->rear = -1;
    q->arr = (int *) malloc(size * sizeof(int));
    q->max_size = size;
}

int is_empty(CircularQueue q) {
    return q.front == -1;
}

int is_full(CircularQueue q) {
    return (q.rear + 1) % q.max_size == q.front;
}

void enqueue(CircularQueue *q, int item) {
    // if (is_full(*q)) {
    //     printf("Error: queue is full\n");
    //     return;
    // }
    if (is_empty(*q))
        q->front = q->rear = 0;
    else
        q->rear = (q->rear + 1) % q->max_size;
    q->arr[q->rear] = item;
}

int dequeue(CircularQueue *q) {
    if (is_empty(*q)) {
        printf("Error: queue is empty\n");
        return -1;
    }
    int item = q->arr[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front = (q->front + 1) % q->max_size;
    return item;
}

void print_queue(CircularQueue q) {
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return;
    }
    printf("Queue contents:\n");
    for (int i = q.front; i != q.rear; i = (i + 1) % q.max_size)
        printf("%d ", q.arr[i]);
    printf("%d\n", q.arr[q.rear]);
}

void print_for_testing(CircularQueue q) {
    printf("Full queue:\n");
    for (int i = 0; i < q.max_size; i++) {
        printf("%d ", q.arr[i]);
    }
}

int* last_10_values(CircularQueue q) {
    static int last_values[10];
    if (is_empty(q)) {
        printf("Queue is empty\n");
        return last_values;
    }
    printf("Last 10 values:\n");
    int i = q.rear;
    for (int j = 0; j < 10 && j < q.max_size; j++) {
        last_values[j] = q.arr[i];
        i = (i - 1 + q.max_size) % q.max_size;
    }
    return last_values;
}

void read_last_10_values(int* list) {
    for (int i = 0; i < 10; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
}

int main() {
    int size;
    printf("Enter the size of the queue: ");
    scanf("%d", &size);
    CircularQueue q;
    init(&q, size);
    for (int i = 0; i < q.max_size + 5; i++) {
        enqueue(&q, i + 1);
    }
    int* data = last_10_values(q);
    read_last_10_values(data);
    print_for_testing(q);
    free(q.arr);
    return 0;
}
