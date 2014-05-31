#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

/** 
 * @mainpage Calendrier Maya
 * @author Jude Séide
 * 
 * Ce projet contient les routines necessaires a la conversion d'une date posterieure a 11 8 -3113
 * (11 aout -3113) et ulterieur a 12 10 4772 (12 Octobre 4772) de notre calendrier grégorien moderne
 * en calendrier Maya Compte long, Haab et Tzolkin
 * le programme prend en entree une date de format JJ MM YYYY et produit la conversion en Maya
 */

/**
* Tableau definissant les mois du calendrier Maya Haab
*/
const char* HAAB[] = {"Pop","Wo","Sip","Sotz'","Sek","Xul","Yaxk'in","Mol","Ch'en","Yax","Sak","Keh","Mak","K'ank'in","Muwan","Pax","K'ayab","Kumk'u","Wayeb"};

/**
* Tableau definissant les mois du calendrier Maya Tzolkin
*/
const char*  TZOLKIN[] = {"Imix","Ik","Akbal","Kan","Chicchan","Cimi","Manik","Lamat","Muluc","Oc","Chuen","Eb","Ben","Ix","Men","Cib","Caban","Etznab","Cauac","Ahau"};

/**
 * Calcule le nombre de jours la date min ( 11 8 -3113 )et l'annee zero.
 * @return un entier indiquant le nombre le nombre de jours.
 */
int nbJourMaya(){
    int maya = 0, anneBissextile = 0, nonBissextile = 0;
    anneBissextile = nombreAnneeBissextile(0, 3112) ;
    nonBissextile = 3112 - anneBissextile ; // 3112 annee suivant l'anne de la date min
    maya += ((anneBissextile * 366) + (nonBissextile * 365));
    maya += 142; // nbr de jour a recuperer pour atteindre la date min
    return maya;
}

/**
 * Calcule le nombre d'annees bissextiles dans une intervalle d'annees donnee.
 * @param un entier annee1 determinant l'annee de debut de l'intervalle.
 * @param un entier annee2 determinant l'annee de fin de l'intervalle.
 * @return un entier indiquant le nombre d'annees bissextiles
 */
int nombreAnneeBissextile(int annee1, int annee2){
    int nbAnnee = 0, intervalle = 0;
    intervalle = annee2 - annee1 ;
    nbAnnee = (intervalle / 4) - ((intervalle / 100) - (intervalle / 400));
    return nbAnnee;
}

/**
 * Determine si une annee est bissextile ou pas.
 * une annee est bissextile si elle divisible par 4 et non par 100
 * ou si elle est divisible par 100
 * @param un entier correspondant au mois donne.
 * @return un entier indiquant 1 si l'annee est bissextile sinon 0.
 */
int bissextile(int annee){
    int valide = 0;
    if((annee % 4 == 0 && annee % 100 != 0) || annee % 400 == 0){
        valide = 1;
    }
    return valide;
}

/**
 * Determine le nombre de jours que comporte un mois donne en fonction de l'annee.
 * Mois (1,3,5,7,8,10,12) : Jours [1...31] , mois (4,6,9,11) : jours [1...30]
 * Mois (2) : jours [1...29] si l'annee est bissextile sinon mois (2) : jours[1...28]
 * @param un entier determinant le mois.
 * @param un entier determinant l'annee.
 * @return un entier indiquant le nombre de jours dans le mois en question.
 */
int nbJourMois(int mois, int annee){
    int nbJour = 0;
    if(mois == 1 || mois == 3 || mois == 5 || mois == 7 || mois == 8 || mois == 10 || mois == 12){
            nbJour = 31;
    }else if (mois == 4 || mois == 6 || mois == 9 || mois == 11) {
            nbJour = 30;
    } else if (mois == 2){
        if (bissextile(annee)){
            nbJour = 29;
        }else{
            nbJour = 28;
        }
    }
    return nbJour;
}

/**
 * Determine le nombre de jours entre une date donnee et la date min 11 8 -3113
 * @param un entier determinant le jour.
 * @param un entier determinant le mois.
 * @param un entier determinant l'annee.
 * @return un entier: le nombre de jours dans cette intervalle
 */
int nbJour_DateMin(int jour, int mois1, int annee,const int MAYA){
    int nbJour = 0, anneBissextile = 0, nonBissextile = 0;

    if(jour == 11 && mois1 == 8 && annee == -3113){
        nbJour = 0;
    }else if(annee > 0){
        anneBissextile = nombreAnneeBissextile(1, annee);
        nonBissextile = annee - anneBissextile ;
        nbJour += ((anneBissextile * 366) + (nonBissextile * 365));
        int mois = 0;
        for(mois = 1; mois < mois1; ++mois){
            nbJour += nbJourMois(mois, annee);
        }
        nbJour += (jour + 1 + MAYA);
    }else{
        nbJour = 0;
        int annee1 = -(annee);
        --annee1;
        anneBissextile = nombreAnneeBissextile(1, annee1);
        nonBissextile = annee1 - anneBissextile;
        nbJour += ((anneBissextile * 366) + (nonBissextile * 365));
        int mois = 0;
        for(mois = 12; mois > mois1; --mois){
            nbJour += nbJourMois(mois, annee1);
        }
        nbJour += (nbJourMois(mois, annee) - jour + 1);
        int temp = MAYA - nbJour;
        nbJour = temp ;
    }
    return nbJour;
}

/**
 * Valide l'annee saisie.
 * L'annee est valide si elle est comprise entre -3113 et 4772 inclusivement
 * @param un entier correspondant a l'annee donnee.
 * @return un entier indiquant 1 si l'annee est valide sinon 0.
 */
int validerAnnee (int annee){
    int valide = 0;
    if (annee >= -3113 && annee <= 4772){
        valide = 1;
    }
    return valide;
}

/**
 * Valide le mois saisi
 * Le mois est valide s'il est compris entre 1 et 12 inclusivement
 * @param un entier correspondant au mois donne.
 * @return un entier indiquant 1 si le mois est valide sinon 0.
 */
int validerMois (int mois){
    int valide = 0;
    if (mois >= 1 && mois <= 12){
        valide = 1;
    }
    return valide;
}

/**
 * Determine si le jour est valide en fonction du mois et de l'annee.
 * Un jour est valide s'il est compris inclusivement entre 1 et le max du mois
 * @param un entier correspondant au jour.
 * @param un entier correspondant au mois.
 * @param un entier correspondant a l'annee.
 * @return un entier indiquant 1 si le jour est valide sinon 0.
 */
int validerJour(int jrs, int mois, int annee){
    int valide = 0, maxJour = 0;
    maxJour = nbJourMois(mois, annee);
    if (jrs >= 1 && jrs <= maxJour){
            valide = 1;
    }
    return valide;
}

/**
 * Determine si la date est valide .
 * La date est valide si elle est comprise entre 11 Aout -3113 et 12 Octobre 4772
 * @param un entier correspondant au jour.
 * @param un entier correspondant au mois.
 * @param un entier correspondant a l'annee.
 * @return un entier indiquant 1 si l'annee est valide sinon 0.
 */
int valider_dateMin_dateMax (int jrs, int mois, int annee){
    int valide = 1;
    if(-3113 == annee ){
        if(mois < 8){
            valide = 0;
        }else if(mois == 8){
            if(jrs <= 10){
                valide = 0;
            }
        }
    }else if(4772 == annee ){
        if(mois > 10){
            valide = 0;
        }else if(mois == 10){
            if(jrs > 12){
                valide = 0;
            }
        }
    }
    return valide;
}

/**
 * Traduit une date du calendrier gregorien vers le calendrier compte long et l'affiche.
 * @param une contante entier correspondant au nombre de jours
 * compris entre la date minimale valide et la date saisie
 */
void compteLong(const int nbJour){
    int kin = 0, uinal = 0, tun = 0, katun = 0, naktun = 0, temp = 0;
    int nbreJour = nbJour;
    if(nbreJour == 0){
        printf("Compte long : 0.0.0.0.0\n");
    }else if(nbreJour > 0){
        naktun = nbreJour / 144000;
        temp = nbreJour % 144000;

        if(temp > 0){
            katun = temp / 7200;
            temp %= 7200;
            if(temp > 0){
                tun = temp / 360;
                temp %= 360;
                if(temp > 0){
                    uinal = temp / 20;
                    kin = temp % 20;
                }
            }
        }
     printf("Compte long : naktun %d. katun %d. tun %d. uinal %d. kin %d\n",naktun,katun,tun,uinal,kin);
    }
}

/**
 * Traduit une date du calendrier gregorien vers le calendrier haab et l'affiche.
 * @param une contante entier correspondant au nombre de jours
 */
void haab(const int nbJour){
     int nbreJour = nbJour;
     nbreJour += 348;
     //pour initialiser l'annee au 8 kumk'u
     if(nbreJour == 0){
            printf("Haab : 8 Kumk'u\n");
     }else{
            nbreJour %= 365;
            int moisHaab = nbreJour / 20;
            int jourHaab = nbreJour % 20;
            printf("Haab : %d %s\n",jourHaab, HAAB[moisHaab]);
     }
}

/**
 * Traduit une date du calendrier gregorien vers le calendrier Tzolk'in et l'affiche.
 * @param une contante entier correspondant au nombre de jours
 */
void tzolkin(const int nbJour){
     int nbreJour = nbJour;
     if(nbreJour == 0){
            printf("Tzolk'in : 4 Ahau\n");
     }else{
            int valeurTzolkin = 0;
            int i = 0;
            nbreJour %= 260;

            valeurTzolkin = nbreJour % 20 - 1;
            
            //pour avoir l'index dans le tableau
            if(valeurTzolkin == -1){
                valeurTzolkin = 19;
            }
            //pour gerer le cas de la fin du cycle
            int jourTzolkin = 4;
            //pour initialiser au 4 Ahau
            int hebdo = nbreJour % 13;
            
            if(hebdo == 0){
                jourTzolkin -= 1;
            }
            
            for(i; i < hebdo; ++i){
                if(jourTzolkin > 13){
                    jourTzolkin = 1;
                }else{
                    ++jourTzolkin;
                }
            }
        printf("Tzolk'in : %d %s\n",jourTzolkin, TZOLKIN[valeurTzolkin]);
     }
}

int main(int argc, char **argv){

    if (argc != 4){
        fprintf (stderr, "Erreur : Nombres d'arguments incorrects !\n");
        exit (-1);
    }

    int jours = atoi(argv[1]);
    int mois = atoi(argv[2]);
    int annee = atoi(argv[3]);

    if (!validerJour(jours, mois, annee)){
        fprintf (stderr, "Erreur : jour invalide !\n");
        exit (-1);
    }

    if (!validerMois(mois)){
        fprintf (stderr, "Erreur : mois invalide !\n");
        exit (-1);
    }

    if (!validerAnnee(annee)){
        fprintf (stderr, "Erreur : annee invalide !\n");
        exit (-1);
    }

    if (!valider_dateMin_dateMax(jours, mois, annee)) {
        fprintf (stderr, "Erreur : date invalide !\n");
        exit (-1);
    }

    int const MAYA = nbJourMaya();
    int const nbJour = nbJour_DateMin(jours,mois,annee, MAYA);

    compteLong(nbJour);
    haab(nbJour);
    tzolkin(nbJour);

    return 0;
}
