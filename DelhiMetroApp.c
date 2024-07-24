#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX 100

typedef struct {
    int distance[MAX][MAX];
    int time[MAX][MAX];
    int num_vertices;
    char vertices[MAX][50];
} Graph;

int findVertexIndex(Graph *g, char *vname) {
    for (int i = 0; i < g->num_vertices; i++) {
        if (strcmp(g->vertices[i], vname) == 0)
            return i;
    }
    return -1;
}

void addVertex(Graph *g, char *vname) {
    strcpy(g->vertices[g->num_vertices], vname);
    g->num_vertices++;
}

void addEdge(Graph *g, char *vname1, char *vname2, int dist, int time) {
    int idx1 = findVertexIndex(g, vname1);
    int idx2 = findVertexIndex(g, vname2);
    g->distance[idx1][idx2] = dist;
    g->distance[idx2][idx1] = dist;
    g->time[idx1][idx2] = time;
    g->time[idx2][idx1] = time;
}

void initializeGraph(Graph *g) {
    g->num_vertices = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            g->distance[i][j] = INT_MAX;
            g->time[i][j] = INT_MAX;
        }
    }
}

void displayStations(Graph *g) {
    printf("\n***********************************************************************\n");
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%d. %s\n", i + 1, g->vertices[i]);
    }
    printf("***********************************************************************\n");
}

void displayMap(Graph *g) {
    printf("\t Delhi Metro Map\n");
    printf("\t------------------\n");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < g->num_vertices; i++) {
        printf("%s =>\n", g->vertices[i]);
        for (int j = 0; j < g->num_vertices; j++) {
            if (g->distance[i][j] != INT_MAX) {
                printf("\t%s\t%d\n", g->vertices[j], g->distance[i][j]);
            }
        }
    }
    printf("----------------------------------------------------\n");
}

int minDistance(int dist[], int sptSet[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int graph[MAX][MAX], int src, int V, int dist[]) {
    int sptSet[MAX];
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = 1;
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

void getShortestDistance(Graph *g, char *src, char *dest) {
    int srcIdx = findVertexIndex(g, src);
    int destIdx = findVertexIndex(g, dest);
    int dist[MAX];
    dijkstra(g->distance, srcIdx, g->num_vertices, dist);
    printf("Shortest distance from %s to %s is %d KM\n", src, dest, dist[destIdx]);
}

void getShortestTime(Graph *g, char *src, char *dest) {
    int srcIdx = findVertexIndex(g, src);
    int destIdx = findVertexIndex(g, dest);
    int time[MAX];
    dijkstra(g->time, srcIdx, g->num_vertices, time);
    printf("Shortest time from %s to %s is %d minutes\n", src, dest, time[destIdx]);
}

void createMetroMap(Graph *g) {
    addVertex(g, "Noida Sector 62~B");
    addVertex(g, "Botanical Garden~B");
    addVertex(g, "Yamuna Bank~B");
    addVertex(g, "Rajiv Chowk~BY");
    addVertex(g, "Vaishali~B");
    addVertex(g, "Moti Nagar~B");
    addVertex(g, "Janak Puri West~BO");
    addVertex(g, "Dwarka Sector 21~B");
    addVertex(g, "Huda City Center~Y");
    addVertex(g, "Saket~Y");
    addVertex(g, "Vishwavidyalaya~Y");
    addVertex(g, "Chandni Chowk~Y");
    addVertex(g, "New Delhi~YO");
    addVertex(g, "AIIMS~Y");
    addVertex(g, "Shivaji Stadium~O");
    addVertex(g, "DDS Campus~O");
    addVertex(g, "IGI Airport~O");
    addVertex(g, "Rajouri Garden~BP");
    addVertex(g, "Netaji Subhash Place~PR");
    addVertex(g, "Punjabi Bagh West~P");

    addEdge(g, "Noida Sector 62~B", "Botanical Garden~B", 8, 8);
    addEdge(g, "Botanical Garden~B", "Yamuna Bank~B", 10, 10);
    addEdge(g, "Yamuna Bank~B", "Vaishali~B", 8, 8);
    addEdge(g, "Yamuna Bank~B", "Rajiv Chowk~BY", 6, 6);
    addEdge(g, "Rajiv Chowk~BY", "Moti Nagar~B", 9, 9);
    addEdge(g, "Moti Nagar~B", "Janak Puri West~BO", 7, 7);
    addEdge(g, "Janak Puri West~BO", "Dwarka Sector 21~B", 6, 6);
    addEdge(g, "Huda City Center~Y", "Saket~Y", 15, 15);
    addEdge(g, "Saket~Y", "AIIMS~Y", 6, 6);
    addEdge(g, "AIIMS~Y", "Rajiv Chowk~BY", 7, 7);
    addEdge(g, "Rajiv Chowk~BY", "New Delhi~YO", 1, 1);
    addEdge(g, "New Delhi~YO", "Chandni Chowk~Y", 2, 2);
    addEdge(g, "Chandni Chowk~Y", "Vishwavidyalaya~Y", 5, 5);
    addEdge(g, "New Delhi~YO", "Shivaji Stadium~O", 2, 2);
    addEdge(g, "Shivaji Stadium~O", "DDS Campus~O", 7, 7);
    addEdge(g, "DDS Campus~O", "IGI Airport~O", 8, 8);
    addEdge(g, "Moti Nagar~B", "Rajouri Garden~BP", 2, 2);
    addEdge(g, "Punjabi Bagh West~P", "Rajouri Garden~BP", 2, 2);
    addEdge(g, "Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3, 3);
}

int main() {
    Graph g;
    initializeGraph(&g);
    createMetroMap(&g);

    int choice;
    
    while (1) {
        printf("\t\t\t****WELCOME TO THE METRO APP*****\n");
        printf("\t\t\t\t~~LIST OF ACTIONS~~\n\n");
        printf("1. LIST ALL THE STATIONS IN THE MAP\n");
        printf("2. SHOW THE METRO MAP\n");
        printf("3. GET SHORTEST DISTANCE FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        printf("4. GET SHORTEST TIME TO REACH FROM A 'SOURCE' STATION TO 'DESTINATION' STATION\n");
        printf("5. EXIT THE MENU\n");
        printf("\nENTER YOUR CHOICE FROM THE ABOVE LIST (1 to 5) : ");
        scanf("%d", &choice);
        printf("***********************************************************\n");

        char src[50], dest[50];

        switch (choice) {
            case 1:
                displayStations(&g);
                break;
            case 2:
                displayMap(&g);
                break;
            case 3:
                printf("ENTER THE SOURCE STATION: ");
                scanf("%s", src);
                printf("ENTER THE DESTINATION STATION: ");
                scanf("%s", dest);
                getShortestDistance(&g, src, dest);
                break;
            case 4:
                printf("ENTER THE SOURCE STATION: ");
                scanf("%s", src);
                printf("ENTER THE DESTINATION STATION: ");
                scanf("%s", dest);
                getShortestTime(&g, src, dest);
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Enter a valid choice!\n");
                break;
        }
        printf("\n***********************************************************\n");
    }

    return 0;
}
