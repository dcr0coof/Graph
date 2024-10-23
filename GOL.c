#include <stdio.h>

typedef struct Glist_node {

	int data;
	int weight;
	Glist_node* next;
}Glist_node;

typedef struct Headon {
	Glist_node* head;
}Headon;

typedef struct Graph {

	int id;
	int V;
	int E;
	Headon* next_v;

}Graph;

Graph* creat_graph(int v,int identify) {

	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->id = identify;
	graph->V = v;
	graph->E = 0;
	graph->next_v = (Glist_node*)malloc(v*sizeof(Glist_node));

	for (int i = 0; i < v;i++) {
		graph->next_v[i].head = NULL;
	}
	return graph;

}

Glist_node* creat_newNode(int data, int weight) {

	Glist_node* new_node = (Glist_node*)malloc(sizeof(Glist_node));
	new_node->data = data;
	new_node->weight = weight;
	new_node->next = NULL;
	return new_node;

}

void insert(int begin,int weight, int end, Graph* graph) {

	Glist_node* p=creatGL(end, weight);

	p->next = graph->next_v[begin].head;
	graph->next_v[begin].head = p;

	if (!graph->id) {
		Glist_node* q = creat(begin, weight);
		q->next = graph->next_v[end].head;
		graph->next_v[end].head = q;
	}

	graph->E++;

}

int count_edges(Graph* graph) {
	if (graph->id) {
		return graph->E;
	}
	else {
		return graph->E / 2;
	}
}

void print_graph(Graph* graph) {

	for (int v = 0; v < graph->V; ++v) {
		Glist_node* p = graph->next_v[v].head;
		printf("Vertex %d: ", v);
		while (p) {
			printf("-> %d", p->data);
			p = p->next;
		}
		printf("\n");
	}

}

int main() {
	int V, E, ID;
	scanf_s("%d %d %d", &V, &E, &ID);

	Graph* graph=creat_graph(V, ID);


	return 0;


}