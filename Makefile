CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14

pe_vector_tests: main.o
	g++ -o $@ $^
