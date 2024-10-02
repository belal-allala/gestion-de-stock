#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// structure d'un contact
struct contact {
     char nom[50];
     char numero[20];
     char email[50];
     char id[8];};

// tableau de contacts et nombre de contacts
struct contact contacts[100];
int nb_contacts = 0;
char id_table[10000][8];
int conteur_id = 0;
int i,d,choix,revenu,verifi;

// les couleurs
const char *reset = "\033[0m";
const char *vert = "\033[32m";
const char *rouge = "\033[31m";
const char *jaune = "\033[33m";

// la fonction qui verifier le nom 
int nom_verifier(char *nom){
    if (strlen(nom) >= 100) {
        printf("%sLe nom est trop long.%s\n",rouge,reset);
        return 0;}

for (int i = 0; nom[i] != '\0'; i++) {
    if (!isalpha(nom[i]) && nom[i] != ' ') {
        printf("%sle nom ne doit contenir que des lettres et des espaces.%s\n",rouge,reset);
        return 0;}
 }
return 1;}

// la fonction qui verifier le numero de telephone
int numero_valide(const char *numero) {
    int longueur = strlen(numero);
    if (longueur != 10) {
        return 0;}

    if (numero[0] != '0' || (numero[1] != '6' && numero[1] != '7')) {
        return 0;}

    for (int i = 0; i < longueur; i++) {
        if (numero[i] < '0' || numero[i] > '9') {
            return 0;}}

    for (int i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].numero, numero) == 0 ) {
            printf("%sle numero existe deja :%s\n",rouge,reset);
            return 0;} }
    return 1;}

// la fonction qui verifier l email
int email_valide(char *email) {
    int i, at_index = -1, dot_index = -1;
    if (email == NULL) {
        return 0;}

    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            if (at_index != -1) { 
                return 0;}
            at_index = i;
        } else if (email[i] == '.') {
            if (at_index == -1) { 
                return 0;
                }
            if (dot_index == -1) {
                dot_index = i;
            }
        } else if (!isalnum(email[i]) ){
            return 0;}
    }

    if (at_index == -1 || dot_index == -1 || at_index >= dot_index) {
    return 0;
    }
    for (int i = at_index + 1; i < dot_index ; i++) {
        if (!isalpha(email[i])) {
            printf("%sle dommaine ne doit contenir que des lettres et des espaces.%s\n",rouge,reset);
            return 0;}
    }

    if (dot_index == strlen(email) - 1) {
        return 0;}

    for (int i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].email, email) == 0 ) {
            printf("%sl email existe deja :%s\n",rouge,reset);
            return 0;}} 

    return 1;}

// la fonction qui generer des id
char *generer_id() {
    char *idi = malloc(8);
    int i;
    authre:
    srand(time(NULL));
    int num = rand() % 900000 + 100000; 
    sprintf(idi, "YC%06d", num);
    for (i = 0; i <= conteur_id;i++){
        if (!strcmp(id_table[conteur_id], idi)){
            free(idi);
            goto authre;}}
    strcpy(id_table[conteur_id],idi);
    conteur_id++; 
    return idi;
    }

//1.Ajouter un contact
void ajouter_contact() {
    struct contact nouveau_contact;
    if (nb_contacts >= 100) {
        printf("%sLe carnet d adresses est plein.%s\n",rouge,reset);
        return;}

    {debutnom:
    getchar();
    printf("entrer le nom : ");
    fgets(nouveau_contact.nom,100,stdin);
    nouveau_contact.nom[strcspn(nouveau_contact.nom, "\n")] = '\0';}
    
    if (!nom_verifier(nouveau_contact.nom)){
        goto debutnom;}
    
    {debutnumero:
    printf("entrer le numero de telephone : ");
    scanf("%s",&nouveau_contact.numero);
    nouveau_contact.numero[strcspn(nouveau_contact.numero, "\n")] = '\0';}

    if (!numero_valide(nouveau_contact.numero)){
        printf("%sce nomero n\'est pas validie \n%s",rouge,reset);
        goto debutnumero;}

    {debutemail:
    printf("entrer l\'adresse email : ");
    scanf("%s",&nouveau_contact.email);
    nouveau_contact.email[strcspn(nouveau_contact.email, "\n")] = '\0';}
    
    if (!email_valide(nouveau_contact.email)){
        printf("%scet email n\'est pas validie \n%s",rouge,reset);
        goto debutemail;
        }
    
    strcpy(nouveau_contact.id,generer_id());
    
    {contacts[nb_contacts] = nouveau_contact;
    nb_contacts++;}
    printf("%sContact ajoute avec succes !%s\n",vert,reset);}

//2.modifier un contact
void modifier_contact() {
    char nom_a_modifier[50];
    char nouveau_numero[20];
    char nouveau_email[50];
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;}

    {debutmodi:
    getchar();
    printf(" ecrit le nom a modifier :");
    fgets(nom_a_modifier, sizeof(nom_a_modifier), stdin);
    nom_a_modifier[strcspn(nom_a_modifier, "\n")] = '\0';}

    if (!nom_verifier(nom_a_modifier)){
        goto debutmodi;}

    {int i;
    for (i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].nom, nom_a_modifier) == 0) {
            break;}}
    
    if (i == nb_contacts) {
        printf("%sContact non trouve.%s\n",rouge,reset);
        return;}}
    
    {debutonum:
    printf("entrer le nouveau numero de telephone : ");
    scanf("%s", nouveau_numero);}
    
    if (numero_valide(nouveau_numero)==0){
        printf("%sce nomero n est pas validie .%s\n",rouge,reset);
        goto debutonum;}
    
    strcpy(contacts[i].numero, nouveau_numero);

    {debutemai:
    printf("entrer la nouvelle adresse email : ");
    scanf("%s", nouveau_email);}
    
    if (!email_valide(nouveau_email)){
        printf("%scet email n\'est pas validie \n%s",rouge,reset);
        goto debutemai;}
    
    strcpy(contacts[i].email, nouveau_email);
    printf("%sContact modifie avec succes.%s\n",vert,reset);}

// 3.supprimer un Contact
void supprimer_contact() {
    char nom_a_supprimer[50];
    int i, j;
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;}

    {debutsupp:
    getchar();
    printf(" ecrit le nom a supprimer :\n");
    fgets(nom_a_supprimer, sizeof(nom_a_supprimer), stdin);
    nom_a_supprimer[strcspn(nom_a_supprimer, "\n")] = '\0';}

    if (!nom_verifier(nom_a_supprimer)){
        goto debutsupp;}

    for (i = 0; i < nb_contacts; i++) {
        if (strcmp(contacts[i].nom, nom_a_supprimer) == 0) {
            break;}}

    if (i == nb_contacts) {
        printf("%scontact non trouve.%s\n",rouge,reset);
        return;}
    for (j = i; j < nb_contacts - 1; j++) {
        contacts[j] = contacts[j + 1];}
        
    (nb_contacts)--;
    printf("%scontact supprime avec succes.%s\n",vert,reset);
}

//4.afficher Tous les Contacts
void afficher_contacts() {
    if (contacts == NULL) {
        printf("%serreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;}

    printf("                       %sListe des contacts :%s\n",jaune,reset);
    printf("+---------------+----------------------+-----------------+----------------------------------+\n");
    printf("|      %sID%s       |         %sName%s         |  %sPhone Number%s   |              %sEmail%s               |\n",jaune,reset,jaune,reset,jaune,reset,jaune,reset);
    printf("+---------------+----------------------+-----------------+----------------------------------+\n");
    for (int i = 0; i < nb_contacts; i++) {
        printf("| %-8s | %-20s | %-15s | %-32s |\n",contacts[i].id,contacts[i].nom,contacts[i].numero,contacts[i].email);
        printf("+---------------+----------------------+-----------------+----------------------------------+\n");}}

//5.rechercher un Contact
void rechercher_contact() {
    char nom_a_rechercher[50];
    int i;
    int trouve = 0;
    if (contacts == NULL) {
        printf("%sErreur : le tableau de contacts est null.%s\n",rouge,reset);
        return;}
        
    {debutrecherch:
    getchar();
    printf("ecrit le nom a rechercher :");
    fgets(nom_a_rechercher, sizeof(nom_a_rechercher), stdin);
    nom_a_rechercher[strcspn(nom_a_rechercher, "\n")] = '\0';}
    
    if (!nom_verifier(nom_a_rechercher)){
        goto debutrecherch;
        }
    for (i = 0; i < nb_contacts; i++) {
        if (!strcmp(contacts[i].nom, nom_a_rechercher)) {
            printf("%scontact trouvé :%s\n",vert,reset);
            printf("%sID :%s %s\n",jaune,reset, contacts[i].id);
            printf("%snom :%s %s\n",jaune,reset, contacts[i].nom);
            printf("%snumero :%s %s\n",jaune,reset, contacts[i].numero);
            printf("%semail :%s %s\n",jaune,reset, contacts[i].email);
            trouve = 1;
            break;}
    }
    if (!trouve) {
        printf("%sContact non trouve.%s\n",rouge,reset);}
}

int main() {
    char noms[10][50] = {"salma", "manal", "karim"};
    char telephones[10][20] = {"0673897654", "0687654321", "0763437907"};
    char emails[10][50] = {"salma@gmail.com", "amal@gmail.com","ahlam@gmail.com",};
    char ids[10][8]={"YC123456","YC112233","YC111234"};

    for (i = 0 ;i < 3 ; i++ ) {
        strcpy(contacts[nb_contacts].id,ids[i]);
        strcpy(contacts[nb_contacts].nom, noms[i]);
        strcpy(contacts[nb_contacts].numero, telephones[i]);
        strcpy(contacts[nb_contacts].email, emails[i]);
        strcpy(id_table[i],ids[i]);
        conteur_id++;
        nb_contacts++;}

    debut:
    printf("\n%s**********Menu*********%s\n",jaune,reset);
    printf("1. ajouter un contact\n");
    printf("2. modifier un contact\n");
    printf("3. supprimer un contact\n");
    printf("4. afficher tous les contacts\n");
    printf("5. rechercher un contact\n" );
    printf("0. quitter\n");
    do {
        printf("%schoix :%s ",jaune,reset);
        verifi = scanf("%d", &choix);
        if (verifi != 1 || choix < 0 || choix > 5){
            printf("%schoix invalide.%s\n",rouge,reset);
            while (getchar() != '\n');}
            
    } while (verifi != 1 || choix < 0 || choix > 5);
    switch (choix) {
        case 1:
            ajouter_contact();
            break;
        case 2:
            modifier_contact();
            break;
        case 3:
            supprimer_contact();
            break;
        case 4:
            afficher_contacts();
            break;
        case 5:
            rechercher_contact();
            break;
        case 0:
            printf("au revoir!\n");
            break;
        default:
            printf("%sChoix invalide.%s\n", rouge, reset);
            break;}

    printf("%schoisir 0 ou 1 pour quitter ou bien revenir au menu pricipal %s\n",jaune,reset);
    printf("0. quitter le programme\n");
    printf("1. revenir au menu principal\n");
    do {
        printf("%schoix :%s ",jaune,reset);
        d = scanf("%d", &revenu);
        if (d != 1 || revenu < 0 || revenu > 1){
            printf("%svirifier votre choix .%s\n",rouge,reset);
            while (getchar() != '\n');}
    } while (d != 1 || revenu < 0 || revenu > 5);
    if (revenu == 1)
    goto debut ;
    else if (revenu == 0)
    printf("merci");
    return 0;
}