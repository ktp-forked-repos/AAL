*Autor:
Piotr Jastrzêbski
p.k.jastrzebski.2@stud.elka.pw.edu.pl
nr. indeksu: 225594

*Temat:
(AAL-8-LS) W uk³adzie wspó³rzêdnych XOY znajduje siê n punktów. Jeden z tych punktów jest wyró¿niony. Nale¿y znaleŸæ wielok¹t wypuk³y o wierzcho³kach wybranych z podanego zbioru punktów oraz wyró¿nionego punktu, który posiada maksymaln¹ liczbê wierzcho³ków (w jednym wariancie) lub pokrywa maksymaln¹ liczb¹ punktów z wejœciowego zbioru (w drugim wariancie).

*Obs³uga
Po uruchomieniu programu w oknie konsoli pojawiaj¹ siê stosowne opcje.
Krokiem pierwszym jest wybranie algorytmu, który bêdzie prezentowany poprzez wprowadzenie cyfry 1 albo 2 i zaakceptowaniem klawiszem ENTER.
Krokiem drugim jest wybranie metody wprowadzania wyników. Wprowadzenie cyfry 1 uaktywni tryb wprowadzania danych z pliku. Wprowadzenie cyfry 2 wygeneruje dane losowe. Wprowadzenie cyfry 3 uaktywnia tryb pomiaru czasu operacji generuj¹c dane losowe.
Krok trzeci w zale¿noœci od trybu prosi o podanie œcie¿ki do pliku z danymi (opcja 1) albo o wprowadzenie liczby okreœlaj¹cej licznoœæ losowo generowanego zbioru (opcja 2 oraz 3).

*Wprowadzanie danych:
Dane wejœciowe pobierane z pliku tekstowego, którego nazwa podana jest przy rozpoczêciu programu przez u¿ytkownika.
W pierwszej linii pliku znajduj¹ siê wspó³rzêdne punktu wyró¿niony w postaci: Wspó³rzêdnaX Wspó³rzêdnaY.
W kolejnych liniach w takiej samej formie inne punkty ze zbioru.
W przypadku danych generowanych losowo u¿ytkownik okreœla rozmiar oczekiwanego zbioru.

*Dane wejœciowe:
Wspó³rzêdne podawane winny byæ w formie liczby podwójnej precyzji (typ double) oddzielone spacj¹. Poszczególne pary rozdzielone znakiem nowej linii.

*Prezentacja wyników:
Wyniki dzia³ania programu prezentowane w formie graficznej w oknie programu. Na czerwono zaznaczony punkt wyró¿niony. Inne punkty maj¹ kolor niebieski. Powsta³y wielok¹t ma kolor ¿ó³ty. Ewentualne dodatkowe dane pomocnicze oraz czasy wykonañ i z³o¿onoœæ obliczeniowa prezentowane w konsoli.

*Metoda rozwi¹zania problemu nr 1. (maksymalna liczba wierzcho³ków wielok¹ta wypuk³ego):
-Pocz¹tkowa koncepcja (metoda biggestVerticesSet(Vertices v) - nie daj¹ca rezultatów):
Dla ca³ego zadanego podzbioru punktów i punktu wyró¿nionego znajdowana jest otoczka wypuk³a. Zapamiêtujê, które punkty do niej nale¿¹ i usuwam je, lecz jeœli punkt wyró¿niony nale¿a³ do otoczki nie jest usuwany, ale wraca do kolejnej iteracji. Teraz na wejœciu jest zmniejszony podzbiór punktów. Powtarzane jest to w ten sposób, a¿ pozostanie w podzbiorze jeden lub 2 punkty, nie bêd¹ce w stanie utworzyæ wielok¹ta. Nastêpnie, pocz¹wszy od najbardziej wewnêtrznej otoczki wypuk³ej przesuwaj¹c siê na zewn¹trz wybieramy krawêdŸ i na jej przed³u¿eniu prowadzimy prost¹. W pó³p³aszczyŸnie po stronie otoczki zliczamy liczbê wierzcho³ków z otoczki wy¿szego rzêdu i jeœli jest ona wy¿sza ni¿ liczba dotychczasowa pozwalamy sobie na nowe po³¹czenie. Rozwa¿amy tak kolejne krawêdzie, do czasu a¿ sprawdzimy wszystkie i wracamy, aby sprawdziæ dotychczasow¹ otoczkê z otoczk¹ kolejnego ju¿ stopnia. Gdy wszystko zostanie sprawdzone, tj. nie ma wiêcej krawêdzi do zbadania oraz nie istnieje wiêksza otoczka, koñczymy.
-Tymczasowa koncepcja naiwna (metoda STUPID_biggestVerticesSet(Vertices v)) - dzia³aj¹ca w akceptowalnym czasie dla maksymalnie 9 elementów zbioru):
Wraz z koniecznoœci¹ zmiany podejœcia i ewentualnego wprowadzenia rozwi¹zania heurystycznego zasadne wyda³o mi siê stworzenie algorytmu badaj¹cego jak dalekie od ca³kowicie poprawnego rozwi¹zania by³yby rozwi¹zania generowane przez algorytm heurystyczny. Metoda naiwna implementuje sprawdzanie rozmiaru generowanych otoczek dla wszystkich podzbiorów zbioru wejœciowego. (tzn. dla zbioru N elementowego sprawdza otoczkê dla N wierzcho³ków, nastêpnie dla ka¿dej kombinacji N-1 wierzcho³ków itd., a¿ do takiego k, ¿e N-k=3) Metoda mimo, ¿e poprawnie rozwi¹zuje problem ma zadanie jedynie porównawcze, gdy¿ wynikaj¹ca z podejœcia z³o¿onoœæ obliczeniowa roœnie w takim tempie, ¿e rozs¹dne staje siê sprawdzanie rezultatów dla zbiorów maksymalnie 9 elementowych.
-Koñcowa koncepcja heurystyczna (metoda HEURISTIC_biggestVerticesSet(Vertices v)) - ta koncepcja z wykorzystaniem heurystyk zak³ada kilka usprawnien w stosunku
do algorytmu naiwnego. Poprawki te zosta³y wprowadzone na podstawie
obserwacji zachowania funkcji naiwnej i dla prawie wszystkich wywo³an daje
bardzo dobre rezultaty przy znacznie zredukowanym koszcie obliczeniowym
m.in. mozliwe sta³y sie obliczenia dla zbioru punktów rzedu kilkudziesieciu
lub kilkuset w porównaniu do kilku przy algorytmie naiwnym. G³ównymi
za³ozeniami jest przeszukiwanie pó³p³aszczyzny bardziej licznej wykreslonej
przez prosta przechodzaca przez punkt wyrózniony i inny dowolny. Nastepnie
wyliczajac i zdejmujac kolejne otoczki ze zbioru otrzymuje sie minimalny
zbiór wypuk³y. Ten zbiór jest punktem wyjscia dla dalszych kroków algorytmu.
Ze zbioru minimalnego program stara sie do³aczyc punkty z otoczki
wyzszego rzedu tak, by licznosc zbioru wyjsciowego nie zmniejszy³a sie. Kiedy
punkty z otoczki rzedu n skoncza sie, sprawdzane sa punkty z otoczki
rzedu n + 1. W momencie wyczerpania zbioru otoczek wszystkich rzedów
funkcja zwraca zbiór zawierajacy maksymalny zestaw wierzcho³ków wielokata
wypuk³ego.

*Metoda rozwi¹zania problemu nr 2. (maksymalna liczba punktów przykryta wilok¹tem wypuk³ym):
Algorytm bazuje na sprawdzaniu licznoœci zbiorów punktów lewej i prawej pó³p³aszczyzny utworzonych przez podzielenie przestrzeni prost¹ zawieraj¹c¹ 2 punkt: jeden sta³y (wyró¿niony) i drugi ze zbioru wejœciowego. Nastêpnie wybierany jest maksymalny lewy lub prawy podzbiór i na punktach z owego podzbioru wyznaczana jest otoczka wypuk³a. Otoczka wyznaczana jest algorytmem Jarvisa pod¹¿aj¹cym dwoma drogami, od punktu o najmniejszych wspó³rzêdnych (x,y) w górê oraz od punktu o nawiêkszych wspó³rzêdnych (x,y) w dó³. Konkatenacja tych dróg w rezultacie daje otoczkê wypuk³¹ tworz¹c¹ wielok¹t wypuk³y pokrywaj¹cy najwiêksz¹ liczbê punktów.

*Struktury danych:
Informacje oraz metody dotycz¹ce pojedynczego punktu w uk³adzie XY (wspó³rzêdna X, wspó³rzêdna Y, fakt bycia punktem zaznaczonym) przechowywane s¹ w klasie MyPoint. 
Informacje oraz metody zbioru punktów (zbiór wejœciowy, wygenerowana otoczka wypuk³a, zbiór punktów do kreœlenia wielok¹ta) przechowywane s¹ w klasie Vertices.

*Informacje o funkcjonalnej dekompozycji programu na modu³y Ÿród³owe - nag³ówkowe i implementacyjne:
Program podzielony zosta³ na pliki Ÿród³owe i nag³ówkowe zgodnie z konwencj¹ jêzyka C++:
Main.cpp		- g³ówna czêœæ programu, obs³uga wstêpnej komunikacji z u¿ytkownikiem
View.cpp/.h		- klasa odpowiedzialna za rysowanie interfejsu graficznego
MyPoint.cpp/.h	- klasa implementuj¹ca pojedynczy punkt
Vertices.cpp/.h	- klasa implementuj¹ca zbiory wierzcho³ków
Functions.cpp.h	- klasa w³aœciwych funkcji zadania

*Inne informacje dodatkowe o szczególnych decyzjach projektowych:
Program wspierany jest wizualizacj¹ w technice OpenGL. Do jego dzia³ania wymagany jest plik biblioteki glut.h.