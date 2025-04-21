//https://iudex.io/problem/6195d96b97713f0001037a14/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int INF = 9999999; // se for inf, nao tem aresta

struct Aresta {
    int custo = INF;
    int destino = -1;
};

int prim(int **matriz_adj, int M) {

    int custoTotal = 0;
    bool incluido[M] = {false}; 
    Aresta menorAresta[M];
    menorAresta[0].custo = 0;

    for (int i=0; i < M; i++) {
        int vert = -1;
        
        for (int j = 0; j < M; j++) {
            
            if (!incluido[j] && (vert == -1 || menorAresta[j].custo < menorAresta[vert].custo)){ //se nao foi selecionado e tem custo menor
                vert = j;
            }
        }

        incluido[vert] = true; //inclui o vertice achado
        custoTotal += menorAresta[vert].custo; //soma o custo dele no total

        for (int j = 0; j < M; j++) {
            if (matriz_adj[vert][j] < menorAresta[j].custo) {
                menorAresta[j].custo = matriz_adj[vert][j];
                menorAresta[j].destino = vert;
            }
        }
    }

    return custoTotal;
}

int main () {
    int M, N; // M- num aeroportos, N- num trechos
    cin >> M >> N;

    int **matriz_adj = new int*[M]; //matriz de adjacencia
    for (int i = 0; i < M; i++) {
        matriz_adj[i] = new int[M];
        
        for (int j = 0; j < M; j++){
            matriz_adj[i][j] = INF; //inicia tudo como inf (nao tem aresta conectando)
        }
    }
    

    for (int i = 0; i < N; i++) {
        int aeroA, aeroB, custo;
        cin >> aeroA >> aeroB >> custo;
        matriz_adj[aeroA][aeroB] = custo;
        matriz_adj[aeroB][aeroA] = custo;
    }

    int custoTotal = prim(matriz_adj, M);
    cout << custoTotal << endl;

    for (int i = 0; i < M; i++){
        delete[] matriz_adj[i];
    }

    delete[] matriz_adj;
}
