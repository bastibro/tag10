#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "geschenke.h"


//sh-Datein nutzbar machen: chmod 777 <datei>.sh
//rückgabewert des programms anzeigen lassen:
// echo $? nach dem Programmaufruf
// Dateien einzeln Hochladen, d.h. Die "zip" unter "Mehrere Dateien als... hochladen" hochladen
//FILE* eingabe = NULL;
//FILE* ausgabe = NULL;

int main(int argc, char **argv){
	if (argc != 2){
		puts("Bitte genau 2 parameter übergeben");
		return 1;
		}
	FILE *input = fopen(argv[1], "r");
	int anzahl;
	puts("hi");
	fscanf(input, "%d", &anzahl);
	puts("bye");
	printf("anzahl ist: %d\n", anzahl);
	schlitten *alle_schlitten = NULL;
	alle_schlitten = read_schlitten(alle_schlitten, anzahl, input);
	puts("printing schlitten...\n");
	print_schlitten(alle_schlitten, anzahl);	
	geschenk *start = NULL;
	start = read_geschenke(start, input);
	puts("printing geschenke...\n");
	print_geschenke(start);
	puts("starting zuordnung...\n");
	geschenke_zuordnen(alle_schlitten, start, anzahl);
	//start = remove_geschenk(start, "C");
	puts("printing geschenke again..\n");
	print_geschenke(start);
	fclose(input);
	return 0;
}


schlitten * read_schlitten(schlitten * alle_schlitten, int anzahl, FILE * input){ //bekommt eine eingabedatei und ließt die schlitten ein
	//puts("CALL: read_schlitten_35");
	int i = 0;
	while(i < anzahl){
		alle_schlitten = add_schlitten(alle_schlitten, input);
		i++; 
	}

    return alle_schlitten;
}

schlitten * add_schlitten(schlitten *alle_schlitten, FILE * input){
	
	char rentier[100];
	int kapazitaet;
	schlitten *i;
	schlitten *tmp = alle_schlitten;
	i = malloc(sizeof(schlitten));
	fscanf(input, "%s %d", i->rentier, &i->kapazitaet);

	//printf("rentier ist: %s\nkapazitaet ist: %d\n\n", i->rentier, i->kapazitaet);
	i->fuellstand = 0;			//kann ersetzt werden durch calloc()
	i->liste = NULL;
	i->naechster = NULL;
	
	if(alle_schlitten == NULL){							//fügt den neuen schlitten ein
	alle_schlitten = i;
	} else {
		while(tmp->naechster != NULL){
			tmp = tmp->naechster;
		}
		tmp->naechster = i;
	}
	if(alle_schlitten == NULL){puts("schlitten ist null\n");}
	return alle_schlitten;
}

geschenk * read_geschenke(geschenk *start, FILE * input){
	int groesse;
	char name[100];
	geschenk * tmp;
    while((fscanf(input, "%d %s", &groesse, name) != EOF)){
    	printf("name: %s\ngroesse: %d\n\n", name, groesse );
		tmp = malloc(sizeof(geschenk));
		tmp->next = NULL;
        tmp->groesse = groesse; 
        //puts("79!!!\n");
    	strcpy(tmp->name, name);
        //puts("80!!!\n");
        start = add_geschenk(start, tmp);	
    }
    //puts("90!!!\n");
    return start;
	}

geschenk * add_geschenk(geschenk * start, geschenk * neu){
	geschenk * tmp = start;
	if (start == NULL){
        	start = neu;
        } else {
        	while(tmp->next != NULL){
				tmp = tmp->next;
			}
			tmp->next = neu;
        }
        return start;
}

void geschenke_zuordnen(schlitten* alle_schlitten, geschenk * start, int anzahl){
	int groesse;
	char name[100];
	geschenk * tmp = start;
	schlitten * tmpschlitten;
	int best_schlitten;
	
	while(tmp != NULL){
		groesse = tmp->groesse;
		strcpy(name, tmp->name);
		best_schlitten = find_schlitten(alle_schlitten, groesse, anzahl); //get best schlitten
		printf("%d is %s\n", best_schlitten, name );

		//alle_schlitten = geschenk_laden(alle_schlitten, best_schlitten, groesse, name);puts("woooow");
		start = remove_geschenk(start, name);
		tmp = tmp->next;
	}

}

int find_schlitten(schlitten * alle_schlitten, int groesse, int anzahl){
	schlitten * tmpschlitten = alle_schlitten;
	int freiraum = 100;
	int best_schlitten = -1;		//speichert den momentan bestgeeigneten schlitten
	
	for(int i = 0; i < anzahl; i++){
		int tmpfreiraum = tmpschlitten->kapazitaet - tmpschlitten->fuellstand; //freiraum des momentanen schlitten
		if( (tmpfreiraum >= groesse) && (tmpfreiraum < freiraum) ){
			freiraum = tmpfreiraum;
			best_schlitten = i;
		}
		tmpschlitten = tmpschlitten->naechster;
	}
	
	//tmpschlitten = alle_schlitten;
	//for(int j = 0; j < best_schlitten; j++){ //gibt schlitten anhand best_schlitten coutner zurück
	//	tmpschlitten = tmpschlitten->naechster;
	//}
	if (best_schlitten == -1){
		puts("NO SCHLITTEN FOUND!!");
	}
	return best_schlitten;
}

schlitten * geschenk_laden(schlitten * alle_schlitten, int best_schlitten, int groesse, char * name){
	schlitten * tmpschlitten = alle_schlitten;
	
	for(int i = 0; i < best_schlitten; i++){
		tmpschlitten = tmpschlitten->naechster;
	}
	puts("woooow1");
	tmpschlitten->liste->groesse = groesse; puts("woooow2");
	strcpy(tmpschlitten->liste->name, name);
	
	return tmpschlitten;
}


geschenk * remove_geschenk(geschenk *start, char * name){	
	if(start == NULL) fprintf(stdout, "Keine Geschenke an Board.\n");
	else {
		geschenk *vorgaenger = NULL;
		geschenk *aktuell = start;

		while(aktuell != NULL){
			//fprintf(stdout, "Name: %s\nGroesse: %d\n\n", start->name, start->groesse);
			if (strcmp(name, aktuell->name) == 0) {
				if (vorgaenger != NULL){
				puts("170!!\n");
				vorgaenger->next = aktuell->next;
				puts("171!!\n");
				//free
				return start;	
			} else {
				geschenk *tmp = start;
				start = start->next;
				//free
				return start;
			}
		}
		vorgaenger = aktuell;
		aktuell = aktuell->next;
		
		}
	}return start;
	return start;
}
void print_schlitten(schlitten *alle_schlitten, int cnt_schlitten){
	if(alle_schlitten == NULL) fprintf(stdout, "Keine Schlitten da.\n");
	else {
		while(alle_schlitten != NULL){
			printf("rentier ist: %s\nkapazitaet ist: %d\n\n", alle_schlitten->rentier, alle_schlitten->kapazitaet);
			//fprintf(stdout, "%s %i\n", start->rentier, start->groesse);
			alle_schlitten = alle_schlitten->naechster; 
		}
	}
	//for(int i = 0; i < cnt_schlitten; i++){
	//	printf("Rentier: %s\t Kap: %i\t Fuell: %i\n", alle_schlitten[i].rentier, alle_schlitten[i].kapazitaet, alle_schlitten[i].fuellstand);
	//	print_geschenke(alle_schlitten[i].liste);
	//}
}


void print_geschenke(geschenk *start){
	if(start == NULL) fprintf(stdout, "Keine Geschenke an Board.\n");
	else {
		while(start != NULL){
			fprintf(stdout, "Name: %s\nGroesse: %d\n\n", start->name, start->groesse);
			start = start->next;
		}
	}
}

