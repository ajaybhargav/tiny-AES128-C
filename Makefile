CC           = gcc

NOVAPROVA_CFLAGS= $(shell pkg-config --cflags novaprova)
NOVAPROVA_LIBS= $(shell pkg-config --libs novaprova)

CFLAGS       = -Wall -g $(NOVAPROVA_CFLAGS)
OBJCOPY      = objcopy

# splint static check
SPLINT       = splint test.c aes.c +charindex -unrecog

.SILENT:
.PHONY:  lint clean

CODE_SOURCE= aes.c
CODE_OBJS= $(CODE_SOURCE:.c=.o)

TEST_SOURCE= test/aes.c
TEST_OBJS= $(TEST_SOURCE:.c=.o)

testrunner:  $(TEST_OBJS) $(CODE_OBJS)
	$(LINK.c) -o $@ $(TEST_OBJS) $(CODE_OBJS) $(NOVAPROVA_LIBS)

clean:
	rm testrunner $(CODE_OBJS) $(TEST_OBJS)

lint:
	$(call SPLINT)

test:  testrunner
	./testrunner
	
