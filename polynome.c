#include "polynome.h"


polynome_coeff* poly_coeff_init()
{
	int i;
    complex w;
	polynome_coeff *P = (polynome_coeff*)malloc(sizeof(polynome_coeff));  //Alloue de la mémoire pour la structure

	printf("Entrez le degre de P :  ");
	scanf("%d", &(P->degre));

	P->coeff = (complex*)malloc((P->degre +1)*sizeof(complex));     // Alloue degre+1 case de complex

	for (i=0; i <= P->degre; i++)       // Demande les valeurs des coéfficients à l'utilisateur
	{
		printf("Entrez le coef de degre %d de P :", i);
		scanf("%lf",&w);
        P->coeff[i] =w;
	}
	return P;       // Renvoie ce nouveau polynome
}

polynome_coeff poly_coeff_mult(polynome_coeff *P1, polynome_coeff *P2)
{
	int i,j;
	polynome_coeff P3;
    P3 = poly_coeff_create(P1->degre + P2->degre);      // Alloue la mémoire pour le polynome produit

	for (i = 0; i <= P1->degre;i++)
	{
		for (j = 0; j <= P2->degre; j++)
		{
			P3.coeff[i+j] += P1->coeff[i] * P2->coeff[j];       // Multiplie les coéfficients en tenant compte de leur degré
		}
	}

	return P3;      // Renvoie ce polynome
}

void poly_coeff_print(polynome_coeff *P)
{
	int i;

	printf("\nLe polynome est : \n");

	for (i = 0; i <= P->degre; i++)     // Pour chaque 0 <= i <= degre
	{
		printfc(P->coeff[i]);       // Affiche le coéfficients du degre i
	}
}

polynome_couples* poly_couples_init(int x)
{
	polynome_couples *P = (polynome_couples*)malloc(sizeof(polynome_couples));      // Alloue de la mémoire pour la structure
    P->degre = x;
	P->couples = (couple*)malloc((P->degre +1)*sizeof(couple));     // Alloue degre+1 couples en mémoire

	return P;       //renvoie ce polynome
}

polynome_couples* poly_couples_mult(polynome_couples *P1, polynome_couples *P2)
{
	int i;
	polynome_couples *P3;       // On créer un nouveau polynome
    P3 = poly_couples_init(P1->degre);      // Alloue la mémoire (on suppose les deux polynomes de même degré)

	for(i=0; i <= P1->degre; i++)
	{
		P3->couples[i].x = P1->couples[i].x;
		P3->couples[i].y = P1->couples[i].y * P2->couples[i].y;     // On multiplie les images des points x par les polynomes
	}

	return P3;      // Renvoie ce polynome
}

void poly_couples_print(polynome_couples *P)
{
	int i;

	printf("\nLes couples sont :");

	for (i = 0; i <= P->degre; i++)     // Pour chaque 0 <= i <= degré
	{
		printf("\nx = ");       // On affiche le point et son image par le polynome
        printfc(P->couples[i].x);
        printf("y = ");
        printfc(P->couples[i].y);
	}
}

polynome_coeff poly_coeff_karatsuba_mult(polynome_coeff A,polynome_coeff B)
{
  int n;
  n= (A.degre>B.degre) ? A.degre:B.degre;
  if (n < 3)    // Si le degré polynome de plus haut degré est inférieur ou égale à deux alors on appelle la multiplication standard
    return poly_coeff_mult(&A, &B);

 n = (n/2);     // On divise le degré par deux

 polynome_coeff A0,A1,B0,B1,Y,U,Z,x,y,w;

 A0 = poly_coeff_firstpart(A,n);        // On recupère la première moitiée du polynome 1
 A1 = poly_coeff_lastpart(A,n);     // On recupère la dernière moitiée du polynome 1

 B0 = poly_coeff_firstpart(B,n);        // On recupère la première moitiée du polynome 2
 B1 = poly_coeff_lastpart(B,n);     // On recupère la dernière moitiée du polynome 1


 Y = poly_coeff_karatsuba_mult(poly_coeff_add(A0,A1),poly_coeff_add(B0,B1));
 U = poly_coeff_karatsuba_mult(A0, B0);
 Z = poly_coeff_karatsuba_mult(A1, B1);

 x = poly_coeff_add(poly_coeff_negative(U), poly_coeff_negative(Z));
 y = poly_coeff_add(x,Y);

 y = poly_coeff_shift(y, n+1);      // On corrige le décalage causé par la séparation en deux des polynomes
 Z = poly_coeff_shift(Z, 2*n+2);

 w = poly_coeff_add(U,y);
 w = poly_coeff_add(w,Z);

 return w;      // On renvoie
 }

polynome_coeff poly_coeff_firstpart(polynome_coeff p, int k)
{
 polynome_coeff r;
 int i;

 if (k<=0)
 {
   r = poly_coeff_create(0);
   return r;
 }

 r = poly_coeff_create(k);      // On créer un nouveau polynome de degré k
 for (i=0; i<=k && i<=p.degre; i++)
 {
   r.coeff[i] = p.coeff[i];     // On recopie les k premiers coéfficients dans ce nouveau polynome
 }

 return r;      // On renvoie ce polynome
}

polynome_coeff poly_coeff_lastpart(polynome_coeff p,int k)
{
  polynome_coeff r;
  int i;

  if (k<0)
  {
    r = poly_coeff_create(0);
    return r;
  }

  r = poly_coeff_create(p.degre-k-1);       // On créer un nouveau polynome de degré k-1
  for (i = 0; i < p.degre-k && i<=p.degre; i++)
  {
    r.coeff[i] = p.coeff[i+k+1];        // On recopie les k-1 derniers coéfficients dans ce nouveau polynome
  }

  return r;     // On renvoie ce polynome

}

polynome_coeff poly_coeff_shift(polynome_coeff p,int k)
{
 int i;
 polynome_coeff r;

 r = poly_coeff_create(p.degre +k);     // On créer un nouveau polynome dont le degré est augmenté de k par rapport au polynome original

 for (i=0; i <= p.degre ;i++)
    r.coeff[k+i]=p.coeff[i];        // On décalle les coéfficients d'un degré k

 return r;      // On renvoie ce polynome
}

polynome_coeff poly_coeff_add(polynome_coeff p,polynome_coeff q)
{
 int i;
 polynome_coeff r;

 if (p.degre>=q.degre)  i=p.degre;
 else i=q.degre;

 r = poly_coeff_create(i);      // On créer un nouveau polynome dont le degré équivaut celui du polynome de plus haut degré

 for (i=0; i <= r.degre;i++)        // Pour chaque i inférieur à ce degré on additionne les coéfficients
 {
     if (i <= p.degre && i <= q.degre)
         r.coeff[i] = p.coeff[i] + q.coeff[i];
     else if (i <= p.degre)
         r.coeff[i] = p.coeff[i];
     else
         r.coeff[i] = q.coeff[i];
 }

 return r;
}

polynome_coeff poly_coeff_negative(polynome_coeff p)
{
  int i;
  polynome_coeff r;
  r = poly_coeff_create(p.degre);   // On créer un nouveau polynome de même degré
  for (i = 0; i <= r.degre; i++)
  {
    r.coeff[i] = -1 * p.coeff[i];       // Pour chaque coéfficient on prend l'opposé
  }
  return r;     // On renvoie ce polynome
}

void poly_coeff_degre_max(polynome_coeff * p)
{
  int i = p->degre;
  while (p->coeff[i] == 0 && i>0)       // Tant que les coéfficients sont nuls, on diminue le degré du polynome
  {
      p->degre--;
      i--;
  }
}

polynome_coeff pair(polynome_coeff P, int n)
{
    int i,c=0;
    polynome_coeff R;
    R = poly_coeff_create((n/2) -1);        // On créer un nouveau polynome
    for (i=0; i<= P.degre; i= i+2)      // On se "déplace" de 2 en 2 en partant de 0 (= pair)
    {
        R.coeff[c] = P.coeff[i];        // On recopie les coéfficients pairs
        c++;
    }
    return R;       // On renvoie ce polynome
}

polynome_coeff impair(polynome_coeff P, int n)
{
    int i,c=0;
    polynome_coeff R;
    R = poly_coeff_create((n/2) -1);        // On créer un nouveau polynome
    for (i=0; i<= P.degre; i++)     // Pour chaque i entre 0 et le degré du polynome
    {
        if (i%2 == 1)       // Si i est impair, alors, on recopie le coéfficient du polynome
        {
            R.coeff[c] = P.coeff[i];
            c++;
        }
    }
    return R;       // On renvoie ce polynome
}

polynome_coeff poly_coeff_create(int degre)
{
    polynome_coeff A;
    A.coeff = (complex *)calloc(sizeof(complex), (size_t) (degre + 1));     // On alloue degre + 1 complexes dans la mémoire
    A.degre = degre;        // Le degré de ce nouveau polynome est degre
    return A;       // On renvoie ce polynome
}

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

polynome_coeff poly_coeff_addcoeff(polynome_coeff P, int x)
{
    polynome_coeff R;
    int i;
    R = poly_coeff_create(P.degre+x);       // On créer un nouveau polynome dont le degré est augmenté de x par rapport au polynome original

    for(i=0; i<= P.degre; i++)
    {
        R.coeff[i] = P.coeff[i];        // On recopie le polynome original
    }

    for (i = P.degre+1; i <=x; i++)     // On mets les coéfficients de degre+1 à 0
    {
        R.coeff[i] = 0;
    }
    return R;       // On renvoie ce polynome
}

polynome_couples poly_couples_fast_mult(polynome_coeff A, polynome_coeff B)
{
    int x;
    polynome_couples *A2, *B2;

    if (A.degre>=B.degre)       // On verifie que les polynomes ont la même taille
    {
				B = poly_coeff_addcoeff(B, A.degre-B.degre + A.degre);    // Si ils n'ont pas la même taille ont augmente la taile du plus petit pour que ce soit le cas
        A = poly_coeff_addcoeff(A, A.degre);
        A2 = poly_couples_init(A.degre +1);     // On créer un nouveau polynome de degre+1 pour pouvoir définir le polynome actuel avec des couples
        B2 = poly_couples_init(B.degre +1);
    }
    else
    {
				A = poly_coeff_addcoeff(A, B.degre - A.degre + B.degre);
        B = poly_coeff_addcoeff(B, B.degre);
        B2 = poly_couples_init(B.degre + 1);
        A2 = poly_couples_init(A.degre + 1);
    }


    A = FFT(A, A.degre +1, A2);     // On passe à la representation couples
    B = FFT(B, B.degre +1, B2);

    A2 = poly_couples_mult(A2, B2);     // On multiplie les couples (O(n))
    return (*A2);       // On renvoie ce polynome
}
