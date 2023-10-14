#ifndef __MULTIMEDIA_MANAGER_HPP__
#define __MULTIMEDIA_MANAGER_HPP__

#include "Multimedia.hpp"
#include "Group.hpp"
#include "Photo.hpp"
#include "Video.hpp"
#include "Film.hpp"
#include "Factory.hpp"

#include <cstdlib>
#include <fstream>
#include <map>
#include <memory>
#include <ostream>
#include <string>
#include <sstream>

/**
 * A type representing a map of MultimediaPointer
 * key: the name of the multimedia
 * @see MultimediaPointer
*/
using MultimediaMap = std::map<std::string, MultimediaPointer>;

/**
 * An enumeration to represent the maps of the multimedia manager
*/
enum MultimediaManagerMap{MULTIMEDIAS, GROUPS};

/**
 * A type representing a map of GroupPointer
 * key: the name of the group
 * @see GroupPointer
*/
using GroupMap = std::map<std::string, GroupPointer>;

/**
 * A type representing a smart pointer to the multimedia manager class
*/
using MultimediaManagerPointer = std::shared_ptr<MultimediaManager>;

/**
 * A class that will handle all the objects (groups and multimedias)
*/
class MultimediaManager{
    private:
        /**
         * A map of all the multimedias
        */
        MultimediaMap _Multimedias;

        /**
         * A map of all the groups
        */
        GroupMap _Groups;

        /**
         * The single instance of the MultimediaManager singleton
        */
        static MultimediaManagerPointer _Instance;

    private:
        /**
         * Check if a name is already in a map and return it
         * @param name The key we want to search
         * @param map The map in which we want to find it
         * @return True if it already exist
        */
        bool doesNameExist(std::string name, MultimediaManagerMap map) const{
            switch(map){
                case MULTIMEDIAS:{
                    auto val = _Multimedias.find(name);
                    return val != _Multimedias.end();
                    break;
                }
                case GROUPS:{
                    auto val = _Groups.find(name);
                    return val != _Groups.end();
                    break;
                }
            }
            return false;
        }

        /**
         * Remove an element of the given name from all the groups
         * @param name The name of the element
        */
        void deleteFromGroups(std::string name){
            for(auto group : _Groups){
                auto mult = group.second->getIterator(name);
                if(mult == nullptr) continue;
                group.second->remove(mult);
            }
        }

    private:
        /**
         * A basic constructor
        */
        MultimediaManager(){}

    public:
        /**
         * Get the single instance of the MultimediaManager
         * @return The instance of the class
        */
        static MultimediaManagerPointer getInstance(){
            if(!_Instance){
                _Instance = MultimediaManagerPointer(new MultimediaManager);
            }
            return _Instance;
        }

        /**
         * A basic destructor
        */
        ~MultimediaManager(){
            for(auto group: _Groups){
                group.second.reset();
            }
            for(auto mult: _Multimedias){
                mult.second.reset();
            }
        }

        /**
         * Create a photo, add it to the map and return it
         * @param name The photo's name
         * @param path The path of the file associated to the photo
         * @param latitude The photo's latitude
         * @param longitude The photo's longitude
         * @return The created photo
        */
        PhotoPointer addPhoto(std::string name, std::string path, float latitude, float longitude){
            if(doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "An object with the name: " << name 
                            << " already exists in the Multimedias map !\n"
                            << "\tObject will not be created, returning a nullptr instead!" 
                            << std::endl;
                return nullptr;
            }
            PhotoPointer photo(new Photo(name, path, latitude, longitude));
            _Multimedias[name] = photo;
            return photo;
        }

        /**
         * Add a multimedia to the map and return it
         * @param mult THe multimedia to add
         * @return The multimedia
        */
        MultimediaPointer addMultimedia(MultimediaPointer mult){
            if(!mult){
                std::cerr << "Can't add an empty object!" << std::endl;
                return nullptr;
            }
            std::string name = mult->getName();
            if(doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "An object with the name: " << name
                            << " already exists in the Multimedias map !\n"
                            << "\tObject will not be added, returning a nullptr instead!" 
                            << std::endl;
                return nullptr;
            }
            _Multimedias[name] = mult;
            return mult;
        }

        /**
         * Create a film, add it to the map and return it
         * @param name The film's name
         * @param path The path of the file associated to the film
         * @param length The film's length
         * @param nbChapters The number of chapters
         * @param chapters The film's chapters
         * @return The newly created film
        */
        FilmPointer addFilm(std::string name, std::string path, int length, int nbChapters, const int* chapters){
            if(doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "An object with the name: " << name 
                            << " already exists in the Multimedias map !\n"
                            << "\tObject will not be created, returning a nullptr instead!" 
                            << std::endl;
                return nullptr;
            }
            FilmPointer film(new Film(name, path, length, nbChapters, chapters));
            _Multimedias[name] = film;
            return film;
        }

        /**
         * Create a video, add it to the map and return it
         * @param name The video's name
         * @param path The path of the file associated to the video
         * @param length The video's length
         * @return THe newly created video
        */
        VideoPointer addVideo(std::string name, std::string path, int length){
            if(doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "An object with the name: " << name 
                            << " already exists in the Multimedias map !\n"
                            << "\tObject will not be created, returning a nullptr instead!" 
                            << std::endl;
                return nullptr;
            }
            VideoPointer video(new Video(name, path, length));
            _Multimedias[name] = video;
            return video;
        }

        /**
         * Create a group, add it to the map and return it
         * @param name The group's name
         * @return The newly created group
        */
        GroupPointer addGroup(std::string name){
            if(doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "An object with the name: " << name 
                            << " already exists in the Groups map !\n"
                            << "\tObject will not be created, returning a nullptr instead!" 
                            << std::endl;
                return nullptr;
            }
            GroupPointer group(new Group(name));
            _Groups[name] = group;
            return group;
        }

        /**
         * Display the entire DB
         * @param stream The output stream
        */
        void displayDB(std::ostream& stream) const {
            for(auto it : _Multimedias){
                auto val = it.second;
                val->print(stream);
                stream << "   /   ";
            }
        }

        /**
         * Find a given object in the given map and print it
         * @param name The name of the wanted object
         * @param map The map in which to look for it
         * @param stream The output stream
         * @return True if all went well
        */
        bool find(std::string name, MultimediaManagerMap map, std::ostream& stream) const{
            if(!doesNameExist(name, map)){
                std::cerr << "The object " << name << " does not exist!" << std::endl;
                return false;
            }
            switch(map){
                case MULTIMEDIAS:{
                    auto val = _Multimedias.find(name);
                    val->second->print(stream);
                    break;
                }
                case GROUPS:{
                    auto val = _Groups.find(name);
                    val->second->print(stream);
                    break;
                }
            }
            return true;
        }

        /**
         * Play a given multimedia
         * @param name The name of the multimedia
         * @return True if all went well
        */
        bool play(std::string name) const {
            if(!doesNameExist(name, MULTIMEDIAS)){
                std::cerr << "The object " << name << " does not exist!" << std::endl;
                return false;
            }
            _Multimedias.find(name)->second->play();
            return true;
        }

        /**
         * Delete a given object from the given map
         * @param name The name of the wanted object
         * @param map The map in which to look for it
        */
        void erase(std::string name, MultimediaManagerMap map) {
            if(!doesNameExist(name, map)){
                std::cerr << "The object " << name << " does not exist!" << std::endl;
                return;
            }
            switch(map){
                case MULTIMEDIAS:{
                    auto it = _Multimedias.find(name);
                    auto val = it->second;
                    // remove val from tab
                    _Multimedias.erase(it);
                    // delete it in all groups
                    deleteFromGroups(name);
                    break;
                }
                case GROUPS:{
                    auto val = _Groups.find(name)->second;
                    auto mult = val->getIterator(name);
                    val->remove(mult);
                    break;
                }
            }
        }

        /**
         * A function to serialize the multimedia manager
         * @param filePath The file in which to write
         * @return True if all went well
        */
        bool write(std::string filePath) const {
            std::ofstream f(filePath);
            if (f.is_open()) {
                // begining of the file
                f << "{\n\"class\":\"MultimediaManager\",\n";
                writeMultimedias(f);
                f << "\n}";
                f.close();
            } else {
                std::cerr << "Failed to open the file: " << filePath << "!" << std::endl;
                return false;
            }

            return true;
        }

        /**
         * A function to deserialize the multimedia manager
         * @param filePath The file from which to read
         * @return True if all went well
        */
        bool read(std::string filePath){
            std::ifstream f(filePath);
            if (f.is_open()) {
                std::string line = "";
                size_t idPos = 0;

                std::string className = "";
                std::getline(f, line);
                std::getline(f,line);
                std::getline(f, line);

                while(std::getline(f, line)){
                    // get separator
                    idPos = line.find(":");

                    // check if not found the last class
                    if(idPos != std::string::npos){
                        // get the class name
                        className = line.substr(idPos+2, line.size()-2-(idPos+2));
                        // create the correct class
                        MultimediaPointer m = nullptr;
                        if(className.compare("Photo") == 0){
                            m = Factory::readPhoto(f);
                        } else if(className.compare("Video") == 0){
                            m = Factory::readVideo(f);
                        } else if(className.compare("Film") == 0){
                            m = Factory::readFilm(f);
                        } else {
                            std::cerr << "Class: " << className <<" not recognized in the file: " << filePath << "!" << std::endl;
                            f.close();
                            return false;
                        }
                        // check if the Factory creation went well
                        if(!m){
                            std::cerr << "Failed to read the current multimedia!" << std::endl;
                            f.close();
                            return false;
                        }
                        // add the multimedia to the manager
                        addMultimedia(m);
                        // read the comma at the end of the current object
                        std::getline(f, line);
                    }
                }
                f.close();
                return true;
            } else {
                std::cerr << "Failed to open the file: " << filePath << "!" << std::endl;
                return false;
            }
        }

    private:
        /**
         * Serialize the multimedia map
         * @param f The ofstream
        */
        void writeMultimedias(std::ofstream& f) const {
            f << "\"multimedias\":[\n";
            for (auto it = _Multimedias.begin(); it != _Multimedias.end(); it++) {
                it->second->write(f);
                // add a comma if not the last element
                if (std::next(it) != _Multimedias.end()) {
                    f << "\n,\n";
                }
            }
            f << "\n]";
        }

};


#endif // __MULTIMEDIA_MANAGER_HPP__