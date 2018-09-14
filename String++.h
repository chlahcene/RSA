#ifndef _String++_H_
#define	_String++_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <time.h>

#include <math.h>
int Max(int a,int b){
    if (a<b) return b;
        else return a;
}
int Min(int a,int b){
    if (a>b) return b;
        else return a;
}


char *str_tolower (const char *ct);
    //mettre un caractère en minuscule
char *str_toupper (const char *ct);
    //mettre un caractère en majuscule
int str_istr (const char *cs, const char *ct);
    //connaître l'index de celle-ci dans le tableau
char *str_sub (const char *s, unsigned int debut, unsigned int fin);
    //extraire une sous-chaîne de s comprise entre l'indice debut et fin
char **str_split (char *s, const char *ct);
    //découper une chaîne de caractère suivant un délimiteur et de placer chaque sous-chaîne dans un tableau terminé par NULL
char *str_join (char **cs,int Taille);
    //réunissant des chaînes de caractères grâce à un séparateur
char *str_remplace (const char *s, unsigned int debut, unsigned int lenght, const char *ct);
    //remplacer length caractères de la chaîne s à partir de l'indice debut par une nouvelle chaîne ct. Une nouvelle chaîne est créée
char *str_strip (const char *st);
    //supprime les espaces superflus dans une chaîne de caractère
void StrSuppChar(char* text,int pos);
    //on supprime le cractere de la postion pos
int isCharSpFr(char ch);
    //c'est le cractrere ch est un cractere special dans la langue france comme é et ù à ç  return 1
void StrInsertChar(char* text,char ch,int pos);
    //on insert la caractere ch a postion pos dans chain caractere text
void cputsxyBlanc(int x,int y,const char* chain,int T);
    // Affichez la chain du caractere chain dans la postion dans la ecran x,y et terminera le reste avec des blanc
char* TimeActuelle(void);
    // Current time
char** Texte_split (const char *s, const char *ct,int NumberMax);
    //découper une chaîne de caractère suivant un délimiteur et de placer chaque sous-chaîne  du taille NumberMax dans un tableau terminé par NULL
int *IndexFileTexte(const char *NomFichier,const char *deliminateur,int MaxLine,int *NMot);
    // donnez tableaux des index de line du fichier text suivant des deliminateur et depasse pas maxline termenra premier case est le nombre du line
void cputsxyAreaBlanc(int x,int y,const char* chain,int max_Nbr_line,int max_length_line,const char *deliminateur);
void cputsxyBlancArea(int x,int y,const char* chain,int max_length_line,const char *deliminateur);
void cputsxyArea(int x,int y,const char* chain,int max_length_line,const char *deliminateur);
void Time_ecoule(time_t time,char* Time_ecl);
void File_Derectory_Current(char ***Fichier,int *Taille);
    // vous donne le name des fichier qui se trouve dans le dossier current
    // il fait le alloucation alors il dois faire liberation

char *str_tolower (const char *ct){
    //mettre un caractère en minuscule
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = tolower (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}
char *str_toupper (const char *ct){
    //mettre un caractère en majuscule
  char *s = NULL;

  if (ct != NULL)
  {
    int i;

    s = malloc (sizeof (*s) * (strlen (ct) + 1));
    if (s != NULL)
    {
      for (i = 0; ct[i]; i++)
      {
        s[i] = toupper (ct[i]);
      }
      s[i] = '\0';
    }
  }
  return s;
}
int str_istr (const char *cs, const char *ct){
  //connaître l'index de celle-ci dans le tableau
  int index = -1;

  if (cs != NULL && ct != NULL)
  {
    char *ptr_pos = NULL;

    ptr_pos = strstr (cs, ct);
    if (ptr_pos != NULL)
    {
      index = ptr_pos - cs;
    }
  }
  return index;
}
char *str_sub (const char *s, unsigned int debut, unsigned int fin){
     //extraire une sous-chaîne de s comprise entre l'indice debut et fin
  char *new_s = NULL;
  if (s != NULL && debut <= fin)
  {
    new_s = malloc (sizeof (*new_s) * (fin - debut + 2));
    if (new_s != NULL)
    {
      int i;

      for (i = debut; i <= fin && s[i]!='\0' ; i++)
      {
        new_s[i-debut] = s[i];
      }
      new_s[i-debut] = '\0';

    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      exit (EXIT_FAILURE);
    }
  }
  return new_s;
}
char **str_split (char *s, const char *ct){
    //découper une chaîne de caractère suivant un délimiteur et de placer chaque sous-chaîne dans un tableau terminé par NULL
  char **tab = NULL;

  if (s != NULL && ct != NULL)
  {
    int i;
    char *cs = NULL;
    size_t sz = 1;

    for (i = 0; (cs = strtok (s, ct)); i++)
    {
      if (sz <= i + 1)
      {
        void *tmp = NULL;

        sz <<= 1;
        tmp = realloc (tab, sizeof (*tab) * sz);
        if (tmp != NULL)
        {
          tab = tmp;
        }
        else
        {
          fprintf (stderr, "Memoire insuffisante\n");
          free (tab);
          tab = NULL;
          exit (EXIT_FAILURE);
        }
      }
      tab[i] = cs;
      s = NULL;
    }
    tab[i] = NULL;
  }
  return tab;
}
char *str_join (char **cs,int Taille){
   //réunissant des chaînes de caractères grâce à un séparateur
  const char *ct;
  char *s = NULL;
  size_t sz = 0;
  int i=0;
  while (i<Taille)
  {
      ct=cs[i++];
    void *tmp = NULL;
    sz += strlen (ct) + strlen (cs);
    tmp = realloc (s, sizeof (*s) * (sz + 1));
    if (tmp != NULL)
    {
      if (s == NULL)
      {
        s = tmp;
        strcpy (s, ct);
      }
      else
      {
         s = tmp;
         strcat (s, cs);
         strcat (s, ct);
      }
    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      free (s);
      s = NULL;
      exit (EXIT_FAILURE);
    }
  }
  return s;
}
char *str_remplace (const char *s, unsigned int debut, unsigned int lenght, const char *ct){
    //remplacer length caractères de la chaîne s à partir de l'indice start par une nouvelle chaîne ct. Une nouvelle chaîne est créée
  char *new_s = NULL;

  if (s != NULL && ct != NULL && debut >= 0 && lenght > 0)
  {
    size_t sz = strlen (s);

    new_s = malloc (sizeof (*new_s) * (sz - lenght + strlen (ct) + 1));
    if (new_s != NULL)
    {
      memcpy (new_s, s, debut);
      memcpy (&new_s[debut], ct, strlen (ct));
      memcpy (&new_s[debut + strlen (ct)], &s[debut + lenght], sz - lenght - debut + 1);
    }
  }
  else
  {
    fprintf (stderr, "Memoire insuffisante\n");
    exit (EXIT_FAILURE);
  }
  return new_s;
}
char *str_strip (const char *st){
    //supprime les espaces superflus dans une chaîne de caractère
  char *strip = NULL;

  if (st != NULL)
  {
    strip = malloc (sizeof (*strip) * (strlen (st) + 1));
    if (strip != NULL)
    {
      int i, j;
      int ps = 0;

      for (i = 0, j = 0; st[i]; i++)
      {
        if (st[i] == ' ')
        {
          if (ps == 0)
          {
            strip[j] = st[i];
            ps = 1;
            j++;
          }
        }
        else
        {
          strip[j] = st[i];
          ps = 0;
          j++;
        }
      }
      strip[j] = '\0';
    }
    else
    {
      fprintf (stderr, "Memoire insuffisante\n");
      exit (EXIT_FAILURE);
    }
  }
  return strip;
}
void StrSuppChar(char* text,int pos){
    /** on supprime le cractere de la postion pos
     ** les postion sont 0..taille chain-1
     **/
    char *B;
    B=&(text[pos+1]);
    text[pos]='\0';
    strcat(text,B);
}
int isCharSpFr(char ch){
    /** c'est le cractrere ch est un cractere special dans la langue france comme é et ù à ç  return 1
     **/
     switch(ch){
        case 'é':
            return 1;
        case 'è':
            return 1;
        case 'ê':
            return 1;
        case 'à':
            return 1;
        case 'ç':
            return 1;
        case '’':
            return 1;
        case 'â':
            return 1;
        case 'î':
            return 1;
        case 'û':
            return 1;
        case 'ú':
            return 1;
        case 'ô':
            return 1;
        }
return 0;
}
void StrInsertChar(char* text,char ch,int pos){
    /** on insert la caractere ch a postion pos dans chain caractere text
     ** pos = [0..taille de chain]
     **/
    char *B;
    B = malloc (sizeof (char) * (strlen (text) - pos + 2));
    if (B!=NULL){
    strcpy(B,&(text[pos]));
    text[pos]=ch;
    text[pos+1]='\0';
    strcat(text,B);
    free(B);
    }
}
void cputsxyBlanc(int x,int y,const char* chain,int T){

    /** affichez un chaine de cractère à la postion (x,y) dans ecran
     ** affichez seulement T cractére
     ** si la longueur de ch < T donc terminera le affichage par de blanc
     **/

     int i,m=strlen(chain);  //calculer la longueur de chain de cractère ch
     gotoxy(x,y); // allez à la postion (x,y)
     for (i=0;i<T;i++){
        if (i<m) printf("%c",chain[i]);
         else printf(" "); // on complete la rest par de blanc
   }
}
char* TimeActuelle(void){
    time_t tk;
    struct tm *TA;
    time(&tk); // ON LIT LE Time De PC
    TA=localtime(&tk); // ON LES CONVERTIRE
    char* Tm=NULL;
    Tm = malloc (sizeof (*Tm)*(20));
    sprintf(Tm,"data\\%04d%02d%02d%02d%02d%02d",TA->tm_year+1900,TA->tm_mon+1,TA->tm_mday,TA->tm_hour,TA->tm_min,TA->tm_sec);
    return Tm;
}
char** Texte_split (const char *s, const char *ct,int NumberMax){
    //découper une chaîne de caractère suivant un délimiteur et de placer chaque sous-chaîne dans un tableau terminé par NULL
char** tab = NULL;
  int taille=strlen(s);
  int T1=taille/NumberMax+2;
  tab = (char**)malloc((T1)*(sizeof(s)));
    tab[0]=NULL;
  if (s != NULL && ct != NULL)
  {
    int i=0,j;
    int M=NumberMax-1,M1=0;
    while (M<taille){
        j=str_istr(s+M1,"\n");
        if (j>-1 && (j+M1)<=M){
            if (i>=T1) tab=realloc(tab,(i+1)*(sizeof(s)));
            tab[i]=str_sub(s,M1,M1+j-1);
            if (tab[i]!=NULL) i++;
            M1+=j+1;
            M=M1+NumberMax-1;
        }else{
            while(strchr(ct,s[M])==NULL && M>0) M--;
            if (i>=T1) tab=realloc(tab,(i+1)*(sizeof(s)));
            tab[i]=str_sub(s,M1,M);
            if (tab[i]!=NULL) i++;
            M1=M+1;
            M=M1+NumberMax-1;
            }
        }
        while((j=str_istr(s+M1,"\n"))>-1 && M1<taille){
            if (i>=T1) tab=realloc(tab,(i+1)*(sizeof(s)));
            tab[i]=str_sub(s,M1,M1+j-1);
            if (tab[i]!=NULL) i++;
            M1+=j+1;
        }
            if (i>=T1) tab=realloc(tab,(i+2)*(sizeof(s)));
            tab[i]=str_sub(s,M1,taille-1);
            if (tab[i]!=NULL) i++;
            tab[i]=NULL;
        }
  return tab;
}
int *IndexFileTexte(const char *NomFichier,const char *deliminateur,int MaxLine,int *NMot){

    /// donnez tableaux des index de line du fichier text suivant des deliminateur et depasse pas maxline termenra premier case est le nombre du line

    FILE* F=fopen(NomFichier,"r");
    int i,j=1,h,*index;
    char* Line;(*NMot)=0;
    index=malloc(2*sizeof(*index));
    Line=malloc((MaxLine+1)*(sizeof(*Line)));
    while (fgets(Line,MaxLine,F)!=NULL){
        h=strlen(Line);
        (*NMot)+=NbreMot(Line);
        i=h-1;
        if (h==(MaxLine-1)){
            while((strchr(deliminateur,Line[i]))==NULL) i--;
            fseek(F,i-h+1,SEEK_CUR);
        }
        index=realloc(index,(j+2)*sizeof(*index));
        if (j>1) index[j]=index[j-1]+i+1;
            else index[j]=i;
        j++;
    }
    index[0]=j-1;
    fclose(F);
    free(Line);
    return index;
}
void cputsxyAreaBlanc(int x,int y,const char* chain,int max_Nbr_line,int max_length_line,const char *deliminateur){

    /** affichez un chaine de cractère à la postion (x,y) dans ecran
     ** affichez seulement max_length_line cractére dans line et au max max_nbr_line
     ** si la longueur de ch < max_length_line donc terminera le affichage par de blanc
     **/

     int i;
     char** tmp;
     tmp=Texte_split(chain,deliminateur,max_length_line);
     for (i=0;i<max_Nbr_line && tmp[i]!=NULL ;i++) cputsxyBlanc(x,y+i,tmp[i],max_length_line);
     for (;i<max_Nbr_line;i++) cputsxyBlanc(x,y+i," ",max_length_line);
     i=0;
     while(tmp[i]!=NULL){
        free(tmp[i++]);
     }
     //free(tmp);
}
void cputsxyBlancArea(int x,int y,const char* chain,int max_length_line,const char *deliminateur){

    /** affichez un chaine de cractère à la postion (x,y) dans ecran
     ** affichez seulement max_length_line cractére dans line
     **/

     int i;
     char** tmp;
     tmp=Texte_split(chain,deliminateur,max_length_line);
     for (i=0;tmp[i]!=NULL ;i++) {
        cputsxyBlanc(x,y+i,tmp[i],max_length_line);
        free(tmp[i]);
     }
     free(tmp);
}
void cputsxyArea(int x,int y,const char* chain,int max_length_line,const char *deliminateur){

    /** affichez un chaine de cractère à la postion (x,y) dans ecran
     ** affichez seulement max_length_line cractére dans line
     **/

     int i;
     char** tmp=NULL;
     tmp=Texte_split(chain,deliminateur,max_length_line);
     for (i=0;tmp[i]!=NULL ;i++) {
        cputsxy(x,y+i,tmp[i]);
        free(tmp[i]);
     }
     if (tmp!=NULL) free(tmp);
}
void Time_ecoule(time_t temp,char* Time_ecl){
    time_t time_acuteul;
    time(&time_acuteul);
    int diff= (int)(difftime(time_acuteul,temp));
    int heure,minut,second;
    heure=diff/3600;
    minut=(diff%3600)/60;
    second=diff%60;
    sprintf(Time_ecl,"%d heurs %d minuts %d seconds",heure,minut,second);
}
void File_Derectory_Current(char ***Fichier,int *Taille){
    // vous donne le name des fichier qui se trouve dans le dossier current
    // il fait le alloucation alors il dois faire liberation
    system("dir /on > data\\file_tmp");
    FILE* F=fopen("data\\file_tmp","r");
    int i,j;(*Taille)=0;
    char tab[1000];
    while(fgets(tab,1000,F)!=NULL){
        if (isdigit(tab[0]))(*Taille)++;
    }
    (*Fichier)=malloc(sizeof(char*)*((*Taille)+1));
    fseek(F,0,SEEK_SET);
    i=0;
    while(fgets(tab,1000,F)!=NULL){
        if (isdigit(tab[0])){
            if (tab[36]!='.') (*Fichier)[i++]=str_sub(tab,36,strlen(tab)-2);
                else (*Taille)--;
        }
    }
    fclose(F);
    remove("data\\file_tmp");
}
int NbreMot(const char *ch){

    /// COMPTER LE NOMBRE DES MOTS DANS CHAIN CH
    char* p=NULL;
	char deliminateur[]=" ''\t\n,;:\"()_{}<>!?&/\\";
	int cpt=0;
	p = strtok(ch, deliminateur);
    while(p!=NULL)
    {
     cpt++;
     p = strtok(NULL, deliminateur);
    }

    return cpt;
}
int Str_Ramplace_mot(char* chain,const char* mot,const char* nouveaux_mot){

    int i=0,k=0,j=0;
    k=str_istr(chain,mot);
    if (k>-1){
    int taille_chain=strlen(chain),taille_ansien=strlen(mot),taille_nouveau=strlen(nouveaux_mot);
    char *tmp;
    tmp=malloc((taille_chain+2)*(sizeof(char)));
    strcpy(tmp,chain);
    for (i=0;i<taille_nouveau;i++){
        chain[i+k]=nouveaux_mot[i];
    }
    i+=k;
    for (j=k+taille_ansien;j<taille_chain;j++){
        chain[i++]=tmp[j];
    }
    chain[i]=0;
    free(tmp);
    }
    return k>-1;
}


#endif
