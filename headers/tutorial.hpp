#include <cstdlib>

void t_main_call(int argc, char* argv[]);

void t_chapter1run();
void t_chapter2run();
void t_chapter3run();
void t_chapter4run();
void t_chapter5run();
void t_chapter6run();
void t_chapter7run(int argc, char** argv);
void t_chapter8run();
void t_chapter9run();
void t_chapter10run();
void t_chapter11run();
void t_chapter12run();
void t_chapter15run();
void t_chapter16run();
void t_appendixB();
void t_chapter13run();

void t_nicNieRob(void*);
inline int t_getNum() {return 5;}


//0 intro, kompilacja
//1 basics
//2 variables, fundamental data types
//3 operatory
//4 bloki, scope, linkagestatic, namespaces, rzutowania, 
            //enumy, typedefy, struct i auto
//5 control flow, if, switch, goto, while,break, random
//6 arrays, sorcint, c-strings, pointers, dynamic memory, 
            //referebces, foreach, void ptr, std::array, std::vector
//7 parametry/argumenty funkcji ref ptr val, inline
            //fun overloading, domyślne parametry, wskaźniki na funkcje
            //stos i sterta, vector advanced, rekursja, handling errors
            //assert, static_assert, commandline args, ellipsis
//8 OOP podstawy, klasy i membery, public/private dostęp i enkapsulacja
            //konstruktory, inicjalizacja w konstruktorze, non-static inicjalizacja
            //nakładanie się konstruktorów, destruktory, THIS, klasy i headery
            //obiekty i metody i pola, static member variables and functions
            //friend functions, anonimowe obiekty, typy zagnieżdżone
            // o kodzie
//9 przeciazenia operatorow: aryrmetyczne, używając friend funkcji,
            //uzywajac normalnych funkcji, I/O, używając metod, unarne -+!m
            //==, ++ --, [], (), operator typecast, copy constructor,
            //copy initialization, konwertowanie konstruktorów jawnych i delete
            // = operator, shallow - deep copy
//10 relacje obiektów: kompozycja, agregacja, asocjacja, zależności,
            //klasy kontenerowe, initializer_list
//11 podstawy dziedziczenia, kolejność dziedziczenia, konstruktory i inicjalizacja
            //specyfikatory dostępu, nowe moetody w klasie dziedziczącej,
            //ukrywanie odziedziczonych funkcjonalności, wielodziedziczenie
//12 pointery i referencje do klasy bazowej
            //funkcje virtual i polimorfizm
            //overrride, final, covriant return type
            //virtual destruktory assigmenty i virtualization overriding
            //early binding and late binding
            //virtual table
            //pure virtual functions, abstract clases, interfaces
            //virtual base classes
            //object slicing
            //dynamic casting
            //operator << and printing inherited classes
//15 semantyka przenoszenia i smart pointery
            //r-values, move semantics, move constructors and assigments
            //std::move, unique_ptr, shared_ptr, weak_ptr
            //circural dependency issue
//appendixB //nowe w C++11
            //C++14, C++17
//13 function templates, function templateinstances, template classes
            //template non-type parameters, function template specialization
            //class template specialization
            //partial template specialization
            //partial template specialization for pointers
