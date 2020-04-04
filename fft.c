#include "polynome.h"

//poly inverse_DFT(poly, int);


int main(int argc, char const *argv[])
{
    polynome_coeff *A;
    polynome_couples * C;

    A = poly_coeff_init();
    C = poly_couples_init(A->degre +1);

    *A = FFT(*A, A->degre +1, C);
    poly_couples_print(C);

    return EXIT_SUCCESS;
}



/*
poly inverse_DFT(poly P, int n)

{
  int i;

  if (n == 1) return P;
  if (n%2 == 1)
  {
    P = poly_coeff_addcoeff(P);
    n++;
  }
  poly A0, A1, B0, B1, B;
  complex Wn, W;

  Wn = cexp( I * (-2*PI/n) );

  A0 = pair(P, n);
  A1 = impair(P, n);

  B0 = DFT(A0, n/2);
  B1 = DFT(A1, n/2);

  B = allocation_memoire(n-1);

  for (i = 0; i < n/2 ; i++)
  {
      W = cexp( I * (-2*PI*i/n) );
      B.coeff[i] = B0.coeff[i] + W*B1.coeff[i];
      B.coeff[i+n/2] = B0.coeff[i] + (-1*W*B1.coeff[i]);
      //W = W*Wn;
      printf("W%lf %lf\n",creal(W), cimag(W));
  }

  return B;
}
*/
/*
polynome_coeff FFT(polynome_coeff P, int n, polynome_couples *C)
{
    int i;

    if (n == 1) return P;       // Si le polynome ne contient que un coéfficient (degré = 0) on le renvoie
    if (n%2 == 1)       // Si le nombre de coéfficients est impair
    {
        P = poly_coeff_addcoeff(P,1);       // On ajoute un coéfficient pour le rendre paire
        n++;
    }
    polynome_coeff A0, A1, B0, B1, B;
    complex Wn, W;

    Wn = cexp( I * (2*PI/n) );      // On calcul la racine n-ième
    W = 1;

    A0 = pair(P, n);        // On recupère les coéfficients pairs
    A1 = impair(P, n);      // On recupère les coéfficients impairs

    B0 = FFT(A0, n/2, C);       // On rappelle l'algorithme pour les coéfficients pairs
    B1 = FFT(A1, n/2, C);       // On rappelle l'algorithme pour les coéfficients impairs

    B = poly_coeff_create(n-1);

    for (i = 0; i < n/2 ; i++)      // En utilisant les racines de l'unité, on peut calculer uniquement n/2 coéfficients
    {
        B.coeff[i] = B0.coeff[i] + W*B1.coeff[i];
        B.coeff[i+n/2] = B0.coeff[i] + (-1*W*B1.coeff[i]);
        C->couples[i].x = W;
        C->couples[i].y = B.coeff[i];
        C->couples[i+n/2].x = -W;
        C->couples[i+n/2].y = B.coeff[i+n/2];
        W = W*Wn;       // On calcul les racines suivantes
    }

    return B;
}
*/

