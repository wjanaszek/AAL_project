Wojciech Janaszek 273689 ISI

<---- O problemie ---->
"Rozpl�tywanie odcink�w"
- mamy 2 zbiory punkt�w na p�aszczy�nie, po N punkt�w ka�dy. Znale�� taki zbi�r odcink�w, w kt�rym �adne odcinki
nie przecinaj� si�.

<---- Dost�pne rozwi�zania ---->
Do rozwi�zania problemu dost�pne s� 2 algorytmy:
1. Tzw. "brutal force" - dzia�aj�cy do 4 wierzcho�k�w (inaczej trwa to d�ugo ze wzgl�du na jego z�o�ono��)
2. Algorytm na podstawie najmniejszej odleg�o�ci mi�dzy punktami 

Efekty pracy algorytm�w zapisywane s� do odpowiednich plik�w *.bmp, kt�rych nazwy s� wy�wietlane przez program po zako�czeniu
oblicze�.

<---- Opcje i parametry uruchomieniowe programu ---->
Podaj�c parametry nale�y wpisywa� "-", ale nie wpisywa� "<" i ">"
1) T11_2 -1f <nazwa_pliku> <T> 
	--> wykonanie wg danych dostarczonych ze strumienia wej�ciowego (pliku o nazwie nazwa_pliku), z prezentacja wynik�w dzia�ania
	    (weryfikacja poprawno�ci), gdzie:
				T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho�k�w - w przypadku niespe�nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					    		       (1 - algorytm na podstawie najmniejszej odleg�o�ci mi�dzy punktami)
2) T11_2 -1k <T> 
	--> wykonanie wg danych dostarczonych ze strumienia wej�ciowego (klawiatury), z prezentacja wynik�w dzia�ania
	    (weryfikacja poprawno�ci), gdzie:
				T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho�k�w - w przypadku niespe�nienia tego warunku
						      zostanie uruchomiony algorytm 1)
						 (1 - algorytm na podstawie najmniejszej odleg�o�ci mi�dzy punktami)
3) T11_2 -2g -N<val> -S<val> <T>
	--> wykonanie wg danych wej�ciowych wygenerowanych automatycznie z parametryzacj�, z prezentacja wynik�w dzia�ania
	    (weryfikacja poprawno�ci), gdzie:						 
				N - liczba punkt�w w jednym zbiorze
				S - ziarno (seed) do generowania warto�ci
				T - wybrany algorytm (0 - brutal force)
				                     (1 - algorytm 1)
4) T11_2 -2gwout -N<val> <T> 
	--> wykonanie wg danych wej�ciowych wygenerowanych automatycznie bez parametryzacji, z prezentacja wynik�w dzia�ania
	    (weryfikacja poprawno�ci), gdzie:
				N - liczba punkt�w w jednym zbiorze 
				T - wybrany algorytm (0 - brutal force)
				                     (1 - algorytm 1)
5) T11_2 -3g -N<val> -S<val> <T> <R> <ilosc_pomiarow>
	--> wykonanie z generacj� danych losowych z zadanym ziarnem , pomiarem czasu i prezentacj� wynik�w pomiar�w, 
			gdzie: 
			      T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho�k�w - w przypadku niespe�nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					           (1 - algorytm na podstawie najmniejszej odleg�o�ci mi�dzy punktami)
			      N - liczba punkt�w w jednym zbiorze
			      S - ziarno (seed) do generowania warto�ci
			      R - krok (co jak� ilo�� N b�dzie generowany kolejny pomiar)
			      ilosc_pomiarow - ilo�� pomiar�w, jakie ma wykona� program
6) T11_2 -3gwout -N<val> <T> <R> <ilosc_pomiarow>
	--> wykonanie z generacj� danych losowo, pomiarem czasu i prezentacj� wynik�w pomiar�w,
			gdzie:
			      T - wybrany algorym (0 - brutal force (tylko do 6 wierzcho�k�w - w przypadku niespe�nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					          (1 - algorytm na podstawie najmniejszej odleg�o�ci mi�dzy punktami)
			      N - liczba punkt�w w jednym zbiorze 
			      R - krok (co jak� ilo�� N b�dzie generowany kolejny pomiar)
			      ilosc_pomiarow - ilo�� pomiar�w, jakie ma wykona� program

<---- Opis konwencji dotycz�cych danych wej�ciowych ---->
Dane wej�ciowe zawarte w pliku s� postaci:
x1,y1
x2,y1
gchange
x3,y3
x4,y4
end		
Nie mo�e by� mi�dzy warto�ciami wsp�rz�dnych bia�ych znak�w, jedynie przecinek. Konieczne jest u�ycie s��w kluczowych "gchange"
(aby zmieni� grup� punkt�w), oraz "end" - aby wskaza� koniec danych. W przypadku, gdy liczba punkt�w z obu grup b�dzie r�na,
zostanie zg�oszony b��d. Dane wczytywane z klawiatury nale�y wpisywa� z zachowaniem tej konwencji, jedynie zako�czenie podawania
danych nale�y zasygnalizowa� s�owem kluczowym "quit".

<---- Prezentacja wynik�w ---->
Po wykonaniu si� algorytmu wynik jego pracy zapisywany jest do pliku graficznego. S� tam narysowane punkty i ��cz�ce je linie. 
Aby obejrze� ten wynik nale�y odszuka� plik i wy�wietli� go w przegl�darce systemowej.

<---- Metoda rozwi�zania ---->
W obydwu rozwi�zaniach wykorzystywany jest kontener "vector".
1. "Brutal force"
   Sprawdzamy wszystkie mo�liwe zbiory po��cze� odcink�w, i odrzucamy te, w kt�rych s� jakie� odcinki, kt�re si� przecinaj�.
   Wykorzystywany jest tu algorytm z tzw. "zamiataniem".
2. Algorytm na podstawie najmniejszej odleg�o�ci
   Najpierw ��czymy punkty najmniej odleg�e od siebie, nast�pnie sprawdzamy pary odcink�w, czy nie przecinaj� si�. Je�li si� 
   przecinaj�, to ��czymy punkty z tej pary odcink�w na inny spos�b. Kontynuujemy sprawdzanie, a� do znalezienia takiego zbioru,
   w kt�rym �adne 2 odcinki si� nie przecinaj�.

<---- Przewodnik po plikach �r�d�owych ---->
1. Algorithms - obiekt udost�pniaj�cy statyczne metody algorytmiczne
2. DataReader - obiekt odpowiedzialny za obs�ug� wczytywania danych     --> zawarty w DataService
3. DataGenerator - obiekt odpowiedzialny za generacj� danych losowych   --> zawarty w DataService
4. FileIOException - obiekt reprezentuj�cy wyj�tek wej�cia-wyj�cia zwi�zany z obs�ug� plik�w
5. Point2D - obiekt reprezentuj�cy punkt na p�aszczy�nie we wsp�rz�dnych XY
6. Segment - obiekt reprezentuj�cy odcinek na p�aszczy�nie
7. SetOfSegments - obiekt reprezentujacy zbi�r odcink�w na p�aszczy�nie 
8. Sweeper - obiekt reprezentuj�cy "miot��"
9. WrongNumberOfElementsException - obiekt reprezentuj�cy wyj�tek wej�cia-wyj�cia zwi�zany z r�n� ilo�ci� punkt�w w obu grupach punkt�w
10. main.cpp - g��wna p�tla programu

<---- Informacje dodatkowe ---->
1. Program mo�na skompliowa� w �rodowisku Windows (w IDE code::blocks po zaimportowaniu projektu znajduj�cego si� w pliku *.cpb)
   lub w �rodowisku Linux, wydaj�c polecenie "make" w g��wnym katalogu programu.
2. W zwi�zku ze z�o�ono�ci� algorytmu 1, maksymalny rozmiar problemu, jaki mo�e zosta� przez niego rozwi�zany, to 6 wierzcho�k�w
   w jednej grupie (��cznie 12 wierzcho�k�w). W przeciwnym razie program generuje tak du�o element�w, kt�re powinny zosta� 
   dodane do vectora, �e �w vector wyrzuca wyj�tek zwi�zany z przepe�nieniem (std::bad_alloc), przerywaj�cy dzia�anie programu.
3. W przypadku podania b��dnej nazwy pliku w trybie wykonania, w kt�rym dane czytane s� z pliku, zostanie wyrzucony wyj�tek 
   zwi�zany z brakiem odpowiedniego pliku na komputerze.
4. Generator danych testowych generuje punkty losowo z zadanym "seed", lub bior�c za ziarno zegar.
5. W przypadku, gdy podczas wczytywania danych z pliku lub z klawiatury, w jednej grupie b�dzie wi�cej
   lub mniej punkt�w, ni� w drugiej, zostanie wyrzucony odpowiedni wyj�tek, niedopuszczaj�cy do dalszego
   wykonania programu.
6. Z niewyja�nionych przyczyn w lini 324 z klasy Algorithm (plik Algorithm.cpp) nie dzia�a inicjowanie obiektu dla
   warto�ci inicjuj�cej generator warto�ci testowych r�wnej 10. 
7. Uwagi i pytania kierowa� do autora projektu.