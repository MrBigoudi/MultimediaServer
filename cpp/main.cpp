//
// main.cpp
// Created on 21/10/2018
//

//#define __VERSION_PRE_SOCKET__
#define __VERSION_POST_SOCKET__

#ifdef __VERSION_PRE_SOCKET__

#include <cstdlib>
#include <iostream>
#include "Multimedia.hpp"
#include "MultimediaManager.hpp"
#include "Photo.hpp"
#include "Video.hpp"
#include "Film.hpp"
#include "Group.hpp"

int main(int argc, const char* argv[]){

    /*
    Multimedia* photo = new Photo("Test", "Path", 1.0f, 2.0f);
    Photo* photo1 = new Photo("Test", "Path", 1.0f, 2.0f);
    Video* video = new Video("Test", "Path", 1);
    photo->print(std::cout);
    photo1->print(std::cout);
    video->print(std::cout);
    delete photo;
    delete photo1;
    delete video;
    */

    /* 
    Photo* photo = new Photo("profilPicture", "media/profilPicture.jpg", 640, 720);
    photo->play();
    Video* video = new Video("lavaSimulation", "media/lavaSimulation.mp4", 600);
    video->play();
    delete photo;
    delete video;
    */

    

    /* 5e étape
    const int DIM = 2;
    Multimedia* mult[DIM];
    mult[0] = photo;
    mult[1] = video;

    for(int i=0; i<DIM; i++){
        mult[i]->print(std::cout);
        mult[i]->play();
        delete(mult[i]);
    }
    */


    /* 6e étape 
    int chapters[3] = {1,1,3};
    Film* film = new Film("lavaSimulation", "media/lavaSimulation.mp4", 600,
                            3, chapters);

    film->print(std::cout);
    const int* newChapters = film->getChapters();
    film->print(std::cout);
    film->setChapters(3, newChapters);
    film->print(std::cout);
    // delete [] newChapters;
    // film->print(std::cout);

    delete film;
    */  


    /* 7e étape
    int chapters[3] = {1,1,3};
    Film* film = new Film("lavaSimulation", "media/lavaSimulation.mp4", 600,
                            3, chapters);
    Film* filmCopy = new Film(*film);
    film->print(std::cout);
    filmCopy->print(std::cout);
    film->setChapter(0, 2);
    film->print(std::cout);
    filmCopy->print(std::cout);

    delete film;
    delete filmCopy;
    */
    

    /* 8e étape
    Group* g1 = new Group("G1");
    Group* g2 = new Group("G2");

    int chapters[3] = {1,1,3};
    Film* film = new Film("Film", "media/lavaSimulation.mp4", 600,
                            3, chapters);
    Photo* photo = new Photo("Photo", "media/profilPicture.jpg", 640, 720);
    Video* video = new Video("Video", "media/lavaSimulation.mp4", 600);

    g1->push_back(film);
    g1->push_back(photo);
    g1->print(std::cout);

    g2->push_back(photo);
    g2->push_back(video);
    g2->print(std::cout);

    delete g2;
    g1->print(std::cout);

    delete g1;
    photo->print(std::cout);
    delete film;
    delete photo;
    delete video;
    */

    /* 9e étape
    Group* g1 = new Group("G1");
    Group* g2 = new Group("G2");

    int chapters[3] = {1,1,3};
    MultimediaPointer film(new Film("Film", "media/lavaSimulation.mp4", 600,
                            3, chapters));
    MultimediaPointer photo(new Photo("Photo", "media/profilPicture.jpg", 640, 720));
    MultimediaPointer video(new Video("Video", "media/lavaSimulation.mp4", 600));

    g1->push_back(film);
    g1->push_back(photo);
    g1->print(std::cout);

    g2->push_back(photo);
    g2->push_back(video);
    g2->print(std::cout);

    delete g2;
    g1->print(std::cout);

    delete g1;
    photo->print(std::cout);
    film.reset();
    photo.reset();
    video.reset();
    */

    MultimediaManager* m = new MultimediaManager();
    int chapters[3] = {1,1,3};
    auto f1 = m->addFilm("Film", "media/lavaSimulation.mp4", 600,
                            3, chapters);
    auto p1 = m->addPhoto("Photo", "media/profilPicture.jpg", 640, 720);
    m->find("Film", MultimediaManagerMap::MULTIMEDIAS, std::cout);
    // m->play("Photo");
    auto g1 = m->addGroup("G1");
    auto g2 = m->addGroup("G2");

    g1->push_back(f1);
    g2->push_back(f1);
    g1->push_back(p1);
    m->find("G1", MultimediaManagerMap::GROUPS, std::cout);
    m->find("G2", MultimediaManagerMap::GROUPS, std::cout);

    m->erase("Film", MultimediaManagerMap::MULTIMEDIAS);
    m->find("Film", MultimediaManagerMap::MULTIMEDIAS);
    m->find("G1", MultimediaManagerMap::GROUPS, std::cout);
    m->find("G2", MultimediaManagerMap::GROUPS, std::cout);

    f1.reset();
    p1.reset();
    g1.reset();
    g2.reset();

    delete(m);

    exit(EXIT_SUCCESS);
}

#endif

#ifdef __VERSION_POST_SOCKET__

#include <cstdlib>
#include <iostream>
#include "MultimediaManager.hpp"

#include <memory>
#include <string>
#include <sstream>
#include "tcpserver.h"
#include <map>

static const int PORT = 3331;
static const std::string DB = "media/db.json";

using Command = std::function<bool(std::string const& request, std::string& response, MultimediaManager const& manager)>;
enum Commands{CMD_PLAY, CMD_SEARCH, CMD_BAD, CMD_GET_DB, CMD_SAVE_DB};

/* SPECIFICATIONS */
// the different commands
bool cmdPlay(std::string const& request, std::string& response, MultimediaManager const& manager);
bool cmdSearch(std::string const& request, std::string& response, MultimediaManager const& manager);
bool cmdBad(std::string const& request, std::string& response, MultimediaManager const& manager);
bool cmdGetDB(std::string const& request, std::string& response, MultimediaManager const& manager);
bool cmdSaveDB(std::string const& request, std::string& response, MultimediaManager const& manager);
// the initializer for the map of commands
std::map<Commands, Command> initCommands();
// get the command given the request
Commands getCommand(std::string const& request);
std::string getFileName(std::string const& request);



/* IMPLEMENTATIONS */
Commands getCommand(std::string const& request){
    std::stringstream ss(request);
    std::string cmd;

    if(!(ss >> cmd)){
        ss.clear();
        return CMD_BAD;
    }

    if(cmd.compare("PLAY") == 0) return CMD_PLAY;
    if(cmd.compare("SEARCH") == 0) return CMD_SEARCH;
    if(cmd.compare("GETDB") == 0) return CMD_GET_DB;
    if(cmd.compare("SAVEDB") == 0) return CMD_SAVE_DB;
    return CMD_BAD;
}

std::string getFileName(std::string const& request){
    std::stringstream ss(request);
    std::string cmd, name;
    
    if(!(ss >> cmd)){
        ss.clear();
        return "";
    }

    if(!(ss >> name)){
        ss.clear();
        return "";
    }

    ss.clear();
    return name;
}

std::map<Commands, Command> initCommands(){
    std::map<Commands, Command> map;
    map[CMD_PLAY] = cmdPlay;
    map[CMD_SEARCH] = cmdSearch;
    map[CMD_BAD] = cmdBad;
    map[CMD_GET_DB] = cmdGetDB;
    map[CMD_SAVE_DB] = cmdSaveDB;
    return map;
}

bool cmdBad(std::string const& request, std::string& response, MultimediaManager const& manager){
    response = "Unrecognized command!";
    return true;
}

bool cmdGetDB(std::string const& request, std::string& response, MultimediaManager const& manager){
    std::stringstream result;
    manager.displayDB(result);
    response = result.str();
    return true;
}

bool cmdSaveDB(std::string const& request, std::string& response, MultimediaManager const& manager){
    std::stringstream result;
    bool success = manager.write(DB);

    if(success){
        response = "Successfully saved the db in " + DB + "!";
        return true;
    }  

    response = "Failed to save the db in " + DB + "!";
    return false;
}

bool cmdSearch(std::string const& request, std::string& response, MultimediaManager const& manager){
    std::string name = getFileName(request);
    if(name.compare("")==0) return false;
    std::stringstream result;

    bool ok = manager.find(name, MultimediaManagerMap::MULTIMEDIAS, result);
    if(!ok){
        response = "Unable to find the file: " + name + "!";
        return false;
    }

    response = result.str();
    return true;
}

bool cmdPlay(std::string const& request, std::string& response, MultimediaManager const& manager){
    std::string name = getFileName(request);
    if(name.compare("")==0) return false;
    std::stringstream result;

    bool ok = manager.play(name);
    if(!ok){
        response = "Unable to find the file: " + name + "!";
        return false;
    }

    response = "Successfully played the file: " + name + " in the set-top box!";
    return true;
}


int main(int agrc, char** argv){
    // init the database
    MultimediaManagerPointer m = MultimediaManager::getInstance();
    // int chapters[3] = {1,1,3};
    // auto f1 = m->addFilm("Film", "media/lavaSimulation.mp4", 600,
    //                         3, chapters);
    // auto p1 = m->addPhoto("Photo", "media/profilPicture.jpg", 640, 720);
    // auto g1 = m->addGroup("G1");
    // auto g2 = m->addGroup("G2");
    m->read(DB);

    // create the map of commands
    std::map<Commands, Command> commands = initCommands();

    // cree le TCPServer
    auto* server =
        new TCPServer( [&](std::string const& request, std::string& response) {
            if(!commands[getCommand(request)](request, response, *m)){
                // TODO: to change when wrong result
                return true;
            };
            return true;
        });


    // lance la boucle infinie du serveur
    std::cout << "Starting Server on port " << PORT << std::endl;

    int status = server->run(PORT);

    // en cas d'erreur
    if (status < 0) {
        std::cerr << "Could not start Server on port " << PORT << std::endl;
        return 1;
    }

    // free the database
    // f1.reset();
    // p1.reset();
    // g1.reset();
    // g2.reset();

    exit(EXIT_SUCCESS);
}

#endif