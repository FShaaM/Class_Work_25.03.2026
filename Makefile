CXXFLAGS += -Wall -Wextra -Weffc++ -std=c++14 -MMD

UNIT_TESTS = pe_vector_tests
-include main.d
DEPS = main.d

$(UNIT_TESTS): main.o
	$(CXX) -o $@ $^

clean:
	-$(RM) $(UNIT_TESTS) main.o
	@$(RM) $(DEPS)
	
