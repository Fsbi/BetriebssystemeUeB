#include <iostream>
#include "Prozess.h"
#include <time.h>
#include <vector>
//Prozess Array Generierung
Prozess* prozessGenerator(int Anzahl) {
	Prozess* meinarr = new Prozess[Anzahl];

	for (unsigned int i = 0; i < Anzahl; i++) {
		unsigned int bereitzeit = 0; // rand() % 10;
		unsigned int ausfuehrungszeit = (rand() % 50) + 1;
		unsigned int deadline = bereitzeit + ausfuehrungszeit + (rand() % 100) + 10;
		meinarr[i] = Prozess(deadline, bereitzeit, ausfuehrungszeit);
	}
	return meinarr;
}
//Prozess wird Ausgegeben 
void prozessAuslese(Prozess* arr, int Anzahl) {

	for (int i = 0; i < Anzahl; i++) {
		std::cout << "-------------------------------------------" << std::endl;
		std::cout << "Prozess: " << i << std::endl;
		std::cout << "Prozess Ausfuehrungszeit: " << arr[i].getAusfuehrungsZeit() << std::endl;
		std::cout << "Prozess BereitZeit: " << arr[i].getBereitZeit() << std::endl;
		//std::cout << "Prozess Deadline: " << arr[i].getDeadline() << std::endl;

	}

}
//berechnung der Durchschnittlichen Wartezeit
unsigned int Wartezeit(Prozess* arr, int Anzahl) {
	unsigned int sum = 0;
	unsigned int finalsum = 0;
	for (int i = 0; i < Anzahl; i++) {
		sum += arr[i].getAusfuehrungsZeit();

		finalsum += sum - arr[i].getBereitZeit();
		//std::cout << sum - arr[i].getBereitZeit() << std::endl;
	}

	return finalsum / Anzahl;
}
//Vergleich der BereitZeit zweier Prozesse 
bool compareArrivalTime(Prozess a, Prozess b) {
	return a.getBereitZeit() <= b.getBereitZeit();
}
//Sortier Array nach Bereitzeit
Prozess* SortBereitZeit(Prozess* arr, int Anzahl) {
	Prozess tmp;
	for (int j = 0; j < Anzahl; j++) {
		for (int i = 0; i < Anzahl; i++) {

			if (i + 1 <= Anzahl) {
				if (compareArrivalTime(arr[i], arr[i + 1])) {
				}
				else {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
				}
			}

		}
	}

	return arr;
}
//Vergleicht zwei Prozesse nach Aufuehrungszeit 
bool compareRunTime(Prozess a, Prozess b) {
	return a.getAusfuehrungsZeit() <= b.getAusfuehrungsZeit();
}
//Sortier Array nach Ausführungszeit
Prozess* SortAusfuehrungsZeit(Prozess* arr, int Anzahl) {
	Prozess tmp;
	for (int j = 0; j < Anzahl; j++) {
		for (int i = 0; i < Anzahl; i++) {
			// && ... anfügen für Aufgabe 3 non Preemptive Scheduling
			if (i + 1 <= Anzahl) {
				if (compareRunTime(arr[i], arr[i + 1])) {
				}
				else {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
				}
			}

		}
	}

	return arr;
}
//Sortier Array nach Ausführungszeit
Prozess* SortAusfuehrungsZeitMitBereitZeit(Prozess* arr, int Anzahl) {
	Prozess tmp;
	for (int j = 0; j < Anzahl; j++) {
		for (int i = 0; i < Anzahl; i++) {
			// && ... anfügen für Aufgabe 3 non Preemptive Scheduling
			if (i + 1 <= Anzahl && arr[i].getBereitZeit() == arr[i + 1].getBereitZeit()) {
				if (compareRunTime(arr[i], arr[i + 1])) {
				}
				else {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
				}
			}

		}
	}

	return arr;
}
// Vergleich von Deadline
bool compareDeadline(Prozess a, Prozess b) {
	return a.getDeadline() <= b.getDeadline();
}
// Sortiert nach Deadline
Prozess* SortDeadline(Prozess* arr, int Anzahl) {
	Prozess tmp;
	for (int j = 0; j < Anzahl; j++) {
		for (int i = 0; i < Anzahl; i++) {

			if (i + 1 <= Anzahl) {
				if (compareDeadline(arr[i], arr[i + 1])) {
				}
				else {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
				}
			}

		}
	}

	return arr;
}
// Vergleich Lexity
bool comparedLexity(Prozess a, Prozess b) {
	return a.getLatenz() <= b.getLatenz();
}
//sortiert nach Lexity 
Prozess* SortLexity(Prozess* arr, int Anzahl) {
	Prozess tmp;
	for (int j = 0; j < Anzahl; j++) {
		for (int i = 0; i < Anzahl; i++) {

			if (i + 1 <= Anzahl) {
				if (comparedLexity(arr[i], arr[i + 1])) {
				}
				else {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
				}
			}

		}
	}

	return arr;
}
//Strategien zur Prozessabarbeitung 
unsigned int SJF(Prozess* arr, int Anzahl) {
	Prozess* SJF = arr;
	SJF = SortAusfuehrungsZeitMitBereitZeit(SJF, Anzahl);
	//prozessAuslese(SJF, Anzahl);
	return Wartezeit(SJF, Anzahl);
}
unsigned int FCFS(Prozess* arr, int Anzahl) {
	Prozess* fcfsarr = arr;
	fcfsarr = SortBereitZeit(fcfsarr, Anzahl);
	return Wartezeit(fcfsarr, Anzahl);
}
unsigned int EDF(Prozess* arr, int Anzahl) {
	Prozess* EDF = arr;
	EDF = SortDeadline(EDF, Anzahl);
	return Wartezeit(EDF, Anzahl);
}
unsigned int LLF(Prozess* arr, int Anzahl) {
	Prozess* LLF = arr;
	LLF = SortLexity(LLF, Anzahl);
	return Wartezeit(LLF, Anzahl);
}

float RoundRobin(Prozess* arr, int Anzahl, int Q) {
	Prozess* RoundRobin = arr;
	int zaehler = 0;
	int sum = 0;
	int AnzahlAnZero = 0;
	bool isfinish = false;
	int Durchschnitt = 0;
	float anzahl = Anzahl;
	while (!isfinish) {
		if (RoundRobin[zaehler].getAusfuehrungsZeit() != 0) { //wenn 0 ist Prozess abgearbeitet und soll übersprungen werden
			if (RoundRobin[zaehler].getAusfuehrungsZeit() <= Q) {//Überprüfung ob Prozess diese Runde Fertig wird

				sum += RoundRobin[zaehler].getAusfuehrungsZeit();
				RoundRobin[zaehler].setAusfuehrungsZeit(0);
				//std::cout << "Sum: " << sum << std::endl;

				AnzahlAnZero++;
				Durchschnitt += sum;
			}
			else {
				sum += Q;
				RoundRobin[zaehler].setAusfuehrungsZeit(RoundRobin[zaehler].getAusfuehrungsZeit() - Q);

			}
		}

		AnzahlAnZero == Anzahl ? isfinish = true : isfinish = false; //Überprüfung ob alle Prozesse abgearbeitet wurden
		zaehler == Anzahl - 1 ? zaehler = 0 : zaehler += 1; //Array Zähler soll zurückgesetzt werden 

	}



	return Durchschnitt / anzahl;
}
//Array Erstellen mit den Vorlesungs Beispielen
Prozess* FCFSArr() {
	Prozess* arr = new Prozess[5];
	arr[0] = Prozess(100, 0, 22);
	arr[1] = Prozess(100, 0, 2);
	arr[2] = Prozess(100, 0, 3);
	arr[3] = Prozess(100, 0, 5);
	arr[4] = Prozess(100, 0, 8);

	return arr;

}
//Array Erstellen mit Vorlesungsbeispiel für Unterschiedliche Bereitzeiten
Prozess* SJFArr() {
	Prozess* arr = new Prozess[5];
	arr[0] = Prozess(100, 0, 22);
	arr[1] = Prozess(100, 0, 2);
	arr[2] = Prozess(100, 4, 3);
	arr[3] = Prozess(100, 4, 5);
	arr[4] = Prozess(100, 4, 8);

	return arr;
}
//Prozzesse im Array vertauschen
Prozess* arrNeuSortieren(Prozess* arr, int Anzahl) {

	Prozess* oldArr = arr;
	int* intArr = new int[Anzahl];
	Prozess* newArr = new Prozess[Anzahl];
	for (int i = 0; i < Anzahl; i++) {
		int randomNr;
		bool alreadyExist = false;


		do
		{
			randomNr = rand() % 5;
			alreadyExist = false;
			for (int ii = 0; ii < i; ii++) {
				if (intArr[ii] == randomNr) { alreadyExist = true; }
			}
			if (!alreadyExist) { intArr[i] = randomNr; }

		} while (alreadyExist);
	}

	for (int i = 0; i < Anzahl; i++) {
		//std::cout << intArr[i] << std::endl;
		newArr[i] = oldArr[intArr[i]];
	}

	//prozessAuslese(newArr, Anzahl);
	delete[] oldArr;
	delete[] intArr;
	return newArr;
}
//aufgabe 2 
void Aufgabe2(Prozess* arr, int Anzahl, int Q, int Permutationen) {
	int sum = 0;
	for (int i = 0; i < Permutationen; i++) {
		std::cout << "Durchschnitt von " << i << ": " << RoundRobin(arrNeuSortieren(FCFSArr(), Anzahl), Anzahl, Q) << std::endl;
		//std::cout << "##################################" << std::endl;
		sum += RoundRobin(arrNeuSortieren(FCFSArr(), Anzahl), Anzahl, Q);
	}
	std::cout << "Overall Durchschnitt: " << sum / Permutationen << std::endl;
}
//Ändern der Bereitzeiten um einem random Wert
Prozess* BereitZeitÄndern(Prozess* arr,int Anzahl) {
	Prozess* newArr = arr;
	int veränderung; 
	for (int i = 0; i < Anzahl; i++) {
		veränderung = (rand() % 10)-5;
		if (newArr[i].getBereitZeit() + veränderung >= 0) {
			newArr[i].setBereitZeit(newArr[i].getBereitZeit() + veränderung);
		}
		else {
			newArr[i].setBereitZeit(0);
		}

	}
	return newArr;
}
// Idee zu Preemptive Scheduling SJF:
// mit For das Array von Prozessen durchgehen um den zu bearbeiten zu finden -> 1 Bearbeitungsschritt machen
// solange wiederholen bis alle Prozesse des Arrays bearbeitet wurden 
int Aufgabe3(Prozess* arr, int Anzahl) {
	Prozess* PreemptSJF = arr;
	int timer = 0;
	//int index = 0;
	//PreemptSJF = SortAusfuehrungsZeit(PreemptSJF, Anzahl);
	Prozess* BereiteProzesse = SortAusfuehrungsZeit(PreemptSJF, Anzahl);


	bool isFinish = false;
	int sum = 0;
	float Ergebnis = 0;
	int ProzessFinished = 0;
	//prozessAuslese(BereiteProzesse, Anzahl);
	prozessAuslese(BereiteProzesse, Anzahl);
	while (!isFinish)
	{


		for (int index = 0; index < Anzahl; index++) {
			if (BereiteProzesse[index].getAusfuehrungsZeit() != 0 && BereiteProzesse[index].getBereitZeit() <= timer) {//Kriterien zur Bearbeitung
				BereiteProzesse[index].setAusfuehrungsZeit(BereiteProzesse[index].getAusfuehrungsZeit() - 1); 
				timer++;
				std::cout << "Timer: " << timer << std::endl;
				if (BereiteProzesse[index].getAusfuehrungsZeit() <= 0) {

					std::cout << "Index des fertigen Prozesses: " << index << std::endl;
					ProzessFinished++;
					sum = timer - BereiteProzesse[index].getBereitZeit();
					Ergebnis += sum;
					std::cout << "Sum des fertigen Prozesses: " << sum << std::endl;

				}
				break; //wenn 1 Prozess des Arrays ausgewählt wurde soll for-Schleife von Vorne beginnen

			}

		}
		if (ProzessFinished >= Anzahl) { isFinish = true; } //Überprüfung ob alle Prozessebearbeitet wurde
		
		int Wert = 0;
		for (int i = 0; i < Anzahl; i++) {
			Wert += BereiteProzesse[i].getAusfuehrungsZeit();
			//std::cout << "Wert: " << Wert << std::endl;
		}
		Wert > 0 ? isFinish = false : isFinish = true; //erneuter Überprüfung ob alle Prozesse bearbeitet wurden, da es oft zu einem Bug kam, indem 
		//die while-Schleife nie beendet wurde
		
	}
	std::cout << "Final Ergebnis von Aufgabe 3 mit VorlesungsBeispiel beim Preemptive Scheduling SJF : " << Ergebnis / Anzahl << std::endl;
	return Ergebnis / Anzahl;
}
int main() {
	srand(time(0));
	const int arrLaenge = 10;
	Prozess* ProzessArr = prozessGenerator(arrLaenge);
	Prozess* VorlesungsBsp = FCFSArr();

	std::cout << "FCFS: " << FCFS(FCFSArr(), 5) << std::endl;
	std::cout << "SJF: " << SJF(FCFSArr(), 5) << std::endl;
	std::cout << "EDF: " << EDF(FCFSArr(), 5) << std::endl;
	std::cout << "LLF: " << LLF(FCFSArr(), 5) << std::endl;
	std::cout << "RoundRobin: " << RoundRobin(FCFSArr(), 5, 3) << std::endl;
	
	Aufgabe2(FCFSArr(), 5, 3, 10);

	std::cout << "SJF Non-preemptive Scheduling: " << SJF(SJFArr(), 5) << std::endl;
	//std::cout << "SJF Preemptive Scheduling mit Vorlesungs Beispiel: " << Aufgabe3mitVorlesungsBeispiel(SJFArr(), 5) << std::endl;
	Aufgabe3(SJFArr(), 5);
}