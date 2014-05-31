
# Makefile du projet Maya.
# auteur : Jude Seide
# -----------------------------

# version construction avec tests unitaires :

#FLAGS=-D TESTS_UNITAIRES

# version construction sans tests unitaires :

#FLAGS=

# version final :

#FLAGS=-D NDEBUG


CC=gcc
BIN=maya
DOC_REP=doc
ARCHIVE=calendriersMaya
OBJETS=\main.o


all : $(OBJETS)
	$(CC) $(FLAGS) $(OBJETS) -lm -o $(BIN)

.c.o :
	$(CC) $(FLAGS) -c $<

main.o : main.c

doc : 
	doxygen main.c

archive : clean
	\rm -f $(ARCHIVE).tar.gz
	tar cvf $(ARCHIVE).tar *
	gzip $(ARCHIVE).tar

clean :
	\rm -f $(BIN)
	\rm -f *.o
	\rm -f *~
	\rm -f core
	\rm -fr html
	\rm -fr latex
