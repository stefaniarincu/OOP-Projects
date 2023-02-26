#include <iostream>
#include <cstring>
#include <ctime>
#include <windows.h>

using namespace std;

string luni[12] = {"Ianuarie", "Februarie", "Martie", "Aprilie",
                   "Mai", "Iunie", "Iulie", "August", "Septembrie",
                   "Octombrie", "Noiembrie", "Decembrie"};

class Data{
    int zi;
    char *luna;
    int an;

public:
    Data(){
       zi = 0;
       luna = NULL;
       an = 0;
    }

    Data(int an){
        this->an = an;
        luna = NULL;
        zi = 0;
    }

    Data(int Zi, char *Luna, int An)
    {
        zi = Zi;

        luna = new char[strlen(Luna)+1];
        strcpy(luna, Luna);

        an = An;
    }

    ~Data()
    {
        if(luna != NULL) delete[]luna;
    }

    Data(const Data& d);

    virtual void set_zi(int);
    virtual int get_zi();
    virtual void set_luna(char*);
    virtual char* get_luna();
    virtual void set_an(int);
    virtual int get_an();

    friend istream& operator>>(istream& in, Data& d);
    friend ostream& operator<<(ostream& out, Data& d);

    Data& operator=(const Data&);
};

void Data::set_zi(int Zi){zi = Zi;}
int Data::get_zi(){return zi;}

void Data::set_luna(char* Luna){
    luna = new char[strlen(Luna)+1];
    strcpy(luna, Luna);
}
char* Data::get_luna(){return luna;}

void Data::set_an(int An){an = An;}
int Data::get_an(){return an;}

Data::Data(const Data& d)
{
    this->zi = d.zi;

    this->luna = new char[strlen(d.luna)+1];
    strcpy(this->luna, d.luna);

    this->an = d.an;
}

istream& operator>>(istream& in, Data& d){
    int flag = 0;
    while(flag == 0){
        flag = 1;
        cout<<"Ziua (numar natural > 0): ";
        in>>d.zi;

        cout<<"Luna (numele lunii in limba romana): ";
        char s[200];
        in.get();
        in.get(s, 200);
        d.luna = new char[strlen(s)+1];
        strcpy(d.luna, s);

        cout<<"Anul (numar natural > 0): ";
        in>>d.an;

        try{
            if(d.get_zi() > 31)throw(0);
            if((d.get_luna() == "aprilie" || d.get_luna() == "iunie" || d.get_luna() == "septembrie"
                || d.get_luna() == "noiembrie")&& d.get_zi() == 31) throw(1);
            if(d.get_an()%4 == 0 && d.get_luna() == "februarie" && d.get_zi() > 29)throw(2);
            if(d.get_an()%4 == 1 && d.get_luna() == "februarie" && d.get_zi() > 28)throw(3);
        }
        catch(int x)
        {
            if(x == 0){
                cout<<"Ziua citita: "<<d.get_zi()<<" nu exista in calendar\n\n";
            }
                else if(x == 1){
                    cout<<"Luna: "<<d.get_luna()<<" nu poate avea mai mult de 30 de zile. Ati citit data: "<<d.get_zi()<<"\n\n";
                }
                    else if(x == 2){
                        cout<<"Anul: "<<d.get_an()<<" este an bisect, iar luna: "<<d.get_luna()<<" nu are mai mult de 29 de zile. Ai citit ziua: "<<d.get_zi()<<"\n\n";
                    }
                        else cout<<"Anul: "<<d.get_an()<<" nu este an bisect, iar luna: "<<d.get_luna()<<" nu are mai mult de 28 de zile. Ai citit ziua: "<<d.get_zi()<<"\n\n";
            flag = 0;
        }
    }
    return in;
}

ostream& operator<<(ostream& out, Data& d){
    out<<"Data ceruta este: "<<d.zi<<" "<<d.luna<<" "<<d.an<<".";
    return out;
}

Data& Data::operator=(const Data& d)
{
    if(this == &d)
        return *this;

    this->zi = d.zi;

    this->luna = new char[strlen(d.luna)+1];
    strcpy(this->luna, d.luna);

    this->an = d.an;

    return *this;
}

class Angajat{
protected:
    string nume;
    string prenume;
    float salariu;
    const float prima;
    Data data_angajare;
public:
    Angajat():prima(1000){
        nume = "";
        prenume = "";
        salariu = 0.0;
    }

    Angajat(string Nume, string Prenume, float Salariu, int Zi, char* Luna, int An):prima(1000){
        nume = Nume;
        prenume = Prenume;
        salariu = Salariu;
        data_angajare.set_zi(Zi);
        data_angajare.set_luna(Luna);
        data_angajare.set_an(An);
    }

    Angajat(string Nume, string Prenume, float Salariu):prima(1000){
        nume = Nume;
        prenume = Prenume;
        salariu = Salariu;
    }

    ~Angajat(){}

    Angajat(Angajat& a);

    virtual void set_nume(string);
    virtual string get_nume();
    virtual void set_prenume(string);
    virtual string get_prenume();
    virtual void set_salariu(float);
    virtual float get_salariu();

    friend istream& operator>>(istream& in, Angajat& a);
    friend ostream& operator<<(ostream& out, Angajat& a);

    Angajat& operator=(Angajat&);

    virtual float sal_prima(){return salariu + prima;}

    void introducere(){
        cout<<"Angajat\n\n";
    }
};

void Angajat::set_nume(string Nume){nume = Nume;}
string Angajat::get_nume(){return nume;}

void Angajat::set_prenume(string Prenume){prenume = Prenume;}
string Angajat::get_prenume(){return prenume;}

void Angajat::set_salariu(float Salariu){salariu = Salariu;}
float Angajat::get_salariu(){return salariu;}

Angajat::Angajat(Angajat& a):prima(1000)
{
    this->nume = a.nume;

    this->prenume = a.prenume;

    this->salariu = a.salariu;

    this->data_angajare.set_zi(a.data_angajare.get_zi());

    this->data_angajare.set_luna(a.data_angajare.get_luna());

    this->data_angajare.set_an(a.data_angajare.get_an());
}

istream& operator>>(istream& in, Angajat& a){
    int flag = 0;
    cout<<"Citeste numele angajatului: ";
    in>>a.nume;

    cout<<"Citeste prenumele angajatului: ";
    in>>a.prenume;

    while(flag == 0){
        flag = 1;

        cout<<"Citeste salariul angajatului: ";
        in>>a.salariu;

        try{
            if(!float(a.salariu) || a.salariu < 0)throw(1);
        }
        catch(int x)
        {
                cout<<"\nPentru salariu trebuie introdusa o valoare numerica rational pozitiva!\n\n";
                flag = 0;
        }
    }

    cout<<"Citeste data calendaristica in care acesta s-a angajat\n";
    in>>a.data_angajare;

    return in;
}

ostream& operator<<(ostream& out, Angajat& a){
    out<<"\nAngajatul se numeste: "<<a.nume<<" "<<a.prenume<<".\n";
    out<<"Acesta castiga un salariu de "<<a.salariu<<" lei.\n";
    out<<"De asemenea, data angajarii este de: "<<a.data_angajare.get_zi()<<" "<<a.data_angajare.get_luna()<<" "<<a.data_angajare.get_an();
    out<<"\n\n";
    return out;
}

Angajat& Angajat::operator=(Angajat& a)
{
    if(this == &a)
        return *this;

    this->nume = a.nume;

    this->prenume = a.prenume;

    this->salariu = a.salariu;

    this->data_angajare.set_zi(a.data_angajare.get_zi());

    this->data_angajare.set_luna(a.data_angajare.get_luna());

    this->data_angajare.set_an(a.data_angajare.get_an());

    return *this;
}

class Part_Time : public Angajat{
    int nr_ore_zi;
    Data final_contract;
public:
    Part_Time(){
        nr_ore_zi = 0;
    }

    Part_Time(string Nume, string Prenume, float Salariu, int Z, char* Lun, int A, int Nr_ore_zi, int Zi, char* Luna, int An):Angajat(Nume, Prenume, Salariu, Z, Lun, A){
        nr_ore_zi = Nr_ore_zi;
        final_contract.set_zi(Zi);
        final_contract.set_luna(Luna);
        final_contract.set_an(An);
    }

    Part_Time(int Nr_ore_zi){
        nr_ore_zi = Nr_ore_zi;
    }

    ~Part_Time(){}

    Part_Time(Part_Time& pt);

    virtual void set_ore(int);
    virtual int get_ore();

    friend istream& operator>>(istream& in, Part_Time& pt);
    friend ostream& operator<<(ostream& out, Part_Time& pt);

    Part_Time& operator=(Part_Time&);

    float sal_prima(){
        time_t ttime = time(0);
        int dt = gmtime(&ttime)->tm_mon;
        int dtan = gmtime(&ttime)->tm_year;
        int ok = 1, var;

        int a = final_contract.get_an();

        if(a < dtan) return -1;

        string s = final_contract.get_luna();
        string t = luni[dt];

        if(s.length() == t.length()){
            for(int i = 0; i < s.length(); i++)
                if(tolower(s[i]) != tolower(t[i]))
                    ok = 0;}
            else ok = 0;

        if(s[0] == 'i')
        {
            if(s[1] == 'a') var = 0;
                else
                {
                    if(s[2] == 'n') var = 5;
                        else var = 6;
                }
        }
            else if(s[0] == 'f') var = 1;
                else if(s[0] == 'm')
                {
                    if(s[2] == 'r') var = 2;
                        else var = 4;
                }
                    else if(s[0] == 'a')
                    {
                        if(s[1] == 'p') var = 3;
                          else var = 7;
                    }
                        else if(s[0] == 's') var = 8;
                            else if(s[0] == 'o') var = 9;
                                else if(s[0] == 'n') var = 10;
                                    else if(s[0] == 'd') var = 11;

        if(var < dt) return -1;

        if(ok == 1)
            return salariu + prima * 0.75;
            else
                return salariu + prima;
    }

    void introducere(){
        cout<<"Angajat Part-Time\n\n";
    }
};

void Part_Time::set_ore(int Nr_ore_zi){nr_ore_zi = Nr_ore_zi;}
int Part_Time::get_ore(){return nr_ore_zi;}

Part_Time::Part_Time(Part_Time& pt):Angajat(pt)
{
    this->nr_ore_zi = pt.nr_ore_zi;

    this->final_contract.set_zi(pt.final_contract.get_zi());

    this->final_contract.set_luna(pt.final_contract.get_luna());

    this->final_contract.set_an(pt.final_contract.get_an());
}

istream& operator>>(istream& in, Part_Time& pt){
    in>>dynamic_cast<Angajat&>(pt);

    int flag = 0;
    while(flag == 0){
        flag = 1;

        cout<<"Citeste numarul de ore lucrate pe zi: ";
        in>>pt.nr_ore_zi;

        try{
            if(!int(pt.nr_ore_zi) || pt.nr_ore_zi < 0)throw(1);
        }
        catch(int x)
        {
                cout<<"\nPentru orele lucrate trebuie introdusa o valoare numerica naturala!\n\n";
                flag = 0;
        }
    }

    cout<<"Citeste data calendaristica in care s-a finalizat contractul\n";
    in>>pt.final_contract;

    return in;
}

ostream& operator<<(ostream& out, Part_Time& pt){
    out<<"\nAngajatul "<<pt.nume<<" "<<pt.prenume<<" lucreaza part-time, muncind: "<<pt.nr_ore_zi<<" ore pe zi.\n";
    out<<"Data finalizarii contractului este de: "<<pt.final_contract.get_zi()<<" "<<pt.final_contract.get_luna()<<" "<<pt.final_contract.get_an()<<"\n";
    return out;
}

Part_Time& Part_Time::operator=(Part_Time& pt)
{
    if(this == &pt)
        return *this;

    Angajat::operator=(pt);

    this->nr_ore_zi = pt.nr_ore_zi;

    this->final_contract.set_zi(pt.final_contract.get_zi());

    this->final_contract.set_luna(pt.final_contract.get_luna());

    this->final_contract.set_an(pt.final_contract.get_an());

    return *this;
}

class Permanent : public Angajat{
    int nr_minori_intretinere;
public:
    Permanent(){
        nr_minori_intretinere = 0;
    }

    Permanent(string Nume, string Prenume, float Salariu, int Z, char* Lun, int A, int Nr_minori_intretinere):Angajat(Nume, Prenume, Salariu, Z, Lun, A){
        nr_minori_intretinere = Nr_minori_intretinere;
    }

    Permanent(int Nr_minori_intretinere){
        nr_minori_intretinere = Nr_minori_intretinere;
    }

    ~Permanent(){}

    Permanent(Permanent& p);

    virtual void set_minori_intretinere(int);
    virtual int get_minori_intretinere();

    friend istream& operator>>(istream& in, Permanent& p);
    friend ostream& operator<<(ostream& out, Permanent& p);

    Permanent& operator=(Permanent&);

    float sal_prima(){
        float x = 2020 - data_angajare.get_an();
        return salariu + prima + prima * (x / 100) * nr_minori_intretinere;
    }

    void introducere(){
        cout<<"Angajat Permanent\n\n";
    }
};

void Permanent::set_minori_intretinere(int Nr_minori_intretinere){nr_minori_intretinere = Nr_minori_intretinere;}
int Permanent::get_minori_intretinere(){return nr_minori_intretinere;}

Permanent::Permanent(Permanent& p):Angajat(p)
{
    this->nr_minori_intretinere = p.nr_minori_intretinere;
}

istream& operator>>(istream& in, Permanent& p){
    in>>dynamic_cast<Angajat&>(p);

    int flag = 0;
    while(flag == 0){
        flag = 1;

        cout<<"Citeste numarul de minori trecuti pe intretinere: ";
        in>>p.nr_minori_intretinere;

        try{
            if(!int(p.nr_minori_intretinere) || p.nr_minori_intretinere < 0)throw(1);
        }
        catch(int x)
        {
                cout<<"\nPentru numarul de minori trebuie introdusa o valoare numerica naturala!\n\n";
                flag = 0;
        }
    }
    return in;
}

ostream& operator<<(ostream& out, Permanent& p){
    out<<"\nAngajatul "<<p.nume<<" "<<p.prenume<<" are "<<p.nr_minori_intretinere<<" minori trecuti la intretinere.\n";
    return out;
}

Permanent& Permanent::operator=(Permanent& p)
{
    if(this == &p)
        return *this;

    Angajat::operator=(p);

    this->nr_minori_intretinere = p.nr_minori_intretinere;

    return *this;
}

void prezentare(Angajat& a){a.introducere();}

int main()
{
    cout<<"                   ------------ DISCLAIMER --------------"<<endl;
    cout<<endl;
    cout<<" Aceasta aplicatie simuleaza un program care ajuta in cadrul unei firme in procesul de salarizare."<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"                  Precizari despre folosirea aplicatiei:"<<endl;
    cout<<"- Daca unui angajat ii expira contractul de munca inainte de luna de la data curenta, atunci acesta NU mai intra in procesul de salarizare."<<endl;
    cout<<"- Luna calendaristica trebuie sa fie de tipul string scriindu-se numele lunii, IN LIMBA ROMANA."<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"-------Rugam citirea cu atentie a instructiunilor date pe ecran!----------"<<endl;
    cout<<endl;
    cout<<endl;
    cout<<"Daca ati citit acest mesaj, puteti trece mai departe!"<<endl;
    cout<<"Pentru acest lucru, apasati tasta ENTER!"<<endl;
    cin.ignore();
    system("cls");

    HANDLE console_color;
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console_color, 10);

    cout<<"--------- Alegeti o cifra care sa corespunda informatiilor dorite! ----------"<<endl;
    cout<<"Pentru a afla detalii despre o data apasati tasta 1\n";
    cout<<"Pentru a afla detalii despre angajati (in general) apasati tasta 2\n";
    cout<<"Pentru a afla detalii despre angajatii part-time apasati tasta 3\n";
    cout<<"Pentru a afla detalii despre angajatii permanenti apasati tasta 4\n\n";
    cout<<"Introduceti numarul optinuii pe care doriti sa o executati, dupa care apasati tasta ENTER!\n";

    int op;
    cin>>op;

    system("cls");

    while(op == 1 || op == 2 || op == 3 || op == 4)
    {
        switch(op)
        {
            case 1:
            {
                cout<<"------Ati ales sa aflati detalii despre o data calendaristica------\n\n";
                cout<<"Introduceti o data calendaristica\n";

                Data d;
                cin>>d;

                cout<<"\nSe afiseaza data calendaristica\n";
                cout<<"------"<<d<<"------\n\n";

                cout<<"\nDaca doriti sa vedeti cum putem construi o data folosind parametrii apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                int optiune;
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom construi o data folosind parametrii\n";
                    Data d1(3, "ianuarie", 2021);

                    cout<<"Dupa cum puteti observa, acum vom afisa detalii despre o data calendaristica fara a va cere sa introduceti nimic\n";
                    cout<<"\nSe afiseaza data calendaristica\n";
                    cout<<"------"<<d1<<"------\n\n";
                }

                cout<<"\nDaca doriti sa vedeti procesul de copiere a unei date deja citite intr-o variabila noua apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom copia data introdusa de dumneavoastra intr-o noua variabila\n\n";

                    cout<<"Se atribuie unei date noi valoarea unei datei deja citite\n\n";
                    Data d2 = d;

                    cout<<"Vom observa ca acum cele doua date sunt identice\n";
                    cout<<d<<"-------vs------"<<d2<<"\n\n";
                }
                break;
            }
            case 2:
            {
                cout<<"------Ati ales sa aflati detalii despre angajati (in general)------\n\n";
                cout<<"Introduceti date despre un angajat\n";

                Angajat a;
                cin>>a;

                cout<<"\nSe afiseaza datele despre angajat\n";
                cout<<a<<"\n";

                cout<<"\nDaca doriti sa vedeti cum putem construi un angajat folosind parametrii apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                int optiune;
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"\nIn continuare vom construi un angajat folosind parametrii\n";
                    Angajat a1("Pitco", "Natalia", 6791.99, 3, "martie", 2022);

                    cout<<"Dupa cum puteti observa, acum vom afisa detalii despre noul angajat fara a va cere sa introduceti nimic\n";
                    cout<<"\nSe afiseaza datele despre angajat\n";
                    cout<<a1<<"\n";
                }

                cout<<"\nDaca doriti sa vedeti procesul de copiere a datelor unui angajat deja citite intr-un nou obiect de tip 'angajat' apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom copia datele introduse de dumneavoastra despre angajat intr-un nou obiect de tip 'angajat'\n\n";

                    cout<<"Se atribuie unui nou angajat valoarile angajatului deja citit\n";
                    Angajat a2 = a;

                    cout<<"Vom observa ca acum cei doi angajati sunt identici\n";
                    cout<<a<<"-------vs------"<<a2<<"\n";
                }
                break;
            }
            case 3:
            {
                cout<<"------Ati ales sa aflati detalii despre angajati part-time------\n\n";
                cout<<"Introduceti date despre un angajat part-time\n";

                Part_Time pt;
                cin>>pt;

                cout<<"\nSe afiseaza datele despre angajatul part-time\n";
                cout<<pt<<"\n";

                cout<<"\nDaca doriti sa vedeti cum putem construi un angajat part-time folosind parametrii apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                int optiune;
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"\nIn continuare vom construi un angajat part-time folosind parametrii\n";

                    Part_Time pt1("Pitco", "Natalia", 6791.99, 3, "aprilie", 2022, 8, 3, "mai", 2022);

                    cout<<"Dupa cum puteti observa, acum vom afisa detalii despre noul angajat part-time fara a va cere sa introduceti nimic\n";
                    cout<<"\nSe afiseaza datele despre angajatul part-time\n";
                    cout<<pt1<<"\n";
                }

                cout<<"\nDaca doriti sa vedeti procesul de copiere a datelor unui angajat part-time deja citite intr-un nou obiect de tip 'angajat part-time' apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom copia datele introduse de dumneavoastra despre angajatul part-time intr-un nou obiect de tip 'angajat part-time'\n\n";

                    cout<<"Se atribuie unui nou angajat part-time valoarile angajatului part-time deja citit\n";
                    Part_Time pt2 = pt;

                    cout<<"Vom observa ca acum cei doi angajati part-time sunt identici\n";
                    cout<<pt<<"-------vs------"<<pt2<<"\n";
                }

                cout<<"\nDaca doriti sa cititi mai multi angajati part-time ai companiei apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";

                    cout<<"Cititi cati angajati part-time se afla in aceasta companie\n";
                    int nr_ang;
                    cin>>nr_ang;

                    cout<<"\n\nIn continuare cititi date despre cei "<<nr_ang<<" angajati part-time ai companiei\n\n";

                    Part_Time ang_pt[nr_ang + 1];
                    for(int i = 1; i <= nr_ang; i++)
                    {
                        cin>>ang_pt[i];
                        cout<<"\n\n";
                    }

                    cout<<"Daca doriti sa observati procesul de salarizare pentru acesti angajati apasati tasta 1\n";
                    cout<<"Altfel apasati oricare alta cifra\n";
                    cin>>optiune;
                    cout<<"\n\n";

                    if(optiune == 1)
                    {
                        cout<<"Ati apasat tasta 1\n";
                        cout<<"Va vom prezenta procesul de salarizare pentru cei "<<nr_ang<<" angajati part-time ai companiei\n";

                        for(int i = 1; i <= nr_ang; i++)
                        {
                            if(ang_pt[i].sal_prima() == -1)
                                cout<<"Nu mai este angajat\n";
                              else
                              {
                                cout<<ang_pt[i].get_nume()<<" "<<ang_pt[i].get_prenume()<<":       ---Salariu vechi---   "<<ang_pt[i].get_salariu();
                                cout<<"   ---Salariu nou---       "<<ang_pt[i].sal_prima()<<"\n";
                              }
                        }
                    }
                }
                ///UPCASTING
                cout<<"\nDaca doriti sa observati procesul de UPCASTING apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom creea un obiect de tip 'part-time'\n";
                    Part_Time pt3;

                    cout<<"Vom observa ca acesta va afisa ceea ce declaram in functia din clasa 'Angajat' chiar daca avem o functie cu acelasi nume in clasa 'Part_Time'\n";
                    cout<<"-------";
                    prezentare(pt3);

                    cout<<"Daca vom apela functia 'introducere' direct din clasa 'Part_Time', atunci se va afisa altceva\n";
                    cout<<"-------";
                    pt3.introducere();
                }
                break;
            }
            case 4:
            {
                cout<<"------Ati ales sa aflati detalii despre angajati permanenti------\n\n";
                cout<<"Introduceti date despre un angajat permanent\n";

                Permanent p;
                cin>>p;

                cout<<"\nSe afiseaza datele despre angajatul permanent\n";
                cout<<p<<"\n";

                cout<<"\nDaca doriti sa vedeti cum putem construi un angajat permanet folosind parametrii apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                int optiune;
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"\nIn continuare vom construi un angajat permanent folosind parametrii\n";
                    Permanent p1("Pitco", "Natalia", 6791.99, 3, "martie", 2008, 4);

                    cout<<"Dupa cum puteti observa, acum vom afisa detalii despre noul angajat permanent fara a va cere sa introduceti nimic\n";
                    cout<<"\nSe afiseaza datele despre angajatul permanent\n";
                    cout<<p1<<"\n";
                }

                cout<<"\nDaca doriti sa vedeti procesul de copiere a datelor unui angajat permanent deja citite intr-un nou obiect de tip 'angajat permanent' apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom copia datele introduse de dumneavoastra despre angajatul permanent intr-un nou obiect de tip 'angajat permanent'\n\n";

                    cout<<"Se atribuie unui nou angajat permanent valoarile angajatului permanent deja citit\n";
                    Permanent p2 = p;

                    cout<<"Vom observa ca acum cei doi angajati permanenti sunt identici\n";
                    cout<<p<<"-------vs------"<<p2<<"\n";
                }

                cout<<"\nDaca doriti sa cititi mai multi angajati permanenti ai companiei apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;
                cout<<"\n\n";

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";

                    cout<<"Cititi cati angajati permanenti se afla in aceasta companie\n";
                    int nr_ang;
                    cin>>nr_ang;

                    cout<<"\n\nIn continuare cititi date despre cei "<<nr_ang<<" angajati permanenti ai companiei\n\n";

                    Permanent ang_p[nr_ang + 1];
                    for(int i = 1; i <= nr_ang; i++)
                    {
                        cin>>ang_p[i];
                        cout<<"\n\n";
                    }

                    cout<<"Daca doriti sa observati procesul de salarizare pentru acesti angajati apasati tasta 1\n";
                    cout<<"Altfel apasati oricare alta cifra\n";
                    cin>>optiune;
                    cout<<"\n\n";

                    if(optiune == 1)
                    {
                        cout<<"Ati apasat tasta 1\n";
                        cout<<"Va vom prezenta procesul de salarizare pentru cei "<<nr_ang<<" angajati permanenti ai companiei\n";

                        for(int i = 1; i <= nr_ang; i++)
                        {
                            cout<<ang_p[i].get_nume()<<" "<<ang_p[i].get_prenume()<<":       ---Salariu vechi---   "<<ang_p[i].get_salariu();
                            cout<<"   ---Salariu nou---       "<<ang_p[i].sal_prima()<<"\n";
                        }
                    }
                }

                ///UPCASTING
                cout<<"\nDaca doriti sa observati procesul de UPCASTING apasati tasta 1\n";
                cout<<"Altfel apasati oricare alta cifra\n";
                cin>>optiune;

                if(optiune == 1)
                {
                    cout<<"Ati apasat tasta 1\n";
                    cout<<"In continuare vom creea un obiect de tip 'permanent'\n";
                    Permanent p3;

                    cout<<"Vom observa ca acesta va afisa ceea ce declaram in functia din clasa 'Angajat' chiar daca avem o functie cu acelasi nume in clasa 'Permanent'\n";
                    cout<<"-------";
                    prezentare(p3);

                    cout<<"Daca vom apela functia 'introducere' direct din clasa 'Permanent', atunci se va afisa altceva\n";
                    cout<<"-------";
                    p3.introducere();
                }
                break;
            }
         }
            cout<<"Ati finalizat optiunea dorita\n\n";
            cout<<"Daca mai doriti noi informatii apasati tastele indicate\n\n";

            system("cls");

            cout<<"Pentru a afla detalii despre o data apasati tasta 1\n";
            cout<<"Pentru a afla detalii despre angajati (in general) apasati tasta 2\n";
            cout<<"Pentru a afla detalii despre angajatii part-time apasati tasta 3\n";
            cout<<"Pentru a afla detalii despre angajatii permanenti apasati tasta 4\n\n";
            cout<<"Daca nu mai doriti informatii apasati oricare alta cifra\n\n";
            cout<<"Introduceti numarul optinuii pe care doriti sa o executati, dupa care apasati tasta ENTER!\n";

            int op;
            cin>>op;

            system("cls");
    }
    cout<<"Ati finalizat procesul!\n";
    cout<<"Va multumim!\n";
    return 0;
}
