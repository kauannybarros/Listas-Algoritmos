//Aluna: Kauanny Karolinna D'Avalon Araujo e Barros

#include <iostream>
using namespace std;

void push(int Pilha[], int &top, int v) {
    Pilha[++top] = v;
}

int pop(int Pilha[], int &top) {
    return Pilha[top--];
}

void visitaTop(int v, int V, int** adj, bool visitados[], int Pilha[], int &top) {
    // marca o no atual como visitado
    visitados[v] = true;

    //vai pra todos os nos adjacentes
    for (int i = 0; i < V; i++) {
        if (adj[v][i] && !visitados[i]) {
            visitaTop(i, V, adj, visitados, Pilha, top);
        }
    }

    push(Pilha, top, v);
}

void ordenaTop(int V, int** adj, bool visitados[], int Pilha[], int &top) {
    //bota todos os nos como nao visitados
    for (int i = 0; i < V; i++) {
        visitados[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (!visitados[i]) {
            visitaTop(i, V, adj, visitados, Pilha, top);
        }
    }

    while (top != -1) {
        cout << pop(Pilha, top) << ",";
    }
}

int main() {

    int V, A; //num de vertices e arestas

    cin >> V >> A;

    int **adj; // matriz de adjacencia
    adj = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        adj[i] = (int *)malloc(V * sizeof(int));
    }

    bool visitados[V]; // vetor de visitados
    int Pilha[V];
    int top = -1;

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < A; i++) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1; 
    }

    ordenaTop(V, adj, visitados, Pilha, top);

    return 0;
}
