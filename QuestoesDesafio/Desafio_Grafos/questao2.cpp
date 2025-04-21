//Aluna: Kauanny Karolinna D'Avalon Araujo e Barros

#include <iostream>
using namespace std;


void enqueue(int fila[], int &fimF, int value) {
    fila[fimF++] = value;
}

int dequeue(int fila[], int &inicioF) {
    return fila[inicioF++];
}

bool bfs(int V, int** adj, int inicio, int fim, int pai[], int distancia[]) {
    bool visitados[V] = {false}; 
    int fila[V];              
    int inicioF = 0, fimF = 0;     

    visitados[inicio] = true;
    distancia[inicio] = 0;
    enqueue(fila, fimF, inicio);

    while (inicioF < fimF) {
        int atual = dequeue(fila, inicioF);

        // Verifica todos os nos adjacentes
        for (int i = 0; i < V; i++) {
            if (adj[atual][i] && !visitados[i]) {
                visitados[i] = true;
                pai[i] = atual;   
                distancia[i] = distancia[atual] + 1; 

                enqueue(fila, fimF, i);

                if (i == fim) {
                    return true;
                }
            }
        }
    }

    //nao tem caminho possivel
    return false;
}

void caminho(int pai[], int inicio, int fim) {
    if (fim == inicio) {
        cout << inicio << " ";
        return;
    }

    caminho(pai, inicio, pai[fim]);
    cout << fim << " ";
}

int main() {
    int V, E;
    int inicio, fim;

    cin >> V >> E;

    int **adj;   
    adj = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        adj[i] = (int *)malloc(V * sizeof(int));
    }

    int pai[V];             
    int distancia[V];          

    for (int i = 0; i < V; i++) {
        pai[i] = -1;
        distancia[i] = -1;
    }

    for (int i=0; i < V; i++) {
        for (int j=0; j < V; j++) {
            adj[i][j] = 0;
        }
    }

    for (int i = 0; i < E; i++) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = 1;  
    }

    cin >> inicio >> fim;


    if (bfs(V, adj, inicio, fim, pai, distancia)) {
        caminho(pai, inicio, fim);
    } else {
        cout << "---" << endl;
    }

    return 0;
}
