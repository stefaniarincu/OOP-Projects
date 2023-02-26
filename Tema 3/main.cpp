#include <iostream>
#include <cstring>
#include <set>
#include <vector>
using namespace std;

class Masina;

template <class T> class Vanzare
{
    static int masini_vand;
    int nr_masini;
    set<pair<T*, bool>> vand;
    set<pair<T*, bool>> stoc;
public:
    Vanzare& operator-=(T&);
    Vanzare& operator+=(T&);

    float pret();

    void afis();
};
template<class T> int Vanzare<T>::masini_vand = 0;

class SingletonCr
{
    static SingletonCr* instanta;
    int nr_mas;
    int nr_mon;
    Vanzare<Masina> v;
    SingletonCr() {};
public:
    static SingletonCr* getInstanta() {
        if (!instanta)
        instanta = new SingletonCr;
        return instanta;
    }

    int getMC() {
        return this -> nr_mas;
    }

    void setMC(int nr_mas) {
        this -> nr_mas = nr_mas;
    }

    int getMonoC() {
        return this -> nr_mon;
    }

    void setMonoC(int nr_mon) {
        this -> nr_mon = nr_mon;
    }

    Vanzare<Masina>& getVanzare(){
        return v;
    }
};
SingletonCr *SingletonCr::instanta = 0;

class Masina
{
protected:
    int an;
    float pret;
    string nume;
public:
    Masina(int An = 0, float Pret = 0.0, string Nume = "") : an(An), pret(Pret), nume(Nume)
    {
        int aux = SingletonCr::getInstanta()->getMC();
        SingletonCr::getInstanta()->setMC(aux + 1);
    }
    virtual ~Masina() {}

    virtual float pret_masina(){return pret;}
    virtual void set_an(int x){an = x;}
    virtual void set_nume(string n){nume = n;}
    int get_an(){return an;}
    virtual void set_pret(float x){pret = x;}


    friend istream& operator>>(istream&, Masina&);
    virtual void citire(istream&);
    virtual void afis(ostream&);
};

istream& operator>>(istream& in, Masina& m)
{
    m.citire(in);
    return in;
}

void Masina::citire(istream& in)
{
    cout<<"Anul fabricatiei: ";
    in>>an;

    cout<<"Numele masinii: ";
    in>>nume;

    cout<<"Pretul masini: ";
    in>>pret;
}

void Masina::afis(ostream& out)
{
    out<<"Masina "<<nume<<" a fost fabricata in anul "<<an<<" si coasta "<<pret<<" lei.\n";
}

template<class T> Vanzare<T>& Vanzare<T>::operator-=(T& ob)
{
    int aux = SingletonCr::getInstanta()->getMC() - 1;
    nr_masini = aux;
    SingletonCr::getInstanta()->setMC(aux);

    masini_vand++;

    bool sh;
    int op;
    cout<<"Citeste 1 daca masina este second hand sau 0 altfel\n";
    cin>>op;
    if(op == 1)
        sh = true;
    else
        sh = false;

    vand.insert(make_pair(&ob, sh));
    return *this;
}

template<class T> Vanzare<T>& Vanzare<T>::operator+=(T& ob)
{
    int aux = SingletonCr::getInstanta()->getMC() + 1;
    nr_masini = aux;
    SingletonCr::getInstanta()->setMC(aux);

    bool sh;
    int op;
    cout<<"Citeste 1 daca masina este second hand sau 0 altfel\n";
    cin>>op;
    if(op == 1)
        sh = true;
    else
        sh = false;

    stoc.insert(make_pair(&ob, sh));
    return *this;
}

 template <class T> float Vanzare<T>::pret()
{
    for(auto& it : vand)
    {
        Masina* m = dynamic_cast<Masina*>(it.first);
        m->set_pret(m->pret_masina());
    }
}


template<class T> void Vanzare<T>::afis()
{
     for(auto& it : vand)
        it.first->afis(cout);
}

class Mini: public Masina
{
    float dimens;
public:
    Mini(int An = 0, float Pret = 0.0, string Nume = "", float Dimens = 0.0) : Masina(An, Pret, Nume), dimens(Dimens) {};
    ~Mini(){};

    void citire(istream&);
    void afis(ostream&);

    float pret_masina(){return Masina::pret;}
    void set_pret(float x){Masina::pret = x;}
    void set_an(int x){Masina::an = x;}
    void set_nume(string n){Masina::nume = n;}

};

void Mini::citire(istream& in)
{
    Masina::citire(in);

    int ok = 0;
    while(ok == 0)
    {
        cout<<"Dimenisiunea (<4): ";
        in>>dimens;
        ok = 1;

        try{
            if(dimens >= 4) throw(1);
        }
        catch(int x)
        {
            ok = 0;
            cout<<"Nu corespunde cu dimensiunea unei masini mini.\n Introduceti o valoare sub 4.\n";
        }
    }


}

void Mini::afis(ostream& out)
{
    Masina::afis(out);

    out<<"Masina mini cautata are dimensiunea "<<dimens<<".\n";
}

class Compacta:public Masina
{
    float dimens;
public:
    Compacta(int An = 0, float Pret = 0, string Nume = "", float Dimens = 0) : Masina(An, Pret, Nume), dimens(Dimens) {};
    ~Compacta(){};

    void citire(istream&);
    void afis(ostream&);

    float pret_masina(){return Masina::pret;}
    void set_pret(float x){Masina::pret = x;}
    void set_an(int x){Masina::an = x;}
    void set_nume(string n){Masina::nume = n;}

};

void Compacta::citire(istream& in)
{
    Masina::citire(in);

    int ok = 0;
    while(ok == 0)
    {
        cout<<"Dimenisiunea (4.2 < dimensiune < 4.5): ";
        in>>dimens;
        ok = 1;

        try{
            if(dimens < 4.2 || dimens > 4.5) throw(1);
        }
        catch(int x)
        {
            ok = 0;
            cout<<"Nu corespunde cu dimensiunea unei masini mini.\n Introduceti o valoare cuprinsa intre 4.2 si 4.5.\n";
        }
    }
}

void Compacta::afis(ostream& out)
{
    Masina::afis(out);

    out<<"Masina compacta cautata are dimensiunea "<<dimens<<".\n";
}

class Monovolum:public Masina
{
protected:
    int nr_pers;
public:
    Monovolum(int An = 0, float Pret = 0, string Nume = "", int NP = 0) : Masina(An, Pret, Nume), nr_pers(NP)
    {
        int aux = SingletonCr::getInstanta()->getMonoC();
        SingletonCr::getInstanta()->setMonoC(aux + 1);
    }
    ~Monovolum(){};

    void citire(istream&);
    void afis(ostream&);
    virtual float get_disc(){return 0;}
    virtual void set_pret(float x){Masina::pret = x;}
    float pret_masina(){return Masina::pret;}
    void set_an(int x){Masina::an = x;}
    void set_nume(string n){Masina::nume = n;}
};

void Monovolum::citire(istream& in)
{
    Masina::citire(in);

    int ok = 0;
    while(ok == 0)
    {
        cout<<"Capacitate persoane (5 <= persoane <= 7): ";
        in>>nr_pers;
        ok = 1;

        try{
            if(nr_pers < 5 || nr_pers > 7) throw(1);
        }
        catch(int x)
        {
            ok = 0;
            cout<<"Capaciatatea de persoane nu se incadreaza in categoria monovolumelor.\n Introduceti o valoare cuprinsa intre 5 si 7.\n";
        }
    }
}

void Monovolum::afis(ostream& out)
{
    Masina::afis(out);

    out<<"Masina monovolum cautata are o capacitate de "<<nr_pers<<" persoane.\n";

    out<<"Pretul masinii este "<<pret_masina()<<"\n";
}

class Sh:public Monovolum
{
    int luna;
public:
    Sh(int An = 0, float Pret = 0, string Nume = "", int NP = 0, int L = 0):Monovolum(An, Pret, Nume, NP), luna(L){};
    ~Sh(){};

    float get_disc()
    {
        if(luna == 6 || luna == 7 || luna == 8)
            return 0.1 * pret;
        else
            return ((2022 - an) / 100) * pret;
    }

    void set_pret(float x){pret = x;}
    void set_an(int x){Masina::an = x;}
    void set_nume(string n){Masina::nume = n;}

    void afis(ostream& out){Monovolum::afis(out);}
};

template<> class Vanzare<Monovolum>{
    static int mon_vand;
    int nr_mon;
    set<pair<Monovolum*, bool>> vandM;
    set<pair<Monovolum*, bool>> stocM;
public:
    Vanzare& operator-=(Monovolum& M)
    {
        int aux = SingletonCr::getInstanta()->getMonoC() - 1;
        nr_mon = aux;
        SingletonCr::getInstanta()->setMonoC(aux);

        mon_vand++;

        bool sh;
        int op;
        cout<<"Citeste 1 daca masina este second hand sau 0 altfel\n";
        cin>>op;
        if(op == 1)
            sh = true;
        else
            sh = false;

        vandM.insert(make_pair(&M, sh));
        return *this;
    }

    Vanzare& operator+=(Monovolum& M)
    {
        int aux = SingletonCr::getInstanta()->getMonoC() + 1;
        nr_mon = aux;
        SingletonCr::getInstanta()->setMonoC(aux);

        bool sh;
        int op;
        cout<<"Citeste 1 daca masina este second hand sau 0 altfel\n";
        cin>>op;
        if(op == 1)
            sh = true;
        else
            sh = false;

        stocM.insert(make_pair(&M, sh));
        return *this;
    }

    float pret()
    {
         for(auto& it : vandM)
         {
            Monovolum* m = dynamic_cast<Monovolum*>(it.first);
            m->set_pret(m->get_disc());
         }
    }

    void afis()
    {
        for(auto& it : vandM)
        {
            Monovolum* m = dynamic_cast<Monovolum*>(it.first);
            m->afis(cout);
        }
    }
};
int Vanzare<Monovolum>::mon_vand = 0;

class MasinaBuilder{
    Masina m;
public:
    MasinaBuilder& set_an(int an){
        m.set_an(an);
        return *this;
    }


    MasinaBuilder& set_pret(float pret){
        m.set_pret(pret);
        return *this;
    }

    MasinaBuilder& set_nume(string nume){
        m.set_nume(nume);
        return *this;
    }

    Masina build(){
        return m;
    }
};

class MasinaFactory{
public:
    static Mini getMasinaMini() {return Mini(2008, 38544.62, "Mini Cooper", 3.8);}
    static Compacta getMasinaCompacta() {return Compacta(2018, 45571.61, "Ford Focus", 4.3);}
    static Monovolum getMasinaMonovolum() {return Monovolum(2016, 78571.73, "VW Touran", 7);}
    static Sh getMonovolumSh(){return Sh(2007, 9141.99, "Opel Zafira", 7, 7);}
};

int main()
{
    Mini m = MasinaFactory::getMasinaMini();
    Compacta m2 = MasinaFactory::getMasinaCompacta();
    Monovolum m3 = MasinaFactory::getMasinaMonovolum();
    Sh m4 = MasinaFactory::getMonovolumSh();

    SingletonCr::getInstanta()->getVanzare() += m;
    SingletonCr::getInstanta()->getVanzare() += m2;
    SingletonCr::getInstanta()->getVanzare() += m3;
    SingletonCr::getInstanta()->getVanzare() += m4;

    MasinaBuilder builder;
    Masina m5 = builder.set_an(2020).set_pret(98129.12).set_nume("Ford Mustang").build();

    SingletonCr::getInstanta()->getVanzare() += m5;

    SingletonCr::getInstanta()->getVanzare().afis();

    int n;
    cout<<"Numarul de masini create si vandute";
    cin>>n;
    try{
        for(int i = 0; i < n; i++){
            int op, f;
            cout<<"0 -> Masina Mini\n";
            cout<<"1 -> Masina Compacta\n";
            cout<<"2 -> Masina Monovolum\n";
            cout<<"3 -> Monovolum Second-Hand\n";
            cin>>op;
            Masina* M;
            if(op == 0){
                M = new Mini();
                cin>>*M;
                SingletonCr::getInstanta()->getVanzare() += *M;
                cout<<"Daca doriti sa vindeti masina apasati tasta 1\n";
                cin>>f;
                if(f == 1)
                    SingletonCr::getInstanta()->getVanzare() -= *M;
            }
            else if(op == 1){
                M = new Compacta();
                cin>>*M;
                SingletonCr::getInstanta()->getVanzare() += *M;
                cout<<"Daca doriti sa vindeti masina apasati tasta 1\n";
                cin>>f;
                if(f == 1)
                    SingletonCr::getInstanta()->getVanzare() -= *M;
            }
            else if(op == 2){
                M = new Monovolum();
                cin>>*M;
                SingletonCr::getInstanta()->getVanzare() += *M;
                cout<<"Daca doriti sa vindeti masina apasati tasta 1\n";
                cin>>f;
                if(f == 1)
                    SingletonCr::getInstanta()->getVanzare() -= *M;
            }
            else if(op == 3)
            {
                M = new Sh();
                cin>>*M;
                SingletonCr::getInstanta()->getVanzare() += *M;
                cout<<"Daca doriti sa vindeti masina apasati tasta 1\n";
                cin>>f;
                if(f == 1)
                    SingletonCr::getInstanta()->getVanzare() -= *M;
            }
        }
    }catch(...){
        cout<<"Nu exsita masina de tipul introdus\n";
    }

    SingletonCr::getInstanta()->getVanzare().afis();

    return 0;
}
