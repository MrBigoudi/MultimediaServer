##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP Java/Swing - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme (doit correspondre au fichier qui contient main())
#
PROG = Client

#
# Fichiers sources .java
#
SOURCES = *.java

#
# Compilateur Java
#
JC = javac

DOCDIR = doc
DOXYFILE = Doxyfile

#
# Options du compilateur Java
#
JFLAGS = -g -Xdiags:verbose


##########################################
#
# Regles de construction/destruction des .class et de l'executable
#
 
all: classes

run: all
	java ${PROG}

classes: $(SOURCES:.java=.class)

clean:
	-@$(RM) *.class 1>/dev/null 2>&1
	-@$(RM) -r ${DOCDIR} 1>/dev/null 2>&1
  
tar:
	tar cvf ${PROG}.tar.gz ${SOURCES}

doc: ${DOXYFILE}
	doxygen ${DOXYFILE}

${DOXYFILE}:
	doxygen -g ${DOXYFILE}


###########################################
#
# Regles implicites
#

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java