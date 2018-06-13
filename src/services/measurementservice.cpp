#include <hub/services/measurementservice.h>

namespace sensorsystem
{

MeasurementService::recordMeasurement(std::unique_ptr<FileStorage> file_storage, std::unique_ptr<RemoteStorage> remote_storage)
    : file_storage(std::move(file_storage)), remote_storage(std::move(remote_storage))
{}

bool MeasurementService::recordMeasurement(const Measurement& measurement)
{
    return file_storage->recordMeasurementToFile(measurement);
}

bool MeasurementService::syncMeasurements()
{
    return remote_storage->syncFiles();
}

}