#ifndef stablo_h
#define stablo_h
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
using namespace std ;

template<typename Tip>
class Stablo {
  public:
  struct Cvor {
      Tip element;
      Cvor *ld, *dd, *rod;
      int prioritet;
      Cvor(Tip el,int p, Cvor* rod = nullptr, Cvor* ld = nullptr, Cvor* dd = nullptr) :
          element(el), prioritet(p), rod(rod), ld(ld), dd(dd) {}
  };
  private:
  int broj_elemenata;
  Cvor* korijen;
  Cvor* NadjiNajmanji(Cvor*);
  Cvor* NadjiSljedbenika(Cvor* cvor);
  public:
  Stablo();
  Stablo(const Stablo &kopija) ;
  Stablo(Stablo &&kopija) ;
  Stablo& operator = (const Stablo& rhs);
  Stablo& operator = (Stablo&& rhs);
  ~Stablo() ;
  pair<Cvor*,bool> Umetni(Tip element,int x);
  void Ispisi();
  void Obrisi(Tip element) ;
  Cvor* NadjiElement(Tip element) ;

};
#include "stablo.cpp"
#endif
