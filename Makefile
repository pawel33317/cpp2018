#CEL: SKLADNIKI
#	KOMENDA
#< - aktualnie przetwarzany plik z listy składników (patrz przykład)
#@ - nazwa pliku docelowego
#^ - składniki
CXX=g++
CXXLAGS=-std=c++17 -Wall -O0 -lstdc++
LFLAGS=-std=c++17 -Wall -O0 -lstdc++  #opcje linkera
RELEASE_DIR=release

#CXXLAGS=-std=c++17 -Wall -O0 -lstdc++
#LFLAGS=-std=c++17 -Wall -O0 -lstdc++ #opcje linkera
LIBS = -l boost_system -l boost_filesystem -lm -lrt -lpthread

SRCS := $(wildcard *.cpp)
WZORCE_SRCS := $(wildcard wzorce/*.cpp)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS_RELEASE := $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(SRCS))
OBJS_RELEASE += $(patsubst wzorce/%.cpp,$(RELEASE_DIR)/%.o,$(WZORCE_SRCS))


TARGET := app.bin

all: $(TARGET)
	./$(RELEASE_DIR)/app.bin

#linkowanie
$(TARGET): $(OBJS_RELEASE)
	$(CXX) $(LFLAGS) $^ $(LIBS) -o $(RELEASE_DIR)/$@

#kompilacja
$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXLAGS) -c $< -o $@

$(RELEASE_DIR)/%.o: wzorce/%.cpp
	$(CXX) $(CXXLAGS) -c $< -o $@ -I.


clean:
	rm -rf $(TARGET) *.o $(RELEASE_DIR)
.PHONY: clean