#!/bin/bash

echo "Valgrindtest einfache Eingabe, nur ein Rentier, passende Menge"
2>&1 valgrind --log-file=valgrind_eingabe1.txt ./geschenke eingabe1.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_eingabe1.txt &&  echo -e "\t... Speicherleck bei ./geschenke eingabe1.txt gefunden. Details in Datei valgrind_eingabe1.txt" || echo -e "\t ...OK\n"

echo "Valgrindtest mehrere Rentiere, keine Gleichstaende, passende Menge"
2>&1 valgrind --log-file=valgrind_eingabe3.txt ./geschenke eingabe3.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_eingabe3.txt &&  echo -e "\t... Speicherleck bei ./geschenke eingabe3.txt gefunden. Details in Datei valgrind_eingabe3.txt" || echo -e "\t ...OK\n"

echo "Valgrindtest mehrere Rentiere, mit Gleichstaenden, passende Menge"
2>&1 valgrind --log-file=valgrind_eingabe2.txt ./geschenke eingabe2.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_eingabe2.txt &&  echo -e "\t... Speicherleck bei ./geschenke eingabe2.txt gefunden. Details in Datei valgrind_eingabe2.txt" || echo -e "\t ...OK\n"

echo "Valgrindtest zu viele Geschenke"
2>&1 valgrind --log-file=valgrind_zu_wenig_kapazitaet.txt ./geschenke zu_wenig_kapazitaet.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_zu_wenig_kapazitaet.txt &&  echo -e "\t... Speicherleck bei ./geschenke zu_wenig_kapazitaet.txt gefunden. Details in Datei valgrind_zu_wenig_kapazitaet.txt" || echo -e "\t ...OK\n"


echo "Valgrindtest Geschenke können nicht aufgeteilt werden"
2>&1 valgrind --log-file=valgrind_keine_aufteilung.txt ./geschenke keine_aufteilung.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_keine_aufteilung.txt &&  echo -e "\t... Speicherleck bei ./geschenke keine_aufteilung.txt gefunden. Details in Datei valgrind_keine_aufteilung.txt" || echo -e "\t ...OK\n"

echo "Valgrindtest Ohne Parameter"
2>&1 valgrind --log-file=valgrind_noparam.txt ./geschenke > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_noparam.txt &&  echo -e "\t... Speicherleck bei ./geschenke gefunden. Details in Datei valgrind_noparam.txt" || echo -e "\t ...OK\n"


echo "Valgrindtest Eingabedatei kann nicht geoeffnet werden"
2>&1 valgrind --log-file=valgrind_NOTTHERE.txt ./geschenke NOTTHERE > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_NOTTHERE.txt &&  echo -e "\t... Speicherleck bei ./geschenke NOTTHERE gefunden. Details in Datei valgrind_NOTTHERE.txt" || echo -e "\t ...OK\n"

touch  out_test.txt
chmod -w out_test.txt
echo "Valgrindtest Ausgabedatei kann nicht geoeffnet werden"
2>&1 valgrind --log-file=valgrind_NOTTHERE_out.txt ./geschenke ausgabe_nicht_moeglich.txt > /dev/null
grep -qE "([^0]|[0-9]0) bytes in" valgrind_NOTTHERE_out.txt &&  echo -e "\t... Speicherleck bei ./geschenke ausgabe_nicht_moeglich.txt gefunden. Details in Datei valgrind_NOTTHERE_out.txt" || echo -e "\t ...OK\n"
rm -f out_test.txt

