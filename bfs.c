#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Queue implementation for BFS
struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
};

// Initialize queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->rear == -1;
}

// Add an item to the queue
void enqueue(struct Queue* queue, int value) {
    if (queue->rear == MAX_SIZE - 1)
        printf("Queue is full\n");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = value;
    }
}

// Remove an item from the queue
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty\n");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
    }
    return item;
}

// BFS function
void BFS(int** graph, int vertices, int startVertex) {
    struct Queue* queue = createQueue();
    int visited[MAX_SIZE] = {0};

    visited[startVertex] = 1;
    enqueue(queue, startVertex);

    printf("BFS Traversal: ");
    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        for (int i = 0; i < vertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(queue, i);
            }
        }
    }
    printf("\n");
}

int main() {
    int vertices, startVertex;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);

    // Allocate memory for the graph
    int** graph = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph[i] = (int*)malloc(vertices * sizeof(int));
    }

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter the starting vertex: ");
    scanf("%d", &startVertex);

    BFS(graph, vertices, startVertex);

    // Free allocated memory
    for (int i = 0; i < vertices; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}

