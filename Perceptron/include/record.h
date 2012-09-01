#ifndef RECORD_H
#define RECORD_H

#include <cassert>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>

class Record {

    std::string filename;
    std::string dir;
    std::string filedir;

    std::string separador;

    std::fstream file;

public:
    Record(std::string filename = "record.log", std::string dir = "logs");
    ~Record();

    void start(bool is_recording = true);
    void finish(bool is_recording = true);

    void add_record(std::stringstream &log, bool is_recording = true);
    void add_log(std::string log, bool is_recording = true);

    std::string get_filedir() {
        return this->filedir;
    }
};

#endif // RECORD_H
