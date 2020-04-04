# Multiplication rapide de polynômes

Librairie permettant la multiplication de polynômes en utilisant différents algorithmes (notamment Karatsuba). Les polynômes sont représentés sous forme de "coefficients" ou de "couples"  

Ce dépôt contient les fichiers suivants :

* makefile 

* polynome.h et polynome.c : Fichiers de base de la librairie

* karatsuba.c : Multiplication de polynômes en utilisant Karatsuba

* fft.c : Passage de la représentation "coefficients" à la représentation "couples"

* fast_mult.c : Multiplication rapide de polynômes à partir de la représentation "coefficients" (transformation en "couples" puis multiplication en O(n))

* std_mult.c : Multiplication naïve en O(n²) en représentation "coefficients"
  


