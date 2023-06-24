#ifndef stablo_cpp
#define stablo_cpp
#include "stablo.h"
#include <iostream>
using namespace std;

template <typename Tip>
Stablo<Tip>::Stablo() {
  korijen = nullptr;
  broj_elemenata = 0;
}
template <typename Tip>
Stablo<Tip> :: Stablo (const Stablo &kopija){
   korijen=kopija.korijen;
   broj_elemenata=kopija.broj_elemenata;
}
template<typename Tip>
Stablo<Tip> :: Stablo(Stablo && kopija){
  korijen=kopija.korijen;
  broj_elemenata=kopija.broj_elemenata;
  kopija.korijen=nullptr;
  kopija.broj_elemenata=0;
}
template<typename Tip>
Stablo<Tip>& Stablo<Tip> :: operator = (const Stablo& rhs){
   Cvor *trenutni=NadjiNajmanji(korijen) ;
   while(broj_elemenata > 1 ){
        Obrisi(trenutni->element);
        trenutni=NadjiSljedbenika(trenutni);
    }
    Obrisi(trenutni->element);
    trenutni=NadjiNajmanji(rhs.korijen);
    cout<<trenutni->element;
    while(trenutni!= nullptr){
         Umetni(trenutni->element,trenutni->prioritet);
         trenutni=NadjiSljedbenika(trenutni);
    }
    return *this;
}
template<typename Tip>
Stablo<Tip>& Stablo<Tip> :: operator = (Stablo &&rhs){
   Cvor *trenutni=NadjiNajmanji(korijen) ;
   while(broj_elemenata >1 ){
        Obrisi(trenutni->element);
        trenutni=NadjiSljedbenika(trenutni);
    }
    Obrisi(trenutni->element);
    korijen=nullptr;
    korijen=rhs.korijen;
    broj_elemenata=rhs.broj_elemenata;
    rhs.broj_elemenata=0;
    rhs.korijen=nullptr;
}
template<typename Tip>
Stablo<Tip> :: ~Stablo(){
   Cvor *trenutni=NadjiNajmanji(korijen) ;
   while(trenutni->rod!=nullptr){
        Obrisi(trenutni->element);
        trenutni=NadjiSljedbenika(trenutni);
    }
    korijen=nullptr;
    delete korijen;
}
template <typename Tip>
pair<typename Stablo<Tip>::Cvor*,bool> Stablo<Tip>::Umetni(Tip element, int x) {
  if(korijen == nullptr) {
    korijen = new Cvor(element,x,nullptr);
    broj_elemenata = 1;
    return {korijen, true};
  }
  Cvor *trenutni1 = korijen, *prethodni = nullptr;
  while(trenutni1 != nullptr) {
    if(element == trenutni1->element)
        return {trenutni1, false};
    prethodni = trenutni1;
    if(element < trenutni1->element)
        trenutni1 = trenutni1->ld;
    else trenutni1 = trenutni1->dd;
  }
  broj_elemenata++;
  Cvor *novi = new Cvor(element,x,prethodni);
  if(element < prethodni->element)
    prethodni->ld = novi;
  else prethodni->dd = novi;
 Cvor *trenutni = novi;
 if(trenutni->prioritet > trenutni->rod->prioritet)
   while(trenutni!=korijen && trenutni->prioritet > trenutni->rod->prioritet){
        if(trenutni == trenutni->rod->dd){
            if(trenutni->rod == korijen) {
                if(trenutni->ld == nullptr) {
                   trenutni->ld=trenutni->rod;
                   trenutni->rod->rod=trenutni;
                   trenutni->rod->dd=nullptr;
                   korijen=trenutni;
                   korijen->rod=nullptr;}
                else {
                  Cvor *kopija=new Cvor(trenutni->ld->element,trenutni->ld->prioritet,nullptr,trenutni->ld->ld,trenutni->ld->dd);
                  trenutni->ld=trenutni->rod;
                  trenutni->ld->rod=trenutni;
                  trenutni->ld->dd=kopija;
                  trenutni->ld->dd=kopija;
                  kopija->rod=trenutni->ld;
                  korijen=trenutni;
                  korijen->rod=nullptr;
                  }
                }
            else{
              if(trenutni->ld == nullptr){
                    trenutni->ld=trenutni->rod;
                    trenutni->rod=trenutni->ld->rod;
                    if(trenutni->ld == trenutni->rod->ld)
                         trenutni->rod->ld=trenutni;
                    else trenutni->rod->dd=trenutni ;
                    trenutni->ld->rod=trenutni ;
                    trenutni->ld->dd=nullptr;}
              else{
                  Cvor *kopija=new Cvor(trenutni->ld->element,trenutni->ld->prioritet,trenutni->rod,trenutni->ld->ld,trenutni->ld->dd);
                  trenutni->ld=trenutni->rod;
                  trenutni->rod=trenutni->ld->rod;
                  if(trenutni->ld == trenutni->rod->ld)
                         trenutni->rod->ld=trenutni;
                    else {trenutni->rod->dd=trenutni ;}
                  trenutni->ld->rod=trenutni;
                  trenutni->ld->dd=kopija;
            }}}
        else{
              if(trenutni->rod == korijen) {
                if(trenutni->dd == nullptr) {
                   trenutni->dd=trenutni->rod;
                   trenutni->rod->rod=trenutni;
                   trenutni->rod->ld=nullptr;
                   korijen=trenutni;
                   korijen->rod=nullptr;}
                else {
                  Cvor *kopija=new Cvor(trenutni->dd->element,trenutni->dd->prioritet,trenutni->rod,trenutni->dd->ld,trenutni->dd->dd);
                  trenutni->dd=trenutni->rod;
                  trenutni->dd->rod=trenutni;
                  trenutni->dd->ld=kopija;
                  korijen=trenutni;
                  korijen->rod=nullptr;}
                  }
            else{
              if(trenutni->dd == nullptr) {
                   trenutni->dd=trenutni->rod;
                   trenutni->rod=trenutni->dd->rod;
                   if(trenutni->dd == trenutni->rod->dd)
                       trenutni->rod->dd=trenutni;
                   else trenutni->rod->ld=trenutni;
                   trenutni->dd->rod=trenutni;
                   trenutni->dd->ld=nullptr;
                 }
               else {
                  Cvor *kopija=new Cvor(trenutni->dd->element,trenutni->dd->prioritet,trenutni->rod,trenutni->dd->ld,trenutni->dd->dd);
                  trenutni->dd=trenutni->rod;
                  trenutni->rod=trenutni->dd->rod;
                  if(trenutni->dd == trenutni->rod->dd)
                     trenutni->rod->dd=trenutni;
                  else {trenutni->rod->ld=trenutni;}
                  trenutni->dd->rod=trenutni;
                  trenutni->dd->ld=kopija;
                }
            }}
}
   return {novi,true} ;
}
template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiElement(Tip element) {
  Cvor* trenutni = korijen;
  while(trenutni != nullptr) {
    if(element == trenutni->element)
      return trenutni;
    if(element < trenutni->element)
      trenutni = trenutni->ld;
    else trenutni = trenutni->dd;
  }
  return nullptr;
}
template<typename Tip>
void Stablo<Tip> :: Obrisi(Tip element){
    Cvor *za_brisanje=NadjiElement(element);

    if(za_brisanje == nullptr)
       return ;
    if(za_brisanje->dd == nullptr) {
      if(za_brisanje->ld == nullptr) {
        if(za_brisanje->rod != nullptr) {
            if(za_brisanje->rod->dd == za_brisanje)
                za_brisanje->rod->dd = nullptr;
            else  za_brisanje->rod->ld = nullptr;
        }
        else { korijen=nullptr;}
      }
      else{
         if(za_brisanje != korijen){
            za_brisanje->ld->rod = za_brisanje->rod;
            if(za_brisanje->rod->dd == za_brisanje)
                za_brisanje->rod->dd = za_brisanje->ld;
            else za_brisanje->rod->ld = za_brisanje->ld;
            }
         else {
             korijen=za_brisanje->ld;
             za_brisanje->ld->rod=nullptr;
          }
        }}
    else{
        if(za_brisanje->ld == nullptr)
            if(za_brisanje->rod!=nullptr){
               if(za_brisanje->rod->ld == za_brisanje)
                  za_brisanje->rod->ld=za_brisanje->dd;
                else za_brisanje->rod->dd=za_brisanje->dd;;
                za_brisanje->dd->rod=za_brisanje->rod;
                }
             else { korijen=za_brisanje->dd;
                    za_brisanje->dd->rod=nullptr;}
        else{
            Cvor *sljedbenik = NadjiSljedbenika(za_brisanje) ;
            if(sljedbenik->rod != za_brisanje)
               if(za_brisanje->rod != nullptr){
                  if(za_brisanje->rod->ld == za_brisanje)
                     za_brisanje->rod->ld=sljedbenik;
                  else za_brisanje->rod->dd=sljedbenik;
                  sljedbenik->rod=za_brisanje->rod;
                  sljedbenik->dd=za_brisanje->dd;
                  sljedbenik->ld=za_brisanje->ld;
                }
               else {
                 sljedbenik->dd=za_brisanje->dd;
                 sljedbenik->ld=za_brisanje->ld;
                 korijen=sljedbenik;
                 }
            else{
              if(za_brisanje != korijen){
                 if(za_brisanje->rod->ld == za_brisanje)
                    za_brisanje->rod->ld=sljedbenik;
                 else za_brisanje->rod->dd=sljedbenik;
                 sljedbenik->rod=za_brisanje->rod;
                 sljedbenik->ld=za_brisanje->ld;
                 sljedbenik->ld->rod=sljedbenik;}
              else{
                  korijen=sljedbenik;
                  if(za_brisanje ->ld != nullptr)
                     za_brisanje->ld->rod=sljedbenik;
                  sljedbenik->ld=za_brisanje->ld;
                  za_brisanje->ld->rod=korijen;
              }
              Cvor *trenutni = sljedbenik ;
              while(trenutni->dd!=nullptr || trenutni->ld!=nullptr){
                   if(trenutni->dd != nullptr && trenutni->ld != nullptr)
                      if(trenutni->dd->prioritet > trenutni->ld->prioritet){
                         if(trenutni->rod != nullptr)
                            if(trenutni->dd->ld == nullptr){
                               trenutni->dd->ld=trenutni;
                               trenutni->dd->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->dd;
                               else trenutni->rod->ld=trenutni->dd;
                               trenutni->rod=trenutni->dd;}
                             else{
                               Cvor *kopija=new Cvor(trenutni->dd->ld->element,trenutni->dd->ld->prioritet,trenutni,trenutni->dd->ld->ld,trenutni->dd->ld->dd);
                               trenutni->dd->ld=trenutni;
                               trenutni->dd->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->dd;
                               else trenutni->rod->ld=trenutni->dd;
                               trenutni->rod=trenutni->dd;
                               trenutni->dd=kopija;
                               }
                         else{
                             if(trenutni->dd->ld == nullptr){
                                trenutni->dd->ld=trenutni;
                                trenutni->dd->rod=trenutni->rod;
                                if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->dd;
                                else trenutni->rod->ld=trenutni->dd;
                                trenutni->rod=trenutni->dd;
                                korijen=trenutni->dd;
                                korijen->rod=nullptr;
                                }
                             else{
                               Cvor *kopija=new Cvor(trenutni->dd->ld->element,trenutni->dd->ld->prioritet,trenutni,trenutni->dd->ld->ld,trenutni->dd->ld->dd);
                               trenutni->dd->ld=trenutni;
                               trenutni->dd->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->dd;
                               else trenutni->rod->ld=trenutni->dd;
                               trenutni->rod=trenutni->dd;
                               trenutni->dd=kopija;
                               korijen=trenutni->dd;
                               korijen->rod=nullptr;
                               }
                             }}
                    else{
                       if(trenutni->rod != nullptr)
                            if(trenutni->ld->dd == nullptr){
                               trenutni->ld->dd=trenutni;
                               trenutni->ld->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->ld;
                               else trenutni->rod->ld=trenutni->ld;
                               trenutni->rod=trenutni->ld;}
                             else{
                               Cvor *kopija=new Cvor(trenutni->ld->dd->element,trenutni->ld->dd->prioritet,trenutni,trenutni->ld->dd->ld,trenutni->ld->dd->dd);
                               trenutni->ld->dd=trenutni;
                               trenutni->ld->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->ld;
                               else trenutni->rod->ld=trenutni->ld;
                               trenutni->rod=trenutni->ld;
                               trenutni->ld=kopija;
                               }
                       else{
                             if(trenutni->ld->dd == nullptr){
                                trenutni->ld->dd=trenutni;
                                trenutni->ld->rod=trenutni->rod;
                                if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->ld;
                                else trenutni->rod->ld=trenutni->ld;
                                trenutni->rod=trenutni->ld;
                                korijen=trenutni->ld;
                                korijen->rod=nullptr;
                                }
                             else{
                               Cvor *kopija=new Cvor(trenutni->ld->dd->element,trenutni->ld->dd->prioritet,trenutni,trenutni->ld->dd->ld,trenutni->ld->dd->dd);
                               trenutni->ld->dd=trenutni;
                               trenutni->ld->rod=trenutni->rod;
                               if(trenutni == trenutni->rod->dd)
                                  trenutni->rod->dd=trenutni->ld;
                               else trenutni->rod->ld=trenutni->ld;
                               trenutni->rod=trenutni->ld;
                               trenutni->ld=kopija;
                               korijen=trenutni->ld;
                               korijen->rod=nullptr;
                               }}}
                    else if(trenutni->dd == nullptr && trenutni->ld != nullptr && trenutni->prioritet < trenutni->ld->prioritet){
                        if(trenutni->ld->dd == nullptr)
                          if(trenutni != korijen){
                            trenutni->ld->dd=trenutni;
                            if(trenutni->rod->dd == trenutni)
                              trenutni->rod->dd=trenutni->ld;
                            else trenutni->rod->ld=trenutni->ld;
                            trenutni->ld->rod=trenutni->rod;
                            trenutni->rod=trenutni->ld;
                            trenutni->ld=nullptr;}
                          else{
                            trenutni->ld->dd=trenutni;
                            trenutni->rod=trenutni->ld;
                            korijen=trenutni->ld;
                            korijen->rod=nullptr;
                        }
                        else{
                          Cvor *kopija=new Cvor(trenutni->ld->dd->element,trenutni->ld->dd->prioritet,trenutni,trenutni->ld->dd->ld,trenutni->ld->dd->dd);
                          if(trenutni != korijen){
                            trenutni->ld->dd=trenutni;
                            if(trenutni->rod->dd == trenutni)
                              trenutni->rod->dd=trenutni->ld;
                            else trenutni->rod->ld=trenutni->ld;
                            trenutni->ld->rod=trenutni->rod;
                            trenutni->rod=trenutni->ld;
                            trenutni->ld=nullptr;
                            trenutni->ld=kopija;
                            }
                          else{
                            trenutni->ld->dd=trenutni;
                            trenutni->rod=trenutni->ld;
                            trenutni->ld=kopija;
                            korijen=trenutni->ld;
                            korijen->rod=nullptr;
                        }}}
                    else if(trenutni->ld == nullptr && trenutni->dd != nullptr && trenutni->prioritet < trenutni->dd->prioritet)
                      if(trenutni->dd->ld == nullptr)
                         if(trenutni != korijen){
                           trenutni->dd->ld=trenutni;
                           if(trenutni->rod->ld == trenutni)
                             trenutni->rod->ld=trenutni->dd;
                           else trenutni->rod->dd=trenutni->dd;
                           trenutni->dd->rod=trenutni->rod;
                           trenutni->rod=trenutni->dd;
                           trenutni->dd=nullptr;}
                         else{
                           trenutni->dd->ld=trenutni;
                           trenutni->rod=trenutni->dd;
                           korijen=trenutni->dd;
                           korijen->rod=nullptr;
                        }
                       else{
                         Cvor *kopija=new Cvor(trenutni->dd->ld->element,trenutni->dd->ld->prioritet,trenutni,trenutni->dd->ld->ld,trenutni->dd->ld->dd);
                         if(trenutni != korijen){
                           trenutni->dd->ld=trenutni;
                           if(trenutni->rod->ld == trenutni)
                             trenutni->rod->ld=trenutni->dd;
                           else trenutni->rod->dd=trenutni->dd;
                           trenutni->dd->rod=trenutni->rod;
                           trenutni->rod=trenutni->dd;
                           trenutni->dd=nullptr;
                           trenutni->dd=kopija;
                           }
                         else{
                           trenutni->dd->ld=trenutni;
                           trenutni->rod=trenutni->dd;
                           korijen=trenutni->dd;
                           korijen->rod=nullptr;
                           trenutni->dd=kopija;
                        }}
                    else break;
            }}
}}
          delete za_brisanje;
          broj_elemenata--;
}
template <typename Tip>
void Stablo<Tip>::Ispisi() {
  Cvor* trenutni = NadjiNajmanji(korijen);
  while(trenutni != nullptr) {
    if(trenutni != korijen)
       cout<<trenutni->element<<" " << trenutni->prioritet <<" ima roditelja "  << trenutni->rod->element << endl ;
    else { cout <<"Korijen je " << trenutni->element <<" " << trenutni->prioritet << endl; }
    trenutni = NadjiSljedbenika(trenutni);
  }
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiNajmanji(Stablo<Tip>::Cvor *cvor) {
  if(cvor == nullptr)
    return nullptr;
  Cvor *trenutni = cvor;
  while(trenutni->ld != nullptr)
    trenutni = trenutni->ld;
  return trenutni;
}

template <typename Tip>
typename Stablo<Tip>::Cvor* Stablo<Tip>::NadjiSljedbenika(Stablo<Tip>::Cvor *cvor) {
  if(cvor->dd != nullptr)
    return NadjiNajmanji(cvor->dd);
  Cvor *trenutni = cvor;
  while(trenutni != korijen && trenutni == trenutni->rod->dd)
    trenutni = trenutni->rod;
  if(trenutni == korijen)
     return nullptr;
  else return trenutni->rod;
}

#endif
