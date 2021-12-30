#Defining constants
CXX = g++
CXXLINK = $(CXX)
CXXFLAGS = -g -Wall -Wextra -std=c++11
OBJS = ip.o port.o field.o string.o
RM =rm -f *.o firewall.exe libfirewall.so

#Dependencies of the .exe file
firewall.exe: main.o libfirewall.so
	$(CXXLINK) main.o -o firewall.exe -lfirewall -linput -L.

#Creating the library
libfirewall.so: $(OBJS)
	$(CXXLINK) -shared $(OBJS) -o libfirewall.so

#Dependencies of the .o files
main.o: main.cpp ip.h port.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp

ip.o: ip.cpp ip.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp

field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp

#Cleaning every file we created
clean:
	$(RM)