#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int nodeNum = 0;
vector<int> visited;

struct node {
	int weight = 0;
	int index = -1;
	int startVertex = -1;
	node* next = NULL;

	node() {

	}
	node(int weight, int index, int startVertex) {
		this->weight = weight;
		this->index = index;
		this->startVertex = startVertex;
	}
};

node* makeGraph();
void DFS(node* now, node* G);
void BFS(node* now, node* G);
bool compare(node* a, node* b); //for Kruskal/Prim edge sort
void Kruskal(node* G);
void Prim(node* start, node* G);
void Sollin(node* G);
void Dijkstra(node* start, node* G);
void Floyd_Warshall(node* G);

node* makeGraph(){
	node* graph = NULL;
	node* now;
	switch (1) { // 몇 번 Graph를 만들건지 사용자가 바꿀 것
	case 1:
		nodeNum = 10;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'J'; i++) {
			graph[i-'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(5, 'C'-'A', 0);
		now = now->next;
		now->next = new node(5, 'D'-'A', 0);
		now = now->next;
		now->next = new node(4, 'I' - 'A', 0);
		//B
		now = &graph[1];
		now->next = new node(7, 'D' - 'A', 1);
		now = now->next;
		now->next = new node(2, 'E' - 'A', 1);
		now = now->next;
		now->next = new node(8, 'F' - 'A', 1);
		now = now->next;
		now->next = new node(1, 'G' - 'A', 1);
		now = now->next;
		now->next = new node(4, 'I' - 'A', 1);
		now = now->next;
		now->next = new node(3, 'J' - 'A', 1);
		//C
		now = &graph[2];
		now->next = new node(5, 'A' - 'A', 2);
		now = now->next;
		now->next = new node(3, 'I' - 'A', 2);
		//D
		now = &graph[3];
		now->next = new node(5, 'A' - 'A', 3);
		now = now->next;
		now->next = new node(7, 'B' - 'A', 3);
		now = now->next;
		now->next = new node(2, 'G' - 'A', 3);
		//E
		now = &graph[4];
		now->next = new node(2, 'B' - 'A', 4);
		now = now->next;
		now->next = new node(12, 'I' - 'A', 4);
		//F
		now = &graph[5];
		now->next = new node(8, 'B' - 'A', 5);
		now = now->next;
		now->next = new node(3, 'G' - 'A', 5);
		now = now->next;
		now->next = new node(1, 'J' - 'A', 5);
		//G
		now = &graph[6];
		now->next = new node(1, 'B' - 'A', 6);
		now = now->next;
		now->next = new node(2, 'D' - 'A', 6);
		now = now->next;
		now->next = new node(3, 'F' - 'A', 6);
		now = now->next;
		now->next = new node(4, 'H' - 'A', 6);
		//H
		now = &graph[7];
		now->next = new node(4, 'G' - 'A', 7);
		now = now->next;
		now->next = new node(5, 'J' - 'A', 7);
		//I
		now = &graph[8];
		now->next = new node(4, 'A' - 'A', 8);
		now = now->next;
		now->next = new node(4, 'B' - 'A', 8);
		now = now->next;
		now->next = new node(3, 'C' - 'A', 8);
		now = now->next;
		now->next = new node(12, 'E' - 'A', 8);
		//J
		now = &graph[9];
		now->next = new node(3, 'B' - 'A', 9);
		now = now->next;
		now->next = new node(1, 'F' - 'A', 9);
		now = now->next;
		now->next = new node(5, 'H' - 'A', 9);
		break;
	case 2:
		nodeNum = 8;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'H'; i++) {
			graph[i-'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(4, 'B' - 'A', 0);
		now = now->next;
		now->next = new node(3, 'C' - 'A', 0);
		now = now->next;
		now->next = new node(4, 'D' - 'A', 0);
		now = now->next;
		now->next = new node(8, 'E' - 'A', 0);
		//B
		now = &graph[1];
		now->next = new node(4, 'A' - 'A', 1);
		now = now->next;
		now->next = new node(2, 'C' - 'A', 1);
		//C
		now = &graph[2];
		now->next = new node(3, 'A' - 'A', 2);
		now = now->next;
		now->next = new node(2, 'B' - 'A', 2);
		now = now->next;
		now->next = new node(12, 'H' - 'A', 2);
		//D
		now = &graph[3];
		now->next = new node(4, 'A' - 'A', 3);
		now = now->next;
		now->next = new node(5, 'E' - 'A', 3);
		//E
		now = &graph[4];
		now->next = new node(8, 'A' - 'A', 4);
		now = now->next;
		now->next = new node(5, 'D' - 'A', 4);
		now = now->next;
		now->next = new node(4, 'F' - 'A', 4);
		now = now->next;
		now->next = new node(7, 'H' - 'A', 4);
		//F
		now = &graph[5];
		now->next = new node(4, 'E' - 'A', 5);
		now = now->next;
		now->next = new node(2, 'G' - 'A', 5);
		now = now->next;
		now->next = new node(3, 'H' - 'A', 5);
		//G
		now = &graph[6];
		now->next = new node(2, 'F' - 'A', 6);
		now = now->next;
		now->next = new node(1, 'H' - 'A', 6);
		//H
		now = &graph[7];
		now->next = new node(12, 'C' - 'A', 7);
		now = now->next;
		now->next = new node(7, 'E' - 'A', 7);
		now = now->next;
		now->next = new node(3, 'F' - 'A', 7);
		now = now->next;
		now->next = new node(1, 'G' - 'A', 7);
		break;
	case 3:
		nodeNum = 11;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'K'; i++) {
			graph[i - 'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(7, 'B' - 'A', 0);
		now = now->next;
		now->next = new node(3, 'H' - 'A', 0);
		//B
		now = &graph[1];
		now->next = new node(7, 'A' - 'A', 1);
		now = now->next;
		now->next = new node(8, 'C' - 'A', 1);
		now = now->next;
		now->next = new node(5, 'I' - 'A', 1);
		//C
		now = &graph[2];
		now->next = new node(8, 'B' - 'A', 2);
		now = now->next;
		now->next = new node(7, 'D' - 'A', 2);
		now = now->next;
		now->next = new node(3, 'F' - 'A', 2);
		now = now->next;
		now->next = new node(8, 'G' - 'A', 2);
		//D
		now = &graph[3];
		now->next = new node(7, 'C' - 'A', 3);
		now = now->next;
		now->next = new node(7, 'G' - 'A', 3);
		now = now->next;
		now->next = new node(3, 'K' - 'A', 3);
		//E
		now = &graph[4];
		now->next = new node(2, 'H' - 'A', 4);
		now = now->next;
		now->next = new node(4, 'I' - 'A', 4);
		//F
		now = &graph[5];
		now->next = new node(3, 'C' - 'A', 5);
		now = now->next;
		now->next = new node(12, 'I' - 'A', 5);
		now = now->next;
		now->next = new node(21, 'J' - 'A', 5);
		//G
		now = &graph[6];
		now->next = new node(8, 'C' - 'A', 6);
		now = now->next;
		now->next = new node(7, 'D' - 'A', 6);
		now = now->next;
		now->next = new node(8, 'J' - 'A', 6);
		now = now->next;
		now->next = new node(5, 'K' - 'A', 6);
		//H
		now = &graph[7];
		now->next = new node(2, 'E' - 'A', 7);
		now = now->next;
		now->next = new node(10, 'K' - 'A', 7);
		//I
		now = &graph[8];
		now->next = new node(5, 'B' - 'A', 8);
		now = now->next;
		now->next = new node(4, 'E' - 'A', 8);
		now = now->next;
		now->next = new node(12, 'F' - 'A', 8);
		now = now->next;
		now->next = new node(9, 'J' - 'A', 8);
		//J
		now = &graph[9];
		now->next = new node(21, 'F' - 'A', 9);
		now = now->next;
		now->next = new node(8, 'G' - 'A', 9);
		now = now->next;
		now->next = new node(9, 'I' - 'A', 9);
		//K
		now = &graph[10];
		now->next = new node(3, 'D' - 'A', 10);
		now = now->next;
		now->next = new node(5, 'G' - 'A', 10);
		now = now->next;
		now->next = new node(10, 'H' - 'A', 10);
		break;
	case 4:
		nodeNum = 9;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'I'; i++) {
			graph[i - 'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(7, 'B' - 'A', 0);
		//B
		now = &graph[1];
		now->next = new node(7, 'A' - 'A', 1);
		now = now->next;
		now->next = new node(12, 'C' - 'A', 1);
		now = now->next;
		now->next = new node(10, 'F' - 'A', 1);
		//C
		now = &graph[2];
		now->next = new node(12, 'B' - 'A', 2);
		now = now->next;
		now->next = new node(1, 'E' - 'A', 2);
		now = now->next;
		now->next = new node(2, 'G' - 'A',2);
		//D
		now = &graph[3];
		now->next = new node(15, 'F' - 'A',3);
		now = now->next;
		now->next = new node(5, 'G' - 'A',3);
		now = now->next;
		now->next = new node(4, 'H' - 'A',3);
		//E
		now = &graph[4];
		now->next = new node(1, 'C' - 'A',4);
		now = now->next;
		now->next = new node(9, 'G' - 'A',4);
		//F
		now = &graph[5];
		now->next = new node(10, 'B' - 'A',5);
		now = now->next;
		now->next = new node(15, 'D' - 'A',5);
		//G
		now = &graph[6];
		now->next = new node(2, 'C' - 'A',6);
		now = now->next;
		now->next = new node(5, 'D' - 'A',6);
		now = now->next;
		now->next = new node(9, 'E' - 'A',6);
		//H
		now = &graph[7];
		now->next = new node(4, 'D' - 'A',7);
		now = now->next;
		now->next = new node(3, 'I' - 'A',7);
		//I
		now = &graph[8];
		now->next = new node(3, 'H' - 'A',8);
		break;
	case 5:
		nodeNum = 5;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'E'; i++) {
			graph[i - 'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(5, 'A' - 'A',0);
		now = now->next;
		now->next = new node(2, 'B' - 'A',0);
		now = now->next;
		now->next = new node(5, 'D' - 'A',0);
		//B
		now = &graph[1];
		now->next = new node(3, 'A' - 'A',1);
		now = now->next;
		now->next = new node(5, 'C' - 'A',1);
		now = now->next;
		now->next = new node(4, 'E' - 'A',1);
		//C
		now = &graph[2];
		now->next = new node(3, 'C' - 'A',2);
		now = now->next;
		now->next = new node(2, 'D' - 'A',2);
		//D
		now = &graph[3];
		now->next = new node(7, 'B' - 'A',3);
		now = now->next;
		now->next = new node(4, 'C' - 'A',3);
		//E
		now = &graph[4];
		now->next = new node(3, 'B' - 'A',4);
		now = now->next;
		now->next = new node(1, 'C' - 'A',4);
		break;
	case 6:
		nodeNum = 8;
		graph = new node[nodeNum];
		for (int i = 'A'; i <= 'H'; i++) {
			graph[i - 'A'].index = i - 'A';
		}
		//A
		now = &graph[0];
		now->next = new node(15, 'C' - 'A',0);
		now = now->next;
		now->next = new node(3, 'E' - 'A',0);
		//B
		now = &graph[1];
		now->next = new node(2, 'A' - 'A',1);
		now = now->next;
		now->next = new node(4, 'C' - 'A',1);
		now = now->next;
		now->next = new node(7, 'D' - 'A',1);
		now = now->next;
		now->next = new node(5, 'F' - 'A',1);
		//C
		now = &graph[2];
		now->next = new node(8, 'D' - 'A',2);
		//D
		now = &graph[3];
		now->next = new node(5, 'C' - 'A',3);
		now = now->next;
		now->next = new node(3, 'H' - 'A',3);
		//E
		now = &graph[4];
		now->next = new node(4, 'B' - 'A',4);
		//F
		now = &graph[5];
		now->next = new node(20, 'D' - 'A',5);
		now = now->next;
		now->next = new node(5, 'E' - 'A',5);
		now = now->next;
		now->next = new node(9, 'G' - 'A',5);
		//G
		now = &graph[6];
		now->next = new node(8, 'E' - 'A',6);
		now = now->next;
		now->next = new node(7, 'H' - 'A',6);
		//H
		now = &graph[7];
		now->next = new node(5, 'B' - 'A',7);
		now = now->next;
		now->next = new node(5, 'D' - 'A',7);
		now = now->next;
		now->next = new node(9, 'F' - 'A',7);
		now = now->next;
		now->next = new node(8, 'G' - 'A',7);
		break;
	}
	return graph;
}

//DFS, BFS, Kruskal's, Prim, Sollin's, Dijkstra's, Floya-Warshall 
void DFS(node* now, node* G) {
	visited[now->index] = 1;
	cout << char(now->index + 'A');
	while (now->next != NULL) {
		now = now->next;
		if (visited[now->index] == 0) {
			cout << " -> ";
			DFS(&G[now->index], G);
		}
	}
}

void BFS(node* now, node* G) {
	queue<int> que;
	que.push(now->index);
	visited[now->index] = 1;

	while (que.empty() == false) {
		int index = que.front();
		que.pop();
		now = &G[index];
		while (now->next != NULL) {
			now = now->next;
			if (!visited[now->index]) {
				que.push(now->index);
				visited[now->index] = 1;
			}
		}
		cout << char(index + 'A');
		if (que.empty() == false) cout << " -> ";
	}
}

bool compare(node* a, node* b) {
	return (a->weight < b->weight);
}

void Kruskal(node* G) {
	vector<node*> edge;
	node* now = &G[0];
	int edgeNum = 0;
	//모든 edge저장
	for (int i = 0; i < nodeNum; i++) {
		now = (&G[i])->next;
		while (now->next != NULL) {
			edge.push_back(now);
			edgeNum++;
			now = now->next;
		}
	}
	//edge를 크기순으로 정렬 (compare은 node*에서 weight를 기준으로 정렬하는 사용자 정의함수)
	sort(edge.begin(), edge.end(), compare);

	int n = 0;
	int m = 0;
	while (n < nodeNum-1) {
		//가중치가 낮은 edge부터 넣되, visited배열을 이어진 정점의 최소 정점 인덱스값으로 저장하고 비교하면서 cycle형성 방지
		if (visited[edge[m]->startVertex] != visited[edge[m]->index]) {
			cout << endl;
			cout << "(" << (char)(edge[m]->startVertex + 'A') << " -- " << (char)(edge[m]->index + 'A') << ") , " << edge[m]->weight << endl;
			int minNum = min(min(min(edge[m]->startVertex, edge[m]->index), visited[edge[m]->startVertex]), visited[edge[m]->index]);
			int startVertex = visited[edge[m]->startVertex];
			int index = visited[edge[m]->index];
			for (int i = 0; i < nodeNum; i++) {
				if (visited[i] == startVertex or visited[i] == index) {
					visited[i] = minNum;
				}
			}
			n++;
		}
		m++;
	}
}

void Prim(node* start, node* G) {
	vector<node*> fringe;
	node* now = start->next;
	int n = 0;
	visited[now->startVertex] = 1;
	while (n < nodeNum - 1) {

		cout << endl;
		//fringe Set 추가
		while (now->next != NULL) {
			fringe.push_back(now);
			now = now->next;
		}
		fringe.push_back(now);
		//fringe 정렬
		sort(fringe.begin(), fringe.end(), compare);

		//가장 weight가 낮은 edge가 이미 방문한 두 점으로 연결되어 있을 시
		while (visited[fringe[0]->index] == 1 and visited[fringe[0]->startVertex] == 1) {
			fringe.erase(fringe.begin());
		}
		
		if (visited[fringe[0]->index] != 1) {
			visited[fringe[0]->index] = 1;
			now = (&G[fringe[0]->index])->next;
		}
		else if (visited[fringe[0]->startVertex] != 1) {
			visited[fringe[0]->startVertex] = 1;
			now = (&G[fringe[0]->startVertex])->next;
		}

		cout << "(" << (char)(fringe[0]->startVertex + 'A') << " -- " << (char)(fringe[0]->index + 'A') << ") , " << fringe[0]->weight << endl;
		n++;
	}
}

void Sollin(node* G) {
	//edge처음에 다 받아서
	//추가되는 edge를 아예 제거
	vector<vector<node*>> subGraph;
	int n = 0;
	int subGraphSize = nodeNum;
	vector<vector<int>> add;
	while (n < nodeNum - 1) {
		subGraph.clear();
		subGraph.resize(subGraphSize);
		bool addflag = true;
		//visited검사해서 edges 병합해서 하는 것 구현
		for (int i = 0; i < nodeNum; i++) {
			node* now = (&G[i])->next;
			//addflag를 이용해 이미 추가되있는 edge는 중복해서 받지 않도록 구현
			while (now->next != NULL) {
				for (int k = 0; k < add.size(); k++) {
					if ((add[k][0] == now->index and add[k][1] == now->startVertex) or 
						(add[k][1] == now->index and add[k][0] == now->startVertex) or 
						(visited[now->index] == visited[now->startVertex])) {
						addflag = false;
						break;
					}
				}
				if (addflag == true) {
					subGraph[visited[i]].push_back(now);
				}
				now = now->next;
				addflag = true;
			}
			for (int k = 0; k < add.size(); k++) {
				if ((add[k][0] == now->index and add[k][1] == now->startVertex) or 
					(add[k][1] == now->index and add[k][0] == now->startVertex) or 
					(visited[now->index] == visited[now->startVertex])) {
					addflag = false;
					break;
				}
			}
			if (addflag == true) {
				subGraph[visited[i]].push_back(now);
			}
			addflag = true;
		}
		
		//subGraph에서 최소 길이를 가지는 edge을 계산
		vector<vector<int>> least;
		int leastIndex = 100;
		int leastWeight = 100;
		for (int i = 0; i < subGraph.size(); i++) {
			if (subGraph[i].size() == 0) continue;
			for (int j = 0; j < subGraph[i].size(); j++) {
				if (subGraph[i][j]->weight < leastWeight) {
					leastIndex = j;
					leastWeight = subGraph[i][j]->weight;
				}
			}
			vector<int> info;
			info.push_back(subGraph[i][leastIndex]->startVertex);
			info.push_back(subGraph[i][leastIndex]->index);
			info.push_back(subGraph[i][leastIndex]->weight);
			least.push_back(info);
			leastWeight = 100;
		}

		//least[i][0] -> startVertex:[0], DestVertex(index):[1], weight:[2]
		//least에서 서로 다른 방향의 간선이 중복되는 경우를  제거
		for (int i = 0; i < least.size(); i++) {
			for (int j = 0; j < least.size(); j++) {
				if (least[i][0] == least[j][1] and least[j][1] == least[i][0] and i != j) {
					least[j][0] = -1;
				}
			}
		}

		//least edge를 출력하되, visited를 그때그때 갱신하면서 least내에서 다시 cycle이 생기는 것을 방지
		for (int i = 0; i < least.size(); i++) {
			if (least[i][0] == -1 or (visited[least[i][0]] == visited[least[i][1]])) continue;
			cout << "(" << (char)(least[i][0] + 'A') << " -- " << (char)(least[i][1] + 'A') << ") , " << least[i][2] << endl;
			int startVertex = least[i][0];
			int index = least[i][1];
			int minNum = min(min(min(visited[least[i][0]], visited[least[i][1]]), least[i][0]), least[i][1]);
			for (int j = 0; j < nodeNum; j++) {
				if (visited[j] == startVertex or visited[j] == index) {
					visited[j] = minNum;
				}
			}
			n++;
			vector<int> addEdge;
			addEdge.push_back(least[i][0]);
			addEdge.push_back(least[i][1]);
			addEdge.push_back(least[i][2]);
			add.push_back(addEdge);
		}
	}
}

void Dijkstra(node* start, node* G) {
	vector<node*> fringe;
	node* now = start->next;
	int n = 0;
	vector<int> distance;
	vector<vector<int>> visitOrder;
	visitOrder.resize(nodeNum);

	for(int i = 0; i < nodeNum; i++) {
		distance.push_back(1000);
	}
	while (now->next != NULL) {
		distance[now->index] = now->weight;
		visitOrder[now->index].push_back(now->index);
		now = now->next;
	}
	distance[now->index] = now->weight;
	visitOrder[now->index].push_back(now->index);
	visited[now->startVertex] = 1;

	while (n < nodeNum - 1) {
		int min = 1000;
		int minIndex = -1;
		for (int i = 0; i < distance.size(); i++) {
			if (min > distance[i] and visited[i] != 1) {
				min = distance[i];
				minIndex = i;
			}
		}
		min = 1000;
		//minIndex를 넣고, distance 갱신
		visited[minIndex] = 1;
		node* now = (&G[minIndex])->next;
		for (int i = 0; i < nodeNum; i++) {
			while (now->next != NULL) {
				if (visited[now->index] == 0) {
					if (distance[minIndex] + now->weight < distance[now->index]) {
						distance[now->index] = distance[minIndex] + now->weight;
						visitOrder[now->index].assign(visitOrder[minIndex].begin(), visitOrder[minIndex].end());
						visitOrder[now->index].push_back(now->index);
					}
				}
				now = now->next;	
			}
			if (visited[now->index] == 0) {
				if (distance[minIndex] + now->weight < distance[now->index]) {
					distance[now->index] = distance[minIndex] + now->weight;
					visitOrder[now->index].assign(visitOrder[minIndex].begin(), visitOrder[minIndex].end());
					visitOrder[now->index].push_back(now->index);
				}
			}
		}
		n++;
	}

	for (int i = 0; i < nodeNum; i++) {
		if (distance[i] == 1000) distance[i] = 0;
		cout << "거리 : " << distance[i] << "\t" <<  (char)(start->index + 'A');
		for (int j = 0; j < visitOrder[i].size(); j++) {
			cout << " -> " << (char)(visitOrder[i][j] + 'A');
		}
		cout << endl;
	}
}

void Floyd_Warshall(node* G) {
	vector<vector<int>> oldWarshall;
	oldWarshall.resize(nodeNum);
	for(int i=0; i<nodeNum; i++) {
		vector<int> column;
		column.resize(nodeNum);
		for (int j = 0; j < nodeNum; j++) {
			column[j] = 1000;
			if (i == j) column[j] = 0;
		}
		node* now = (&G[i])->next;
		while(now->next != NULL) {
			column[now->index] = now->weight;
			now = now->next;
		}
		column[now->index] = now->weight;
		oldWarshall[i] = column;
	}

	for(int k=0; k<nodeNum; k++) {
		vector<vector<int>> newWarshall;
		newWarshall.resize(nodeNum);
		for (int i = 0; i < nodeNum; i++) {
			newWarshall[i].resize(nodeNum);
			for (int j = 0; j < nodeNum; j++) {
				newWarshall[i][j] = 1000;
			}
		}
		for (int i = 0; i < nodeNum; i++) {
			for (int j = 0; j < nodeNum; j++) {
				newWarshall[i][j] = min(oldWarshall[i][j], oldWarshall[i][k] + oldWarshall[k][j]);
			}
		}
		oldWarshall = newWarshall;
	}
	
	//출력
	cout << "\t";
	for (int i = 0; i < nodeNum; i++) {
		cout << (char)(i + 'A') << "\t";
	}
	cout << endl;
	for (int i = 0; i < nodeNum; i++) {
		cout << (char)(i + 'A') << "\t";
		for (int j = 0; j < nodeNum; j++) {
			cout << oldWarshall[i][j] << "\t";
		}
		cout << endl;
	}
}

int main() {
	node* graph = makeGraph();

	//수행 시간 계산
	clock_t startTime, endTime;
	startTime = clock();

	char startVertex = 'G'; //여기에 출발지점 설정
	node* now;
	//여기에 그래프 알고리즘에 따라 switch 변경
	//단, MST는 digraph인 5,6번 그래프에 대해 올바른 결과를 내지 못함.
	//1:DFS 2:BFS 3:Kruskal 4:Prim 5:Sollin 6:Dijkstra 7:Floyd-Warshall
	switch (7) {
	case 1:
		cout << "DFS" << endl;
		now = &graph[startVertex - 'A'];

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(0);
		}

		DFS(now, graph);
		break;
	case 2:
		cout << "BFS" << endl;
		now = &graph[startVertex - 'A'];

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(0);
		}

		BFS(now, graph);
		break;
	case 3:
		cout << "Kruskal" << endl;

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(i);
		}
		Kruskal(graph);
		break;
	case 4:
		cout << "Prim" << endl;
		now = &graph[startVertex - 'A'];

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(0);
		}
		Prim(now, graph);
		break;
	case 5:
		cout << "Sollin" << endl;

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(i);
		}
		Sollin(graph);
		break;
	case 6:
		cout << "Dijkstra" << endl;
		now = &graph[startVertex - 'A'];

		//방문 배열 초기화
		for (int i = 0; i < nodeNum; i++) {
			visited.push_back(0);
		}
		Dijkstra(now, graph);
		break;
	case 7:
		cout << "Floyd-Warshall" << endl;

		Floyd_Warshall(graph);
		break;
	}
	endTime = clock();
	int time = endTime - startTime;
	cout << endl << "소요된 시간 : " << time << "ms";
	return 0;
}