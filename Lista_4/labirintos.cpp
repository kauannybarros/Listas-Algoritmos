//https://iudex.io/problem/618cdff697713f00010377c8/statement

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct No {
    int x, y; //posicao no lab
    int dist; 
};

void enqueue(No fila[], int &fimF, int x, int y, int dist) {
    fila[fimF].x = x;
    fila[fimF].y = y;
    fila[fimF].dist = dist;
    fimF++;
}

No dequeue(No fila[], int &inicioF) {
    return fila[inicioF++];
}

int bfs(int **labirinto, int M, int N, int inicio[], int destino[]) {
   
    //bool visitado[M][N] = {false}; //marca todos como nao visitados
   
    bool **visitado = new bool*[M];
    for (int i = 0; i < M; i++) {
        visitado[i] = new bool[N];
        for (int j = 0; j < N; j++) {
            visitado[i][j] = false;
        }
    }

    No fila[M * N];
    int inicioFila = 0, fimFila = 0;

    visitado[inicio[0]][inicio[1]] = true;
    enqueue(fila, fimFila, inicio[0], inicio[1], 0);

    while (inicioFila < fimFila) {
        No atual = dequeue(fila, inicioFila);

        //chegou no 3
        if (atual.x == destino[0] && atual.y == destino[1]) {
            delete []visitado;
            return atual.dist;
        }

        //ver pra onde pode andar
        //direita
        if (atual.x + 1 < M && labirinto[atual.x + 1][atual.y] != 1 && !visitado[atual.x + 1][atual.y]) {
            visitado[atual.x + 1][atual.y] = true;
            enqueue(fila, fimFila, atual.x + 1, atual.y, atual.dist + 1);
        }

        //esquerda
        if (atual.x - 1 >= 0 && labirinto[atual.x - 1][atual.y] != 1 && !visitado[atual.x - 1][atual.y]) {
            visitado[atual.x - 1][atual.y] = true;
            enqueue(fila, fimFila, atual.x - 1, atual.y, atual.dist + 1);
        }

        //baixo
        if (atual.y + 1 < N && labirinto[atual.x][atual.y + 1] != 1 && !visitado[atual.x][atual.y + 1]) {
            visitado[atual.x][atual.y + 1] = true;
            enqueue(fila, fimFila, atual.x, atual.y + 1, atual.dist + 1);
        }

        //cima
        if (atual.y - 1 >= 0 && labirinto[atual.x][atual.y - 1] != 1 && !visitado[atual.x][atual.y - 1]) {
            visitado[atual.x][atual.y - 1] = true;
            enqueue(fila, fimFila, atual.x, atual.y - 1, atual.dist + 1);
        }
    }

    //se nao encontrou
    delete []visitado;
    return -1;
}

int main() {
    int M, N;
    cin >> M >> N;

    int **labirinto = (int **)malloc(M * sizeof(int *));
    int inicio[2], destino[2];

    for (int i = 0; i < M; i++) {
        labirinto[i] = (int *)malloc(N * sizeof(int));
        for (int j = 0; j < N; j++) {
            cin >> labirinto[i][j];
            if (labirinto[i][j] == 2) {
                inicio[0] = i;
                inicio[1] = j;
            }
            if (labirinto[i][j] == 3) {
                destino[0] = i;
                destino[1] = j;
            }
        }
    }

    int resultado = bfs(labirinto, M, N, inicio, destino);

    if (resultado != -1) {
        cout << resultado << endl;
    } else {
        cout << "Labirinto Impossivel" << endl;
    }

    for (int i = 0; i < M; i++) {
        free(labirinto[i]);
    }
    free(labirinto);

    return 0;
}

