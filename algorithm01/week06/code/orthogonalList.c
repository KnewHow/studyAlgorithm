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

/*define the data structure of the orthogonal list table node*/
typedef struct adjNode *ptrToAdjNode;
typedef struct adjNode{
    vertex tailVertex;      /*the inde of tail vertex*/
    vertex headVertex;      /*the index of the head vertex*/
    weightType weight;      /*the valie of the weight*/
    ptrToAdjNode hLink;     /*the point to point next node who point the head vertex*/
    ptrToAdjNode tLink;     /*the point to point next node who point the tail vertex*/
};
/*define the data structure of orthogonal list of head node*/
typedef struct headNode{
    dataType data;          /*the space to store the name of the vertex,but some time the vertex has no names*/
    ptrToAdjNode firstin;   /*the point to point the in-degree node*/
    ptrToAdjNode firstout;   /*the point to poit the out-degree node*/
}headList[MAX_VERTEX_NUM];

typedef struct gNode *ptrToGNode;
typedef struct gNode{
    int vertex_number;  /*the number of the vertex*/
    int edge_nunber;    /*the number of the edge*/
    headList head;
};
typedef ptrToGNode orthogonalList;

/*
create a graph given the vertex number.
@param vertexNum The verter number of the graph
@return a graph with vertex but no any egdgs
*/
orthogonalList createGraph(int vertexNum){
    orthogonalList graph;
    vertex v;
    graph =(orthogonalList)malloc(sizeof(struct gNode));
    graph->vertex_number;
    graph->edge_nunber=0;
    for(v=0;v<graph->vertex_number;v++){
        graph->head[v].firstin=NULL;
        graph->head[v].firstout=NULL;
    }
    return graph;
}

/*
insert a edge to graph.We will distinct oriented graph and undirected graph
The e->v1 and e->v2 are the vertexs' indexs in the orthogoanlList
@param graph The graph you want to insert edge
@param e The edge you want to insert the graph
*/
void insertEdge(orthogonalList graph,edge e){
    ptrToAdjNode newNode;
    newNode =(ptrToAdjNode)malloc(sizeof(struct adjNode));
    newNode->tailVertex=e->v1;
    newNode->headVertex=e->v2;
    newNode->weight = e->weight;
    /*let v1 head's firstout point to the new node */
    newNode->tLink=graph->head[e->v1].firstout;
    graph->head[e->v1].firstout=newNode;

    /*let v2 head's firstin point to new node*/
    newNode->hLink=graph->head[e->v2].firstin;
    graph->head[e->v2].firstin=newNode;
}

/*
build a graph stored by orthogonal list
*/
orthogonalList buildGraph(){
    orthogonalList graph;
    edge e;
    vertex v;
    int vertex_num,i;

    scanf("%d",&vertex_num);
    graph = createGraph(vertex_num);
    scanf("%d",&(graph->edge_nunber));
    if(!graph->vertex_number){
        e = (edge)malloc(sizeof(struct eNode));
        for(i=0;i<graph->edge_nunber;i++){
            scanf("%d %d %d",&e->v1,&e->v2,&e->weight);
            insertEdge(graph,e);
        }
    }

    /*if the vertex has name,we will set it following*/
    for(i=0;i<graph->vertex_number;i++){
        scanf("%c",&(graph->head[i].data));
    }
    return graph;
}
int main(){
    printf("just test");
    return 0;
}
