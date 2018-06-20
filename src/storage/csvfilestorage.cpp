#include <fstream>
#include <curl/curl.h>
#include <hub/storage/csvfilestorage.h>
#include <hub/compatibility.h>

namespace sensorsystem
{

CSVFileStorage::CSVFileStorage(std::string prefix_path)
    : prefix_path(prefix_path) {}

bool CSVFileStorage::recordMeasurementToFile(const Measurement& measurement)
{
    const tm *time = &measurement.timestamp;
    std::stringstream ss;
    ss << (time->tm_mon + 1) << "-" << time->tm_mday << "-" << (time->tm_year + 1900);
    std::string date = ss.str();
    ss = std::stringstream();
    ss << time->tm_hour << ":" << time->tm_min;
    std::string time_str = ss.str();
    std::string path = prefix_path + date + ".csv";
    bool exists = fs::exists(path);
    std::ofstream file(path, exists ? std::ios::app : std::ios::out);
    
    if(!exists)
        file << "date, time, signature, ambient, object, lux\n";

    file << date << ", " << time_str << ", " << measurement.signature << ", "
        << measurement.ambient << ", " << measurement.object << ", "
        << measurement.lux << std::endl;

    std::string sync_file_path = prefix_path + ".sync";
    std::ofstream(sync_file_path, fs::exists(sync_file_path) ? std::ios::out : std::ios::app) << path;

    return true;
}

}
