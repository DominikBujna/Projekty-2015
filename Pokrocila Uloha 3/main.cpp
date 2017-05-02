//
//  main.cpp
//  Pokrocila Uloha 3
//
//  Created by Dominik Bujna on 13/11/15.
//  Copyright © 2015 Dominik Bujna. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

/* TUTO CAST PROGRAMU NEMENTE */

/* struktura pre jeden uzol zoznamu */
struct node {
    double data;  // data ulozene vo vrchole
    node* next;   // smernik na dalsi uzol
};

/* Pomocna funkcia pre funkciu readInput,
 * ktora dostane cislo nasledujuceho uzlu a najde
 * smernik na tento uzol v poli a. Ak je id -1, vrati NULL. */
node *selectPointer(int id, node **a, int n) {
    if (id >= 0) {
        assert(id < n);
        return a[id];
    } else {
        assert(id == -1);
        return NULL;
    }
}

/* Funkcia, ktora nacita vstup a do premennych list1 a list2
 * ulozi smerniky na prve uzly dvoch zoznamov. */
void readInput(node *&list1, node *&list2) {
    int n;  // nacitaj pocet uzlov n
    cin >> n;
    assert(n >= 0);
    node **a = new node*[n]; // vytvor pole n uzlov
    for (int i = 0; i < n; i++) {
        a[i] = new node;
    }
    for (int i = 0; i < n; i++) { // nacitavaj uzly
        double data;
        int next;
        cin >> data >> next;
        a[i]->data = data;
        a[i]->next = selectPointer(next, a, n);
    }
    int n1, n2;  // nacitaj zaciatky zoznamov
    cin >> n1 >> n2;
    list1 = selectPointer(n1, a, n);
    list2 = selectPointer(n2, a, n);
    delete[] a;
}



/* VASE FUNKCIE TU */

//funkcia, ktora zisti, ci obsahuje cyklus a dlzku nezacykleneho zoznamu
int cyklus (node* list, bool cely){
    int h = 2;
    node* s1 = list;
    if(list == NULL){
        return 0;
    }
    node* s2 = list->next;
    if(s2 == NULL){
        return 1;
    }
    int n = 2;
    while(true){
      
            if(s2->next == NULL){
                return n;
            }
            if(s1 == s2){
                s1 = list;
                node* s2 = s1;
                if(s1->next == s1){
                    if(cely){
                        return 1;
                    }else{
                        return 0;
                    }
                }
                //idem pre kazde s1, maximalne tolko krat, ako predosla funkcia vyplula
                for(int m = 0; m < n; m++){
                    //pre kazde s2, kym nezacne ukazocat na s1, ktore
                    for(int j = 1; j <= n; j++){
                        if(s2->next == s1){
                            //ak ma ratat cely cyklus, vrati n+m, ak len uvodnu cestu, vrati m
                            if(cely){
                                return j + m;
                            }else{
                                return m;
                            }
                        }
                        s2 = s2->next;
                    }
                    s1 = s1->next;
                    s2 = s1;
                }

            }
            if(n == h){
                h = h*2;
                s1 = s2;
            }
            s2 = s2->next;
            n++;
    }
    return -666666;
}

int spolocne(node* list1, node* list2){
    int n = 0;
    node* s1 = list1;
    node* s2 = list2;
    int list1Length = cyklus(list1, true);
    int list2Length = cyklus(list2, true);


    //skontrolujem kazdy prvok, nakolko viem, kolko ich tam je
    for(int i = 0; i < list1Length; i++){
        for(int j = 0;j < list2Length; j++){
            //ak su si rovne, pripocitam n
            
            if(s1 == s2){
                n++;
            }
                s2 = s2->next;
            
            
        }
        s2 = list2;
        s1 = s1->next;
    }
    return (list1Length + list2Length - n);
}
int prvyspolocny1(node* list1, node* list2){
    node* s1 = list1;
    node* s2 = list2;
    int list1Length = cyklus(list1, true);
    int list2Length = cyklus(list2, true);
    
    
    //skontrolujem kazdy prvok, nakolko viem, kolko ich tam je
    for(int i = 0; i < list1Length; i++){
        for(int j = 0;j < list2Length; j++){
            //ak su si rovne, pripocitam n
            
            if(s1 == s2){
                return i;
            }
            s2 = s2->next;
            
            
        }
        s2 = list2;
        s1 = s1->next;
    }
    return -1;
}
int pocet(node* list1, node* list2, int spolocny){
    return prvyspolocny1(list1, list2) + cyklus(list2, true);
}

void odalokuj(node* list1, node* list2, int spolocny){
  
    
    int l1Size = cyklus(list1, true);
    int l2Size = cyklus(list2, true);
    node* s1 = list1;
    node* s2;
    if(s1!=NULL){
        s2 = s1->next;
    }
     //pojde len ak nie su disjunktne
    for(int i = 0; i < spolocny; i++){
        delete [] s1;
        s1 = s1->next;
        s2 = s1->next;
    }
    if(spolocny == -1){
        for(int i = 0; i < l1Size; i++){
            delete [] s1;
            s1 = s1->next;
            s2 = s1->next;
        }
    }
    s1 = list2;
    if(s1 != NULL){
        s2 = s1->next;
    }
    for(int i = 0; i < l2Size - 1; i++){
        delete [] s1;
        s1 = s1->next;
        s2 = s1->next;
    }
    
    
}

//vytvor list
int main(void) {
    /* TUTO CAST PROGRAMU NEMENTE */
    node *list1, *list2;
    readInput(list1, list2);
    
    /* VAS KOD TU */
    cout<<cyklus(list1, true)<<" ";
    cout<<cyklus(list1, false)<<endl;
    cout<<cyklus(list2, true)<<" ";
    cout<<cyklus(list2, false)<<endl;
    cout<<spolocne(list1, list2)<<endl;
    odalokuj(list1, list2, prvyspolocny1(list1, list2));
}
