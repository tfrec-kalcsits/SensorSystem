#pragma once

#include <memory>
#include <hub/data/measurement.h>
#include <hub/storage/filestorage.h>
#include <hub/storage/remotestorage.h>
#include <hub/storage/dropboxstorage.h>
#include <hub/storage/csvfilestorage.h>

namespace sensorsystem
{

class MeasurementService
{
    public:
    MeasurementService(std::unique_ptr<FileStorage> file_storage, std::unique_ptr<RemoteStorage> remote_storage);
    bool recordMeasurement(const Measurement& measurement);
    bool syncMeasurements();

    private:
    std::unique_ptr<FileStorage> file_storage;
    std::unique_ptr<RemoteStorage> remote_storage;
};
    
} // sensorsystem
