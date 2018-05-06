#include "math.h"
#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#define N 100000000

int main() {
	double x,y;
	int i;
	long count = 0;
	double r;
	double pi;
	
	// Set up timing variables
	clock_t timer;
	double time_to_calculate = clock();

	// Seed random function with current time
	srand(time(0));

	for(i = 1; i<N ; i++) {
		// Calculate random coordinates
		x = (double)rand()/((double)RAND_MAX);
		y = (double)rand()/((double)RAND_MAX);

		// Calculate radius of point (x,y)
		r = sqrt(x*x + y*y);
	
		// Check if current point is inside of unit circle
		if(r <= 1.) {
			count++;
		}	// if(r <= 1) {	
	}	// for(i = 1; i < N; i++) {

	// Finalize timer
	timer = clock() - timer;
	time_to_calculate = ((double)timer)/((double)CLOCKS_PER_SEC);

	// Now calculate pi, print results
	pi = ((double)count/((double)N))*4.0;
	printf("Pi = %f\n",pi);
	printf("Time to calculate pi (in serial): %f (s)\n",time_to_calculate);
	
	return 0;
}
