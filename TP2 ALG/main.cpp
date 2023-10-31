#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std; 

struct Quintupla {
    long long int first;
    long long int second;
    long long int third;
    long long int forth;
    long long int fifth;

    // Constructor for convenience
    Quintupla(long long int a, long long int b, long long int c, long long int d, long long int e) : first(a), second(b), third(c), forth(d), fifth(e) {}
};

struct CompareSecond {
    bool operator()(const Quintupla& a, const Quintupla& b) const {
        if(a.second!=b.second)
        return a.second > b.second;
        else
        return a.fifth > b.fifth;
    }
};
struct Edge{
    long long int v_inicial;
    long long int v_final;
    long long int custo;
};
struct CompareCusto {
    bool operator()(const Edge& a, const Edge& b) const {
        return a.custo < b.custo; 
    }
};


void dijkstra(vector<vector<long long int>> adj, vector<vector<long long int>> pesos_tempo_travessia,vector<vector<long long int>> pesos_tempo_construcao, long long int& tempo_maximo, long long int v,vector<long long int> &custo) {
//Dijkstra
// Queremos analisar os vertices por camadas, escolheremos sempre a menor camada, de maneira a não repetir nenhum vértice que já tenha sido escolhido
// Todo caminho mínimo de a até c, caso passe por b pode ser descrito como o caminho mínimo de a até b e o caminho mínimo de b até c
// Ou seja, todo caminho mínimo é composto por caminhos mínimos
// Não faz sentido começarmos com um caminho mínimo de a até a e escolhermos o menor caminho possível a partir de a e esse não ser mínimo, pois
// todo caminho mínimo que buscamos começa em a e deve passar por a
// ou seja, o caminho mínimo de a até b é aquele composto pelas menores arestas e todo caminho mínimo que passa por b também terá esse mesmo trecho
// Dessa forma, se estamos sempre pegando as menores arestas a partir de caminhos mínimos, não faz sentido "do nada" o caminho deixar de ser mínimo
// o caminho mínimo não apresenta ciclo, pois voltar sempre será um custo a mais
// Tendo isso em vista iremos explorar o grafo por camadas, de acordo com o custo de cada vertice por caminho e sempre escolheremos o menor, 
// dessa forma teremos o menor caminho para o primeiro o vértice e por consequência o do segundo e do terceiro e...

//Criamos a o heap minimo para acessarmos sempre o menor caminho possível para os próximos vértices
priority_queue<Quintupla, vector<Quintupla>, CompareSecond> pq; //First: Vértice; Second: Valor associado ao caminho; Third: Pai
//Colocamos o vértice de partida no heap como ponto inicial
Quintupla aux(v,0,0,0,0);
pq.push(aux);
//Iremos monitorar quando o vértice é retirado da fila pela primeira vez, pois esse será o menor custo devido a construção da fila
vector<bool> popped(adj.size());
//podemos criar um count para não termos iterações desnecessárias
long long int count=0;
while(!pq.empty()){
    Quintupla vertice_menor_custo = pq.top();
    pq.pop();
    if(popped[vertice_menor_custo.first-1]==false){
        popped[vertice_menor_custo.first-1]=true;
        //Quando retiramos o vértice pela primeira vez aquela aresta é definitiva na solução, pois esse é o caminho mínimo e cada aresta da solução
        //leva a um novo vértice, portanto se quisermos saber o 'tempo máximo de construção' ou melhor, qual o maior peso secundário(um peso associado a aresta que não é o que o dijstraka está analisando)
        //nesse caminho mínimo de cada vértice, podemos fazer uma simples comparação cada vez que retiramos um vértice e ver essa propriedade secundária da aresta
        //Mas, para sabermos qual aresta foi utilizada, precisamo saber quem é o pai do vértice nesse caminho específico que gera o menor custo
        //Dessa forma, teremos (u,v)
        if(!(vertice_menor_custo.first==1))
        if(tempo_maximo<pesos_tempo_construcao[vertice_menor_custo.third-1][vertice_menor_custo.forth]) // para o primeiro vertice não teremos um custo para si mesmo em adj
        tempo_maximo=pesos_tempo_construcao[vertice_menor_custo.third-1][vertice_menor_custo.forth];
        
        //Agora olharemos para as possibilidades a partir do novo vértice e veremos em qual camada cada vizinho nos leva
        //só precisamos olhar os vizinhos quando damos o primeiro pop, pois não tem como um vizinho ter um caminho menor partindo do msm ponto sendo que o custo para esse ponto é maior
        for(long long int i=0; i<adj[vertice_menor_custo.first-1].size();i++){
        if(adj[vertice_menor_custo.first-1][i] != vertice_menor_custo.third){
        Quintupla aux(adj[vertice_menor_custo.first-1][i],vertice_menor_custo.second+pesos_tempo_travessia[vertice_menor_custo.first-1][i],vertice_menor_custo.first,i,pesos_tempo_construcao[vertice_menor_custo.first-1][i]);
        pq.push(aux);
        }
        }
        //Salvamos o custo desse vertice
        custo[vertice_menor_custo.first-1]=vertice_menor_custo.second;

        //Se já achamos o custo de todos os vértices quer dizer que na fila só possuem caminho que não são mínimos e não precisam ser explorados
        count++;
        if(count==adj.size())
        break;
    }   
}

}

//Union-Find, Kruskal

//Podemos usar o algoritmo para duas aplicações
//1-) Encontrar a AGM mínima, ou melhor para nosso contexto, o caminho mínimo que passa por todos os vértices
//2-) Aglutinar todos os vértices evitando as arestas de maior peso
/*
    Ambas aplicações possuem o mesmo efeito. Mas, qual o motivo de separar?
    a-) Qual é o min(max(E)) utilizada para conectar todos os vértices? 
    Ou seja, qual o caminho que conecta todos os vértices de forma que a aresta de maior peso utilizada seja mínima.
    Perceba que essa pergunta se encaixa mais a aplicação 2 do que com a 1.
    Porém, pela forma que o Kruskal é construído, pegando sempre a menor aresta possível, podemos afirmar que o caminho que ele encontrar
    evita as arestas de maior peso, pois ele não se baseia em um somátorio, o que poderia levar em escolher diversas arestas pequenas e uma muito grande e essa muito grande iria pesar para nossa segunda aplicação. Mas, como o Kruskal sempre pega a menor aresta possível, não precisamo preocupar com esse caso em que há uma aresta desnecessariamente grande
*/

//Internamente no vetor de nós cada vértice vai de 0 até n-1
//a componente 3 está no componentes[3]
//o pai de cada vértice respeita a numeração de 0 até n-1 e não a numeração externa dee 1 até n

void MakeSet(vector<long long int> &componentes){
    for(long long int i=0;i<componentes.size();i++){
        componentes[i]=i;
    }
}
long long int Find(long long int v,vector<long long int> &componentes){
    long long int index = v-1;
    while(componentes[index]!=index){ //Enquanto não encontrar a raiz
        index=componentes[index];
    }
    //Conecta o filho diretamente na raiz
    componentes[v-1]=index;
    return componentes[index];
}
void Union(long long int c_1, long long int c_2,vector<long long int> &componentes){
    componentes[c_1]=c_2;
}

int main() {
    long long int num_vilas = 0;
    long long int num_con = 0;
    scanf("%d %d", &num_vilas, &num_con);
    vector<vector<long long int>> adj(num_vilas); // lembrando que a posicao 0 significa vertice 1 e por ai em diante
    vector<vector<long long int>> pesos_tempo_travessia(num_vilas);
    vector<vector<long long int>> pesos_tempo_construcao(num_vilas);
    vector<vector<long long int>> pesos_custo(num_vilas);
    long long int v_inicial=0;
    long long int v_final=0;
    long long int tempo_construcao=0;
    long long int tempo_travessia=0;
    long long int custo=0;
    vector<Edge> arestas_ano_construcao(num_con);
    vector<Edge> arestas_custo(num_con);
    for (long long int i = 0; i < num_con; i++) {
        scanf("%d %d %d %d %d", &v_inicial, &v_final, &tempo_construcao, &tempo_travessia, &custo);
        // Essa parte é crucial e cria a lista de adjacencia
        adj[v_inicial - 1].push_back(v_final);
        adj[v_final - 1].push_back(v_inicial);
        // Pesos em O(1)
        pesos_tempo_travessia[v_inicial - 1].push_back(tempo_travessia);
        pesos_tempo_travessia[v_final - 1].push_back(tempo_travessia);
        pesos_tempo_construcao[v_inicial - 1].push_back(tempo_construcao);
        pesos_tempo_construcao[v_final - 1].push_back(tempo_construcao);
        pesos_custo[v_inicial - 1].push_back(custo);
        pesos_custo[v_final - 1].push_back(custo);

        //Para o Kruskal que precisamos só n/2 arestas
        Edge aux_tempo_construcao;
        aux_tempo_construcao.v_inicial=v_inicial;
        aux_tempo_construcao.v_final=v_final;
        aux_tempo_construcao.custo=tempo_construcao;
        arestas_ano_construcao[i]=aux_tempo_construcao;

        Edge aux_custo;
        aux_custo.v_inicial=v_inicial;
        aux_custo.v_final=v_final;
        aux_custo.custo=custo;
        arestas_custo[i]=aux_custo;
    }
    // Tempo Mínimo saindo do palácio real
    long long int tempo_construcao_menor_caminho = 0;
    vector<long long int> custo_minimo(adj.size());
    dijkstra(adj, pesos_tempo_travessia, pesos_tempo_construcao, tempo_construcao_menor_caminho, 1,custo_minimo);
    for (long long int i = 0; i < custo_minimo.size(); i++) {
        cout << custo_minimo[i] << endl;
    }
    cout << tempo_construcao_menor_caminho << endl;

    //Primeiro ano a partir do qual é possível chegar em qualquer vila do reino a partir do palácio real
    vector<long long int> componentes_ano (num_vilas);
    MakeSet(componentes_ano);
    sort(arestas_ano_construcao.begin(),arestas_ano_construcao.end(),CompareCusto());
    long long int count_ano=0;
    for(long long int i=0;i<arestas_ano_construcao.size();i++){
        long long int c_1=Find(arestas_ano_construcao[i].v_inicial,componentes_ano);
        long long int c_2=Find(arestas_ano_construcao[i].v_final,componentes_ano);
        if(c_1!=c_2){//se a aresta atravessa o corte
            Union(c_1,c_2,componentes_ano);
             count_ano++;
            if(count_ano==(num_vilas-1)){ //se já fizemos o número de conexões máximas, interrompe
            cout<<arestas_ano_construcao[i].custo<<endl;//a ultima deve ser a maior
            break;
            }
        }
    }

    vector<long long int> componentes_custo (num_vilas);
    long long int resultado=0;
    MakeSet(componentes_custo);
    sort(arestas_custo.begin(),arestas_custo.end(),CompareCusto());
    long long int count_custo=0;
    for(long long int i=0;i<arestas_custo.size();i++){
        long long int c_1=Find(arestas_custo[i].v_inicial,componentes_custo);
        long long int c_2=Find(arestas_custo[i].v_final,componentes_custo);
        if(c_1!=c_2){//se a aresta atravessa o corte
            Union(c_1,c_2,componentes_custo);
            resultado += arestas_custo[i].custo;
            count_custo++;
            if(count_custo==(num_vilas-1)){ //se já fizemos o número de conexões máximas, interrompe
            cout<<resultado<<endl;//a ultima deve ser a maior
            break;
        }
        }
    }


    return 0;
} 