CMD = cc -Wall -Wextra -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wvla -Wfloat-equal
SRC = ./src/
BIN = ./bin/
INC = ./include/
CMD += -I $(INC)
TST = ./test/
TSTSRC = ./test/src/
TSTBIN = ./test/bin/
TSTINC = ./test/include
LNK = -lcheck -lm -lpthread -lrt -lsubunit

all: $(BIN)libdtype.a

################
# main targets #
################
$(BIN)list.o: $(SRC)list.c $(INC)list.h
	$(CMD) -c $< -o $@

################
# test targets #
################
$(TST)check_check: $(TSTBIN)check_check.o $(BIN)libdtype.a
	$(CMD) $^ $(LNK) -o $@
$(TSTBIN)check_check.o: $(TSTSRC)check_check.c
	$(CMD) -c $^ -o $@
$(TSTBIN)test_list.o: $(TSTSRC)test_list.c
	$(CMD) -c $^ -o $@ 

####################
# libarary targets #
####################
$(BIN)libdtype.a: $(BIN)libdtype.a($(BIN)list.o);
clean:
	find . -type f -iname *.o -exec rm -rf {} \;
	find . -type f -iname *.a -exec rm -rf {} \;
	find . -type f -iname check_check -exec rm -rf {} \;
debug: CMD += -g
debug: clean all
profile: CMD += -pg
profile: debug
check: CMD += -I $(TSTINC)
check: debug
check: $(TST)check_check
valgrind: check 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./test/check_check
