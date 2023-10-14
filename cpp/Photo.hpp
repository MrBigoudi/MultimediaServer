#ifndef __PHOTO_HPP__
#define __PHOTO_HPP__

#include "Multimedia.hpp"
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>

class Photo;

/**
 * A type representing a smart pointer of a photo
 * @see Photo
*/
using PhotoPointer = std::shared_ptr<Photo>;

/**
 * A class representing a Photo extending the Multimedia interface
*/
class Photo : public Multimedia{

    friend class MultimediaManager;
    friend class Factory;

    private:
        /**
         * The latitude of the photo
        */
        float _Latitude = 0.0f;

        /**
         * The longitude of the photo
        */
        float _Longitude = 0.0f;

        /**
         * The program to open a photo
        */
        static const std::string _PHOTO_MANAGER;

    private:
        /**
         * Check the validity of the latitude
         * @param latitude The new latitude
         * @return True if it is valid
        */
        bool checkLatitude(float latitude) const {
            return latitude < 0.0f;
        }

        /**
         * Check the validity of the longitude
         * @param longitude The new longitude
         * @return True if it is valid
        */
        bool checkLongitude(float longitude) const {
            return longitude < 0.0f;
        }

    public:
        /**
         * A basic destructor
        */
        ~Photo(){};

    private:
        /**
         * An empty constructor
        */
        Photo(){};

        /**
         * A basic constructor
         * @param name The photo's name
         * @param path The path of the file associated to the photo
         * @param latitude The photo's latitude
         * @param longitude The photo's longitude
        */
        Photo(std::string name, std::string path, float latitude, float longitude) : Multimedia(name, path){
            _Latitude = latitude;
            if(checkLatitude(latitude)){
                std::cerr << "Photo constructor:\n\tThe new latitude: " << latitude 
                            << " is not correct; default back to 0.0f" << std::endl;
                _Latitude = 0.0f;
            }

            _Longitude = longitude;
            if(checkLongitude(longitude)){
                std::cerr << "Photo constructor:\n\tThe new longitude: " << longitude 
                            << " is not correct; default back to 0.0f" << std::endl;
                _Longitude = 0.0f;
            }
        }

    public:
        /**
         * A setter for the latitude
         * @param latitude The new latitude (default 0.0f)
        */
        void setLatitude(float latitude = 0.0f){
            _Latitude = latitude;
            if(checkLatitude(latitude)){
                std::cerr << "Photo latitude setter:\n\tThe new latitude: " << latitude 
                        << " is not correct; default back to 0.0f" << std::endl;
                _Latitude = 0.0f;
            }
        }

        /**
         * A setter for the longitude
         * @param longitude The new longitude (default 0.0f)
        */
        void setLongitude(float longitude = 0.0f){
            _Longitude = longitude;
            if(checkLongitude(longitude)){
                std::cerr << "Photo longitude setter:\n\tThe new longitude: " << longitude 
                        << " is not correct; default back to 0.0f" << std::endl;
                _Longitude = 0.0f;
            }
        }

        /**
         * A getter for the latitude
         * @return The photo's latitude
        */
        float getLatitude() const {
            return _Latitude;
        }

        /**
         * A getter for the longitude
         * @return The photo's longitude
        */
        float getLongitude() const {
            return _Longitude;
        }

        /**
         * A printing method
         * @param stream The output stream
        */
        void print(std::ostream& stream) const override {
            Multimedia::print(stream);
            stream << ", Latitude: " << _Latitude 
                    << ", Longitude: " << _Longitude;
        }

        /**
         * Display the photo in parallel (using xdg-open)
         * Leave the program if the path is not correct
        */
        void play() const override{
            std::string command = _PHOTO_MANAGER + " " + _Path + "&";
            system(command.data());
        }

    private:

        /**
         * A function to serialize the multimedia
         * @param f The stream
        */
        void write(std::ofstream& f) const override {
            Multimedia::write(f);
            f << "{\"class\":\"Photo\",\n" 
              << "\"name\":\"" << _Name << "\",\n"
              << "\"path\":\"" << _Path << "\",\n"
              << "\"latitude\":\"" << _Latitude << "\",\n"
              << "\"longitude\":\"" << _Longitude << "\"}";
        }

};

#endif