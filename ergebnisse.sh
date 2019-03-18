#!/bin/bash

echo -e "#\n# Test einfache Eingabe, nur ein Rentier, passende Menge\n#"
./geschenke eingabe1.txt
if [ $? -eq 0 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi
echo -e "\t Wenn hier keine Ausgabe folgt, sind die Ausgabedateien in Ordnung."
diff test_Prancer1.txt Prancer1.txt || echo -e "\t Die Ausgabedatei ist nicht korrekt."

echo -e "\n#\n# Test mehrere Rentiere, keine Gleichstaende, passende Menge\n#"
./geschenke eingabe3.txt
if [ $? -eq 0 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi
echo -e "\tWenn hier keine Ausgabe folgt, sind die Ausgabedateien in Ordnung."
diff test_Blitzen5.txt Blitzen5.txt || echo -e "\t Die Ausgabedatei Blitzen5.txt ist nicht korrekt."
diff test_Comet5.txt Comet5.txt || echo -e "\t Die Ausgabedatei Comet5.txt ist nicht korrekt."
diff test_Cupid5.txt Cupid5.txt || echo -e "\t Die Ausgabedatei Cupid5.txt ist nicht korrekt."
diff test_Dancer5.txt Dancer5.txt  || echo -e "\t Die Ausgabedatei Dancer5.txt ist nicht korrekt."
diff test_Dasher5.txt Dasher5.txt || echo -e "\t Die Ausgabedatei Dasher5.txt ist nicht korrekt."
diff test_Donner5.txt Donner5.txt || echo -e "\t Die Ausgabedatei Donner5.txt ist nicht korrekt."
diff test_Prancer5.txt Prancer5.txt || echo -e "\t Die Ausgabedatei Prancer5.txt ist nicht korrekt."
diff test_Rudolph5.txt Rudolph5.txt || echo -e "\t Die Ausgabedatei Rudolph5.txt ist nicht korrekt."
diff test_Vixen5.txt Vixen5.txt || echo -e "\t Die Ausgabedatei Vixen5.txt ist nicht korrekt."

echo -e "\n#\n# Test mehrere Rentiere, mit Gleichstaenden, passende Menge\n#"
./geschenke eingabe2.txt
if [ $? -eq 0 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi
echo -e "\tWenn hier keine Ausgabe folgt, sind die Ausgabedateien in Ordnung."
diff test_Blitzen2.txt Blitzen2.txt || echo -e "\t Die Ausgabedatei Blitzen2.txt ist nicht korrekt."
diff test_Comet2.txt Comet2.txt || echo -e "\t Die Ausgabedatei Comet2.txt ist nicht korrekt."
diff test_Dancer2.txt Dancer2.txt || echo -e "\t Die Ausgabedatei Dancer2.txt ist nicht korrekt."
diff test_Rudolf2.txt Rudolf2.txt || echo -e "\t Die Ausgabedatei Rudolf2.txt ist nicht korrekt."

echo -e "\n#\n# Test zu viele Geschenke\n#"
./geschenke zu_wenig_kapazitaet.txt
if [ $? -eq 3 ]
	then echo -e "*\t...Rückgabe: OK"
	else echo -e "*\t...Rückgabewert stimmt nicht."
fi

echo -e "\n#\n# Test Geschenke können nicht aufgeteilt werden\n#"
./geschenke keine_aufteilung.txt
if [ $? -eq 3 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi

echo -e "\n#\n# Test Ohne Parameter\n#"
./geschenke 
if [ $? -eq 1 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi

echo -e "\n#\n# Test Datei kann nicht geoeffnet werden\n#"
./geschenke notreadable.txt
if [ $? -eq 2 ]
	then echo -e "\t...Rückgabe: OK"
	else echo -e "\t...Rückgabewert stimmt nicht."
fi
