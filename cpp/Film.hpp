#ifndef __FILM_HPP__
#define __FILM_HPP__

#include "Multimedia.hpp"
#include "Video.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>

class Film;

/**
 * A type representing a smart pointer of a film
 * @see Film
*/
using FilmPointer = std::shared_ptr<Film>;

/**
 * A class representing a film extending the Video class
*/
class Film : public Video{

    friend class MultimediaManager;
    friend class Factory;

    private:
        /**
         * The film chapters
        */
        int* _Chapters = nullptr;

        /**
         * The number of chapters
        */
        int _NbChapters = 0;

    public:
        /**
         * A basic destructor
        */
        ~Film(){
            delete [] _Chapters;
        };

    private:    
        /**
         * An empty constructor
        */
        Film(){}

        /**
         * A basic constructor
         * @param name The film's name
         * @param path The path of the file associated to the film
         * @param length The film's length
         * @param nbChapters The number of chapters
         * @param chapters The film's chapters
        */
        Film(std::string name, std::string path, int length, int nbChapters, const int* chapters) : Video(name, path, length){
            _NbChapters = nbChapters;
            setChapters(nbChapters, chapters);
        }

        /**
         * A constructor by copy
         * @param film The film to copy
        */
        Film(const Film& film): Video(film._Name, film._Path, film._Length){
            _NbChapters = film._NbChapters;
            setChapters(_NbChapters, film._Chapters);
        }

    public:
        /**
         * Redefinition of the equal
         * @param film The film to copy
        */
        Film & operator=(const Film& film){
            Video::operator=(film);
            _NbChapters = film._NbChapters;
            setChapters(_NbChapters, film._Chapters);
            return *this;
        }

        /**
         * Get the number of chapters
         * @return The number of chapters
        */
        int getNbChapters() const {return _NbChapters;}

        /**
         * Get the chapters
         * @return A copy of the chapters
        */
        const int* getChapters() const {
            return _Chapters;
        }

        /**
         * Set a chapter
         * @param chapterIdx The chapter's index (must be >=0 and <_NbChapters)
         * @param newVal The new chapter's value
        */
        void setChapter(int chapterIdx, int newVal){
            if(newVal < 0 || newVal >= _NbChapters) return;
            _Chapters[chapterIdx] = newVal;
        }

        /**
         * Set the chapters
         * @param nbChapters The number of chapters
         * @param chapters The new chapters
        */
        void setChapters(int nbChapters, const int* chapters){
            // free old array
            if(chapters == _Chapters) return;
            delete [] _Chapters;
            // recreate an array
            _NbChapters = nbChapters;
            if(nbChapters <= 0 || chapters == nullptr){
                _Chapters = nullptr;
                return;
            }
            _Chapters = new int[_NbChapters];
            // refill the old array
            for(int i=0; i<nbChapters; i++)
                _Chapters[i] = chapters[i];
        }

        /**
         * A printing method
         * @param stream The output stream
        */
        void print(std::ostream& stream) const override {
            Video::print(stream);
            stream << ", nbChapters: " << _NbChapters
                    << ", chapters: [";
            for(int i=0; i<_NbChapters-1; i++){
                stream << _Chapters[i] << ", ";
            }
            stream << _Chapters[_NbChapters-1] << "]";
        }

    private:

        /**
         * A function to serialize the multimedia
         * @param f The stream
        */
        void write(std::ofstream& f) const override {
            Multimedia::write(f);
            f << "{\"class\":\"Film\",\n" 
              << "\"name\":\"" << _Name << "\",\n"
              << "\"path\":\"" << _Path << "\",\n"
              << "\"length\":\"" << _Length << "\",\n"
              << "\"nbChapters\":\"" << _NbChapters << "\",\n";
            writeChapters(f);
            f << "}";
        }

    private:
        /**
         * A function to serialize the chapters
         * @param f The stream
        */
        void writeChapters(std::ofstream& f) const {
            f << "\"chapters\":\"[";
            for(int i=0; i<_NbChapters; i++){
                f << _Chapters[i];
                // if not last, add comma
                if(i != _NbChapters-1){
                    f << ",";
                }
            }
            f << "]\"";
        }

};

#endif