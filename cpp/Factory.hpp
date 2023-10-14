#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include "Photo.hpp"
#include "Video.hpp"
#include "Film.hpp"

#include <iostream>
#include <vector>
#include <sstream>

class MultimediaManager;

/**
 * A static class to create multimedias of the different types
*/
class Factory{
    friend class MultimediaManager;


    private:
        /**
         * Create a Photo given an ifstream
         * @param f The file to read from
         * @return A Photo smart pointer
        */
        static PhotoPointer readPhoto(std::ifstream& f) {
            int nbParams = 4;
            std::vector<std::string> params = getParams(f, nbParams);
            std::string name = params[0];
            std::string path = params[1];
            int latitude = atoi(params[2].c_str());
            int longitude = atoi(params[3].c_str());
            return PhotoPointer(new Photo(name, path, latitude, longitude));
        }

        /**
         * Create a Video given an ifstream
         * @param f The file to read from
         * @return A Video smart pointer
        */
        static VideoPointer readVideo(std::ifstream& f) {
            int nbParams = 3;
            std::vector<std::string> params = getParams(f, nbParams);
            std::string name = params[0];
            std::string path = params[1];
            int length = atoi(params[2].c_str());
            return VideoPointer(new Video(name, path, length));
        }

        /**
         * Create a Film given an ifstream
         * @param f The file to read from
         * @return A Film smart pointer
        */
        static FilmPointer readFilm(std::ifstream& f) {
            int nbParams = 5;
            std::vector<std::string> params = getParams(f, nbParams);
            std::string name = params[0];
            std::string path = params[1];
            int length = atoi(params[2].c_str());
            int nbChapters = atoi(params[3].c_str());
            std::vector<int> chapters(nbChapters);
            createChapters(params[4], nbChapters, chapters);
            return FilmPointer(new Film(name, path, length, nbChapters, chapters.data()));
        }

    private:
        /**
         * Get the attributes from an ifstream
         * @param f The file to read from
         * @param nbParams The number of attributes to get
        */
        static std::vector<std::string> getParams(std::ifstream& f, int nbParams){
            std::string line = "";
            size_t idPos = 0;
            std::vector<std::string> params(nbParams);

            for(int i=0; i<nbParams; i++){
                std::getline(f, line);
                idPos = line.find(":");
                if(idPos != std::string::npos){
                    params[i] = line.substr(idPos+2, line.size()-2-(idPos+2));
                }
            }

            // for(int i=0; i<nbParams; i++){
            //     std::cout << "\nparams[" << i << "]: " << params[i];
            // }
            // std::cout << std::endl;

            return params;
        }

        /**
         * Create the array of film chapters
         * @param chapters The chapters as a string
         * @param nbChapters The number of chapters
         * @param realChapters The vector containing the real chapters in the end
        */
        static void createChapters(const std::string& chapter, int nbChapters, std::vector<int>& realChapters){
            // remove the brackets
            std::string modifiedChapters = chapter.substr(1, chapter.size() - 2);
            // create a stream to parse the modified string
            std::istringstream iss(modifiedChapters);
            int val = 0;
            int i = 0;

            while (iss >> val) {
                realChapters[i++] = val;
                if (iss.peek() == ',') {
                    iss.ignore();
                }
            }
        }
};

#endif