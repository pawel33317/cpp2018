#CEL: SKLADNIKI
#	KOMENDA
#< - aktualnie przetwarzany plik z listy składników (patrz przykład)
#@ - nazwa pliku docelowego
#^ - składniki
CXX=g++
CXXLAGS=-std=c++14 -Wall -O0 -lstdc++
LFLAGS=-std=c++14 -Wall -O0 -lstdc++  #opcje linkera

#CXXLAGS=-std=c++17 -Wall -O0 -lstdc++
#LFLAGS=-std=c++17 -Wall -O0 -lstdc++ #opcje linkera
LIBS = -l boost_system -l boost_filesystem -lm -lrt -lpthread

SRCS := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
TARGET := app.bin

all: $(TARGET)
	./app.bin

#linkowanie
$(TARGET): $(OBJS)
	$(CXX) $(LFLAGS) $^ $(LIBS) -o $@ 

#kompilacja
%.o: %.cpp
	$(CXX) $(CXXLAGS) -c $<

clean:
	rm -rf $(TARGET) *.o
.PHONY: clean


