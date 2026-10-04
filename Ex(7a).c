#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    struct Node* adjLists[MAX_VERTICES];
    int visited[MAX_VERTICES];
};

struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph() {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void BFS(struct Graph* graph, int startVertex) {
    int queue[MAX_VERTICES];
    int front = 0;
    int rear = 0;

    graph->visited[startVertex] = 1;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];

        printf("Visited %d\n", currentVertex);

        struct Node* temp = graph->adjLists[currentVertex];

        while (temp) {
            int connectedVertex = temp->vertex;

            if (graph->visited[connectedVertex] == 0) {
                graph->visited[connectedVertex] = 1;
                queue[rear++] = connectedVertex;
            }

            temp = temp->next;
        }
    }
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < 4; v++) {
        struct Node* temp = graph->adjLists[v];

        printf("\nAdjacency list of vertex %d\n", v);

        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }

        printf("NULL\n");
    }
}

int main() {
    struct Graph* graph = createGraph();

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);

    printf("Graph:\n");
    printGraph(graph);

    printf("\nBFS Traversal starting from vertex 0:\n");
    BFS(graph, 0);

    return 0;
}