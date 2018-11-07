# Data-Stuctures-HW-2

Sursa "AVLTree.h"

-> createTree :
	- am alocat memeorie pentru arbore, am initializat functiile pentru element / info
	- am initializat dimensiunea cu 0
-> createTreeNode :
	- am alocat memorie pentru un nod si am initializat valorile pentru elem si info folosind
	 functiile corespunzatoare lor
	- am stabilit legaturile de baza pentru end, lt(left), rt(right), prev si next
	- am setat inaltimea nodului ca fiind 1
-> destryTreeNode :
	- distrus campurile pt elem si info
	- am dezalocat memoria nodului
-> isEmpty : 
	- am verificat printr-o linie daca tree->root este / nu este NULL
-> search : 
	- plecand de la un nod dat ca paramentru, parcurg arborele pana la nodul dorit
-> minimum : 
	- cat timp nodul din stanga nu era NULL am parcurs arborele
	- ultimul nod la care s-a ajuns este chiar minimul
-> maximum :
	- cat timp nodul din dreapta nu era NULL am parcurs arborele
	- ultimul nod la care s-a ajuns este chiar maximul
-> successor :
	-
-> predecessor :
	-
-> avlRotateLeft :
	-
-> avlRotateRight :
	-
-> avlGetBalance :
	- calculez diferenta de nivel intre copiii nodului x
-> avlFixUp :
	- un functie de diferenta de nivel am stabilit cele 4 cazuri de rotire
-> insert : 
	- daca arborele este NULL atunci se iese din functie
	- creez nodul ce trebuie adaugat
	- daca arborele e gol atunci initializez tree->root = newNode;
	- daca nu este gol atunci se merge pana la pozitia unde trebuie inserat noul nod
	- daca elementul nu se mai gasesc in arbore atunci se insereaza ca si copil al nodului unde
	s-a oprit cautare; se actualizeaza parintele nodului nou si nivelul nodului care primeste copil nou
	- se apeleaza avlFixUp pentru a repara diferentele de nivel dintre noduri
	- se actualizeaza legaturiile de prev si next ale nodului nou, deoarece acestea trebuie sa
	pointeze catre predecesorul nodului, respectiv succesorul nodului
	- daca elementul se afla deja in arbore atunci trebuie adaugat in lista si se actualizeaza 
	legaturile next si prev;
	- list este capul listei;
	- noul element din lista va fi pus mereu la sfarsit;
-> deleteHelper :
	- ma ajuta la delete pentru modularizarea codului
	- elibereaza zona alocata pentru nod si distruge campurile pentru info si element
-> delete :
	-
-> destroyTree : 
	- pornind de la minimul arborelui sterg fiecare nod al arborelui, arborele este parcurs cu next
