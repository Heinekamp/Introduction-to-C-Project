#Adapted from Makefile for the StupidCalculator by Armin Biere
# .SUFFIXES:

# TEST=checkerTest
# MAIN=main
# CHECKER_MAIN=checkerMain

# SRC=$(filter-out $(TEST).cpp $(MAIN).cpp $(CHECKER_MAIN).cpp,$(wildcard *.cpp))
# OBJ=$(SRC:.cpp=.o)
# CHECKER_MAIN_OBJ=$(CHECKER_MAIN).o

# HEADERS=$(wildcard *.hpp)

# %.o: %.cpp $(HEADERS)
# 	$(CXX) -c -g $<

# compile: $(MAIN) $(CHECKER_MAIN)
# format:
# 	clang-format -i *.[ch]pp
# clean:
# 	rm -f *.o main checkerTest checkerMain
# test: $(TEST)
# 	./$(TEST)

# $(TEST): $(TEST).o $(OBJ)
# 	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

# $(MAIN): $(MAIN).o $(OBJ)
# 	$(CXX) -o $@ $^

# $(CHECKER_MAIN): $(CHECKER_MAIN_OBJ) $(OBJ)
# 	$(CXX) -o $@ $^

# $(TEST).o: $(TEST).cpp $(HEADERS)
# 	$(CXX) -c -g $< -o $@

# $(CHECKER_MAIN_OBJ): $(CHECKER_MAIN).cpp $(HEADERS)
# 	$(CXX) -c -g $< -o $@
	
# .PHONY: compile clean format test

#Adapted from Makefile for the StupidCalculator by Armin Biere
.SUFFIXES:

SOLVER_TEST=solverTest
TEST=checkerTest
MAIN=parsePrintMain
CHECKER_MAIN=checkerMain
SOLVER_MAIN=solverMain

SRC=$(filter-out $(SOLVER_TEST).cpp $(TEST).cpp $(MAIN).cpp $(CHECKER_MAIN).cpp $(SOLVER_MAIN).cpp,$(wildcard *.cpp))
OBJ=$(SRC:.cpp=.o)
CHECKER_MAIN_OBJ=$(CHECKER_MAIN).o
SOLVER_MAIN_OBJ=$(SOLVER_MAIN).o

HEADERS=$(wildcard *.hpp)

%.o: %.cpp $(HEADERS)
	$(CXX) -c -g $<

compile: $(MAIN) $(CHECKER_MAIN) $(SOLVER_MAIN)
format:
	clang-format -i *.[ch]pp
clean:
	rm -f *.o main checkerTest checkerMain solverTest parsePrintMain solverMain
test: $(TEST) $(SOLVER_TEST)
	./$(TEST)
	./$(SOLVER_TEST)

$(TEST): $(TEST).o $(OBJ)
	$(CXX) -o $@ $^ -lgtest -lgtest_main -lpthread

$(SOLVER_TEST): $(SOLVER_TEST).o $(OBJ)
	$(CXX) -o $@ $^

$(MAIN): $(MAIN).o $(OBJ)
	$(CXX) -o $@ $^

$(CHECKER_MAIN): $(CHECKER_MAIN_OBJ) $(OBJ)
	$(CXX) -o $@ $^

$(SOLVER_MAIN): $(SOLVER_MAIN_OBJ) $(OBJ)
	$(CXX) -o $@ $^

$(TEST).o: $(TEST).cpp $(HEADERS)
	$(CXX) -c -g $< -o $@

$(SOLVER_TEST).o: $(SOLVER_TEST).cpp $(HEADERS)
	$(CXX) -c -g $< -o $@

$(CHECKER_MAIN_OBJ): $(CHECKER_MAIN).cpp $(HEADERS)
	$(CXX) -c -g $< -o $@

$(SOLVER_MAIN_OBJ): $(SOLVER_MAIN).cpp $(HEADERS)
	$(CXX) -c -g $< -o $@
	
.PHONY: compile clean format test