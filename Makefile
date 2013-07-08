
CFLAGS += -Wall -std=c99

# TODO: main to test on dict
mainOBJ=hash.o main.o
# pFast [-8|-16] string

testOBJ=hash.o test.o

test: $(testOBJ)
	$(CC) $(CFLAGS) $^ -o $@

#pFast: $(mainOBJ)

clean:
	rm -f test $(testOBJ) $(mainOBJ)
