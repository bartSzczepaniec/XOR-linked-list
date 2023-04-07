#include<iostream>
#include<string>

using namespace std;

struct xorllist // xor linked list
{
	int value;
	xorllist* xornp; // xor z next i previous
};

void addBeg(xorllist** beg, xorllist** end, xorllist** actual, int data);
void addEnd(xorllist** beg, xorllist** end, xorllist** actual, int data);
void addAct(xorllist** beg, xorllist** end, xorllist** actual, int data);
void printForward(xorllist* beg);
void printBackward(xorllist* end);
void showActual(xorllist* actual);
void goNext(xorllist** actual, xorllist* beg, xorllist* end);
void goPrev(xorllist** actual, xorllist* beg, xorllist* end);
void delBeg(xorllist** beg, xorllist** end, xorllist** actual);
void delEnd(xorllist** beg, xorllist** end, xorllist** actual);
void delAct(xorllist** beg, xorllist** end, xorllist** actual);
void delVal(xorllist** beg, xorllist** end, xorllist** actual, int data);
void clearList(xorllist** beg, xorllist** end, xorllist** actual);

int main()
{
	string command;
	xorllist* beg; // ustawienie wszystkich wskaŸników jako nullptr
	xorllist* end;
	xorllist* actual;
	beg = nullptr;
	end = nullptr;
	actual = nullptr;

	while (cin >> command) // obs³uga komend
	{
		if (command == "ACTUAL")
		{
			showActual(actual);
		}
		else if (command == "NEXT")
		{
			goNext(&actual,beg,end);
		}
		else if (command == "PREV")
		{
			goPrev(&actual, beg, end);
		}
		else if (command == "ADD_BEG")
		{
			int added_value;
			cin >> added_value;
			addBeg(&beg, &end, &actual, added_value);
		}
		else if (command == "ADD_END")
		{
			int added_value;
			cin >> added_value;
			addEnd(&beg, &end, &actual, added_value);
			
		}
		else if (command == "ADD_ACT")
		{
			int added_value;
			cin >> added_value;
			addAct(&beg, &end, &actual, added_value);
		}
		else if (command == "DEL_BEG")
		{
			delBeg(&beg, &end, &actual);
		}
		else if (command == "DEL_END")
		{
			delEnd(&beg, &end, &actual);
		}
		else if (command == "DEL_VAL")
		{
			int deleted_value;
			cin >> deleted_value;
			delVal(&beg, &end, &actual, deleted_value);
		}
		else if (command == "DEL_ACT")
		{
			delAct(&beg, &end, &actual);
		}
		else if (command == "PRINT_FORWARD")
		{
			printForward(beg);
		}
		else if (command == "PRINT_BACKWARD")
		{
			printForward(end);
		}
	}
	clearList(&beg, &end, &actual); // zwalnianie pamiêci, jeœli w liœcie pozosta³y jakieœ elementy
	return 0;
}

void addBeg(xorllist** beg, xorllist** end, xorllist** actual, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wskaŸniki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
		*actual = temp;
	}
	else
	{
		temp->xornp = *beg; // tworzymy nowy wêze³, który zawiera wskaŸnik na nastêpny (ten który wczeœniej by³ pierwszy)
		(*beg)->xornp = (xorllist*)((int)(*beg)->xornp ^ (int)temp); // przypisujemy nowy xor wskaŸników elementowi, który "przesuwamy"
		*beg = temp; // ustawiamy wskaŸnik na pocz¹tek na nowo dodany wêze³
	}
}

void addEnd(xorllist** beg, xorllist** end, xorllist** actual, int data)
{
	xorllist* temp = new xorllist;
	temp->value = data;
	if (*beg == nullptr) // w przypadku, gdy lista jest pusta ustawiamy wszystkie wskaŸniki na pierwszy element
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
		*actual = temp;
	}
	else
	{
		temp->xornp = *end; // tworzymy nowy wêze³, który zawiera wskaŸnik na poprzedni (ten który wczeœniej by³ ostatni)
		(*end)->xornp = (xorllist*)((int)(*end)->xornp ^ (int)temp); // przypisujemy nowy xor wskaŸników elementowi, który "przesuwamy"
		*end = temp; // ustawiamy wskaŸnik na koniec na nowo dodany wêze³
	}
}

void addAct(xorllist** beg, xorllist** end, xorllist** actual, int data)
{
	xorllist* temp = new xorllist; // temp to dodawany wêze³
	temp->value = data;
	if (*actual == nullptr)
	{
		temp->xornp = nullptr;
		*beg = temp;
		*end = temp;
		*actual = temp;
	}
	else if (*actual == *beg) // jeœli aktualny element jest pocz¹tkowym to dodajemy tak samo jak na pocz¹tek
	{
		temp->xornp = *beg; // tworzymy nowy wêze³, który zawiera wskaŸnik na nastêpny (ten który wczeœniej by³ pierwszy)
		(*beg)->xornp = (xorllist*)((int)(*beg)->xornp ^ (int)temp); // przypisujemy nowy xor wskaŸników elementowi, który "przesuwamy"
		*beg = temp; // ustawiamy wskaŸnik na pocz¹tek na nowo dodany wêze³
	}
	else
	{
		xorllist* temp2 = *end; // temp2 bêdzie wskazywa³ na miejsce, przed które dodaæ nasz wêze³
		xorllist* prevtemp = nullptr;
		while (temp2 != *actual)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp2; // poprzednik aktualnego (licz¹c od koñca)
			temp2 = (xorllist*)((int)prev ^ (int)temp2->xornp); // docelowy aktualny
		}
		xorllist* next = (xorllist*)((int)temp2->xornp ^ (int)prevtemp); // adres nastêpnika actuala (od koñca)
		temp->xornp = (xorllist*)((int)temp2 ^ (int)next); // nowy element znajduje siê miêdzy aktualnym elementem, a poprzednim poprzednikiem (licz¹c od koñca)
		temp2->xornp = (xorllist*)((int)prevtemp ^ (int)temp); // xor nastêpnika actuala i nowego poprzednika
		xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp2); // nastêpnik nastêpnika actuala
		next->xornp = (xorllist*)((int)nextnext ^ (int)temp);
	}
}

void printBackward(xorllist* end)
{
	if (end != nullptr)
	{
		xorllist* temp = end;
		xorllist* prevtemp = nullptr; // przypisanie poprzedniego adresu wskaŸnika jako 0
		cout << temp->value << " ";
		while (((xorllist*)((int)prevtemp ^ (int)temp->xornp)) != nullptr)
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			cout << temp->value << " ";
		}
		cout << endl;
	}
	else
		cout << "NULL" << endl;
}

void printForward(xorllist* beg)
{
	if (beg != nullptr)
	{
		xorllist* temp = beg;
		xorllist* prevtemp = nullptr;
		cout << temp->value << " ";
		while (((xorllist*)((int)prevtemp ^ (int)temp->xornp)) != nullptr) // póki temp nie bêdziê wskazywa³ na nullptr
		{
			xorllist* prev = prevtemp;
			prevtemp = temp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			cout << temp->value << " ";
		}
		cout << endl;
	}
	else
		cout << "NULL" << endl;
}

void showActual(xorllist* actual)
{
	if (actual == nullptr)
		cout << "NULL" << endl;
	else
		cout << actual->value << endl;
}

void goNext(xorllist** actual, xorllist* beg, xorllist* end)
{
	if (*actual != nullptr)
	{
		if (*actual == end)// sytuacja, kiedy actual jest koniec -> przechodzi na pocz¹tek
		{
			cout << beg->value << endl;
			*actual = beg;
		}
		else
		{
			xorllist* temp = beg;
			xorllist* prev = nullptr;
			xorllist* prevtemp = nullptr;
			while (temp != *actual) // szukanie actual, a nastêpnie jego nastêpnika
			{
				prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			}
			prev = prevtemp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			// temp wskazuje na nastêpnik actuala
			cout << temp->value << endl;
			*actual = temp;

		}
	}
	else
		cout << "NULL" << endl;
}

void goPrev(xorllist** actual, xorllist* beg, xorllist* end)
{
	if (*actual != nullptr)
	{
		if (*actual == beg) // sytuacja, kiedy actual jest pocz¹tkiem -> przechodzi na koniec
		{
			cout << end->value << endl;
			*actual = end;
		}
		else
		{
			xorllist* temp = end;
			xorllist* prev = nullptr;
			xorllist* prevtemp = nullptr;
			while (temp != *actual)// szukanie actual, a nastêpnie jego poprzednika
			{
				prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			}
			prev = prevtemp;
			temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			// temp wskazuje na poprzednik actuala
			cout << temp->value << endl;
			*actual = temp;

		}
	}
	else
		cout << "NULL" << endl;
}

void delBeg(xorllist** beg, xorllist** end, xorllist** actual)
{
	if (*beg != nullptr)
	{
		if (*actual == *beg) // przesuniêcie actuala, jeœli jest taka sytuacja
			*actual = *end;

		xorllist* temp = (*beg);
		if (temp->xornp == nullptr) // kiedy jest tylko 1 element listy
		{
			delete temp;
			*beg = nullptr;
			*end = nullptr;
			*actual = nullptr;
		}
		else if (temp->xornp == *end) // kiedy s¹ tylko 2 elementy - pocz¹tek i koniec
		{
			delete temp;
			*beg = *end;
			(*end)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*) ((int)*beg ^ (int)temp->xornp->xornp); // adres trzeciego wêz³a (licz¹c od pocz¹tku)
			temp->xornp->xornp = tempnext;
			*beg = temp->xornp;
			delete temp;
		}
	}
}

void delEnd(xorllist** beg, xorllist** end, xorllist** actual)
{
	if (*beg != nullptr)
	{
		if (*actual == *end) // przesuniêcie actuala, jeœli jest taka sytuacja
			*actual = (*end)->xornp;

		xorllist* temp = (*end);
		if (temp->xornp == nullptr) // kiedy jest tylko 1 element listy
		{
			delete temp;
			*beg = nullptr;
			*end = nullptr;
			*actual = nullptr;
		}
		else if (temp->xornp == *beg) // kiedy s¹ tylko 2 elementy - pocz¹tek i koniec
		{
			delete temp;
			*end = *beg;
			(*beg)->xornp = nullptr;
		}
		else
		{
			xorllist* tempnext = (xorllist*)((int)*end ^ (int)temp->xornp->xornp); // adres trzeciego wêz³a (licz¹c od koñca)
			temp->xornp->xornp = tempnext;
			*end = temp->xornp;
			delete temp;
		}
	}
}

void delAct(xorllist** beg, xorllist** end, xorllist** actual)
{
	if (*actual != nullptr)
	{
		if (*actual == *beg)
			delBeg(beg,end,actual);
		else if(*actual == *end)
			delEnd(beg, end, actual);
		else // sytuacja, w której s¹ przynajmniej 3 elementy listy, a actual nie jest na brzegu
		{
			xorllist* temp = *end;
			xorllist* prev = nullptr;
			xorllist* prevtemp = nullptr;
			while (temp != *actual)
			{
				prev = prevtemp;
				prevtemp = temp; // poprzednik aktualnego (licz¹c od koñca)
				temp = (xorllist*)((int)prev ^ (int)temp->xornp); // docelowy aktualny
			}
			xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nastêpnika actuala (od koñca)
			xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp); // nastêpnik nastêpnika actuala
			next->xornp = (xorllist*)((int)nextnext ^ (int)prevtemp);
			if(prevtemp !=nullptr)
				prevtemp->xornp = (xorllist*)((int)prev ^ (int)next);
			*actual = next; // przechodz¹c liste od koñca next, jest poprzednikiem ( w normalnej kolejnoœci)
			delete temp;
		}
	}
}

void delVal(xorllist** beg, xorllist** end, xorllist** actual, int data)
{
	if (*beg != nullptr)
	{
		xorllist* temp = *end;
		xorllist* prevtemp = nullptr;
		xorllist* prev = nullptr;
		while (temp != nullptr)
		{
			while (temp != nullptr && temp->value != data)
			{
				prev = prevtemp;
				prevtemp = temp;
				temp = (xorllist*)((int)prev ^ (int)temp->xornp);
			}
			if (temp != nullptr && temp->value == data)
			{
				if (temp == *beg)
				{
					delBeg(beg, end, actual);
					temp = *beg;
					break;
				}
				else if (temp == *end)
				{
					delEnd(beg, end, actual);
					temp = *end;
				}
				else // sytuacja, w której usuwany wêze³ nie jest ani pierwszy ani ostatni
				{
					xorllist* next = (xorllist*)((int)temp->xornp ^ (int)prevtemp); // adres nastêpnika usuwanego wêz³a (od koñca)
					xorllist* nextnext = (xorllist*)((int)next->xornp ^ (int)temp); // nastêpnik nastêpnika usuwanego wêz³a
					next->xornp = (xorllist*)((int)nextnext ^ (int)prevtemp);
					prevtemp->xornp = (xorllist*)((int)prev ^ (int)next);
					if (temp == *actual)
						*actual = next; // przechodz¹c liste od koñca next, jest poprzednikiem ( w normalnej kolejnoœci)
					delete temp;
					temp = next;
				}

			}
		}
	}
}

void clearList(xorllist** beg, xorllist** end, xorllist** actual)
{
	while (*beg != nullptr)
		delBeg(beg, end, actual);
}