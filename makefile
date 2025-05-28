PROGRAM = test
INCLUDEDIRS = \
	-I/usr/local/ssl/include


LIBDIRS = \
	-L/usr/local/ssl/lib


LIBS = -lssl -lcrypto

CXXSOURCES = test.cpp block.cpp blockchain.cpp
CXXOBJECTS = $(CXXSOURCES:.cpp=.o)
CXXFLAGS = -DESRI_UNIX $(INCLUDEDIRS)
CXX = g++

LDFLAGS = $(LIBDIRS) $(LIBS)

all: $(PROGRAM)

$(PROGRAM): $(CXXOBJECTS)
	$(CXX) -o $@ $(CXXOBJECTS) $(LDFLAGS)

test.o: test.cpp hash.h
	$(CXX) $(CXXFLAGS) -c -o test.o test.cpp
block.o: block.cpp block.h
	$(CXX) $(CXXFLAGS) -c -o block.o block.cpp
blockchain.o: blockchain.cpp blockchain.h
	$(CXX) $(CXXFLAGS) -c -o blockchain.o blockchain.cpp

clean:
	$(RM) -f $(CXXOBJECTS) $(PROGRAM)

run:
	./$(PROGRAM)

