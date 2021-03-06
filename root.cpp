#include <iostream>
#include "all.hpp"
#include "boost/filesystem/path.hpp"
using namespace std;

//variadic templates
//#include "chapter14.hpp" exceptions
//typedef i fun ptr, odbieranie tablicy przez referencję
//https://en.cppreference.com/w/cpp/language/noexcept_spec
    //https://en.cppreference.com/w/cpp/memory/new/nothrow
    //14.callallandspecifiers
//wzorce
    //łańcuch zdarzeń
    //RAII
    //mediator
    //https://infotraining.bitbucket.io/cpp-dp/
    //https://pl.wikipedia.org/wiki/Wzorzec_projektowy_(informatyka)
//#include "appendixA.hpp" static vs dynamic libraries
//#include "chapter18.hpp" Input and output + operacje na plikach c++11
//#include "chapter17.hpp" std::string
//#include "appendixC.hpp" end
//tworzenie własnej biblioteki
//serializacja
//trudniejsze wskaźniki na funkcje + bind
//
int main(int argc, char* argv[])
{
    i_main_call();
    w_main_call();
    t_main_call(argc, argv);
    std::cout << std::endl;
}
//threading, transaction_safe_dynamic, transaction_safe, mutex, conditional_variable
//socket programming sys/socket
//regex expressions
//filesystem library
//C++11/14/17 new feature - unicode characters
//Najważniejsze funkcje - std::time
//functional - std::cref, std::reference_wrapper, std::ref, std::forward
//STL LIB -> http://en.cppreference.com/w/cpp/header WAŻNIEJSZE TYLKO

//GUI - Qt, wxWidgets, GTK+, other
//Setup środowiska do OpenGl (jakiś rozsądny połączony z gitem) + prosta aplikacja
//Krótki opis i test działania - gdb lub inny debugger 
//Plik o przeliczaniu liczb na system U2
//Zaimplementować i opisać binarne drzewo poszukiwań (set) i_drzewo_binarne.cpp
//Zaimplementować i opisać listy https://pl.wikipedia.org/wiki/Lista
//Zaimplementować i opisać set - prawdopodobnie jest to binarne drzewo poszukiwań
//STL LIB -> http://en.cppreference.com/w/cpp/header TYLKO RESZTA
//WSZYSTKO https://en.cppreference.com/w/cpp
//CPP17, 20, 14 features https://gcc.gnu.org/projects/cxx-status.html#cxx11
