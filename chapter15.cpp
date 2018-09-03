#include <iostream>
#include "chapterS.hpp"
using namespace std;

void smartPointersAndMoveSemanticsIntro();


void chapter15run()
{
    cout << "\n\n-----chapter 15 started-----\n";
    smartPointersAndMoveSemanticsIntro();
}

class Resource
{
public:
    Resource(){ cout << "Resource constructor\n";}
    ~Resource(){ cout << "Resource destructor\n";}
    void show(){ cout << "I am resource\n";};
};
template<class T>
class MyPtr
{
    T* mPtr;
public:
    MyPtr(T* ptr=nullptr) : mPtr(ptr) {}
    ~MyPtr() {delete mPtr; mPtr=nullptr;}
    T& operator*() {return *mPtr;}
    T* operator->() {return mPtr;}
};
void smartPointersAndMoveSemanticsIntro()
{
    //często zdarza się zapomnieć wolnić pamięć
    //nawet jak zwalaniamy na końcu funkcji może gdzieś nastąpić wcześniej
    //return lub throw

    //!!!dobrym rozwiązaniem jest użycie destruktorów, które wykonają się
    //po wyjściuze scope
    //!!!jest to sercem RAII

    MyPtr<Resource> mptr1{new Resource};//alokacja pamięci, brak jawnego delete
    //nie potrzebna* (<Resource*>) jako specyfikator typu dla MyPtr
    //ponieważ templatka ma już* (T*)
    //po wyjsciu ze scope resource będzie skasowane bo myptr jest zmienną lokalną
    (*mptr1).show();
    mptr1->show();
    (mptr1.operator->())->show();
    //!!!kompozycja MyPtr jest właścicielem Resource
    //!!!taka klasa jak MyPtr jest nazywana smart_pointerem
    //composition class zarządzająca dynamicznie zaalokowanymi zmiennymi
    //gwarantuje że zmienne zalokowane dynamiczne zostaną zdealokowane
    //po wyjściu ze scope

    //!!!destruktor obiektów lokalnych zostanie wykonany nawet jeśli nastąpi
    //wcześniejsze niespodziewane wyjście z funkcji

    //!!!poniższa linia bez semantyki przenoszenia lub licznika referencji
    //spowoduje critical flow
    //bo zdealokuje pamięć, która już została zdealokowana
    //MyPtr<Resource> mptr2{mptr1};
    //!!!ponieważ nie napisaliśmy operatora przypisania i konstruktora
    //kopiującego C++ dostarczył domyślne i jest robiona płytka kopia
    //Podobnie będzie jezeli przekażemy nasz obiekt mptr1 do funkcji przez wartość

    //Opcja 1: żeby rozwiązać ten problem można np usunąć operator przypisania i
    //konstruktor kopiujący ale wtedy nie będziemy mogli zwrócić MyPtr przez wartość
    //przez referencję czy pointer też nie bo będzie w jakiejś funkcji alokowana
    //lokalnie i po wyjściu czyszczona więc trzeba zwrócić przez wartość
    //co spowoduje shallow copies zduplikowane pointery i crashe

    //Opcja2: zoverridować konstruktor kopiujący i operator przypisania aby
    //robił głębokie kopie, ale kopie są drogie i czasami mogą być niemożliwe
    //dodatkowo po co robić głęboką kopię tylko po to żeby móc zwracać przez wartość
    //i dodatkowo przy przypisaniu raczej nie spodziewamy się, że 
    //będzie robiona kopia

    //Rozwiązanie - semantyka przenoszenia
    //SEMANTYKA PRZENOSZENIA oznacza że klasa przejmie własność obiektu zamiast robić kopię

    //Zacząć od move semantics
}
