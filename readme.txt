Wojciech Janaszek 273689 ISI

<---- O problemie ---->
"Rozpl¹tywanie odcinków"
- mamy 2 zbiory punktów na p³aszczyŸnie, po N punktów ka¿dy. ZnaleŸæ taki zbiór odcinków, w którym ¿adne odcinki
nie przecinaj¹ siê.

<---- Dostêpne rozwi¹zania ---->
Do rozwi¹zania problemu dostêpne s¹ 2 algorytmy:
1. Tzw. "brutal force" - dzia³aj¹cy do 4 wierzcho³ków (inaczej trwa to d³ugo ze wzglêdu na jego z³o¿onoœæ)
2. Algorytm na podstawie najmniejszej odleg³oœci miêdzy punktami 

Efekty pracy algorytmów zapisywane s¹ do odpowiednich plików *.bmp, których nazwy s¹ wyœwietlane przez program po zakoñczeniu
obliczeñ.

<---- Opcje i parametry uruchomieniowe programu ---->
Podaj¹c parametry nale¿y wpisywaæ "-", ale nie wpisywaæ "<" i ">"
1) T11_2 -1f <nazwa_pliku> <T> 
	--> wykonanie wg danych dostarczonych ze strumienia wejœciowego (pliku o nazwie nazwa_pliku), z prezentacja wyników dzia³ania
	    (weryfikacja poprawnoœci), gdzie:
				T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho³ków - w przypadku niespe³nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					    		       (1 - algorytm na podstawie najmniejszej odleg³oœci miêdzy punktami)
2) T11_2 -1k <T> 
	--> wykonanie wg danych dostarczonych ze strumienia wejœciowego (klawiatury), z prezentacja wyników dzia³ania
	    (weryfikacja poprawnoœci), gdzie:
				T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho³ków - w przypadku niespe³nienia tego warunku
						      zostanie uruchomiony algorytm 1)
						 (1 - algorytm na podstawie najmniejszej odleg³oœci miêdzy punktami)
3) T11_2 -2g -N<val> -S<val> <T>
	--> wykonanie wg danych wejœciowych wygenerowanych automatycznie z parametryzacj¹, z prezentacja wyników dzia³ania
	    (weryfikacja poprawnoœci), gdzie:						 
				N - liczba punktów w jednym zbiorze
				S - ziarno (seed) do generowania wartoœci
				T - wybrany algorytm (0 - brutal force)
				                     (1 - algorytm 1)
4) T11_2 -2gwout -N<val> <T> 
	--> wykonanie wg danych wejœciowych wygenerowanych automatycznie bez parametryzacji, z prezentacja wyników dzia³ania
	    (weryfikacja poprawnoœci), gdzie:
				N - liczba punktów w jednym zbiorze 
				T - wybrany algorytm (0 - brutal force)
				                     (1 - algorytm 1)
5) T11_2 -3g -N<val> -S<val> <T> <R> <ilosc_pomiarow>
	--> wykonanie z generacj¹ danych losowych z zadanym ziarnem , pomiarem czasu i prezentacj¹ wyników pomiarów, 
			gdzie: 
			      T - wybrany algorytm (0 - brutal force (tylko do 6 wierzcho³ków - w przypadku niespe³nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					           (1 - algorytm na podstawie najmniejszej odleg³oœci miêdzy punktami)
			      N - liczba punktów w jednym zbiorze
			      S - ziarno (seed) do generowania wartoœci
			      R - krok (co jak¹ iloœæ N bêdzie generowany kolejny pomiar)
			      ilosc_pomiarow - iloœæ pomiarów, jakie ma wykonaæ program
6) T11_2 -3gwout -N<val> <T> <R> <ilosc_pomiarow>
	--> wykonanie z generacj¹ danych losowo, pomiarem czasu i prezentacj¹ wyników pomiarów,
			gdzie:
			      T - wybrany algorym (0 - brutal force (tylko do 6 wierzcho³ków - w przypadku niespe³nienia tego warunku 
							            zostanie uruchomiony algorytm 1)
					          (1 - algorytm na podstawie najmniejszej odleg³oœci miêdzy punktami)
			      N - liczba punktów w jednym zbiorze 
			      R - krok (co jak¹ iloœæ N bêdzie generowany kolejny pomiar)
			      ilosc_pomiarow - iloœæ pomiarów, jakie ma wykonaæ program

<---- Opis konwencji dotycz¹cych danych wejœciowych ---->
Dane wejœciowe zawarte w pliku s¹ postaci:
x1,y1
x2,y1
gchange
x3,y3
x4,y4
end		
Nie mo¿e byæ miêdzy wartoœciami wspó³rzêdnych bia³ych znaków, jedynie przecinek. Konieczne jest u¿ycie s³ów kluczowych "gchange"
(aby zmieniæ grupê punktów), oraz "end" - aby wskazaæ koniec danych. W przypadku, gdy liczba punktów z obu grup bêdzie ró¿na,
zostanie zg³oszony b³¹d. Dane wczytywane z klawiatury nale¿y wpisywaæ z zachowaniem tej konwencji, jedynie zakoñczenie podawania
danych nale¿y zasygnalizowaæ s³owem kluczowym "quit".

<---- Prezentacja wyników ---->
Po wykonaniu siê algorytmu wynik jego pracy zapisywany jest do pliku graficznego. S¹ tam narysowane punkty i ³¹cz¹ce je linie. 
Aby obejrzeæ ten wynik nale¿y odszukaæ plik i wyœwietliæ go w przegl¹darce systemowej.

<---- Metoda rozwi¹zania ---->
W obydwu rozwi¹zaniach wykorzystywany jest kontener "vector".
1. "Brutal force"
   Sprawdzamy wszystkie mo¿liwe zbiory po³¹czeñ odcinków, i odrzucamy te, w których s¹ jakieœ odcinki, które siê przecinaj¹.
   Wykorzystywany jest tu algorytm z tzw. "zamiataniem".
2. Algorytm na podstawie najmniejszej odleg³oœci
   Najpierw ³¹czymy punkty najmniej odleg³e od siebie, nastêpnie sprawdzamy pary odcinków, czy nie przecinaj¹ siê. Jeœli siê 
   przecinaj¹, to ³¹czymy punkty z tej pary odcinków na inny sposób. Kontynuujemy sprawdzanie, a¿ do znalezienia takiego zbioru,
   w którym ¿adne 2 odcinki siê nie przecinaj¹.

<---- Przewodnik po plikach Ÿród³owych ---->
1. Algorithms - obiekt udostêpniaj¹cy statyczne metody algorytmiczne
2. DataReader - obiekt odpowiedzialny za obs³ugê wczytywania danych     --> zawarty w DataService
3. DataGenerator - obiekt odpowiedzialny za generacjê danych losowych   --> zawarty w DataService
4. FileIOException - obiekt reprezentuj¹cy wyj¹tek wejœcia-wyjœcia zwi¹zany z obs³ug¹ plików
5. Point2D - obiekt reprezentuj¹cy punkt na p³aszczyŸnie we wspó³rzêdnych XY
6. Segment - obiekt reprezentuj¹cy odcinek na p³aszczyŸnie
7. SetOfSegments - obiekt reprezentujacy zbiór odcinków na p³aszczyŸnie 
8. Sweeper - obiekt reprezentuj¹cy "miot³ê"
9. WrongNumberOfElementsException - obiekt reprezentuj¹cy wyj¹tek wejœcia-wyjœcia zwi¹zany z ró¿n¹ iloœci¹ punktów w obu grupach punktów
10. main.cpp - g³ówna pêtla programu

<---- Informacje dodatkowe ---->
1. Program mo¿na skompliowaæ w œrodowisku Windows (w IDE code::blocks po zaimportowaniu projektu znajduj¹cego siê w pliku *.cpb)
   lub w œrodowisku Linux, wydaj¹c polecenie "make" w g³ównym katalogu programu.
2. W zwi¹zku ze z³o¿onoœci¹ algorytmu 1, maksymalny rozmiar problemu, jaki mo¿e zostaæ przez niego rozwi¹zany, to 6 wierzcho³ków
   w jednej grupie (³¹cznie 12 wierzcho³ków). W przeciwnym razie program generuje tak du¿o elementów, które powinny zostaæ 
   dodane do vectora, ¿e ów vector wyrzuca wyj¹tek zwi¹zany z przepe³nieniem (std::bad_alloc), przerywaj¹cy dzia³anie programu.
3. W przypadku podania b³êdnej nazwy pliku w trybie wykonania, w którym dane czytane s¹ z pliku, zostanie wyrzucony wyj¹tek 
   zwi¹zany z brakiem odpowiedniego pliku na komputerze.
4. Generator danych testowych generuje punkty losowo z zadanym "seed", lub bior¹c za ziarno zegar.
5. W przypadku, gdy podczas wczytywania danych z pliku lub z klawiatury, w jednej grupie bêdzie wiêcej
   lub mniej punktów, ni¿ w drugiej, zostanie wyrzucony odpowiedni wyj¹tek, niedopuszczaj¹cy do dalszego
   wykonania programu.
6. Z niewyjaœnionych przyczyn w lini 324 z klasy Algorithm (plik Algorithm.cpp) nie dzia³a inicjowanie obiektu dla
   wartoœci inicjuj¹cej generator wartoœci testowych równej 10. 
7. Uwagi i pytania kierowaæ do autora projektu.