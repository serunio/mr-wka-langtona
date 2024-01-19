Program może być wywołany z flagami:
-m – wymiar x planszy (poziomy),
-n – wymiar y planszy (pionowy),
-i – ilość kroków jaką ma wykonać mrówka,
-f – przedrostek plików wynikowych ze stanami planszy,
-k – początkowy kierunek mrówki,
-p – procent mapy jaki ma być na starcie zapełniony czarnymi polami.
odpowiednie ustawienie należy wpisać po fladze mu odpowiadającej, np.:
./mrowka -m 100 -n 100 -i 11000 -f mrowka -k gora -p 2
oznacza wymiary planszy 100 na 100, 11000 kolejnych stanów planszy drukowanych do plików o przedrostkach „mrowka”, mrówkę zwróconą na początku w górę i 2% planszy zapełnione czarnymi polami.
