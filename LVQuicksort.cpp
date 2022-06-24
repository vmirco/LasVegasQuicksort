#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>
using namespace std;

//DEFINIZIONE FUNZIONI
void scambia(vector<int> v, int i, int j);
void LVQuicksort_aux(vector<int> v, int inizio, int fine, int& confronti);
int partitionRandom(vector<int> v, int inizio, int fine, int& confronti);
void LVQuicksort(vector<int>, int& confronti);

int main(){
	int confronti = 0;
	vector<int> v1(10000);
	for(int j = 0; j < 100000 ; j++){
	//GENERO VETTORE DI 10000 ELEMENTI CASUALI
		srand(time(NULL));
		int temp;
		for(int i = 0; i < 10000; i++){
			temp = rand()%1000;
			v1.at(i) = temp;
		}
	//CHIAMO QUICKSORT RANDOMIZZATO
		LVQuicksort(v1, confronti);
		cout << confronti << endl;
		confronti = 0; //Ripristino il counter
	}

}

//IMPLEMENTAZIONE FUNZIONI AUSILIARIE
void scambia(vector<int> v, int i, int j)
{
  int tmp = v[j];
  v[j] = v[i];
  v[i] = tmp;
}

/**************************************************************************************
				                 LAS VEGAS QUICKSORT
***************************************************************************************/
int partitionRandom(vector<int> v, int inizio, int fine, int& confronti)
{
 		srand(time(NULL));
  	int indicep = inizio + rand()%(fine - inizio +1); //Indice pivot randomico
  	scambia(v,inizio,indicep); //Sposto il valore del pivot al primo posto
  	int i = inizio + 1; //Assegno all'indice i la seconda posizione, stessa cosa j
  	int pivot = v[inizio]; //Assegno a pivot il valore del pivot (serve per confronto nel for)
  	for(int j = inizio + 1; j <= fine; j++){
			confronti++;
    	if(v[j] < pivot){
      	scambia(v,j,i);
      	i++;
    	}
  	}
  	scambia(v,inizio,i-1); //Sposto pivot in posizione i-1
  	return i-1; //Riporto l'indice di dove si trova il pivot
}

void LVQuicksort_aux(vector<int> v, int inizio, int fine, int& confronti)
{
   if (inizio < fine) {
  		int p = partitionRandom(v,inizio,fine, confronti); //Indirizzo di dove si trova il pivot in v
	   	LVQuicksort_aux(v, inizio, (p-1), confronti); //Prima sottosequenza da analizzare
	   	LVQuicksort_aux(v, (p+1), fine, confronti); //Seconda sottosequenza da analizzare
   }
}

void LVQuicksort(vector<int> v, int& confronti)
{
   LVQuicksort_aux(v,0,v.size()-1, confronti); //Chiamata
}
