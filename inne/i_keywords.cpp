#include <iostream>
#include <memory>
#include <cassert>
#include "chapterS.hpp"
using namespace std;

class SizeClass { double d; int i;};
class alignas(128) SizeClass2 { double d; int i;};
class alignas(1)   SizeClass3 { double d; int i;};//pominiete bo zbyt male
class alignas(32)   SizeClass4 { int i; char s; };
class alignas(8)   SizeClass5 { SizeClass2 ss; int i; char s; };
void i_keywords()
{
    cout << "-----i_keywords-----\n";

    //alignas określa alligment
    //można dodać deklaracji zmiennej, nie-bitowego członka klasy
    //do deklaracji/definicji klasy/struktury/unii/enuma func param, exceptiona

    //!!!jak alignas jest mniejsze niż rzeczywiste będzie pominięty
    cout << "sizeof(SizeClass { double d; int i;};) = " <<
        sizeof(SizeClass) << endl;

    cout << "sizeof(alignas(128) SizeClass2 { double d; int i;};) = " <<
        sizeof(SizeClass2) << endl;

    cout << "alignas(8) SizeClass3 { double d; int i;}; = " <<
        sizeof(SizeClass3) << endl;

    cout << "alignas(32) SizeClass4 { int i; char s;}; = " <<
        sizeof(SizeClass4) << endl;

    cout << "alignas(8) SizeClass5 { int i; char s; SizeClass2 s;}; = " <<
        sizeof(SizeClass5) << endl;

    //alignof zwraca aliement w bajtach
    cout << "alignof(SizeClass) = " << alignof(SizeClass) << endl;
    cout << "alignof(SizeClass2) = " << alignof(SizeClass2) << endl;
    cout << "alignof(SizeClass3) = " << alignof(SizeClass3) << endl;
    cout << "alignof(SizeClass4) = " << alignof(SizeClass4) << endl;
    cout << "alignof(SizeClass5) = " << alignof(SizeClass5) << endl;

///////////////////////////////////
//////////1 SŁOWA KLUCZOWE
///////////////////////////////////
// asm
// compl
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
}
