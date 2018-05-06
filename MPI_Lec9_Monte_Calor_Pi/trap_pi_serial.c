#include "time.h"
#include "stdlib.h"
#include "stdio.h"
#include "math.h"

#define N 1000000

int main () {
	long double dx = 1./((long double)N);
	long double x;
	double f_x;
	double Area;
	int i;
	double pi;

	// Set up timer variables
	clock_t timer = clock();
	float time_to_calculate;

	for(int i = 0; i < N; i++) {
		// Calculate x	
		x = dx*i;
		
		// Use this to find y = (1-x^2)^(1/2)
		f_x = sqrt(1-x*x);

		// Add to area (note, we don't multiply by dx here)
		Area += f_x;
	} // for(int i = 0; i < N; i++) {

	// Multiply Area by dx
	Area = Area*dx;

	// Stop timer, calculate time
	timer = clock() - timer;
	time_to_calculate = ((float)timer)/((float)CLOCKS_PER_SEC);

	// Find PI, print results
	pi = 4*Area;
	printf("PI = %f\n",pi);
	printf("Time to calculate pi in serial: %f (s)\n",time_to_calculate);

	return 0;
}
