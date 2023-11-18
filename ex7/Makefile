# Copyright 2023 <Wei-Mei(Katrina) Hsiung>
# Email: whsiung@uw.edu

# define the commands we will use for compilation and library building
CXX = g++

# define useful flags to cc/ld/etc.
CPPFLAGS = -Wall -g -std=c++17

# define common dependencies
OBJS = Vector.o ex7.o
HEADERS = Vector.h
EXE  = ex7

# ouput & execution files
$(EXE): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(EXE) $(OBJS)

# header files
%.o: %.cc $(HEADERS)
	$(CXX) $(CPPFLAGS) -c $<

clean:
	rm -rf $(EXE) *.o *~