#include <iostream>
#include "chapterS.hpp"
using namespace std;

void smartPointersAndMoveSemanticsIntro();
void rvalueReferences();
void moveConstructorAndAssigment();

void chapter15run()
{
    cout << "\n\n-----chapter 15 started-----\n";
    smartPointersAndMoveSemanticsIntro();
    rvalueReferences();
    moveConstructorAndAssigment();
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
class Resource2
{
public:
    Resource2(){ cout << "Resource constructor2\n";}
    ~Resource2(){ cout << "Resource destructor2\n";}
    void show(){ cout << "I am resource2\n";};
};
template<class T>
class MyPtr2
{
    T* mPtr;
public:
    MyPtr2(T* ptr=nullptr) : mPtr(ptr) {}
    ~MyPtr2() {delete mPtr; mPtr=nullptr;}
    T& operator*() {return *mPtr;}
    T* operator->() {return mPtr;}
    string isNull()
    {
        return mPtr?"NO":"YES";
    }
    MyPtr2(MyPtr2& other)
    {
        cout << "Transfering ownership using constructor\n";
        mPtr = other.mPtr;
        other.mPtr = nullptr;
    }
    MyPtr2& operator=(MyPtr2& other)
    {
        if(this == &other)
            return *this;
        cout << "Transfering ownership using operator=\n";
        delete mPtr;
        mPtr = other.mPtr;
        other.mPtr = nullptr;
        return *this;
    }
};
void smartPointersAndMoveSemanticsIntro()
{
    //często zdarza się zapomnieć wolnić pamięć
    //nawet jak zwalaniamy w na końcu funkcji może gdzieś nastąpić wcześniej
    //return lub throw
    //!!!dobrym rozwiązaniem jest użycie destruktorów, które wykonają się po wyjściu ze scope
    //!!!jest to sercem RAII
    {
    MyPtr<Resource> mptr1{new Resource};//alokacja pamięci, brak jawnego delete
    //nie potrzebna* (<Resource*>) jako specyfikator typu dla MyPtr ponieważ templatka ma już* (T*)
    //po wyjsciu ze scope resource będzie skasowane bo myptr jest zmienną lokalną
    (*mptr1).show();
    mptr1->show();
    (mptr1.operator->())->show();
    }
    //!!!kompozycja MyPtr jest właścicielem Resource
    //!!!taka klasa jak MyPtr jest nazywana smart_pointerem
    //composition class zarządzająca dynamicznie zaalokowanymie zmiennymi
    //gwarantuje że zmienne zalokowane dynamiczne zostaną zdealokowane po wyjściu ze scope

    //!!!destruktor obiektów lokalnych zostanie wykonany nawet jeśli nezstąpi wcześniejsze
    //niespodziewane wyjście z funkcji

    //!!!poniższa linia bez semantyki przenoszenia lub licznika referencji spowoduje critical flow
    //bo zdealokuje pamięć, która już została zdealokowana
    //MyPtr<Resource> mptr2{mptr1};
    //!!!ponieważ nie napisaliśmy operatora przypisania i konstruktora kopiującego C++ dostarczył domyślne
    //i jest robiona płytka kopia
    //Podobnie będzie jezeli przekażemy nasz obiekt mptr1 do funkcji przez wartość
    //Opcja 1: żeby rozwiązać ten problem można np usunąć operator przypisania i konstruktor kopiujący
    //ale wtedy nie będziemy mogli zwrócić MyPtr przez wartość
    //przez referencję czy pointer też bo będzie w jakiejś funkcji alokowana lokalnie i po wyjściu czyszczona więc trzeba zwrócić przez wartość
    //co spowoduje shallow copies zduplikowane pointery i crashe
    //Opcja2: zoverridować konstruktor kopiujący i operator przypisania aby robił głębokie kopie, ale kopie są drogie i czasami mogą być niemożliwe
    //ale po co robić głęboką kopię tylko żeby móc zwracać przez wartość
    //i dodatkowo przy przypisaniu raczej nie spodziewamy się, że będzie robiona kopia

    cout << "----------------\n";
    //Rozwiązanie - semantyka przenoszenia
    //SEMANTYKA PRZENOSZENIA oznacza że klasa przejmie własność obiektu zamiast robić kopię
    //główną różnicą nad "copy semantics" jest to, że nie kopiujemy resourców a przenosimy ich prawo własności
    MyPtr2<Resource2> mptr2{new Resource2};
    MyPtr2<Resource2> mptr22;
    cout << "Is mptr2 null: " << mptr2.isNull() << endl;
    cout << "Is mptr22 null: " << mptr22.isNull() << endl;
    mptr22 = mptr2;
    cout << "Is mptr2 null: " << mptr2.isNull() << endl;
    cout << "Is mptr22 null: " << mptr22.isNull() << endl;

    //!!!std::auto_ptr -> UNIKAĆ został wprowadzony w C++98 jako pierwsza próba sdandaryzacji smart pointerów działał jak klasa nasza MyPtr2
    //jednam auto_ptr i nasza klasa ma masę problemów
    //po piwersze: w związku z tym, że auto_ptr czy też MyPtr2 implementuję move semantics powoduje że przekazanei tego obiektu do funkcji spowoduje
    //przeniesienie prawa własności do parametru funkcji i zostanie on zniszczone na koniec funkcji i powyjściu z funkcji nastąpi prawdopodobnie próba dereferencji
    //po drugie: auto_ptr kasuje resource używając nietablicowego delete więc nie będzie działał dla dynamicznie zaalokowanych tablic i dodatkowo nie
    //zapobiega przekazaniu tablic więc będą memory leaks
    //po trzecie: auto_ptr nie działa dobrze z klasami standardowymi włączając większość kontenerów i algorytmów, ponieważ zakładają one, że kiedy wykonują kopię
    //jest rzeczywiście robiona kopia a nie przenoszone prawo własności
    //!!!std::auto_ptr zostało deprecated w C++11 i nie powinno być używane i prawdopodobnie będzie usuniętew Cpp17

    //!!!problem z C++11 wynikał z tego, że przed C++11 nie byłomechanizmu do odróżnienia "copy semantics" od "movesemantic"
    //można byłojedynie overridować copy semantykę move semantyką co prowadziło do wielu problemów i dziwnych zachowań.
    //nie dzło się okreslić czy res1 = res2 zmodyfikowało obiekt res2 czy nie
    //w c++11 zosta rozróżniona semantyka przenoszenia od kopiowania
    //auto_ptr został zastąpiony przez: scoped_ptr, unique_ptr, weak_ptr oraz shared_ptr
}



//!!!! kiedy przekazywana jest r-value jest wykonywana jest funkcja przujmująca
//r-value reference bo jest rozważana że ma większą zgodność niż const l-value reference
void fun1(const int& i) //void fun1(int& i) też ok //void fun1(int i) ambigous
{
    cout << "Wywolanie funkcji przyjmujacej l-value reference\n";
}
void fun1(int&& i)//bez tej funkcji zawsze wykonałavy się funkcja przyjmujaca const l-value reference
{
    cout << "Wywolanie funkcji przyjmujacej r-value reference\n";
}

void rvalueReferences()
{
    //l-values & r-values nie są właściwościami wartości a raczej właściwościami wyrażeń
    //każde wyrażenie w C++ ma 2 właściwości: typ (do sprawdzenia typu) i
    //value category (do pewnego rodzaju sprawdzenia składni np czy wynik wyrażenia może zostać przypisany do)
    //Do C++03 VALUE CATEGORY były tylko 2: l-values i r-values

    //aktualnie definicja, które wyrażenie jest r-value a które r-value jest skomplikowana

    //!!!L-value (locator value) -> można rozważyć jako funkcja lub obiekt (lub wyrażenie które ewoluuje do funkcji lub obiektu)
    //wszystkie L-values mają przypisane adres w pamięci

    //początkowo l-values były zdefiniowane jako wartości, które są zdo bycia po lewej stronie przy wyrażeniu przypisania
    //później dodane zostało słowo const i l-values zostały podzielone na nodivable l-values i non-modifable l-values które są const

    //R-values w skrócie są tym czym nie są l-values. Wczyli w szczególności: literały(5), wartości tymczasowe(x+1), anonimowe obiekty(Object(5,6))
    //R-values są ewaluowane do ich wartości, mają expression scope (umierają na końcu expression) i nie mogą być przypisane
    //to że nie mogą być przypisane ma sens bo przypisanie ma side effect obiektu
    //w związku z tym, że r-values mają expression scope jeżeli przypisalibyśmy  value do r-value r-value wyszłoby poza scope zanim mielibyśmy szansę
    //użyć przypisanej wartości do kolejnego wyrażenia lub musielibyśmy zrobić side effect co powoduje undevined behavior

    //żeby wspierać semantyke przenoszenia C++11 wprowadziło 3 nowe VALUE CATEGORY: pr-values, x-values, gl-values
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category
    //!!!!!!!!!!!!!!!!!!!https://en.cppreference.com/w/cpp/language/value_category WIECEJ INFO


    //!!!L-value REFERENCES -> przed c++11 istniała tylko "reference" teraz jest ich więcej

    //L-value reference może jedynie być initializowana jedynie modyfikowalną l-value
    //|----------------------------------------------------------------------|
    //|L-value reference               |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |Yes                    |Yes          |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |No                     |No           |
    //|----------------------------------------------------------------------|

    //L-value reference to const objects może być inicjalizowana l-value - r-value jednak wartość nie może być modyfikowana
    //|----------------------------------------------------------------------|
    //|L-value reference to const      |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |Yes                    |No           |
    //|Non Modifable l-values          |Yes                    |No           |
    //|R-values                        |Yes                    |No           |
    //|----------------------------------------------------------------------|
    //L-value references do constowych obiektów są szczególnie użyteczne po pozwalają nam przekazać dowolny argument l-value i r-value do funkcji
    //bez kopiowania argumentu

    //W C++11 został dodany nowy typ referencji -> R-value reference
    //R-value reference jest zaprojektowana aby być inicjalizowana JEDYNIE przez R-Value
    int x = 5;
    int& lref = x;//l-value reference initialized with l-value
    //int& lref2 = 5;//cannot bind non-const lvalue reference to rvalue
    const int& lref3 = 5;//l-value reference to const initizlized with r-value //przedłuża czas życia r-value
    int&& rref = 5;//r-value reference initialized with r-value
    //int&& rref2 = x;//cannot bind rvalue reference to lvalue
    int&& ref2 = std::move(x);
    int&& ref22 = static_cast<int&&>(int(5));//chyba równoważne z powyższym move
    cout << ref22 << endl;
    nicNieRob(&lref);
    nicNieRob((void*)&lref3);
    nicNieRob(&rref);
    nicNieRob(&ref2);

    //Rvalue references cannot be initialized witch L-values
    //|----------------------------------------------------------------------|
    //|R-value reference               |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |No                     |No           |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |Yes                    |Yes          |
    //|----------------------------------------------------------------------|
    //|----------------------------------------------------------------------|
    //|R-value reference to const      |Can be initialize with |Can modify   |
    //|----------------------------------------------------------------------|
    //|Modifable l-values              |No                     |No           |
    //|Non Modifable l-values          |No                     |No           |
    //|R-values                        |Yes                    |No           |
    //|----------------------------------------------------------------------|

    //R-value references mają dwie użyteczne właściwości:
    //wydłuzają żywotność obiektu dla którego zostały zainicjalizowane do czasu życia odwołania r-value (tak jak l-value do const wartości)
    //!!!!!!non-const r-value references allows to modify the r-value;
    int&& rref3 = 7;
    rref3 = 8;

    string&& str = string("ala ma kota");//r-value reference to temporary object
    //zniszczony zostanie jak referencja str będzie niszczona czyli po wyjściu z bloku

    int&& rref4 = 4;
    nicNieRob(&rref4);
    //kiedy inicjalizujemy r-velue literałem  obiekt tymczasowy jest tworzony z literału więc referencja wskazuje na tymczasowy obiekt

    //!!!!!!!R-value referencje nie są często stosowane w taki sposób jak były stosowane powyżej

    //!!!R-value references są często używane jako parametry funkcji, często stosuje się przeciążenia funkcji jezeli chceemy inne zachowanie dla
    //r-value a inne dla l-value

    int x3 = 55;
    fun1(x3);
    fun1(55);
    fun1(move(x3));

    //!!!nie powinno się prawie nigdy zwracać l-value reference ani r-value reference bo w większości przypadków siończy sie z wiszącą referencją kiedy obiekt
    //wyjdzie poza scope
}





void moveConstructorAndAssigment()
{
    //!!!konstruktor kopiujący jest używany aby zainicjalizować klasę robiąc kopię obiektu tej samej klasy
    //Copy assigment jest używany aby skopiować klasę do innej istniejącej klasy
    //C++ dostarcza domyślnie copy constructor i copy assigment jezeli nie podamy wlasnego (shallow copy i problemy)

}
