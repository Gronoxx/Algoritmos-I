#include <iostream>
#include <math.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

struct Ponto {
int i;
double x, y;
bool operator==(const Ponto& other) const {
        return x == other.x && y == other.y;
}
};

double PolarAngle(Ponto p, Ponto q) {
return atan2(q.y - p.y, q.x - p.x);
}

struct Edge{
    bool visited;
    int id_final;
    double angle;
};

int main(){
    using namespace std;
    //Vetor para guardar as coordenadas de cada vértice
    vector<Ponto> vertices;
    //Vetor que guarda os adjacentes de cada vértice
    std::vector<std::vector<int>> VerticesAdj;
    //Recebe da primeira linha do arquivo a quantidade de vértices e arestas
    int qntd_vertices=0;    
    cin>> qntd_vertices; // vertices
    int qntd_arestas;
    cin>> qntd_arestas; // arestas
    
    //Preencher os vetores "vertices" e "VerticesAdj"
    int index = 1;
    for(int i=0;i<qntd_vertices;i++) {
        std::vector<int> subVector;
        //Pega cada coordenada e cria o ponto correspondente
        double number; 
        cin >> number;
        Ponto p;
        p.i = index;
        p.x = number;
        cin >> number;
        p.y = number;
        vertices.push_back(p);
        //Pega o grau e armazena cada vértice adjacente
        int grau=0;
        cin >> grau;// pega o grau do vertice
        for(int count=0;count<grau;count++) { // pega os vertices adjacentes e coloca no subvetor daquele vertice
            cin >> number;
            subVector.push_back(number);
        }
        VerticesAdj.push_back(subVector);
        index++;
    }

    vector<vector<Edge>> arestas;

    //Precisamos encontrar os ângulos de cada aresta

    //Para cada par de adjacencia se calcula o ângulo, gera a aresta e a adiciona no hashmap de acordo com o ponto de partida
    for(int i=0;i<VerticesAdj.size();i++){
        vector<Edge> subaresta;
        for(int count=0;count<VerticesAdj[i].size();count++){
            double angle= PolarAngle(vertices[i],vertices[VerticesAdj[i][count]-1]);
            Edge aux = {false,VerticesAdj[i][count],angle};
            subaresta.push_back(aux);
        }
        sort(subaresta.begin(), subaresta.end(), [](const Edge& a, const Edge& b) {
        // Implement your comparison logic here
        return a.angle < b.angle;
        });
        arestas.push_back(subaresta);
    }
    //Preciso saber o pai, vértice que eu vim, para encontrar a aresta dele e encontrar o ângulo formado, a partir daí pego o ângulo imediatamente maior sendo essa minha aresta no anti-horário    
    std::vector<std::vector<int>> faces;
    for(int i=1 ; i<=arestas.size();i++){
        for(int edge_id=0;edge_id<arestas[i-1].size();edge_id++){
            //Vamos passar por todas as arestas do hashmap, pulando aquelas que já forma visitadas. Lembrando que como o grafo está direcionado cada aresta é visitada uma única vez
            if(arestas[i-1][edge_id].visited){
                continue;
            }
            Edge * e= &(arestas[i-1][edge_id]); //Estamos pegando a aresta que sai do vértice i e vai para o vértice [i][edge_id]
            int v=i;
            vector<int> face;
            while(!e->visited){
                e->visited=true;
                face.push_back(v);
                //Precisamos encontrar o ângulo formado pelo caminho inverso e usá-lo como referência
                for(int index=0;index<arestas[e->id_final-1].size();index++){
                    if(arestas[e->id_final-1][index].id_final==v){ // n eh possivel acessar o indice do hashmap pelo indice igual de um vetor
                       if(index==0){
                        v=e->id_final;
                        e=&(arestas[e->id_final-1][arestas[e->id_final-1].size()-1]);
                        break;
                        }
                        else{
                        v=e->id_final;
                        e=&(arestas[e->id_final-1][index-1]);
                        break;
                        } 
                    }
                }
            }
            face.push_back(v);
            faces.push_back(face);
        }
    }

    cout<<faces.size()<<endl;
    for (const std::vector<int>& face : faces) {
        cout<<face.size()<<" ";
        for (int elemento : face) {
            std::cout << elemento << " ";
        }
        std::cout << std::endl;
    }
    
    



    return 0;
}