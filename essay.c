#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#ifdef _WIN32
    #include <windows.h>
    #define SLEEP_MS(x) Sleep(x)
#else
    #include <unistd.h>
    #define SLEEP_MS(x) usleep(x * 1000)
#endif

/**variables generales**/

int main_exit;
int choix;
char idm[10];
char ids[10];

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**fonction pour positionner l'affichage**/
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
/**fonction pour changer de la couleur bg et texte**/
void setcolor(int textcolor, int bgcolor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolor + (bgcolor << 4));}
/**fonction pour changer de la couleur text unique**/
void setcolortxt(int textcolor) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), textcolor );}
/**fonction pour attendre une periode de temps avant l'affichage**/
void delay(int milliseconds) {
    SLEEP_MS(milliseconds);
}
/**fonction pour masquer le mot de passe**/
 void maskPassword(int *password) {
    *password = 0;
    char ch;
    while (1) {
        ch = getch();
        if (ch == '\r' || ch == '\n') {
            break;
        }
        putchar('*');
        *password = *password * 10 + (ch - '0');
    }
    printf("\n");
}
/**fonction pour quitter**/
void close(){
system("cls");
setcolortxt(15);
gotoxy(92,10);
printf("Mission finiched");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**les structures utilisées**/
/**structure qui definit la date de naissance**/
typedef struct DDN{
   int j;
   int m;
   int a;
}DDN;

 /**structure qui definit le role de medecin**/
typedef struct medeciin{
  char nommaladie[200];
  char antecedents[500];
  char statut[100];
  }medeciin;

/**structure qui definit le patient**/
 typedef struct Patient{
 char NOM[50];
 char PRENOM[50];
 char CIN[10];
 long N_telephone;
 DDN DP;
 char adresse[200];
 medeciin M;
 char medic[20000];
 }patient;

 /**structure qui definit le rendez-vous d'une personne**/
 typedef struct Personne{
 char NOM[50];
 char PRENOM[50];
 char CIN[10];
 DDN date_RV;
 int NUM_RV;
 }personne;

 /**structure qui definit la facture**/
 typedef struct Facture{
char NOM[100];
char CIN[20];
DDN date_payement;
float montant;
float paye;
float restant;
 }facture;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/**les fcts du medecin**/
/**fonction du medecin (l'authentification )**/
void medecin(){
    system("cls");
 int motm;
 char idm2[10];
 int motm2;
 patient P;
 FILE *fpm;
 fpm=fopen("medecin.txt","r");
 if(fpm==NULL){
    printf("erreur");
    exit(1);
 }
 int m=0;
 while(fscanf(fpm,"%s\n%d",idm2,&motm2)==2){
    do{
        if(m!=0){
        setcolortxt(4);
        gotoxy(85,8);
        printf("--Vos infos ne sont pas valides--\n\n");}
        setcolortxt(15);
        gotoxy(85,10);
        printf("**  L'identifiant   :  ");
        scanf("%s",idm);
        fflush(stdin);
        gotoxy(85,12);
        printf("**  Mot_De_Passe    :  ");
        maskPassword(&motm);
        system("cls");
        m++;
        }while((strcmp(idm2, idm) != 0) || (motm2 != motm));}
  fclose(fpm);
  menumedecin(&idm);
 }


 /**fonction de menu du medecin**/
 void menumedecin( char *n){
     patient P;
    int choix;
   setcolor(0,15);
   gotoxy(87,5);
  printf("--  Bienvenue monsieur %s --",n);
  gotoxy(80,10);
  setcolortxt(15);
  printf("---- 1: CONSULTATION & ORDONNANCE ----");
  gotoxy(80,12);
  printf("---- 2: DOSSIER MEDICAL ----");
  gotoxy(90,19);
  setcolortxt(9);
  printf("---> Entrer Votre Choix:");
  scanf("%d",&choix);
  switch(choix){
    case 1:
     consultation();
    break;
    case 2:
     menudoss(&idm);
     break;

    default:{
    setcolortxt(4);
    gotoxy(76,22);
    printf("<!> VEUILLEZ CHOISIR UN NOMBRE ENTRE 1 ET 3");
    delay(1200);
    system("cls");
    menumedecin(n);
  }}
 }

 /**fonction de consultation et ordonnance**/
 void consultation(){
     char line[200];
     FILE *fmp = fopen("dm.txt", "a+");
     if (fmp == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
     FILE *FP = fopen("patient.txt", "r");
     if (FP == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
     char cin_p[20];
     int i,n; patient P;
     system("cls");
     setcolortxt(9);
     gotoxy(80,1);
     printf("*Le CIN du patient ");
     scanf("%s",&cin_p);
     int c=0;
     while(fgets(line, sizeof(line), FP) != NULL) {
    sscanf(line, "%[^\n]", P.NOM);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%[^\n]",P.PRENOM);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%[^\n]", P.CIN);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%d\n",&P.N_telephone);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%d %d %d\n",&P.DP.j, &P.DP.m,&P.DP.a);
    fgets(line, sizeof(line), FP);
    sscanf(line, "%[^\n]", P.adresse);
        if(strcmp(cin_p,P.CIN)==0){
            c++;
             setcolortxt(15);
            fprintf(fmp,"%s\n%s\n%s\n%d\n%d %d %d\n%s\n",P.NOM,P.PRENOM,P.CIN,P.N_telephone,P.DP.j,P.DP.m,P.DP.a,P.adresse);
            gotoxy(81,3);
            printf("-Nom de maladie: ");
            fflush(stdin);
            gets(P.M.nommaladie);
            gotoxy(81,5);
            printf("-Les precedents du patient: ");
            fflush(stdin);
            gets(P.M.antecedents);
            gotoxy(81,7);
            printf("-Statut de maladie: ");
            fflush(stdin);
            gets(P.M.statut);
            fprintf(fmp,"%s\n%s\n%s\n",P.M.nommaladie,P.M.antecedents,P.M.statut);
            gotoxy(81,9);
            setcolortxt(9);
            printf("*L'ordonnance : ");
            gotoxy(81,11);
             setcolortxt(15);
            printf("-Le nombre des medicaments: ");
            scanf("%d",&n);
            for(i=0;i<n;i++){
            printf("\n");
            printf("                                                                                 --Le medicament %d :",i+1);
            fflush(stdin);
            gets(P.medic);
            fprintf(fmp,"%s ",P.medic);
            printf("\n");
            printf("                                                                                  -- Son traitement : ");
            fflush(stdin);
            gets(P.medic);
            fprintf(fmp,"%s ",P.medic);
            }
            //fprintf(fmp,"\n");
            fclose(fmp);
            view_list_invalid:
            gotoxy(85,22);
            printf("      <-- : 1   ||   0 : --> \n");
            gotoxy(85,24);
            scanf("%d",&main_exit);
            system("cls");
            if(main_exit==1)
            menumedecin(&idm);
            else if (main_exit==0)
            close();
            else{
                printf("invalid!");
                goto view_list_invalid;
            }
        }

        }
        if (c==0){
            gotoxy(80,7);
            printf("----CIN INTROUVABLE----");
            delay(1500);
            consultation();
            fclose(fmp);}

}

/**fonction du menu du dosiier**/
void menudoss(char *n){
    system("cls");
    setcolor(0,15);
   gotoxy(87,5);
  printf("--  Bienvenue monsieur %s --",n);
    int choix;
     gotoxy(80,10);
    setcolortxt(15);
  printf("---- 1: AFFICHER DOSSIER MEDICAL ----");
  gotoxy(80,12);
  printf("---- 2: MODIFIER STATUT ----");
  gotoxy(90,19);
  setcolortxt(9);
  printf("---> Entrer Votre Choix:");
  scanf("%d",&choix);
  switch(choix){
    case 1:
     dossiermedi();
    break;
    case 2:
     modifier();
     break;
    default:{
    setcolortxt(4);
    gotoxy(76,22);
    printf("<!> VEUILLEZ CHOISIR 1 OU 2");
    delay(1200);
    system("cls");
    menudoss(&idm);
  }}
     view_list_invalid:
            gotoxy(85,22);
            printf("      <-- : 1   ||   0 : --> \n");
            gotoxy(85,24);
            scanf("%d",&main_exit);
            system("cls");
            if(main_exit==1)
            menumedecin(&idm);
            else if (main_exit==0)
            close();
            else{
                printf("invalid!");
                goto view_list_invalid;
            }

 }


/**fonction de l'affichage dossier medical**/
void dossiermedi(){
    system("cls");
    setcolortxt(15);
    char cin_p[20];
    patient P;
    gotoxy(80,5);
    printf(" Entrer le CIN du patient ");
    scanf("%s",&cin_p);
    int c=0;
    FILE *fmp = fopen("dm.txt", "r");
     if (fmp == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
    int i;
    char line[200];
    while (fgets(line, sizeof(line), fmp) != NULL) {
    sscanf(line, "%[^\n]", P.NOM);
    fgets(line, sizeof(line),fmp);
    sscanf(line, "%[^\n]",P.PRENOM);
    fgets(line, sizeof(line),fmp);
    sscanf(line, "%[^\n]", P.CIN);
    fgets(line, sizeof(line),fmp);
    sscanf(line, "%d\n",&P.N_telephone);
    fgets(line, sizeof(line),fmp);
    sscanf(line, "%d %d %d\n",&P.DP.j, &P.DP.m,&P.DP.a);
    fgets(line, sizeof(line), fmp);
    sscanf(line, "%[^\n]", P.adresse);
    fgets(line, sizeof(line), fmp);
    sscanf(line, "%[^\n]", P.M.nommaladie);
    fgets(line, sizeof(line), fmp);
    sscanf(line, "%[^\n]", P.M.antecedents);
    fgets(line, sizeof(line), fmp);
    sscanf(line, "%[^\n]",P.M.statut);
    fgets(line, sizeof(line), fmp);
    sscanf(line, "%[^\n]",P.medic);
    sscanf(P.NOM, "%[^\n]", P.NOM);
    sscanf(P.PRENOM, "%[^\n]", P.PRENOM);
    sscanf(P.CIN, " %s", P.CIN);
         if(strcmp(cin_p,P.CIN)==0){
            c++;
            gotoxy(80,7);
            printf("Le dossier medical du patient ayant ");
            gotoxy(80,8);
            printf("CIN '%s' est comme suit : ",P.CIN);
            gotoxy(80,10);
            printf("NOM: %s",P.NOM);
            gotoxy(80,11);
            printf("PRENOM: %s",P.PRENOM);
            gotoxy(80,12);
            printf("CIN: %s",P.CIN);
            gotoxy(80,13);
            printf("N TELEPHONE: %d",P.N_telephone);
            gotoxy(80,14);
            printf("DATE DE NAISSANCE: %d %d %d",P.DP.j,P.DP.m,P.DP.a);
            gotoxy(80,15);
            printf("ADRESSE: %s",P.adresse);
            gotoxy(80,16);
            printf("MALADIE: %s",P.M.nommaladie);
            gotoxy(80,17);
            printf("PRECEDENTS: %s",P.M.antecedents);
            gotoxy(80,18);
            printf("STATUT: %s",P.M.statut);
            gotoxy(80,19);
            printf("MEDIC & TRAITEMENT: \n                                                                             %s",P.medic);

        }}
    if(c==0){
        gotoxy(80,7);
        printf("----CIN INTROUVABLE----");
        delay(1500);
        dossiermedi();}
    view_list_invalid:
    gotoxy(85,22);
    printf("      <-- : 1   ||   0 : --> \n");
    gotoxy(85,24);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menudoss(&idm);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
    fclose(fmp);

}

/**fonction qui modifie le statut**/
 void modifier(){
     int i;
     char line[200];
     char cin_p[122];
     FILE *fmp = fopen("dm.txt", "r");
     if (fmp == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
    FILE *temp = fopen("temp.txt", "w");
     if (temp == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
    int c=0;
     patient P;
     system("cls");
     setcolortxt(15);
     gotoxy(80,5);
     printf("Le CIN du patient ");
     scanf("%s",&cin_p);
     gotoxy(80,7);
     while (fgets(line, sizeof(line), fmp) != NULL) {
        sscanf(line, "%[^\n]", P.NOM);
        fgets(line, sizeof(line),fmp);
        sscanf(line, "%[^\n]",P.PRENOM);
        fgets(line, sizeof(line),fmp);
        sscanf(line, "%[^\n]", P.CIN);
        fgets(line, sizeof(line),fmp);
        sscanf(line, "%d\n",&P.N_telephone);
        fgets(line, sizeof(line),fmp);
        sscanf(line, "%d %d %d\n",&P.DP.j, &P.DP.m,&P.DP.a);
        fgets(line, sizeof(line), fmp);
        sscanf(line, "%[^\n]", P.adresse);
        fgets(line, sizeof(line), fmp);
        sscanf(line, "%[^\n]", P.M.nommaladie);
        fgets(line, sizeof(line), fmp);
        sscanf(line, "%[^\n]", P.M.antecedents);
        fgets(line, sizeof(line), fmp);
        sscanf(line, "%[^\n]",P.M.statut);
        fgets(line, sizeof(line), fmp);
        sscanf(line, "%[^\n]",P.medic);
        if(strcmp(cin_p,P.CIN)==0){
                c++;
          printf("Le nouveau statut : ");
          fflush(stdin);
          gets(P.M.statut);
        }
        fprintf(temp,"%s\n%s\n%s\n%d\n%d %d %d\n%s\n%s\n%s\n%s\n%s\n",P.NOM,P.PRENOM,P.CIN,P.N_telephone,P.DP.j,P.DP.m,P.DP.a,P.adresse,P.M.nommaladie,P.M.antecedents,P.M.statut,P.medic);
        }
        if (c==0){
        gotoxy(80,7);
        printf("----CIN INTROUVABLE----");
        delay(1500);
        dossiermedi();}
        fclose(fmp);
        fclose(temp);
        remove("dm.txt");
        rename("temp.txt","dm.txt");
 }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**les fcts de la secretaire**/
/**menu de secretaire**/
void menu_secrtaire(char*n){
patient P;
personne p;
facture F;
int main_exit;
int fonction;
int choix;
setcolor(0,15);
gotoxy(85,2);
printf("--  Bienvenue secretaire %s --",n);
gotoxy(85,4);
setcolortxt(15);
printf("----  1:GESTION RENDEZ-VOUS   ----");
gotoxy(85,6);
printf("----  2:GESTION PATIENT   ----");
gotoxy(85,8);
printf("----  3:GESTION DE COMTABILITE ----");
gotoxy(85,10);
printf("----  4:CHERCHER UN PATIENT ----");
gotoxy(85,12);
printf("----  5:AFFICHER UN RENDEZ-VOUS ---");
gotoxy(85,14);
printf("----  6:AFFICHER UNE FACTURE ---");
gotoxy(85,16);
printf("----  7:SUPPRIMER UN RENDEZ-VOUS --");
gotoxy(90,19);
setcolortxt(9);
printf("---> Entrer Votre Choix:");
scanf("%d",&fonction);
system("cls"); // Efface la console sur Windows
 switch(fonction){
 case 1:GestionRD(p);
    break;
 case 2:GestionPatient(P);
     break;
 case 3:
    GestionCompt(F);
     break;
 case 4 :
    AffichePatient()  ;
     break;
 case 5 :
    afficheRV();
    break;
 case 6:
    AfficheFacture();
    break;
 case 7:
     SupprimerRV();
    break;
 default:
      {setcolortxt(4);
      gotoxy(76,22);
      printf("<!> VEUILLEZ CHOISIR UN NOMBRE ENTRE 1 ET 7");
      delay(1500);
      system("cls");
      menu_secrtaire(&ids);
      }
      }

 }



 /**fct qui affiche un patient**/
 void AffichePatient(){
 patient P;
 FILE *FP;
 char cin[10];
 setcolortxt(15);
 gotoxy(78,8);
 printf("Veuillez entrer le CIN du patient :");
 gotoxy(80,10);
 fflush(stdin);
 scanf("%s",cin);
 system("cls");
 FP=fopen("patient.txt","r");
   if(FP==NULL){
    printf("erreur");
    exit(1);}
int count = 0;
char line[200];  // Adjust MAX_LINE_SIZE according to your needs

while (fgets(line, sizeof(line), FP) != NULL) {
    sscanf(line, "%[^\n]", P.NOM);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%[^\n]",P.PRENOM);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%[^\n]", P.CIN);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%d\n",&P.N_telephone);
    fgets(line, sizeof(line),FP);
    sscanf(line, "%d %d %d\n",&P.DP.j, &P.DP.m,&P.DP.a);
    fgets(line, sizeof(line), FP);
    sscanf(line, "%[^\n]", P.adresse);
    if ((strcmp(cin,P.CIN) == 0)) {
        printf("                                                                             ----------------------------------------\n");
        printf("                                                                            * NOM : %s\n", P.NOM);
        printf("                                                                            * PRENOM : %s\n", P.PRENOM);
        printf("                                                                            * CIN : %s\n", P.CIN);
        printf("                                                                            * NUMERO DE TELE: %d\n", P.N_telephone);
        printf("                                                                            * DATE DE NAISSANCE: %d %d %d\n", P.DP.j, P.DP.m, P.DP.a);
        printf("                                                                            * ADRESSE:%s\n", P.adresse);
        printf("                                                                             ----------------------------------------\n");
        count = 1;
    }
}

if (!count) {
       gotoxy(85,9);
    printf("!Aucun patient pour ce CIN!\n");
}
fclose(FP);
view_list_invalid:
    gotoxy(85,18);
    printf("      <-- : 1   ||   0 : --> \n");
    fflush(stdin);
    gotoxy(85,20);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}


/**fct qui affiche un rendez-vous**/
void afficheRV(){
FILE *RV;
DDN DR;
personne p;
setcolortxt(15);
gotoxy(78,8);
printf("Veuillez entrer la date de rendez-vous :");
gotoxy(79,10);
setcolortxt(9);
scanf("%d %d %d",&DR.j,&DR.m,&DR.a);
system("cls");
RV=fopen("RendezVous.txt","r");
    if(RV==NULL)
    {
        gotoxy(76,14);
        printf("Fichier introuvable!!");
        exit(1);
    }
int rendezVousTrouves = 0;
setcolortxt(15);
printf("                                                                            ----> Rendez-vous pour la date %d/%d/%d\n\n", DR.j, DR.m, DR.a);
 while (fscanf(RV,"%[^\n]\n%[^\n]\n%[^\n]\n%d %d %d\n%d\n", p.NOM, p.PRENOM, p.CIN, &p.date_RV.j, &p.date_RV.m, &p.date_RV.a, &p.NUM_RV) ==7) {
        if (DR.j == p.date_RV.j && DR.m == p.date_RV.m && DR.a == p.date_RV.a) {
            printf("                                                                            * NOM : %s\n", p.NOM);
            printf("                                                                            * PRENOM : %s\n", p.PRENOM);
            printf("                                                                            * CIN : %s\n", p.CIN);
            printf("                                                                            * DATE DE RENDEZ-VOUS : %d %d %d\n", p.date_RV.j, p.date_RV.m, p.date_RV.a);
            printf("                                                                            * NUMERO DE RENDEZ-VOUS: %d\n", p.NUM_RV);
            setcolortxt(9);
            printf("                                                                             ----------------------------------------\n");
            setcolortxt(15);
            rendezVousTrouves = 1;
        }
    }

    if (!rendezVousTrouves) {
        gotoxy(85,9);
        printf("!Aucun rendez-vous pour cette date!.\n");
    }
    fclose(RV);
view_list_invalid:
    gotoxy(85,22);
    printf("      <-- : 1   ||   0 : --> \n");
    gotoxy(85,24);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}


/**fct qui affiche une facture**/
void AfficheFacture(){
char cin[20];
facture F;
FILE *FF;
setcolortxt(15);
gotoxy(78,8);
printf("Veuillez entrer le CIN du patient :");
gotoxy(80,10);
fflush(stdin);
gets(cin);
system("cls");
 FF=fopen("factures.txt","r");
   if(FF==NULL){
    printf("erreur");
    exit(1);}
int count = 0;
char line[200];  // Adjust MAX_LINE_SIZE according to your needs

while (fgets(line, sizeof(line), FF) != NULL) {
    sscanf(line, "%[^\n]",F.NOM);
    fgets(line, sizeof(line),FF);
    sscanf(line, "%[^\n]",F.CIN);
    fgets(line, sizeof(line),FF);
    sscanf(line, "%d %d %d\n",&F.date_payement.j,&F.date_payement.m,&F.date_payement.a);
    fgets(line, sizeof(line),FF);
    sscanf(line, "%f\n",&F.montant);
    fgets(line, sizeof(line),FF);
    sscanf(line, "%f\n",&F.paye);
    fgets(line,sizeof(line),FF);
    sscanf(line,"%f\n",&F.restant);
    if ((strcmp(cin,F.CIN) == 0)) {
        printf("                                                                             ----------------------------------------\n");
        printf("                                                                            * NOM : %s\n", F.NOM);
        printf("                                                                            * CIN: %s\n", F.CIN);
        printf("                                                                            * DATE DE PAYEMENT: %d %d %d\n",F.date_payement.j,F.date_payement.m,F.date_payement.a);
        printf("                                                                            * MONTANT:%.2f\n",F.montant);
        printf("                                                                            * PAYE:%.2f\n", F.paye);
        printf("                                                                            * RESTANT:%.2f\n",F.restant);
        printf("                                                                             ----------------------------------------\n");
        count = 1;
    }
}

if (!count) {
    gotoxy(85,9);
    printf("!Aucun facture pour ce CIN!\n");
}
fclose(FF);
view_list_invalid:
    gotoxy(85,18);
    printf("      <-- : 1   ||   0 : --> \n");
    fflush(stdin);
    gotoxy(85,20);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}

/**fct qui supprime un rendez-vous**/
void SupprimerRV(){
FILE *RV;
char CIN[20];
RV=fopen("RendezVous.txt","r");
 if(RV==NULL)
    {
        gotoxy(76,14);
        printf("Fichier introuvable!!");
        exit(1);
    }
FILE *temp = fopen("temp.txt", "w");
     if (temp == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
personne p;
system("cls");
setcolortxt(15);
gotoxy(80,5);
printf("Veuillez entrer le CIN:\n");
fflush(stdin);
gotoxy(80,7);
gets(CIN);
gotoxy(80,9);
setcolortxt(9);
printf("Le rendez-vous est supprime avec succes!");
while (fscanf(RV,"%[^\n]\n%[^\n]\n%[^\n]\n%d %d %d\n%d\n", p.NOM, p.PRENOM, p.CIN, &p.date_RV.j, &p.date_RV.m, &p.date_RV.a, &p.NUM_RV) ==7) {
        if(strcmp(CIN,p.CIN)!=0){
            fprintf(temp,"%s\n%s\n%s\n%d %d %d\n%d\n",p.NOM,p.PRENOM,p.CIN,p.date_RV.j,p.date_RV.m,p.date_RV.a,p.NUM_RV);
}}
fclose(RV);
fclose(temp);
remove("RendezVous.txt");
rename("temp.txt","RendezVous.txt");
view_list_invalid:
    gotoxy(85,22);
    setcolortxt(15);
    printf("      <-- : 1   ||   0 : --> \n");
    gotoxy(85,24);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}

/**fonction de gestion de patient par la secretaire**/
void GestionPatient(patient P){
gotoxy(85,4);
setcolortxt(1);
fflush(stdin);
printf("-->LE NOM: ");
setcolortxt(15);
gets(P.NOM);
gotoxy(85,6);
setcolortxt(1);
printf("-->LE PRENOM: ");
setcolortxt(15);
gets(P.PRENOM);
gotoxy(85,8);
setcolortxt(1);
printf("-->CIN: ");
setcolortxt(15);
gets(P.CIN);
fflush(stdin);
gotoxy(85,10);
setcolortxt(1);
printf("-->N° TELEPHONE: ");
setcolortxt(15);
scanf("%d",&P.N_telephone);
gotoxy(85,12);
fflush(stdin);
setcolortxt(1);
printf("-->DATE DE NAISSANCE: ");
setcolortxt(15);
fflush(stdin);
scanf("%d %d %d",&P.DP.j,&P.DP.m,&P.DP.a);
gotoxy(85,14);
setcolortxt(1);
printf("-->ADRESSE: ");
setcolortxt(15);
fflush(stdin);
gets(P.adresse);
FILE *FP = fopen("patient.txt", "a");
int main_exit;
if (FP == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }
fprintf(FP,"%s\n",P.NOM);
fprintf(FP,"%s\n",P.PRENOM);
fprintf(FP,"%s\n",P.CIN);
fprintf(FP,"%d\n",P.N_telephone);
fprintf(FP,"%d %d %d\n",P.DP.j,P.DP.m,P.DP.a);
fprintf(FP,"%s\n",P.adresse);
    // Close the file
    fclose(FP);
    delay(1500);
    gotoxy(80,20);
    printf("les informations sont bien enrigestrees\n");
    view_list_invalid:
    gotoxy(85,22);
    printf("      <-- : 1   ||   0 : --> \n");
    gotoxy(85,24);
    fflush(stdin);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}


/**fonction de gestion des rendez-vous par la secretaire**/

void GestionRD(personne p){
FILE *RV;
gotoxy(85,8);
fflush(stdin);
setcolortxt(1);
printf("* NOM :");
setcolortxt(15);
gets(p.NOM);
gotoxy(85,10);
fflush(stdin);
setcolortxt(1);
printf("* PRENOM :");
setcolortxt(15);
gets(p.PRENOM);
gotoxy(85,12);
fflush(stdin);
setcolortxt(1);
printf("* CIN :");
setcolortxt(15);
gets(p.CIN);
fflush(stdin);
gotoxy(85,14);
setcolortxt(1);
printf("* DATE DE RENDEZ-VOUS :");
setcolortxt(15);
scanf("%d %d %d",&p.date_RV.j,&p.date_RV.m,&p.date_RV.a);
gotoxy(85,16);
setcolortxt(1);
printf("* NUMERO DE RENDEZ-VOUS:");
scanf("%d",&p.NUM_RV);
setcolortxt(15);
RV=fopen("RendezVous.txt","a");
if(RV==NULL){
    printf("erreur");
    exit(1);
}
    fprintf(RV, "%s\n", p.NOM);
    fprintf(RV, "%s\n", p.PRENOM);
    fprintf(RV, "%s\n", p.CIN);
    fprintf(RV, "%d %d %d\n", p.date_RV.j, p.date_RV.m, p.date_RV.a);
    fprintf(RV, "%d\n", p.NUM_RV);
    fclose(RV); // Fermer le fichier après écriture
    delay(1500);
    gotoxy(85,20);
    printf("le rendez-vous est bien pris.\n");
    view_list_invalid:
    gotoxy(85,22);
    printf("      <-- : 1   ||   0 : --> \n");
    gotoxy(85,24);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}


/**fonction de gestion de comptabilité par la secrétaire**/

void GestionCompt(facture F){
gotoxy(95,2);
fflush(stdin);
setcolortxt(1);
printf("| FACTURE |");
gotoxy(80,4);
fflush(stdin);
printf("-----------------------------------------");
gotoxy(85,8);
fflush(stdin);
setcolortxt(1);
printf(" * NOM :");
setcolortxt(15);
gets(F.NOM);
gotoxy(85,10);
fflush(stdin);
setcolortxt(1);
printf(" * CIN :");
setcolortxt(15);
gets(F.CIN);
gotoxy(85,12);
fflush(stdin);
setcolortxt(1);
printf(" * DATE DE PAYEMENT :");
setcolortxt(15);
scanf("%d %d %d",&F.date_payement.j,&F.date_payement.m,&F.date_payement.a);
gotoxy(85,14);
fflush(stdin);
setcolortxt(1);
printf(" * LE MONTANT :");
setcolortxt(15);
scanf("%f",&F.montant);
gotoxy(85,16);
fflush(stdin);
setcolortxt(1);
printf(" * PAYE :");
setcolortxt(15);
scanf("%f",&F.paye);
gotoxy(85,18);
fflush(stdin);
setcolortxt(1);
printf(" * RESTANT :");
setcolortxt(15);
scanf("%f",&F.restant);
fflush(stdin);
delay(1500);
gotoxy(85,20);
printf(" * la facture est effectuee *");
FILE *FF;
FF=fopen("factures.txt","a");
if(FF==NULL){
    printf("erreur");
    exit(1);
 }
fprintf(FF, "%s\n", F.NOM);
fprintf(FF,"%s\n",F.CIN);
fprintf(FF, "%d %d %d\n",F.date_payement.j,F.date_payement.m,F.date_payement.a);
fprintf(FF, "%.2f\n", F.montant);
fprintf(FF, "%.2f\n", F.paye);
fprintf(FF, "%.2f\n", F.restant);
fclose(FF);
    view_list_invalid:
    gotoxy(85,22);
    printf("      <-- : 1   ||   0 : --> ");
    gotoxy(85,24);
    scanf("%d",&main_exit);
    system("cls");
    if(main_exit==1)
        menu_secrtaire(&ids);
    else if (main_exit==0)
        close();
    else{
        printf("invalid!");
        goto view_list_invalid;
    }
}


/**fonction de la secretaire(l'authentification)**/
void SECRETAIRE(){
 FILE *fps;
 fps=fopen("secretaire.txt","r");
 if(fps==NULL){
    printf("erreur");
    exit(1);
 }
 char ids[10];
 int mots;
 char ids2[10];
 int mots2;
 int fonction;
 printf("\n\n\n\n\n\n\n\n\n\n\n");
int m=0;
 while(fscanf(fps,"%s\n%d",ids2,&mots2) == 2){
    do{
        if(m!=0){
        setcolortxt(4);
        gotoxy(85,8);
        printf("--Vos infos ne sont pas valides--\n\n");}
        setcolortxt(15);
        gotoxy(85,10);
        printf("**  L'identifiant   :  ");
        scanf("%s",ids);
        fflush(stdin);
        gotoxy(85,12);
        printf("**  Mot_De_Passe    :  ");
        maskPassword(&mots);
        system("cls");
        m++;


        }while((strcmp(ids2, ids)!= 0) || (mots2 != mots));}
        fclose(fps);
menu_secrtaire(&ids);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**fct du menu principal**/
void menu(){
   int choix;
   setcolor(0,15);
   gotoxy(90,5);
   printf("-BIENVEUE CHEZ E-SANTE-");
   gotoxy(85,10);
   setcolortxt(15);
   printf("---->  1: MEDECIN  ---- ");
   gotoxy(85,15);
   printf("----> 2: SECRETAIRE  ----");
   gotoxy(90,19);
   setcolortxt(9);
   printf("---> Entrer Votre Choix:");
   scanf("%d",&choix);
    system("cls");
    // Efface la console sur Windows
    switch(choix){
    case 1:
        medecin();
        break;
    case 2:
        SECRETAIRE();
        break;
    default:{
    setcolortxt(4);
    gotoxy(90,22);
    printf("<!> VEUILLEZ CHOISIR 1 OU 2");
    delay(1200);
    system("cls");
    menu();
  }
    }}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**main**/
int  main()
{
menu();
return 0;
}
