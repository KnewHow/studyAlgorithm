#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 100 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/

typedef int vertex;        /*define the data type of the vertex*/
typedef int weightType;    /*define the data type of the weight*/
typedef char dataType; /*define the data type of the vertex value*/

/*define the data structure of the Edge*/
typedef struct eNode *ptrToENode;
typedef struct eNode{
    vertex v1,v2;           /*two vertex between the edge <v1,v2>*/
    weightType weight;      /*the value of the edge's weigth */
};
typedef ptrToENode edge;

/*define the data structure adjacent table node*/
typedef struct adjNode *ptrToAdjNode;
typedef struct adjNode{
    vertex adjVerx;         /*the index of the vertex*/
    weightType weight;      /*the value of the weight*/
    ptrToENode next;        /*the point to point the next node*/
};

/*define the data structure of the adjacent head*/
typedef struct vNode{
    ptrToAdjNode head;      /*the point to point the adjacent table node*/
    dataType data;          /*the space to store the name of the vertex,but some time the vertex has no names*/
}adjList[MAX_VERTEX_NUM];

/*define the data structure of graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode{
    int vertex_number;  /*the number of the vertex*/
    int edge_nunber;    /*the number of the edge*/
    adjList g;          /*adjacent table*/
};
typedef ptrToGNode adjacentTableGraph;             /*a graph show by adjacent table*/


/*
create a graph given the vertex number.
@param vertexNum The verter number of the graph
@return a graph with vertex but no any egdgs
*/
adjacentTableGraph createGraph(int vertexNum){
    adjacentTableGraph graph;

    vertex v;
    graph =(adjacentTableGraph)malloc(sizeof(struct gNode));
    graph->vertex_number=vertexNum;
    graph->vertex_number=0;
    /*initialize the adjacent table*/
    for(v=0;v<graph->vertex_number;v++){
        graph->g[v].head=NULL;
    }
    return graph;
}

/*
insert a edge to graph.We will distinct oriented graph and undirected graph
The e->v1 and e->v2 are the vertexs' indexs in the adjacent table
@param graph The graph you want to insert edge
@param e The edge you want to insert the graph
@param isOriented Whether the graph is oriented graph.If the graph is oriented
        we will set adjacent table graph[v1]->head=v2 and set graph[v1].head=v2
        otherwise we only set graph[v1].head=v2
*/
void insertEdge(adjacentTableGraph graph,edge e,int isOriented){
    /*build node<v1,v2>*/
    ptrToAdjNode newNode;
    newNode =(ptrToAdjNode)malloc(sizeof(struct adjNode));
    newNode->adjVerx=e->v1;
    newNode->weight=e->weight;
    newNode->next = graph->g[e->v1].head;
    graph->g[e->v1].head=newNode;
    /*if the graph is directed graph*/
    if(!isOriented){
        newNode =(ptrToAdjNode)malloc(sizeof(struct adjNode));
        newNode->adjVerx=e->v1;
        newNode->weight = e->weight;
        newNode->next = graph->g[e->v2].head;
        graph->g[e->v1].head=newNode;
    }
}

/*
build a graph stored by adjacent table
*/
adjacentTableGraph buildGraph(){
    adjacentTableGraph graph;
    edge e;
    vertex v;
    int vertex_num,i;

    scanf("%d",&vertex_num);
    graph  = createGraph(vertex_num);
    scanf("%d",(graph->edge_nunber));
    if(!graph->edge_nunber){
        e = (edge)malloc(sizeof(struct eNode));
        for(i=0;i<graph->edge_nunber;i++){
            scanf("%d %d %d",&e->v1,&e->v2,&e->weight);
            insertEdge(graph,e,1);
        }
    }

    /*if the vertex has name*/
    for(i=0;i<graph->vertex_number;i++){
        scanf("%c",&(graph->g[i].data));
    }
    return graph;
}


int main(){
    printf("just test");
}
