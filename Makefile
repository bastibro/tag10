compile: geschenke.h geschenke.c
	gcc -o geschenke -Wall -std=c99 geschenke.c
# TODO ergänzen Sie die Abhängigkeiten hier, kompilieren Sie Ihr Programm mit Debug Parametern
	# den geforderten Warnings und nach dem Standard c99
	# die Programmaufrufe in ergebnisse.sh müssena anschließend funktionieren

clean: # entfernen Sie hier Ihr ausführbares Programm und alle Ausgaben sowie Logdateien
	rm -f geschenke valgrind_*.txt

diff: compile 
	./ergebnisse.sh

valgrind: compile valgrind.sh
	./valgrind.sh
