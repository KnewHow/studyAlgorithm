/*DFS(depth first search)伪代码描述*/

void DFS(vertex V){
	visited[V]=true;
	for(every adjacent W of V){
		if(!visited[W]){
			DFS(W)
		}
	}
}
