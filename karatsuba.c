#include "polynome.h"

int main(int argc, char const *argv[]) {
    polynome_coeff *A, *B, C;

    A = poly_coeff_init();
    B = poly_coeff_init();

    C = poly_coeff_karatsuba_mult(*A, *B);
    poly_coeff_degre_max(&C);
    poly_coeff_print(&C);
		
    return EXIT_SUCCESS;
}
