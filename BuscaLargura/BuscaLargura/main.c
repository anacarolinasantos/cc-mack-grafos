//Ana Carolina dos Santos Silva, TIA: 31525962
//Michelle Faifer dos Santos, TIA: 31581463
//Piera Carolina Marchesini Dutra, TIA: 31581773

/*Source to adjacency list and insertion methods of edges and graph creation:
 https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html
*/
 
/*Source to Queue:
 http://www.cprogressivo.net/2014/05/Filas-em-C-Como-Programar-Tutorial-Estrutura-de-Dados-Dinamica-Queue.html
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define vertex int

//Enumeration to define vetices' colors
enum color {
    white = 0,
    gray = 1,
    black = 2
};

//MARK: - Adjacency list methods
/**/
typedef struct node *link;
struct node {
    vertex w;
    link next;
};

/*The graph is formed by vertices, that have all the information that belong to it (the identifier, distance to get to the vertex, color, the parent -that is the antecessor to get to the vertex- and a list of all the vertexes adjacent)*/
typedef struct vert *vert;
struct vert {
    vertex v;
    int distance;
    enum color colorVert;
    vert parent;
    link *adjList;
};

/*The graph is composed by the number of vertices, edges and a list of all vertices*/
typedef struct {
    int V;
    int A;
    vert *vert;
} *Graph;

//MARK: - Graph methods
/*The method insert a new edge on the graph, creating a node with the identifier w, and putting this node at the begging of the list*/
static link NEWedge(vertex w, link next) {
    link a = malloc(sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

/**/
static vert NEWvert(vertex v){
    vert vertG = malloc(sizeof(vert));
    vertG->v = v;
    vertG->adjList = (link*) malloc(sizeof (link));;
    return vertG;
}

/**/
Graph GRAPHinit(int V) {
    vertex v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->vert = malloc( V * sizeof (link));
    
    for (v = 0; v < V; v++){
        G->vert[v] = NEWvert(v);
    }
    
    return G;
}

/**/
void GRAPHinsertEdge( Graph G, vertex v, vertex w) {
    link a;
    
    for (a = G->vert[v]->adjList[0]; a != NULL; a = a->next)
        if (a->w == w) return;
    
    G->vert[v]->adjList[0] = NEWedge(w, G->vert[v]->adjList[0]);
    
    G->A++;
}

//MARK: - Queue methods
/**/
struct NodeQueue{
    int num;
    struct NodeQueue *next;
};
typedef struct NodeQueue nodeQueue;
int size;

void initialize(nodeQueue *Queue) {
    Queue->next = NULL;
    size=0;
}

/**/
int isEmpty(nodeQueue *Queue){
    if(Queue->next == NULL)
        return 1;
    else
        return 0;
}

/**/
nodeQueue *allocate(vertex num) {
    nodeQueue *new=(nodeQueue *) malloc(sizeof(nodeQueue));
    if(!new){
        printf("Sem memoria disponivel!\n");
        exit(1);
    }else{
        new->num = num;
        return new;
    }
}

/**/
void insert(nodeQueue *Queue, vertex num) {
    nodeQueue *new=allocate(num);
    new->next = NULL;
    
    if(isEmpty(Queue))
        Queue->next=new;
    else{
        nodeQueue *tmp = Queue->next;
        
        while(tmp->next != NULL)
            tmp = tmp->next;
        
        tmp->next = new;
    }
    size++;
}

/**/
nodeQueue *removeQueue(nodeQueue *Queue) {
    if(Queue->next == NULL){
        printf("Fila ja esta vazia\n");
        return NULL;
    }else{
        nodeQueue *tmp = Queue->next;
        Queue->next = tmp->next;
        size--;
        return tmp;
    }
    
}

/**/
void searchOnWidth(Graph G, vertex s) {
    vert currentVertex;
    link currentEdge;
    vertex v;
    nodeQueue *queue = (nodeQueue *) malloc(sizeof(nodeQueue));
    
    for (v = 0; v < G->V; v++){
        currentVertex = G->vert[v];
        currentVertex->distance = INT_MAX;
        currentVertex->colorVert = white;
        currentVertex->parent = NULL;
    }
    
    G->vert[s]->colorVert = gray;
    G->vert[s]->distance = 0;
    G->vert[s]->parent = NULL;
    
    initialize(queue);
    insert(queue, s);
    
    while (!isEmpty(queue)) {
        nodeQueue *nodeQ = removeQueue(queue);
        
        currentVertex = G->vert[nodeQ->num];
        currentEdge = currentVertex->adjList[0];
        
        while (currentEdge != NULL) {
            
            if (G->vert[currentEdge->w]->colorVert == white) {
                
                G->vert[currentEdge->w]->colorVert = gray;
                G->vert[currentEdge->w]->distance = currentVertex->distance+1;
                G->vert[currentEdge->w]->parent = G->vert[nodeQ->num];
                
                insert(queue, currentEdge->w);
            }
            currentEdge = currentEdge->next;
        }
        
        G->vert[nodeQ->num]->colorVert = black;
    }
    
}

/**/
int main(int argc, const char * argv[]) {
    Graph g;
    int i = 0;
    
    g = GRAPHinit(6);
    
    GRAPHinsertEdge(g, 0, 1);
    GRAPHinsertEdge(g, 0, 3);
    GRAPHinsertEdge(g, 0, 4);
    GRAPHinsertEdge(g, 1, 0);
    GRAPHinsertEdge(g, 1, 2);
    GRAPHinsertEdge(g, 2, 1);
    GRAPHinsertEdge(g, 2, 5);
    GRAPHinsertEdge(g, 3, 0);
    GRAPHinsertEdge(g, 3, 4);
    GRAPHinsertEdge(g, 3, 5);
    GRAPHinsertEdge(g, 4, 0);
    GRAPHinsertEdge(g, 4, 3);
    GRAPHinsertEdge(g, 4, 5);
    GRAPHinsertEdge(g, 5, 2);
    GRAPHinsertEdge(g, 5, 3);
    GRAPHinsertEdge(g, 5, 4);

//    GRAPHinsertEdge(g, 0, 1);
//    GRAPHinsertEdge(g, 0, 2);
//    GRAPHinsertEdge(g, 1, 0);
//    GRAPHinsertEdge(g, 1, 2);
//    GRAPHinsertEdge(g, 1, 3);
//    GRAPHinsertEdge(g, 2, 0);
//    GRAPHinsertEdge(g, 2, 1);
//    GRAPHinsertEdge(g, 2, 3);
//    GRAPHinsertEdge(g, 3, 1);
//    GRAPHinsertEdge(g, 3, 2);
//    GRAPHinsertEdge(g, 3, 4);
//    GRAPHinsertEdge(g, 4, 3);
//    GRAPHinsertEdge(g, 4, 5);
//    GRAPHinsertEdge(g, 5, 4);
    
    searchOnWidth(g, 0);
    
    for (i = 0; i < g->V; i++) {
        printf("distancia: %d até o vértice: %d \n", g->vert[i]->distance, i);
    }
    
    return 0;
}
