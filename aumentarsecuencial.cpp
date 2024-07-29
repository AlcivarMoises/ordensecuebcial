//Estudiante: Moises Alcivar Castillo
//Fecha : 25/07/2024
//Curso: 1ro de TI
//utilize el programa que miede el tiempo de ejecucion de los algortimos  de ordenacion 
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <windows.h>

using namespace std;


void ImprimeVector(int x[], int total)
{

    for(int k = 0; k < total; k++)
    {
        cout << endl << (k + 1) << ": " << x[k];
    }
}

void VectorNumAleatorio(int vector1[], int vector2[], int vector3[], int vector4[],int vector5[], int total)
{
    int lim_inf = 1;
    int lim_sup = 10000;
    for(int k = 0; k < total; k++)
    {
        int numero = lim_inf + rand() % ((lim_sup + 1) - lim_inf);
        vector1[k] = numero;
        vector2[k] = numero;
        vector3[k] = numero;
        vector4[k] = numero;
        vector5[k] = numero;
    }
}
void intercambiar(int& num1, int& num2)
{
    int aux = num1;
    num1 = num2;
    num2 = aux;
}

void burbujaMejorado(int arreglo[], int tamano){

    int comparaciones = tamano;

    bool termino = false;

    for (int i = 0; i<(tamano-1) ; i++){

        if (termino)

            break;

        termino = true;

        for (int j = 0; j<comparaciones-1 ; j++)

            if(arreglo[j] > arreglo[j+1]){

                intercambiar(arreglo[j],arreglo[j+1]);

                termino = false;

            }

        comparaciones--;

    }

}

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b)
{
  LARGE_INTEGER freq;
  QueryPerformanceFrequency(&freq);
  return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void ordenShell(int a[], int n)
{
    int ints,i,aux;
    bool band;
    ints=n;
    while(ints>1){
        ints=ints/2;
        band=true;
        while(band==true){
            band=false;
            i=0;
            while((i+ints)<n){
                if(a[i]>a[i + ints]){
                    aux=a[i];
                    a[i]=a[i + ints];
                    a[i + ints]=aux;
                    band=true;
                }
                i++;
            }
        }
    }
}

void ordenShell2(int a[], int n)
{
    int i,j,inc;
    int temp;
    for(inc=1;inc<n;inc=inc*3+1);
    while(inc>0){
        for(i=inc;i<n;i++){
            j=i;
            temp=a[i];
            while((j>=inc)&&(a[j-inc]>temp)){
                a[j]=a[j-inc];
                j=j-inc;
            }
            a[j]=temp;
        }
        inc=inc/2;

    }

}

void OrdenamientoQuicksort(int a[], int primerValor, int ultimoValor)

{

    int central, i, j, pivote;

    central= (primerValor+ultimoValor)/2; //Posicion central del arreglo

    pivote= a[central]; //Capturar el valor medio del arreglo

    i = primerValor;

    j = ultimoValor;

    do{

        //Separando en dos partes el arreglo

        while(a[i] < pivote) i++; //Separando los valores menores al pivote

        while(a[j] > pivote) j--; //Separando los valores mayores al pivote

        if(i<=j){

            int temporal;

            //Intercambio de valores

            temporal = a[i];

            a[i] = a[j];

            a[j] = temporal;

            i++;

            j--;

        }

    }while(i<=j);

    if (primerValor < j)

        OrdenamientoQuicksort(a, primerValor, j);

    if (i < ultimoValor)

        OrdenamientoQuicksort(a, i, ultimoValor);

}

void ordenSecuencial(int vector[], int total)
{
    for (int i = 0; i < total; i++)
    {
        for (int j = i + 1; j < total; j++)
    {
        if (vector [i]>vector [j])
        intercambiar (vector [i], vector [j]);
    }
    }
}
int main() 
{
    srand(time(NULL));
    const int MAX = 5000;
    int vectorburbuja [MAX];
    int vectorshell [MAX];
    int vectorshell2 [MAX];
    int vectorquick [MAX];
    int vectorordsecuencial [MAX];

    LARGE_INTEGER t_ini, t_fin;
    double secs, secsshell, secsshell2, secsquick, secsecuencial;

    VectorNumAleatorio(vectorburbuja, vectorshell, vectorshell2, vectorquick,vectorordsecuencial, MAX);
    
    //Burbuja Mejorado 4291
    QueryPerformanceCounter(&t_ini);
    burbujaMejorado(vectorburbuja, MAX);
    QueryPerformanceCounter(&t_fin);
    secs = performancecounter_diff(&t_fin, &t_ini);
    
    //Orden Shell
    QueryPerformanceCounter(&t_ini);
    ordenShell(vectorshell, MAX);
    QueryPerformanceCounter(&t_fin);
    secsshell = performancecounter_diff(&t_fin, &t_ini);

    //Orden Shell Optimizado
    QueryPerformanceCounter(&t_ini);
    ordenShell2(vectorshell2, MAX);
    QueryPerformanceCounter(&t_fin);
    secsshell2 = performancecounter_diff(&t_fin, &t_ini);

    //Quick Sort
    QueryPerformanceCounter(&t_ini);
    OrdenamientoQuicksort(vectorquick, 0, MAX -1);
    QueryPerformanceCounter(&t_fin);
    secsquick = performancecounter_diff(&t_fin, &t_ini);


    //Orden secuencial

    QueryPerformanceCounter(&t_ini);
    ordenSecuencial(vectorordsecuencial,MAX);
    QueryPerformanceCounter(&t_fin);
    secsecuencial = performancecounter_diff(&t_fin, &t_ini);
    
    cout << endl << "Prueba con " << MAX << " elementos";
    cout << endl << "Tiempo de ejecución burbuja mejorado: " << secs * 1000.0;

    cout << endl << "Tiempo de ejecución orden shell: " << secsshell * 1000.0;

    cout << endl << "Tiempo de ejecución orden shell optimizado: " << secsshell2 * 1000.0;
    
    cout << endl << "Tiempo de ejecución quick sort: " << secsquick * 1000.0;

    cout << endl << "Tiempo de ejecución Orden secuencial: " << secsecuencial * 1000.0;
    
    
 
    return 0;
}