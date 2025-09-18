//username-urile si parolele se gasesc in fisierul date_login
//merge doar cazul 1.Gestionarea posturilor si angajatilor - doar subcazurile;
//         1.Afisarea ierarhiei posturilor
//         2.Afisarea posturilor ocupate
//                -aici merge doar subcazul 1 - afisarea fisei unui angajat
//         3.Angajari
//                -merge subcazul 1.Afisarea CV-urilor
//                -la subcazul 2 intreaba doar de Stravu, web developeru, pt care nu exista post; o sa-ti dea mesajul bun
#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <random>
using namespace std;

int vtati_j[10000], niv_j[1000][1000], nr_pe_niv_j[1000], nr_niv_j, nr_j, nr_dep, nr_ang, nr_cv_ang, nr_utilizatori, nr_ret, nr_cret;
int vtati_f_i[10000], niv_f_i[1000][1000], nr_pe_niv_f_i[1000], nr_niv_f_i, nr_fur, nr_ingr;
int vtati_e[10000], niv_e[1000][1000], nr_pe_niv_e[1000], nr_niv_e, nr_et_de_prod, nr_tip_ret;
int id_i, id_superior_i; float pret_i; char nume_i[40], unit_i[10];

//nr_j=nr joburi; nr_dep=nr departamente; nr_ang=nr angajati; nr_fur=nr furnizori; nr_ingr=nr ingrediente; nr_cv_ang=nr CV-uri angajari

//vtati_j = vectorul de tati pentru joburi
//niv_j = matrice care tine id-urile joburilor grupate pe niveluri
//nr_pe_niv_j = nr de noduri de pe fiecare nivel al arborelui de joburi
//nr_niv_j = nr de niveluri al arborelui de joburi

//vtati_f_i = vectorul de tati pentru furnizori si ingrediente
//niv_f_i = matrice care tine id-urile furnizorilor si ingredientelor grupate pe niveluri
//nr_pe_niv_f_i = nr de noduri de pe fiecare nivel al arborelui de furnizori si ingrediente
//nr_niv_f_i = nr de niveluri al arborelui de furnizori si ingrediente

struct joburi
{
    int id, id_superior, zilelucr, orepezi, salariu;
    char nume[40];
}job[100];
struct angajat
{
    int id, ani_experienta, nr_limbi;
    char nume[40], prenume[40], data_nasterii[40], adresa[100], nrtel[15], email[40], limbi[10][40];
}ang[100];
struct departament
{
    int nr;
    char nume[40];
}dep[10];
struct furnizor
{
    int id;
    char nume[100];
    int id_superior;
}fur[100];
struct ingredient
{
    int id, id_superior;
    float pret;
    char nume[40], unit[10];
}ingr[300];
struct reteta
{
    int cod, nr_ingred, timpdeprep[50];
    float gramaj_ing[30];
    char tip[40], nume[40], nume_ing[30][40], unit_ing[30][10];
}ret[1000], cret[1000];
struct tip_produs
{
    int nr, nr_et;
    char nume[40];
}tipp[100];
struct etapa
{
   int cod, cod_sup;
   char nume[100];
}et[100];
struct CV_angajari
{
    int cod, ani_experienta, nr_limbi, nota;
    char nume[40], prenume[40];
    char data_nasterii[40], adresa[100], nrtel[15], email[40];
    char dep_dorit[40], job_dorit[40], limbi[10][40];
    char intentie[1000], studii[100], obs[5][100];
}CV[100];
struct date_login
{
    char username[100], parola[100];
}login[10];
struct nod
{
    int id, id_superior;
    float pret;
    char nume[40], unit[10];
    nod *st, *dr;
};
nod*r=NULL; nod*cresc=NULL; nod*descresc=NULL;



void initializari()
{
    int i;
    for (i=0; i<10000; i++)
        vtati_j[i]=-1;
    for (i=0; i<10000; i++)
        vtati_f_i[i]=-1;
    for (i=0; i<10000; i++)
        vtati_e[i]=-1;
}
char* fara_(char *x)
{
    int i;
    for (i=0; i<strlen(x); i++)
        if (x[i]=='_')
            x[i]=' ';
    return x;
}
char* cu_(char*x)
{
    int i;
    for (i=0; i<strlen(x); i++)
        if (x[i]==' ')
            x[i]='_';
    return x;
}
char prima_lit(char*x)
{
    return x[0];
}
void spatii(int x)
{
    int i;
    for (i=1; i<=x; i++)
        cout << " ";
}
void undersc(int x)
{
    int i;
    for (i=1; i<=x; i++)
        cout << "_";
}
int nrc(int x)
{
    int nrc=0;
    while(x)
    {
        nrc++;
        x/=10;
    }
    return nrc;
}



void citire_angajati()
{
    ifstream a("angajati.txt");
    int i=1, j;
    while (!a.eof())
    {
        a >> ang[i].id >> ang[i].nume >> ang[i].prenume >> ang[i].data_nasterii >> ang[i].adresa
          >> ang[i].nrtel >> ang[i].email >> ang[i].ani_experienta >> ang[i].nr_limbi;
        for (j=1; j<=ang[i].nr_limbi; j++)
            a >> ang[i].limbi[j];
        i++;
    }
    nr_ang=i-2;
    a.close();
}
void citire_furnizori()
{
    ifstream f("furnizori.txt");
    int i=1;
    while (!f.eof())
    {
        f >> fur[i].id >> fur[i].nume >> fur[i].id_superior;
        i++;
    }
    nr_fur=i-2;
    f.close();
}
void citire_ingrediente()
{
    ifstream ing("ingrediente.txt");
    int i=1;
    while (!ing.eof())
    {
        ing >> ingr[i].id >> ingr[i].nume >> ingr[i].id_superior >> ingr[i].pret >> ingr[i].unit;
        i++;
    }
    ing.close();
    nr_ingr=i-2;
}
void citire_tip_produse()
{
    ifstream tp("tip_produse.txt");
    int i=1;
    while (!tp.eof())
    {
        tp >> tipp[i].nr >> tipp[i].nume >> tipp[i].nr_et;
        i++;
    }
    tp.close();
    nr_tip_ret=i-2;
}
void citire_retete()
{
    ifstream r("retete.txt");
    int i=1, j, k, ii;
    while (!r.eof())
    {
        r >> ret[i].cod >> ret[i].tip >> ret[i].nume >> ret[i].nr_ingred;
        for (j=1; j<=ret[i].nr_ingred; j++)
            r >> ret[i].nume_ing[j] >> ret[i].gramaj_ing[j] >> ret[i].unit_ing[j];
        for (k=1; k<=nr_tip_ret; k++)
            if(strcmp(tipp[k].nume, ret[i].tip)==0)
                ii=k;
        for(j=1; j<=tipp[ii].nr_et; j++)
            r >> ret[i].timpdeprep[j];
        i++;
    }
    r.close();
    nr_ret=i-2;
    /*nr_tip_ret=1;
    strcpy(tip_ret[1], ret[1].tip);
    for (i=2; i<=nr_ret; i++)
        for (j=1; j<=nr_tip_ret; j++)
            if(strcmp(tip_ret[j], ret[i].tip)!=0)
            {
                nr_tip_ret++;
                strcpy(tip_ret[nr_tip_ret], ret[i].tip);
            }*/
}
void citire_retete_in_copie()
{
    ifstream cr("retete.txt");
    int i=1, j, k, ii;
    while (!cr.eof())
    {
        cr >> cret[i].cod >> cret[i].tip >> cret[i].nume >> cret[i].nr_ingred;
        for (j=1; j<=ret[i].nr_ingred; j++)
            cr >> cret[i].nume_ing[j] >> cret[i].gramaj_ing[j] >> cret[i].unit_ing[j];
        for (k=1; k<=nr_tip_ret; k++)
            if(strcmp(tipp[k].nume, cret[i].tip)==0)
                ii=k;
        for(j=1; j<=tipp[ii].nr_et; j++)
            cr >> cret[i].timpdeprep[j];
        i++;
    }
    cr.close();
    nr_cret=i-2;
}
void citire_departamente()
{
    ifstream d("departamente.txt");
    int i=1;
    while (!d.eof())
    {
        d >> dep[i].nr >> dep[i].nume;
        i++;
    }
    nr_dep = i-2;
    d.close();
}
void citire_joburi()
{
    ifstream j("joburi.txt");
    int i=1;
    while (!j.eof())
    {
        j >> job[i].id >> job[i].nume >> job[i].id_superior >> job[i].zilelucr >> job[i].orepezi >> job[i].salariu;
        i++;
    }
    nr_j = i-2;
    j.close();
}
void citire_CV_angajari()
{
    ifstream cv("CV_angajari.txt");
    int i=1, j;
    while (!cv.eof())
    {
        cv >> CV[i].cod >> CV[i].nume >> CV[i].prenume >> CV[i].data_nasterii >> CV[i].adresa >> CV[i].nrtel
           >> CV[i].email >> CV[i].ani_experienta >> CV[i].dep_dorit >> CV[i].job_dorit >> CV[i].nr_limbi;
        for (j=1; j<=CV[i].nr_limbi; j++)
            cv >> CV[i].limbi[j];
        cv >> CV[i].intentie >> CV[i].studii >> CV[i].nota >> CV[i].obs[1] >> CV[i].obs[2];
        i++;
    }
    nr_cv_ang = i-2;
    cv.close();
}
void citire_date_login()
{
    ifstream dl("date_login.txt");
    int i=1;
    while (!dl.eof())
    {
        dl >> login[i].username >> login[i].parola;
        i++;
    }
    nr_utilizatori=i-2;
    dl.close();
}
void citire_etape_de_prod()
{
    ifstream e("etape_de_productie.txt");
    int i=1;
    while (!e.eof())
    {
        e >> et[i].cod >> et[i].nume >> et[i].cod_sup;
        i++;
    }
    e.close();
    nr_et_de_prod=i-2;
}




void afisare_info_angajati()
{
    int i, j;
    for(i=1; i<=nr_ang; i++)
    {   cout << ang[i].id << " " << ang[i].nume << " " << ang[i].prenume << " " << fara_(ang[i].data_nasterii) << " "
             << fara_(ang[i].adresa) << " " << ang[i].nrtel << " " << ang[i].email << " " << ang[i].ani_experienta << " ";
        cu_(ang[i].adresa); cu_(ang[i].data_nasterii);
        for(j=1; j<=ang[i].nr_limbi; j++)
            cout << ang[i].limbi[j] << " ";
        cout << endl;
    }
}
void afisare_info_furnizori()
{
    int i;
    for (i=1; i<=nr_fur; i++)
    {
        cout << fur[i].id << " " << fara_(fur[i].nume) << " " << fur[i].id_superior << endl;
        cu_(fur[i].nume);
    }
}
void afisare_info_ingrediente()
{
    int i;
    for (i=1; i<=nr_ingr; i++)
    {
        cout << ingr[i].id << " " << fara_(ingr[i].nume) << " " << ingr[i].id_superior << " " << ingr[i].pret << " lei/" << ingr[i].unit << endl;
        cu_(ingr[i].nume);
    }
}
void afisare_info_joburi()
{
    int i;
    for (i=1; i<=nr_j; i++)
    {   cout << job[i].id << " " << fara_(job[i].nume) << " " << job[i].id_superior << " " << job[i].zilelucr
             << " zile/sapt " << job[i].orepezi << " ore/zi " << job[i].salariu << " lei" << endl;
        cu_(job[i].nume);
    }

}
void afisare_CV_angajari()
{
    int i, j;
    for(i=1; i<=nr_cv_ang; i++)
    {   cout << CV[i].cod << " " << CV[i].nume << " " << CV[i].prenume << " " << fara_(CV[i].data_nasterii) << " "
             << fara_(CV[i].adresa) << " " << CV[i].nrtel << " " << CV[i].email << " " << CV[i].ani_experienta << " ";
        cu_(CV[i].data_nasterii); cu_(CV[i].adresa);
        for(j=1; j<=CV[i].nr_limbi; j++)
            cout << CV[i].limbi[j] << " ";
        cout << fara_(CV[i].intentie) << " " << fara_(CV[i].studii) << " " << CV[i].nota << " " << fara_(CV[i].obs[1]) << " " << fara_(CV[i].obs[2]);
        cu_(CV[i].studii); cu_(CV[i].obs[1]); cu_(CV[i].obs[2]);
        cout << endl;
    }
}
void afisare_date_login()
{
    int i;
    for (i=1; i<=nr_utilizatori; i++)
        cout << i << ". " << login[i].username << " " << login[i].parola << endl;
}
void afisare_info_retete()
{
    int i, j;
    for (i=1; i<=nr_ret; i++)
    {
        cout<<ret[i].cod<<" "<<ret[i].tip<<" "<<ret[i].nume<<" "<<ret[i].nr_ingred<<" ";
        for (j=1; j<=ret[i].nr_ingred; j++)
            cout<<ret[i].nume_ing[j]<<" "<<ret[i].gramaj_ing[j]<<" "<<ret[i].unit_ing[j]<<" ";
        for(j=1; j<=10; j++)
            cout<<ret[i].timpdeprep[j]<<" ";
        cout<<endl;
    }
}



void stergerea_unui_CV(int poz)
{
    int i;
    for (i=poz; i<nr_cv_ang; i++)
    {   int j;
        CV[i].cod = CV[i+1].cod;
        CV[i].ani_experienta = CV[i+1].ani_experienta;
        CV[i].nr_limbi = CV[i+1].nr_limbi;
        CV[i].nota = CV[i+1].nota;
        strcpy(CV[i].nume, CV[i+1].nume);
        strcpy(CV[i].prenume, CV[i+1].prenume);
        strcpy(CV[i].data_nasterii, CV[i+1].data_nasterii);
        strcpy(CV[i].adresa, CV[i+1].adresa);
        strcpy(CV[i].nrtel, CV[i+1].nrtel);
        strcpy(CV[i].email, CV[i+1].email);
        strcpy(CV[i].dep_dorit, CV[i+1].dep_dorit);
        strcpy(CV[i].job_dorit, CV[i+1].job_dorit);
        for (j=1; j<=CV[i].nr_limbi; j++)
            strcpy(CV[i].limbi[j], CV[i+1].limbi[j]);
        strcpy(CV[i].intentie, CV[i+1].intentie);
        strcpy(CV[i].studii, CV[i+1].studii);
        strcpy(CV[i].obs[1], CV[i+1].obs[1]);
        strcpy(CV[i].obs[2], CV[i+1].obs[2]);
    }
    nr_cv_ang--;
}
void stergerea_unui_ang(int poz)
{
    int i;
    for (i=poz; i<nr_ang; i++)
    {   int j;
        ang[i].id = ang[i+1].id;
        ang[i].ani_experienta = ang[i+1].ani_experienta;
        ang[i].nr_limbi = ang[i+1].nr_limbi;
        strcpy(ang[i].nume, ang[i+1].nume);
        strcpy(ang[i].prenume, ang[i+1].prenume);
        strcpy(ang[i].data_nasterii, ang[i+1].data_nasterii);
        strcpy(ang[i].adresa, ang[i+1].adresa);
        strcpy(ang[i].nrtel, ang[i+1].nrtel);
        strcpy(ang[i].email, ang[i+1].email);
        for (j=1; j<=ang[i].nr_limbi; j++)
            strcpy(ang[i].limbi[j], ang[i+1].limbi[j]);
    }
    nr_ang--;
}
void stergerea_unei_etape(int poz)
{
    int i;
    for (i=poz; i<nr_et_de_prod; i++)
    {   et[i].cod = et[i+1].cod;
        et[i].cod_sup= et[i+1].cod_sup;
        strcpy(et[i].nume, et[i+1].nume);
        if((et[poz].cod/100)==(et[i].cod/100))
        {   et[i].cod--;
            et[i].cod_sup--;
        }
    }
    nr_et_de_prod--;
}


void sort_alf_cret()
{
    int i, j;
    /*int h, ki, kj, a, b, aux;
    char auxx[40];
    int cod, nr_ingred, timpdeprepi[50], timpdeprepj[50];
    float gramaj_ing[30];
    char tip[40], nume[40], nume_ing_i[30][40], nume_ing_j[30][40], unit_ing[30][10];*/
    for (i=1; i<nr_cret; i++)
    {
        for(j=i+1; j<=nr_cret; j++)
        {
            if(strcmp(cret[i].nume, cret[j].nume)>0)
            {   swap(cret[i], cret[j]);
                /*aux = cret[i].cod;
                cret[i].cod = cret[j].cod;
                cret[j].cod = aux;

                aux = cret[i].nr_ingred;
                cret[i].nr_ingred = cret[j].nr_ingred;
                cret[j].nr_ingred = aux;

                strcpy(auxx, cret[i].tip);
                strcpy(cret[i].tip, cret[j].tip);
                strcpy(cret[j].tip, auxx);

                strcpy(auxx, cret[i].nume);
                strcpy(cret[i].nume, cret[j].nume);
                strcpy(cret[j].nume, auxx);

                for(h=1; h<=cret[i].nr_ingred)

                ki=tipp[cautare_poz_tipp_dupa_nume_tip(cret[i].tip)].nr_et;
                kj=tipp[cautare_poz_tipp_dupa_nume_tip(cret[j].tip)].nr_et;

                for(a=1; a<=ki; a++)
                    timpdeprepi[a]=cret[i].timpdeprep[a];
                for(b=1; b<=kj; b++)
                    timpdeprepj[b]=cret[i].timpdeprep[b];*/
            }
        }
    }
}


void creare_arbore_joburi()
{
    int i;
    for (i=1; i<=nr_j; i++)
        vtati_j[job[i].id]=job[i].id_superior;
}
void creare_arbore_fur_si_ingr()
{
    int i;
    for (i=1; i<=nr_fur; i++)
        vtati_f_i[fur[i].id]=fur[i].id_superior;
    for (i=1; i<=nr_ingr; i++)
        vtati_f_i[ingr[i].id]=ingr[i].id_superior;
    //for (i=1; i<=nr_ingr; i++)
    //    if (vtati_f_i[i])
    //        cout << vtati_f_i[i] << " ";
}
void creare_arbore_et_de_prod()
{
    int i;
    for (i=1; i<=nr_et_de_prod; i++)
        vtati_e[et[i].cod]=et[i].cod_sup;
}



void citiri()
{
    citire_angajati();// cout << 'a';
    citire_departamente();// cout <<'b';
    citire_furnizori();// cout << 'c';
    citire_ingrediente();// cout <<'d';
    citire_joburi();// cout << 'e';
    citire_CV_angajari();
    citire_date_login();
    citire_etape_de_prod();
    citire_tip_produse();
    citire_retete();
}
void afisari_info()
{
    afisare_info_angajati(); cout << endl;
    afisare_info_furnizori(); cout << endl;
    afisare_info_ingrediente(); cout << endl;
    afisare_info_joburi(); cout << endl;
    afisare_date_login(); cout << endl;
    afisare_CV_angajari(); cout << endl;
    afisare_info_retete(); cout << endl;
}
void creare_arbori()
{
    creare_arbore_joburi();
    creare_arbore_fur_si_ingr();
    creare_arbore_et_de_prod();
}



int cautare_nr_dep_dupa_nume (char* nume)
{
    int i;
    for (i=1; i<=nr_dep; i++)
       if(strcmp(nume, dep[i].nume)==0)
           return dep[i].nr;
}
int cautare_poz_job_dupa_id(int id)
{
    int i;
    for(i=1; i<=nr_j; i++)
        if (id==job[i].id)
            return i;
}
int cautare_poz_ang_dupa_id(int id)
{
    int i;
    for (i=1; i<=nr_ang; i++)
        if (id==ang[i].id)
            return i;
}
int cautare_poz_fur_dupa_id(int id)
{
    int i;
    for (i=1; i<=nr_fur; i++)
        if (id==fur[i].id)
            return i;


}
int cautare_poz_ingr_dupa_id(int id)
{
     int i;
     for (i=1; i<=nr_ingr; i++)
        if (id==ingr[i].id)
            return i;
}
int cautare_poz_ang_dupa_nume(char *nume)
{
    int i;
    for (i=1; i<=nr_ang; i++)
        if (strcmp(nume, ang[i].nume)==0)
            return i;
    return -1;
}
int cautare_id_job_dupa_nume(char *nume)
{
    int i;
    for (i=1; i<=nr_j; i++)
        if (strcmp(nume, job[i].nume)==0)
            return job[i].id;
}
int cautare_id_job_dupa_job_dorit_CV (char *nume)
{
    int i;
    for (i=1; i<=nr_j; i++)
        if (strcmp(nume, job[i].nume)==0)
            return job[i].id;
    return -1;
}
int cautare_poz_et_dupa_cod(int cod)
{
    int i;
    for(i=1; i<=nr_et_de_prod; i++)
        if (cod==et[i].cod)
            return i;
}
int cautare_poz_et_dupa_nume(char* nume)
{
    int i; char copie[100];
    for(i=1; i<=nr_et_de_prod; i++)
    {
        strcpy(copie, et[i].nume);
        if (strcmp(nume, fara_(copie))==0)
            return i;
    }
    return -1;
}
int cautare_poz_tipp_dupa_nume_tip(char* nume)
{
    int i; char copie[100];
    for(i=1; i<=nr_tip_ret; i++)
    {
        strcpy(copie, tipp[i].nume);
        if (strcmp(nume, fara_(copie))==0)
            return i;
    }
    return -1;
}
int cautare_poz_fur_dupa_nume(char *nume)
{
    int i;
    for (i=1; i<=nr_fur; i++)
        if (strcmp(nume, fur[i].nume)==0)
            return i;
    return -1;
}

void matrice_niv_et(int vtati[10000], int niv[1000][1000], int nr_pe_niv[1000], int &nr_niv)
{
    int i, j, h, k, niv_prec=1, ok=1;
    niv[1][1]=1;
    nr_pe_niv[1]=1;
    while(ok==1)
    {
        ok=0; k=1;
        for (i=1; i<=nr_tip_ret; i++)// i=1...2
            for (h=1; h<=nr_pe_niv[niv_prec]; h++) //h=1...1
                for (j=i*100+1; j<=i*100+99; j++) //j=101....199
                    if (niv[niv_prec][h]==vtati[j]) //niv[1][1]==vtati[101] //1==1
                    {
                        niv[niv_prec+1][k]=j; //niv[2][1]=101
                        k++;//k=2
                        ok=1;
                    }
        nr_pe_niv[niv_prec+1]=k-1;
        niv_prec++;
    }
    nr_niv=niv_prec;
}
void matrice_niv_job(int vtati[10000], int niv[1000][1000], int nr_pe_niv[1000], int &nr_niv)
{
    int i, j, h, k, niv_prec=1, ok;
    niv[1][1]=100;
    nr_pe_niv[1]=1;
    do
    {
        ok=0; k=1;
        for (i=1; i<=nr_dep; i++)
            for (h=1; h<=nr_pe_niv[niv_prec]; h++)
                for (j=i*100; j<=i*100+99; j++)
                    if (niv[niv_prec][h]==vtati[j])
                    {
                        niv[niv_prec+1][k]=j;
                        k++;
                        ok=1;
                    }
        nr_pe_niv[niv_prec+1]=k-1;
        niv_prec++;
    }while (ok==1);
    nr_niv=niv_prec-1;
}


int suma_strlen_pe_niv_job(int x)
{
    int i, s=0;
    matrice_niv_job(vtati_j, niv_j, nr_pe_niv_j, nr_niv_j);
    for (i=1; i<=nr_pe_niv_j[x]; i++)
        s+=strlen(job[cautare_poz_job_dupa_id(niv_j[x][i])].nume);
    return s;
}
int suma_strlen_pe_niv_et(int x)
{
    int i, s=0;
    matrice_niv_et(vtati_e, niv_e, nr_pe_niv_e, nr_niv_e);
    for (i=1; i<=nr_pe_niv_e[x]; i++)
        s+=strlen(et[cautare_poz_et_dupa_cod(niv_e[x][i])].nume);
    return s;
}
void chestionar_creare_job(char* depar, char* post, char* sup, int &zile, int &ore, int &bani)
{
                int i, id, ok, okk, exista;
                spatii(80); cout << "Introduceti caracteristicile noului post." << endl << endl;
                spatii(60); cout << "Departamnet (conducere/bucatarie/relatii cu clientii/intretinere firma): ";
                cin.getline(depar, 40);
                ok=0;
                for (i=1; i<=nr_dep; i++)
                {
                    if (strcmp(depar, fara_(dep[i].nume))==0)
                    {   ok=1; id = i;}
                    cu_(dep[i].nume);
                }
                while (ok==0)
                {   cout << endl;
                    spatii(60); cout << "Acest departament nu exista in cadrul afacerii!" << endl;
                    spatii(60); cout << "Departament (conducere/bucatarie/relatii cu clientii/intretinere firma): "; cin.getline(depar, 40);
                    for (i=1; i<=nr_dep; i++)
                    {
                        if (strcmp(depar, fara_(dep[i].nume))==0)
                        {   ok=1; id = i;}
                        cu_(dep[i].nume);
                    }
                }
                spatii(60); cout << "Numele postului superior: "; cin.getline(sup, 40);
                ok=0;
                if (dep[id].nr==(cautare_id_job_dupa_nume(cu_(sup))/100))
                        ok=1; //jobul superiorului se afla in dep potrivit
                fara_(sup);
                okk=0;
                for (i=1; i<=nr_j; i++)
                {
                    if (strcmp(sup, fara_(job[i].nume))==0)
                        okk=1; //jobul superiorului exista
                    cu_(job[i].nume);
                }
                while (ok==0||okk==0)
                {   if (ok==0&&okk==1)
                    {
                        cout << endl;
                        spatii(60); cout << "Acest post nu se afla in departamentul <" << dep[id].nume << ">!" << endl;
                        spatii(60); cout << "Numele postului superior: "; cin.getline(sup, 40);
                    }
                    else if (ok==0&&okk==0)
                    {
                        cout << endl;
                        spatii(60); cout << "Acest post nu exista in cadrul afacerii!" << endl;
                        spatii(60); cout << "Numele postului superior: "; cin.getline(sup, 40);
                    }

                    ok=0;
                    if (dep[id].nr==(cautare_id_job_dupa_nume(cu_(sup))/100))
                        ok=1; //jobul superiorului se afla in dep potrivit
                    fara_(sup);
                    okk=0;
                    for (i=1; i<=nr_j; i++)
                    {
                        if (strcmp(sup, fara_(job[i].nume))==0)
                            okk=1; //jobul superiorului exista
                        cu_(job[i].nume);
                    }
                }
                spatii(60); cout << "Numele postului: "; cin.getline(post, 40);
                exista=0;
                for (i=1; i<=nr_j; i++)
                {
                    if (strcmp(post, fara_(job[i].nume))==0)
                        exista=1;
                    cu_(job[i].nume);
                }
                while (exista==1)//daca jobul exista deja
                {
                    cout << endl;
                    spatii(60); cout << "Un post cu acelasi nume exista deja!" << endl;
                    spatii(60); cout << "Numele postului: "; cin.getline(post, 40);
                    exista=0;
                    for (i=1; i<=nr_j; i++)
                    {   if (strcmp(post, fara_(job[i].nume))==0)
                            exista=1;
                        cu_(job[i].nume);
                    }
                }
                spatii(60); cout << "Nr. de zile lucratoare/saptamana: "; cin >> zile;
                spatii(60); cout << "Nr. de ore de lucru/zi: "; cin >> ore;
                spatii(60); cout << "Salariul lunar: "; cin >> bani;
                cout << endl;
}
void chestionar_adaugare_reteta(int &it, int &nr_ingred, int timpdeprep[50], float gramaj_ing[30], char tip[40], char nume[40], char nume_ing[30][40], char unit_ing[30][10])
{
    int i, j, exista; char zero[2]="0", copie[100];
    it=-1;
    cout << endl;
    spatii(75); cout << "Introduceti datele retetei:" << endl << endl;
    spatii(65); cout << "Numele retetei: "; cin.get(); cin.getline(nume, 40);
    exista=0;
                for (i=1; i<=nr_ret; i++)
                {
                    if (strcmp(nume, fara_(ret[i].nume))==0)
                        exista=1;
                    cu_(ret[i].nume);
                }
                while (exista==1)//daca reteta exista deja
                {
                    cout << endl << endl;
                    spatii(65); cout << "O reteta cu acelasi nume exista deja!" << endl;
                    spatii(65); cout << "Numele retetei: "; cin.getline(nume, 40);
                    exista=0;
                    for (i=1; i<=nr_ret; i++)
                    {   if (strcmp(nume, fara_(ret[i].nume))==0)
                            exista=1;
                        cu_(ret[i].nume);
                    }
                }
    cout << endl << endl;
    spatii(65); cout << "Tipul retetei (";
                        for (i=1; i<=nr_tip_ret; i++)
                            {
                                cout << fara_(tipp[i].nume);
                                cu_(tipp[i].nume);
                                if (i!=nr_tip_ret)
                                    cout << "/";
                            }
                            cout << "): "; cin.getline(tip, 40);
                            for (i=1; i<=nr_tip_ret; i++)
                            {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                    it=i;
                                cu_(tipp[i].nume);
                            }
                            while (it==-1)
                            {
                                cout << endl<< endl;
                                spatii(65); cout << "Acest tip de reteta nu exista!" << endl;
                                spatii(65); cout << "Tipul retetei (";
                                for (i=1; i<=nr_tip_ret; i++)
                                {
                                    cout << fara_(tipp[i].nume);
                                    cu_(tipp[i].nume);
                                    if (i!=nr_tip_ret)
                                        cout << "/";
                                }
                                cout << "): "; cin.getline(tip, 40);
                                for (i=1; i<=nr_tip_ret; i++)
                                {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                       it=i;
                                    cu_(tipp[i].nume);
                                }
                            }
    cout << endl << endl;
    spatii(65); cout << "Ingredientele necesare, insotite de gramaj si unitate de masura:" << endl;
    spatii(65); cout << "    APASATI TASTA 0 CAND ATI INTRODUS TOATE INGREDIENTELE!" << endl << endl;
    i=0;
    do
    {   cout << endl;
        i++;
        spatii(65); cout << "Ingredient: "; cin.getline(nume_ing[i], 40);
        if (strcmp(zero, nume_ing[i])!=0)
        {
            spatii(65); cout << "Gramaj: "; cin >> gramaj_ing[i];
            spatii(65); cout << "Unitatea de masura: "; cin.get(); cin.getline(unit_ing[i], 10);
        }
        cout << endl;
    }
    while (strcmp(zero, nume_ing[i])!=0);
    nr_ingred=i-1;
    cout << endl;
    spatii(65); cout << "Timpii de preparare: " << endl << endl;
    spatii(70); cout << " "; undersc(52); cout << endl;
    j=0;
    for (i=1; i<=nr_et_de_prod; i++)
        if(tipp[it].nr==et[i].cod/100)
            //if (strcmp(tipp[it].nume, et[i].nume)==0)
            {   j++;
                strcpy(copie, et[i].nume);
                spatii(70); cout << "|"; spatii(52); cout << "|" << endl;
                spatii(70); cout << "|  " << fara_(copie); spatii(50-strlen(et[i].nume)); cout << "|  Timpul necesar (in minute): "; cin >> timpdeprep[j];
                spatii(70); cout << "|"; undersc(52); cout << "|" << endl;
            }
}



void afisare_arbore_joburi()
{
    int i, j, k, h, sp; char copie[40];
    matrice_niv_job(vtati_j, niv_j, nr_pe_niv_j, nr_niv_j);
    cout << endl;
    for(i=1; i<=nr_niv_j; i++)
    {   if (nr_pe_niv_j[i]==1)
            sp=90;
        else if (nr_pe_niv_j[i]<9)
        {
            if (suma_strlen_pe_niv_job(i)>=105)
                sp=80;
            else sp=100;;
        }
        else if (nr_pe_niv_j[i]==9)
            sp=80;
        else sp=50;

        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-1; k++)
                cout << " ";
            for(h=1; h<=strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)+3; h++)
                cout << "_";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)+2; h++)
                cout << " ";
            cout << "|";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            int o;
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "| ";
            strcpy(copie, job[cautare_poz_job_dupa_id(niv_j[i][j])].nume);
            cout << fara_(strupr(copie));
            cout << " |";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)+2; h++)
                cout << "_";
            cout << "|";
        }
        cout << endl << endl;
    }
    //pt niv 5 - special - asistentii unui cofetar sef pe cate un rand
    //adauga -1 la for(i=..)
    //merge pe un singur rand pt 5 noduri pe nivelul 5
}
void afisare_arbore_joburi_si_angajati()
{
    int i, j, k, h, l, ii, sp; char copie[40];
    matrice_niv_job(vtati_j, niv_j, nr_pe_niv_j, nr_niv_j);
    cout << endl;
    for(i=1; i<=nr_niv_j; i++)
    {   if (nr_pe_niv_j[i]==1)
            sp=90;
        else if (nr_pe_niv_j[i]<9)
        {
            if (suma_strlen_pe_niv_job(i)>=105)
                sp=80;
            else sp=100;;
        }
        else if (nr_pe_niv_j[i]==9)
            sp=80;
        else sp=50;


        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-1; k++)
                cout << " ";
            for(h=1; h<=max(strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume), strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3)+2; h++)
                cout << "_";
            cout << " ";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=max(strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume), strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3)+2; h++)
                cout << " ";
            cout << "|";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            int o;
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "| ";
            strcpy(copie, job[cautare_poz_job_dupa_id(niv_j[i][j])].nume);
            cout << fara_(strupr(copie));
            if (strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)<strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3)
                for (o=1; o<=strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3-strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume); o++)
                   cout << " ";
            cout << " |";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            int o, ok=0;
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "| ";
            for (l=1; l<=nr_ang; l++)
                if(ang[l].id==niv_j[i][j])
                    ok=1;

            if(ok==1)
            {
                cout << prima_lit(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].prenume) << ". ";
                cout << fara_(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume);
                cu_(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume);

                if (strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)>strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3)
                    for (o=1; o<=strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)-strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)-3; o++)
                       cout << " ";
            }
            else
            {
                cout << "-";
                for (o=1; o<=strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume)-1; o++)
                    cout << " ";
            }
            cout << " |";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_j[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=max(strlen(job[cautare_poz_job_dupa_id(niv_j[i][j])].nume), strlen(ang[cautare_poz_ang_dupa_id(niv_j[i][j])].nume)+3)+2; h++)
                cout << "_";
            cout << "|";
        }
        cout << endl << endl;
    }
    //pt niv 5 - special - asistentii unui cofetar sef pe cate un rand
    //adauga -1 la for(i=..)
    //merge pe un singur rand pt 5 noduri pe nivelul 5

}
/*void afisare_arbore_fur_si_ingr()///probleme!!
{
    int i, j, k, h, sp;
    matrice_niv_job(vtati_f_i, niv_f_i, nr_pe_niv_f_i, nr_niv_f_i);
    cout << endl;
    for(i=1; i<=nr_niv_f_i; i++)
    {   if (nr_pe_niv_f_i[i]==1)
            sp=90;
        else if (nr_pe_niv_f_i[i]<9)
        {
            if (suma_strlen_pe_niv(i)>=105)
                sp=80;
            else sp=100;;
        }
        else if (nr_pe_niv_f_i[i]==9)
            sp=80;
        else sp=50;

        for(j=1; j<=nr_pe_niv_f_i[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_f_i[i]-1; k++)
                cout << " ";
            if (niv_f_i[i][j]%10==0)
                for(h=1; h<=strlen(fur[cautare_poz_fur_dupa_id(niv_f_i[i][j])].nume)+3; h++)
                    cout << "_";
            else
                for(h=1; h<=strlen(ingr[cautare_poz_ingr_dupa_id(niv_f_i[i][j])].nume)+3; h++)
                    cout << "_";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_f_i[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_f_i[i]-2; k++)
                cout << " ";
            cout << "|";
            if (niv_f_i[i][j]%10)
                for(h=1; h<=strlen(fur[cautare_poz_fur_dupa_id(niv_f_i[i][j])].nume)+2; h++)
                    cout << " ";
            else
                for(h=1; h<=strlen(ingr[cautare_poz_ingr_dupa_id(niv_f_i[i][j])].nume)+2; h++)
                    cout << " ";
            cout << "|";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_f_i[i]; j++)
        {
            int o;
            for(k=1; k<=sp/nr_pe_niv_f_i[i]-2; k++)
                cout << " ";
            cout << "| ";
            if (niv_f_i[i][j]%10==0)
                cout << fara_(strupr(fur[cautare_poz_fur_dupa_id(niv_f_i[i][j])].nume));
            else
                cout << fara_(strupr(ingr[cautare_poz_ingr_dupa_id(niv_f_i[i][j])].nume));
            cout << " |";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_j[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_f_i[i]-2; k++)
                cout << " ";
            cout << "|";
            if (niv_f_i[i][j]%10==0)
                for(h=1; h<=strlen(fur[cautare_poz_fur_dupa_id(niv_f_i[i][j])].nume)+2; h++)
                    cout << "_";
            else
                for(h=1; h<=strlen(ingr[cautare_poz_ingr_dupa_id(niv_f_i[i][j])].nume)+2; h++)
                    cout << "_";
            cout << "|";
        }
        cout << endl << endl;
    }
    //pt niv 5 - special - asistentii unui cofetar sef pe cate un rand
    //adauga -1 la for(i=..)
    //merge pe un singur rand pt 5 noduri pe nivelul 5
}*/

void afisare_arbore_et_de_prod() //nu afiseaza ultimul rand - problema in functia matrice_niv_et - REZOLVAT
{
    int i, j, k, h, sp; char copie[100];
    matrice_niv_et(vtati_e, niv_e, nr_pe_niv_e, nr_niv_e);
    //cout << endl << nr_tip_ret << endl << nr_niv_e << endl;
    //for (i=1; i<=nr_niv_e; i++)
    //{ for (j=1; j<=nr_pe_niv_e[i]; j++)
    //        cout << niv_e[i][j] << " " << et[cautare_poz_et_dupa_cod(niv_e[i][j])].nume << "        ";
    //    cout << endl;}
    cout << endl;
    for(i=1; i<=nr_niv_e; i++)
    {
        if (suma_strlen_pe_niv_et(i)<10)
        {
            if(nr_pe_niv_e[i]==1)
                sp=105;
            else
                sp=50;
        }
        else if (suma_strlen_pe_niv_et(i)>=10 && suma_strlen_pe_niv_et(i)<=40)
        {
            if(nr_pe_niv_e[i]==1)
                sp=50;
            else
                sp=80;
        }
        else if(suma_strlen_pe_niv_et(i)>40 && suma_strlen_pe_niv_et(i)<=60)
            sp=50;
        else if (suma_strlen_pe_niv_et(i)>=60)
            sp=40;
        else sp=60;
        /*if (nr_pe_niv_e[i]==1 && suma_strlen_pe_niv_et(i)<=10)
            sp=100;
        else if (suma_strlen_pe_niv_et(i)<=16)
            sp=90;
        else if (suma_strlen_pe_niv_et(i)>=70)
            sp=50;
        else sp=90;*/

        for(j=1; j<=nr_pe_niv_e[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_e[i]-1; k++)
                cout << " ";
            for(h=1; h<=strlen(et[cautare_poz_et_dupa_cod(niv_e[i][j])].nume)+3; h++)
                cout << "_";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_e[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_e[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=strlen(et[cautare_poz_et_dupa_cod(niv_e[i][j])].nume)+2; h++)
                cout << " ";
            cout << "|";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_e[i]; j++)
        {
            int o;
            for(k=1; k<=sp/nr_pe_niv_e[i]-2; k++)
                cout << " ";
            cout << "| ";
            strcpy(copie, et[cautare_poz_et_dupa_cod(niv_e[i][j])].nume);
            cout << fara_(strupr(copie));
            cout << " |";
        }
        cout << endl;
        for(j=1; j<=nr_pe_niv_e[i]; j++)
        {
            for(k=1; k<=sp/nr_pe_niv_e[i]-2; k++)
                cout << " ";
            cout << "|";
            for(h=1; h<=strlen(et[cautare_poz_et_dupa_cod(niv_e[i][j])].nume)+2; h++)
                cout << "_";
            cout << "|";
        }
        cout << endl << endl;
    }
    //pt niv 5 - special - asistentii unui cofetar sef pe cate un rand
    //adauga -1 la for(i=..)
    //merge pe un singur rand pt 5 noduri pe nivelul 5
}



void creare_caut_bin_ingr_alfabetic(nod*&r,int id_i, char nume_i[40], int id_superior_i, float pret_i, char unit_i[10])
{
    if(r)
    {
        if(strcmp(r->nume,nume_i)>0)
            creare_caut_bin_ingr_alfabetic(r->st,id_i, nume_i, id_superior_i, pret_i, unit_i);
        else if (strcmp(r->nume,nume_i)<0)
            creare_caut_bin_ingr_alfabetic(r->dr ,id_i, nume_i, id_superior_i, pret_i, unit_i);
    }
    else{   r=new nod;
            r->st=r->dr= NULL;
            strcpy(r->nume,nume_i);
            strcpy(r->unit,unit_i);
            r->id = id_i;
            r->id_superior = id_superior_i;
            r->pret = pret_i;
        }
}
void creare_caut_bin_ingr_dupa_pret_cresc(nod*&cresc,int id_i, char nume_i[40], int id_superior_i, float pret_i, char unit_i[10])
{
    if(cresc)
    {
        if(cresc->pret>pret_i)
            creare_caut_bin_ingr_dupa_pret_cresc(cresc->st,id_i, nume_i, id_superior_i, pret_i, unit_i);
        else
            creare_caut_bin_ingr_dupa_pret_cresc(cresc->dr ,id_i, nume_i, id_superior_i, pret_i, unit_i);
    }
    else{   cresc=new nod;
            cresc->st=cresc->dr= NULL;
            strcpy(cresc->nume,nume_i);
            strcpy(cresc->unit,unit_i);
            cresc->id = id_i;
            cresc->id_superior = id_superior_i;
            cresc->pret = pret_i;
        }
}
void creare_caut_bin_ingr_dupa_pret_descresc(nod*&descresc,int id_i, char nume_i[40], int id_superior_i, float pret_i, char unit_i[10])
{
    if(descresc)
    {
        if(descresc->pret<pret_i)
            creare_caut_bin_ingr_dupa_pret_descresc(descresc->st,id_i, nume_i, id_superior_i, pret_i, unit_i);
        else
            creare_caut_bin_ingr_dupa_pret_descresc(descresc->dr ,id_i, nume_i, id_superior_i, pret_i, unit_i);
    }
    else{   descresc=new nod;
            descresc->st=descresc->dr= NULL;
            strcpy(descresc->nume,nume_i);
            strcpy(descresc->unit,unit_i);
            descresc->id = id_i;
            descresc->id_superior = id_superior_i;
            descresc->pret = pret_i;
        }
}
void citire_caut_bin_ingr_alfabetic()
{
    ifstream ingg("ingrediente.txt");
    while (ingg >> id_i >> nume_i >> id_superior_i >> pret_i >> unit_i)
    {   creare_caut_bin_ingr_alfabetic(r,id_i, nume_i, id_superior_i, pret_i, unit_i);}
}
void citire_caut_bin_ingr_dupa_pret_cresc()
{
    ifstream ingg("ingrediente.txt");
    while (ingg >> id_i >> nume_i >> id_superior_i >> pret_i >> unit_i)
    {   creare_caut_bin_ingr_dupa_pret_cresc(cresc,id_i, nume_i, id_superior_i, pret_i, unit_i);}
}
void citire_caut_bin_ingr_dupa_pret_descresc()
{
    ifstream ingg("ingrediente.txt");
    while (ingg >> id_i >> nume_i >> id_superior_i >> pret_i >> unit_i)
    {   creare_caut_bin_ingr_dupa_pret_descresc(descresc,id_i, nume_i, id_superior_i, pret_i, unit_i);}
}
void inserare_bin_ingr(nod*&r, int id, char nume[40], int id_superior, char unit[10])
{   if(r)
        if(strcmp(r->nume, nume)>0)inserare_bin_ingr(r->st, id, nume, id_superior, unit);
            else inserare_bin_ingr(r->dr,id, nume, id_superior, unit);
      else {r=new nod;
            r->st=r->dr= NULL;
            strcpy(r->nume, nume);
            r->id=id;
            r->id_superior=id_superior;
            if(strcmp(unit, "g")==0)
                strcpy(r->unit, "kg");
            else if(strcmp(unit, "ml")==0)
                strcpy(r->unit, "l");
            else strcpy(r->unit, unit);

            int lowerLimit = 1;
            int upperLimit = 20;
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<int> dist(lowerLimit, upperLimit);
            int randomNumber = dist(gen);

            r->pret = randomNumber;
           }
}
void afisare_caut_bin_ingr(nod*r)
{
    if(r)
        {afisare_caut_bin_ingr(r->st);
         spatii(20); cout << fara_(r->nume); spatii(40-strlen(r->nume)); cout << r->pret << " lei/" << r->unit << endl;
         cu_(r->nume);
         afisare_caut_bin_ingr(r->dr);
        }
}
void afisare_caut_bin_ingr_in_fisier_ajutor(nod*r, ofstream &out)
{
    if (r)
    {   afisare_caut_bin_ingr_in_fisier_ajutor(r->st, out);
        out << r->id << " " << r->nume << " " << r->id_superior << " " << r->pret << " " << r->unit << endl;
        afisare_caut_bin_ingr_in_fisier_ajutor(r->dr, out);
    }
}

void afisare_caut_bin_ingr_in_fisier(nod*r)
{
    ofstream out;
    out.open("ingrediente.txt", ios::out | ios::trunc);
    if (out.is_open())
    {
        afisare_caut_bin_ingr_in_fisier_ajutor(r, out);
        out.close();
    }
}

int cautare_bin_ingr(nod*&r, char nume[40])
{if(r)
    if(strcmp(nume,r->nume)<0) cautare_bin_ingr(r->st,nume);
              else if(strcmp(nume,r->nume)>0)cautare_bin_ingr(r->dr,nume);
                        else return 1;
    else return -1;
}
/*void cmmd(nod*r, nod*& q)
{ nod*p;
    if(q->dr) cmmd(r,q->dr);
           else
            {strcpy(r->nume,q->nume);
             strcpy(r->pre,q->pre);
             p=q;
             q=q->st;
             delete p;
            }
}
void stergere(nod*&r, char autor[40])
{ nod*q;
    if(r)
        if(strcmp(r->nume,autor)==0)
              if(r->st==NULL && r->dr==NULL)
                      {delete r;
                       r=NULL;
                       }
                 else
                   if(r->st==NULL)
                       {q=r->dr;
                        delete r;
                        r=q;
                        }
                      else
                        if(r->dr==NULL)
                            {q=r->st;
                             delete r;
                             r=q;
                            }
                          else cmmd(r,r->st);
            else if(strcmp(r->nume,autor)>0) stergere(r->st,autor);
                            else             stergere(r->dr,autor);
      else cout<<"nu exista acest autor";
}
*/
void afisare_fur_cu_ing()
{
    int i, j, h; char copie[100];
    for(i=1; i<=nr_fur; i++)
    {   if(fur[i].id!=1000 && fur[i].id%1000==0)//i%1000
        {
            strcpy(copie, fur[i].nume);
            spatii(25); cout << " "; undersc(100); cout << endl;
            spatii(25); cout << "|"; spatii(100); cout << "|" << endl;
            spatii(25); cout << "|  FURNIZOR INTERMEDIAR: " << fara_(strupr(copie)); spatii(100-24-strlen(copie)); cout << "|" << endl;
            spatii(25); cout << "|"; undersc(100); cout << "|" << endl << endl;
            for(j=1; j<=nr_fur; j++)
            {
                if(fur[j].id%1000!=0 && fur[i].id/1000==fur[j].id/1000)
                {
                    strcpy(copie, fur[j].nume);
                    spatii(45); cout << " "; undersc(50); cout << endl;
                    spatii(45); cout << "|"; spatii(50); cout << "|" << endl;
                    spatii(45); cout << "|  " << fara_(strupr(copie)); spatii(50-2-strlen(copie)); cout << "|" << endl;
                    spatii(45); cout << "|"; undersc(50); cout << "|" << endl;
                    spatii(55); cout << "(";
                    for(h=1; h<=nr_ingr; h++)
                    {
                        if(ingr[h].id/100==fur[j].id/100)
                        {   strcpy(copie, ingr[h].nume);
                            cout << fara_(copie) << ", ";
                        }
                    }
                    cout << '\b' << '\b' << ")" << endl;
                }
             }
        }
    }
}

void ascii_art_posturi_si_ang()
{
    cout << R"(
                                                          _____          _              _       _                              _       _   _
                                                         |  __ \        | |            (_)     (_)     /\                     (_)     | | (_)
                                                         | |__) |__  ___| |_ _   _ _ __ _   ___ _     /  \   _ __   __ _  __ _ _  __ _| |_ _
                                                         |  ___/ _ \/ __| __| | | | '__| | / __| |   / /\ \ | '_ \ / _` |/ _` | |/ _` | __| |
                                                         | |  | (_) \__ \ |_| |_| | |  | | \__ \ |  / ____ \| | | | (_| | (_| | | (_| | |_| |
                                                         |_|   \___/|___/\__|\__,_|_|  |_| |___/_| /_/    \_\_| |_|\__, |\__,_| |\__,_|\__|_|
                                                                                                                    __/ |    _/ |
                                                                                                                   |___/    |__/

)"<< endl << endl;
}
void ascii_art_et_de_prod_retete()
{
    cout << R"(
                                                      ______ _                         _        _____               _            _   _
                                                     |  ____| |                       | |      |  __ \             | |          | | (_)
                                                     | |__  | |_ __ _ _ __   ___    __| | ___  | |__) | __ ___   __| |_   _  ___| |_ _  ___
                                                     |  __| | __/ _` | '_ \ / _ \  / _` |/ _ \ |  ___/ '__/ _ \ / _` | | | |/ __| __| |/ _ \
                                                     | |____| || (_| | |_) |  __/ | (_| |  __/ | |   | | | (_) | (_| | |_| | (__| |_| |  __/_
                                                     |______|\__\__,_| .__/ \___|  \__,_|\___| |_|   |_|  \___/ \__,_|\__,_|\___|\__|_|\___( )
                                                                     | |                                                                   |/
                                                                     |_|____      _       _
                                                                      |  __ \    | |     | |
                                                                      | |__) |___| |_ ___| |_ ___
                                                                      |  _  // _ \ __/ _ \ __/ _ \
                                                                      | | \ \  __/ ||  __/ ||  __/_
                                                      ______          |_|  \_\___|\__\___|\__\___( )     _                          _ _            _
                                                     |  ____|              (_)             (_)   |/     (_)                        | (_)          | |
                                                     | |__ _   _ _ __ _ __  _ _______  _ __ _   ______   _ _ __   __ _ _ __ ___  __| |_  ___ _ __ | |_ ___
                                                     |  __| | | | '__| '_ \| |_  / _ \| '__| | |______| | | '_ \ / _` | '__/ _ \/ _` | |/ _ \ '_ \| __/ _ \
                                                     | |  | |_| | |  | | | | |/ / (_) | |  | |          | | | | | (_| | | |  __/ (_| | |  __/ | | | ||  __/
                                                     |_|   \__,_|_|  |_| |_|_/___\___/|_|  |_|          |_|_| |_|\__, |_|  \___|\__,_|_|\___|_| |_|\__\___|
                                                                                                                  __/ |
                                                                                                                 |___/                                     )" << endl;
}

void gestionarea_ang_si_posturilor()//de lucrat la grafica la 4.Concedieri
{
    int x;
    do
    {
        system("CLS");
        cout << endl;
        ascii_art_posturi_si_ang();
        cout << endl << endl;
        spatii(70); cout << " ______________________________________________________ " << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  1.Afisarea ierarhiei posturilor                     |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  2.Afisarea posturilor ocupate                       |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  3.Angajari                                          |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  4.Concedieri                                        |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  5.Crearea unui nou post                             |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  0.Inapoi la pagina principala                       |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl<< endl;
        cout << endl;
        spatii(80); cout << "Alegeti optiunea dorita: "; cin >> x;
        while (x!=1 && x!=2 && x!=3 && x!=4 && x!=5 && x!=0)
        {
            cout << endl;
            spatii(85); cout << "Raspuns invalid!" << endl;
            spatii(80); cout << "Alegeti optiunea dorita: ";
            cin >> x;
        }
        switch (x)
        {
            case 1: //Afisarea ierarhiei posturilor
            {
                system("CLS");
                afisare_arbore_joburi();
            }_getch(); break;
            case 2: //Afisarea posturilor ocupate
            {
                int y;
                do
                {   system("CLS");
                    afisare_arbore_joburi_si_angajati();
                    cout << endl << endl << endl;
                    spatii(60); cout << " _______________________________________________________________________________ " << endl;
                    spatii(60); cout << "|                                                                               |" << endl;
                    spatii(60); cout << "|  1.Afisarea fisei personale a unui angajat                                    |" << endl;
                    spatii(60); cout << "|_______________________________________________________________________________|" << endl;
                    spatii(60); cout << "|                                                                               |" << endl;
                    spatii(60); cout << "|  0.Inapoi la meniul anterior                                                  |" << endl;
                    spatii(60); cout << "|_______________________________________________________________________________|" << endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                    while (y!=1 && y!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> y;
                    }
                    if(y==1)
                    {       char nume[40]; int k, i, s=0; char copie[40];
                            system("CLS");
                            afisare_arbore_joburi_si_angajati();
                            cout << endl << endl;
                            spatii(70); cout << "Introduceti numele de familie al angajatului cautat: " << endl;
                            spatii(80); cin >> nume;
                            k=cautare_poz_ang_dupa_nume(nume);
                            while (k==-1)
                            {
                                cout << endl;
                                spatii(75); cout << "Acest nume nu corespunde niciunui angajat!" << endl;
                                spatii(70); cout << "Introduceti numele de familie al angajatului cautat: " << endl;
                                spatii(80); cin >> nume;
                                k=cautare_poz_ang_dupa_nume(nume);
                            }
                            system ("CLS"); cout << endl << endl;
                            spatii(30); strcpy(copie, ang[k].nume); cout << strupr(copie) << " "; strcpy(copie, ang[k].prenume); cout << strupr(copie) << endl;
                            spatii(35); cout << " __________________________ "; undersc(50); cout << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Departament             |  "; cout << fara_(dep[(ang[k].id)/100].nume); spatii(48-strlen(dep[(ang[k].id)/100].nume)); cout << "|" << endl; cu_(dep[(ang[k].id)/100].nume);
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Functie                 |  "; cout << fara_(job[cautare_poz_job_dupa_id(ang[k].id)].nume); spatii(48-strlen(job[cautare_poz_job_dupa_id(ang[k].id)].nume)); cout << "|" << endl; cu_(job[cautare_poz_job_dupa_id(ang[k].id)].nume);
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Salariu lunar           |  "; cout << job[cautare_poz_job_dupa_id(ang[k].id)].salariu << " lei"; spatii(48-nrc(job[cautare_poz_job_dupa_id(ang[k].id)].salariu)-4); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Nr.zile lucratoare/sapt |  "; cout << job[cautare_poz_job_dupa_id(ang[k].id)].zilelucr; spatii(48-nrc(job[cautare_poz_job_dupa_id(ang[k].id)].zilelucr)); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Nr.ore de lucru/zi      |  "; cout << job[cautare_poz_job_dupa_id(ang[k].id)].orepezi; spatii(48-nrc(job[cautare_poz_job_dupa_id(ang[k].id)].orepezi)); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Data nasterii           |  "; cout << fara_(ang[k].data_nasterii); spatii(48-strlen(ang[k].data_nasterii)); cout << "|" << endl; cu_(ang[k].data_nasterii);
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Numar de telefon        |  "; cout << ang[k].nrtel; spatii(38); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Email                   |  "; cout << ang[k].email; spatii(48-strlen(ang[k].email)); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Adresa                  |  "; cout << fara_(ang[k].adresa); spatii(48-strlen(ang[k].adresa)); cout << "|" << endl; cu_(ang[k].adresa);
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Ani de experienta       |  "; cout << ang[k].ani_experienta; spatii(48-nrc(ang[k].ani_experienta)); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            spatii(35); cout << "|                          |"; spatii(50); cout << "|" << endl;
                            spatii(35); cout << "|  Limbi vorbite           |  ";
                            for (i=1; i<=ang[k].nr_limbi; i++)
                            {
                                cout << ang[k].limbi[i];
                                if (i!=ang[k].nr_limbi)
                                {
                                    cout << ", ";
                                    s+=2;
                                }
                                s+=strlen(ang[k].limbi[i]);
                            }
                            spatii(48-s); cout << "|" << endl;
                            spatii(35); cout << "|__________________________|"; undersc(50); cout << "|" << endl;
                            cout << endl;
                            _getch();
                    }
                }while(y);
            } break;
            case 3: //Angajari
            {
                int y;
                do
                {
                    system("CLS");
                    cout << endl << endl << endl;
                    spatii(70); cout << " ______________________________________________________ " << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  1.Afisarea CV-urilor depuse                         |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  2.Selectarea unui candidat                          |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                    while (y!=1 && y!=2 && y!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> y;
                    }
                    switch(y)
                    {
                        case 1: //Afisarea CV-urilor depuse
                        {
                            int i, k, s; char copie[40];
                            system ("CLS");
                            for (k=1; k<=nr_cv_ang; k++)
                            {
                                cout << endl << endl;
                                spatii(20); strcpy(copie, CV[k].nume); cout << strupr(copie) << " "; strcpy(copie, CV[k].prenume); cout << strupr(copie) << endl;
                                spatii(25); cout << " __________________________ "; undersc(150); cout << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Departament dorit       |  "; cout << fara_(CV[k].dep_dorit); spatii(148-strlen(CV[k].dep_dorit)); cout << "|" << endl; cu_(CV[k].dep_dorit);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Functie dorita          |  "; cout << fara_(CV[k].job_dorit); spatii(148-strlen(CV[k].job_dorit)); cout << "|" << endl; cu_(CV[k].job_dorit);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Data nasterii           |  "; cout << fara_(CV[k].data_nasterii); spatii(148-strlen(CV[k].data_nasterii)); cout << "|" << endl; cu_(CV[k].data_nasterii);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Numar de telefon        |  "; cout << CV[k].nrtel; spatii(138); cout << "|" << endl;
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Email                   |  "; cout << CV[k].email; spatii(148-strlen(CV[k].email)); cout << "|" << endl;
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Ani de experienta       |  "; cout << CV[k].ani_experienta; spatii(148-nrc(CV[k].ani_experienta)); cout << "|" << endl;
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Limbi vorbite           |  ";
                                s=0;
                                for (i=1; i<=CV[k].nr_limbi; i++)
                                {
                                    cout << CV[k].limbi[i];
                                    if (i!=CV[k].nr_limbi)
                                    {
                                        cout << ", ";
                                        s+=2;
                                    }
                                    s+=strlen(CV[k].limbi[i]);
                                }
                                spatii(148-s); cout << "|" << endl;
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Scrisoare de intentie   |  "; cout << fara_(CV[k].intentie); spatii(148-strlen(CV[k].intentie)); cout << "|" << endl; cu_(CV[k].intentie);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Studii in domeniu       |  "; cout << fara_(CV[k].studii); spatii(148-strlen(CV[k].studii)); cout << "|" << endl; cu_(CV[k].studii);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Nota interviu           |  "; cout << CV[k].nota; spatii(148-nrc(CV[k].nota)); cout << "|" << endl;
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                spatii(25); cout << "|                          |"; spatii(150); cout << "|" << endl;
                                spatii(25); cout << "|  Observatii interviu     |  "; cout << fara_(CV[k].obs[1]) << ", " << fara_(CV[k].obs[2]); spatii(148-strlen(CV[k].obs[1])-strlen(CV[k].obs[2])-2); cout << "|" << endl; cu_(CV[k].obs[1]); cu_(CV[k].obs[2]);
                                spatii(25); cout << "|__________________________|"; undersc(150); cout << "|" << endl;
                                cout << endl;
                            }
                        }_getch();break;
                        case 2: //Selectarea unui candidat
                        {
                            char nume[40], zero[2]="0", da_nu[10], copie[100]; int i, j, ok, okk=1, k=-1, id_job_dorit;
                            cout << endl << endl;
                            spatii(61); undersc(81); cout << endl;
                            for(i=1; i<=nr_cv_ang; i++)
                            {   strcpy(copie, CV[i].job_dorit);
                                spatii(60); cout << "|"; spatii(40); cout << "|"; spatii(40); cout << "|" << endl;
                                spatii(60); cout << "|  "; cout << CV[i].nume; spatii(40-2-strlen(CV[i].nume)); cout << "|  "; cout << fara_(copie); spatii(40-2-strlen(copie)); cout << "|" << endl;
                                spatii(60); cout << "|"; undersc(40); cout << "|"; undersc(40); cout << "|"; cout << endl;
                            }
                            cout << endl << endl;
                            spatii(60); cout << "Introduceti numele de familie al candidatului pe care doriti sa-l angajati: ";
                            cin >> nume;
                            for (i=1; i<=nr_cv_ang; i++)
                            {
                                if (strcmp(nume, CV[i].nume)==0)
                                    k=i;
                            }
                            while (k==-1)
                            {
                                cout << endl;
                                spatii(80); cout << "Nu exista acest nume in lista candidatilor!" << endl;
                                spatii(45); cout << "Introduceti numele de familie al candidatului pe care doriti sa-l angajati sau tastati 0 pentru a va intoarce la meniu: ";
                                cin >> nume;
                                if (strcmp(nume, zero)==0)
                                {
                                    okk=0;
                                    break;
                                }
                                for (i=1; i<=nr_cv_ang; i++)
                                    if (strcmp(nume, CV[i].nume)==0)
                                        k=i;
                            }
                            if (okk==1)
                            {   id_job_dorit = cautare_id_job_dupa_job_dorit_CV(CV[k].job_dorit);
                                if (id_job_dorit == -1) //daca nu exista jobul respectiv
                                {   cout << endl << endl;
                                    spatii(60); cout << "Postul pentru care candidatul a aplicat (" << fara_(CV[k].job_dorit) << ") nu exista in cadrul afacerii!" << endl;
                                    spatii(65); cout << " _______________________________________________________________________________ " << endl;
                                    spatii(65); cout << "|                                                                               |" << endl;
                                    spatii(65); cout << "|  Doriti sa eliminati CV-ul candidatului din lista CV-urilor depuse? (Da/Nu)   |" << endl;
                                    spatii(65); cout << "|_______________________________________________________________________________|" << endl;
                                    spatii(100); cin >> da_nu;
                                    if (strcmp(da_nu, "Da")==0 || strcmp(da_nu, "da")==0 || strcmp(da_nu, "DA")==0)
                                    {   if (k==nr_cv_ang)
                                            nr_cv_ang--;
                                        else
                                           stergerea_unui_CV(k);

                                        ofstream file("CV_angajari.txt", ios::trunc);
                                        if (file.is_open())
                                        {
                                            file.close();
                                            file.open("CV_angajari.txt", ios::app);
                                            if(file.is_open())
                                            {
                                                for(i=1; i<=nr_cv_ang; i++)
                                                {   file << CV[i].cod << " " << CV[i].nume << " " << CV[i].prenume << " " << CV[i].data_nasterii << " "
                                                         << CV[i].adresa << " " << CV[i].nrtel << " " << CV[i].email << " " << CV[i].ani_experienta<< " "
                                                         << CV[i].dep_dorit << " " << CV[i].job_dorit << " " << CV[i].nr_limbi<< " ";

                                                    for(j=1; j<=CV[i].nr_limbi; j++)
                                                        file << CV[i].limbi[j] << " ";
                                                    file << CV[i].intentie << " " << CV[i].studii << " " << CV[i].nota << " " << CV[i].obs[1] << " " << CV[i].obs[2];
                                                    file << endl;
                                                }
                                                file.close();
                                            }
                                        }
                                    }
                                }
                                else //daca exista jobul respectiv
                                {   ok=0; //presupunem ca jobul este liber
                                    for (i=1; i<=nr_ang && ok==0; i++)
                                        if (id_job_dorit==ang[i].id) //daca jobul este ocupat
                                        {   cout << endl;
                                            spatii(65); cout << "Postul de <" << fara_(job[cautare_poz_job_dupa_id(ang[i].id)].nume) << "> este deja ocupat de " << ang[i].nume << " " << ang[i].prenume << ".";
                                            ok=1;
                                            cu_(job[cautare_poz_job_dupa_id(ang[i].id)].nume);
                                            _getch();
                                        }
                                    if (ok==0) //daca jobul este liber
                                    {
                                        cout << endl;
                                        spatii(80); cout << "Postul este disponibil!" << endl;
                                        spatii(65); cout << "Doriti sa il/o angajati pe " << CV[k].nume  << " " << CV[k].prenume << " pe postul de <" << CV[k].job_dorit << ">? (Da/Nu)" << endl;
                                        spatii(90); cin >> da_nu;
                                        if (strcmp(da_nu, "Da")==0 || strcmp(da_nu, "da")==0 || strcmp(da_nu, "DA")==0)
                                        {   //ADAUGAREA datelor in fisierul de ANGAJATI
                                            ofstream an("angajati.txt", ios::app);
                                            if (an.is_open())
                                            {
                                                an << id_job_dorit << " " << CV[k].nume << " " << CV[k].prenume << " " << CV[k].data_nasterii << " "
                                                   << CV[k].adresa << " " << CV[k].nrtel << " " << CV[k].email << " " << CV[k].ani_experienta << " "
                                                   << CV[k].nr_limbi << " ";
                                                for(i=1; i<=CV[k].nr_limbi; i++)
                                                    an << CV[k].limbi[i] << " ";
                                                an << endl;
                                                an.close();
                                            }
                                            //STERGEREA datelor din fisierul de CV-URI
                                            if (k==nr_cv_ang)
                                                nr_cv_ang--;
                                            else
                                               stergerea_unui_CV(k);

                                            ofstream ann("CV_angajari.txt", ios::trunc);
                                            if (ann.is_open())
                                            {
                                                ann.close();
                                                ann.open("CV_angajari.txt", ios::app);
                                                if(ann.is_open())
                                                {
                                                    for(i=1; i<=nr_cv_ang; i++)
                                                    {   ann << CV[i].cod << " " << CV[i].nume << " " << CV[i].prenume << " " << CV[i].data_nasterii << " "
                                                             << CV[i].adresa << " " << CV[i].nrtel << " " << CV[i].email << " " << CV[i].ani_experienta<< " "
                                                             << CV[i].dep_dorit << " " << CV[i].job_dorit << " " << CV[i].nr_limbi<< " ";

                                                        for(j=1; j<=CV[i].nr_limbi; j++)
                                                            ann << CV[i].limbi[j] << " ";
                                                        ann << CV[i].intentie << " " << CV[i].studii << " " << CV[i].nota << " " << CV[i].obs[1] << " " << CV[i].obs[2];
                                                        ann << endl;
                                                    }
                                                    ann.close();
                                                }
                                            }
                                        }
                                    }
                                }
                                citire_angajati(); citire_CV_angajari();
                            }
                        }break;
                    }
                }while(y);
            }break;
            case 4: //Concedieri
            {
                int y;
                do
                {
                    system("CLS");
                    afisare_arbore_joburi_si_angajati();
                    cout << endl << endl << endl;
                    spatii(60); cout << " _______________________________________________________________________________ " << endl;
                    spatii(60); cout << "|                                                                               |" << endl;
                    spatii(60); cout << "|  1.Selectarea angajatului dorit                                               |" << endl;
                    spatii(60); cout << "|_______________________________________________________________________________|" << endl;
                    spatii(60); cout << "|                                                                               |" << endl;
                    spatii(60); cout << "|  0.Inapoi la meniul anterior                                                  |" << endl;
                    spatii(60); cout << "|_______________________________________________________________________________|" << endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                    while (y!=1 && y!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> y;
                    }
                    if(y==1)
                    {       char nume[40]; int k, i;
                            system("CLS");
                            afisare_arbore_joburi_si_angajati();
                            cout << endl << endl;
                            spatii(65); cout << "Introduceti numele de familie al angajatului pe care doriti sa-l concediati: " << endl;
                            spatii(80); cin >> nume;
                            k=cautare_poz_ang_dupa_nume(nume);
                            while (k==-1)
                            {
                                cout << endl;
                                spatii(75); cout << "Acest nume nu corespunde niciunui angajat!" << endl;
                                spatii(70); cout << "Introduceti numele de familie al angajatului cautat: " << endl;
                                spatii(80); cin >> nume;
                                k=cautare_poz_ang_dupa_nume(nume);
                            }
                            stergerea_unui_ang(k);
                            ofstream annn("angajati.txt", ios::trunc);
                            if (annn.is_open())
                            {   int j;
                                annn.close();
                                annn.open("angajati.txt", ios::app);
                                if(annn.is_open())
                                {
                                    for(i=1; i<=nr_ang; i++)
                                    {   annn << ang[i].id << " " << ang[i].nume << " " << ang[i].prenume << " " << ang[i].data_nasterii << " "
                                            << ang[i].adresa << " " << ang[i].nrtel << " " << ang[i].email << " " << ang[i].ani_experienta<< " "
                                            << ang[i].nr_limbi<< " ";
                                        for(j=1; j<=ang[i].nr_limbi; j++)
                                            annn << ang[i].limbi[j] << " ";
                                        annn << endl;
                                    }
                                    annn.close();
                                }
                            }
                    }
                }while(y);
            }_getch(); break;
            case 5: //Crearea unui nou post ---probleme la relatiile cu clientii!!!-REZOLVAT
            {
                char depar[40], post[40], sup[40], da_nu[10];
                int zile, ore, bani, i, j, z, ok, okk=1;
                system("CLS");
                afisare_arbore_joburi(); cout << endl;
                cin.get();
                chestionar_creare_job(depar, post, sup, zile, ore, bani);
                spatii(60); cout << "Continuati cu datele introduse? (Da/Nu)"; cin >> da_nu;

                //daca a zis nu
                while (strcmp(da_nu, "Nu")==0 || strcmp(da_nu, "NU")==0 || strcmp(da_nu, "nu")==0)
                {
                        cout << endl;
                        spatii(70); cout << " ______________________________________________________" << endl;
                        spatii(70); cout << "|                                                      |" << endl;
                        spatii(70); cout << "|  1.Repetarea procesului                              |" << endl;
                        spatii(70); cout << "|______________________________________________________|" << endl;
                        spatii(70); cout << "|                                                      |" << endl;
                        spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                        spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                        spatii(80); cout << "Alegeti optiunea dorita: "; cin >> z;
                        while (z!=1 && z!=0)
                        {
                            cout << endl;
                            spatii(85); cout << "Raspuns invalid!" << endl;
                            spatii(80); cout << "Alegeti optiunea dorita: ";
                            cin >> z;
                        }
                        if (z==0)
                        {
                            break;
                            okk=0;
                        }
                        else
                        {
                            system("CLS");
                            afisare_arbore_joburi(); cout << endl;
                            cin.get();
                            chestionar_creare_job(depar, post, sup, zile, ore, bani);
                            spatii(60); cout << "Continuati cu datele introduse? (Da/Nu) "; cin >> da_nu;
                        }
                }
                //daca a zis da
                if (okk==1)
                {
                    ok=1;
                    cu_(depar);
                    for (i=cautare_nr_dep_dupa_nume(depar)*100; i<=cautare_nr_dep_dupa_nume(depar)*100+99 && ok==1; i++)
                    {   ok=0;
                        for (j=1; j<=nr_j; j++)
                            if (i==job[j].id)
                                ok=1;
                    }
                    fara_(depar);
                    job[nr_j+1].id = i-1;
                    strcpy(job[nr_j+1].nume, cu_(post));
                    fara_(post);
                    job[nr_j+1].id_superior = cautare_id_job_dupa_nume(cu_(sup));
                    fara_(sup);
                    job[nr_j+1].orepezi = ore;
                    job[nr_j+1].zilelucr = zile;
                    job[nr_j+1].salariu = bani;
                    nr_j++;

                    ofstream jo("joburi.txt", ios::app);
                    if (jo.is_open())
                    {
                        jo << job[nr_j].id << " " << job[nr_j].nume << " " << job[nr_j].id_superior << " "
                           << job[nr_j].zilelucr << " " << job[nr_j].orepezi << " " << job[nr_j].salariu << endl;
                        jo.close();
                    }
                    citire_joburi();
                    creare_arbore_joburi();
                    //for (i=1; i<=1000; i++)
                    //    if (vtati_j[i]!=-1)
                    //        cout << i << " " << vtati_j[i] << endl;

                    cout << endl << endl;
                    spatii(80); cout << "Inserare realizata cu succes!" << endl;
                    spatii(65); cout << "Puteti vizualiza modificarile in meniul de afisare a ierarhiei posturilor." << endl;

                }
            }_getch(); break;
        }
    }while(x);
}


void gestionarea_et_de_productie_si_retetelor()//de lucrat la 1.Gestionarea etapelor de productie - Afisare
{
    int x;
    do
    {   system("CLS");
        cout << endl;
        ascii_art_et_de_prod_retete();
        cout << endl << endl;
        spatii(70); cout << " ______________________________________________________ " << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  1.Gestionarea etapelor de productie                 |" << endl; //de lucrat la grafica putin
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  2.Gestionarea retetelor                             |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  3.Relatii furnziori-ingrediente                     |" << endl; //facut-eventual de adaugat alte cazuri
        spatii(70); cout << "|______________________________________________________|" << endl;
        spatii(70); cout << "|                                                      |" << endl;
        spatii(70); cout << "|  0.Inapoi la pagina principala                       |" << endl;
        spatii(70); cout << "|______________________________________________________|" << endl<< endl;
        cout << endl;
        spatii(80); cout << "Alegeti optiunea dorita: "; cin >> x;
        while (x!=1 && x!=2 && x!=3 && x!=4 && x!=5 && x!=6 && x!=7 && x!=0)
        {
            cout << endl;
            spatii(85); cout << "Raspuns invalid!" << endl;
            spatii(80); cout << "Alegeti optiunea dorita: ";
            cin >> x;
        }
        switch (x)
        {
            case 1: //Gestionarea etapelor de productie
            {
                int y;
                do
                {   system("CLS");
                    cout << endl << endl << endl;
                    spatii(70); cout << " ______________________________________________________ " << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  1.Afisarea etapelor de productie                    |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  2.Inserarea unei etape de productie                 |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  3.Eliminarea unei etape de productie                |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                    while (y!=1 && y!=2 && y!=3 && y!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> y;
                    }
                    switch(y)
                    {
                        case 1: //Afisarea etapelor de productie - probleme!!!
                        {
                            afisare_arbore_et_de_prod();
                        }_getch();break;

                        case 2: //Inserarea unei etape de productie
                        {
                            int i, j, it=-1, poz, ok, tmp; char tip[40], pre[100], num[100], copie[100];
                            system("CLS");
                            afisare_arbore_et_de_prod();
                            //cout << endl<< endl;
                            spatii(65); cout << "In care dintre procesele de productie doriti sa inserati o etapa? (";
                            for (i=1; i<=nr_tip_ret; i++)
                            {
                                cout << fara_(tipp[i].nume);
                                cu_(tipp[i].nume);
                                if (i!=nr_tip_ret)
                                    cout << "/";
                            }
                            cout << ") "; cin.get(); cin.getline(tip, 40);
                            for (i=1; i<=nr_tip_ret; i++)
                            {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                    it=i;
                                cu_(tipp[i].nume);
                            }
                            while (it==-1)
                            {
                                cout << endl<< endl;
                                spatii(65); cout << "Acest tip de produs nu exista!" << endl;
                                spatii(65); cout << "In care dintre procesele de productie doriti sa inserati o etapa? (";
                                for (i=1; i<=nr_tip_ret; i++)
                                {
                                    cout << fara_(tipp[i].nume);
                                    cu_(tipp[i].nume);
                                    if (i!=nr_tip_ret)
                                        cout << "/";
                                }
                                cout << ") "; cin.getline(tip, 40);
                                for (i=1; i<=nr_tip_ret; i++)
                                {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                       it=i;
                                    cu_(tipp[i].nume);
                                }
                            }
                            cout << endl;
                            spatii(65); cout << "Precizati etapa precedenta etapei pe care doriti sa o inserati: ";
                            cin.getline(pre, 100);
                            poz=-1;
                            if (strcmp(pre, fara_(et[1].nume))==0)
                               poz=1;
                            else
                                for (i=2; i<=nr_et_de_prod; i++)
                                    if((et[i].cod/100)==it)
                                    {   if(strcmp(fara_(et[i].nume), pre)==0)
                                           poz=i;
                                        cu_(et[i].nume);
                                    }
                            cu_(et[1].nume);
                            while(poz==-1)
                            {   cout << endl << endl;
                                spatii(65); cout << "Aceasta etapa de productie nu exista in categoria <" << tipp[it].nume << ">!" << endl;
                                spatii(65); cout << "Precizati etapa precedenta etapei pe care doriti sa o inserati: ";
                                cin.getline(pre, 100);
                                if (strcmp(pre, fara_(et[1].nume))==0)
                                   poz=1;
                                else
                                    for (i=2; i<=nr_et_de_prod; i++)
                                        if(et[i].cod/100==it)
                                        {   if(strcmp(fara_(et[i].nume), pre)==0)
                                               poz=i;
                                            cu_(et[i].nume);
                                        }
                                cu_(et[1].nume);
                            }

                            spatii(65); cout << "Numele etapei pe care doriti sa o inserati: "; cin.getline(num, 100);
                            strcpy(copie, num);
                            /*ok=1; //tip[it].nume (tort, prajitura) //et[poz].cod -->codul etapei anterioare
                            for (i=tipp[it].nr*100+1; i<=tipp[it].nr*100+99 && ok==1; i++)
                            {   ok=0;
                                for (j=1; j<=nr_et_de_prod; j++)
                                    if (i==et[j].cod)
                                        ok=1;
                            }*/
                            nr_et_de_prod++;
                            for(i=nr_et_de_prod; i>poz+1; i--)
                            {
                                et[i].cod=et[i-1].cod;
                                et[i].cod_sup=et[i-1].cod_sup;
                                strcpy(et[i].nume, et[i-1].nume);
                                if(et[i].cod/100==it)
                                {
                                    et[i].cod++;
                                    et[i].cod_sup++;
                                }
                            }
                            et[poz+1].cod=et[poz].cod+1;
                            strcpy(et[poz+1].nume, cu_(copie));
                            et[poz+1].cod_sup=et[poz].cod;
                            /*et[nr_et_de_prod+1].cod=et[poz+1].cod;
                            strcpy(et[nr_et_de_prod+1].nume, cu_(copie));
                            et[nr_et_de_prod+1].cod_sup = et[poz].cod;
                            nr_et_de_prod++;
                            for (i=poz+1; i<=nr_et_de_prod && (et[poz].cod/100)==(et[i].cod/100); i++)
                            {
                                et[i].cod++;
                                et[i].cod_sup++;
                            }*/

                            ofstream epp("etape_de_productie.txt", ios::trunc);
                            if (epp.is_open())
                            {
                                epp.close();
                                epp.open("etape_de_productie.txt", ios::app);
                                if(epp.is_open())
                                {
                                    for(i=1; i<=nr_et_de_prod; i++)
                                       epp << et[i].cod << " " << et[i].nume << " " << et[i].cod_sup << endl;
                                    epp.close();
                                }
                            }

                            citire_etape_de_prod();
                            creare_arbore_et_de_prod();
                            //for (i=1; i<=1000; i++)
                            //    if (vtati_j[i]!=-1)
                            //        cout << i << " " << vtati_j[i] << endl;

                            cout << endl << endl;
                            spatii(80); cout << "Inserare realizata cu succes!" << endl;
                            spatii(65); cout << "Puteti vizualiza modificarile in meniul de afisare a etapelor de productie." << endl << endl;
                            //cout <<it<<" "<< tipp[it].nr_et << endl; _getch();
                            tipp[it].nr_et++;

                            spatii(65); cout << "Adaugati timpul necesar etapei introduse (" << fara_(copie) << ") pentru fiecare reteta:" << endl << endl;
                            spatii(70); cout << " "; undersc(52); cout << endl;
                            for(i=1; i<=nr_ret; i++)
                            {   //cout << tipp[it].nume << " " << ret[i].tip << endl;
                                if (strcmp(tipp[it].nume, ret[i].tip)==0)
                                {   strcpy(copie, ret[i].nume);
                                    spatii(70); cout << "|"; spatii(52); cout << "|" << endl;
                                    spatii(70); cout << "|  " << fara_(copie); spatii(50-strlen(ret[i].nume)); cout << "|  Timpul necesar (in minute): "; cin >> tmp;
                                    spatii(70); cout << "|"; undersc(52); cout << "|" << endl;
                                    //cout << "nr de et: " << tipp[it].nr_et << "; poz: " << poz;
                                    for(j=tipp[it].nr_et; j>et[poz+1].cod%100; j--)
                                        ret[i].timpdeprep[j]=ret[i].timpdeprep[j-1];
                                    //cout << et[poz].cod%100 << " " << et[poz+1].cod%100 << endl; _getch();
                                    ret[i].timpdeprep[et[poz+1].cod%100]=tmp;
                                }
                            }

                            ofstream rett("retete.txt", ios::trunc);
                            if (rett.is_open())
                            {
                                rett.close();
                                rett.open("retete.txt", ios::app);
                                if(rett.is_open())
                                {
                                    for(i=1; i<=nr_ret; i++)
                                    {
                                        rett<<ret[i].cod<<" "<<ret[i].tip<<" "<<ret[i].nume<<" "<<ret[i].nr_ingred<<" ";
                                        for (j=1; j<=ret[i].nr_ingred; j++)
                                            rett<<ret[i].nume_ing[j]<<" "<<ret[i].gramaj_ing[j]<<" "<<ret[i].unit_ing[j]<<" ";
                                        for(j=1; j<=tipp[cautare_poz_tipp_dupa_nume_tip(ret[i].tip)].nr_et; j++)
                                            rett<<ret[i].timpdeprep[j]<<" ";
                                        rett<<endl;
                                    }
                                    rett.close();
                                }
                            }
                            citire_retete();
                            ofstream tippprod("tip_produse.txt", ios::trunc);
                            if (tippprod.is_open())
                            {
                                tippprod.close();
                                tippprod.open("tip_produse.txt", ios::app);
                                if(tippprod.is_open())
                                {
                                    for(i=1; i<=nr_tip_ret; i++)
                                        tippprod<<tipp[i].nr<<" "<<tipp[i].nume<<" "<<tipp[i].nr_et<<endl;
                                    tippprod.close();
                                }
                            }
                            citire_tip_produse();
                        }_getch();break;

                        case 3: //Eliminarea unei etape de productie
                        {
                            char nume[100], tip[40]; int i, j, poz=-1, it=-1;
                            system("CLS");
                            afisare_arbore_et_de_prod();
                            cout << endl;
                            spatii(65); cout << "Precizati din care dintre procesele de productie doriti sa eliminati o etapa (";
                            for (i=1; i<=nr_tip_ret; i++)
                                {
                                    cout << fara_(tipp[i].nume);
                                    cu_(tipp[i].nume);
                                    if (i!=nr_tip_ret)
                                        cout << "/";
                                }
                            cout << ") "; cin.get(); cin.getline(tip, 40);
                            for (i=1; i<=nr_tip_ret; i++)
                            {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                    it=i;
                                cu_(tipp[i].nume);
                            }
                            while (it==-1)
                            {
                                cout << endl<< endl;
                                spatii(65); cout << "Acest tip de produs nu exista!" << endl;
                                spatii(65); cout << "Precizati din care dintre procesele de productie doriti sa eliminati o etapa (";
                                for (i=1; i<=nr_tip_ret; i++)
                                    {
                                        cout << fara_(tipp[i].nume);
                                        cu_(tipp[i].nume);
                                        if (i!=nr_tip_ret)
                                            cout << "/";
                                    }
                                cout << ") "; cin.getline(tip, 40);
                                for (i=1; i<=nr_tip_ret; i++)
                                {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                       it=i;
                                    cu_(tipp[i].nume);
                                }
                            }
                            cout << endl;//avem pozitia tipului de produs corect(it) -tort/prajituta/etc
                            spatii(65); cout << "Introduceti numele etapei pe care doriti sa-o eliminati: ";
                            cin.getline(nume, 100);
                            if (strcmp(nume, fara_(et[1].nume))==0)
                               poz=1;
                            else
                                for (i=2; i<=nr_et_de_prod; i++)
                                    if((et[i].cod/100)==it)
                                    {   if(strcmp(fara_(et[i].nume), nume)==0)
                                           poz=i;
                                        cu_(et[i].nume);
                                    }
                            cu_(et[1].nume);
                            while(poz==-1)
                            {   cout << endl << endl;
                                spatii(65); cout << "Aceasta etapa de productie nu exista in categoria <" << tipp[it].nume << ">!" << endl;
                                spatii(65); cout << "Introduceti numele etapei pe care doriti sa-o eliminati: ";
                                cin.getline(nume, 100);
                                if (strcmp(nume, fara_(et[1].nume))==0)
                                   poz=1;
                                else
                                    for (i=2; i<=nr_et_de_prod; i++)
                                        if(et[i].cod/100==it)
                                        {   if(strcmp(fara_(et[i].nume), nume)==0)
                                               poz=i;
                                            cu_(et[i].nume);
                                        }
                                cu_(et[1].nume);
                            }
                            //poz = pozitia etapei pe care vrem sa o eliminam

                            stergerea_unei_etape(poz);

                            ofstream ettt("etape_de_productie.txt", ios::trunc);
                            if (ettt.is_open())
                            {
                                ettt.close();
                                ettt.open("etape_de_productie.txt", ios::app);
                                if(ettt.is_open())
                                {
                                    for(i=1; i<=nr_et_de_prod; i++)
                                       ettt << et[i].cod << " " << et[i].nume << " " << et[i].cod_sup << endl;
                                    ettt.close();
                                }
                            }
                            citire_etape_de_prod();
                            creare_arbore_et_de_prod();

                            for(i=1; i<=nr_ret && strcmp(tipp[it].nume, ret[i].tip)==0; i++)
                            {
                                for(j=et[poz].cod%100; j<tipp[it].nr_et; j++)
                                    ret[i].timpdeprep[j]=ret[i].timpdeprep[j+1];
                            }
                            tipp[it].nr_et--;
                            ofstream tippp("tip_produse.txt", ios::trunc);
                            if (tippp.is_open())
                            {
                                tippp.close();
                                tippp.open("tip_produse.txt", ios::app);
                                if(tippp.is_open())
                                {
                                    for(i=1; i<=nr_tip_ret; i++)
                                       tippp << tipp[i].nr << " " << tipp[i].nume << " " << tipp[i].nr_et << endl;
                                    tippp.close();
                                }
                            }
                            citire_tip_produse();

                            ofstream rettt("retete.txt", ios::trunc);
                            if (rettt.is_open())
                            {
                                rettt.close();
                                rettt.open("retete.txt", ios::app);
                                if(rettt.is_open())
                                {
                                    for(i=1; i<=nr_ret; i++)
                                    {
                                        rettt<<ret[i].cod<<" "<<ret[i].tip<<" "<<ret[i].nume<<" "<<ret[i].nr_ingred<<" ";
                                        for (j=1; j<=ret[i].nr_ingred; j++)
                                            rettt<<ret[i].nume_ing[j]<<" "<<ret[i].gramaj_ing[j]<<" "<<ret[i].unit_ing[j]<<" ";
                                        for(j=1; j<=tipp[cautare_poz_tipp_dupa_nume_tip(ret[i].tip)].nr_et; j++)
                                            rettt<<ret[i].timpdeprep[j]<<" ";
                                        rettt<<endl;
                                    }
                                    rettt.close();
                                }
                            }
                            citire_retete();
                        }_getch();break;
                    }
                }while(y);
            }break;
            case 2: //Gestionarea retetelor
            {
                int y;
                do
                {   system("CLS");
                    cout << endl << endl << endl;
                    spatii(70); cout << " ______________________________________________________ " << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  1.Afisarea retetelor alfabetic, dupa tip            |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  2.Adaugarea unei retete                             |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl;
                    spatii(70); cout << "|                                                      |" << endl;
                    spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                    spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                    while (y!=1 && y!=2 && y!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> y;
                    }
                    switch(y)
                    {
                        case 1: //Afisarea retetelor
                        {
                            char tip[40], copie[100]; int i, it=-1, ii, j, z;
                            spatii(65); cout << "Precizati tipul de produs pentru care doriti sa se afiseze retetele (";
                            for (i=1; i<=nr_tip_ret; i++)
                            {
                                cout << fara_(tipp[i].nume);
                                cu_(tipp[i].nume);
                                if (i!=nr_tip_ret)
                                    cout << "/";
                            }
                            cout << ") " << endl; cin.get();
                            spatii(80);cin.getline(tip, 40);
                            for (i=1; i<=nr_tip_ret; i++)
                            {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                    it=i;
                                cu_(tipp[i].nume);
                            }
                            while (it==-1)
                            {
                                cout << endl<< endl;
                                spatii(65); cout << "Acest tip de produs nu exista!" << endl;
                                spatii(65); cout << "Precizati tipul de produs pentru care doriti sa se afiseze retetele (";
                                for (i=1; i<=nr_tip_ret; i++)
                                {
                                    cout << fara_(tipp[i].nume);
                                    cu_(tipp[i].nume);
                                    if (i!=nr_tip_ret)
                                        cout << "/";
                                }
                                cout << ") " << endl;
                                spatii(80); cin.getline(tip, 40);
                                for (i=1; i<=nr_tip_ret; i++)
                                {   if (strcmp(tip, fara_(tipp[i].nume))==0)
                                       it=i;
                                    cu_(tipp[i].nume);
                                }
                            }
                                //it=pozitia tipului de produs ales (tort/prajitura/etc)
                                citire_retete_in_copie();
                                sort_alf_cret();
                                for(i=1; i<=nr_cret; i++)
                                {
                                    if(strcmp(cret[i].tip,tipp[it].nume)==0)
                                    {
                                        strcpy(copie, cret[i].nume);
                                        spatii(25); cout << " "; undersc(50); cout << endl;
                                        spatii(25); cout << "|"; spatii(50); cout << "|" << endl;
                                        spatii(25); cout << "|  NUMELE RETETEI: " << fara_(strupr(copie)); spatii(50-18-strlen(copie)); cout << "|" << endl; //19
                                        spatii(25); cout << "|"; undersc(50); cout << "|" << endl;
                                        cout << endl;
                                        spatii(55); cout << "INGREDIENTE:" << endl;
                                        spatii(65); cout << " "; undersc(56); cout << endl;
                                        for(j=1; j<=cret[i].nr_ingred; j++)
                                        {   strcpy(copie, cret[i].nume_ing[j]);
                                            spatii(65); cout << "|   " << fara_(copie); spatii(40-strlen(cret[i].nume_ing[j])-3); cout << "|   "; cout << cret[i].gramaj_ing[j] << " " << cret[i].unit_ing[j]; spatii(15-nrc(cret[i].gramaj_ing[j])-strlen(cret[i].unit_ing[j])-4); cout << "|" << endl;
                                            spatii(65); cout << "|"; undersc(40); cout << "|"; undersc(15); cout << "|" << endl;
                                        }
                                        cout << endl;
                                        spatii(55); cout << "TIMPI DE PREPARARE:" << endl;
                                        spatii(65); cout << " "; undersc(56); cout << endl;
                                        ii=0;
                                        for(j=1; j<=nr_et_de_prod; j++)
                                        {
                                            if (et[j].cod/100==tipp[it].nr)
                                            {   ii++;
                                                strcpy(copie, et[j].nume);
                                                spatii(65); cout << "|   " << fara_(copie); spatii(40-strlen(copie)-3); cout << "|   "; cout << cret[i].timpdeprep[ii] << " min"; spatii(15-nrc(cret[i].timpdeprep[ii])-7); cout << "|" << endl;
                                                spatii(65); cout << "|"; undersc(40); cout << "|"; undersc(15); cout << "|" << endl;
                                            }
                                        }
                                        cout << endl << endl;
                                    }
                                }
                            cout << endl;
                        }_getch();break;

                        case 2: //Adaugarea unei retete
                        {                              //se adauga reteta la final
                            int i, j, it, ifu, k=-1, okk=1, z, cod, nr_ingred, nr_ing_inex, timpdeprep[50], vcaract[1000]={0};
                            float gramaj_ing[30];
                            char tip[40], nume[40], nume_ing[30][40], unit_ing[30][10], copie[100], copie2[100], da_nu[10], ing_inex[100][40], unit_ing_inex[30][10], furni[100];
                            cout << endl;
                            spatii(20); cout << "INGREDIENTELE/ECHIPAMENTELE DISPONIBILE MOMENTAN DE LA FURNIZORII PARTENERI:" << endl << endl;
                            citire_caut_bin_ingr_alfabetic();
                            afisare_caut_bin_ingr(r);
                            cout << endl;
                            chestionar_adaugare_reteta(it, nr_ingred, timpdeprep, gramaj_ing, tip, nume, nume_ing, unit_ing);
                            cout << endl;
                            spatii(80); cout << "Continuati cu datele introduse? (Da/Nu)"; cin >> da_nu;

                            //daca a zis nu
                            while (strcmp(da_nu, "Nu")==0 || strcmp(da_nu, "NU")==0 || strcmp(da_nu, "nu")==0)
                            {
                                    cout << endl;
                                    spatii(70); cout << " ______________________________________________________" << endl;
                                    spatii(70); cout << "|                                                      |" << endl;
                                    spatii(70); cout << "|  1.Repetarea procesului                              |" << endl;
                                    spatii(70); cout << "|______________________________________________________|" << endl;
                                    spatii(70); cout << "|                                                      |" << endl;
                                    spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                                    spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> z;
                                    while (z!=1 && z!=0)
                                    {
                                        cout << endl;
                                        spatii(85); cout << "Raspuns invalid!" << endl;
                                        spatii(80); cout << "Alegeti optiunea dorita: ";
                                        cin >> z;
                                    }
                                    if (z==0)
                                    {
                                        break;
                                        okk=0;
                                    }
                                    else
                                    {
                                        system("CLS");
                                        cout << endl;
                                        spatii(20); cout << "INGREDIENTELE/ECHIPAMENTELE ACHIZITIONATE DE LA FURNIZORI LA MOMENTUL ACTUAL:" << endl << endl;
                                        citire_caut_bin_ingr_alfabetic();
                                        afisare_caut_bin_ingr(r);
                                        cout << endl << endl;
                                        //cin.get();
                                        chestionar_adaugare_reteta(it, nr_ingred, timpdeprep, gramaj_ing, tip, nume, nume_ing, unit_ing);
                                        cout << endl;
                                        spatii(80); cout << "Continuati cu datele introduse? (Da/Nu) "; cin >> da_nu;
                                    }
                            }
                            //daca a zis da
                            if (okk==1)
                            {
                                for(i=1; i<nr_ret; i++)
                                    vcaract[ret[i].cod]++;
                                for(i=1; i<1000 && k==-1; i++)
                                    if(vcaract[i]==0)
                                        k=i;
                                nr_ret++;
                                ret[nr_ret].cod = k;
                                strcpy(ret[nr_ret].tip, cu_(tip));
                                fara_(tip);
                                strcpy(ret[nr_ret].nume, cu_(nume));
                                fara_(nume);
                                ret[nr_ret].nr_ingred = nr_ingred;
                                for(i=1; i<=nr_ingred; i++)
                                {
                                    strcpy(ret[nr_ret].nume_ing[i], cu_(nume_ing[i]));
                                    fara_(nume_ing[i]);
                                    ret[nr_ret].gramaj_ing[i]=gramaj_ing[i];
                                    strcpy(ret[nr_ret].unit_ing[i], cu_(unit_ing[i]));
                                    fara_(unit_ing[i]);
                                }
                                for(i=1; i<=tipp[it].nr_et; i++)
                                    ret[nr_ret].timpdeprep[i]=timpdeprep[i];
                                ofstream rettt("retete.txt", ios::trunc);
                                if (rettt.is_open())
                                {
                                    rettt.close();
                                    rettt.open("retete.txt", ios::app);
                                    if(rettt.is_open())
                                    {
                                        for(i=1; i<=nr_ret; i++)
                                        {
                                            rettt<<ret[i].cod<<" "<<ret[i].tip<<" "<<ret[i].nume<<" "<<ret[i].nr_ingred<<" ";
                                            for (j=1; j<=ret[i].nr_ingred; j++)
                                                rettt<<ret[i].nume_ing[j]<<" "<<ret[i].gramaj_ing[j]<<" "<<ret[i].unit_ing[j]<<" ";
                                            for(j=1; j<=tipp[cautare_poz_tipp_dupa_nume_tip(ret[i].tip)].nr_et; j++)
                                                rettt<<ret[i].timpdeprep[j]<<" ";
                                            rettt<<endl;
                                        }
                                        rettt.close();
                                    }
                                }
                                citire_retete();
                                // de continuat cu ingredientele care nu se gasesc pe lista ingredientelor achizitionate
                                cout << endl << endl;
                                spatii(20); cout << "INGREDIENTELE DIN RETETA INDISPONIBILE MOMENTAN: " << endl << endl;
                                nr_ing_inex=0;
                                for(i=1; i<=ret[nr_ret].nr_ingred; i++)
                                {   strcpy(copie, ret[nr_ret].nume_ing[i]);
                                    if (cautare_bin_ingr(r, copie)==-1)
                                    {   nr_ing_inex++;
                                        strcpy(ing_inex[nr_ing_inex], copie);
                                        strcpy(unit_ing_inex[nr_ing_inex], unit_ing[i]);
                                        spatii(20); cout << fara_(copie) << endl;
                                    }
                                }
                                _getch(); cout << endl;

                                spatii(20); cout << "FURNIZORII PARTENERI, INSOTITI DE INGREDIENTELE AFERENTE: " << endl << endl;
                                afisare_fur_cu_ing();
                                _getch();
                                cout << endl << endl;
                                spatii(20); cout << "Pentru fiecare dintre ingredientele INDISPONIBILE, alegeti un furnizor: " << endl << endl;

                                for(i=1; i<=nr_ing_inex; i++)
                                {   ifu=-1;
                                    strcpy(copie, ing_inex[i]);
                                    spatii(20); cout << fara_(copie) << " -----> furnizor: "; cin.get(); cin.getline(furni, 100);
                                    strcpy(copie2, furni);
                                    for (j=1; j<=nr_fur; j++)
                                        if(strcmp(cu_(copie2), fur[j].nume)==0)
                                            if (fur[cautare_poz_fur_dupa_nume(fur[j].nume)].id%1000!=0)
                                               ifu=j;
                                    while (ifu==-1)
                                    {
                                        cout << endl << endl;
                                        spatii(40); cout << "Acest nume NU corespunde niciunui furnizor disponibil!" << endl;
                                        spatii(20); cout << fara_(copie) << " -----> furnizor: "; cin.getline(furni, 100);
                                        strcpy(copie2, furni);
                                        for (j=1; j<=nr_fur; j++)
                                        {
                                            if(strcmp(cu_(copie2), fur[j].nume)==0)
                                                if (fur[cautare_poz_fur_dupa_nume(fur[j].nume)].id%1000!=0)
                                                   ifu=j;
                                        }
                                    }//NU MAI AM INGREDIENTELE IN INGR

                                    int vcar[10000]={0}, k=-1;
                                    //for(j=1; j<=nr_ingr; j++)
                                    //    cout << ingr[j].id << endl;
                                    //_getch();
                                    for(j=1; j<=nr_ingr; j++)
                                    {
                                        if(ingr[j].id_superior==fur[ifu].id)
                                            vcar[ingr[j].id]++;
                                    }

                                    for(j=fur[ifu].id+1; j<=fur[ifu].id+99&&k==-1; j++)
                                        if(vcar[j]==0)
                                            k=j;
                                    inserare_bin_ingr(r, k, ing_inex[i], fur[ifu].id, unit_ing_inex[i]);
                                    nr_ingr++;
                                }
                                afisare_caut_bin_ingr_in_fisier(r);
                                citire_ingrediente();
                                cout << endl << endl;
                                spatii(80); cout << "Adaugare realizata cu succes!" << endl;
                                spatii(60); cout << "Puteti vizualiza modificarile in meniul de afisare a retetelor si a ingredientelor.";
                            }
                        }_getch();break;

                        case 3: //Eliminarea unei retete
                        {

                        }_getch();break;
                    }
                }while(y);
            }break;
            case 3: //Relatii furnziori-ingrediente
            {
                int w;
                do
                {   system("CLS");
                    cout << endl << endl << endl;
                    spatii(55); cout << " ________________________________________________________________________________ " << endl;
                    spatii(55); cout << "|                                                                                |" << endl;
                    spatii(55); cout << "|  1.Afisarea furnizorilor pe categorii, impreuna cu ingredientele furnizate     |" << endl;
                    spatii(55); cout << "|________________________________________________________________________________|" << endl;
                    spatii(55); cout << "|                                                                                |" << endl;
                    spatii(55); cout << "|  2.Afisarea ingredientelor alfabetic / dupa pret                               |" << endl;
                    spatii(55); cout << "|________________________________________________________________________________|" << endl;
                    spatii(55); cout << "|                                                                                |" << endl;
                    spatii(55); cout << "|  0.Inapoi la meniul anterior                                                   |" << endl;
                    spatii(55); cout << "|________________________________________________________________________________|" << endl<< endl;
                    cout << endl;
                    spatii(80); cout << "Alegeti optiunea dorita: "; cin >> w;
                    while (w!=1 && w!=2 && w!=0)
                    {
                        cout << endl;
                        spatii(85); cout << "Raspuns invalid!" << endl;
                        spatii(80); cout << "Alegeti optiunea dorita: ";
                        cin >> w;
                    }
                    switch(w)
                    {
                        case 1: //Afisarea furnizorilor pe categorii, impreuna cu ingredientele furnizate
                        {
                            afisare_fur_cu_ing();
                        }_getch();break;
                        case 2: //Afisarea ingredientelor alfabetic / dupa pret
                        {
                            int y;
                            do
                            {   system("CLS");
                                spatii(70); cout << " ______________________________________________________ " << endl;
                                spatii(70); cout << "|                                                      |" << endl;
                                spatii(70); cout << "|  1.Afisarea ingredientelor alfabetic                 |" << endl;
                                spatii(70); cout << "|______________________________________________________|" << endl;
                                spatii(70); cout << "|                                                      |" << endl;
                                spatii(70); cout << "|  2.Afisarea ingredientelor dupa pret                 |" << endl;
                                spatii(70); cout << "|______________________________________________________|" << endl;
                                spatii(70); cout << "|                                                      |" << endl;
                                spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                                spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                                cout << endl;
                                spatii(80); cout << "Alegeti optiunea dorita: "; cin >> y;
                                while (y!=1 && y!=2 && y!=0)
                                {
                                    cout << endl;
                                    spatii(85); cout << "Raspuns invalid!" << endl;
                                    spatii(80); cout << "Alegeti optiunea dorita: ";
                                    cin >> y;
                                }
                                switch(y)
                                {
                                    case 1: //Afisarea ingredientelor alfabetic
                                    {
                                        citire_caut_bin_ingr_alfabetic();
                                        cout << endl << endl;
                                        afisare_caut_bin_ingr(r);
                                    }_getch();break;
                                    case 2: //Afisarea ingredientelor dupa pret
                                    {
                                        int z;
                                        do
                                        {   system("CLS");
                                            spatii(70); cout << " ______________________________________________________ " << endl;
                                            spatii(70); cout << "|                                                      |" << endl;
                                            spatii(70); cout << "|  1.Afisarea ingredientelor dupa pret crescator       |" << endl;
                                            spatii(70); cout << "|______________________________________________________|" << endl;
                                            spatii(70); cout << "|                                                      |" << endl;
                                            spatii(70); cout << "|  2.Afisarea ingredientelor dupa pret descrescator    |" << endl;
                                            spatii(70); cout << "|______________________________________________________|" << endl;
                                            spatii(70); cout << "|                                                      |" << endl;
                                            spatii(70); cout << "|  0.Inapoi la meniul anterior                         |" << endl;
                                            spatii(70); cout << "|______________________________________________________|" << endl<< endl;
                                            cout << endl;
                                            spatii(80); cout << "Alegeti optiunea dorita: "; cin >> z;
                                            while (z!=1 && z!=2 && z!=0)
                                            {
                                                cout << endl;
                                                spatii(85); cout << "Raspuns invalid!" << endl;
                                                spatii(80); cout << "Alegeti optiunea dorita: ";
                                                cin >> z;
                                            }
                                            switch(z)
                                            {
                                                case 1: //Afisarea ingredientelor dupa pret crescator
                                                {
                                                    citire_caut_bin_ingr_dupa_pret_cresc();
                                                    cout << endl << endl;
                                                    afisare_caut_bin_ingr(cresc);
                                                }_getch();break;
                                                case 2: //Afisarea ingredientelor dupa pret descrescator
                                                {
                                                    citire_caut_bin_ingr_dupa_pret_descresc();
                                                    cout << endl << endl;
                                                    afisare_caut_bin_ingr(descresc);
                                                }_getch();break;
                                            }
                                        }while(z);
                                    }break;
                                }
                            }while(y);
                        }break;
                    }
                }while(w);
            }break;
        }
    }while(x);
}

void TnDs_pastry_mare()
{
    cout << R"(
                                                                                                                      ''''''
                                                        TTTTTTTTTTTTTTTTTTTTTTT   &&&&&&&&&&    DDDDDDDDDDDDD         '::::'
                                                        T:::::::::::::::::::::T  &::::::::::&   D::::::::::::DDD      '::::'
                                                        T:::::::::::::::::::::T &::::&&&:::::&  D:::::::::::::::DD    ':::''
                                                        T:::::TT:::::::TT:::::T&::::&   &::::&  DDD:::::DDDDD:::::D  ':::'
                                                        TTTTTT  T:::::T  TTTTTT&::::&   &::::&    D:::::D    D:::::D ''''       ssssssssss
                                                                T:::::T         &::::&&&::::&     D:::::D     D:::::D         ss::::::::::s
                                                                T:::::T         &::::::::::&      D:::::D     D:::::D       ss:::::::::::::s
                                                                T:::::T          &:::::::&&       D:::::D     D:::::D       s::::::ssss:::::s
                                                                T:::::T        &::::::::&   &&&&  D:::::D     D:::::D        s:::::s  ssssss
                                                                T:::::T       &:::::&&::&  &:::&  D:::::D     D:::::D          s::::::s
                                                                T:::::T      &:::::&  &::&&:::&&  D:::::D     D:::::D             s::::::s
                                                                T:::::T      &:::::&   &:::::&    D:::::D    D:::::D        ssssss   s:::::s
                                                              TT:::::::TT    &:::::&    &::::&  DDD:::::DDDDD:::::D         s:::::ssss::::::s
                                                              T:::::::::T    &::::::&&&&::::::&&D:::::::::::::::DD          s::::::::::::::s
                                                              TTTTTTTTTTT       &&&&&&&&   &&&&&DDDDDDDDDDDDDDDD              sssssssssss

                                          PPPPPPPPPPPPPPPPP                                            tttt
                                          P::::::::::::::::P                                        ttt:::t
                                          P::::::PPPPPP:::::P                                       t:::::t
                                          PP:::::P     P:::::P                                      t:::::t
                                            P::::P     P:::::Paaaaaaaaaaaaa      ssssssssss   ttttttt:::::ttttttt   rrrrr   rrrrrrrrryyyyyyy           yyyyyyy
                                            P::::P     P:::::Pa::::::::::::a   ss::::::::::s  t:::::::::::::::::t   r::::rrr:::::::::ry:::::y         y:::::y
                                            P::::PPPPPP:::::P aaaaaaaaa:::::ass:::::::::::::s t:::::::::::::::::t   r:::::::::::::::::ry:::::y       y:::::y
                                            P:::::::::::::PP           a::::as::::::ssss:::::stttttt:::::::tttttt   rr::::::rrrrr::::::ry:::::y     y:::::y
                                            P::::PPPPPPPPP      aaaaaaa:::::a s:::::s  ssssss       t:::::t          r:::::r     r:::::r y:::::y   y:::::y
                                            P::::P            aa::::::::::::a   s::::::s            t:::::t          r:::::r     rrrrrrr  y:::::y y:::::y
                                            P::::P           a::::aaaa::::::a      s::::::s         t:::::t          r:::::r               y:::::y:::::y
                                            P::::P          a::::a    a:::::assssss   s:::::s       t:::::t    ttttttr:::::r                y:::::::::y
                                          PP::::::PP        a::::a    a:::::as:::::ssss::::::s      t::::::tttt:::::tr:::::r                 y:::::::y
                                          P::::::::P        a:::::aaaa::::::as::::::::::::::s       tt::::::::::::::tr:::::r                  y:::::y
                                          PPPPPPPPPP          aaaaaaaaaa  aaaa sssssssssss              ttttttttttt  rrrrrrr                y:::::y
                                                                                                                                           y:::::y
                                                                                                                                          y:::::y
                                                                                                                                         y:::::y
                                                                                                                                        y:::::y
                                                                                                                                        yyyyyyy
)" << endl;
}

void TnDs_pastry_paradise_mic()
{
    cout << R"(

                                                _______      _____  _       _____          _                _____                    _ _
                                               |__   __|__  |  __ \( )     |  __ \        | |              |  __ \                  | (_)
                                                  | | ( _ ) | |  | |/ ___  | |__) |_ _ ___| |_ _ __ _   _  | |__) |_ _ _ __ __ _  __| |_ ___  ___
                                                  | | / _ \/\ |  | | / __| |  ___/ _` / __| __| '__| | | | |  ___/ _` | '__/ _` |/ _` | / __|/ _ \
                                                  | || (_>  < |__| | \__ \ | |  | (_| \__ \ |_| |  | |_| | | |  | (_| | | | (_| | (_| | \__ \  __/
                                                  |_| \___/\/_____/  |___/ |_|   \__,_|___/\__|_|   \__, | |_|   \__,_|_|  \__,_|\__,_|_|___/\___|
                                                                                                     __/ |
                                                                                                    |___/                                      )";
    cout << endl << endl;
}

int pagina_login()
{
    char usr[100], par[100], zero[5]="0", ok=1, ch, *copie_ch;
    int i, j=0;
    for (i=1; i<=5; i++)
        cout << endl;
    spatii(80); cout << " _________________" << endl;
    spatii(80); cout << "|                 |" << endl;
    spatii(80); cout << "|  PAGINA LOGIN   |" << endl;
    spatii(80); cout << "|_________________|" << endl << endl;
    spatii(80); cout << "Bine ati venit in aplicatie!"; _getch(); cout << endl << endl;
    spatii(80); cout << "Introduceti USERNAME-ul: " << endl;
    spatii(80); cin.getline(usr, 100);
    for (i=1; i<=nr_utilizatori; i++)
        if (strcmp(usr,login[i].username)==0)
            j=i;
    while(j==0)
    {
        cout << endl;
        spatii(80); cout << "Username gresit! Introduceti USERNAME-ul sau tastati 0 pentru a inchide aplicatia: " << endl;
        spatii(80); cin.getline(usr, 100);
        if (strcmp(usr, zero)==0)
        {   ok=0;
            j=-1;
        }
        else
           for (i=1; i<=nr_utilizatori; i++)
                if (strcmp(usr,login[i].username)==0)
                    j=i;
    }
    if(ok)
    {   cout << endl;
        spatii(80); cout << "Introduceti PAROLA: " << endl;
        spatii(80); //cin.getline(par, 100);
        int a=0;
        while ((ch=_getch())!='\r')
        {
            if (ch=='\b')
            {   if (a>0)
                {
                    cout << "\b \b";
                    a--;
                }
            }
            else
            {
                par[a++]=ch;
                cout << "*";
            }
        }
        par[a]=NULL;
        while (strcmp(par,login[j].parola)!=0)
        {
            cout << endl;
            spatii(80); cout << "Parola gresita! Introduceti PAROLA sau tastati 0 pentru a inchide aplicatia: " << endl;
            spatii(80);
            int a=0;
            while ((ch=_getch())!='\r')
            {   if (ch=='\b')
                {   if (a>0)
                    {   cout << "\b \b";
                        a--;
                    }
                }
                else
                {   par[a++]=ch;
                    cout << "*";
                }
            }
            par[a]=NULL;
            if (strcmp(par, zero)==0)
            {
                ok=0;
                strcpy(par, login[j].parola);
            }
        }
    }
    return ok;
}
void pagina_principala()
{
    int x;
    do
    {
        system("CLS");
        cout << endl << endl << endl;
        TnDs_pastry_paradise_mic();
        cout << endl << endl << endl;
        spatii(60); cout << " ______________________________________________________________________ " << endl;
        spatii(60); cout << "|                                                                      |" << endl;
        spatii(60); cout << "|  1.Gestionarea angajatilor si posturilor                             |" << endl;
        spatii(60); cout << "|______________________________________________________________________|" << endl;
        spatii(60); cout << "|                                                                      |" << endl;
        spatii(60); cout << "|  2.Gestionarea etapelor de productie, a retetelor si a furnizorilor  |" << endl;
        spatii(60); cout << "|______________________________________________________________________|" << endl;
        spatii(60); cout << "|                                                                      |" << endl;
        spatii(60); cout << "|  0.Deconectare                                                       |" << endl;
        spatii(60); cout << "|______________________________________________________________________|" << endl<< endl;

        spatii(80); cout << "Alegeti sectiunea dorita: "; cin >> x;
        while (x!=1 && x!=2 && x!=0)
        {
            cout << endl;
            spatii(85); cout << "Raspuns invalid!" << endl;
            spatii(80); cout << "Alegeti sectiunea dorita: ";
            cin >> x;
        }
        switch (x)
        {
            case 1: {gestionarea_ang_si_posturilor();} break;
            case 2: {gestionarea_et_de_productie_si_retetelor();} break;
        }
    }while(x);
}
int main()
{
    int ok;
    initializari();
    citiri();
    //afisari_info(); _getch();
    creare_arbori();
    cout << endl << endl << endl;
    TnDs_pastry_mare();_getch();
    system("CLS");
    //ok=1;
    ok=pagina_login();
    if (ok)
    {
       pagina_principala();
    }
    return 0;
}

/*matrice_niv(vtati_j, niv_j, nr_pe_niv_j, nr_niv_j);
    for(i=1; i<=nr_niv_j; i++)
    {   for(j=1; j<=nr_pe_niv_j[i]; j++)
            cout << niv_j[i][j] << " ";
        cout << endl;
    }
    afisare_arbore_joburi();
    cout << endl << endl;
    afisare_arbore_joburi_si_angajati();
    cout << endl << endl;
    afisare_arbore_fur_si_ingr();*/
