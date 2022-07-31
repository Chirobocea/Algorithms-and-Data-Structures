#include <iostream>
using namespace std;

struct nod_arbore{
    int info;
    nod_arbore* fiu_stang;
    nod_arbore* fiu_drept;
};

struct arbore{
    nod_arbore* radacina;
    arbore(){
        radacina=NULL;
    }

    void insert_element(int x){
        nod_arbore* nou = new nod_arbore;
        nou->info = x;
        nou->fiu_stang=NULL;
        nou->fiu_drept=NULL;

        if (radacina==NULL){
            radacina=nou;
            return;
        }

        nod_arbore* pointer_prev = NULL;
        nod_arbore* pointer = radacina;
        int directie = 0;

        while(pointer!=NULL){
            pointer_prev=pointer;
            if (x<=pointer->info){
                pointer=pointer->fiu_stang;
                directie = -1;
            }else{
                pointer=pointer->fiu_drept;
                directie = 1;
            }
        }

        if (directie <0)
            pointer_prev->fiu_stang=nou;
        else
            pointer_prev->fiu_drept=nou;
    }

    bool find(int x){
        nod_arbore* current_node = radacina;
        while (true) {
            if (x == current_node->info)
                return true;
            if (x <= current_node->info) {
                if (current_node->fiu_stang == nullptr)
                    return false;
                current_node = current_node->fiu_stang;
            } else {
                if (current_node->fiu_drept == nullptr)
                    return false;
                current_node = current_node->fiu_drept;
            }
        }
    }

    void parcurg(nod_arbore* current_node, arbore B){
        int value = current_node->info;
        if(B.find(value)==0){
            cout<<"Value: "<<value<<endl;
            this->insert_element(value);
        }
        if(current_node->fiu_stang != nullptr)
            this->parcurg(current_node->fiu_stang, B);
        if(current_node->fiu_drept != nullptr)
            this->parcurg(current_node->fiu_drept, B);
    }

    arbore difference(arbore B){
        arbore C;
        C.parcurg(this->radacina, B);
        return C;
    }

    void RSD(){RSD(radacina,0,0);}
    void RSD(nod_arbore *radacina, int nivel, int dir){
        if (radacina!=NULL){
            for (int i=0;i<nivel;i++) cout<<" ";
            cout<<radacina->info<<(dir==-1?"st":"")<<(dir==1?"dr":"")<<endl;
            RSD(radacina->fiu_stang,nivel+1,-1);
            RSD(radacina->fiu_drept,nivel+1,1);
        }
    }

};

int main()
{
    arbore a, b;
    a.insert_element(6);
    a.insert_element(4);
    a.insert_element(9);
    a.insert_element(2);
    a.insert_element(1);
    a.insert_element(5);
    a.insert_element(3);
    a.insert_element(7);
    a.insert_element(8);

    b.insert_element(7);
    b.insert_element(4);
    b.insert_element(8);
    b.insert_element(2);
    b.insert_element(3);

    a.RSD();
    cout<<endl;
    b.RSD();
    cout<<endl;
    arbore c=a.difference(b);
    cout<<endl;
    c.RSD();
    cout<<endl;

    return 0;
}