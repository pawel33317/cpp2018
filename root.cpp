#include <iostream>
#include "chapterS.hpp"
using namespace std;

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
// #include "chapter13.hpp"
// #include "chapter14.hpp"
// #include "chapter15.hpp"
// #include "chapter16.hpp"
// #include "chapter17.hpp"
// #include "chapter18.hpp"
// #include "appendixA.hpp"
// #include "appendixB.hpp"
// #include "appendixC.hpp"
#include "boost/filesystem/path.hpp"
#include <limits>
void myStrCpy(const char* src, char* dst)
{
    while((*dst++ = *src++));
}
int main(int argc, char* argv[])
{
    chapter1run();
    chapter2run();
    chapter3run();
    chapter4run();
    chapter5run();
    chapter6run();
    chapter7run(argc, argv);
    chapter8run();
    chapter9run();
    chapter10run();
    chapter11run();
    chapter12run();

    chapter15run();
    //15
    //AppendixB
    //AppendixA
    //16
    //14
    //13
    //18
    //17
    //AppendixC
    printf("\n");

    //int( *l)(int) = [](int i) -> int {return i*2;};
    //cout << l(12) << endl;
}


//fabryka, dekorator, łańcuch zdarzeń, maszyna stanów, singleton, fasada, kompozyt
//obserwator https://pl.wikipedia.org/wiki/Wzorzec_projektowy_(informatyka)
//tworzenie własnej biblioteki

//serialization !!!!

// alignas **
// alignof **
// asm
// compl
// decltype	
// dynamic_cast *
// export *
// extern "C" 
// mutable *
// noexcept **
// register
// template
// thread_local **
// throw 
// try
// typedef	
// typeid *
// typename *
// union
// virtual
// volatile

// override (C++11)
// final (C++11)
// transaction_safe (PT TS)
// transaction_safe_dynamic (PT TS)
//_pragma
// auto_ptr
//std::cref
//std::reference_wrapper
//std::ref
//https://gcc.gnu.org/projects/cxx-status.html#cxx11
//gdb lub inny
//std move forward function 
//http://en.cppreference.com/w/cpp/header
//u2
//threading
//sockets
//random liczby pseudolosowe
//regex
//operacje na plikach c++11, operator >>, openy
//lambdy
//wskaźniki na funkcje
//time
//drzewa binarne
//listy dwukierunkowe wiązane
//gui
//unicode characters
//opengl
//variadic templates
//stl
//std::forward
