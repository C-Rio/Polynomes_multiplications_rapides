#include "polynome.h"

int main()
{
    polynome_coeff *A, *B;
    polynome_couples E;


    A = poly_coeff_init();
    B = poly_coeff_init();

    E = poly_couples_fast_mult(*A, *B);
    poly_couples_print(&E);

    return EXIT_SUCCESS;
}
