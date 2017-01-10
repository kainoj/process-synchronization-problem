#Problem palaczy

Mamy trzech palaczy. Każdy z nich ma nieskończenie wiele albo tytoniu, albo zapałek albo bibułek. Aby skręcić papierosa, palacz potrzebuje komplet wszystkich trzech składników. Mamy również dilera, który kładzie na stół dwa losowe składniki na *pustym* stole. Następnie palacz, któremu do kompletu brakuje tych składników, zgarnia je, skręca papierosa, pali go przez chwilę i sygnalizuje dilerowi aby dostarczył kolejne zapasy. Scenariusz powtarza się.


####Zakleszczenie

Rozważmy sytuację, w której diler kładzie na stole tytoń i bibułki. Palacz, który potrzebuje bibułki, bierze ją. Jednakże równocześnie inny palacz, który potrzebuje tytoniu, też go zgarnia. Niestety, żaden z palaczy nie ma wystarczającej ilości składników, aby skręcić papierosa. Czyli żaden z nich nie może poinformować dilera, aby położył on kolejne składniki.

####Rozwiązanie

Aby uniknąć tej sytuacji, diler musi umożliwić konkretnemu palaczowi zabrać przedmioty. Czyli potrzebujemy czterech semaforów. Trzy z nich umożliwiają palaczom wziąć oba składniki ze stołu. Czwarty z nich informuje dilera o pustym stole.

##Implementacja

####`main.c`
Deklaracja i inicjowanie: semaforów oraz wątków palaczy i dilera.

####`smoker.c`
Proces palacza: `smoker(void *_ownedMaterial)`. Każdy z palaczy czeka pod jednym z trzech semaforów: `PaperAndMatches`, `TobaccoAndPaper`, `MatchesAndTobacco`. Po otrzymaniu pozwolenia od dilera palacz bierze przedmioty ze stołu, skręca papierosa i wypala go przez `SMOKINGTIME` sekund. Następnie sygnalizowany jest semafor `Delivery`, który umożliwia dilerowi ponownie wykonać swoją pracę.

####`agent.c`
Proces dilera. `agent()` - wybiera dwa różne składniki i kładzie je na stole (`putOnTheTable()`). Następnie odpowiedni diler otrzymuje pozwolenie na zabranie składników. W celu ułatwienia odrobaczenia programu diler położy przedmioty jedynie `DELIVERIES` razy.

####`main.h`
Definicja wszystkich wyżej wymienionych funkcji, semaforów i stałych.

##Testowanie
Po prostu wykonaj `make && ./cigs` i obejrzyj wynik.

##Przydatne źródła

* [The Cigarette-Smokers Problem na Michigan Technological University](https://www.cs.mtu.edu/~shene/NSF-3/e-Book/SEMA/TM-example-smoker.html)
* [Dokumentacja fork()](https://linux.die.net/man/2/fork)
* [O pamięci dzielonej na Cardiff University](https://users.cs.cf.ac.uk/Dave.Marshall/C/node27.html)
* [POSIX Semaphores na Villanova University](http://www.csc.villanova.edu/~mdamian/threads/posixsem.html)

___
* [POSIX Threads na Wikibooks](https://pl.wikibooks.org/wiki/POSIX_Threads)
