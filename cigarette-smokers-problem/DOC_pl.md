#Problem palaczy

Mamy trzech palaczy. Każdy z nich ma nieskończenie wiele albo tytoniu, albo zapałek albo bibułek. Aby skręcić papierosa, palacz potrzebuje wszystkich trzech składników. Mamy również dilera, który kładzie na stół dwa składniki na *pustym* stole. Następnie palacz, któremu do kompletu brakuje tych składników, zgarnia je, skręca papierosa, pali go przez chwilę i sygnalizuje dilerowi aby dostarczył kolejne zapasy. Scenariusz powtarza się.


####Problem - Zakleszczenie

Rozważmy sytuację, w której diler kładzie na stole tytoń i bibułki. Placz, który potrzebuje bibułki, bierze ją. Jednakże równocześnie inny palacz, który potrzebuje tytoniu, też go zgarnia. Niestety, żaden z palaczy nie ma wystarczającej ilości składników, aby skręcić papierosa. Czyli żaden z nich nie może poinformować dilera, aby położył kolejne składniki.

####Rozwiązanie - semafory

Aby uniknąc tej sytuacji, diler musi pozwolić konkretnemu palaczowi zabrać przedmioty. Czyli potrzebujemy czterech semaforów. Trzy z nich pozwalają palaczom wziąć oba składniki ze stołu. Czwarty z nich informuje dilera o pustym stole.

##Implementacja

####`main.c`
Deklaracja i inicjowanie: semaforów oraz wątków palaczy i dilera.

####`smoker.c`
Proces palacza: `smoker(void *_ownedMaterial)`. Każdy z placzy czeka pod jednym z trzech semaforów: `PaperAndMatches`, `TobaccoAndPaper`, `MatchesAndTobacco`. Będąc poinformowanym, palacz bierze przedmioty, skręca papierosa i wypala go przez `SMOKINGTIME` sekund. 

???? TO ZDANIE ZREDAGUJ Po wszystkim podnoszony jest semafor `Delivery`, który pozwala dilerowi ponownie wykonać swoją pracę.


####`agent.c`
Proces dilera. `agent()` - wybiera dwa składniki i kładzie je (`putOnTheTable()`) na stole. Następnie odpowiedni diler otrzymuje pozolenie na zabranie składników. W celu uławienia odrobaczenia programu diler położy przedmioty jedynie `DELIVERIES` razy.


####`main.h`
Definicja wszystkich wyżej wymienionych funkcji, semaforów i stałych.


##Testowanie
Po prostu wykonaj `make && ./cigs` i obejrzyj wynik.

##Przydatne źródła

* [The Cigarette-Smokers Problem na Michigan Technological University](https://www.cs.mtu.edu/~shene/NSF-3/e-Book/SEMA/TM-example-smoker.html)
* [POSIX Threads na Wikibooks](https://pl.wikibooks.org/wiki/POSIX_Threads)
* [POSIX Semaphores na Villanova University](http://www.csc.villanova.edu/~mdamian/threads/posixsem.html)
