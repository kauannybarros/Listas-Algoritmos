//https://iudex.io/problem/5bcc95305cd44b0001fdbf74/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

void enqueue(int fila[], int &fimF, int value) {
    fila[fimF++] = value;
}

int dequeue(int fila[], int &inicioF) {
    return fila[inicioF++];
}

void bfs(int N, int adj[][6], int inicio, int componente[], int contador) {
    int fila[N];
    int inicioF = 0, fimF = 0;

    componente[inicio] = contador;
    enqueue(fila, fimF, inicio);

    while (inicioF < fimF) {
        int atual = dequeue(fila, inicioF);

        for (int i = 1; i <= adj[atual][0]; i++) {
            int aux = adj[atual][i];
            if (componente[aux] == -1) { // se ainda nao visitado
                componente[aux] = contador; 
                enqueue(fila, fimF, aux);
            }
        }
    }
}

int main() {
    int K; // num de casos
    cin >> K;
    for (int k = 0; k < K; k++) {
        int N, M, Q; //tam do lab, qntd de removidas, qntd de consultas
        cin >> N >> M >> Q;

        int lista_adj[N*N][6]; //lista de adjacencia
        for (int i = 0; i < N*N; i++) {
            lista_adj[i][0] = 1;
            lista_adj[i][1] = i;
        }

        //ler todas as paredes removidas
        for (int i = 0; i < M; i++) {
            int parede;
            cin >> parede;
            if (parede % (2*N - 1) < N - 1) {
                //eh uma parede vertical
                int linha = parede / (2 * N - 1);
                int coluna = parede % (2 * N - 1);
                int x = linha * N + coluna;

                lista_adj[x][++lista_adj[x][0]] = x + 1;
                lista_adj[x+1][++lista_adj[x+1][0]] = x;
            } 
            
            else {
                //eh uma parede horizontal
                int linha = (parede - (N - 1)) / (2 * N - 1);
                int coluna = (parede % (2 * N - 1)) - (N - 1);
                int x = linha * N + coluna;
                
                lista_adj[x][++lista_adj[x][0]] = x + N;
                lista_adj[x+N][++lista_adj[x+N][0]] = x;
            }
        }


        //fazer oq Pierre falou: uma lista de componentes p ver todos os nos que da pra se alcancar entre si
        int componente[N*N];
        for (int i = 0; i < N*N; i++) {
            componente[i] = -1;
        }

        int contador = 0;
        for (int i = 0; i < N*N; i++) {
            if (componente[i] == -1) { //se ainda nao foi visitado, chama o bfs pra ir marcando os possiveis 
                bfs(N*N, lista_adj, i, componente, contador);
                contador++;
            }
        }

        //ler todas as posicoes
        for (int i = 0; i < Q; i++) {
            int inicio, fim;
            cin >> inicio >> fim;

            if (componente[inicio] == componente[fim]) {
                cout << k << "." << i << " 1" << endl;
            } else {
                cout << k << "." << i << " 0" << endl;
            }
        }

        cout << endl;
    }
}
