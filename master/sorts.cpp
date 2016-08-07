#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <list>

#include "../libs/sortview.h"
#include "../libs/player.h"

static SortView sview;

using namespace std;

vector<int> init_vet(int qtd, int min, int max){
    vector<int> vet;
    vet.reserve(qtd);
    for(int i = 0; i < qtd; i++)
        vet.push_back(rand() % (max - min + 1) + min);
    return vet;
}

void visualizarNum(vector<int> vet){
    for (int i = 0; i < (int)vet.size(); ++i)
        cout << vet[i] << " ";
    cout << endl;
}

void visualizarNum(list<int> lista){
    for (int i = 0; i < (int)lista.size(); ++i){
        cout << lista.front() << " ";
        lista.pop_front();
    }
    cout << endl;
}

void minimum_sort(vector<int> &vet){
    int tam = (int)vet.size();
    for(int i = 0; i < tam - 1; i++){
        for(int j = i + 1; j < tam; j++){
            sview.show(vet, {i, j}, "gb");
            if(vet[j] < vet[i]){
                sview.show(vet, {i, j}, "rb");
                std::swap(vet[i], vet[j]);
                sview.show(vet, {i, j}, "cb");
            }
        }
    }
}

void insertion2(vector<int> &vet){
    for (int i = 1; i < (int)vet.size(); ++i) {
        sview.show(vet, {i}, "g");
        for (int j = i; j > 0; --j) {
            if(vet[j] < vet[j-1]){
                sview.show(vet, {i, j-1}, "rb");
                swap(vet[j], vet[j-1]);
            }
        }
    }
}

void insertion(vector<int> &vet){
    for (int i = 1; i < (int)vet.size(); ++i) {
        sview.show(vet, {i}, "g");
        if(vet[i] < vet[i-1]){
            for (int j = i; j > 0; --j) {
                if(vet[j] < vet[j-1]){
                    sview.show(vet, {i, j-1}, "rb");
                    swap(vet[j], vet[j-1]);
                }
            }
        }
    }
}

void insertion3(list<int> &lista){ //Listas
    for (auto i = lista.begin(); i != lista.end(); i++)
        for (auto j = i, k = i; j != lista.begin() && k != lista.begin(); j--)
            if(*j < *(--k))
                swap(*j, *k);
}

void selection(vector<int> &vet){ //Minimun sort
    for (int i = 0; i <= (int)vet.size(); ++i) {
        int menor = i;
        int maior = (vet.size()-1)-i;
        for (int j = i; j < maior; ++j) {
            if(vet[j] < vet[menor])
                swap(vet[j], vet[menor]);
            if(vet[j] > vet[maior])
                swap(vet[j], vet[maior]);
            sview.show(vet, {i, j-1}, "rb");
        }
    }
}

void buble_sort(vector<int> &vet){
    for (int i = 0; i < (int)vet.size(); ++i) {
        for (int j = 0; j < (int)vet.size(); ++j) {
            if(vet[i] < vet[j])
                swap(vet[i], vet[j]);
            sview.show(vet, {i, j}, "rb");
        }
    }
}

void join(vector<int> &vet, int inicio, int meio, int fim){
    int i = inicio, j = meio + 1;
    vector<int> aux;
    aux.reserve(vet.size());

    while(i < meio + 1 || j < fim + 1) {
        if (i == meio + 1 ) aux.push_back(vet[j++]); // i terminou, entao v[j] tem o ultimo
        else if (j == fim + 1) aux.push_back(vet[i++]); // j terminou, entao v[i] tem o ultimo
        else if (vet[i] < vet[j]) aux.push_back(vet[i++]);
        else aux.push_back(vet[j++]);
    }
    for(int i = inicio; i <= fim; i++) vet[i] = aux[i - inicio];

    sview.show(vet, {inicio, fim}, "rb");
}

void mergesort(vector<int> &vet, int inicio, int fim){
    if(inicio == fim) return;
    int meio = (inicio + fim) / 2;
    mergesort(vet, inicio, meio);
    mergesort(vet, meio + 1, fim);
    join(vet, inicio, meio, fim);
}

template<class Iter> void mergesort2(vector<int> &vet, Iter inicio, Iter fim){
    if((fim - inicio) < 2) return;
    Iter meio = inicio + (fim - inicio) / 2;
    mergesort2(vet, inicio, meio);
    mergesort2(vet, meio, fim);
    std::inplace_merge(inicio, meio, fim);
    sview.show(vet, {inicio, fim}, "rb");
}

void functionJoin(vector<int> &vet, int inicio, int meio, int fim){
    list<int> left(vet.begin() + inicio, vet.begin() + meio);
    list<int> right(vet.begin() + meio, vet.begin() + fim);
    while(!left.empty() && !right.empty()){
        auto &lista = left.front() < right.front() ? left : right;
        vet[inicio++] = lista.front();
        lista.pop_front();
    }
    vet[inicio] = left.empty() ? right.front() : left.front();
}

void mergesort3(vector<int> &vet, int inicio, int fim){
    if((fim - inicio) < 2) return;
    int meio = (fim + inicio) / 2;
    mergesort3(vet, inicio, meio);
    mergesort3(vet, meio, fim);
    functionJoin(vet, inicio, meio, fim);
}

void quick(vector<int> &vet, int inicio, int fim){
    int pivo = vet[rand() % (fim - inicio) + inicio], i = inicio, j = fim; // Pivo e um valor do vector

    while(i <= j){ //separa os lados LEFT - MENORES & RIGHT - MAIORES
        while(vet[i] < pivo && i < fim) i++; //Encontrei um valor maior que o pivo
        while(vet[j] > pivo && j > inicio) j--; //Encontrei um valor menor que o pivo
        if(i <= j) swap(vet[i++], vet[j--]); //Para garantir que nenhum valor seja discrepante
        sview.show(vet, {inicio, pivo, fim}, "rgb");
    }

    if(j > inicio) //Existe valores antes do pivo
        quick(vet, inicio, j);
    if(i < fim) //Existe valores apos o pivo
        quick(vet, i, fim);

}

//Temos 10 baldes
//qtd começa em 1, para cada vez q executar (no caso, tem valores para ordenar) * 10
int contDig(int num){
    int cont = 1;
    while(num/=10)
        cont++;
    return cont;
}

int maximo(vector<int> vet){
    int max = 0;
    for (int i = 0; i < (int) vet.size(); ++i) {
        int a = contDig(vet[i]);
        if(a > max) max = a;
    }
    return max;
}

int cont = 0;
void bucket(vector<int> &vet, int qtd, int max){
    if(cont++ > max) return;

    vector<int> values;
    vector< vector<int> > baldes;
    baldes.reserve(10);
    values.reserve(10);

    for (int i = 0; i < 10; ++i) {
        values.clear();
        for (int j = 0; j < (int)vet.size(); ++j) {
            int pos = vet[j] / qtd;
            int resto = pos % 10;
            if(resto == i)
                values.push_back(vet[j]);
        }
        baldes.push_back(values);
    }
    vet.clear();
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < (int)baldes[i].size(); ++j){
            vet.push_back(baldes[i][j]);
            sview.show(vet, {i} , "w");
        }
    bucket(vet, qtd * 10, max);
}



int main_sorts(){
    srand(time(NULL));
    my_player->autoplay = true;

    sview.set_bar_view();
    sview.set_thickness(8);

    vector<int> vet = init_vet(70, 50, 300);

    //minimum_sort(vet);

    //insertion(vet);

    //selection(vet);

    //buble_sort(vet);

    //mergesort(vet, 0, vet.size() - 1);

    //quick(vet, 0, vet.size() - 1);

    //bucket(vet, 1, maximo(vet));

    //insertion(vet);

    //mergesort(vet, 0, vet.size() - 1);

    //mergesort2(vet, vet.begin(), vet.end()); //Merge sort com Iteradores

    //visualizarNum(vet);

    //mergesort3(vet, 0, vet.size()); //Implementacao gamb com lista

    //list<int> lista(vet.begin(), vet.end());

    //insertion3(lista);

    visualizarNum(lista);

    my_player->wait();

    return 0;
}

int main(){
    main_sorts();
}
