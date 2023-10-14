#ifndef __VIDEO_HPP__
#define __VIDEO_HPP__

#include "Multimedia.hpp"
#include <cstdlib>
#include <iostream>

class Video;

/**
 * A type representing a smart pointer of a video
 * @see Video
*/
using VideoPointer = std::shared_ptr<Video>;

/**
 * A class representing a video extending the Multimedia interface
*/
class Video : public Multimedia{

    friend class MultimediaManager;
    friend class Factory;
    
    private:
        /**
         * The default video manager
        */
        static const std::string _VIDEO_MANAGER;

    protected:
        /**
        * The length of the video
        */
        int _Length = 0;

    private:
        /**
         * Check the validity of the length
         * @param length The new length
         * @return True if it is valid
        */
        bool checkLength(int length) const {
            return length >= 0;
        }

    public:
        /**
         * A basic destructor
        */
        ~Video(){};

    protected:
        /**
         * An empty constructor
        */
        Video(){};

        /**
         * A basic constructor
         * @param name The video's name
         * @param path The path of the file associated to the video
         * @param length The video's length
        */
        Video(std::string name, std::string path, int length) : Multimedia(name, path){
            _Length = length;
            if(!checkLength(length)){
                std::cerr << "Video constructor:\n\tThe new length: " << length 
                            << " is not correct; default back to 0" << std::endl;
                _Length = 0;
            }
        }
    
    public:
        /**
         * A setter for the length
         * @param length The new length (default 0)
        */
        void setLength(int length = 0){
            _Length = length;
            if(!checkLength(length)){
                std::cerr << "Video length setter:\n\tThe new length: " << length 
                            << " is not correct; default back to 0" << std::endl;
                _Length = 0;
            }
        }

        /**
         * A getter for the length
         * @return The video's length
        */
        float getLength() const {
            return _Length;
        }

        /**
         * A printing method
         * @param stream The output stream
        */
        void print(std::ostream& stream) const override {
            Multimedia::print(stream);
            stream << ", Length: " << _Length;
        }

        /**
         * Play the video in parallel (using mpv)
         * Leave the program if the path is not correct
        */
        void play() const override{
            std::string command = _VIDEO_MANAGER + " " + _Path + "&";
            system(command.data());
        }

    private:
        /**
         * A function to serialize the multimedia
         * @param f The stream
        */
        void write(std::ofstream& f) const override {
            Multimedia::write(f);
            f << "{\"class\":\"Video\",\n" 
              << "\"name\":\"" << _Name << "\",\n"
              << "\"path\":\"" << _Path << "\",\n"
              << "\"length\":" << _Length << "}";
        }

};

#endif