//
//  main.c
//  LearningC
//
//  Created by Milo Moisson on 18/07/2019.
//  Copyright © 2019 Milo Moisson. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "fonctionsTableaux.h"

int main(int argc, const char * argv[]) {
    int DOB[6] = {20, 24, 25, 6, 71, 69};
    int DOBcopie[6];
    
    afficheTableau(DOB, 6);
    printf("--\n");
    printf("%d\n", sommeTableau(DOB, 6));
    printf("--\n");
    printf("%f\n", moyenneTableau(DOB, 6));
    printf("--\n");
    copieTableau(DOB, DOBcopie, 6);
    afficheTableau(DOBcopie, 6);
    printf("--\n");
    ordonnerTableau(DOB, 6);
    afficheTableau(DOB, 6);
    printf("--\n");
//    maximumTableau(DOB, 6, 24);
//    afficheTableau(DOB, 6);
    
    printf("\n\n");
    return 0;
}
