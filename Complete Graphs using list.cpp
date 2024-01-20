#include <iostream>
#include <stack>
#include <algorithm> 
#include <climits>
#define SIZE 100
using namespace std;

struct Node {
	int destination;
	int weight;
	Node* next;

	Node(int dest, int w) : destination(dest), weight(w), next(nullptr) {}
};

class LinkedList {
	public:
		Node* head;
		LinkedList() : head(nullptr) {}

		void addNode(int dest, int weight) {
			Node* newNode = new Node(dest, weight);
			newNode->next = head;
			head = newNode;
		}

		void removeNode(int dest) {
			Node* temp = head;
			Node* prev = nullptr;

			while (temp && temp->destination != dest) {
				prev = temp;
				temp = temp->next;
			}
			if (temp) {
				if (prev) {
					prev->next = temp->next;
				} else {
					head = temp->next;
				}
				delete temp;
			}
		}

		void displayList() {
			Node* temp = head;
			while (temp) {
				cout << temp->destination << " ";
				temp = temp->next;
			}
			cout << endl;
		}

		Node* getHead() {
			return head;
		}
};

class Graph {
	private:
		LinkedList* list;
		int numVertices;
		bool* isVisited;

	public:
		Graph() : list(nullptr), numVertices(0), isVisited(nullptr) {}

		void addVertex() {
			LinkedList* newList = new LinkedList[numVertices + 1];

			for (int i = 0; i < numVertices; ++i) {
				newList[i] = list[i];
			}
			delete[] list;

			list = newList;
			++numVertices;
		}

		void addEdge(int source, int destination, int weight) {
			list[source].addNode(destination, weight);
			list[destination].addNode(source, weight);
		}

		void updateEdge(int source, int oldDestination, int newDestination, int weight) {
			list[source].removeNode(oldDestination);
			list[source].addNode(newDestination, weight);

			list[newDestination].removeNode(source);
			list[newDestination].addNode(source, weight);
		}

		void retrieveEdges(int vertex) {
			cout << "Edges for vertex " << vertex << ": ";
			list[vertex].displayList();
		}

		void displayAllEdgesForAllVertices() {
			for (int i = 0; i < numVertices; ++i) {
				cout << "All Edges for vertex " << i << ": ";
				list[i].displayList();
			}
		}

		// DFS function
		void DFS(int startVertex) {
			bool* visited = new bool[numVertices];
			for (int i = 0; i < numVertices; ++i) {
				visited[i] = false;
			}
			DFSUtil(startVertex, visited);
			delete[] visited;
		}

		void DFSUtil(int vertex, bool* visited) {
			visited[vertex] = true;
			cout << vertex << " ";

			Node* temp = list[vertex].getHead();
			while (temp) {
				int adjVertex = temp->destination;
				if (!visited[adjVertex]) {
					DFSUtil(adjVertex, visited);
				}
				temp = temp->next;
			}
		}

		// BFS function
		void BFS(int startVertex) {
			bool* visited = new bool[numVertices];
			for (int i = 0; i < numVertices; ++i) {
				visited[i] = false;
			}

			const int maxQueueSize = 100;
			int queue[maxQueueSize];
			int front = 0, rear = 0;

			visited[startVertex] = true;
			queue[rear++] = startVertex;

			while (front != rear) {
				int currentVertex = queue[front++];
				cout << currentVertex << " ";

				Node* temp = list[currentVertex].getHead();
				while (temp) {
					int adjVertex = temp->destination;
					if (!visited[adjVertex]) {
						visited[adjVertex] = true;
						queue[rear++] = adjVertex;
					}
					temp = temp->next;
				}
			}
			delete[] visited;
		}

		// Kruskal's Algorithm
		void kruskal() {
			pair<int, pair<int, int>>* edges;
			
			edges = new pair<int, pair<int, int>>[SIZE * SIZE];

			int edgeCount = 0;
			for (int i = 0; i < numVertices; ++i) {
				Node* temp = list[i].getHead();
				while (temp) {
					int dest = temp->destination;
					int weight = temp->weight;
					if (i < dest) {
						edges[edgeCount++] = make_pair(weight, make_pair(i, dest));
					}
					temp = temp->next;
				}
			}

			sort(edges, edges + edgeCount);

			int* parent = new int[numVertices];
			for (int i = 0; i < numVertices; ++i)
				parent[i] = i;

			cout << "\nMinimum Spanning Tree using Kruskal's algorithm:\n";
			int totalCost = 0;
			for (int i = 0; i < edgeCount; ++i) {
				int u = edges[i].second.first;
				int v = edges[i].second.second;

				int parentU = findParent(parent, u);
				int parentV = findParent(parent, v);

				if (parentU != parentV) {
					totalCost += edges[i].first;
					cout << "Edge " << u << " - " << v << " added to MST\n";
					parent[parentU] = parentV;
				}
			}

			cout << "Total cost of MST: " << totalCost << endl;

			delete[] edges;
			delete[] parent;
		}

		// Prim's Algorithm
		void prim() {
			const int INF = INT_MAX;

			int* parent = new int[numVertices];
			int* key = new int[numVertices];
			bool* mstSet = new bool[numVertices];

			for (int i = 0; i < numVertices; ++i) {
				key[i] = INF;
				mstSet[i] = false;
			}

			key[0] = 0;
			parent[0] = -1;

			for (int count = 0; count < numVertices - 1; ++count) {
				int u = minKey(key, mstSet);
				mstSet[u] = true;

				Node* temp = list[u].getHead();
				while (temp) {
					int v = temp->destination;
					int weight = temp->weight;
					if (!mstSet[v] && weight < key[v]) {
						parent[v] = u;
						key[v] = weight;
					}
					temp = temp->next;
				}
			}

			cout << "\nMinimum Spanning Tree using Prim's algorithm:\n";
			int totalCost = 0;
			for (int i = 1; i < numVertices; ++i) {
				totalCost += key[i];
				cout << "Edge " << parent[i] << " - " << i << " added to MST\n";
			}

			cout << "Total cost of MST: " << totalCost << endl;

			delete[] parent;
			delete[] key;
			delete[] mstSet;
		}


		int minKey(int key[], bool mstSet[]) {
			const int INF = INT_MAX;
			int min = INF, min_index;

			for (int v = 0; v < numVertices; ++v) {
				if (!mstSet[v] && key[v] < min) {
					min = key[v];
					min_index = v;
				}
			}

			return min_index;
		}

		int findParent(int* parent, int v) {
			if (parent[v] == v)
				return v;
			return findParent(parent, parent[v]);
		}


		void dijkstra(int startVertex, int endVertex) {
			const int INF = INT_MAX;

			int* distance = new int[numVertices];
			bool* settled = new bool[numVertices];

			for (int i = 0; i < numVertices; ++i) {
				distance[i] = INF;
				settled[i] = false;
			}

			distance[startVertex] = 0;

			while (true) {
				int u = minKey(distance, settled);
				if (u == -1 || u == endVertex) {
					break;  // Either all vertices are settled or reached the destination vertex
				}

				settled[u] = true;

				Node* temp = list[u].getHead();
				while (temp) {
					int v = temp->destination;
					int weight = temp->weight;
					if (!settled[v] && distance[u] != INF && distance[u] + weight < distance[v]) {
						distance[v] = distance[u] + weight;
					}
					temp = temp->next;
				}
			}

			cout << "\nShortest distance from vertex " << startVertex << " to " << endVertex << " using Dijkstra's algorithm: " << distance[endVertex] << endl;

			delete[] distance;
			delete[] settled;
		}

		bool hasCycleDFS(int v, int parent) {
			isVisited[v] = true;

			Node* temp = list[v].getHead();
			while (temp) {
				int adjVertex = temp->destination;

				if (!isVisited[adjVertex]) {
					if (hasCycleDFS(adjVertex, v)) {
						return true;
					}
				} 
				else if (adjVertex != parent) {
					return true;
				}
				temp = temp->next;
			}
			return false;
		}

		bool hasCycle() {		//make bool variable here not on top for proper work
			for (int i = 0; i < numVertices; i++) {
				isVisited[i] = false;
			}
			for (int i = 0; i < numVertices; i++) {
				if (!isVisited[i]) {
					if (hasCycleDFS(i, -1)) {
						cout << "\nGraph has a cycle!" << endl;
						return true;
					}
				}
			}
			cout << "\nGraph does not have a cycle." << endl;
			return false;
		}
		
		void topologicalSortUtil(int v, bool visited[], stack<int>& stack) {
			visited[v] = true;

			Node* temp = list[v].getHead();
			while (temp) {
				int adj = temp->destination;
				if (!visited[adj]) {
					topologicalSortUtil(adj, visited, stack);
				}
				temp = temp->next;
			}

			stack.push(v);
		}

		void topologicalSort() {
			stack<int> stack;
			bool* visited = new bool[numVertices];
			for (int i = 0; i < numVertices; i++) {
				visited[i] = false;
			}

			for (int i = 0; i < numVertices; i++) {
				if (!visited[i]) {
					topologicalSortUtil(i, visited, stack);
				}
			}

			cout << "\nTopological Sort: ";
			while (!stack.empty()) {
				cout << stack.top() << " ";
				stack.pop();
			}
			delete[] visited;
		}
		
};

int main() {
	Graph graph;

	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();

	graph.addEdge(0, 1, 2);		// source - dest - weight
	graph.addEdge(0, 4, 5);
	graph.addEdge(1, 2, 4);
	graph.addEdge(1, 3, 1);
	graph.addEdge(2, 3, 3);

	cout << "After displaying all edges for every vertex: " << endl;
	graph.displayAllEdgesForAllVertices();

	cout << "After retrieving edge for vertex 1:" << endl;
	graph.retrieveEdges(1);

	graph.updateEdge(1, 3, 4, 6);		// source - olddest - newdest - weight

	cout << endl << "After updating edge for vertex 1:" << endl;
	graph.retrieveEdges(1);

	cout << endl << "After displaying all edges for every vertex: " << endl;
	graph.displayAllEdgesForAllVertices();

	cout << endl << "DFS starting from vertex 1: ";
	graph.DFS(1);
	cout << endl;

	cout << "BFS starting from vertex 1: ";
	graph.BFS(1);
	cout << endl;

    graph.topologicalSort();
	cout << endl;
		
	graph.kruskal();
	graph.prim();

	int startVertex, endVertex;
	cout << endl << "Enter the starting vertex for Dijkstra's algorithm: ";
	cin >> startVertex;
	cout << "Enter the ending vertex for Dijkstra's algorithm: ";
	cin >> endVertex;

	graph.dijkstra(startVertex, endVertex);
	return 0;
}