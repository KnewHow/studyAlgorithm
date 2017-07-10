#include<stdio.h>
#include<stdlib.h>

#define MAX_VERTEX_NUM 100 /*define the max number of the vertex*/
#define INFINITY 65535     /*define double byte no negitive integer max number is 65535*/



typedef int vertex;        /*define the data type of the vertex*/
typedef int weightType;    /*define the data type of the weight*/
typedef char dataType; /*define the data type of the vertex value*/

//int visited[MAX_VERTEX_NUM];

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
typedef struct vNode *ptrToVNode;
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
    graph->edge_nunber=0;
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
    newNode->adjVerx=e->v2;
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

    printf("please input the quantity of the vertex:");
    scanf("%d",&vertex_num);
    graph  = createGraph(vertex_num);
    printf("please input the quantity of the edges:");
    scanf("%d",&(graph->edge_nunber));
    if(graph->edge_nunber){
        e = (edge)malloc(sizeof(struct eNode));
        for(i=0;i<graph->edge_nunber;i++){
            scanf("%d %d %d",&e->v1,&e->v2,&e->weight);
            insertEdge(graph,e,1);
        }
    }

    /*if the vertex has name*/
    for(i=0;i<graph->vertex_number;i++){
        scanf(" %c",&(graph->g[i].data));
    }
    //printf("lala:%c,%c\n",graph->g[0].data,graph->g[1].data);
    //printf("lala:%d\n",graph->vertex_number);
    //printf("%c",graph->g[1].data);
    return graph;
}



/*==============================define a queue=====================================================*/
/*define a list to store the element in the queue*/
typedef ptrToVNode elementType;
typedef struct node *pList;
typedef struct node{
    elementType element;
    struct node *next;
};

/*define a queue to point the list*/
typedef struct node2 *pQueue;
typedef struct node2{
    pList front;    /*the front point to point the head of the list*/
    pList rear;     /*the rear point to point the rear of of the list*/
};

/*create a empty list to store the queue element*/
pList createEmptyList(){
    pList list;
    list = (pList)malloc(sizeof(struct node));
    list->next=NULL;
    return list;
}
/*create a empty queye*/
pQueue createEmptyQueue(){
    pQueue queue = (pQueue)malloc(sizeof(struct node2));
    queue->front=NULL;
    queue->rear=NULL;
    return queue;
}

/*
Wether the queue is empty
@param queue The queue need to adjust
@return If the queue is null,return 1 otherwise return 0
*/
int isQueueEmpty(pQueue queue){
    return(queue->front==NULL);
}

/*
Add a element to a queue,If the queue is null,we will create a new queue
@parama queue The queue we will add elememt to
@prama element The element we will add to queue
*/
void addQueue(pQueue queue,elementType element){
    if(isQueueEmpty(queue)){
        pList list = createEmptyList();
        list->element=element;
        queue->front=queue->rear=list;
    }else{
        pList newNode = (pList)malloc(sizeof(struct node));
        newNode->element = element;
        newNode->next = queue->rear->next;
        queue->rear->next=newNode;
        queue->rear=newNode;
    }
}

/*
delete a element from a queue
@param queue The queue will be deleted a element
@return The element has been deleted
*/
elementType deleteEleFromQueue(pQueue queue){
    if(isQueueEmpty(queue)){
        printf("the queue is empty,don't allow to delete elemet from it!");
    }else{
        pList oldNode = queue->front;
        elementType element = oldNode->element;
        if(queue->front==queue->rear){
            queue->rear=queue->front=NULL;
        }else{
            queue->front=queue->front->next;
        }
        free(oldNode);
        return element;
    }
}

/*
visite a graph's node
@param graph The graph to store the elements
@param v The index of vertex in the adjacent table
*/
void visit(adjacentTableGraph graph,vertex v){
    printf("%c ",graph->g[v].data);
}

/*
Breadth first search
@param graph The graph stored by the adjacent table
@param startPoint The point we start search 
@param visited A array to tag the elemeent whether has been visited
*/
void BFS(adjacentTableGraph graph,vertex startPoint,int *visited){
    ptrToAdjNode p;
    //printf("lala:%d",graph->g[3].head->adjVerx);
    visited[startPoint]=1;
    visit(graph,startPoint);
    pQueue queue = createEmptyQueue();
    addQueue(queue,&(graph->g[startPoint]));
    while(!isQueueEmpty(queue)){
        elementType element = deleteEleFromQueue(queue);
        //printf("lala:%d\n",element->head->adjVerx);
        for(p=element->head;p;p=p->next){
            if(visited[p->adjVerx]==0){
                visited[p->adjVerx]=1;
                visit(graph,p->adjVerx);
                addQueue(queue,&(graph->g[p->adjVerx]));
            }
        }
    }
}

/*
Depth first search a graph
@param graph The graph need to search
@param startPoint The fisrt point we start search the graph
@paran int *visited The array we use to tag the vertex we has visited.
*/
void DFS(adjacentTableGraph graph,vertex startPoint,int *visited){
    ptrToAdjNode p;
    visit(graph,startPoint);
    p=graph->g[3].head;
    //printf("lala%d",p->adjVerx);
    visited[startPoint]=1;
    for(p=graph->g[startPoint].head;p;p=p->next){
        if(visited[p->adjVerx]==0){
        //printf("lala:%d",p->adjVerx);
            DFS(graph,p->adjVerx,visited);
        }
    }
}



int main(){
    int i;
    adjacentTableGraph graph=buildGraph();
    int visited[graph->vertex_number];
    for(i=0;i<graph->vertex_number;i++){
        visited[i]=0;
    }
    DFS(graph,0,visited);
    printf("\n");
    for(i=0;i<graph->vertex_number;i++){
        visited[i]=0;
    }
    BFS(graph,0,visited);
    printf("just test\n");
    return 0;
}

