//
//  fonctionsTableaux.c
//  LearningC
//
//  Created by Milo Moisson on 22/07/2019.
//  Copyright © 2019 Milo Moisson. All rights reserved.
//

#include "fonctionsTableaux.h"

void afficheTableau(int tableau[], int tailleTableau) {
    for (int i = 0; i < tailleTableau; i++) {
        printf("%d\n", tableau[i]);
    }
}

int sommeTableau(int tableau[], int tailleTableau) {
    int sommeTableau = 0;
    for (int i = 0; i < tailleTableau; i++) {
        sommeTableau += tableau[i];
    }
    return sommeTableau;
}

double moyenneTableau(int tableau[], int tailleTableau){
    int moyenneTableau =0;
    for (int i = 0; i < tailleTableau; i++) {
        moyenneTableau += tableau[i];
    }
    moyenneTableau /= tailleTableau;
    return moyenneTableau;
}

void copieTableau(int tableauOriginal[], int tableauCopie[], int tailleTableau) {
    for (int i = 0; i < tailleTableau; i++) {
        tableauCopie[i] = tableauOriginal[i];
    }
}

void maximumTableau(int tableau[], int tailleTableau, int valeurMax) {
    for (int i = 0; i < tailleTableau; i++) {
        if (tableau[i] > valeurMax) {
            tableau[i] = 0;
        }
    }
}

void ordonnerTableau(int tableau[], int tailleTableau) {
    int tableauAide[6];
    for (int i = 0; i < tailleTableau; i++) {
		
    }
}
