#include <iostream>
#include <cstring>

using namespace std;

class Actor{
    char* numeActor;
    int varsta;
    int nrPremii; ///numarul premiilor obtinute
    int k; ///anii diferiti in care a luat premii
    int *an; ///anul in care a primit fiecare premiu

public:
    Actor(){
        an = NULL;
        k = 0;
        numeActor = NULL;
        varsta = 0;
        nrPremii = 0;
    }

    ~Actor(){
        if (numeActor != NULL) delete[] numeActor;
        if (an != NULL) delete[]an;
   }

    Actor(int k){
        this->k = k;
        an = new int[k];
        numeActor = NULL;
        varsta = 0;
        nrPremii = 0;
    }

    Actor(bool b){
        if(b == true) cin>>this->k>>an;
         else {f.open ....}

    Actor(char* NumeActor, int Varsta)
    {
        numeActor = new char[strlen(NumeActor)+1];
        strcpy(numeActor, NumeActor);

        varsta = Varsta;

        nrPremii = 0;
        k = 0;
        an = NULL;
    }

    Actor(char* NumeActor, int Varsta, int NrPremii){
        numeActor = new char[strlen(NumeActor)+1];
        strcpy(numeActor, NumeActor);

        varsta = Varsta;
        nrPremii = NrPremii;

        k = 0;
        an = NULL;
    }

    void Prez_act(){
        cout<<numeActor<<" are "<<varsta<<" ani, iar pana in prezent a castigat ";
        cout<<nrPremii<<" de premii."<<endl;
    }

    void set_nameA(char*);
    char* get_nameA();

    Actor(const Actor& a);

    friend istream& operator>>(istream& in, Actor& a);
    friend ostream& operator<<(ostream& out, Actor& a);

    ///Actor& operator+(int);
    friend Actor& operator+(Actor& a,int x);
    friend Actor& operator+(int x, Actor& a);

    operator char*(){return numeActor;}
    operator int(){return varsta;}

 //   int operator[](int index){return an[index];}

    Actor& operator=(const Actor&);
    Actor& operator-();
    Actor& operator-(const Actor&);
    Actor& operator++();
    Actor operator++(int);
    int operator!=(const Actor& a){if(strcmp(this->numeActor, a.numeActor) != 0)return 0;
                                    else return 1;}
    Actor& operator+=(const Actor& a);
    Actor& operator!();
};

void Actor::set_nameA(char* NumeActor){
        numeActor = new char[strlen(NumeActor)+1];
        strcpy(numeActor, NumeActor);}
char* Actor::get_nameA(){return numeActor;}

Actor::Actor(const Actor& a){
    this->numeActor = new char[strlen(a.numeActor)+1];
    strcpy(this->numeActor, a.numeActor);

    this->varsta = a.varsta;
    this->nrPremii = a.nrPremii;

    this->k = a.k;
    this->an = new int[this->k];
    for(int i = 0; i < this->k; i++)
        this->an[i] = a.an[i];
}

istream& operator>>(istream& in, Actor& a){
    cout<<"Numele de actorului: "<<endl;
    char s[200];
    in.get();
    in.get(s,200);
    a.numeActor = new char[strlen(s)+1];
    strcpy(a.numeActor, s);

    cout<<"Varsta actorului: "<<endl;
    in>>a.varsta;

    cout<<"Numarul de prmii castigate de acesta: "<<endl;
    in>>a.nrPremii;

    cout<<"Numarul de ani distincti in care a primit premiile: "<<endl;
    in>>a.k;

    cout<<"Anii distincti sunt: "<<endl;
    a.an = new int[a.k];
    for(int i = 0; i < a.k; i++)
        in>>a.an[i];
    cout<<endl;
    return in;
}

ostream& operator<<(ostream& out, Actor& a){
    out<<a.numeActor<<" are varsta de "<<a.varsta<<"."<<endl;
    out<<"Pana in prezent a castigat "<<a.nrPremii<<" premii."<<endl;
    out<<"Acestea au fost castigate in "<<a.k<<" ani, si anume: ";
    for(int i = 0; i < a.k; i++)
        out<<a.an[i]<<" ";
    out<<".\n";
    return out;
}
/*
Actor& Actor::operator+(int x){
    cout<<"Se adauga anul "<<x<<" la anii in care acesta a castigat premii"<<endl;
    cout<<endl;
    k++;
    int *aux = new int[k];
    for(int i = 0; i < k-1; i++)
        aux[i] = an[i];
    aux[k-1] = x;
    delete[]an;
    an = aux;
    return *this;
}
*/

Actor& operator+(Actor& a,int x){
    cout<<"Se adauga anul "<<x<<" la anii in care acesta a castigat premii"<<endl;
    cout<<endl;
    a.k++;
    int *aux = new int[a.k];
    for(int i = 0; i < a.k-1; i++)
        aux[i] = a.an[i];
    aux[a.k-1] = x;
    delete[]a.an;
    a.an = aux;
    return a;
}

Actor& operator+(int x, Actor& a){
    cout<<"Se adauga anul "<<x<<" la anii in care acesta a castigat premii"<<endl;
    cout<<endl;
    a.k++;
    int *aux = new int[a.k];
    for(int i = 0; i < a.k-1; i++)
        aux[i] = a.an[i];
    aux[a.k-1] = x;
    delete[]a.an;
    a.an = aux;
    return a;
}

Actor& Actor::operator=(const Actor& a)
{
    if(this == &a)
        return *this;

    this->numeActor = new char[strlen(a.numeActor) + 1];
    strcpy(this->numeActor, a.numeActor);


    this->varsta = a.varsta;
    this->nrPremii = a.nrPremii;
    this->k = a.k;


    this->an = new int[k];
    for(int i = 0; i < this->k; ++i)
    {
        this->an[i] = a.an[i];
    }

    return *this;
}

Actor& Actor::operator-()
{
    this->varsta = -1 * this->varsta;
    this->nrPremii = -1 * this->nrPremii;
    this->k = this->k;

    for(int i = 0; i < this->k; ++i)
    {
        this->an[i] = -1 * this->an[i];
    }
    return *this;
}

Actor& Actor::operator-(const Actor& a)
{
    this->varsta = this->varsta - a.varsta;
    this->nrPremii = this->nrPremii - a.nrPremii;

    for(int i = 0; i < this->k; ++i)
    {
        this->an[i] = this->an[i] - a.an[i];
    }
    return *this;
}

Actor& Actor::operator++()
{
    for(int i = 0; i < this->k; ++i)
    {
        this->an[i] = this->an[i] + 1;
    }
    return *this;
}

Actor Actor::operator++(int i)
{
    Actor temp(*this);
    operator++();
    return temp;
}

Actor& Actor::operator+=(const Actor& a)
{
    this->nrPremii = this->nrPremii + a.nrPremii;
    int var = this->k;

    this->k = this->k + a.k;

    int *aux = new int[this->k];

    aux = this->an;

    delete[]this->an;

    this->an = aux;

    for(int i = 0; i < a.k; i++)
        this->an[var+i+1] = a.an[i];

    return *this;
}

Actor& Actor::operator!()
{
     if (this->nrPremii > 0) return *this;
     this->nrPremii = 0;
     delete[]this->an;
     return *this;
}

class Film{
    char* numeFilm;
    char* regizor;
    char* scriitorCarte;
    char* gen;
    double rating;
    int durata;
    int n; ///nr de preturi din lista
    float *v; ///pretul unui bilet
    int y; ///nr actori celebrii care joaca
    Actor A[15];

public:
    Film(){
        v = NULL;
        n = 0;
        numeFilm = NULL;
        regizor = NULL;
        scriitorCarte = NULL;
        gen = NULL;
        rating = 0.0;
        durata = 0;
        y = 0;
    }

    ~Film(){
        if (numeFilm != NULL) delete[] numeFilm;
        if (regizor != NULL) delete[] regizor;
        if (scriitorCarte != NULL) delete[] scriitorCarte;
        if (gen != NULL) delete[] gen;
        if (v != NULL) delete[]v;
    }

    Film(int n){
        this->n = n;
        v = new float[n];
        numeFilm = NULL;
        regizor = NULL;
        scriitorCarte = NULL;
        gen = NULL;
        rating = 0.0;
        durata = 0;
        y = 0;
    }

    void Prezentare_film_carte(){
        cout<<"Numele filmului: "<<numeFilm<<endl;
        cout<<"Regizorul: "<<regizor<<endl;
        cout<<"Inspirat dupa cartea scrisa de: "<<scriitorCarte<<endl;
        cout<<"Genul: "<<gen<<endl;
        cout<<"Are ratingul de: "<<rating<<" din 10"<<endl;
        cout<<"Durata filmului: "<<durata<<" minute"<<endl;
        cout<<endl;
    }

    void Prezentare_film(){
        cout<<"Numele filmului: "<<numeFilm<<endl;
        cout<<"Regizorul: "<<regizor<<endl;
        cout<<"Genul: "<<gen<<endl;
        cout<<"Are ratingul de: "<<rating<<" din 10"<<endl;
        cout<<"Durata filmului: "<<durata<<" minute"<<endl;
        cout<<endl;
    }

    Film(char* NumeFilm, char* Regizor, char* ScriitorCarte, char* Gen, double Rating, int Durata){
        numeFilm = new char[strlen(NumeFilm)+1];
        strcpy(numeFilm, NumeFilm);

        regizor = new char[strlen(Regizor)+1];
        strcpy(regizor, Regizor);

        scriitorCarte = new char[strlen(ScriitorCarte)+1];
        strcpy(scriitorCarte,ScriitorCarte);

        gen = new char[strlen(Gen)+1];
        strcpy(gen,Gen);

        rating = Rating;
        durata = Durata;

        n = 0;
        v = NULL;
        y = 0;
    }

    Film(char* NumeFilm, char* Regizor, char* Gen, double Rating, int Durata){
        numeFilm = new char[strlen(NumeFilm)+1];
        strcpy(numeFilm, NumeFilm);

        regizor = new char[strlen(Regizor)+1];
        strcpy(regizor, Regizor);

        gen = new char[strlen(Gen)+1];
        strcpy(gen,Gen);

        rating = Rating;
        durata = Durata;

        n = 0;
        v = NULL;
        scriitorCarte = NULL;
        y = 0;
    }


    void set_name(char* NumeFilm){
        numeFilm = new char[strlen(NumeFilm)+1];
        strcpy(numeFilm, NumeFilm);
    }
    char* get_name(){
        return numeFilm;
    }

    void set_duration(int Durata){
        durata = Durata;
    }
    int get_duration(){
        return durata;
    }

    Film(const Film&);

    friend istream& operator>>(istream& in, Film& f);
    friend ostream& operator<<(ostream& out, Film& f);

    Film& operator+(float);
    friend Film& operator+(float x, Film& f);

    friend Film& ad_actor(char* Nume, Film& f);
    friend Film& ad_actor(Film& f, char* Nume);

    operator char*(){return numeFilm;}
    operator double(){return rating;}

    char* operator[](int index){return A[index].get_nameA();}
};

Film::Film(const Film& f){
    this->numeFilm = new char[strlen(f.numeFilm)+1];
    strcpy(this->numeFilm, f.numeFilm);

    this->regizor = new char[strlen(f.regizor)+1];
    strcpy(regizor, f.regizor);

    this->scriitorCarte = new char[strlen(f.scriitorCarte)+1];
    strcpy(this->scriitorCarte, f.scriitorCarte);

    this->gen = new char[strlen(f.gen)+1];
    strcpy(this->gen,f.gen);

    this->rating = f.rating;
    this->durata = f.durata;

    this->n = f.n;
    this->v = new float[this->n];
    for(int i = 0; i < this->n; i++)
        this->v[i] = f.v[i];

    this->y = f.y;
    for(int i = 0; i < this->y; i++)
        this->A[i] = f.A[i];
}

istream& operator>>(istream& in, Film& f){
    char s[200];
    cout<<"Numele filmului este: "<<endl;
    in.get();
    in.get(s,200);
    f.numeFilm = new char[strlen(s)+1];
    strcpy(f.numeFilm, s);

    cout<<"Numele regizorului este: "<<endl;
    in.get();
    in.get(s,200);
    f.regizor = new char[strlen(s)+1];
    strcpy(f.regizor, s);

    cout<<"Numele scriitorului cartii dupa care este inspirat filmul este: "<<endl;
    in.get();
    in.get(s,200);
    f.scriitorCarte = new char[strlen(s)+1];
    strcpy(f.scriitorCarte, s);

    cout<<"Genul filmului este: "<<endl;
    in.get();
    in.get(s,200);
    f.gen = new char[strlen(s)+1];
    strcpy(f.gen, s);

    cout<<"Ratingul este: "<<endl;
    in>>f.rating;

    cout<<"Durata filmului este: "<<endl;
    in>>f.durata;

    cout<<"Numarul de preturi distincte de bilete este: "<<endl;
    in>>f.n;

    cout<<"Preturile distincte sunt: "<<endl;
    f.v = new float[f.n];
    for(int i = 0; i < f.n; i++)
        in>>f.v[i];

    cout<<"Numarul celebritatilor care apar in film: "<<endl;
    in>>f.y;

    cout<<"Numele celebritatilor: "<<endl;
    for(int i = 0; i < f.y; i++)
    {
        in.get();
        in.get(s,200);
        f.A[i].set_nameA(s);
    }
    cout<<endl;
    return in;
}

ostream& operator<<(ostream& out, Film& f){
    out<<"Filmul "<<f.numeFilm<<" regizat de "<<f.regizor<<" este inspirat dupa cartea scrisa de "<<f.scriitorCarte<<".\n";
    out<<"Genul fimului este "<<f.gen<<", avand un rating de "<<f.rating<<" si o durata de "<<f.durata<<" minute.\n";
    out<<"Exista "<<f.n<<" categorii de preturi, oferindu-se reduceri speciale, iar lista este: ";
    for(int i = 0; i < f.n; i++)
        out<<f.v[i]<<" ";
    out<<"\n";
    out<<"In acest film joaca "<<f.y<<" celebritati, dintre care: ";
    out<<f.A[0].get_nameA();
    for(int i = 1; i < f.y ;i++)
            out<<", "<<f.A[i].get_nameA()<<" ";
    out<<".\n";
    return out;
}

Film& Film::operator+(float x){
    cout<<"Se adauga noul pret "<<x<<" pentru biletele de film"<<endl;
    cout<<endl;
    n++;
    float *aux = new float[n];
    for(int i = 0; i < n-1; i++)
        aux[i] = v[i];
    aux[n-1] = x;
    delete[]v;
    v = aux;
    return *this;
}

Film& operator+(float x, Film& f){
    cout<<"Se adauga noul pret "<<x<<" pentru biletele de film"<<endl;
    cout<<endl;
    f.n++;
    float *aux = new float[f.n];
    for(int i = 0; i < f.n-1; i++)
        aux[i] = f.v[i];
    aux[f.n-1] = x;
    delete[]f.v;
    f.v = aux;
    return f;
}

Film& ad_actor(char* Nume, Film& f){
    cout<<"Se adauga noul actor "<<Nume<<" care este o celebritate"<<endl;
    cout<<endl;
    f.y++;
    f.A[f.y-1].set_nameA(Nume);
    return f;
}

Film& ad_actor(Film& f, char* Nume){
    cout<<"Se adauga noul actor "<<Nume<<" care este o celebritate"<<endl;
    cout<<endl;
    f.y++;
    f.A[f.y-1].set_nameA(Nume);
    return f;
}



class Cinematograf{
    char* numeCinema;
    char* localitate;
    char* numeStrada;
    int nr_strada;
    int nr_sali; ///cate sali sunt disponibile
    int m; ///in cate sali ruleaza un film
    int *sala; ///numarul salii respective in care ruleaza filmul
    int z; ///cate filme ruleaza
    Film F[20];

public:
    Cinematograf(){
        sala = NULL;
        m = 0;
        nr_sali = 0;
        numeCinema = NULL;
        localitate = NULL;
        numeStrada = NULL;
        nr_strada = 0;
        z = 0;
    }

    ~Cinematograf(){
        if (numeCinema != NULL) delete[] numeCinema;
        if (localitate != NULL) delete[] localitate;
        if (numeStrada != NULL) delete[] numeStrada;
        if (sala != NULL) delete[]sala;
    }

    Cinematograf(int m){
        this->m = m;
        sala = new int[m];
        numeCinema = NULL;
        localitate = NULL;
        numeStrada = NULL;
        nr_strada  = 0;
        nr_sali = 0;
        z = 0;
    }

    void DescriereCinema(){
        cout<<"Numele cinematografului este: "<<numeCinema<<endl;
        cout<<"Este situat in "<<localitate<<" pe strada "<<numeStrada<<" numarul "<<nr_strada<<endl;
        cout<<"Capacitate "<<nr_sali<<" sali"<<endl;
    }

    Cinematograf(char* NumeCinema, char* Localitate, char* NumeStrada, int Nr_strada, int Nr_sali){
        numeCinema = new char[strlen(NumeCinema)+1];
        strcpy(numeCinema, NumeCinema);

        localitate = new char[strlen(Localitate)+1];
        strcpy(localitate, Localitate);

        numeStrada = new char[strlen(NumeStrada)+1];
        strcpy(numeStrada, NumeStrada);

        nr_strada = Nr_strada;
        nr_sali = Nr_sali;

        m = 0;
        sala = NULL;
        z = 0;
    }
    void set_nameC(char*);
    char* get_nameC();

    Cinematograf(const Cinematograf&);

    friend istream& operator>>(istream& in, Cinematograf& c);
    friend ostream& operator<<(ostream& out, Cinematograf& c);

    Cinematograf& operator+(int);
    friend Cinematograf& operator+(int x, Cinematograf& c);

    friend Cinematograf& ad_film(char* Nume, Cinematograf& c);
  //  friend Cinematograf& ad_film(Cinematograf& c, char* Nume);

    Cinematograf& ad_film(char*);

    operator char*(){return numeCinema;}
    operator int(){return nr_sali;}

    char* operator[](int index){return F[index].get_name();}
};

void Cinematograf::set_nameC(char* NumeCinema){
    numeCinema = new char[strlen(NumeCinema)+1];
    strcpy(numeCinema, NumeCinema);}
char* Cinematograf::get_nameC(){return numeCinema;}

Cinematograf::Cinematograf(const Cinematograf& c){
    this->numeCinema = new char[strlen(c.numeCinema)+1];
    strcpy(this->numeCinema, c.numeCinema);

    this->localitate = new char[strlen(c.localitate)+1];
    strcpy(this->localitate, c.localitate);

    this->numeStrada = new char[strlen(c.numeStrada)+1];
    strcpy(this->numeStrada, c.numeStrada);

    this->nr_strada = c.nr_strada;
    this->nr_sali = c.nr_sali;

    this->m = c.m;
    this->sala = new int[c.m];
    for(int i = 0; i < this->m; i++)
        this->sala[i] = c.sala[i];

    this->z = c.z;
    for(int i = 0; i < this->z; i++)
        this->F[i] = c.F[i];
}

istream& operator>>(istream& in, Cinematograf& c){
    char s[200];

    cout<<"Numele cinematografului: "<<endl;
    in.get();
    in.get(s,200);
    c.numeCinema = new char[strlen(s)+1];
    strcpy(c.numeCinema, s);

    cout<<"Numele localitatii in care se afla cinematograful: "<<endl;
    in.get();
    in.get(s,200);
    c.localitate = new char[strlen(s)+1];
    strcpy(c.localitate, s);

    cout<<"Numele strazii pe care se afla cinematograful: "<<endl;
    in.get();
    in.get(s,200);
    c.numeStrada = new char[strlen(s)+1];
    strcpy(c.numeStrada, s);

    cout<<"Numarul strazii pe care se afla cinematograful: "<<endl;
    in>>c.nr_strada;

    cout<<"Numarul de sali disponibile: "<<endl;
    in>>c.nr_sali;

    cout<<"Numarul de sali in care ruleaza filme azi: "<<endl;
    in>>c.m;

    cout<<"Numarul fiecarei sali in care ruleaza filme azi: "<<endl;
    c.sala = new int[c.m];
    for(int i = 0; i < c.m; i++)
        in>>c.sala[i];

    cout<<"Numarul de filme care ruleaza azi: "<<endl;
    in>>c.z;

    cout<<"Numele filmelor respective: "<<endl;
    for(int i = 0; i < c.z; i++)
    {
        in.get();
        in.get(s,200);
        c.F[i].set_name(s);
    }
    cout<<endl;
    return in;
}

ostream& operator<<(ostream& out, Cinematograf& c){
    out<<"Cinematograful "<<c.numeCinema<<" se afla in "<<c.localitate<<" pe strada "<<c.numeStrada<<" numarul "<<c.nr_strada<<".\n";
    out<<"Acesta detine "<<c.nr_sali<<" sali, dintre care in "<<c.m<<" sali ruleaza astazi filme, salile fiind: ";
    for(int j = 0; j < c.m; j++)
                out<<c.sala[j]<<" ";
    out<<".\n";
    out<<c.z<<" filme ruleaza astazi: ";
    out<<c.F[0].get_name();
    for(int i = 1; i < c.z ;i++)
            out<<", "<<c.F[i].get_name()<<" ";
    out<<".\n";
    return out;
}

Cinematograf& Cinematograf::operator+(int x){
    cout<<"Se adauga noua sala "<<x<<" in care vor rula filme"<<endl;
    cout<<endl;
    m++;
    int *aux = new int[m];
    for(int i = 0; i < m-1; i++)
        aux[i] = sala[i];
    aux[m-1] = x;
    delete[]sala;
    sala = aux;
    return *this;
}

Cinematograf& operator+(int x, Cinematograf& c){
    cout<<"Se adauga noua sala "<<x<<" in care vor rula filme"<<endl;
    cout<<endl;
    c.m++;
    int *aux = new int[c.m];
    for(int i = 0; i < c.m-1; i++)
        aux[i] = c.sala[i];
    aux[c.m-1] = x;
    delete[]c.sala;
    c.sala = aux;
    return c;
}

Cinematograf& ad_film(char* Nume, Cinematograf& c){
    cout<<"Se adauga noul film "<<Nume<<" care va rula azi"<<endl;
    cout<<endl;
    c.z++;
    c.F[c.z-1].set_name(Nume);
    return c;
}
/*
Cinematograf& ad_film(Cinematograf& c, char* Nume){
    cout<<"Se adauga noul film "<<Nume<<" care va rula azi"<<endl;
    cout<<endl;
    c.z++;
    c.F[c.z-1].set_name(Nume);
    return c;
}*/

Cinematograf& Cinematograf::ad_film(char* Nume){
    cout<<"Se adauga noul film "<<Nume<<" care va rula azi"<<endl;
    cout<<endl;
    this->z++;
    this->F[this->z-1].set_name(Nume);
    return *this;
}

int main()
{
    int op;
    cout<<"Citeste o cifra"<<endl;
    cout<<"Pentru a afla date despre un actor citeste cifra 0"<<endl;
    cout<<"Pentru a afla date despre un film citeste cifra 1"<<endl;
    cout<<"Pentru a afla date despre un cinematograf citeste cifra 2"<<endl;
    cout<<"Daca nu mai doresti nicio informatie citeste orice alta cifra"<<endl;
    cout<<endl;

    cin>>op;

    cout<<endl;

    while(op == 0||op == 1||op == 2)
    {
        switch(op){
            case 0:{
                cout<<"Ai ales optiunea 0, adica vei afla date despre actori"<<endl;
                cout<<endl;

                Actor a1("Emma Watson", 31, 24);
                a1.Prez_act();

                cout<<endl;

                Actor a2;
                cout<<"Citeste date despre un actor"<<endl;
                cin>>a2;
                cout<<a2;

                cout<<endl;

                int n;
                cout<<"Citeste un numar care sa indice un nou an in care actorul respectiv a primit un premiu"<<endl;
                cin>>n; ///citeste un an in care a fost premiat

                cout<<endl;

                a2 = a2 + n; ///adauga anul citit la vectorul de ani in care a luat premii
                cout<<a2;

                cout<<endl;

                cout<<"Citeste un numar care sa indice un nou an in care actorul respectiv a primit un premiu"<<endl;
                cin>>n;  ///citeste un alt an in care a fost premiat

                cout<<endl;

                a2 = n + a2;  ///adauga noul an citit la vectorul curent de ani
                cout<<a2;

                cout<<endl;

                int index;

                cout<<"Citeste un index pentru care sa afisezi anul care corespunde acelei pozitii in lista de premii: ";
         //       cin>>index;

                cout<<endl;

                cout<<"Anul care se afla pe pozitia "<<index<<" in lista de premii este: ";
             //   cout<<a2[index]<<endl;

                cout<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Actor in char*, astfel incat sa se afiseze numele acestuia:\n";
                cout<<(char*)a2<<endl; ///operatorul de cast pentru char*

                cout<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Actor in int, astfel incat sa se afiseze varsta acestuia:\n";
                cout<<(int)a2<<endl; ///operatorul de cast pentru int

                cout<<endl;
                ///Adaugari

                cout<<"Aici incep adaugarile"<<"\n";
                Actor a3(2), a4("Tom Holland", 26), a5 = a2;

                cout<<a2<<" "<<-a2<<"\n";

                a2 = -a2;

                ++a2;

                cout<<a2<<"\n\n";

                a2++;

                cout<<a2<<"\n\n";

                int y = a2;
                cout<<y<<"\n\n";

                Actor v[3];
                v[0] = a1;
                v[1] = v[2] = a2 - a3;

                if(v[0] != v[2])v[0] += v[2];
                 else if(!v[1]) cout<<"v[1] nu e zero";
///Final Adaugari
                break;}
            case 1:{
                cout<<"Ai ales optiunea 1, adica vei afla date despre filme"<<endl;
                cout<<endl;

                Film f1("Little Women", "Greta Gerwig", "Louisa May Alcott", "Romance and Drama", 7.8, 135);
                f1.Prezentare_film_carte();

                Film f2("Red Notice", "Rawson Marshall Thurber", "Action, Comedy and Thriller", 6.4, 118);
                f2.Prezentare_film();

                cout<<endl;

                Film f3;
                cout<<"Citeste date despre un film"<<endl;
                cin>>f3;
                cout<<f3;

                cout<<endl;

                float x;
                cout<<"Citeste un nou pret pentru bilete"<<endl;
                cin>>x; ///citim un nou pret de bilet

                cout<<endl;

                f3 = f3 + x; ///adaugam noul pret citit la vectorul de preturi
                cout<<f3;

                cout<<endl;

                cout<<"Citeste un nou pret pentru bilete"<<endl;
                cin>>x;  ///citim un alt nou pret de bilet

                cout<<endl;

                f3 = x + f3;  ///adaugam si actualul pret citit la vectorul de preturi
                cout<<f3;

                cout<<endl;

                char s[200];

                cout<<"Citeste o noua celebritate care joaca in filmul "<<f3.get_name()<<endl;
                cin.get();
                cin.get(s, 200);
                cout<<endl;

                cout<<ad_actor(s, f3);

                cout<<endl;

                cin.get();
                cout<<"Citeste o noua celebritate care joaca in filmul "<<f3.get_name()<<endl;
                cin.get();
                cin.get(s, 200);

                cout<<endl;

                cout<<ad_actor(f3, s);

                cout<<endl;

                int index;

                cout<<"Citeste un index pentru care sa afisezi numele actorului care corespunde acelei pozitii in lista: ";
                cin>>index;

                cout<<endl;

                cout<<"Numele actorului care joaca in filmul "<<f3.get_name()<<" si se afla pe pozitia "<<index<<" in lista este: ";
                cout<<f3[index]<<endl;

                cout<<endl;

                Film f4(f1);  ///constructor de copiere
                Film f5 = f1;  ///constructor de copiere

                cout<<"Citeste un nume pe care sa il atribui unui film"<<endl;
                cin.get();
                cin.get(s, 200);
                f4.set_name(s); ///resetam/setam numele unui film printr-un set-ter, redenumindu-l
                cout<<"Numele filmului este: "<<f4.get_name()<<endl; ///afisam numele nou prin functia get-ter

                cout<<endl;

                cout<<"Citeste un numar pe care sa il atribui unui film ca durata"<<endl;
                cin>>x;
                f4.set_duration(x); ///resetam/setam durata unui film printr-un set-ter
                cout<<"Durata filmului este de: "<<f4.get_duration()<<" minute"<<endl; ///afisam durata noua prin functia get-ter

                cout<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Film in char*, astfel incat sa se afiseze numele acestuia:\n";
                cout<<(char*)f3<<endl; ///operatorul de cast pentru char*

                cout<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Film in double, astfel incat sa se afiseze ratingul acestuia:\n";
                cout<<(double)f3<<endl; ///operatorul de cast pentru double

                cout<<endl;

                break;}
            case 2:{
                cout<<"Ai ales optiunea 2, adica vei afla date despre cinematografe"<<endl;
                cout<<endl;

                Cinematograf c1("Cinema City", "Bucuresti", "Liviu Rebreanu", 4, 20);
                c1.DescriereCinema();
                cout<<c1.get_nameC()<<endl;

                cout<<endl;

                Cinematograf c2;
                cout<<"Citeste date despre un cinematograf"<<endl;
                cin>>c2;
                cout<<c2;

                cout<<endl;

                int m;
                cout<<"Citeste o noua sala care se deschide pentru a rula filme in ea"<<endl;
                cin>>m; ///se deschide o noua sala si o citim

                cout<<endl;

                c2 = c2 + m; ///se adauga sala la vectorul de sali in care ruleaza filmele
                cout<<c2;

                cout<<endl;

                cout<<"Citeste o noua sala care se deschide pentru a rula filme in ea"<<endl;
                cin>>m; ///se mai deschide o noua sala si o citim

                cout<<endl;

                c2 = m + c2;  ///adaugam sala la vectorul de sali in care ruleaza filme
                cout<<c2;

                cout<<endl;

                char s[200], aux[200];
                cin.get();

                cout<<"Citeste un nou film care va rula azi in cinematograful "<<c2.get_nameC()<<endl;
                cin.get(s, 200); ///citesc un nou film care ruleaza in cinema

                cout<<endl;

                cout<<ad_film(s, c2); ///afisez noile detalii
                strcpy(aux,s);

                cout<<endl;

                cin.get();
                cout<<"Citeste un nou film care va rula azi in cinematograful "<<c2.get_nameC()<<endl;
                cin.get(s, 200);  ///citesc un alt nou film

                cout<<endl;

                cout<<c2.ad_film(s); ///afisez noile detalii despre cinema si filmele care ruleaza

                cout<<endl;

                int index;

                cout<<"Citeste un index pentru care sa afisezi numele filmului care corespunde acelei pozitii in lista: ";
                cin>>index;

                cout<<endl;

                cout<<"Numele filmului care se afla pe pozitia "<<index<<" in lista este: ";
                cout<<c2[index]<<endl;

                cout<<endl;

                cout<<"Se citeste numarul de cinematografe in care ruleaza filmul "<<aux<<endl;
                cin>>m;

                cout<<endl;

                Cinematograf c3[100];
                cout<<"Se citesc numele celor "<<m<<" cinematografe"<<endl;
                for(int i = 1; i <= m; i++){
                    cin.get();
                    cin.get(s, 200);
                    c3[i].set_nameC(s);
                }

                cout<<endl;

                cout<<"Astazi filmul "<<aux<<" va rula in cinematografele: ";
                cout<<c3[1].get_nameC();
                for(int i = 2; i <= m; i++)
                    cout<<", "<<c3[i].get_nameC();

                cout<<endl<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Cinematograf in char*, astfel incat sa se afiseze numele acestuia:\n";
                cout<<(char*)c2<<endl; ///operatorul de cast pentru char*

                cout<<endl;

                cout<<"Am folosit operatorul de cast pentru a converti obiectul Cinematograf in int, astfel incat sa se afiseze numarul de sali pe care le detine:\n";
                cout<<(int)c2<<endl; ///operatorul de cast pentru int

                cout<<endl;

                break;}
        }
        cout<<"Citeste o cifra"<<endl;
        cout<<"Pentru a afla date despre un actor citeste cifra 0"<<endl;
        cout<<"Pentru a afla date despre un film citeste cifra 1"<<endl;
        cout<<"Pentru a afla date despre un cinematograf citeste cifra 2"<<endl;
        cout<<"Daca nu mai doresti nicio informatie citeste orice alta cifra"<<endl;
        cout<<endl;
        cin>>op;

        cout<<endl;
    }
    return 0;
}

