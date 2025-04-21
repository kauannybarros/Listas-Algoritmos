//https://iudex.io/problem/6195d96b97713f0001037a14/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int INF = 99999999; //se for inf, nao tem aresta

int dijkstra(int **adj, int A, int B, int Q) {

    int dist[Q];
    int antecessor[Q];
    bool visitados[Q];

    //bota tudo como inf e falso
    for (int i = 0; i < Q; i++) {
        dist[i] = INF;
        antecessor[i] = -1;
        visitados[i] = false;
    }

    dist[A] = 0; //distancia de A p A eh 0

    for (int i = 0; i < Q; i++) {
        int v = -1;

        for (int j = 0; j < Q; j++) {
            if (!visitados[j] && (v == -1 || dist[j] < dist[v])) {    //se nao foi visitado e a distancia eh menor
                v = j;
            }
        }

        //nao tem caminho 
        if (dist[v] == INF){
            break;
        }

        visitados[v] = true;

        if (v == B) { //se ja chegou
            return dist[B];
        }

        for (int j = 0; j < Q; j++) {
            if (adj[v][j] != INF) { 
                int aux = adj[v][j];
                if (dist[v] + aux < dist[j]) { //se a distancia de A p v + v p j eh menor q A p j
                    dist[j] = dist[v] + aux; 
                    antecessor[j] = v;  
                }
            }
        }
    }

    return dist[B];
}

int main() {
    int Q, R, N; // Q- total de quadras, R- total de ruas, N- num de eventos
    cin >> Q >> R >> N;

    int **matriz_adj = new int*[Q]; 
    for (int i = 0; i < Q; i++) {
        matriz_adj[i] = new int[Q];
        
        for (int j = 0; j < Q; j++) {
            matriz_adj[i][j] = INF; //bota tudo como inf
        }
    }

    for (int i = 0; i < R; i++) {
        int A, B, M; //rua A, B, tempo
        cin >> A >> B >> M;
        matriz_adj[A][B] = M;
    }

    cin.ignore();
    
    for (int i = 0; i < N; i++) {
        string linha;
        getline(cin, linha); 
        stringstream ss(linha);
        int tipo;
        ss >> tipo;
        int A, B;
        ss >> A >> B;

        if (tipo == 1) {
            //atualiza o tempo da rua
            int M;
            ss >> M;
            matriz_adj[A][B] = M;
        } else {
            //ver o tempo de A p B
            int menorT = dijkstra(matriz_adj, A, B, Q);

            if (menorT == INF) { //nao tem caminho conectando
                cout << "-1" << endl;
            }
            else{
                cout << menorT << endl;
            }
        }
    }

    for (int i = 0; i < Q; i++) {
        delete[] matriz_adj[i];
    }

    delete[] matriz_adj;
}
