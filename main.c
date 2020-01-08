#include "conio.c"
#include "conio.h"
#include "conio2.h"
#include <ctype.h>
#include <gmp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BigInt mpz_t
#include "Input.h"
#include "String++.h"
#include "TP RSA.h"

#define PX 25
#define PY 10
#define HTR 20
#define LNGR 80

#define PX1 25
#define PY1 10
#define HTR1 30
#define LNGR1 80

UtilisateurRSA user_data_Rsa;
void Log_in(UtilisateurRSA *user);
void ChioxMenu();
void Compte_ouvert(int inveter);
void Debut();
int *Corredonne_Recharche_File(const char *chain, const char *NomFichier);
void display_text_Page(int x, int y, int max_char_line, int NumeroPage,
                       int NbrLine, int *index, const char *NomFichier);
// Affiche un page text dans secreen debutera a la postion x et Numero du page
// est suivant un index des line dans le fichier
char *Text_File(const char *NomFichier, int debut, int fin) {

  FILE *F = fopen(NomFichier, "rb");
  if (F == NULL) {
    fprintf(stderr, "Erreur d'ouverture le fichier %s ", NomFichier);
    return 1;
  }
  char *chain = NULL;
  int taille;
  if (debut <= fin) {
    chain = malloc(sizeof(*chain) * (fin - debut + 2));
    if (chain != NULL) {
      fseek(F, debut, SEEK_SET);
      taille = fread(chain, sizeof(char), fin - debut + 1, F);
      chain[taille] = '\0';
    } else {
      fprintf(stderr, "Memoire insuffisante\n");
      exit(EXIT_FAILURE);
    }
  }
  fclose(F);
  return chain;
}

int main() {
  system("mode con LINES=1000 COLS=130");
  /*char A[256],a[255],b[255];
  do{
      fgets(A,255,stdin);
      fscanf(stdin,"%s %s",a,b);
      printf("%s ---> ",A);
      Str_Ramplace_mot(A,a,b);
      printf("%s",A);
  }while(1);
*/
  ChioxMenu();
  return 0;
}
void ChioxMenu() {
  int i;
  int a = 4;
  char *A[] = {"Connecter", "Creer Compte", "Invite", "Quitter Le Programme"};
  do {
    Debut();
    do {
      textbackground(BLACK);
      system("CLS");
      textbackground(WHITE);
      textcolor(GREEN);
      FrameRectangle(PX - 1, PY - 1, LNGR + 2, HTR + 2, 4);
      textcolor(BLACK);
      i = Menu(A, a, PX, PY, LNGR, HTR, WHITE, LIGHTGRAY);
      if (i == 0)
        break;
      if (i == 1) {
        // Connecter
        Log_in(&user_data_Rsa);
      } else if (i == 2) {
        // Creer Compte
        Create_new_RSA_Account();
      } else if (i == 3) {
        // Inviter
        Read_RSA_File("cle rsa.txt", &user_data_Rsa);
        Compte_ouvert(1);
      } else if (i == 4) {
        // Quiter Le programme

        // FIN();
        return 0;
      }
    } while (1);
  } while (1);
}
void Compte_ouvert(int inveter) {
  int i;
  int b = 5;
  int c3 = 10;
  char **B;
  B = malloc(6 * sizeof(char *));
  for (i = 0; i < b; i++)
    B[i] = malloc(100 * sizeof(char));
  strcpy(B[2], "CRYPTOGRAPHY RSA ");
  strcpy(B[0], "Display");
  strcpy(B[3], "Calcule  RSA ");
  strcpy(B[1], "Search and Replace");
  if (inveter)
    strcpy(B[4], "Retourne au menu principale and save data ");
  else
    strcpy(B[4], "Ferme Session and save data  ");
  char *C3[] = {"Genere Cle Aleatoire ",
                "Genere Nombre Premier Aleatoire ",
                "Teste C'est Premier Avec les Proba ",
                "Teste C'est Premier Avec les Division",
                "Le Nombre Premier Proche a Nombre Donner ",
                "Creer Cle Avec P et Q ",
                "Ajoutez Cle Manulement",
                "Liste Des Nombres Premiers",
                "Liste Des Cles Publics",
                "Liste Des Cles Publics et Prives"};
  int c1 = 2, c;
  char *C1[] = {"Crypter un fichier", "Decrypter un fichier"};
  srand(time(NULL));
  gmp_randstate_t state;
  gmp_randinit_default(state);
  gmp_randseed_ui(state, (unsigned)time(NULL));
  do {
    textbackground(BLACK);
    system("CLS");
    textbackground(WHITE);
    textcolor(GREEN);
    FrameRectangle(PX - 1, PY - 1, LNGR + 2, HTR + 2, 4);
    textcolor(BLACK);
    i = Menu(B, b, PX, PY, LNGR, HTR, WHITE, LIGHTGRAY);
    if (i == 0)
      continue;
    if (i == 3) {
      /// Cryptography
      do {
        textbackground(BLACK);
        system("CLS");
        textbackground(WHITE);
        textcolor(GREEN);
        FrameRectangle(PX - 1, PY - 1, LNGR + 2, HTR + 2, 4);
        textcolor(BLACK);
        i = Menu(C1, c1, PX, PY, LNGR, HTR, WHITE, LIGHTGRAY);
        if (i == 0)
          break;
        if (i == 1) {
          if ((user_data_Rsa.TClePublic) != 0) {
            choix_crypt(user_data_Rsa);
          } else {
            textbackground(BLACK);
            system("CLS");
            textcolor(WHITE);
            cputsxy(10, 15, "La liste est vide va remplire calcule rsa");
            system("PAUSE");
          }
        } else if (i == 2) {
          if ((user_data_Rsa.TCleComplet) != 0) {
            choix_Decrypt(user_data_Rsa);
          } else {
            textbackground(BLACK);
            system("CLS");
            textcolor(WHITE);
            cputsxy(10, 15, "La liste est vide va remplire calcule rsa");
            system("PAUSE");
          }
        }
      } while (1);

    } else if (i == 1) {
      /// Editeur de Texte
      EditeurText();
    } else if (i == 4) {
      /// Calcule RSA

      do {

        textbackground(BLACK);
        system("CLS");
        textbackground(WHITE);
        textcolor(GREEN);
        FrameRectangle(PX - 1, PY - 1, LNGR + 2, HTR + 2, 4);
        textcolor(BLACK);
        i = Menu(C3, c3, PX, PY, LNGR, HTR, WHITE, LIGHTGRAY);

        if (i == 0)
          break;
        if (i == 1) {
          /// Genere Cle Aleatoire
          Genere_Cle_Aleatoire(&user_data_Rsa, state);
        } else if (i == 2) {
          /// Genere Nombre Premier Aleatoire
          Genere_Premier(&user_data_Rsa, state);
        } else if (i == 4) {
          /// Tester c'est Premier Avec la Division
          Test_Prime(&user_data_Rsa);
        } else if (i == 3) {
          /// Teste C'est Premier avec les probabiliter
          Test_Propa_Prime(&user_data_Rsa);
        } else if (i == 5) {
          /// Le Nombre Premier Le Proche a Nombre Donner
          Next_Prime(&user_data_Rsa);
        } else if (i == 6) {
          /// Creer Cle Avec P et Q
          Creer_Cle(&user_data_Rsa);
        } else if (i == 8) {
          /// Votre Liste Des Nombres Premiers
          if (user_data_Rsa.TPremier == 0) {
            textbackground(BLACK);
            system("CLS");
            textcolor(WHITE);
            printf("LA LISTE EST VIDE  AJOUTES DES CLE DANS LA PARTIE CALCULE "
                   "RSA MERCI ...");
            getch();
          } else {
            do {
              textbackground(BLACK);
              system("CLS");
              textbackground(WHITE);
              textcolor(GREEN);
              FrameRectangle(PX1 - 1, PY1 - 1, LNGR1 + 2, HTR1 + 2, 4);
              textcolor(BLACK);
              i = Menu(user_data_Rsa.NomPremier, user_data_Rsa.TPremier, PX1,
                       PY1, LNGR1, HTR1, WHITE, LIGHTGRAY);
              if (i == 0)
                break;
              textbackground(WHITE);
              system("CLS");
              textcolor(BLACK);
              gotoxy(20, 2);
              printf("Le Nombre Premier Avec le nom %s est :\n\n",
                     (user_data_Rsa.NomPremier)[i - 1]);
              printf("\tNombre Premier=%s\n\n\t",
                     (user_data_Rsa.Premier)[i - 1]);
              printf("\t\t Apuiyer sur < retoure <-- > pour supprimer cette "
                     "cle ou d'autre touch pour retourner en arreier ");
              c = getch();
              if (c == 8) {
                if (AreYouSure(20, 10)) {
                  free((user_data_Rsa.Premier)[i - 1]);
                  free((user_data_Rsa.NomPremier)[i - 1]);
                  (user_data_Rsa.Premier)[i - 1] =
                      (user_data_Rsa.Premier)[(user_data_Rsa.TPremier) - 1];
                  (user_data_Rsa.NomPremier)[i - 1] =
                      (user_data_Rsa.NomPremier)[(user_data_Rsa.TPremier) - 1];
                  (user_data_Rsa.TPremier)--;
                  if (user_data_Rsa.TPremier == 0)
                    break;
                }
              }

            } while (1);
          }
        } else if (i == 7) {
          /// Ajoutez Cle Manulement
          Lire_cle_complet(&user_data_Rsa);
        } else if (i == 9) {
          /// Votre Liste Des Cles Publics
          if (user_data_Rsa.TClePublic == 0) {
            textbackground(BLACK);
            system("CLS");
            textcolor(WHITE);
            printf("LA LISTE EST VIDE  AJOUTES DES CLE DANS LA PARTIE CALCULE "
                   "RSA MERCI ...");
            getch();
          } else {
            do {
              textbackground(BLACK);
              system("CLS");
              textbackground(WHITE);
              textcolor(GREEN);
              FrameRectangle(PX1 - 1, PY1 - 1, LNGR1 + 2, HTR1 + 2, 4);
              textcolor(BLACK);
              i = Menu(user_data_Rsa.NomClePublic, user_data_Rsa.TClePublic,
                       PX1, PY1, LNGR1, HTR1, WHITE, LIGHTGRAY);
              if (i == 0)
                break;
              textbackground(WHITE);
              system("CLS");
              textcolor(BLACK);
              gotoxy(20, 2);
              printf("Le cle publice Avec le nom %s est :\n\n",
                     (user_data_Rsa.NomClePublic)[i - 1]);
              printf("\tn=%s\n\n\te=%s\n\n\t",
                     (user_data_Rsa.ClePublicN)[i - 1],
                     (user_data_Rsa.ClePublicE)[i - 1]);
              printf("\t\t Apuiyer sur <retoure <-- > pour supprimer cette cle "
                     "ou d'autre touch pour retourner en arreier ");
              c = getch();
              if (c == 8) {
                if (AreYouSure(20, 10)) {
                  free((user_data_Rsa.ClePublicN)[i - 1]);
                  free((user_data_Rsa.NomClePublic)[i - 1]);
                  free((user_data_Rsa.ClePublicE)[i - 1]);
                  (user_data_Rsa.ClePublicN)[i - 1] =
                      (user_data_Rsa
                           .ClePublicN)[(user_data_Rsa.TClePublic) - 1];
                  (user_data_Rsa.ClePublicE)[i - 1] =
                      (user_data_Rsa
                           .ClePublicE)[(user_data_Rsa.TClePublic) - 1];
                  (user_data_Rsa.NomClePublic)[i - 1] =
                      (user_data_Rsa
                           .NomClePublic)[(user_data_Rsa.TClePublic) - 1];
                  (user_data_Rsa.TClePublic)--;
                  if (user_data_Rsa.TClePublic == 0)
                    break;
                }
              }
            } while (1);
          }
        } else if (i == 10) {
          /// Votre Liste Des Cles Publics et Prives
          if (user_data_Rsa.TCleComplet == 0) {
            textbackground(BLACK);
            system("CLS");
            textcolor(WHITE);
            printf("LA LISTE EST VIDE  AJOUTES DES CLE DANS LA PARTIE CALCULE "
                   "RSA MERCI ...");
            getch();
          } else {
            do {
              textbackground(BLACK);
              system("CLS");
              textbackground(WHITE);
              textcolor(GREEN);
              FrameRectangle(PX1 - 1, PY1 - 1, LNGR1 + 2, HTR1 + 2, 4);
              textcolor(BLACK);
              i = Menu(user_data_Rsa.NomCleComplet, user_data_Rsa.TCleComplet,
                       PX1, PY1, LNGR1, HTR1, WHITE, LIGHTGRAY);
              if (i == 0)
                break;
              textbackground(WHITE);
              system("CLS");
              textcolor(BLACK);
              gotoxy(20, 2);
              printf("Le cle Complet Avec le nom %s est :\n\n",
                     (user_data_Rsa.NomCleComplet)[i - 1]);
              printf("\tn=%s\n\n\te=%s\n\n\td=%s\n\n\t",
                     (user_data_Rsa.CleCompletN)[i - 1],
                     (user_data_Rsa.CleCompletE)[i - 1],
                     (user_data_Rsa.CleCompletD)[i - 1]);
              printf("\t\t Apuiyer sur <retoure <-- > pour supprimer cette cle "
                     "ou d'autre touch pour retourner en arreier ");
              c = getch();
              if (c == 8) {
                if (AreYouSure(20, 10)) {
                  free((user_data_Rsa.CleCompletN)[i - 1]);
                  free((user_data_Rsa.NomCleComplet)[i - 1]);
                  free((user_data_Rsa.CleCompletD)[i - 1]);
                  free((user_data_Rsa.CleCompletE)[i - 1]);
                  (user_data_Rsa.CleCompletN)[i - 1] =
                      (user_data_Rsa
                           .CleCompletN)[(user_data_Rsa.TCleComplet) - 1];
                  (user_data_Rsa.CleCompletE)[i - 1] =
                      (user_data_Rsa
                           .CleCompletE)[(user_data_Rsa.TCleComplet) - 1];
                  (user_data_Rsa.CleCompletD)[i - 1] =
                      (user_data_Rsa
                           .CleCompletD)[(user_data_Rsa.TCleComplet) - 1];
                  (user_data_Rsa.NomCleComplet)[i - 1] =
                      (user_data_Rsa
                           .NomCleComplet)[(user_data_Rsa.TCleComplet) - 1];
                  (user_data_Rsa.TCleComplet)--;
                  if (user_data_Rsa.TCleComplet == 0)
                    break;
                }
              }
            } while (1);
          }
        }
      } while (1);

    } else if (i == 2) {
      /// recharche
      char *Nom;
      if (Nom_Fichier(&Nom) != 0) {
        textbackground(BLACK);
        recharche_ramplacer(Nom);
      }
    } else if (i == 5) {
      /// Fermer la session
      if (inveter == 0)
        Save_File_Data_RSA(user_data_Rsa);
      else
        Write_RSA_File(user_data_Rsa, "cle rsa.txt");
      liberer_sup_Continu_UtilisateurRSA(&user_data_Rsa);
      return 0;
    }
  } while (1);
}
void EditeurText(void) {

  char *Nom;
  if (Nom_Fichier(&Nom) == 0)
    return 1;
  textbackground(BLACK);
  system("CLS");
  PrintFile(Nom);
  // recharche_ramplacer(Nom);
}
void PrintFile(const char *NomFichier) {
  char deliminateur[] = " \t\n,;:)_}>!?&/\\";
  int *index;
  int i = 0, j = 0, i1 = 0, j1 = 0, x = 10, y = 5, ch, Last_Page, tmp_in,
      Nbr_mot;
  int LongEcran = 30, LargeEcran = 130;
  int NumeroPage = 1, NbrPage, LinePage = 50, line_char_max = 80,
      espace_entre_page = 1, videH = 5, videL = 5;
  index = IndexFileTexte(NomFichier, " \t\n,.;:)!?0123456789", line_char_max,
                         &Nbr_mot);
  NbrPage = index[0] / LinePage + 1; // le nombre des page
  char *sta1 = NULL;
  sta1 = malloc(900 * sizeof(char));
  textcolor(BLACK);
  textbackground(WHITE);
  sprintf(sta1,
          "  Nombre des pages : %d\n  Nombre des mots : %d\n  Nombre des "
          "Linges : %d\n  Nombre des Chars : %d",
          NbrPage, Nbr_mot, index[0], index[index[0]]);
  cputsxyAreaBlanc(30, 15, sta1, 5, 40, "\n : 0123456789");
  getch();
  free(sta1);
  DrawRectangle(x, y, line_char_max + 2 * videL,
                LinePage + 2 * videH); // affiche page plan
  gotoxy(x + videL - 3 + line_char_max / 2,
         y + (videL * 3) / 2 + LinePage); // affiche nemero de page
  printf("%02d / %02d", NumeroPage, NbrPage);
  display_text_Page(x + videL, y + videH, line_char_max, NumeroPage, LinePage,
                    index, NomFichier);
  i1 = 1;
  j1 = 1;
  Last_Page = y + LinePage + 2 * videH;
  gotoxy(i1, j1);
  do {
    ch = SaiserCtrlText();
    if (ch == 72) {
      // touch up
      gotoxy(j1, --i1);
    } else if (ch == 80) {
      // touch down
      i1++;
      gotoxy(j1, i1 + LongEcran);
    } else if (ch == 77) {
      // touch right
      j1++;
      gotoxy(j1 + LargeEcran, i1);
    } else if (ch == 75) {
      // touch left
      gotoxy(--j1, i1);
    } else if (ch == 81) {
      // touch page suivant
      i1 += LongEcran;
      if (NumeroPage < NbrPage && (i1 + LongEcran) >= Last_Page) {
        tmp_in = (NumeroPage) * (LinePage + 2 * videH + espace_entre_page);
        NumeroPage++;
        textbackground(WHITE);
        textcolor(BLACK);
        DrawRectangle(x, y + tmp_in, line_char_max + 2 * videL,
                      LinePage + 2 * videH); // affiche page plan
        gotoxy(x + videL - 3 + line_char_max / 2,
               y + (videL * 3) / 2 + LinePage +
                   tmp_in); // affiche nemero de page
        printf("%02d / %02d", NumeroPage, NbrPage);
        display_text_Page(x + videL, y + videH + tmp_in, line_char_max,
                          NumeroPage, LinePage, index, NomFichier);
        Last_Page = y + LinePage + 2 * videH + tmp_in;
      }

      gotoxy(j1, i1 + LongEcran);
    } else if (ch == 73) {
      // touch page precedant
      i1 -= LongEcran;
      gotoxy(j1, i1);
    } else if (ch == 71) {
      // num lk page
      i1 = 1;
      gotoxy(j1, i1);
    } else if (ch == 79) {
      // FIN page
      gotoxy(j1, Last_Page);
      i1 = Last_Page - LongEcran;
    } else if (ch == 13) {
      // touch etres

    } else if (ch == 27) {
      // touch echap
      free(index);
      return 1;
    } else if (ch == 61) {
      // touch F3

    } else if (ch == 9) {
      // touch --
      char *sta = NULL;
      sta = malloc(900 * sizeof(char));
      if (sta != NULL) {
        textcolor(BLACK);
        textbackground(YELLOW);
        sprintf(sta,
                "  Nombre des pages : %d\n  Nombre des mots : %d\n  Nombre des "
                "Linges : %d\n  Nombre des Chars : %d",
                NbrPage, Nbr_mot, index[0], index[index[0]]);
        Page_Temporaire(10, 5, 40, 5, sta);
        free(sta);
        textcolor(BLACK);
        textbackground(WHITE);
      }
    } else if (ch == 8) {
      // touch Ramplacer ctrl H
      recharche_ramplacer(NomFichier);
      free(index);
      return 1;
    } else if (ch == 6) {
      // touch Recharche ctrl F
      int *cord;
      char mot[30] = "\0";
      do {
        textcolor(BLACK);
        ch = Input_Text(mot, 1, 1, 15);
        if (ch == 27) {
          break;
        } else if (ch == 13) {
          cord = Corredonne_Recharche_File(mot, NomFichier);
          gotoxy(1, 2);
          printf("Nombre d'occrance est %d             ", cord[0]);
          char *stacord = NULL;
          int jkl = 0, hg = 1;
          textcolor(BLACK);
          stacord = malloc(80 * (cord[0] + 1) * sizeof(char));
          for (jkl = 1; jkl <= cord[0]; jkl++) {
            while (index[hg + 1] <= cord[jkl])
              hg++;
            tmp_in = ((hg + 1) / LinePage) *
                     (LinePage + 2 * videH + espace_entre_page);
            textbackground(YELLOW);
            if (cord[jkl] < index[hg])
              gotoxy(x + videL + cord[jkl],
                     y + videH + tmp_in + (hg) % LinePage - 1);
            else
              gotoxy(x + videL + cord[jkl] - index[hg],
                     y + videH + tmp_in + (hg) % LinePage - 1);
            printf("%s", mot);
            do {
              ch = getch();
            } while (ch != 13 && ch != 27);
            if (cord[jkl] < index[hg])
              gotoxy(x + videL + cord[jkl],
                     y + videH + tmp_in + (hg) % LinePage - 1);
            else
              gotoxy(x + videL + cord[jkl] - index[hg],
                     y + videH + tmp_in + (hg) % LinePage - 1);
            textbackground(WHITE);
            printf("%s", mot);
            if (ch == 27)
              break;
          }
          free(stacord);
          textcolor(BLACK);
          textbackground(WHITE);
        }
      } while (1);
    } else if (ch == 32) {
      // touch Espace
      i1 += LongEcran;
      if (NumeroPage < NbrPage && (i1 + LongEcran) >= Last_Page) {
        tmp_in = (NumeroPage) * (LinePage + 2 * videH + espace_entre_page);
        NumeroPage++;
        textbackground(WHITE);
        textcolor(BLACK);
        DrawRectangle(x, y + tmp_in, line_char_max + 2 * videL,
                      LinePage + 2 * videH); // affiche page plan
        gotoxy(x + videL - 3 + line_char_max / 2,
               y + (videL * 3) / 2 + LinePage +
                   tmp_in); // affiche nemero de page
        printf("%02d / %02d", NumeroPage, NbrPage);
        display_text_Page(x + videL, y + videH + tmp_in, line_char_max,
                          NumeroPage, LinePage, index, NomFichier);
        Last_Page = y + LinePage + 2 * videH + tmp_in;
      }

      gotoxy(j1, i1 + LongEcran);
    }
  } while (1);
}
void display_text_Page(int x, int y, int max_char_line, int NumeroPage,
                       int NbrLine, int *index, const char *NomFichier) {
  // Affiche un page text dans secreen debutera a la postion x et Numero du page
  // est suivant un index des line dans le fichier
  int j = 1, debut = 0, fin = 0;
  j = (NumeroPage - 1) * NbrLine;
  if (j > 0)
    debut = index[j];
  j = j + NbrLine;
  if (j <= index[0])
    fin = index[j] - 1;
  else
    fin = index[index[0]] - 1;
  char *tx = Text_File(NomFichier, debut, fin);
  cputsxyArea(x, y, tx, max_char_line, " \t\n,.;:)!? }0123456789");
  free(tx);
}
int *Corredonne_Recharche_File(const char *chain, const char *NomFichier) {

  FILE *F = fopen(NomFichier, "r");
  int i = 0, j = 0, h, k, *index, c;
  char *Line;
  index = malloc(2 * sizeof(*index));
  Line = malloc((256) * (sizeof(*Line)));
  index[0] = 0;
  j = 1;
  while (fgets(Line, 255, F) != NULL) {
    c = 0;
    while ((k = str_istr(Line + c, chain)) > -1 && Line[c] != 0) {
      index = realloc(index, (j + 2) * sizeof(*index));
      index[j++] = i + c + k;
      c += k + 1;
    }
    i = ftell(F);
  }
  index[0] = j - 1;
  fclose(F);
  free(Line);

  return index;
}
void Page_Temporaire(int x, int y, int longueur, int hauteur,
                     const char *text) {
  /// affiche page avec text si apuiyer entre elle dispareur
  struct char_info *AncienTexte;
  AncienTexte =
      malloc((longueur + 2) * (hauteur + 4) * sizeof(struct char_info));
  if (AncienTexte != NULL) {
    gettext(x, y - 1, x + longueur, y + hauteur + 3, AncienTexte);
    cputsxyBlanc(x, y - 1, " ", longueur);
    cputsxyAreaBlanc(x, y, text, hauteur, longueur, " :");
    cputsxyBlanc(x, y + hauteur, " ", longueur);
    cputsxyBlanc(x, y + hauteur + 1, " ", longueur);
    cputsxyBlanc(x, y + hauteur + 2, " ", longueur);
    textcolor(BLACK);
    textbackground(LIGHTCYAN);
    AfficheButton("Ok", x + longueur / 2 - 5, y + hauteur, 10, 3);
    int c;
    do {
      c = getch();
    } while (c != 13);
    puttext(x, y - 1, x + longueur, y + hauteur + 3, AncienTexte);
    // free(AncienTexte);
  } else
    fprintf(stderr, "erreur de alocation");

  return 0;
}
void recharche_ramplacer(const char *NomFichier) {

  textbackground(BLACK);
  system("CLS");
  textcolor(WHITE);
  char mot[50] = "\0", nouveau_mot[50] = "\0";
  if (Lire_mot_recharche(mot, nouveau_mot))
    return 1;
  int *index;
  int x = 0, y = 0, a = 10, b = 5, ch, Nbr_mot;
  int NbrPage, LinePage = 50, line_char_max = 80;
  index = IndexFileTexte(NomFichier, " \t\n,.;:)!?", line_char_max, &Nbr_mot);
  NbrPage = index[0] / LinePage + 1; // le nombre des page
  int *cord;
  cord = Corredonne_Recharche_File(mot, NomFichier);
  char *stacord = NULL;
  int jkl = 0, hg = 0, jj;
  stacord = malloc(80 * (cord[0] + 1) * sizeof(char));
  textbackground(BLACK);
  system("CLS");
  textcolor(WHITE);
  if (stacord != NULL) {
    sprintf(stacord, "  Nombre d'occrance est %d", cord[0]);
    for (jkl = 1; jkl <= cord[0]; jkl++) {
      while (index[hg + 1] <= cord[jkl])
        hg++;
      if (hg <= index[0]) {
        if (index[hg] <= cord[jkl])
          jj = cord[jkl] - index[hg] + 1;
        else if (hg == 1)
          jj = cord[jkl] + 1;
      } else
        jj = cord[jkl] - index[index[0]] + 1;
      sprintf(stacord, "%s\n  %d : Page %d Line %d Position %d", stacord, jkl,
              (hg + 1) / LinePage + 1, (hg) % LinePage + 1, jj);
    }
    int *ramplace_boulean;
    ramplace_boulean = calloc((cord[0] + 1), sizeof(int));
    textbackground(WHITE);
    textcolor(BLACK);
    cputsxyAreaBlanc(a, b, stacord, cord[0] + 5, 100, " \n : ");
    if (cord[0] == 0) {
      getch();
      goto FI;
    }
    x = a;
    y = b + cord[0] + 5, textcolor(BLACK);
    textbackground(BLUE);
    AfficheButton("Ramplacer", x, y + 3, 12, 3);
    textbackground(LIGHTCYAN);
    AfficheButton("Ramplacer tous", x + 20, y + 3, 15, 3);
    int i = 1, c;
    do {
      do {
        c = SaiserCntrl();
      } while (c != 13 && c != 75 && c != 77 && c != 27);
      if (c == 27) {
        goto FI;
      } else if (c == 13) {
        break;
      } else if (i == 1) {
        textbackground(LIGHTCYAN);
        AfficheButton("Ramplacer", x, y + 3, 12, 3);
        textbackground(BLUE);
        AfficheButton("Ramplacer tous", x + 20, y + 3, 15, 3);
        i = 0;
      } else {
        textbackground(BLUE);
        AfficheButton("Ramplacer", x, y + 3, 12, 3);
        textbackground(LIGHTCYAN);
        AfficheButton("Ramplacer tous", x + 20, y + 3, 15, 3);
        i = 1;
      }
    } while (1);
    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    if (i == 1) {
      FILE *F = fopen(NomFichier, "r");
      FILE *G = fopen("tmppppp.txt", "w");
      int j1 = 0, k1, c1, i1 = 0;
      char *Line1;
      Line1 = malloc((256) * (sizeof(*Line1)));
      if (Line1 != NULL) {
        while (fgets(Line1, 255, F) != NULL) {
          c1 = 0;
          while ((k1 = str_istr(Line1 + c1, mot)) > -1 && Line1[c1] != 0) {
            textcolor(WHITE);
            textbackground(BLACK);
            system("CLS");
            gotoxy(1, 5);
            // printf("%s",Line1);
            i1 = 0;
            while (Line1[i1] != 0)
              putch((unsigned char)(Line1[i1++]));
            // puts(Line1);
            textcolor(BLACK);
            textbackground(YELLOW);
            gotoxy(c1 + k1 + 1, 5);
            printf("%s", mot);
            if (AreYouSure(15, 10)) {
              Str_Ramplace_mot(Line1 + c1, mot, nouveau_mot);
            }
            c1 += k1 + 1;
          }
          fprintf(G, "%s", Line1);
        }
        fclose(F);
        fclose(G);
        remove(NomFichier);
        if (rename("tmppppp.txt", NomFichier))
          fprintf(stderr, "Erreur de Renamation");
        ;
        free(Line1);
      } else
        fprintf(stderr, "Erreur de alocation");

      /*
      hg=1;
  for(jkl=1;jkl<=cord[0];jkl++){
  while (index[hg+1]<=cord[jkl]) hg++;
  textcolor(WHITE);
  textbackground(BLACK);
  system("CLS");
  gotoxy(10,5);
  if (hg<=index[0]){
      if (index[hg]<=cord[jkl]) jj=cord[jkl]-index[hg]+1;
          else if (hg==1) jj=cord[jkl]+1;
  }else jj=cord[jkl]-index[index[0]]+1;
  printf("Occurance %d : Page %d Line %d Position
  %d",jkl,(hg+1)/LinePage+1,(hg)%LinePage+1,jj); if (AreYouSure(15,7))
  ramplace_boulean[jkl-1]=1; else ramplace_boulean[jkl-1]=0;

  }*/
    } else {
      for (jkl = 1; jkl <= cord[0]; jkl++)
        ramplace_boulean[jkl - 1] = 1;
      Ramplace_File(NomFichier, mot, nouveau_mot, ramplace_boulean);
    }

    textbackground(BLACK);
    system("CLS");
    textcolor(WHITE);
    cputsxyTemp(15, 5, "Le remplacemant est terminer avec succes merci ... ",
                15);
  FI:
    free(index);
    free(ramplace_boulean);
    free(stacord);
  }
}
int Lire_mot_recharche(char *Mot, char *Nouveau_Mot) {
  // textbackground(LIGHTBLUE);
  system("CLS");
  // textattr(169);
  // FrameRectangle(40,5,80,60,'|');
  int x = 40, y = 2;
  textcolor(LIGHTBLUE);
  cputsxy(x + 10, y + 4, "Recharhce et Ramplacer un Mot");
  textcolor(WHITE);
  cputsxy(x, y + 7, "Mot Recharcher");
  cputsxy(x, y + 13, "Nouveau Mot");
  textcolor(RED);
  putchxy(x + 16, y + 7, '*');
  putchxy(x + 12, y + 13, '*');
  textbackground(WHITE);
  DrawRectangle(x, y + 8, 48, 2);
  DrawRectangle(x, y + 14, 48, 2);
  textbackground(LIGHTCYAN);
  textcolor(WHITE);
  AfficheButton("Recharcher", x, y + 20, 20, 3);
  int NumbreInput = 1;
  int c = 0;
  Mot[0] = 0;
  Nouveau_Mot[0] = 0;
  textbackground(WHITE);
  textcolor(BLACK);
  do {
    if (NumbreInput > 0 && NumbreInput < 3) {

      if (NumbreInput == 1) {
        // Mot
        c = Input_Text(Mot, x, y + 9, 48);

      } else if (NumbreInput == 2) {
        // Nouveau_Mot
        c = Input_Text(Nouveau_Mot, x, y + 15, 48);
      }
      if (c == 80 || c == 81 || c == 9 || c == 13)
        NumbreInput++;
      else if (c == 72 || c == 73) {
        NumbreInput--;
        if (NumbreInput == 0)
          NumbreInput = 3;
      }
    } else if (NumbreInput == 3) {
      // Button recharche
      textbackground(BLUE);
      textcolor(WHITE);
      AfficheButton("Recharcher", x, y + 20, 20, 3);
      do {
        c = SaiserCntrl();
      } while (c == 75 ||
               c == 77); // car here touch left and right ne faite rien
      if (c == 13) {
        if (!(Mot[0] && Nouveau_Mot[0])) {
          // This is input vide
          AfficheErreur(x + 5, y + 5,
                        "You have to fill in the input they are required.");
          textcolor(BLACK);
          textbackground(WHITE);
          continue;
        }
        return 0;

      } else if (c == 80 || c == 81 || c == 9)
        NumbreInput = 1;
      else if (c == 72 || c == 73)
        NumbreInput = 2;
      textbackground(LIGHTCYAN);
      AfficheButton("Recharcher", x, y + 20, 20, 3);
      textbackground(WHITE);
      textcolor(BLACK);
    }
    if (c == 27) {
      // return Backs
      if (AreYouSure(20, 15))
        return 1;
      textbackground(WHITE);
      textcolor(BLACK);
    }
  } while (1);
  return 0;
}
void Ramplace_File(const char *NomFichier, const char *mot,
                   const char *nouveaux_mot, int *ramplace_boulean) {
  FILE *F = fopen(NomFichier, "r");
  FILE *G = fopen("tmppppp.txt", "w");
  int j = 0, k, c;
  char *Line;
  Line = malloc((256) * (sizeof(*Line)));
  if (Line != NULL) {
    while (fgets(Line, 255, F) != NULL) {
      c = 0;
      while ((k = str_istr(Line + c, mot)) > -1 && Line[c] != 0) {
        if (ramplace_boulean[j++])
          Str_Ramplace_mot(Line + c, mot, nouveaux_mot);
        c += k + 1;
      }
      fprintf(G, "%s", Line);
    }
    fclose(F);
    fclose(G);
    remove(NomFichier);
    if (rename("tmppppp.txt", NomFichier))
      fprintf(stderr, "Erreur de Renamation");
    ;
    free(Line);
  } else
    fprintf(stderr, "Erreur de alocation");
}

void Debut() {
  system("CLS");
  int z = 40;
  int w = 10;
  char a = 219;
  system("cls");
  puts("    ");
  textbackground(15);
  system("cls");
  gotoxy(z, w - 3);
  textcolor(0);

  printf("                 ---| ECOLE SUPERIEURE D'INFORMATIQUE ESI |---  ");
  textcolor(0);
  puts("    ");
  puts("    ");
  textcolor(15);

  gotoxy(z, w + 5);
  printf("<>");
  textcolor(3);

  gotoxy(z, w + 1);
  printf("                     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c      "
         "%c%c%c%c%c%c%c%c%c     ",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 2);
  printf("                     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c      "
         "%c%c%c%c%c%c%c%c%c      ",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 3);
  printf(
      "                     %c%c       %c%c   %c%c             %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 4);
  printf(
      "                     %c%c       %c%c   %c%c             %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 5);
  printf(
      "                     %c%c       %c%c   %c%c             %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 6);
  printf("                     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c      "
         "%c%c%c%c%c%c%c%c%c    ",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 7);
  printf("                     %c%c%c%c%c%c%c%c%c     %c%c%c%c%c%c%c%c%c      "
         "%c%c%c%c%c%c%c%c%c     ",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 8);
  printf(
      "                     %c%c %c%c                %c%c      %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 9);
  printf(
      "                     %c%c   %c%c              %c%c      %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 10);
  printf(
      "                     %c%c    %c%c             %c%c      %c%c     %c%c",
      a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 11);
  printf("                     %c%c     %c%c     %c%c%c%c%c%c%c%c%c      %c%c  "
         "   %c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z, w + 12);
  printf("                     %c%c      %c%c    %c%c%c%c%c%c%c%c%c      %c%c  "
         "   %c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  gotoxy(z + 20, w + 13);
  printf("\n");
  textcolor(4);
  printf("                                         < CRYPTOGRAPHIE RSA > |");
  textcolor(12);
  printf("                                                 | V 1.0 ");
  puts("                          ");
  textcolor(0);
  printf("                                         "
         "_____________________________________________________________________"
         "_________");
  printf("\n");
  textcolor(5);
  printf("                                        |%c%c                        "
         "                                                    %c%c|",
         a, a, a, a);
  textcolor(0);
  printf("\n");
  textcolor(5);
  printf("                                        |%c%c           REALISE PAR  "
         " --->   CHAKLALA LAHCENE | ISMAIL KHERBACH          %c%c|",
         a, a, a, a);
  textcolor(0);
  printf("\n");
  printf("                                        "
         "|%c%c________________________________________________________________"
         "___________ %c%c|",
         a, a, a, a);
  textcolor(0);
  printf("\n");
  printf("                                        |%c%C                        "
         "                                                     %c%c|",
         a, a, a, a);
  textcolor(5);
  printf("\n");
  printf("                                        |%c%c           SECTION A    "
         "--|-->    2CPI   --|-->    GO4                      %c%c|",
         a, a, a, a);
  textcolor(5);
  printf("\n");
  textcolor(5);
  printf("                                        "
         "|%c%c________________________________________________________________"
         "____________%c%c|",
         a, a, a, a);
  textcolor(0);
  printf("\n");
  printf("                                        "
         "|%c%c________________________________________________________________"
         "___________ %c%c|",
         a, a, a, a);
  textcolor(0);
  printf("\n");
  printf("                                        |%c%C                        "
         "                                                     %c%c|",
         a, a, a, a);
  textcolor(5);
  printf("\n");
  printf("                                        |%c%c           ENCADRE PAR "
         "MR KERMI ADEL                                        %c%c|",
         a, a, a, a);
  textcolor(5);
  printf("\n");
  textcolor(5);
  printf("                                        "
         "|%c%c________________________________________________________________"
         "____________%c%c|",
         a, a, a, a);
  textcolor(5);
  printf("\n");
  textcolor(0);
  puts("                          ");
  printf("                                                       "
         "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%"
         "c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a);
  printf("\n");
  textcolor(4);
  printf("                                                       %c%c%c%c%c    "
         "                                      %c%c%c%c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  printf("\n");
  printf("                                                       %c%c%c%c%c    "
         "    | CLIQUER POUR CONTINUER |        %c%c%c%c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  printf("\n");
  printf("                                                       %c%c%c%c%c    "
         "                                      %c%c%c%c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  textcolor(0);
  printf("\n");
  printf("                                                       "
         "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%"
         "c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a);

  puts("                         ");
  printf("\n");
  printf("\n");
  printf("\n");
  puts("                                                                       "
       "                       Copyrights Reserved 2017");
  printf("\n");

  getch();
}
