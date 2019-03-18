typedef struct geschenk{
	int groesse;
	char name[100];
	struct geschenk *next;
} geschenk;

typedef struct{
	int kapazitaet;
	int fuellstand;
	char rentier[100];
	geschenk *liste;
	struct schlitten *naechster;
} schlitten;

void print_schlitten(schlitten *alle_schlitten, int cnt_schlitten);
void print_geschenke(geschenk *start);
schlitten * read_schlitten(schlitten * alle_schlitten, int anzahl, FILE * input);
schlitten * add_schlitten(schlitten *alle_schlitten, FILE * input);
geschenk * read_geschenke(geschenk *start, FILE * input);
geschenk * add_geschenk(geschenk * start, geschenk * neu);
void geschenke_zuordnen(schlitten* alle_schlitten, geschenk * start, int anzahl);
schlitten * geschenk_laden(schlitten * alle_schlitten, int best_schlitten, int groesse, char * name);
geschenk * remove_geschenk(geschenk *start, char * name);
