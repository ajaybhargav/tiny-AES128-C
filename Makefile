CC           = gcc

NOVAPROVA_CFLAGS= $(shell pkg-config --cflags novaprova 2>/dev/null)
NOVAPROVA_LIBS= $(shell pkg-config --libs novaprova 2>/dev/null)

CFLAGS       = -Iinc/ -Wall -g $(NOVAPROVA_CFLAGS)
OBJCOPY      = objcopy
OUTDIR       = build
SRCDIR	     = src

# splint static check
SPLINT       = splint test.c aes.c +charindex -unrecog

.SILENT:
.PHONY:  lint clean

$(OUTDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	echo "Compiling $<"
	$(CC) -o $@ -c $< $(CFLAGS)

_CODE_OBJS= aes.o pkcs7_padding.o
CODE_OBJS=$(patsubst %,$(OUTDIR)/%,$(_CODE_OBJS))

ifneq ($(strip $(NOVAPROVA_CFLAGS)), )
_TEST_OBJS= test/aes.o test/pkcs7_padding.o
else
_TEST_OBJS= test/test.o
endif
TEST_OBJS=$(patsubst %,$(OUTDIR)/%,$(_TEST_OBJS))

testrunner: $(TEST_OBJS) $(CODE_OBJS)
	echo "Linking $@"
	$(LINK.c) -o $(OUTDIR)/$@ $(TEST_OBJS) $(CODE_OBJS) $(NOVAPROVA_LIBS)

clean:
	rm -rf $(OUTDIR)

lint:
	$(call SPLINT)

test:  testrunner
	./$(OUTDIR)/testrunner
