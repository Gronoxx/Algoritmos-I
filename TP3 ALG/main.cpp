#include <iostream>
#include <vector>
#include <algorithm>
#include <utility> 
#include <cmath>
#include <bitset>
#include <climits>

using namespace std;

struct Manobra{
    int pontuacao;
    int tempo;
    int id;   
    Manobra(int f, int s, int t) : pontuacao(f), tempo(s), id(t) {} 
};
struct Celula{
    long long pont;
    bitset<10> manobras;
};

bool compareSecondElement(const Manobra& a, const Manobra& b) {
    return a.tempo < b.tempo;
}

struct Pista{
    int bonificacao;
    int tempo;
    Pista(int f, int s) : bonificacao(f), tempo(s) {} 
};

int binarySearch(vector<Manobra>& arr, int l, int r, int x)
{
    while (l <= r) {
        int m = l + (r - l) / 2;
 
        // Check if x is present at mid
        if (arr[m].tempo == x){
            while(arr[m].tempo==arr[m+1].tempo){
                if(m==arr.size()-1){//se estamos no ultimo index pare
                m--;
                break;
                }
                m++;
            }
            return m+1;  
        }

 
        // If x greater, ignore left half
        if (arr[m].tempo < x)
            l = m + 1;
 
        // If x is smaller, ignore right half
        else
            r = m - 1;
    }
 
    // If we reach here, then element was not present
    return l;
}

void table_creation(vector<vector<long long>> &Matriz,vector<Manobra> manobras){ //X: manobras a fazer  Y:manobras feitass na secao passada
    int size = Matriz.size();
    for(int lin=0;lin<size;lin++){
        for(int col=0;col<size;col++){
            int pontuacao_celula=0;
            int qntd_manobras=0;
            bitset<10> bitset1 (col); //X
            bitset<10> bitset2 (lin); //Y
            for(int i=0;i<10;i++){
                if(bitset1[i]==1){
                    if(bitset2[i]==1){
                        pontuacao_celula += manobras[i].pontuacao/2;
                    }
                    else{
                        pontuacao_celula += manobras[i].pontuacao;
                    }
                    qntd_manobras++;
                }
            }
            Matriz[lin][col] = pontuacao_celula * qntd_manobras;
        }
    }


}

int main(){
    int n,k;
    cin>>n;
    cin>>k;
    vector<Pista> secoes;
    vector<Manobra> manobras;
    vector<int> bonificacoes;

    //Recebe entrada da pista
    for(int i=0;i<n;i++){
        int bonificacao,tempo;
        cin>>bonificacao;
        cin>>tempo;
        Pista aux (bonificacao,tempo);
        secoes.push_back(aux);
        bonificacoes.push_back(bonificacao);
    }
    //Recebe entrada da manobra
    for(int i=0;i<k;i++){
        int pontuacao,tempo;
        cin>>pontuacao;
        cin>>tempo;
        Manobra aux (pontuacao,tempo,i+1);
        manobras.push_back(aux);
    }


    //Ordena as manobras em ordem crescente de tempo

    
    std::sort(manobras.begin(), manobras.end(), compareSecondElement);

    vector<vector<int>> manobras_possiveis_por_secao(n);
    int max_size=0;
    
    //calculando quais manobras sao possiveis naquela pista
    for(int i=0;i<n;i++){
    //limite superior de manobra
    int size = binarySearch(manobras,0,manobras.size()-1,secoes[i].tempo);
    if(int(pow(2,size))>max_size){  
        max_size=int(pow(2,size));
    }
    //combinaçõoeos possiveis dentro desse limite
    for(int man=0;man<int(pow(2,size));man++){
        bitset<10> bit_man(man);
        int tempo_conjunto=0;
        for(int count=0;count<10;count++){
            if(bit_man[count]==1){
                tempo_conjunto+=manobras[count].tempo;
                if(tempo_conjunto>secoes[i].tempo)
                break;
            }
        }
        if(tempo_conjunto<=secoes[i].tempo)
        manobras_possiveis_por_secao[i].push_back(man);
    }
    }

    vector<vector<long long>> pontos (max_size, std::vector<long long>(max_size));
    table_creation(pontos,manobras);
    vector<int> manobras_usadas_section(n);



     std::vector<std::vector<Celula>> f(n, std::vector<Celula>(max_size, {LLONG_MIN}));

    for(int i=n-1;i>=0;i--){ //secao

    for(int m=0;m<max_size;m++){ //manobra antiga
    
    //queremos descobrir a melhor manobra dada a manobra anterior
    for(int count=0; count<manobras_possiveis_por_secao[i].size(); count++){//manobras atuais
        if(i==n-1){
        if(f[i][m].pont< 0 + pontos[m][manobras_possiveis_por_secao[i][count]] * bonificacoes[i]){
        f[i][m].pont= 0 + pontos[m][manobras_possiveis_por_secao[i][count]] * bonificacoes[i];     
        bitset<10> aux(manobras_possiveis_por_secao[i][count]);
        f[i][m].manobras= aux;
        }
        }
        else if(f[i][m].pont< f[i+1][manobras_possiveis_por_secao[i][count]].pont + pontos[m][manobras_possiveis_por_secao[i][count]] * bonificacoes[i]){
        f[i][m].pont= f[i+1][manobras_possiveis_por_secao[i][count]].pont + pontos[m][manobras_possiveis_por_secao[i][count]] * bonificacoes[i];   
        bitset<10> aux(manobras_possiveis_por_secao[i][count]);
        f[i][m].manobras= aux;
        }
    }
    
    }
    }
    long long max_value = LLONG_MIN;
    int index=0;
    for (int i = 0; i < n; ++i) {
        if (f[i][0].pont > max_value) {
            max_value = f[i][0].pont;
            index=i;
        }
    }

    // Imprimir o maior valor encontrado
    std::cout << max_value << std::endl;

    for(int i=0;i<n;i++){
        vector<int> id_manobras;
        bitset<10> confg = f[i][index].manobras;
        for(int count=0;count<10;count++){
            if(confg[count]==1){
                id_manobras.push_back(manobras[count].id); //MUDAR PARA ID
            }
        }
        cout<<id_manobras.size();
        for(int size=0;size<id_manobras.size();size++){
            cout<<" "<<id_manobras[size];
        }
        index = f[i][index].manobras.to_ulong();
        cout<<endl;
    }





    return 0;
}