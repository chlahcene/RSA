#ifndef _TP_RSA_H_
#define	_TP_RSA_H_
#include <string.h>
#include <ctype.h>
#include <gmp.h>
#include "String++.h"
#include "Input.h"
#define BigInt mpz_t
#define PX  25
#define PY  10
#define HTR  20
#define LNGR 80

#define PX1  25
#define PY1  10
#define HTR1  30
#define LNGR1 80

#define FolderDATA "data\\user data rsa"

typedef struct UtilisateurRSA UtilisateurRSA ;
typedef struct Profile Profile ;

struct Profile{
    char NOMFICHIER[50];
    char NOM[50];
    char PRENOM[50];
    char NOMPROFILE[50];
    char MOTPASS[30];
};
struct UtilisateurRSA{
    char NOMFICHIER[50];
    char MOTPASS[30];
    char** Premier;
    char** NomPremier;
    int TPremier; /// LA TAILLE DU TABLEAUX DES NOMBRES PREMIERS
    char** ClePublicN;
    char** ClePublicE;
    char** NomClePublic;
    int TClePublic; /// LA TAILLE DU TABLEAUX DES CLES PUBLICS
    char** CleCompletN;
    char** CleCompletE;
    char** CleCompletD;
    char** NomCleComplet;
    int TCleComplet; /// LA TAILLE DU TABLEAUX DES CLES COMPLET
}user_data_Rsa;



void Create_new_RSA_Account(void);
    // Create new RSA Account
void Log_in(UtilisateurRSA *user);
    // Log in the RSA account
void TextEnNumber(const char *text,int taille, BigInt *Number);
    // convertion du code asci en nombre entier
int NumberEnText(BigInt Number,char** text);
     // convertion du nombre entier en code asci return le taille du text
int NbrOcterBigInt(BigInt Number);
    // clacule le nombre des octer neccessaire pour sauvergarder Number
void Save_File_Data_RSA(UtilisateurRSA user);
    // save the data en file and crypt the file
void Crypt_Chain_RSA(const char *chain,int taille,BigInt n,BigInt e,BigInt *code_Chain_Crypter);
    // crypt chain avec cle (n,e)
void Decryp_Chain_RSA(BigInt code_Chain_A_decrypter,BigInt n,BigInt d,char** chain_decrypter);
    // Decrypt code_Chain_A_decrypter avec cle prive (n,d)
void Crypt_Fichier(const char *NomFichierACrypt,const char *NouveauxFichier,BigInt n,BigInt e);
    // CRYPTER LE FICHIER NomFichierACrypt AVEC LA CLE (n,e)
void Decrypt_Fichier(const char *NomFichierADecrypt,const char *NouveauxFichier,BigInt n,BigInt d);
    // DECRYPTER LE FICHIER NomFichierADecrypt AVEC LA CLE (n,d)
void CalculeCleRSA(BigInt p,BigInt q,BigInt *n,BigInt *e,BigInt *d);
    // CALCULE LES CLE PUBLIC (n,e) et LE CLE PRIVE (n,d)
char* hachage(const char* chain);
    // crypeter un chaine avec RSA avec clé public sans avoir le clé privé
void Write_RSA_File(UtilisateurRSA user,const char* Nom_Fichier);
    // write user dans un fichier Nom_Fichier
void Read_RSA_File(const char* Nom_Fichier,UtilisateurRSA *user);
    // read file Nom_Fichier et le met dans *user
void Genere_Nbr_Premier(BigInt *Nombre,int tailleNombre,gmp_randstate_t  state);
void Genere_Cle_Aleatoire(UtilisateurRSA *user,gmp_randstate_t state);
void Ajoute_Nbr_premier(UtilisateurRSA *user,BigInt nbr,const char* Nom);
void Ajoute_cle_Public(UtilisateurRSA *user,BigInt n,BigInt e,const char* Nom);
void Ajoute_cle_complet(UtilisateurRSA *user,BigInt n,BigInt e,BigInt d,const char* Nom);
void liberer_sup_Continu_UtilisateurRSA(UtilisateurRSA *user);
    // reset le continu du *user
void File_Derectory_Current(char ***Fichier,int *Taille);
    // vous donne le name des fichier qui se trouve dans le dossier current
    // il fait le alloucation alors il dois faire liberation
int Nom_Fichier(char **nom);
    // affiche liste des fichiers et l'utilisatuer choiser un nom fichier pour l'utiliser


void Create_new_RSA_Account(void){

  /** Create new RSA Account
   **/

     textbackground(BLACK);
     system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=35,y=2;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"Create New RSA Account");
    textcolor(WHITE);
    cputsxy(x,y+7,"Username ");
    cputsxy(x,y+13,"First Name ");
    cputsxy(x,y+19,"Last Name ");
    cputsxy(x,y+25,"Password ");
    cputsxy(x,y+31,"Confirm Password ");
    textcolor(RED);
    putchxy(x+9,y+7,'*');
    putchxy(x+11,y+13,'*');
    putchxy(x+10,y+19,'*');
    putchxy(x+10,y+25,'*');
    putchxy(x+17,y+31,'*');
    textbackground(WHITE);
    DrawRectangle(x,y+8,48,2);
    DrawRectangle(x,y+14,48,2);
    DrawRectangle(x,y+20,48,2);
    DrawRectangle(x,y+26,24,2);
    DrawRectangle(x,y+32,24,2);
    textbackground(LIGHTCYAN);
    textcolor(WHITE);
    AfficheButton("Create new account",x,y+37,20,3);
    int NumbreInput=1;
    int c=0;
    char Username[48]="\0",LastName[48]="\0",FirstName[48]="\0",Password[24]="\0",ConfirmPassword[24]="\0";
    textbackground(WHITE);
    textcolor(BLACK);
    do{
        if (NumbreInput>0 && NumbreInput<6){

            if (NumbreInput==1){
                // Username
                c=Input_Text(Username,x,y+9,48);

            }else if (NumbreInput==2){
                // First Name
                c=Input_Text(FirstName,x,y+15,48);

            }else if (NumbreInput==3){
                // Last Name
                c=Input_Text(LastName,x,y+21,48);

            }else if (NumbreInput==4){
                // Password
                c=Input_MotPass(Password,x,y+27,24);

            }else if (NumbreInput==5){
                // Confirm Password
                c=Input_MotPass(ConfirmPassword,x,y+33,24);
            }
            if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
            else if (c==72 || c==73) {
                NumbreInput--;
                if (NumbreInput==0) NumbreInput=6;
            }
        }else if (NumbreInput==6){
            // Button Create new account
            textbackground(BLUE);
            textcolor(WHITE);
            AfficheButton("Create new account",x,y+37,20,3);
            do{
                c=SaiserCntrl();
            }while(c==75 || c==77 ); // car here touch left and right ne fait rien
            if (c==13){
                // here est create new account

                if (!(Username[0] && LastName[0] && FirstName[0] && Password[0] && ConfirmPassword[0])) {
                    // This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in required inputs.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                if (strcmp(Password,ConfirmPassword)!=0){
                    // the password is diffirent
                    AfficheErreur(x+5,y+5,"The Password and Confirm Password no match");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                 int exist=0;
                FILE* F=fopen(FolderDATA,"rb");
                Profile Pr;
                while(fread(&Pr,sizeof(Pr),1,F)){
                    if (strcmp(Pr.NOMPROFILE,Username)==0){
                        exist=1;break;
                    }
                }
                fclose(F);
                if (exist==1){
                    // This is username not found
                    AfficheErreur(x+5,y+5,"Username is exist try others");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                // The create new account is success
                textbackground(BLACK);
                system("CLS");
                 F=fopen(FolderDATA,"ab+");
                if (F==NULL){
                    fprintf(stderr,"Erreur de ouverteur le ficheir de %s",FolderDATA);
                    return 1;
                }else {

                    // on rempler les information du notre utilisateur
                    char* ChainTmp=hachage(Password);
                    strcpy(Pr.MOTPASS,ChainTmp);
                    free(ChainTmp);
                    strcpy(Pr.NOM,FirstName);
                    strcpy(Pr.PRENOM,LastName);
                    ChainTmp=TimeActuelle();
                    strcpy(Pr.NOMFICHIER,ChainTmp);
                    strcpy(Pr.NOMPROFILE,Username);
                    UtilisateurRSA user;
                    // on inthisyalise aussi les data que le utilisateur a besoin
                    strcpy(user.MOTPASS,Password);
                    strcpy(user.NOMFICHIER,ChainTmp);
                    free(ChainTmp);
                    // nombre premier
                    user.TPremier=0;
                    user.NomPremier=NULL;
                    user.Premier=NULL;
                    // cle public
                    user.TClePublic=0;
                    user.NomClePublic=NULL;
                    user.ClePublicE=NULL;
                    user.ClePublicN=NULL;
                    // cle prive et public
                    user.TCleComplet=0;
                    user.NomCleComplet=NULL;
                    user.CleCompletN=NULL;
                    user.CleCompletE=NULL;
                    user.CleCompletD=NULL;
                    fseek(F,0,SEEK_END);
                    fwrite(&Pr,sizeof(Pr),1,F);
                    Save_File_Data_RSA(user);
                    textcolor(WHITE);
                    cputsxyTemp(22,3,"The create the new account end with success thanks you ...",10);
                    }
                    c=getch();
                    fclose(F);
                    return 0;
            }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
             else if (c==72 || c==73) NumbreInput=5;
            textbackground(LIGHTCYAN);
            AfficheButton("Create new account",x,y+37,20,3);
            textbackground(WHITE);
            textcolor(BLACK);
        }
        if (c==27){
            // return Backs
            if (AreYouSure(20,15)) return 1;
            textbackground(WHITE);
            textcolor(BLACK);
        }
    }while(1);

}
int NbrOcterBigInt(BigInt Number){
    /// clacule le nombre des octer neccessaire pour sauvergarder Number
     BigInt a; mpz_init_set_ui(a,256);
     int i = 1;
     while(mpz_cmp(Number,a)>=0){
        mpz_mul_2exp(a,a,8);
        i++;
     }
     mpz_clear(a);
     return i;
}
void TextEnNumber(const char *text,int taille, BigInt *Number){
    /// convertion du code asci en nombre entier
     int i;
     mpz_set_ui(*Number,0);
     if (taille=!0){
         BigInt a; mpz_init(a);
         mpz_ui_pow_ui(a,256,taille);
         for( i = 0;i<taille; i++)
         {
            mpz_div_2exp(a,a,8);
            mpz_addmul_ui(*Number,a,(unsigned char)(*(text+i)));
         }
         mpz_clear(a);
     }
     return 0;
}
int NumberEnText(BigInt Number,char** text){
     /// convertion du nombre entier en code asci return le taille du text
     int i = NbrOcterBigInt(Number);
     int taille=i;
     (*text)=malloc((i+1)*sizeof(**text));
     BigInt Number2; mpz_init_set(Number2, Number);
     BigInt a; mpz_init(a);
     (*text)[i--]=0;
     for ( ;i>-1;i--){
            mpz_mod_2exp(a,Number2,8);
            mpz_div_2exp(Number2,Number2,8);
            (*text)[i]=(unsigned char)mpz_get_ui(a);
     }
     mpz_clear(a);
     mpz_clear(Number2);
    return taille;
}
void Save_File_Data_RSA(UtilisateurRSA user){

    /// save the data en file and crypt the file

        Write_RSA_File(user,"Temp.txt");
        BigInt n,e,d,p,q;
        mpz_init(n);mpz_init(e);mpz_init(d);mpz_init(p);mpz_init(q);
        TextEnNumber(user.MOTPASS,strlen(user.MOTPASS),&p);
        mpz_mul_ui(q,p,7);
        while(mpz_probab_prime_p(q,15)==0){
            mpz_nextprime(q,q);
        }
        while(mpz_probab_prime_p(p,15)==0){
            mpz_nextprime(p,p);
        }
        CalculeCleRSA(p,q,&n,&e,&d);
        Crypt_Fichier("Temp.txt",user.NOMFICHIER,n,e);
            // on crypt le fichier temp et met dans le user.NOMFICHIER
        FILE* F=fopen("Temp.txt","w");
            fclose(F);// on supprime les donner que dans Temp
            remove("Temp.txt");
            mpz_clear(n);mpz_clear(e);mpz_clear(d);mpz_clear(p);mpz_clear(q);

     return 0;
}
void Crypt_Chain_RSA(const char *chain,int taille,BigInt n,BigInt e,BigInt *code_Chain_Crypter){
    // crypt chain avec cle (n,e)
    if (taille>0){
        TextEnNumber(chain,taille,code_Chain_Crypter);
        mpz_powm (*code_Chain_Crypter,*code_Chain_Crypter,e,n);
    }

}
void Decryp_Chain_RSA(BigInt code_Chain_A_decrypter,BigInt n,BigInt d,char** chain_decrypter){
    // Decrypt code_Chain_A_decrypter avec cle prive (n,d)
    BigInt x;mpz_init(x);
    mpz_powm (x,code_Chain_A_decrypter,d,n);
    NumberEnText(x,chain_decrypter);
    mpz_clear(x);
}
void Crypt_Fichier(const char *NomFichierACrypt,const char *NouveauxFichier,BigInt n,BigInt e){
    /** CRYPTER LE FICHIER NomFichierACrypt AVEC LA CLE (n,e)
     ** ET SAUVERGARDER DANS LE FICHIER NouveauxFichier
     **/
     FILE *F,*G;
        if ((F=fopen(NomFichierACrypt,"rb")) == NULL ) {
            fprintf(stderr, "Erreur de l'ouverture (fopen) du fichier %s\n", NomFichierACrypt);
            exit(EXIT_FAILURE);
        }
        if ((G=fopen(NouveauxFichier,"w")) == NULL ) {
            fprintf(stderr, "Erreur de l'cretion (fopen) du fichier %s\n", NouveauxFichier);
            exit(EXIT_FAILURE);
        }
        BigInt x;mpz_init(x);
        int i,max_char=NbrOcterBigInt(n)-1;
        char *chain;
        chain=malloc((max_char+1)*(sizeof(*chain)));
        chain[max_char]=0;
        fprintf(G,"%04d ",max_char);
        while(i=fread(chain,sizeof(char),max_char,F)){
            if (i!=0){
                Crypt_Chain_RSA(chain,i,n,e,&x);
                gmp_fprintf(G,"%Zd ",x);
            }
        }
     fclose(G);
     fclose(F);
     free(chain);
     mpz_clear(x);
     return 0;
}
void Decrypt_Fichier(const char *NomFichierADecrypt,const char *NouveauxFichier,BigInt n,BigInt d){
    /** DECRYPTER LE FICHIER NomFichierADecrypt AVEC LA CLE (n,d)
     ** ET SAUVERGARDER DANS LE FICHIER NouveauxFichier
     **/

     FILE *F,*G;
        if ((F=fopen(NomFichierADecrypt,"r")) == NULL ) {
            fprintf(stderr, "Erreur de l'ouverture (fopen) du fichier %s\n", NomFichierADecrypt);
            exit(EXIT_FAILURE);
        }
        if ((G=fopen(NouveauxFichier,"wb")) == NULL ) {
            fprintf(stderr, "Erreur de l'cretion (fopen) du fichier %s\n", NouveauxFichier);
            exit(EXIT_FAILURE);
        }
    BigInt x;mpz_init(x);
    int i,max_char=NbrOcterBigInt(n)-1,j=0;
    fscanf(F,"%d ",&i);
    unsigned char *chain;
    while(gmp_fscanf(F,"%Zd ",x)!=EOF){
        if (j){
            fwrite(chain,sizeof(unsigned char),max_char,G);
            free(chain);
        }else j=1;
        Decryp_Chain_RSA(x,n,d,&chain);
        }
            //printf("")
        fwrite(chain,sizeof(unsigned char),i,G);
            free(chain);
     fclose(G);
     fclose(F);
     mpz_clear(x);

     return 0;
}
void CalculeCleRSA(BigInt p,BigInt q,BigInt *n,BigInt *e,BigInt *d){
    /** CALCULE LES CLE PUBLIC (n,e) et LE CLE PRIVE (n,d)
     **/
     BigInt fn,p1,q1,J;
     mpz_init(fn);mpz_init(p1);mpz_init(q1);mpz_init(J);
     mpz_mul(n,p,q);/// CALCULE N=P*Q
     mpz_sub_ui(p1,p,1);
     mpz_sub_ui(q1,q,1);
     mpz_mul(fn,p1,q1);/// CALCULE FN=(P-1)*(Q-1)
     /// calcule du e elle que PGCD(e,fn)=1

     mpz_init_set_ui(*e,1);
     if (mpz_cmp(p,q)>0) mpz_add(*e,*e,p);
        mpz_add(*e,*e,q);
     do{
        mpz_gcd(J,fn,*e);
        if (mpz_cmp_ui(J,1)!=0) mpz_nextprime(*e,*e);
            else break;
     }while(1);
     /// calcule du telle que e*d module 1[fn]
     mpz_invert(*d,e,fn);
     mpz_clear(fn);mpz_clear(p1);mpz_clear(q1);mpz_clear(J);
     return 0;
}
char* hachage(const char* chain){
    /// crypeter un chaine avec RSA avec clé public sans avoir le clé privé
    BigInt n,e,x;
    mpz_init_set_str(n,"29961950402435000214455332031185772183148942025143725898858497",10);
    mpz_init_set_str(e,"7",10);
    mpz_init(x);
    Crypt_Chain_RSA(chain,strlen(chain),n,e,&x);
    char *ch;
    NumberEnText(x,&ch);
    mpz_clear(n);mpz_clear(e);mpz_clear(x);
    return ch;
}
void Write_RSA_File(UtilisateurRSA user,const char* Nom_Fichier){
    // write user dans un fichier Nom_Fichier
     FILE* F=fopen(Nom_Fichier,"w");
     if (F==NULL) {
            fprintf(stderr,"Erreur de ouverteur le ficheir de %s",Nom_Fichier);
            return 1;
     }else{
        fprintf(F,"%d %d %d\n",user.TPremier,user.TClePublic,user.TCleComplet);
        int i;
        for (i=0;i<user.TPremier;i++)
            fprintf(F,"%s %s\n",user.Premier[i],user.NomPremier[i]);

        for (i=0;i<user.TClePublic;i++)
            fprintf(F,"%s %s %s\n",user.ClePublicN[i],user.ClePublicE[i],user.NomClePublic[i]);

        for (i=0;i<user.TCleComplet;i++)
            fprintf(F,"%s %s %s %s\n",user.CleCompletN[i],user.CleCompletE[i],user.CleCompletD[i],user.NomCleComplet[i]);

         fclose(F);
     }
}
void Read_RSA_File(const char* Nom_Fichier,UtilisateurRSA *user){
    // read file Nom_Fichier et le met dans *user
     FILE* F=fopen(Nom_Fichier,"r");
     if (F==NULL) {
            fprintf(stderr,"Erreur de ouverteur le ficheir de %s",Nom_Fichier);
            return 1;
     }else{
            char* tmp;
            tmp=malloc(10000000*sizeof(char));
        if (tmp!=NULL) {
        fscanf(F,"%d %d %d\n",&(user->TPremier),&(user->TClePublic),&(user->TCleComplet));
        user->Premier=malloc((user->TPremier+2)*sizeof(*(user->Premier)));
        user->NomPremier=malloc((user->TPremier+2)*sizeof(*(user->NomPremier)));
        user->ClePublicN=malloc((user->TClePublic+2)*sizeof(*(user->ClePublicN)));
        user->ClePublicE=malloc((user->TClePublic+2)*sizeof(*(user->ClePublicE)));
        user->NomClePublic=malloc((user->TClePublic+2)*sizeof(*(user->NomClePublic)));
        user->CleCompletN=malloc((user->TCleComplet+2)*sizeof(*(user->CleCompletN)));
        user->CleCompletE=malloc((user->TCleComplet+2)*sizeof(*(user->CleCompletE)));
        user->CleCompletD=malloc((user->TCleComplet+2)*sizeof(*(user->CleCompletD)));
        user->NomCleComplet=malloc((user->TCleComplet+2)*sizeof(*(user->NomCleComplet)));
        int i;char* ptr;
        for (i=0;i<user->TPremier;i++){
            fscanf(F,"%s ",tmp);
            (user->Premier)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->Premier)[i])));
            strcpy((user->Premier)[i],tmp);
            fgets(tmp,1000,F);ptr = strchr(tmp, '\n'); if (ptr != NULL) *ptr = '\0';
            (user->NomPremier)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->NomPremier)[i])));
            strcpy((user->NomPremier)[i],tmp);
        }
        for (i=0;i<user->TClePublic;i++){
            fscanf(F,"%s ",tmp);
            (user->ClePublicN)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->ClePublicN)[i])));
            strcpy((user->ClePublicN)[i],tmp);
            fscanf(F,"%s ",tmp);
            (user->ClePublicE)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->ClePublicE)[i])));
            strcpy((user->ClePublicE)[i],tmp);
            fgets(tmp,1000,F);ptr = strchr(tmp, '\n'); if (ptr != NULL) *ptr = '\0';
            (user->NomClePublic)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->NomClePublic)[i])));
            strcpy((user->NomClePublic)[i],tmp);
        }
        for (i=0;i<user->TCleComplet;i++){
            fscanf(F,"%s ",tmp);
            (user->CleCompletN)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletN)[i])));
            strcpy((user->CleCompletN)[i],tmp);
            fscanf(F,"%s ",tmp);
            (user->CleCompletE)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletE)[i])));
            strcpy((user->CleCompletE)[i],tmp);
            fscanf(F,"%s ",tmp);
            (user->CleCompletD)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletD)[i])));
            strcpy((user->CleCompletD)[i],tmp);
            fgets(tmp,1000,F);ptr = strchr(tmp, '\n'); if (ptr != NULL) *ptr = '\0';
            (user->NomCleComplet)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->NomCleComplet)[i])));
            strcpy((user->NomCleComplet)[i],tmp);

        }
        free(tmp);
        }
         fclose(F);
     }
}
void Log_in(UtilisateurRSA *user){

  /// log in old account

    // textbackground(LIGHTBLUE);
    system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=40,y=2;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"User login");
    textcolor(WHITE);
    cputsxy(x,y+7,"Username ");
    cputsxy(x,y+13,"Password");
    textcolor(RED);
    putchxy(x+9,y+7,'*');
    putchxy(x+11,y+13,'*');
    textbackground(WHITE);
    DrawRectangle(x,y+8,48,2);
    DrawRectangle(x,y+14,48,2);
    textbackground(LIGHTCYAN);
    textcolor(WHITE);
    AfficheButton("Log in",x,y+20,20,3);
    int NumbreInput=1;
    int c=0;
    char Username[48]="\0",Password[48]="\0";
    textbackground(WHITE);
    textcolor(BLACK);
    do{
        if (NumbreInput>0 && NumbreInput<3){

            if (NumbreInput==1){
                // Username
                c=Input_Text(Username,x,y+9,48);

            }else if (NumbreInput==2){
                // Password
                c=Input_MotPass(Password,x,y+15,48);

            }
            if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
            else if (c==72 || c==73) {
                NumbreInput--;
                if (NumbreInput==0) NumbreInput=3;
            }
        }else if (NumbreInput==3){
            // Button Log in
            textbackground(BLUE);
            textcolor(WHITE);
            AfficheButton("Log in",x,y+20,20,3);
            do{
                c=SaiserCntrl();
            }while(c==75 || c==77 ); // car here touch left and right ne faite rien
            if (c==13){
                if (!(Username[0] && Password[0])) {
                    // This is input vide
                    textbackground(WHITE);
                    textcolor(RED);
                    AfficheErreur(x+5,y+5,"You have to fill in the input required");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                // The test of account if exist
                int exist=0;
                FILE* F=fopen(FolderDATA,"rb");
                Profile pr;
                while(fread(&pr,sizeof(pr),1,F)){
                    if (strcmp(pr.NOMPROFILE,Username)==0){
                        exist=1;break;
                    }
                }
                if (exist==0){
                    // This is username not found
                    textbackground(WHITE);
                    textcolor(RED);
                    AfficheErreur(x+5,y+5,"Username not found");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                char *chainTmp;
                chainTmp=hachage(Password);
                if (strcmp(pr.MOTPASS,chainTmp)!=0){
                    // This is Password warning
                    textbackground(WHITE);
                    textcolor(RED);
                    AfficheErreur(x+5,y+5,"Password wrong");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                }
                // chargement des data of user
                BigInt n,e,d,p,q;
                mpz_init(n);mpz_init(e);mpz_init(d);mpz_init(p);mpz_init(q);
                TextEnNumber(Password,strlen(Password),&p);
                mpz_mul_ui(q,p,7);
                while(mpz_probab_prime_p(q,15)==0){
                    mpz_nextprime(q,q);
                }
                while(mpz_probab_prime_p(p,15)==0){
                    mpz_nextprime(p,p);
                }
                CalculeCleRSA(p,q,&n,&e,&d);
                Decrypt_Fichier(pr.NOMFICHIER,"Temp.txt",n,d);
                strcpy(user->MOTPASS,Password);
                strcpy(user->NOMFICHIER,pr.NOMFICHIER);
                Read_RSA_File("Temp.txt",user);
                remove("Temp.txt");
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                gotoxy(20,3);
                printf("Hello %s %s",pr.NOM,pr.PRENOM);
                cputsxyTemp(10,5,"l'ouverteur du votre compte est terminer avec succes nous avier deja chrger votre data tu peux les utiliser merci\n",20);
                system("PAUSE");
                Compte_ouvert(0);
                return 0;

            }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
             else if (c==72 || c==73) NumbreInput=2;
            textbackground(LIGHTCYAN);
            AfficheButton("Log in",x,y+20,20,3);
            textbackground(WHITE);
            textcolor(BLACK);
        }
        if (c==27){
            // return Backs
            if (AreYouSure(20,15)) return 1;
            textbackground(WHITE);
            textcolor(BLACK);
        }
    }while(1);

}
void liberer_sup_Continu_UtilisateurRSA(UtilisateurRSA *user){
    // reset le continu du *user
        strcpy(user->MOTPASS,"");strcpy(user->NOMFICHIER,"");
        int i;
        for (i=0;i<user->TPremier;i++){
            free((user->Premier)[i]);
            free((user->NomPremier)[i]);
        }
        free(user->Premier);free(user->NomPremier);
        for (i=0;i<user->TClePublic;i++){
            free((user->ClePublicN)[i]);
            free((user->ClePublicE)[i]);
            free((user->NomClePublic)[i]);
        }
            free(user->ClePublicN);free(user->ClePublicE);free(user->NomClePublic);
        for (i=0;i<user->TCleComplet;i++){
            free((user->CleCompletN)[i]);
            free((user->CleCompletE)[i]);
            free((user->CleCompletD)[i]);
            free((user->NomCleComplet)[i]);
            }
            free(user->CleCompletN);free(user->CleCompletE);free(user->CleCompletD);free(user->NomCleComplet);
            user->TPremier=0;user->TCleComplet=0;user->TClePublic=0;
  }
void Genere_Nbr_Premier(BigInt *Nombre,int tailleNombre,gmp_randstate_t  state){

     BigInt rand;mpz_init( rand );
     BigInt max; mpz_init( max );
     mpz_ui_pow_ui( max, 10, tailleNombre+1 );
     BigInt min;mpz_init( min );
     mpz_ui_pow_ui( min, 10, tailleNombre );
     do{
        mpz_urandomm( rand, state, max );
     }while( mpz_cmp( rand, min) > 0 );
     mpz_nextprime( *Nombre,rand );
     while( !mpz_probab_prime_p(*Nombre,15)){
        mpz_nextprime( *Nombre, *Nombre );
     }
}
void Ajoute_cle_complet(UtilisateurRSA *user,BigInt n,BigInt e,BigInt d,const char* Nom){
    // ajoute le cle n,e,d a user
        int i=user->TCleComplet;
        (user->TCleComplet)++;
        user->CleCompletN=realloc(user->CleCompletN,(user->TCleComplet+2)*sizeof(*(user->CleCompletN)));
        user->CleCompletE=realloc(user->CleCompletE,(user->TCleComplet+2)*sizeof(*(user->CleCompletE)));
        user->CleCompletD=realloc(user->CleCompletD,(user->TCleComplet+2)*sizeof(*(user->CleCompletD)));
        user->NomCleComplet=realloc(user->NomCleComplet,(user->TCleComplet+2)*sizeof(*(user->NomCleComplet)));
        char* tmp;
        tmp=malloc(10000000*sizeof(char));
        gmp_sprintf(tmp,"%Zd",n);
        (user->CleCompletN)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletN)[i])));
        strcpy((user->CleCompletN)[i],tmp);
        gmp_sprintf(tmp,"%Zd",e);
        (user->CleCompletE)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletE)[i])));
        strcpy((user->CleCompletE)[i],tmp);
        gmp_sprintf(tmp,"%Zd",d);
        (user->CleCompletD)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->CleCompletD)[i])));
        strcpy((user->CleCompletD)[i],tmp);
        (user->NomCleComplet)[i]=malloc((strlen(Nom)+1)*sizeof(*((user->NomCleComplet)[i])));
        strcpy((user->NomCleComplet)[i],Nom);
        free(tmp);

}
void Ajoute_cle_Public(UtilisateurRSA *user,BigInt n,BigInt e,const char* Nom){
    // ajoute le cle (n,e) a user
        int i=user->TClePublic;
        (user->TClePublic)++;
        user->ClePublicN=realloc(user->ClePublicN,(user->TClePublic+2)*sizeof(*(user->ClePublicN)));
        user->ClePublicE=realloc(user->ClePublicE,(user->TClePublic+2)*sizeof(*(user->ClePublicE)));
        user->NomClePublic=realloc(user->NomClePublic,(user->TClePublic+2)*sizeof(*(user->NomClePublic)));
        char* tmp;
        tmp=malloc(10000000*sizeof(char));

        gmp_sprintf(tmp,"%Zd",n);
        (user->ClePublicN)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->ClePublicN)[i])));
        strcpy((user->ClePublicN)[i],tmp);

        gmp_sprintf(tmp,"%Zd",e);
        (user->ClePublicE)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->ClePublicE)[i])));
        strcpy((user->ClePublicE)[i],tmp);

        (user->NomClePublic)[i]=malloc((strlen(Nom)+1)*sizeof(*((user->NomClePublic)[i])));
        strcpy((user->NomClePublic)[i],Nom);
        free(tmp);

}
void Ajoute_Nbr_premier(UtilisateurRSA *user,BigInt nbr,const char* Nom){
    // ajoute le nbr premier a user
        int i=user->TPremier;
        (user->TPremier)++;
        user->Premier=realloc(user->Premier,(user->TPremier+2)*sizeof(*(user->Premier)));
        user->NomPremier=realloc(user->NomPremier,(user->TPremier+2)*sizeof(*(user->NomPremier)));
        char* tmp;
        tmp=malloc(10000000*sizeof(char));

        gmp_sprintf(tmp,"%Zd",nbr);
        (user->Premier)[i]=malloc((strlen(tmp)+1)*sizeof(*((user->Premier)[i])));
        strcpy((user->Premier)[i],tmp);

        (user->NomPremier)[i]=malloc((strlen(Nom)+1)*sizeof(*((user->NomPremier)[i])));
        strcpy((user->NomPremier)[i],Nom);
        free(tmp);

}
void Genere_Cle_Aleatoire(UtilisateurRSA *user,gmp_randstate_t state){
    // genere cle aleatoire
            textbackground(BLACK);
            system("CLS");
            int x=35,y=2;
            textcolor(WHITE);
            cputsxy(x,y+7,"Entrez la taille du cle generer ENTRE 4  ..  999 ");
            textbackground(WHITE);
            DrawRectangle(x-1,y+9,10,2);
            textbackground(WHITE);
            textcolor(BLACK);
            char TailleNombre[10]="\0";
            int i,c,nbrChfr=0;
            do{
                c=Input_Number(TailleNombre,x,y+10,3);
                if (c==13){
                    sscanf(TailleNombre,"%d",&nbrChfr);
                    if (nbrChfr>3) break;
                        else continue;
                }else if (c==27) return 1;
            }while(1);
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y+14);
            printf("Patientez ... \n\n");
            i=rand()%(nbrChfr-3)+3;
            BigInt p,q,n,e,d;
            mpz_init(p);mpz_init(q);mpz_init(n);mpz_init(d);mpz_init(e);
            Genere_Nbr_Premier(&p,i,state);
            Genere_Nbr_Premier(&q,nbrChfr-i,state);
            CalculeCleRSA(p,q,&n,&e,&d);
            printf("\t\tc'est voulez vous ajoute cette cle a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            gmp_printf("n=%Zd\n\ne=%Zd\n\nd=%Zd",n,e,d);
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);
            if (c==13){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette cle pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_cle_complet(user,n,e,d,Nom);
                          Ajoute_cle_Public(user,n,e,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le ajoutation est terminera avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }
        mpz_clear(p);mpz_clear(q);mpz_clear(n);mpz_clear(d);mpz_clear(e);

        }
void Genere_Premier(UtilisateurRSA *user,gmp_randstate_t state){
    // genere les nombres premiers
            textbackground(BLACK);
            system("CLS");
            int x=35,y=2;
            textcolor(WHITE);
            cputsxy(x,y+7,"Entrez la taille du nombre premier ENTRE 1  ..  999999999 ");
            textbackground(WHITE);
            DrawRectangle(x-1,y+9,15,2);
            textbackground(WHITE);
            textcolor(BLACK);
            char TailleNombre[10]="\0";
            int i,c,nbrChfr=0;
            do{
                c=Input_Number(TailleNombre,x+1,y+10,9);
                if (c==13){
                    sscanf(TailleNombre,"%d",&nbrChfr);
                    if (nbrChfr>0) break;
                        else continue;
                }else if (c==27) return 1;
            }while(1);
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y+14);
            printf("Patientez ... \n\n");
            BigInt n;
            mpz_init(n);
            Genere_Nbr_Premier(&n,nbrChfr,state);
            printf("\t\tc'est voulez vous ajoute cette nombre a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            gmp_printf("n=%Zd",n);
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);
            if (c==13){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette nombre pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_Nbr_premier(user,n,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le ajoutation est terminera avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }
        mpz_clear(n);

        }
void Next_Prime(UtilisateurRSA *user){
    // donne le nombre premier proche a nombre donne
            textbackground(BLACK);
            system("CLS");
            int x=5,y=2;
            textcolor(WHITE);
            cputsxy(x,y+7,"Entrez un nombre qui ne depasse pas 1000 chiffre et nous vous donne un nombre premier proche de lui ");
            textbackground(WHITE);
            DrawRectangle(x-1,y+9,102,11);
            textbackground(WHITE);
            textcolor(BLACK);
            char Nombre[1010]="\0";
            int i,c;
            do{
                c=Input_Area_Number(Nombre,x,y+10,999,100);
                if (c==13){
                    break;
                }else if (c==27) return 1;
            }while(1);
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y+30);
            printf("Patientez ... \n\n");
            BigInt n;
            mpz_init_set_str(n,Nombre,10);
            mpz_nextprime(n,n);
            while( !mpz_probab_prime_p(n,15)){
                mpz_nextprime(n,n);
                }
            printf("\t\tc'est voulez vous ajoute cette nombre a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            gmp_printf("n=%Zd",n);
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);
            if (c==13){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette nombre pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_Nbr_premier(user,n,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le Ajoutation est terminera avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }
        mpz_clear(n);

}
void Test_Propa_Prime(UtilisateurRSA *user){
    // test c'est il premier ou non
            textbackground(BLACK);
            system("CLS");
            int x=5,y=2;
            textcolor(WHITE);
            cputsxy(x,y+7,"Entrez un nombre pour tester sa primetiviter qui ne depasse pas 1000 chiffre ");
            textbackground(WHITE);
            DrawRectangle(x-1,y+9,102,11);
            textbackground(WHITE);
            textcolor(BLACK);
            char Nombre[1010]="\0";
            int i,c;
            do{
                c=Input_Area_Number(Nombre,x,y+10,999,100);
                if (c==13){
                    break;
                }else if (c==27) return 1;
            }while(1);
            textbackground(BLACK);
            textcolor(WHITE);
            gotoxy(x,y+25);
            printf("Patientez ... \n\n");
            BigInt n;
            mpz_init_set_str(n,Nombre,10);
            i=mpz_probab_prime_p(n,15);
            if (i==0){
                cputsxyTemp(x,y+30,"cette nombre n'est pas premier ",15);
            }else {
                if (i==2){
                cputsxyTemp(x,y,"cette nombre est premier ",15);
            }else if (i==1){
                cputsxyTemp(x,y,"Cette nombre peux etre premier ",15);
                cputsxyTemp(x,y+1,"Pour le test vraiment avec la methode des divisions ( Mais elle Prends Plus de Temps )",15);
                cputsxyTemp(x,y+2,"Apuiyer sur < Entre > pour debuter le test et < echap > sinon \n\n",15);
                do{
                c=SaiserCntrl();
                }while(c!=13 && c!=27);
                if (c==13) {
                    Test_Prime_Div(n,user);
                    mpz_clear(n);
                    return 0;
                }
            }
            printf("\t\tc'est voulez vous ajoute cette nombre a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);
            if (c==13){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette nombre pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_Nbr_premier(user,n,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le ajoutation est terminera avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }
        }
        printf("\n");
        system("PAUSE");
        mpz_clear(n);
}
void Test_Prime_Div(BigInt nomber,UtilisateurRSA *user){
    // test c'est il premier ou non avec la metode des division
            textbackground(BLACK);
            system("CLS");
            int x=20,y=5;
            textcolor(WHITE);
            cputsxy(x,y+7,"Le operation peux prendre plus temps Patianter un Peu ... ");
            cputsxy(x,y+8,"Le operation est en cours de excution  ... ");
            textbackground(GREEN);
            textcolor(BLUE);
            chargerA(x,y+12,0);
            textbackground(WHITE);
            textcolor(BLACK);
            time_t Debut_Excution;
            time(&Debut_Excution);
            char Te[100];
            BigInt d,q,n,m,procentage,tmpbig;
            int i=0;
            mpz_init_set_ui(d,2);
            mpz_init_set(n,nomber);
            mpz_init(q);mpz_init(m);mpz_init(procentage);
            mpz_sqrt(q,n);mpz_divexact_ui(procentage,q,100);
            mpz_init_set(tmpbig,procentage);
            int premier=1;
            while(premier && mpz_cmp(q,d)>=0){
                mpz_mod(m,n,d);
                if (mpz_sgn(m)==0) premier=0;
                else {
                    mpz_nextprime(d,d);
                    if (mpz_cmp(tmpbig,d)<0){
                        i++;
                        mpz_add(tmpbig,tmpbig,procentage);
                        Time_ecoule(Debut_Excution,Te);
                        textbackground(GREEN);
                        textcolor(BLUE);
                        chargerA(x,y+12,i);
                        textbackground(BLACK);
                        textcolor(WHITE);
                        cputsxyBlanc(x-1,y+10,Te,30);
                    }
                }
            }
            char c;
            Time_ecoule(Debut_Excution,Te);
            textbackground(GREEN);
            textcolor(BLUE);
            chargerA(x,y+12,100);
            textbackground(BLACK);
            textcolor(WHITE);
            cputsxyBlanc(x-1,y+10,Te,30);
            cputsxyTemp(x,y+20,"Le operation est Terminer Avec Succes",15);
            if (premier==0){
                cputsxyTemp(1,y+22,"Le Nombre n'est pas Premier car il Divisable par : ",15);
                gmp_printf("%Zd\n\n\t\t",d);
                system("PAUSE");
            }else {
                cputsxyTemp(x,y+22,"cette nombre est premier \n",15);
                gmp_printf("%Zd",nomber);
                            printf("\t\tc'est voulez vous ajoute cette nombre a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);

                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette nombre pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_Nbr_premier(user,n,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le Ajoutation est terminera avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }

             mpz_clear(tmpbig);mpz_clear(d);mpz_clear(q);mpz_clear(n);mpz_clear(m);mpz_clear(procentage);
}
void Test_Prime(UtilisateurRSA *user){
    // test c'est il premier ou non avec divisions
            textbackground(BLACK);
            system("CLS");
            int x=5,y=2;
            textcolor(WHITE);
            cputsxy(x,y+7,"Entrez un nombre pour tester sa primetiviter Avec divisions qui ne depasse pas 1000 chiffre ");
            textbackground(WHITE);
            DrawRectangle(x-1,y+9,102,11);
            textbackground(WHITE);
            textcolor(BLACK);
            char Nombre[1010]="\0";
            int i,c;
            do{
                c=Input_Area_Number(Nombre,x,y+10,999,100);
                if (c==13){
                    break;
                }else if (c==27) return 1;
            }while(1);
            BigInt n;
            mpz_init_set_str(n,Nombre,10);
            Test_Prime_Div(n,user);
            mpz_clear(n);
}
void Creer_Cle(UtilisateurRSA *user){
    // creer cle avec nombre p et q choiser
    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    cputsxyTemp(10,20,"Choiser 2 nombre premier du liste des nombre premier qui suive pour creer cle rsa \n\n",15);
    int j=0,i,c,choix[2]={0,0};
        if (user->TPremier==0){
            printf("\t\tLA LISTE EST VIDE  AJOUTES DES CLE DANS LA PARTIE CALCULE RSA MERCI ...");
            getch();
            return 1;
        }else{
              do{
                  textbackground(BLACK);
                  system("CLS");
                  textbackground(WHITE);
                  textcolor(GREEN);
                  FrameRectangle(PX-1,PY-1,LNGR+2,40+2,4);
                  textcolor(BLACK);
                  i=Menu(user->NomPremier,user->TPremier,PX,PY,LNGR,40,WHITE,LIGHTGRAY);
                  if (i==0) return 1;
                  textbackground(WHITE);
                  system("CLS");
                  textcolor(BLACK);
                  gotoxy(20,2);printf("Le Nombre Premier Avec le nom %s est :\n\n",(user->NomPremier)[i-1]);
                  printf("\tNombre Premier=%s\n\n\t",(user->Premier)[i-1]);
                  printf("voulez vous choiser cette nombre pour creer cle RSA si oui Apuiyer sur < entres > sinon <echap>");
                  do{
                    c=SaiserCntrl();
                   }while(c!=13 && c!=27);
                   if (c==13){
                        choix[j++]=i-1;
                        if (j==2) break;
                   }
              }while(1);
             textbackground(BLACK);
             system("CLS");
             textcolor(WHITE);
             BigInt p,q,n,e,d;
             int x=10,y=4;
            mpz_init_set_str(p,(user->Premier)[choix[0]],10);
            mpz_init_set_str(q,(user->Premier)[choix[1]],10);
            mpz_init(n);mpz_init(d);mpz_init(e);
            CalculeCleRSA(p,q,&n,&e,&d);
            printf("\t\tc'est voulez vous ajoute cette cle a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
            gmp_printf("n=%Zd\n\ne=%Zd\n\nd=%Zd",n,e,d);
            do{
                c=SaiserCntrl();
            }while(c!=13 && c!=27);
            if (c==13){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette cle pour plus vite le connaitre");
                textbackground(WHITE);
                DrawRectangle(x-1,y+9,30,2);
                textbackground(WHITE);
                textcolor(BLACK);
                char Nom[30]="\0";
                do{
                    c=Input_Text(Nom,x,y+10,25);
                    if (c==13){
                        if (strlen(Nom)==0) continue;
                          Ajoute_cle_complet(user,n,e,d,Nom);
                          Ajoute_cle_Public(user,n,e,Nom);
                          textbackground(BLACK);
                          textcolor(WHITE);
                          cputsxyTemp(x,y+15,"Le Ajoutation est terminer avec succes \n",15);
                          c=getch();
                          break;
                    }else if (c==27){
                        if(AreYouSure(x,y)) break;
                    }
                }while(1);
            }
        mpz_clear(p);mpz_clear(q);mpz_clear(n);mpz_clear(d);mpz_clear(e);
        }
}
void Lire_cle_complet(UtilisateurRSA *user){

             textbackground(BLACK);
             system("CLS");
            //textattr(169);
            //FrameRectangle(40,5,80,60,'|');
            int x=5,y=2;
            textcolor(LIGHTBLUE);
            cputsxy(x+10,y+4,"Cle RSA (n,e,d)");
            textcolor(WHITE);
            cputsxy(x,y+7,"Cle n");
            cputsxy(x,y+17,"Cle e");
            cputsxy(x,y+28,"Cle d");
            textcolor(RED);
            putchxy(x+9,y+7,'*');
            putchxy(x+11,y+17,'*');
            textbackground(WHITE);
            DrawRectangle(x,y+8,102,8);
            DrawRectangle(x,y+18,102,8);
            DrawRectangle(x,y+29,102,8);
            textbackground(LIGHTCYAN);
            textcolor(WHITE);
            AfficheButton("Ajoute CLE",x,y+40,20,3);
            int NumbreInput=1;
            int c=0;
            char nombreN[1002]="\0",nombreE[1002]="\0",nombreD[1002]="\0";
            textbackground(WHITE);
            textcolor(BLACK);
            do{
                if (NumbreInput>0 && NumbreInput<4){

                    if (NumbreInput==1){
                        // Cle n
                        c=Input_Area_Number(nombreN,x,y+10,500,100);

                    }else if (NumbreInput==2){
                        // Cle e
                        c=Input_Area_Number(nombreE,x,y+20,500,100);

                    }else if (NumbreInput==3){
                        // Cle d
                        c=Input_Area_Number(nombreD,x,y+31,500,100);

                    }
                    if (c==80 || c==81 || c==9 || c==13) NumbreInput++;
                    else if (c==72 || c==73) {
                        NumbreInput--;
                        if (NumbreInput==0) NumbreInput=4;
                    }
                }else if (NumbreInput==4){
                    // Button Create new account
                    textbackground(BLUE);
                    textcolor(WHITE);
                    AfficheButton("Ajoute CLE",x,y+40,20,3);
                    do{
                        c=SaiserCntrl();
                    }while(c==75 || c==77 ); // car here touch left and right ne fait rien
                    if (c==13){
                        // Ajoutations
                        if (!(nombreE[0] && nombreN[0])) {
                            // This is input vide
                            AfficheErreur(x+5,y+5,"You have to fill in the input they are required.");
                            textcolor(BLACK);
                            textbackground(WHITE);
                            continue;
                        }

                    textbackground(BLACK);
                    system("CLS");
                    textcolor(WHITE);
                    gotoxy(1,3);
                    printf("\t\tc'est voulez vous ajoute cette cle a votre liste des cle Apuiyer sur <entre> et <echap> sinon\n\n");
                    printf("\t\tn=%s\n\n\t\te=%s\n\n",nombreN,nombreE);
                    if (nombreD[0]) printf("\t\td=%s\n\n",nombreD);
                    do{
                        c=SaiserCntrl();
                    }while(c!=13 && c!=27);
                    if (c==13){
                        BigInt n,e,d;
                        mpz_init(d);
                        if (nombreD[0]) mpz_set_str(d,nombreD,10);
                        mpz_init_set_str(n,nombreN,10);mpz_init_set_str(e,nombreE,10);
                        textbackground(BLACK);
                        system("CLS");
                        textcolor(WHITE);
                        cputsxy(x,y+7,"Entrez le nom que voulez vous donnez a cette cle pour plus vite le connaitre");
                        textbackground(WHITE);
                        DrawRectangle(x-1,y+9,30,2);
                        textbackground(WHITE);
                        textcolor(BLACK);
                        char Nom[30]="\0";
                        do{
                            c=Input_Text(Nom,x,y+10,25);
                            if (c==13){
                                if (strlen(Nom)==0) continue;
                                  Ajoute_cle_Public(user,n,e,Nom);
                                  if (nombreD) Ajoute_cle_complet(user,n,e,d,Nom);
                                  textbackground(BLACK);
                                  textcolor(WHITE);
                                  cputsxyTemp(x,y+15,"Le ajoutation est terminera avec succes \n",15);
                                  c=getch();
                                  break;
                            }else if (c==27){
                                if(AreYouSure(x,y)) break;
                            }
                        }while(1);
                        mpz_clear(n);mpz_clear(d);mpz_clear(e);
                        }
                        return 0;
                    }else if (c==80 || c==81 || c==9 ) NumbreInput=1;
                     else if (c==72 || c==73) NumbreInput=4;
                    textbackground(LIGHTCYAN);
                    AfficheButton("Ajoute CLE",x,y+40,20,3);
                    textbackground(WHITE);
                    textcolor(BLACK);
                }
                if (c==27){
                    // return Backs
                    if (AreYouSure(20,15)) return 1;
                    textbackground(WHITE);
                    textcolor(BLACK);
                }
            }while(1);

}
int Nom_Fichier(char **nom){
    // affiche liste des fichiers et l'utilisatuer choiser un nom fichier pour l'utiliser
          char **NFile;
          int i,j,taille;
          File_Derectory_Current(&NFile,&taille);
          do{
          textbackground(BLACK);
          system("CLS");
          textbackground(WHITE);
          textcolor(YELLOW);
          FrameRectangle(PX-1,PY-1,LNGR+2,HTR+2,4);
          textcolor(BLACK);
          i=Menu(NFile,taille,PX,PY,LNGR,HTR,WHITE,LIGHTGRAY);
          if (i!=0) {
            (*nom)=NFile[i-1];
            FILE* F=fopen(*nom,"r");
            if (F==NULL){
                textbackground(BLACK);
                system("CLS");
                textcolor(WHITE);
                cputsxyTemp(10,2,"THIS is derecotory try again file \n\t",15);
                system("PAUSE");
                continue;
            }
            fclose(F);
          }
            break;
          }while(1);
          for (j=0;j<taille;j++) if ((j+1)!=i) free(NFile[j]);
          free(NFile);
        return i;
}

void choix_crypt(UtilisateurRSA user_data_Rsa){
    //  crypter
    char* Nom;
    if (Nom_Fichier(&Nom)==0) return 1;
    textbackground(BLACK);
     system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=35,y=2,i;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"CRYPTRER");
    textcolor(WHITE);
    cputsxy(x,y+7,"Le Nouveau Nom du Fichier qui a Le code du Cypetage");
    textbackground(WHITE);
    DrawRectangle(x,y+8,50,2);
    int c=0;
    char Nouveau_Nom[48]="\0";
    textbackground(WHITE);
    textcolor(BLACK);
    do{
    c=Input_Text(Nouveau_Nom,x,y+9,48);
    if (c==27) if (AreYouSure(30,20)) return 1;
        if (c==13)
            if (Nouveau_Nom[0]==0) {// This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in the input they are required.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                } else break;
    }while(1);

        do{
          textbackground(BLACK);
          system("CLS");
          textbackground(WHITE);
          textcolor(GREEN);
          FrameRectangle(PX1-1,PY1-1,LNGR1+2,HTR1+2,4);
          textcolor(BLACK);
          i=Menu(user_data_Rsa.NomClePublic,user_data_Rsa.TClePublic,PX1,PY1,LNGR1,HTR1,WHITE,LIGHTGRAY);
          if (i==0) if (AreYouSure(30,35)) return 1 ;else continue;
          textbackground(WHITE);
          system("CLS");
          textcolor(BLACK);
          gotoxy(20,2);printf("Le cle Public Avec le nom %s est :\n\n",(user_data_Rsa.NomClePublic)[i-1]);
          printf("\tn=%s\n\n\te=%s\n\n",(user_data_Rsa.ClePublicN)[i-1],(user_data_Rsa.ClePublicE)[i-1]);
          printf("\t\t Apuiyer sur < Entre > pour Crypter avec cette Cle ou d'autre touch pour Retourner en Arreier ");
          c=getch();
          if (c==13) break;
        }while(1);
          textbackground(WHITE);
          system("CLS");
          textcolor(BLACK);
        BigInt n,e;
        cputsxyTemp(20,4,"Le Crypetage est En cours de excution Pationter .. \n",10);
        mpz_init_set_str(n,(user_data_Rsa.ClePublicN)[i-1],10);
        mpz_init_set_str(e,(user_data_Rsa.ClePublicE)[i-1],10);
        Crypt_Fichier(Nom,Nouveau_Nom,n,e);
        cputsxyTemp(20,6,"Le Crypetage est Termenier Avec Succes  MERCI .. \n",10);
        system("PAUSE");
        free(Nom);
        mpz_clear(n);mpz_clear(e);
}
void choix_Decrypt(UtilisateurRSA user_data_Rsa){
    //  Decrypter
    char* Nom;
    if (Nom_Fichier(&Nom)==0) return 1;
    textbackground(BLACK);
     system("CLS");
    //textattr(169);
    //FrameRectangle(40,5,80,60,'|');
    int x=35,y=2,i;
    textcolor(LIGHTBLUE);
    cputsxy(x+10,y+4,"DECRYPTRER");
    textcolor(WHITE);
    cputsxy(x,y+7,"Le Nom du Nouveau Fichier qui va DECypeter");
    textbackground(WHITE);
    DrawRectangle(x,y+8,50,2);
    int c=0;
    char Nouveau_Nom[48]="\0";
    textbackground(WHITE);
    textcolor(BLACK);
    do{
    c=Input_Text(Nouveau_Nom,x,y+9,48);
    if (c==27) if (AreYouSure(30,20)) return 1;
        if (c==13)
            if (Nouveau_Nom[0]==0) {// This is input vide
                    AfficheErreur(x+5,y+5,"You have to fill in the input they are required.");
                    textcolor(BLACK);
                    textbackground(WHITE);
                    continue;
                } else break;
    }while(1);

        do{
          textbackground(BLACK);
          system("CLS");
          textbackground(WHITE);
          textcolor(GREEN);
          FrameRectangle(PX1-1,PY1-1,LNGR1+2,HTR1+2,4);
          textcolor(BLACK);
          i=Menu(user_data_Rsa.NomCleComplet,user_data_Rsa.TCleComplet,PX1,PY1,LNGR1,HTR1,WHITE,LIGHTGRAY);
          if (i==0) if (AreYouSure(30,35)) return 1 ;else continue;
          textbackground(WHITE);
          system("CLS");
          textcolor(BLACK);
          gotoxy(20,2);printf("Le cle Complet Avec le nom %s est :\n\n",(user_data_Rsa.NomCleComplet)[i-1]);
          printf("\tn=%s\n\n\te=%s\n\n\td=%s\n\n\t",(user_data_Rsa.CleCompletN)[i-1],(user_data_Rsa.CleCompletE)[i-1],(user_data_Rsa.CleCompletD)[i-1]);
          printf("\t\t Apuiyer sur < Entre > pour DECrypter avec cette Cle ou d'autre touch pour Retourner en Arreier ");
          c=getch();
          if (c==13) break;
        }while(1);
          textbackground(WHITE);
          system("CLS");
          textcolor(BLACK);
        BigInt n,d;
        cputsxyTemp(20,4,"Le DECrypetage est En cours de excution Pationter .. \n",10);
        mpz_init_set_str(n,(user_data_Rsa.CleCompletN)[i-1],10);
        mpz_init_set_str(d,(user_data_Rsa.CleCompletD)[i-1],10);
       Decrypt_Fichier(Nom,Nouveau_Nom,n,d);
        cputsxyTemp(20,6,"Le DECrypetage est Termenier Avec Succes  MERCI .. \n",10);
        system("PAUSE");
        free(Nom);
        mpz_clear(n);mpz_clear(d);
}




#endif
