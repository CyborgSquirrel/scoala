#include <stdio.h>
#include <math.h>

int main(int argc, char **argv) {
	float Tc    = 10;
	float Tgsa  = 10;
	float Ew    = 10;
	float Rw    = 0;
	float Esh   = 10;
	float Rsh   = 0;
	float Epr   = 10;
	float Rpr   = 0;
	float Eth   = 10;
	float Rth   = 0;
	
	while (1) {
		printf("Ew = "); scanf("%f", &Ew);
		float Grade = floor(0.5 + 1 + 0.05*Tc + 0.05*Tgsa + 0.3*fmax(Ew, Rw) + 0.2*fmax(Esh, Rsh) + 0.15*fmax(Epr, Rpr) + 0.15*fmax(Eth, Rth));
		printf("Grade = %f\n", Grade);
	}
	
	return 0;
 }
