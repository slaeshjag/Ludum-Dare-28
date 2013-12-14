include $(TOPDIR)/config.mk

OUTBIN		=	../bin/ld28.elf

DEPENDS		=

STRIP		=	strip
LDFLAGS		+=	-ldarnit_s -lbz2 -lmodplug -lm -lSDL -lGL
SRCFILES	=	$(wildcard *.c)
OBJFILES	=	$(SRCFILES:.c=.o)
.PHONY: all clean

all: $(OBJFILES) $(DEPENDS)
	@echo " [ LD ] $(OUTBIN)"
	@$(CC) $(CFLAGS) -o $(OUTBIN) $(OBJFILES) $(LDFLAGS)
#	@$(STRIP) $(OUTBIN)
	@echo "Done."
	@echo
	
clean:
	@echo
	@echo " [ RM ] $(OBJFILES)"
	@$(RM) $(OBJFILES)
	@echo "Done."
	@echo 

%.o: %.c %.h
	@echo " [ CC ] src/$<"
	@$(CC) $(CFLAGS) -c -o $@ $<
	
