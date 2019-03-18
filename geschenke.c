#include "geschenke.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sh-Datein nutzbar machen: chmod 777 <datei>.sh
// rückgabewert des programms anzeigen lassen:
// echo $? nach dem Programmaufruf
// Dateien einzeln Hochladen, d.h. Die "zip" unter "Mehrere Dateien als...
// hochladen" hochladen
// FILE* eingabe = NULL;
// FILE* ausgabe = NULL;

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("Bitte genau 2 parameter übergeben");
    return 1;
  }
  FILE *input = fopen(argv[1], "r");
  int anzahl;
  puts("hi");
  fscanf(input, "%d", &anzahl);
  puts("bye");
  printf("anzahl ist: %d\n", anzahl);
  struct schlitten *alle_schlitten = NULL;
  alle_schlitten = read_schlitten(alle_schlitten, anzahl, input);
  puts("printing schlitten...\n");
  print_schlitten(alle_schlitten, anzahl);

  struct geschenk *start = NULL;
  start = read_geschenke(start, input);

  puts("printing geschenke...\n");
  print_geschenke(start);

  puts("starting zuordnung...\n");
  start = geschenke_zuordnen(alle_schlitten, start, anzahl);

  puts("printing after zuordnung...\n");
  print_schlitten(alle_schlitten, anzahl);
  /* start = remove_geschenk(start, "C"); */
  puts("printing geschenke again..\n");
  print_geschenke(start);

  alle_schlitten = free_schlitten(alle_schlitten, anzahl);
  fclose(input);
  return 0;
}

struct schlitten *free_schlitten(struct schlitten *alle_schlitten, int anzahl) {
  while (alle_schlitten != NULL) {
    struct schlitten* aktueller_schlitten = alle_schlitten;
    struct geschenk* liste = aktueller_schlitten->liste;

    while (liste != NULL) {
      struct geschenk* aktuell = liste;

      liste = liste->next;
      free(aktuell);
    }


    alle_schlitten = alle_schlitten->naechster;
    free(aktueller_schlitten);
  }

  return NULL;
}

struct schlitten *read_schlitten(
    struct schlitten *alle_schlitten, int anzahl,
    FILE *input) { // bekommt eine eingabedatei und ließt die schlitten ein
  int i = 0;
  while (i < anzahl) {
    alle_schlitten = add_schlitten(alle_schlitten, input);
    i++;
  }

  return alle_schlitten;
}

struct schlitten *add_schlitten(struct schlitten *alle_schlitten, FILE *input) {
  char rentier[100];
  int kapazitaet;
  struct schlitten *i;
  struct schlitten *tmp = alle_schlitten;
  i = malloc(sizeof(struct schlitten));
  fscanf(input, "%s %d", i->rentier, &i->kapazitaet);

  i->fuellstand = 0; // kann ersetzt werden durch calloc()
  i->liste = NULL;
  i->naechster = NULL;

  if (alle_schlitten == NULL) { // fügt den neuen schlitten ein
    alle_schlitten = i;
  } else {
    while (tmp->naechster != NULL) {
      tmp = tmp->naechster;
    }
    tmp->naechster = i;
  }
  if (alle_schlitten == NULL) {
    puts("schlitten ist null\n");
  }
  return alle_schlitten;
}

struct geschenk *read_geschenke(struct geschenk *start, FILE *input) {
  int groesse;
  char name[100];
  struct geschenk *tmp;
  while ((fscanf(input, "%d %s", &groesse, name) != EOF)) {
    printf("name: %s\ngroesse: %d\n\n", name, groesse);
    tmp = malloc(sizeof(struct geschenk));
    tmp->next = NULL;
    tmp->groesse = groesse;
    strcpy(tmp->name, name);
    start = add_geschenk(start, tmp);
  }
  return start;
}

struct geschenk *add_geschenk(struct geschenk *start, struct geschenk *neu) {
  struct geschenk *tmp = start;
  if (start == NULL) {
    start = neu;
  } else {
    while (tmp->next != NULL) {
      tmp = tmp->next;
    }
    tmp->next = neu;
  }
  return start;
}

struct geschenk *geschenke_zuordnen(struct schlitten *alle_schlitten, struct geschenk *start,
                             int anzahl) {
  int groesse;
  char name[100];
  struct geschenk *tmp = start;
  struct schlitten *tmpschlitten;
  int best_schlitten;

  while (tmp != NULL) {
    groesse = tmp->groesse;
    strcpy(name, tmp->name);
    best_schlitten =
        find_schlitten(alle_schlitten, groesse, anzahl); // get best schlitten

    alle_schlitten =
        geschenk_laden(alle_schlitten, best_schlitten, groesse, name);

    start = remove_geschenk(start, name);

    tmp = tmp->next;
  }

  return start;
}

int find_schlitten(struct schlitten *alle_schlitten, int groesse, int anzahl) {
  struct schlitten *tmpschlitten = alle_schlitten;
  int freiraum = 100;
  int best_schlitten = -1; // speichert den momentan bestgeeigneten schlitten

  for (int i = 0; i < anzahl; i++) {
    int tmpfreiraum =
        tmpschlitten->kapazitaet -
        tmpschlitten->fuellstand; // freiraum des momentanen schlitten
    if ((tmpfreiraum >= groesse) && (tmpfreiraum < freiraum)) {
      freiraum = tmpfreiraum;
      best_schlitten = i;
    }
    tmpschlitten = tmpschlitten->naechster;
  }

  if (best_schlitten == -1) {
    puts("NO SCHLITTEN FOUND!!");
  }
  return best_schlitten;
}

struct schlitten *geschenk_laden(struct schlitten *alle_schlitten, int best_schlitten,
                          int groesse, char *name) {
  struct schlitten *tmpschlitten = alle_schlitten;

  for (int i = 0; i < best_schlitten; i++) {
    tmpschlitten = tmpschlitten->naechster;
  }

  struct geschenk *geschenk_pt = malloc(sizeof(struct geschenk));
  geschenk_pt->next = NULL;
  geschenk_pt->groesse = groesse;
  strcpy(geschenk_pt->name, name);

  tmpschlitten->liste = add_geschenk(tmpschlitten->liste, geschenk_pt);

  tmpschlitten->fuellstand += groesse;

  return alle_schlitten;
}

struct geschenk *remove_geschenk(struct geschenk *start, char *name) {
  if (start == NULL)
    fprintf(stdout, "Keine Geschenke an Board.\n");
  else {
    struct geschenk *vorgaenger = NULL;
    struct geschenk *aktuell = start;

    while (aktuell != NULL) {
      if (strcmp(name, aktuell->name) == 0) {
        if (vorgaenger != NULL) {
          vorgaenger->next = aktuell->next;
          free(aktuell);
          return start;
        } else {
          struct geschenk* new_start = start->next;
          free(start);
          return new_start;
        }

        /*   vorgaenger->next = aktuell->next; */
        /*   free(aktuell); */
        /*   return start; */
        /* } else { */
        /*   start = start->next; */
        /*   free(aktuell); */
        /*   return start; */
        /* } */
      }
      vorgaenger = aktuell;
      aktuell = aktuell->next;
    }
  }
  return start;
}
void print_schlitten(struct schlitten *alle_schlitten, int cnt_schlitten) {
  if (alle_schlitten == NULL)
    fprintf(stdout, "Keine Schlitten da.\n");
  else {
    while (alle_schlitten != NULL) {
      printf("rentier ist: %s\nkapazitaet ist: %d\n", alle_schlitten->rentier,
             alle_schlitten->kapazitaet);
      printf("fuellstand ist: %d\n\n", alle_schlitten->fuellstand);
      print_geschenke(alle_schlitten->liste);

      alle_schlitten = alle_schlitten->naechster;
    }
  }
}

void print_geschenke(struct geschenk *start) {
  if (start == NULL)
    fprintf(stdout, "Keine Geschenke an Board.\n");
  else {
    while (start != NULL) {
      fprintf(stdout, "Name: %s\nGroesse: %d\n\n", start->name, start->groesse);
      start = start->next;
    }
  }
}
