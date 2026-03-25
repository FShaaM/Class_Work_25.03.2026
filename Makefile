CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14

UNIT_TESTS = pe_vector_tests

$(UNIT_TESTS): main.o
	$(CXX) -o $@ $^

clean:
	$(RM) $(UNIT_TESTS) main.o
