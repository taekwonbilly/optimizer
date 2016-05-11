.DEFAULT_GOAL := all

FLAGS_LIB = ${LDFLAGS} #-lmpfr -lgmp
FLAGS_INC = ${CPPFLAGS} ${CFLAGS} -I./include
#FLAGS = -lmpfr -lgmp ${CPPFLAGS} ${CFLAGS} ${LDFLAGS} -fexceptions

ifeq ($(CXX),)
	#CC = g++-5 -g -ggdb -O0 -Wuninitialized -fno-omit-frame-pointer
	CC = g++-5 -g -ggdb -O0 -Wuninitialized -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
	#CC = clang++-3.6 -g -ggdb -O0 -Wuninitialized -fsanitize=address -fno-omit-frame-pointer
	#CC = clang++-3.6 -g -ggdb -O0 -fno-omit-frame-pointer
	#-Wuninitialized -Wall
else
	CC = $(CXX)
endif

reverse = $(if $(1),$(call reverse,$(wordlist 2,$(words $(1)),$(1)))) $(firstword $(1))

srcs =  ./src/Main.cpp\


objs = $(patsubst ./%.cpp, bin/%.o, $(srcs))

# pull in dependency info for *existing* .o files
-include $(bin:.o=.d)

all: bin/optimizer

bin/optimizer: $(objs)
	@echo "Linking"
	$(CC) $(objs) $(FLAGS_LIB) -o ./bin/optimizer

bin/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CC) -c $(patsubst bin/%.o, ./%.cpp, $@) $(FLAGS_INC) -std=c++1y -o $@
	@$(CC) -MM $(patsubst bin/%.o, ./%.cpp, $@) $(FLAGS_INC) -std=c++1y > $(patsubst %.o, %.d, $@)
	@mv -f $(patsubst %.o, %.d, $@) $(patsubst %.o, %.d.tmp, $@)
	@sed -e 's|.*:|$@:|' < $(patsubst %.o, %.d.tmp, $@) > $(patsubst %.o, %.d, $@)
	@sed -e 's/.*://' -e 's/\\@@//' < $(patsubst %.o, %.d.tmp,$@) | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(patsubst %.o, %.d.tmp,$@)
	@rm -f $(pathsubst %.o, %.d.tmp, $@)

clean:
	rm -rf bin

run: all
	./bin/optimizer
