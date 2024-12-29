CXX = g++
FLAGS = -Wall -Wextra -O3 -std=c++17 -fopenmp -mcmodel=large

APP_SOURCES = app.cpp
TBC_SOURCES = TBC.cpp
APP_OBJECTS = $(APP_SOURCES:.cpp=.o)
TBC_OBJECTS = $(TBC_SOURCES:.cpp=.o)
APP_EXE = app
TBC_EXE = tbc

all: $(APP_EXE) $(TBC_EXE)

$(APP_EXE): $(APP_OBJECTS)
	$(CXX) $(APP_OBJECTS) -o $(APP_EXE) $(FLAGS)  

$(TBC_EXE): $(TBC_OBJECTS)
	$(CXX) $(TBC_OBJECTS) -o $(TBC_EXE) $(FLAGS)  

-include $(APP_OBJECTS:.o=.d) $(TBC_OBJECTS:.o=.d)

%.o: %.cpp
	$(CXX) -c $(FLAGS) $< -o $@
	$(CXX) -MM $(FLAGS) $< > $*.d; \
	sed -i 's|\($*\)\.o:|\1.o $*.d:|' $*.d

# Clean only object files
.PHONY: cleanobj
cleanobj:
	rm -f $(APP_OBJECTS) $(TBC_OBJECTS)

# Clean all generated files
.PHONY: clean
clean:
	rm -f $(APP_OBJECTS) $(TBC_OBJECTS) *.d $(APP_EXE) $(TBC_EXE)
