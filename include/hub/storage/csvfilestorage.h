#pragma once

#include <string>
#include <vector>

#include <hub/data/measurement.h>
#include "filestorage.h"

namespace sensorsystem
{

class CSVFileStorage : public FileStorage
{
    public:
    CSVFileStorage(std::string prefix_path="~/home/.hub/");

    bool recordMeasurementToFile(const Measurement& measurement) override;

    private:
    const std::string prefix_path;
};

}