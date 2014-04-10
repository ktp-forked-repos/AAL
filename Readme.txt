*Autor:
Piotr Jastrz�bski
p.k.jastrzebski.2@stud.elka.pw.edu.pl
nr. indeksu: 225594

*Temat:
(AAL-8-LS) W uk�adzie wsp�rz�dnych XOY znajduje si� n punkt�w. Jeden z tych punkt�w jest wyr�niony. Nale�y znale�� wielok�t wypuk�y o wierzcho�kach wybranych z podanego zbioru punkt�w oraz wyr�nionego punktu, kt�ry posiada maksymaln� liczb� wierzcho�k�w (w jednym wariancie) lub pokrywa maksymaln� liczb� punkt�w z wej�ciowego zbioru (w drugim wariancie).

*Obs�uga
Po uruchomieniu programu w oknie konsoli pojawiaj� si� stosowne opcje.
Krokiem pierwszym jest wybranie algorytmu, kt�ry b�dzie prezentowany poprzez wprowadzenie cyfry 1 albo 2 i zaakceptowaniem klawiszem ENTER.
Krokiem drugim jest wybranie metody wprowadzania wynik�w. Wprowadzenie cyfry 1 uaktywni tryb wprowadzania danych z pliku. Wprowadzenie cyfry 2 wygeneruje dane losowe. Wprowadzenie cyfry 3 uaktywnia tryb pomiaru czasu operacji generuj�c dane losowe.
Krok trzeci w zale�no�ci od trybu prosi o podanie �cie�ki do pliku z danymi (opcja 1) albo o wprowadzenie liczby okre�laj�cej liczno�� losowo generowanego zbioru (opcja 2 oraz 3).

*Wprowadzanie danych:
Dane wej�ciowe pobierane z pliku tekstowego, kt�rego nazwa podana jest przy rozpocz�ciu programu przez u�ytkownika.
W pierwszej linii pliku znajduj� si� wsp�rz�dne punktu wyr�niony w postaci: Wsp�rz�dnaX Wsp�rz�dnaY.
W kolejnych liniach w takiej samej formie inne punkty ze zbioru.
W przypadku danych generowanych losowo u�ytkownik okre�la rozmiar oczekiwanego zbioru.

*Dane wej�ciowe:
Wsp�rz�dne podawane winny by� w formie liczby podw�jnej precyzji (typ double) oddzielone spacj�. Poszczeg�lne pary rozdzielone znakiem nowej linii.

*Prezentacja wynik�w:
Wyniki dzia�ania programu prezentowane w formie graficznej w oknie programu. Na czerwono zaznaczony punkt wyr�niony. Inne punkty maj� kolor niebieski. Powsta�y wielok�t ma kolor ��ty. Ewentualne dodatkowe dane pomocnicze oraz czasy wykona� i z�o�ono�� obliczeniowa prezentowane w konsoli.

*Metoda rozwi�zania problemu nr 1. (maksymalna liczba wierzcho�k�w wielok�ta wypuk�ego):
-Pocz�tkowa koncepcja (metoda biggestVerticesSet(Vertices v) - nie daj�ca rezultat�w):
Dla ca�ego zadanego podzbioru punkt�w i punktu wyr�nionego znajdowana jest otoczka wypuk�a. Zapami�tuj�, kt�re punkty do niej nale�� i usuwam je, lecz je�li punkt wyr�niony nale�a� do otoczki nie jest usuwany, ale wraca do kolejnej iteracji. Teraz na wej�ciu jest zmniejszony podzbi�r punkt�w. Powtarzane jest to w ten spos�b, a� pozostanie w podzbiorze jeden lub 2 punkty, nie b�d�ce w stanie utworzy� wielok�ta. Nast�pnie, pocz�wszy od najbardziej wewn�trznej otoczki wypuk�ej przesuwaj�c si� na zewn�trz wybieramy kraw�d� i na jej przed�u�eniu prowadzimy prost�. W p�p�aszczy�nie po stronie otoczki zliczamy liczb� wierzcho�k�w z otoczki wy�szego rz�du i je�li jest ona wy�sza ni� liczba dotychczasowa pozwalamy sobie na nowe po��czenie. Rozwa�amy tak kolejne kraw�dzie, do czasu a� sprawdzimy wszystkie i wracamy, aby sprawdzi� dotychczasow� otoczk� z otoczk� kolejnego ju� stopnia. Gdy wszystko zostanie sprawdzone, tj. nie ma wi�cej kraw�dzi do zbadania oraz nie istnieje wi�ksza otoczka, ko�czymy.
-Tymczasowa koncepcja naiwna (metoda STUPID_biggestVerticesSet(Vertices v)) - dzia�aj�ca w akceptowalnym czasie dla maksymalnie 9 element�w zbioru):
Wraz z konieczno�ci� zmiany podej�cia i ewentualnego wprowadzenia rozwi�zania heurystycznego zasadne wyda�o mi si� stworzenie algorytmu badaj�cego jak dalekie od ca�kowicie poprawnego rozwi�zania by�yby rozwi�zania generowane przez algorytm heurystyczny. Metoda naiwna implementuje sprawdzanie rozmiaru generowanych otoczek dla wszystkich podzbior�w zbioru wej�ciowego. (tzn. dla zbioru N elementowego sprawdza otoczk� dla N wierzcho�k�w, nast�pnie dla ka�dej kombinacji N-1 wierzcho�k�w itd., a� do takiego k, �e N-k=3) Metoda mimo, �e poprawnie rozwi�zuje problem ma zadanie jedynie por�wnawcze, gdy� wynikaj�ca z podej�cia z�o�ono�� obliczeniowa ro�nie w takim tempie, �e rozs�dne staje si� sprawdzanie rezultat�w dla zbior�w maksymalnie 9 elementowych.
-Ko�cowa koncepcja heurystyczna (metoda HEURISTIC_biggestVerticesSet(Vertices v)) - ta koncepcja z wykorzystaniem heurystyk zak�ada kilka usprawnien w stosunku
do algorytmu naiwnego. Poprawki te zosta�y wprowadzone na podstawie
obserwacji zachowania funkcji naiwnej i dla prawie wszystkich wywo�an daje
bardzo dobre rezultaty przy znacznie zredukowanym koszcie obliczeniowym
m.in. mozliwe sta�y sie obliczenia dla zbioru punkt�w rzedu kilkudziesieciu
lub kilkuset w por�wnaniu do kilku przy algorytmie naiwnym. G��wnymi
za�ozeniami jest przeszukiwanie p�p�aszczyzny bardziej licznej wykreslonej
przez prosta przechodzaca przez punkt wyr�zniony i inny dowolny. Nastepnie
wyliczajac i zdejmujac kolejne otoczki ze zbioru otrzymuje sie minimalny
zbi�r wypuk�y. Ten zbi�r jest punktem wyjscia dla dalszych krok�w algorytmu.
Ze zbioru minimalnego program stara sie do�aczyc punkty z otoczki
wyzszego rzedu tak, by licznosc zbioru wyjsciowego nie zmniejszy�a sie. Kiedy
punkty z otoczki rzedu n skoncza sie, sprawdzane sa punkty z otoczki
rzedu n + 1. W momencie wyczerpania zbioru otoczek wszystkich rzed�w
funkcja zwraca zbi�r zawierajacy maksymalny zestaw wierzcho�k�w wielokata
wypuk�ego.

*Metoda rozwi�zania problemu nr 2. (maksymalna liczba punkt�w przykryta wilok�tem wypuk�ym):
Algorytm bazuje na sprawdzaniu liczno�ci zbior�w punkt�w lewej i prawej p�p�aszczyzny utworzonych przez podzielenie przestrzeni prost� zawieraj�c� 2 punkt: jeden sta�y (wyr�niony) i drugi ze zbioru wej�ciowego. Nast�pnie wybierany jest maksymalny lewy lub prawy podzbi�r i na punktach z owego podzbioru wyznaczana jest otoczka wypuk�a. Otoczka wyznaczana jest algorytmem Jarvisa pod��aj�cym dwoma drogami, od punktu o najmniejszych wsp�rz�dnych (x,y) w g�r� oraz od punktu o nawi�kszych wsp�rz�dnych (x,y) w d�. Konkatenacja tych dr�g w rezultacie daje otoczk� wypuk�� tworz�c� wielok�t wypuk�y pokrywaj�cy najwi�ksz� liczb� punkt�w.

*Struktury danych:
Informacje oraz metody dotycz�ce pojedynczego punktu w uk�adzie XY (wsp�rz�dna X, wsp�rz�dna Y, fakt bycia punktem zaznaczonym) przechowywane s� w klasie MyPoint. 
Informacje oraz metody zbioru punkt�w (zbi�r wej�ciowy, wygenerowana otoczka wypuk�a, zbi�r punkt�w do kre�lenia wielok�ta) przechowywane s� w klasie Vertices.

*Informacje o funkcjonalnej dekompozycji programu na modu�y �r�d�owe - nag��wkowe i implementacyjne:
Program podzielony zosta� na pliki �r�d�owe i nag��wkowe zgodnie z konwencj� j�zyka C++:
Main.cpp		- g��wna cz�� programu, obs�uga wst�pnej komunikacji z u�ytkownikiem
View.cpp/.h		- klasa odpowiedzialna za rysowanie interfejsu graficznego
MyPoint.cpp/.h	- klasa implementuj�ca pojedynczy punkt
Vertices.cpp/.h	- klasa implementuj�ca zbiory wierzcho�k�w
Functions.cpp.h	- klasa w�a�ciwych funkcji zadania

*Inne informacje dodatkowe o szczeg�lnych decyzjach projektowych:
Program wspierany jest wizualizacj� w technice OpenGL. Do jego dzia�ania wymagany jest plik biblioteki glut.h.