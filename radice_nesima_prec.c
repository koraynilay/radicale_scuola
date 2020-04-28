// compilare con: gcc [nome file].c -o [nome file eseguibile] -lm
#include <stdio.h>
#include <stdlib.h>
#include <math.h> //solo per fmod() (per controllare se l'esponente è pari) e abs()
#define np(x) ((to_root < 0) ? (x * -1) : x)
#define mz(x) ((x < 0) ? (x+add) : (x-add))

double power(double base, double exp);
double trun(double x,double n);

int main(int argc, char *argv[])
{
	int r = 1;
	double to_root;
	double to_rootf;
	double exponent;
	double add;
	int prec;
	double input;
	double elev = 0;
	if(argv[1]){
		r = 0;
		to_root = atof(argv[1]);
		if(argv[2]){
			exponent = atof(argv[2]);
			if(argv[3]){
				prec = atoi(argv[3]);
			}
			else{
				printf("Scrivi il numero di cifre che vuoi dopo la virgola (max 9): ");scanf("%d", &prec);
			}
		}else{
			printf("Scrivi il tuo esponente: ");scanf("%lf", &exponent);
		}
	}else{
		printf("Scrivi il tuo numero: ");scanf("%lf", &to_root);
		printf("Scrivi il tuo esponente: ");scanf("%lf", &exponent);
		printf("Scrivi il numero di cifre che vuoi dopo la virgola: ");scanf("%d", &prec);
	}
	if(fmod(exponent,2.0) == 0){
		if(to_root < 0){
			fprintf(stderr,"errore: Impossibile calcolare una radice pari di un numero negativo.\n");
			if(r == 1){
				printf("\nPremere Ctrl+C per fermare l'esecuzione\n\n");
				main(argc, argv);
			}else{
				return 2;
			}
		}
	}
	if(prec > 9){
		fprintf(stderr,"errore: Il massimo di precisione è 9.\n");
		// "è" si vede giusta solo su linux, su windows (cmd o powershell) si vede "├¿" (almeno sul mio pc)
		// io l'ho sostituita con "e'" per il file di windows
		if(r == 1){
			printf("\nPremere Ctrl+C per fermare l'esecuzione\n\n");
			main(argc, argv);
		}else{
			return 2;
		}
	}
	to_rootf = abs(to_root);
	if(to_rootf >= 1){
		input = 1.0f;
	}else{
		input = 0.0f;
	}
	double power_ten = power(10,prec);
	add = 1/power_ten;
	while(elev < to_rootf){
		input += add;
		elev = power(input,exponent);
	}
	if(to_root == 1){
		printf("La radice %g di %.f è: %.f\n",exponent,to_root,to_root);
	}else{
		printf("La radice %g di %g è compresa tra %.16g e %.16g\n",exponent,to_root,trun(mz(np(input)),power_ten),trun(np(input),power_ten));
		// "è" si vede giusta solo su linux, su windows (cmd o powershell) si vede "├¿" (almeno sul mio pc)
		// io l'ho sostituita con "e'" per il file di windows
	}
	if(r == 1){
		printf("\nPremere Ctrl+C per fermare l'esecuzione\n\n");
		main(argc, argv);
	}else{
		return 0;
	}
	
}

double power(double base, double exp){
	double res = base;
	for(int i = 0; i < exp-1; i++)
	{
		res = res*base;
	}
	return res;
}
double trun(double x, double n)
{
	int a=x*n;
	return a/n;
}