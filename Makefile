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
SRCS_WZORCE := $(wildcard wzorce/*.cpp)
SRCS_INNE := $(wildcard inne/*.cpp)
SRCS_TUTORIAL := $(wildcard tutorial/*.cpp)
#OBJS := $(patsubst %.cpp,%.o,$(SRCS))
OBJS_RELEASE := $(patsubst %.cpp,$(RELEASE_DIR)/%.o,$(SRCS))
OBJS_RELEASE += $(patsubst wzorce/%.cpp,$(RELEASE_DIR)/wzorce/%.o,$(SRCS_WZORCE))
OBJS_RELEASE += $(patsubst inne/%.cpp,$(RELEASE_DIR)/inne/%.o,$(SRCS_INNE))
OBJS_RELEASE += $(patsubst tutorial/%.cpp,$(RELEASE_DIR)/tutorial/%.o,$(SRCS_TUTORIAL))


TARGET := app.bin

all: $(TARGET)
	./$(RELEASE_DIR)/app.bin

#linkowanie
$(TARGET): $(OBJS_RELEASE)
	$(CXX) $(LFLAGS) $^ $(LIBS) -o $(RELEASE_DIR)/$@

#kompilacja
$(RELEASE_DIR)/%.o: %.cpp
	@mkdir -p $(RELEASE_DIR)
	$(CXX) $(CXXLAGS) -c $< -o $@ -I./headers/

$(RELEASE_DIR)/wzorce/%.o: wzorce/%.cpp
	@mkdir -p $(RELEASE_DIR)/wzorce
	$(CXX) $(CXXLAGS) -c $< -o $@ -I./headers/

$(RELEASE_DIR)/inne/%.o: inne/%.cpp
	@mkdir -p $(RELEASE_DIR)/inne
	$(CXX) $(CXXLAGS) -c $< -o $@ -I./headers/

$(RELEASE_DIR)/tutorial/%.o: tutorial/%.cpp
	@mkdir -p $(RELEASE_DIR)/tutorial
	$(CXX) $(CXXLAGS) -c $< -o $@ -I./headers/

clean:
	rm -rf $(TARGET) *.o $(RELEASE_DIR)
.PHONY: clean