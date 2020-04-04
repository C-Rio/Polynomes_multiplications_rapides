#include "stdlib.h"
#include "stdio.h"
#include "complex.h"

#define PI 3.14159265358979323846
#define printfc(c) printf("%lf + %lf*I\n",creal(c), cimag(c))

// Permet de representer un couple
typedef struct couple_t {
  complex x;
  complex y;
}couple;

// Representation couple d'un polynome
typedef struct polynome_couples_t {
  couple * couples;
  int degre;
}polynome_couples;

// Representation par coefficients d'un polynome
typedef struct polynome_coeff_t {
  int degre;
  complex * coeff;
}polynome_coeff;



// Fonctions concernant la representation "couples"
//----------------------------------------------------------------------------------------------------------------------

// Initialise un polynome sous la representation "couples"
polynome_couples* poly_couples_init(int);

// Multiplie un polynome sous la representation "couples" : O(n)
polynome_couples* poly_couples_mult(polynome_couples *, polynome_couples *);

// Affiche les coefficients d'un polynome sous la representation "couples"
void poly_couples_print(polynome_couples *P);


// Fonctions concernant la representation "coefficients"
//----------------------------------------------------------------------------------------------------------------------

// Initialise un polynome sous la representation "coefficients"
polynome_coeff* poly_coeff_init();

// Multiplie deux polynomes sous la representation "coefficients" : O(n^2)
polynome_coeff poly_coeff_mult(polynome_coeff *, polynome_coeff *);

// Affiche les coefficients d'un polynome sous la representation "coefficients"
void poly_coeff_print(polynome_coeff *P);

// Multiplie deux polynomes sous la representation "coefficients" en utilisant Karatsuba : O(n^log(3))
polynome_coeff poly_coeff_karatsuba_mult(polynome_coeff ,polynome_coeff);

// Recupere les k premiers coefficients d'un polynome sous la representation "coefficients"
polynome_coeff poly_coeff_firstpart(polynome_coeff, int);

// Recupere les k derniers coefficients d'un polynome sous la representation "coefficients"
polynome_coeff poly_coeff_lastpart(polynome_coeff,int );

// Multiplie le polynome sous la representation "coefficients" par x^k
polynome_coeff poly_coeff_shift(polynome_coeff ,int );

// Additionne deux polynomes sous la representation "coefficients"
polynome_coeff poly_coeff_add(polynome_coeff , polynome_coeff );

// Renvoie l'oppose d'un polynome sous la representation "coefficients"
polynome_coeff poly_coeff_negative(polynome_coeff );

// Reduit le degre d'un polynome sous la representation "coefficients" en supprimant les coefficients inutiles
void poly_coeff_degre_max(polynome_coeff *);

// On créer un polynome de degré k
polynome_coeff poly_coeff_create(int );

// Ajoute k coéfficients nuls au polynome initial
polynome_coeff poly_coeff_addcoeff(polynome_coeff, int);



// Fonctions concernant les deux representations
//----------------------------------------------------------------------------------------------------------------------

// On passe en representation couples puis on utilise la multiplication naive en O(n)
polynome_couples poly_couples_fast_mult(polynome_coeff, polynome_coeff);

// Permet de passer de la representation coéfficients à la representations couples
polynome_coeff FFT(polynome_coeff, int, polynome_couples *);
