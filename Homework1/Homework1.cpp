#include <iostream>

using namespace std;

struct nod{
    int coeficient, exponent;
    nod* next;
};

struct Polinom{
    nod* primul_element;    //pointer la primul element
    nod* ultimul_element;   //pointer la ultimul element

    Polinom(){
        primul_element=nullptr;
        ultimul_element=nullptr;
    }

    int insert_at_begining(){
        nod* nou = new nod; //alocam spatiu
        cout<<"Introduceti coeficientul: ";
        cin>>nou->coeficient;
        cout<<"Introduceti exponentul: ";
        cin>>nou->exponent;
        nou->next = primul_element; // punem adresa din primul_element in campul adresa next
        // legam nou de primul_element
        primul_element = nou; // actualizam care este adresa noului nod de la inceput
        if (ultimul_element==nullptr) // daca lista era goala -> acum extista 1 nod
            ultimul_element=nou; //ultimul_element trebuie sa-l indice pe acel nod
        if(nou->exponent==0)
            return 0;
        return 1;
    }

    void insert_la_final(int coeficient, int exponent){
        nod* nou = new nod; //alocam spatiu
        nou->coeficient=coeficient;
        nou->exponent=exponent;
        nou->next = nullptr; //punem NULL in adresa pentru ca acest nod va fi ultimul
        if (ultimul_element==nullptr) //daca lista era vida
            primul_element=ultimul_element=nou; //atunci ambii pointeri indica noul nod
        else{
            ultimul_element->next=nou; //legam ultimul de nou
            ultimul_element=nou; //ultimul nod trebuie actualizat, stocam adresa lui in ultimul_element
        }
    }

    void create(){
        while(true){
            if(insert_at_begining() == 0)
                break;
        }
    }

    Polinom operator+(Polinom p) const{
        Polinom aux;
        nod *p1, *p2;
        p1=this->primul_element;
        p2=p.primul_element;
        while(p1!=nullptr && p2!=nullptr){
            if(p1->exponent == p2->exponent){
                aux.insert_la_final(p1->coeficient + p2->coeficient, p1->exponent);
                p1=p1->next;
                p2=p2->next;
            }
            else if(p1->exponent > p2->exponent){
                aux.insert_la_final(p1->coeficient, p1->exponent);
                p1=p1->next;
            }
            else{
                aux.insert_la_final(p2->coeficient, p2->exponent);
                p2=p2->next;
            }
        }
        while(p1!= nullptr){
            aux.insert_la_final(p1->coeficient, p1->exponent);
            p1=p1->next;
        }
        while(p2!= nullptr){
            aux.insert_la_final(p2->coeficient, p2->exponent);
            p2=p2->next;
        }
        return aux;
    }

    void afisare() const {
        nod *pointer;
        for (pointer = primul_element; pointer != nullptr; pointer = pointer->next)
            cout << "(" << pointer->exponent << "," << pointer->coeficient << ")" << " -> ";
        cout << endl;
    }

};

int main(){
    Polinom p1, p2, p;
    p1.insert_la_final(8,5);
    p1.insert_la_final(5,3);
    p1.insert_la_final(3,2);
    p1.insert_la_final(7,0);
    p2.insert_la_final(6,4);
    p2.insert_la_final(4,2);
    p2.insert_la_final(1,1);
    p=p1+p2;
    p1.afisare();
    p2.afisare();
    p.afisare();
    return 0;
}