#ifndef __GROUP_HPP__
#define __GROUP_HPP__


#include "Multimedia.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <memory>

class Group;

/**
 * A type representing a list of MultimediaPointer
 * @see MultimediaPointer
*/
using GroupList = std::list<MultimediaPointer>;

/**
 * A type representing a smart pointer of a group
 * @see Group
*/
using GroupPointer = std::shared_ptr<Group>;

/**
 * A class representing a group of object
*/
class Group : public GroupList {

    friend class MultimediaManager;

    private:
        /**
         * The group's name
        */
        std::string _Name = "";

    private:
        /**
         * A basic constructor
        */
        Group(){};

        /**
         * A basic constructor
         * @param name The group's name
        */   
        Group(std::string name){
            _Name = name;
        }

    public:
        /**
         * A basic destructor
        */
        ~Group(){}

        /**
         * Get the group's name
         * @return The group's name
        */
        std::string getName() const {
            return _Name;
        }

        /**
         * Check if a given name is in the group
         * @param name The name of the wanted element
         * @return The element of the given name in the group, nullptr otherwise
        */
        MultimediaPointer getIterator(std::string name) const {
            for(auto it : *this){
                if(it->getName().compare(name) == 0){
                    return it;
                }
            }
            return nullptr;
        }

        /**
         * Remove a given element from the group
         * Elements in the group must have unique name
         * @param mult The multimedia to remove
        */
        void remove(MultimediaPointer mult){
            for(auto it = begin(); it!=end(); it++){
                if(*it==mult){
                    erase(it);
                    return;
                }
            }
        }

        /**
         * A printing method
         * @param stream The output stream
        */
        void print(std::ostream& stream) const {
            stream << "Group: " << _Name << ", ";
            for(MultimediaPointer mult : *this){
                mult->print(stream);
                stream << "; ";
            }
        }

};

#endif