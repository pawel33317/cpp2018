#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <forward_list>
#include "chapterS.hpp"
using namespace std;

void stlContainers();

void chapter16run()
{
    cout << "\n\n-----chapter 16 started-----\n";
    stlContainers();
}

void stlContainers()
{
    //3 główne rodzaje: sequence kontenery, asocjacyjne, adaptery



    //SEKWENCYJNE: utrzymują kolejność elementów, można wybrać miejsce wstawienia elementu
    //vector, deque, array, list, forward_list, basic_string

    //vector - dynamiczna array, która umie rosnąć, pozwala na random access (i[6])
    //pozwala na SZYBKIE dodawanie i usuwanie elementów na końcu .push_back(), pop_back()
    vector<int> vec;
    vec.push_back(5);

    //deque - czyt deck (desk) - podwójnie zakończona dynamiczna array może rosnąć
    // .push_back(), .push_front()
    deque<int> deq;
    deq.push_back(5);
    deq.push_front(25);
    cout << deq.front() << endl;
    deq.pop_front();

    //list - double linked list, każdy element listy posiada wskaźnik na kolejny
    //i poprzedni element w liście, lista daje dostep tylko do pierwszego i ostatniego elementu
    //czyli brak random access, aby znalźć element pośrodku trzeba przechodzić po kolei
    //dodawanie elementów do listy jest bardzo szybkie (o ile wiemy gdzie chcemy dodać)
    //używa się iteratorów do chodzenia po liście
    list<int> l;
    l.push_back(5);
    l.push_front(4);
    auto it = l.begin();
    l.insert(++it, 100);
    for(auto& elem : l){
        cout << elem << ", ";
    }

    //string i wstring niby nie są uwzględnione jako kontenery sekwencyjne ale tak naprawdę są
    //nimi można je rozważać jak wektory z elementami typu char
    string st = "abcde"s;

    //forward_list - singly-linked list ma tylko 1 pointer a nie jak lista 2 
    //czyli iteracja tylko z początku do końca
    forward_list<int> fl {12};
    fl.push_front(5);//nie ma back
    fl.push_front(4);
    fl.insert_after(fl.begin(), 100);
    for(auto& elem : fl)
        cout << elem << ", ";
    cout << endl;



    //ASOCJACYJNE - automatycznie sortują dane wejściowe podczas wstawiania
    //elementy są porównywane przez operator<

    //set - trzyma unikalne elementy, nie pozwala na duplikaty, kolejność zgodna z wartościami
    //prawie jak binarne drzewo przeszukiwań
    set<int> s {1,2,3,4,3,2,1};
    s.insert(5);
    s.insert(1);
    for(auto& elem : s)
        cout << elem << ",";
    cout << endl;

    //multiset - set pozwalający na duplikaty
    multiset<int> ms {1,2,3,4,3,2,1};
    ms.insert(5);
    ms.insert(1);
    for(auto& elem : ms)
        cout << elem << ",";
    cout << endl;

    //map - associative array - set w którym każdy element jest parą zwaną klucz/wartość
    //klucz jest używany do sortowania i indexowania danych, musi być unikalny,
    //wartość jest rzeczywistą wartością
    map<int, string> m {{1, "jeden"}};
    m[2] = "dwa"s;
    m[3] = "trzy"s;
    m[3] = "cztery"s;
    for(auto& elem : m)
        cout << "[" << elem.first << "]" << ": " << elem.second << ", ";
    cout << endl;

    //multimap - dictionart - mapa pozwalająca na zduplikowane klucze (jak przwdziwy słownik)
    //elementy uporządkowane rosnąco
    multimap<int, string> mm {{1, "jeden"}};
    mm.insert(make_pair<int, string>(2, "dwa"s));
    mm.insert(make_pair<int, string>(3, "trzy"s));
    mm.insert(make_pair<int, string>(3, "cztery"s));
    for(auto& elem : mm)
        cout << "[" << elem.first << "]" << ": " << elem.second << ", ";
    cout << endl;

    //ADAPTERS - specjalnie zdefiniowane kontenery przystosowane do specjalnego użycia
    //w kontenerach adapterach można wybrać kontener sekwencyjny, którego chce sie używać

    //stack - elementy działają jak kolejka LIFO, push, pop alementy są wrzucane i ściągane
    //z końca kontenera stack domyślnie uπywa deque co jest dziwne może też używać vector, list
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);
    cout << stk.top();
    stk.pop();
    cout << stk.top();
    stk.pop();
    cout << stk.top();
    stk.pop();
    cout << endl;
    //queue - elementy działaja jak kolejka FIFO, elementy są pushowane na koniec kontenera
    //i popowane z początku kontenera, queue domyslnie używa deque może też używać listy
    queue<int> que;
    que.push(1);
    que.push(2);
    que.push(3);
    cout << que.front();
    que.pop();
    cout << que.front();
    que.pop();
    cout << que.front();
    que.pop();
    cout << endl;

    //priority_queue ekementy sa sortowane poprzez operator< podczaas pushowania elementu
    //usuwanie elementu z początku zwraca item najwyższego priorytetu w kolejce
    queue<int> pque;
    pque.push(1);
    pque.push(2);
    pque.push(3);
    cout << pque.front();
    pque.pop();
    cout << pque.front();
    pque.pop();
    cout << pque.front();
    pque.pop();
    cout << endl;
}
