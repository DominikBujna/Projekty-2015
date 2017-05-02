//
//  main.cpp
//  DomacaUloha9
//
//  Created by Dominik Bujna on 06/01/16.
//  Copyright © 2016 Dominik Bujna. All rights reserved.
//

#include <iostream>
using namespace std;


int main(int argc, const char * argv[]) {
    int s,p,n,k;
    int* poradie;
    int kolky = 0;
    cin>>s>>p>>n>>k;
    //vytvori sa hracia plocha
    int pole[n][n];
    for(int i = 0; i < n; i++){
        for(int  j = 0; j < n; j++){
            pole[i][j] = -1;
            
        }
    }
    //nacitaju sa suradnice stanovist, prve je start - prva pozicia pre kazdeho pretekara
    int x, y;
    cin>>x>>y;
    pole[x][y] = 0;
    //zapisane aktualne policko, kde sa pretekar nachadza, 0 je sucasne pole, 1 stanovisko
    int pretekari[p][2];
    
    for(int i = 0; i < p; i++){
        pretekari[i][0] = ((x*n) + y);
        pretekari[i][1] = 0;
    }
    
    for(int i = 1; i < s; i++){
        cin>>x>>y;
        pole[x][y] = i;
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout<<pole[i][j]<<" ";
        }
        cout<<endl;
    }
    //pre kazdy tah
    for(int i = 0; i < k; i++){
         //pre kazdeho hraca
        for(int j = 0; j < p; j++){
            int x, y;
            cin>>x>>y;
            //pre kazdy pohyb na x
            if(x>0){
                for(int t = 0; t < x; t++){
                    pretekari[j][0] += n;
                    //ak je policku, na ktorom je pretekar stanovisko o 1 vacsie ako jeho posledne, zvysi sa stanovisko
                    if(pole[pretekari[j][0] / n][pretekari[j][0]%n] == pretekari[j][1] + 1){
                        pretekari[j][1] = pretekari[j][1] + 1;
                }
                    if( pretekari[j][1] == s-1){
                        pretekari[j][1] = -10;
                        poradie[kolky] = j;
                        kolky++;
                }
            }
            }else if(x<0){
                for(int t = 0; t > x; t--){
                    pretekari[j][0] -= n;
                    //ak je policku, na ktorom je pretekar stanovisko o 1 vacsie ako jeho posledne, zvysi sa stanovisko
                    if(pole[pretekari[j][0] / n][pretekari[j][0]%n] == pretekari[j][1] + 1){
                        pretekari[j][1] = pretekari[j][1] + 1;
                    }
                    if( pretekari[j][1] == s-1){
                        pretekari[j][1] = -10;
                        poradie[kolky] = j;
                        kolky++;
                    }
            }
                
                
                
                if(y>0){
                    for(int t = 0; t < y; t++){
                        pretekari[j][0]++;
                        //ak je policku, na ktorom je pretekar stanovisko o 1 vacsie ako jeho posledne, zvysi sa stanovisko
                        if(pole[pretekari[j][0] / n][pretekari[j][0]%n] == pretekari[j][1] + 1){
                            pretekari[j][1] = pretekari[j][1] + 1;
                        }
                        if( pretekari[j][1] == s-1){
                            pretekari[j][1] = -10;
                            poradie[kolky] = j;
                            kolky++;
                        }
                    }
                }else if(y<0){
                    for(int t = 0; t > y; t--){
                        pretekari[j][0]--;
                        //ak je policku, na ktorom je pretekar stanovisko o 1 vacsie ako jeho posledne, zvysi sa stanovisko
                        if(pole[pretekari[j][0] / n][pretekari[j][0]%n] == pretekari[j][1] + 1){
                            pretekari[j][1] = pretekari[j][1] + 1;
                        }
                        if( pretekari[j][1] == s-1){
                            pretekari[j][1] = -10;
                            poradie[kolky] = j;
                            kolky++;
                        }
                    }
                
                }
            }
            
                
                
          
        }
        cout<<"Aktualne stanovistia po "<<i + 1<<". kole:";
        for(int t = 0; t < p; t++){
            cout<<" "<<pretekari[t][1];
        }
        cout<<endl;
    }
    for(int i = 0; i < kolky; i++){
        cout<<i + 1<<". skoncil pretekar "<<poradie[i]<<endl;
    }
    if(kolky < p){
        cout<<"Neuspesni:";
        for(int i = 0; i < p-kolky; i++){
            if(pretekari[i][1] != -10){
                cout<<" "<<i;
            }
        }
    }
    
    
    
    
    return 0;
}
