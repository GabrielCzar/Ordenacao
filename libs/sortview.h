#ifndef SORTVIEW_H
#define SORTVIEW_H

#include <SFML/Graphics.hpp>

#include "player.h"

#include <queue>
#include <sstream>
#include <vector>

class SortView{
private:
    int _begin;
    int _end;
    enum ViewOption{BAR, DOT};
    ViewOption _voption;
    float _thick;
    sf::RenderTexture painel;

public:
    SortView()
    {
        _begin = 0;
        _end = 0;
        _voption = BAR;
        _thick = 2.0;
        painel.create(800, 600);
    }


    void set_faixa(int begin, int end){
        _begin = begin;
        _end = end;
    }

    void set_bar_view(){
        _voption = BAR;
    }

    void set_dot_view(){
        _voption = DOT;
    }

    void set_thickness(float thick){
        _thick = thick;
    }

    void show(const std::vector<int> &vet, std::vector<int> pos = {}, std::string cores = ""){
        if(my_window->isOpen() == false)
            return;

        painel.clear();
        auto dim = painel.getSize();
        int offleft = 50;
        int offdown = 50;
        ColorMap * cmap = ColorMap::get_instance();
        int tam = vet.size();
        float xfator = (dim.x - 100) / (float)tam;
        for(int x = 0; x < tam; x++){
            sf::Color cor_linha = sf::Color::White;
            for(int k = 0; k < (int)pos.size(); k++){
                if(x == pos[k]){
                    cor_linha = cmap->get(cores[k]);
                }
            }

            if(_voption == BAR){
                painel.draw(sfLine(sf::Vector2f(xfator * x + offleft, dim.y - offdown),
                                     sf::Vector2f(xfator * x + offleft, dim.y - offdown - vet[x]),
                                     _thick, cor_linha));
            }else{
                painel.draw(sfLine(sf::Vector2f(xfator * x + offleft, dim.y - vet[x] + 5 - offdown),
                             sf::Vector2f(xfator * x + offleft, dim.y - vet[x] - offdown),
                                   _thick, cor_linha));
            }
        }
        if(pos.size() > 0)
            painel.draw(sfLine(sf::Vector2f(xfator * _begin - 3 + offleft, dim.y - offdown + 5),
                             sf::Vector2f(xfator * _end + 3   + offleft, dim.y - offdown + 5),
                                   _thick, sf::Color::Yellow));

        painel.display();
        my_player->_push(painel.getTexture());
    }
};
#endif

