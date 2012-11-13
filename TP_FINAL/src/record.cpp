#include "../include/record.h"

Record::Record(std::string filename, std::string dir) {
    this->dir = dir;
    this->filename = filename;
    this->filedir = dir + "/" + filename;
    this->separador = "--------------------------------------------------------------------------------\n";
}

Record::~Record() {
    file.close(); // por las dudas
}

/* CREAMOS UN INICIO DE REGISTRO, O LO ADHERIMOS AL TEXTO DEL ARCHIVO ANTERIOR */
void Record::start(bool is_recording) {
    // Current date/time based on current system
    time_t now = time(0);

    // Convert now to tm struct for local timezone
    tm* localtm = localtime(&now);

    std::stringstream ss;

    ss << separador;
    ss << "Inicio de Nuevo Registro | Fecha/Hora: " << asctime(localtm) << std::endl;

    add_record(ss, is_recording);
}

void Record::finish(bool is_recording) {
	add_record("\n", is_recording);
}

/* AGREGAN LAS LINEAS AL ARCHIVO, UNO COMO STRINGSTREAM Y OTRO COMO STRING */
void Record::add_record(std::stringstream &log, bool is_recording) {
    if (!is_recording) {
        std::cout << log.str();
    }

    // Solo guarda el archivo si esta siendo grabado
    if (is_recording) {
        file.open(filedir.c_str(), std::fstream::out | std::fstream::app);
        assert(file.is_open()); //muestra error si no se pudo abrir el archivo

        file << log.str();

        file.close();
    }
}

void Record::add_record(std::string log, bool is_recording) {
    std::stringstream ss;
    ss << log;
    add_record(ss, is_recording);
}
