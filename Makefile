PREF_SRC = ./sourсes/
PREF_OBJ = ./objects/

SRCS    := $(wildcard $(PREF_SRC)*.cpp)
OBJS    := $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRCS))

TARGET := SecondLab

all: $(TARGET)

$(TARGET) : $(OBJS)
	g++ $(OBJS) -o $(TARGET)

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp
	g++ -c $< -o $@



run : all
	./$(TARGET)



report :
	cd doc && \
	rm -rf latex html && \
	doxygen Doxyfile && \
	cd latex && \
	make

graphs :
	python3 $(HOME)/Desktop/hse/mp/data-search-algorithms/utils/genGraphs.py



clean-sorted-data :
	rm -f $(HOME)/Desktop/hse/mp/data-search-algorithms/out/*.txt

clean-info :
	rm -f $(HOME)/Desktop/hse/mp/data-search-algorithms/info_time.txt

clean :
	rm -f $(TARGET) $(PREF_OBJ)*.o

clean-all : clean-sorted-data clean-info clean