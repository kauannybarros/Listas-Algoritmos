//https://iudex.io/problem/62797c280b5c8500010c5dd6/statement

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct brinq {
    int S; //indice inicial de diversao
    int B; //fator de aborrecimento
    int C; //custo de creditos
};

int aborrecimento(int t, brinq brinquedo){
    int aux = brinquedo.S - (t-1)*(t-1)*brinquedo.B;
    if (aux < 0) return 0;
    else return aux;
}

void knapsack(int creditosMax, brinq brinquedos[], int num_brinq, int dp[]){
    for (int i=0; i < num_brinq; i++){
        
        for (int j = creditosMax; j >= brinquedos[i].C; j--){
           int diversaoMax = 0;
           int aux = brinquedos[i].S;
           int vezes = j/brinquedos[i].C;

           for(int k=1; k <= vezes; k++){

               int diversao = dp[j - brinquedos[i].C * k] + aux;

               if(diversao > diversaoMax){
                   diversaoMax = diversao;
               }

               aux += aborrecimento(k + 1, brinquedos[i]); //atualiza o valor da diversao a cada repeticao
           }
           
           if(diversaoMax > dp[j]){
                dp[j] = diversaoMax;
            }
        }
    }
}

int main () {
    int num_brinq; 
    cin >> num_brinq;
    brinq brinquedos[num_brinq];

    //formula: F(i,t) = S[i] - (t-1)² * B[i]

    for(int i=0; i < num_brinq; i++){

        cin >> brinquedos[i].S >> brinquedos[i].B >> brinquedos[i].C;	
    }

    int num_visitas, creditosMax = 0;
    cin >> num_visitas;
    
    int creditos[num_visitas];

    for (int i=0; i < num_visitas; i++){
        cin >> creditos[i];
        
        //fazer oq jv disse: ver qual o max de creditos possivel, assim so vai precisar calcular 1x
        if(creditos[i] > creditosMax) creditosMax = creditos[i]; 
    }

    int dp[creditosMax+1] = {0};

    knapsack(creditosMax, brinquedos, num_brinq, dp);
    
    for (int i=0; i < num_visitas; i++){
        cout << i << ": " << dp[creditos[i]] << endl;
    }
}
