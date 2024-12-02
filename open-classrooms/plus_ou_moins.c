//
//  main.c
//  LearningC
//
//  Created by Milo Moisson on 18/07/2019.
//  Copyright © 2019 Milo Moisson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

int main(int argc, const char * argv[]) {
    int continuerPartie = 0;
    do {
        printf("Bienvenue au jeu du Plus ou Moins\nCe jeu consiste à trouver un nombre entre:\n");
        printf("1 et 100 au niveau de difficultée 1\n");
        printf("1 et 1000 au niveau de difficultée 2\n");
        printf("1 et 10000 au niveau de difficultée 3\n");
        
        int niveauDeDifficulte = 0;
        int Max = 0, Min = 0;
        printf("\nChoisis ton niveau de difficulté: ");
        scanf("%d", &niveauDeDifficulte);
        if (niveauDeDifficulte == 1) {
            Max = 100;
            Min = 1;
            printf("Je suis sur que tu pourra prendre un autre niveau de difficultée au prochain tour.\n");
        } else if (niveauDeDifficulte == 2) {
            Max = 1000;
            Min = 1;
            printf("Conciencieux, humm...\n");
        } else if (niveauDeDifficulte == 3) {
            Max = 10000;
            Min = 1;
            printf("Tu cherche la difficultée c'est ça?\n");
        } else {
            Max = 100;
            Min = 1;
            printf("Ton niveau à été mis à 1.\n");
        }
        
        
        srand(time(NULL));
        int nombreMystere = (rand() % (Max - Min + 1)) + Min;
        int nombreEntre = 0;
        signed int nombreDeCoups = 0;
        do {
            printf("Quel est le nombre ? ");
            scanf("%d", &nombreEntre);
            if (nombreEntre == nombreMystere) {
                nombreDeCoups++;
                printf("%d Coups\n\n", nombreDeCoups);
                break;
            } else if (nombreEntre <= nombreMystere) {
                printf("C'est plus\n");
                nombreDeCoups++;
                printf("%d Coups\n\n", nombreDeCoups);
            } else if (nombreEntre >= nombreMystere) {
                printf("C'est moins\n");
                nombreDeCoups++;
                printf("%d Coups\n\n", nombreDeCoups);
            }
        } while (nombreEntre != nombreMystere);
        printf("Bravisimo, tu a trouvé le nombre mystère en %d coups!!!\n", nombreDeCoups);
        
        int continuerPartieQuestion = 0;
        printf("Veut-tu continuer la partie ? (0 pour Non ou 1 pour Oui): ");
        scanf("%d", &continuerPartieQuestion);
        printf("\n");
        if (continuerPartieQuestion == 0) {
            printf("Merci d'avoir joué!");
            continuerPartie = 0;
        } else if (continuerPartieQuestion == 1) {
            printf("Et c'est reparti pour une autre partie!!!\n");
            continuerPartie = 1;
        } else {
            printf("Merci d'avoir joué!");
            continuerPartie = 0;
        }
        
    } while (continuerPartie);

    printf("\n\n");
    return 0;
}
