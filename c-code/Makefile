CC=g++
CFLAGS="-std=c++11"
SOURCES=getFreqRep_data.c getFreqRep_initialize.c getFreqRep_terminate.c getFreqRep.c fft.c FFTImplementationCallback.c getFreqRep_emxutil.c getFreqRep_emxAPI.c WebAssembly.cpp
DEPS=
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=fft

all:$(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE):$(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) -c $*.c

clean:
	$(RM) *.o *$(EXECUTABLE)
