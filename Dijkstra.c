#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define INF INT_MAX 

int findMinDistance(int dist[], int visited[], int n) {
	int min = INF, minIndex = -1;

	for (int i = 0; i < n; i++) {
		if (!visited[i] && dist[i] < min) {
			min = dist[i];
			minIndex = i;
		}
	}

	return minIndex;
}

void Dijkstra(int graph[MAX_NODES][MAX_NODES], int n, int scr) {
	int dist[MAX_NODES];
	int visited[MAX_NODES];
	int parent[MAX_NODES];

	for (int i = 0; i < n; i++) {
		dist[i] = INF;
		visited[i] = 0;
		parent[i] = -1;

	}
	dist[scr] = 0;

	for (int i = 0; i < n - 1; i++) {
		int node = findMinDistance(dist, visited, n);
		visited[node] = 1;

		for (int v = 0; v < n; v++) {
			if (!visited[v] && graph[node][v] && dist[node] != INF && dist[node] + graph[node][v] < dist[v]) {
				dist[v] = dist[node] + graph[node][v];
				parent[v] = node;
			}
		}

	}
	printf("�ڵ�\t��̾���\t·��\n");

	for (int i = 0; i < n; i++) {
		printf("%d\t%d\t\t", i, dist[i]);
		// ��ӡ·��
		int temp = i;
		while (temp != -1) {
			printf("%d ", temp);
			temp = parent[temp];
		}
		printf("\n");
	}
}

int main() {
	int n, src;

	// ʾ��ͼ
	int graph[MAX_NODES][MAX_NODES] = {
		{0, 10, 20, 0, 0, 0},
		{10, 0, 0, 50, 10, 0},
		{20, 0, 0, 20, 33, 0},
		{0, 50, 20, 0, 20, 2},
		{0, 10, 33, 20, 0, 1},
		{0, 0, 0, 2, 1, 0}
	};

	n = 6;  // ͼ�Ľڵ���
	src = 0; // Դ�ڵ�

	printf("Dijkstra�㷨ʾ�����ӽڵ� %d ����\n", src);
	Dijkstra(graph, n, src);

	return 0;
}