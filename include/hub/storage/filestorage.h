#pragma once

#include <vector>
#include <string>

#include <hub/data/measurement.h>

namespace sensorsystem
{

class FileStorage
{
    public:
    virtual bool recordMeasurementToFile(const Measurement& measurement) = 0;

    virtual ~FileStorage() = default;
};

}