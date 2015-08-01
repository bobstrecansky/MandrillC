CC=gcc
CFLAGS = -g -Wall -lcurl
OBJS = mandrill.c
mandrillC: mandrill.c
	$(CC)  -o $@ ${OBJS} ${CFLAGS}

clean:
	rm -f *.o a.out mandrillC

cleanRC:
	rm -f *.o mandrillrc a.out mandrillC
