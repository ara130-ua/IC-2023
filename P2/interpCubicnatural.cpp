#include <math.h>
#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>

using namespace std;

const int T = 1400;

float fact(float x){
    if(x==0) return 1;
    else return x*fact(x-1);
}

float f(float x){
    return sqrt( pow(( x + fact(20) ) 
    / fact(20), 20) 
    / pow(( x + fact(20) ) 
    / fact(20), 20)) * 
    sqrt( pow(( x + fact(20) ) 
    / fact(20), 20) 
    / pow(( x + fact(20) ) 
    / fact(20), 20)) ;
}

void calcularA (float a[]){
    for(unsigned int i=0; i<T; i++){
        a[i] = f(i);
    }
}

void calcularH (float h[], float listaPuntos[]){
    for(unsigned int i=0; i<T-1; i++){
        h[i] = (listaPuntos[i+1] - listaPuntos[i]);
    }
}

void calcularV (float v[], float h[], float a[]){
    for(unsigned int i=1; i<T-1; i++){
        v[i-1] = (3/h[i])*(a[i+1]-a[i])-(3/h[i-1])*(a[i]-a[i-1]);
    }
}

void calcularM (float m[T-2][T-2], float h[]) {
    for (unsigned int i = 1 ; i < T-1 ; i++) {
        for (unsigned int j = 1 ; j < T-1 ; j++) {
            if (i == j) {
                m[i-1][j-1] = 2*(h[i-1]+h[i]);
            } else if (i == j+1) {
                m[i-1][j-1] = h[i];
            } else if (i+1 == j) {
                m[i-1][j-1] = h[i];
            } else {
                m[i-1][j-1] = 0;
            }
        }
    }
}

void traspuesta (float m[T-2][T-2], float t[T-2][T-2]) {
    float aux;
    for (unsigned int i = 0 ; i < T-2 ; i++) {
        for (unsigned int j = 0 ; j < T-2 ; j++) {
            t[j][i] = m[i][j];
        }
    }
}

void calcularC ( float c[], float m[T-2][T-2], float v[]){

    for ( unsigned int i = 0 ; i < T ; i++ ) {
        c[i] = 0;
    } 

    for (unsigned int i = 0 ; i < T ; i++) {
        if(i == 0 || i == T-1){
            c[i] = 0;
        }
        else{
            for (unsigned int j = 0 ; j < T-2 ; j++) {
                c[i] += m[i][j]*v[j];
            }
        }
    }
}

void calcularB(float b[], float a[], float h[], float c[]){
    for(unsigned int i=0; i<T-1; i++){
        b[i] = (a[i+1]-a[i])/h[i] - (h[i]*(c[i+1]+2*c[i]))/3;
    }
}

void calcularD(float d[], float c[], float h[]){
    for(unsigned int i=0; i<T-1; i++){
        d[i] = (c[i+1]-c[i])/(3*h[i]);
    }
}

void crearMatrizResultado ( float m[6][T], float x[], float h[], float a[], float b[], float c[], float d[]  ) {
    for ( unsigned int i = 0 ; i < T ; i++ ) {
        for ( unsigned int j = 0 ; j < 6 ; j++ ) {
			if ( i < T - 1 ) { 
				switch (j) {
					case 0: m[j][i] = x[i];
						break;
					case 1: m[j][i] = h[i];
						break;
					case 2: m[j][i] = a[i];
						break;
					case 3: m[j][i] = b[i];
						break;
					case 4: m[j][i] = c[i];
						break;
					case 5: m[j][i] = d[i];
						break;
					default:
						break;
				}
			} else {
				switch (j) {
					case 0: m[j][i] = x[i];
						break;
					case 2: m[j][i] = a[i];
						break;
					case 4: m[j][i] = c[i];
						break;
					default:
						break;
				}
			}
        }
    }
}

void imprimirMatrizResultado ( float m[6][T] ) {
    cout << "-------------------------" << endl;
    cout << "| x | h | a | b | c | d |" << endl;
    for ( unsigned int i = 0 ; i < T ; i++ ) {
        cout << "-------------------------" << endl;
        for ( unsigned int j = 0 ; j < 6 ; j++ ) {
            cout << "| " << m[j][i] << " ";    
        }
        cout << "|" << endl;
    } cout << "-------------------------" << endl;
}

void imprimirFuncionResultado (float m[6][T]) {
    for ( unsigned int i = 0 ; i < T-1 ; i++ ) {
        cout << "x pertenece [" << m[0][i] << "," << m[0][i+1] << ")" <<
                "   S" << i << "(x) = " << m[2][i] << " + " <<
                m[3][i] << " * ( x - " << m[0][i] << " ) + " <<
                m[4][i] << " * ( x - " << m[0][i] << " )^2 +  " <<
                m[5][i] << " * ( x - " << m[0][i] << " )^3" << endl;
    }
}

int main(){

    clock_t inicio, fin;
    float tiempo;
    inicio = clock();

    float listaPuntos[T];
    float a[T], h[T-1], d[T-1], b[T-1], c[T-1], v[T-2], m[T-2][T-2];
    float matrizR[6][T];
    
    for (int i = 0 ; i < T ; i++ ) {
        listaPuntos[i] = i;
    }
    
    calcularH(h, listaPuntos);
    calcularA(a);
    calcularV(v, h, a);
    calcularM(m, h);
    traspuesta(m, m);
    calcularC(c, m, v);
    calcularB(b, a, h, c);
    calcularD(d, c, h);
	crearMatrizResultado(matrizR, listaPuntos, h, a, b, c, d);
	imprimirMatrizResultado(matrizR);
	imprimirFuncionResultado(matrizR);

    fin = clock();
    tiempo = (float) (fin - inicio) / CLOCKS_PER_SEC;
    cout << "Tiempo: " << tiempo << endl;

    return 0;
}
