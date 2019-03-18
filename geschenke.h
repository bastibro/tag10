#include <stdio.h>

struct geschenk{
	int groesse;
	char name[100];
	struct geschenk *next;
} geschenk;

struct schlitten{
	int kapazitaet;
	int fuellstand;
	char rentier[100];
	struct geschenk *liste;
	struct schlitten *naechster;
} schlitten;

void print_schlitten(struct schlitten *alle_schlitten, int cnt_schlitten);
void print_geschenke(struct geschenk *start);
int find_schlitten(struct schlitten *alle_schlitten, int groesse, int anzahl);
struct schlitten * read_schlitten(struct schlitten * alle_schlitten, int anzahl, FILE * input);
struct schlitten * free_schlitten(struct schlitten * alle_schlitten, int anzahl);
struct schlitten * add_schlitten(struct schlitten *alle_schlitten, FILE * input);
struct geschenk * read_geschenke(struct geschenk *start, FILE * input);
struct geschenk * add_geschenk(struct geschenk * start, struct geschenk * neu);
struct geschenk * geschenke_zuordnen(struct schlitten* alle_schlitten, struct geschenk * start, int anzahl);
struct schlitten * geschenk_laden(struct schlitten * alle_schlitten, int best_schlitten, int groesse, char * name);
struct geschenk * remove_geschenk(struct geschenk *start, char * name);
