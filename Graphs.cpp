#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(NULL) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(NULL) {}

    void addNode(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
        } 
		else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void removeNode(int value) {
        Node* temp = head;
        Node* prev = NULL;

        while (temp && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }
        if (temp) {
            if (prev) {
                prev->next = temp->next;
            } 
			else {
                head = temp->next;
            }
            delete temp;
        }
    }

    void displayList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
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
    LinkedList* adjacencyList;
    int numVertices;

public:
    Graph() {
    	adjacencyList = NULL;
		numVertices = 0; 
	}
	
    void addVertex() {
        LinkedList* newList = new LinkedList[numVertices + 1];

        for (int i = 0; i < numVertices; ++i) {
            newList[i] = adjacencyList[i];
        }
        delete[] adjacencyList;

        adjacencyList = newList;
        ++numVertices;
    }

    void addEdge(int source, int destination) {			//undirected graph
        adjacencyList[source].addNode(destination);
        adjacencyList[destination].addNode(source);  
    }

    void updateEdge(int source, int oldDestination, int newDestination) {
        adjacencyList[source].removeNode(oldDestination);
		adjacencyList[source].addNode(newDestination);
        
		adjacencyList[newDestination].removeNode(source);
		adjacencyList[newDestination].addNode(source);
    }

    void retrieveEdges(int vertex) {
        cout << "Edges for vertex " << vertex << ": ";
        adjacencyList[vertex].displayList();
    }
    
    void displayAllEdgesForAllVertices() {
        for (int i = 0; i < numVertices; ++i) {
            cout << "All Edges for vertex " << i << ": ";
       		adjacencyList[i].displayList();
        }
    }
    
    //DFS function
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

        Node* temp = adjacencyList[vertex].getHead();
        while (temp) {
            int adjVertex = temp->data;
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

            Node* temp = adjacencyList[currentVertex].getHead();
            while (temp) {
                int adjVertex = temp->data;
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    queue[rear++] = adjVertex;
                }
                temp = temp->next;
            }
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

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
	
	cout<<"After retrieving edge for vetix 1:"<<endl;
    graph.retrieveEdges(1);
	
    graph.updateEdge(1,3,4);
	
	cout<<endl<<"After updating edge for vetix 1:"<<endl;
    graph.retrieveEdges(1);
    
    cout<<endl<<"After displaying all edges for every vertix: "<<endl;
    graph.displayAllEdgesForAllVertices();
    
    cout << endl << "DFS starting from vertex 1: ";
    graph.DFS(1);
    cout << endl;

    cout << "BFS starting from vertex 1: ";
    graph.BFS(1);
    cout << endl;
    
    return 0;
}
