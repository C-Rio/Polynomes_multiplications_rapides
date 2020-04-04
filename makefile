all : karatsuba std_mult fft fast_mult

karatsuba : polynome.c polynome.h karatsuba.c
		gcc karatsuba.c polynome.c polynome.h -o karatsuba

std_mult : polynome.c polynome.h std_mult.c
		gcc std_mult.c polynome.c polynome.h -o std_mult

fft : polynome.c polynome.h fft.c
		gcc fft.c polynome.c polynome.h -o fft

fast_mult : fast_mult.c polynome.c polynome.h
		gcc fast_mult.c polynome.c polynome.h -o fast_mult
