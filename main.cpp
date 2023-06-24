#include <iostream>
#include <utility>
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "stablo.h" ;
using namespace std ;

int main(){

  Stablo<int> s;
  s.Umetni(5,((rand()%1000)+1));
  s.Umetni(6,((rand()%1000)+1));
  s.Umetni(3,((rand()%1000)+1));
  s.Umetni(12,((rand()%1000)+1));
  s.Umetni(11,((rand()%1000)+1));
  s.Umetni(26,((rand()%1000)+1));
  s.Umetni(36,((rand()%1000)+1));
  s.Umetni(21,((rand()%1000)+1));
  s.Umetni(75,((rand()%1000)+1));
  s.Umetni(60,((rand()%1000)+1));
  s.Umetni(77,((rand()%1000)+1));
  s.Umetni(30,((rand()%1000)+1));
  s.Ispisi();
  cout<<endl;
  s.Obrisi(60);
  s.Obrisi(36);
  s.Obrisi(77);
  s.Obrisi(21);
  s.Obrisi(75);
  s.Obrisi(6);
  s.Ispisi();
  cout<<endl;
  s.Umetni(25,((rand()%1000)+1));
  s.Umetni(60,((rand()%1000)+1));
  s.Ispisi();
  cout<<endl;
  Stablo<int>t ;
  t.Umetni(17,((rand()%1000)+1));
  t.Umetni(13,((rand()%1000)+1));
  t.Umetni(56,((rand()%1000)+1));
  t.Umetni(22,((rand()%1000)+1));
  t.Umetni(8,((rand()%1000)+1));
  t.Umetni(7,((rand()%1000)+1));
  t.Umetni(69,((rand()%1000)+1));
  t.Obrisi(69) ;
  t.Ispisi();
}
