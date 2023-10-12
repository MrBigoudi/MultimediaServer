#ifndef __MULTIMEDIA_HPP__
#define __MULTIMEDIA_HPP__

#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class Multimedia;

/**
 * A type representing a smart pointer of a Multimedia
*/
using MultimediaPointer = std::shared_ptr<Multimedia>;


/**
 * Class containing common things for multimedia objects
*/
class Multimedia{

    protected:
        /**
         * The name of the multimedia object
        */
        std::string _Name = "";

        /**
         * Path to file associated to the multimedia object
        */
        std::string _Path = "";

    protected:
        /**
         * Check the path of the object
         * @param path The new path
         * @return true if the path is correct
        */
        bool checkPath(std::string path) const {
            std::ifstream test(path);
            if(!test){
                return false;
            }
            return true;
        }


    public:
        /**
         * A virtual destructor
        */
        virtual ~Multimedia(){};

        /**
         * A basic constructor
         * @param name The object's name
         * @param path The path of the file associated to the object
        */
        Multimedia(std::string name, std::string path){
            _Name = name;
            if(checkPath(path)){
                _Path = path;
                return;
            }
            std::cerr << "Multimedia constructor:\n\tThe file: " << path 
                    << " doesn't exist; default back to the empty string." << std::endl;
            _Path = "";
        }

        /**
         * A basic contructor initializing with empty strings
        */
        Multimedia(){}

        /**
         * A getter for the object's name
         * @return The object's name
        */
        std::string getName() const {
            return _Name;
        }

        /**
         * A getter for the object's path
         * @return The object's path
        */
        std::string getPathName() const {
            return _Path;
        }

        /**
         * A setter for the object's name
         * @param name The new name (default empty string)
        */
        void setName(std::string name = ""){
            _Name = name;
        }

        /**
         * A setter for the object's path
         * @param path The path to the object (default empty string)
        */
        void setPath(std::string path = ""){
            if(checkPath(path)){
                _Path = path;
                return;
            }
            std::cerr << "Path setter:\n\tThe file: " << path 
                    << " doesn't exist; default back to the empty string." << std::endl;
            _Path = "";
        }

        /**
         * A printing method
         * @param stream The output stream
        */
        virtual void print(std::ostream& stream) const{
            stream << "Name: " << _Name << ", Path: " << _Path;
        }

        /**
         * A purely virtual method to play the multimedia
        */
        virtual void play() const = 0;
};

#endif