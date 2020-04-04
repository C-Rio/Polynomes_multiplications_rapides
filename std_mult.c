#include "polynome.h"

int main()
{
    polynome_coeff *A, *B, C;

    A = poly_coeff_init();
    B = poly_coeff_init();

    C = poly_coeff_mult(A, B);
    poly_coeff_print(&C);

    return EXIT_SUCCESS;
}
