//Ana Carolina dos Santos Silva, TIA: 31525962
//Michelle Faifer dos Santos, TIA: 31581463
//Piera Carolina Marchesini Dutra, TIA: 31581773

//COMENTARIOS EM INGLES

//Fonte Lista Ligada e métodos de inserção de aresta e criação do grafo: https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html
//Fonte Fila: http://www.cprogressivo.net/2014/05/Filas-em-C-Como-Programar-Tutorial-Estrutura-de-Dados-Dinamica-Queue.html

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define vertex int

//MARK: - Métodos de Lista Ligada
enum color {
    white = 0,
    gray = 1,
    black = 2
};

typedef struct node *link;
struct node {
    vertex w;
    link next;
    int distance;
    enum color colorNode;
    link parent;
};

/* A lista de adjacência de um vértice v é composta por nós do tipo node. Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. Um link é um ponteiro para um node. */
typedef struct {
    int V;
    int A;
    link *adj;
} *Graph;

//MARK: - Métodos do grafo
/* A função NEWnode() recebe um vértice w e o endereço next de um nó e devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */
static link NEWnode( vertex w, link next) {
    link a = malloc( sizeof (struct node));
    a->w = w;
    a->next = next;
    return a;
}

/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit( int V) {
    vertex v;
    Graph G = malloc( sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc( V * sizeof (link));
    for (v = 0; v < V; v++)
        G->adj[v] = NULL;
    return G;
}
/* REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA: A função GRAPHinsertArc() insere um arco v-w no grafo G. A função supõe que v e w são distintos, positivos e menores que G->V. Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertEdge( Graph G, vertex v, vertex w) {
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w) return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

//MARK: - Métodos de fila
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

int isEmpty(nodeQueue *Queue){
    if(Queue->next == NULL)
        return 1;
    else
        return 0;
}

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

void searchOnWidth(Graph G, vertex s) {
    link nextVertex;
    vertex v;
    nodeQueue *queue = (nodeQueue *) malloc(sizeof(nodeQueue));
    
    for (v = 0; v < G->V; v++){
        nextVertex = G->adj[v];
        while (nextVertex != NULL) {
            nextVertex->distance = INT_MAX;
            nextVertex->colorNode = white;
            nextVertex->parent = NULL;
            
            nextVertex = nextVertex->next;
        }
    }
    
    G->adj[s]->colorNode = gray;
    G->adj[s]->distance = 0;
    G->adj[s]->parent = NULL;
    
    initialize(queue);
    insert(queue, s);
    
    while (!isEmpty(queue)) {
        
        nodeQueue *nodeQ = removeQueue(queue);
        
        nextVertex = G->adj[nodeQ->num];
        
        while (nextVertex != NULL) {
            
            if (nextVertex->colorNode == white) {
                
                printf("%d\n", G->adj[nodeQ->num]->distance);
                
                nextVertex->colorNode = gray;
                nextVertex->distance = G->adj[nextVertex->w]->distance+1;
//                nextVertex->distance = G->adj[nextVertex->w]->distance+1;
                nextVertex->parent = G->adj[nodeQ->num];
                
                insert(queue, nextVertex->w);
            }
            nextVertex = nextVertex->next;
        }
        
        G->adj[nodeQ->num]->colorNode = black;
    }
    
}


int main(int argc, const char * argv[]) {
    Graph g;
    int i = 0;
    
    g = GRAPHinit(6);
    
    //Arestas sem repetição
//    GRAPHinsertEdge(g, 0, 1);
//    GRAPHinsertEdge(g, 0, 2);
//    GRAPHinsertEdge(g, 1, 2);
//    GRAPHinsertEdge(g, 2, 3);
//    GRAPHinsertEdge(g, 1, 3);
//    GRAPHinsertEdge(g, 3, 4);
//    GRAPHinsertEdge(g, 4, 5);
    
    //Arestas repetidas
    GRAPHinsertEdge(g, 0, 1);
    GRAPHinsertEdge(g, 0, 2);
    GRAPHinsertEdge(g, 1, 0);
    GRAPHinsertEdge(g, 1, 2);
    GRAPHinsertEdge(g, 1, 3);
    GRAPHinsertEdge(g, 2, 0);
    GRAPHinsertEdge(g, 2, 1);
    GRAPHinsertEdge(g, 2, 3);
    GRAPHinsertEdge(g, 3, 1);
    GRAPHinsertEdge(g, 3, 2);
    GRAPHinsertEdge(g, 3, 4);
    GRAPHinsertEdge(g, 4, 3);
    GRAPHinsertEdge(g, 4, 5);
    GRAPHinsertEdge(g, 5, 4);
    
    searchOnWidth(g, 0);
    
    for (; i < g->V; i++) {
        printf("%d \n", g->adj[i]->distance);
    }
    
    
    return 0;
}
