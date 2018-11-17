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


// słowa kluczowe poniżej
// wektor alokator, iterator
// variadic templates
// #include "chapter14.hpp"
// implementacja mapy, set (drzewa binarne), iteratora, listy dwukierunkowe wiązane
// wzorce

// #include "appendixA.hpp"
// #include "chapter18.hpp"
// #include "chapter17.hpp"
// #include "appendixC.hpp"
// tworzenie własnej biblioteki
// operacje na plikach c++11, operator >>, openy
// serializacja
// std::cref, std::reference_wrapper, std::ref
// std::forward
// wskaźniki na funkcje
#include "boost/filesystem/path.hpp"

int main(int argc, char* argv[])
{
    /*chapter1run();
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
    chapter16run();
    appendixB();
    chapter13run();*/

    w_fabryka();
    w_singleton();

    i_iterator();
    printf("\n");
}


///////////////////////////////////
//////////1 SŁOWA KLUCZOWE
///////////////////////////////////
// alignas **
// alignof **
// asm
// compl
// decltype	
// export *
// extern "C" 
// mutable *
// noexcept **
// register
// thread_local **
// typedef	
// typeid *
// typename *
// union
// volatile
// transaction_safe_dynamic
// https://pl.cppreference.com/w/cpp/keyword

///////////////////////////////////
//////////2 WZORCE
///////////////////////////////////
//fabryka
//dekorator
//łańcuch zdarzeń
//maszyna stanów
//singleton
//fasada
//kompozyt
//RAII
//obserwator
//https://infotraining.bitbucket.io/cpp-dp/
//https://pl.wikipedia.org/wiki/Wzorzec_projektowy_(informatyka)


//https://gcc.gnu.org/projects/cxx-status.html#cxx11

//gdb lub inny

//STL LIB -> http://en.cppreference.com/w/cpp/header

//u2

//threading

//sockets

//regex

//time

//gui

//unicode characters

//opengl

//!!!WSZYSTKO https://en.cppreference.com/w/cpp