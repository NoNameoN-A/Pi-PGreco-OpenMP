#include <iostream>
#include <omp.h>
#include <cmath>
#include <stdio.h>
#include <time.h>
#include <cstdlib>

using namespace std;

const int NUM_THREADS = 8;

int main() {
	double x, y, startTime, stopTime, raggio = 1.0, dentroIlCerchio = 0;
	double pGreco;
	const unsigned int ripetizioni = 1000000; //10^7
	srand(time(NULL));
	int num_threads = 9899;
	
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel for  private (x,y) reduction(+:dentroIlCerchio) num_threads(16)
	{

		if (omp_get_thread_num() == 0) startTime = omp_get_wtime();

		for (int i = 0; i < ripetizioni; i++) {
			x = rand() % 1000 + 1; //Calcolo x
			y = rand() % 1000 + 1; //Calcolo y
			x /= 1000, y /= 1000;

			//cout << "x: " << x << " && y: " << y << endl;
			if ((x * x + y * y) <= raggio * raggio)
				dentroIlCerchio += 1;
			num_threads = omp_get_num_threads();
		}

		stopTime = omp_get_wtime();
	}

	cout << "Numero di threads -> " << num_threads << endl; //Questo
	cout << "Start -> " << startTime << endl;

	pGreco = 4.0 * (dentroIlCerchio / (double)ripetizioni);

	cout << "In " << ripetizioni << " pi e': " << pGreco << endl;
	cout << "Tempo impiegato: " << (stopTime - startTime) * 1000 <<" millisecondi."<< endl;
	
	

}