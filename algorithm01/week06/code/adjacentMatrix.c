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

/*define the data structure of the graph*/
typedef struct gNode *ptrToGNode;
typedef struct gNode{
    int vertex_number;  /*the number of the vertex*/
    int edge_nunber;    /*the number of the edge*/
    weightType g[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   /*define the adjacent matrix of graph*/
    dataType data[MAX_VERTEX_NUM];                  /*define the dataType array to store the value of vertex*/
};
typedef ptrToGNode adjacentMatrixGraph;             /*a graph show by adjacent matrix*/

/*
create a graph given the vertex number.
@param vertexNum The verter number of the graph
@return a graph with vertex but no any egdgs
*/
adjacentMatrixGraph createGraph(int vertexNum){
    vertex v,w;
    adjacentMatrixGraph graph;
    graph =(adjacentMatrixGraph)malloc(sizeof(struct gNode));
    graph->vertex_number=vertexNum;
    graph->edge_nunber=0;
    /*initialize the adjacent matrix*/
    for(v=0;v<graph->vertex_number;v++){
        for(w=0;w<graph->vertex_number;w++){
            graph->g[v][w]= INFINITY;
        }
    }

    return graph;
}

/*
insert a edge to graph.We will distinct oriented graph and undirected graph
@param graph The graph you want to insert edge
@param e The edge you want to insert the graph
@param isOriented Whether the graph is oriented graph.If the graph is oriented
        we will set adjacent matrix [n][m]=[m][n]=edge's weight,else we only set
        the adjacent matrix [n][m]=edge's weight
*/
void inserEdge(adjacentMatrixGraph graph,edge e,int isOriented){
    graph->g[e->v1][e->v2]=e->weight;
    if(!isOriented){
        graph->g[e->v2][e->v1]=e->weight;
    }
}

/*
construct a graph according user's input

@return a graph has been filled good
*/
adjacentMatrixGraph buildGraph(){
    adjacentMatrixGraph graph;
    edge e;
    vertex v;
    int vertex_num,i;
    scanf("%d",&vertex_num);
    graph = createGraph(vertex_num);
    scanf("%d",&(graph->edge_nunber));
    if(!graph->edge_nunber){
        e = (edge)malloc(sizeof(struct eNode));
        for(i=0;i<graph->edge_nunber;i++){
            scanf("%d %d %d",&e->v1,&e->v2,&e->weight);
            inserEdge(graph,e,1);
        }
    }

    for(i=0;i<graph->vertex_number;i++){
        scanf("%c",&(graph->data[i]));
    }

    return graph;


}


int main(){
    printf("just test");
    return 0;
}
