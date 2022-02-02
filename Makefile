TARGET?=$(shell $(CXX) -dumpmachine)

BIN=mathlib
CXXFLAGS=-Wall -Wno-unused-variable -O0 -g
CFLAGS=$(CXXFLAGS)
CPPFLAGS=-Iexternals/include -MMD
LDFLAGS=-Lexternals/libs-$(TARGET)

ifeq ($(TARGET),x86_64-pc-cygwin)
LDLIBS=
else ifeq ($(TARGET),x86_64-pc-linux-gnu)
LDLIBS=
else ifeq ($(TARGET),x86_64-linux-gnu)
LDLIBS=
endif

OBJS=main.o mathlib.o
DEPS=$(OBJS:.o=.d)

.PHONY: all clean

all: $(BIN)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@

clean:
	rm -f $(BIN) $(OBJS) $(DEPS)
