##########################################
#
#  Exemple de Makefile
#  Eric Lecolinet - Reda Dehak - Telecom ParisTech 2015
#  INF224 - TP C++ - http://www.telecom-paristech.fr/~elc/inf224
#
##########################################

#
# Nom du programme
#
SERVER = server.exe
CLIENT = client.exe

DOCDIR = doc
DOXYFILE = Doxyfile

#
# Fichiers sources (NE PAS METTRE les .h ni les .o seulement les .cpp)
#
SERVER_SOURCES = main.cpp Photo.cpp Video.cpp MultimediaManager.cpp ccsocket.cpp tcpserver.cpp
CLIENT_SOURCES = client.cpp ccsocket.cpp 

#
# Fichiers objets (ne pas modifier sauf si l'extension n'est pas .cpp)
#
SERVER_OBJETS = ${SERVER_SOURCES:%.cpp=%.o}
CLIENT_OBJETS = ${CLIENT_SOURCES:%.cpp=%.o}

#
# Compilateur C++
#
CXX = g++

#
# Options du compilateur C++
#   -g pour debugger, -O optimise, -Wall affiche les erreurs, -I pour les headers
#   -std=c++11 pour C++11
# Exemple: CXXFLAGS= -std=c++11 -Wall -O -I/usr/local/qt/include
#
CXXFLAGS = -std=c++11 -Wall -g

#
# Options de l'editeur de liens
#
LDFLAGS = 

#
# Librairies a utiliser
# Exemple: LDLIBS = -L/usr/local/qt/lib -lqt
#
LDLIBS = -lpthread


##########################################
#
# Regles de construction/destruction des .o et de l'executable
# depend-${SERVER} sera un fichier contenant les dependances
#
 
all: ${SERVER} ${CLIENT}

${SERVER}: depend-${SERVER} ${SERVER_OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${SERVER_OBJETS} ${LDLIBS}

${CLIENT}: depend-${CLIENT} ${CLIENT_OBJETS}
	${CXX} -o $@ ${CXXFLAGS} ${LDFLAGS} ${CLIENT_OBJETS} ${LDLIBS}

run: ${SERVER} ${CLIENT}
	./${SERVER}

clean:
	-@$(RM) *.o depend-${CLIENT} depend-${SERVER} core 1>/dev/null 2>&1

clean-all: clean
	-@$(RM) ${SERVER} ${CLIENT} 1>/dev/null 2>&1
	-@$(RM) -r ${DOCDIR} 1>/dev/null 2>&1
  
tar:
	tar cvf client_server.tar.gz ${CLIENT_SOURCES} ${SERVER_SOURCES}

# Gestion des dependances : creation automatique des dependances en utilisant 
# l'option -MM de g++ (attention tous les compilateurs n'ont pas cette option)
#
depend-${SERVER}:
	${CXX} ${CXXFLAGS} -MM ${SERVER_SOURCES} > depend-${SERVER}
depend-${CLIENT}:
	${CXX} ${CXXFLAGS} -MM ${CLIENT_SOURCES} > depend-${CLIENT}


doc: ${DOXYFILE}
	doxygen ${DOXYFILE}

${DOXYFILE}:
	doxygen -g ${DOXYFILE}

###########################################
#
# Regles implicites
#

.SUFFIXES: .cpp .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c (CFLAGS) $(INCPATH) -o $@ $<


#############################################
#
# Inclusion du fichier des dependances
#
-include depend-${SERVER}
-include depend-${CLIENT}
