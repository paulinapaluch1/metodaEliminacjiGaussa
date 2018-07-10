#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

int wyborGaussa();
void definicjaTablicy(double **M,int r,int ch);
int wyborZadania();
void pobranieDanych(double **M,int r);
void Gauss(double **M,int r,int w);; //funkcja doprowadzajaca do macierzy trojkatnej gornej
void szukamyMaksW(double **M, int r, int i,int &maksK);
void szukamyMaks(double **M,int r,int i,int &maksW,int &maksK);
void zamianaWierszy(double **M,int i,int r,int maksW);
void zamianaKolumn(double **M,int i,int r,int maksK);
void krok(double **M,int roz, int i);
void wypelnij(int r,int *W); //tworzenie ntablicy indeksow
void obliczWyswietl(double **M,int r,double *odp,int *W);

int main()
{
    int c=wyborGaussa();
    if(c==0) return 0;
    int r,ch=wyborZadania();
    if(ch==1) r=4;
    else if(ch==2) r=3;
    else if(ch==3) r=4;
    else if(ch==4) r=3;
    if(ch!=5)
   {
        double **M=new double*[r];
        for(int i=0; i<r; i++)
        *(M+i)=new double[r+1];
            definicjaTablicy(M,r,ch);
            Gauss(M,r,c);
   }
   else if(ch==5)
   {
        cout<<"Podaj ilosc wierszy macierzy kwadratowej:" <<endl;
        cin>>r;
            double **M=new double*[r];
            for(int i=0; i<r; i++)
            *(M+i)=new double[r+1];
                pobranieDanych(M,r);
                Gauss(M,r,c);
   }    return 0;
}

int wyborZadania()
{
    int ch;
    cout<<"Wybierz zadanie"<<endl<<"1-przyklad 1"<<endl<<"2-przyklad 2"<<endl;
    cout<<"3-przyklad 3 "<<endl<<"4-przyklad 4"<<endl<<"5-dane od uzytkownika"<<endl;
    cin>>ch;
    while(ch<1||ch>5)
    {
        cout<<"Wybierz odpowiedni numer!"<<endl;
        cin>>ch;
    }
    return ch;
}
void definicjaTablicy(double **M,int r,int ch)
{
    if(ch==1)
    {
     M[0][0]=0; M[0][1]=1; M[0][2]=2; M[0][3]=3; M[0][4]=8;
     M[1][0]=1; M[1][1]=0; M[1][2]=1; M[1][3]=2; M[1][4]=4;
     M[2][0]=1; M[2][1]=2; M[2][2]=3; M[2][3]=4; M[2][4]=10;
     M[3][0]=0; M[3][1]=1; M[3][2]=3; M[3][3]=2; M[3][4]=7;
    }
    else if(ch==2)
    {
     M[0][0]=2; M[0][1]=3; M[0][2]=4; M[0][3]=9;
     M[1][0]=1; M[1][1]=2; M[1][2]=-2; M[1][3]=7;
     M[2][0]=4; M[2][1]=-2; M[2][2]=5; M[2][3]=-5;
    }
    else if(ch==3)
    {
     M[0][0]=1; M[0][1]=2; M[0][2]=3; M[0][3]=4; M[0][4]=2;
     M[1][0]=1; M[1][1]=4; M[1][2]=9; M[1][3]=16; M[1][4]=10;
     M[2][0]=1; M[2][1]=8; M[2][2]=27; M[2][3]=64; M[2][4]=44;
     M[3][0]=1; M[3][1]=16; M[3][2]=81; M[3][3]=256; M[3][4]=190;

    }
    else if(ch==4)
    {
     M[0][0]=5; M[0][1]=2; M[0][2]=-2; M[0][3]=5;
     M[1][0]=3; M[1][1]=1; M[1][2]=2; M[1][3]=1;
     M[2][0]=2; M[2][1]=3; M[2][2]=2; M[2][3]=5;
    }


}

void pobranieDanych(double **M,int r)
{
     for(int i=0;i<r;i++)
    {
        for(int j=0;j<r+1;j++)
        {
            cout<<"Podaj element ["<<i<<"]["<<j<<"]   ";
            cin>>M[i][j];
        }
    }}

int wyborGaussa()
{
    int w;
    cout<<"Metoda eliminacji Gaussa"<<endl;
    cout<<"1. Gauss podstawowy"<<endl<<"2. Gauss z wyborem el. max w wierszu"<<endl;
    cout<<"3. Gauss pelny"<<endl<<"4. Koniec programu"<<endl<<"Wybierz odpowiednia cyfre"<<endl;
    cin>>w;
    if(w==1||w==2||w==3)
    return w;
    else return 0;
}

void Gauss(double **M,int r,int w)
{   int maksW,maksK;
    int W[r]; wypelnij(r, W); //tablica indeksow
    double odp[r]; //tablica wynikow
    for(int k=0; k<r; k++)
    {   maksW=k; maksK=k;
        if(w==2)
        {
            szukamyMaksW(M,r,k,maksK);
            if(k!=maksK)
            {swap((W[k]),(W[maksK])); //zamieniam indeksy przed zamianie kolumn
            zamianaKolumn(M,k,r,maksK);}
        }
        else if(w==3)
        {
              szukamyMaks(M,r,k,maksW,maksK);
              if(k!=maksW) zamianaWierszy(M,k,r,maksW);
              if(k!=maksW){swap((W[k]),(W[maksK]));
              zamianaKolumn(M,k,r,maksK);}

        }
        if(fabs(M[k][k])<0.00000001)
        {
            cout<<"Nie da sie rozwiazac takiego ukladu rownan"<<endl;
            return;
        }
        krok(M,r,k);
    }
    if(fabs(M[r-1][r-1])<0.00000001)
        {
            cout<<"Nie da sie rozwiazac takiego ukladu rownan"<<endl;
            return;
        }
        obliczWyswietl(M,r,odp,W);
}


void krok(double **M,int roz, int i)
{
    double p;
    for(int j=i+1;j<roz;j++)
    {   p=(M[j][i])/(M[i][i]);
        for(int k=i;k<roz+1;k++)
        {
            M[j][k]=M[j][k]-(p*(M[i][k]));
            if(fabs(M[j][k])<0.0000000001) M[j][k]=0;
        }
    }
}

void szukamyMaksW(double **M, int r, int i,int &maksK)
{

    for(int k=i;k<r;k++)
    {
        if(fabs(M[i][maksK])<fabs(M[i][k]))  maksK=k;

    }
}


void szukamyMaks(double **M,int r,int i, int  &maksW,int &maksK)
{
    for(int j=i;j<r;j++)
    {
    for(int k=i;k<r;k++)
    {
        if(fabs(M[maksW][maksK])<fabs(M[j][k]))
        {
            maksW=j;
            maksK=k;
        }
    }
    }
}

void zamianaWierszy(double **M,int i,int r,int maksW)
{
    for(int k=0;k<(r+1);k++) swap((M[maksW][k]),(M[i][k]));
}


void zamianaKolumn(double **M,int i,int r,int maksK)
{
     for(int k=0;k<r;k++) swap(M[k][maksK],M[k][i]);
}

void wypelnij(int r, int *W)
{
    for(int i=0;i<r;i++)
    {
        W[i]=i+1;
    }
}

void obliczWyswietl(double **M,int r,double *odp,int *W)
{
    cout<<endl<<"Macierz trojkatna: "<<endl;
    for(int i=0;i<r;i++)
    {

        for(int j=0;j<r+1;j++)
            cout<<M[i][j]<<"  ";

        cout<<endl;
    }
    cout<<endl;
    odp[r-1]=(M[r-1][r])/(M[r-1][r-1]);
    for(int i=r-2;i>-1;i--)
    {
        odp[i]=M[i][r];
        for(int j=r-1;j>i;j--)
        {
            odp[i]=odp[i]-(M[i][j]*odp[j]);
        }
        odp[i]=(odp[i])/(M[i][i]);
        if(fabs(odp[i])<0.0000001)odp[i]=0;
    }
    cout<<"Rozwiazania ukladu rownan:"<<endl;
    for(int i=0;i<r;i++) cout<<"x"<<W[i]<<" = "<<odp[i]<<endl;
}

