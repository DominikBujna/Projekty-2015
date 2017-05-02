//
//  main.cpp
//  Pokrocila Uloha 2
//
//  Created by Dominik Bujna on 19/10/15.
//  Copyright © 2015 Dominik Bujna. All rights reserved.
//
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

/*
 skusobne vstupy mam ako globalne premenne, ked ich bude zvladat, staci aby ostala 1 premenna
 */
vector < vector <char> > vstup1;

vector < vector <char> > vstup2;

vector < vector <char> > vstup3;

vector < vector <char> > vstupUser;

void vypis(vector < vector<char> > pole, int dlzka) {
    for (int i = 0; i < dlzka; i++) {
        for (int n = 0; n < dlzka; n++) {
            cout << pole[i][n];
            if(n < dlzka - 1){
                cout<<" ";
            }
        }
        cout << endl;
    }
    cout << endl;
}


//nahodim si vzorove vstupy do vectorov + jeden minimalisticky

void vstupy() {
    string input1 = "....3....2....2..B.332232";
    
    for (int i = 0; i < 5; i++) {
        vector<char> riadok;
        for (int n = 0; n < 5; n++) {
            riadok.push_back(input1.at(i * 5 + n));
        }
        vstup1.push_back(riadok);
    }
    
    
    string input2 = "B.B.BC..3CCBBCBBC4CCC..CBB5..CCC..C5BB.CBCB.3B.CBCBCC5CC..C.C.6CCBBBCCC5455355456";
    for (int i = 0; i < 9; i++) {
        vector<char> riadok;
        for (int n = 0; n < 9; n++) {
            riadok.push_back(input2.at(i * 9 + n));
        }
        vstup2.push_back(riadok);
    }
    string input3 = "..1..1111";
    
    for (int i = 0; i < 3; i++) {
        vector<char> riadok;
        for (int n = 0; n < 3; n++) {
            riadok.push_back(input3.at(i * 3 + n));
        }
        vstup3.push_back(riadok);
    }
}

void citajVstup(){
    int size;
    int max;
    cin>>size>>max;
    size+=1;
    //realna velkost vstupu je o 1 vacsia, preto potrebujeme vacsie pole
    for (int i = 0; i < size; i++){
        vector< char > riadok;
        for(int n = 0; n < size; n++){
            if(i == (size - 1) && n == (size - 1)){
                riadok.push_back(max);
            }else{
                char vstup;
                cin>>vstup;
                riadok.push_back(vstup);
            }
            vstupUser.push_back(riadok);
        }
    }
}

/* vlozim pole, poziciu prave zvazovaneho prvku, velkost pola (v podstate zbytocne), pocet ciernych v riadku, pocet ciernych za sebou
 
 ked vyriesim, preco mi to nevytvara ten spravny vystup, tak pridam premennu na pocet bielych za sebou, kedze aj to je potrebne
 
 */
void vyries(vector < vector<char> > pole, int stlpec, int riadok, int size, int pocetR, int comboR) {
    
    //int dlzka je quickfixom pre out of bounds vectora, co sa mi stavalo povodne
    
    int dlzka = size - 1;
    //spocitam cierne v stlpci
    
    int pocetS = 0;
    int comboS = 0;
    for (int i = 0; i < riadok; i++) {
        if (pole.at(i).at(stlpec) == 'C') {
            pocetS++;
            comboS++;
        }
        if (pole.at(i).at(stlpec) == 'B') {
            comboS = 0;
        }
    }
    
    //skontrolujem, ci v stlpci nie je viac ciernych ako by malo byt, musim odpocitat 48 ako prevod z cifry v char na int
    if (pocetS <= (pole.at(dlzka).at(stlpec) - 48)) {
       
        //ak je koniec riadku, skontrolujem pocet ciernych a zavolam ho na novy riadok, do prveho stlpca
        if (stlpec == dlzka) {
            //ak pocet ciernych sedi
            if (pocetR == (pole[riadok][dlzka] - 48)) {
                
                // vypis(pole, size);
                //ak bol zavolany do posledneho riadku, je hotovo
                if (riadok == dlzka-1) {
                    //kontrola stlpcov
                    // cout << endl<<endl<<"kontrolujem kandidata" << endl;
                    vypis(pole, size);
                    bool ok = true;
                    pocetS = 0;
                    comboS = 0;
                    int comboB = 0;
                    //pre kazdy stlpec
                    for (int i = 0; i < dlzka; i++) {
                        //pre kazdy riadok
                        for (int n = 0; n < dlzka; n++) {
                            //ak je pocet ciernych za sebou a pocet bielych za sebou mensi ako maxialny
                            if (comboS <= (pole[dlzka][dlzka] - 48) && comboB <= (pole[dlzka][dlzka] - 48)) {
                                   cout << "comba su v pohode" << endl;
                                if (pole[n][i] == 'B') {
                                    comboB++;
                                    comboS = 0;
                                          cout << "ma tam B, combo ma: " << comboB << endl;
                                } else if (pole[n][i] == 'C') {
                                    comboS++;
                                    pocetS++;
                                    comboB = 0;
                                      cout << "ma tam C, combo ma: " << comboS << endl;
                                        cout << "ma tam C, v stlpci "<<n<< " ich uz ma: " << pocetS << endl;
                                }
                                //inak mozeme ist rovno prec, pretoze to nevyhovuje
                            }
                            else{
                                cout<<endl<<"MOC VELA NIECOHO" << endl <<endl;
                            }
                            if (comboS > (pole[dlzka][dlzka] - 48) && comboB > (pole[dlzka][dlzka] - 48)) {
                                cout << "privela combo " << comboB << " > " <<  (pole[dlzka][dlzka] - 48) << " < "<< comboS <<endl;
                                cout << "v stlpci " << n << endl;
                                i += 200000;
                                ok = false;
                            }
                        }
                        //ak je pocet zhodny a nie je vela rovnakych za sebou, tak nic
                        if (pocetS == (pole.at(dlzka).at(stlpec) - 48)) {
                                cout << "vsetko je OK" << endl;
                        }//inak mozeme ist prec, lebo to nevyhovuje
                        else {
                            //       cout << "Nema ich tak akurat v stlpci " << i <<" smola" << endl;
                            i += 1000000;
                            ok = false;
                        }
                        
                    }
                    //ak je vsetko OK, vypis
                    if (ok) {
                        cout << "hotovo" << endl << endl;
                        vypis(pole, size);
                    }
                    
                } else {
                    //inak ide na dalsi riadok
                    vyries(pole, 0, (riadok + 1), size, 0, 0);
                }
            }
        } else {
            
            
            //ak je tam C, ide dalej, zvysi pocet v riadku a pocet za sebou
            if (pole[riadok][stlpec] == 'C') {
                
                vyries(pole, stlpec + 1, riadok, size, pocetR + 1, comboR + 1);
            }//ak je tam B, ide dalej, vynuluje pocet C za sebou
            else if (pole[riadok][stlpec] == 'B') {
                
                vyries(pole, stlpec + 1, riadok, size, pocetR, 0);
            }
            // ak je to prazdne,
            if (pole[riadok][stlpec] == '.') {
                //len ak je pocet mensi ma vyznam skusat C
                if (pocetR < (pole[riadok].at(dlzka) - 48) && pocetS < (pole.at(dlzka).at(stlpec) - 48)) {
                    pole[riadok][stlpec] = 'C';
                    vyries(pole, stlpec + 1, riadok, size, pocetR + 1, comboR + 1);
                    
                }
                //okrem toho skusime kombinaciu s B
                pole[riadok][stlpec] = 'B';
                vyries(pole, stlpec + 1, riadok, size, pocetR, 0);
                
            }
            
        }
    }
}
//funkcia, ktorou sa to spusta, aby nebolo treba tolko parametrov do nej davat

void vyries(vector < vector<char> > pole, int dlzka) {
    vyries(pole, 0, 0, dlzka, 0, 0);
    
}

int main(int argc, char** argv) {
    //citajVstup();
    //nahodi vstupy zo stringov do vektorov vektorov charov
    vstupy();
    //vyries(vstup1, 5);
    //vypis(vstup3, 3);
    
vyries(vstup2, 9);
   //vyries(vstupUser, vstupUser[0].size());
    return 0;
}

