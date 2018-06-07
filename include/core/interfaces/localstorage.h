#ifndef SENSORSYSTEM_HUB_CORE_INTERFACES_LOACLSTORAGE_H
#define SENSORSYSTEM_HUB_CORE_INTERFACES_LOCALSTORAGE_H

#include <vector>
#include <string>

#include <core/data/measurement.h>

namespace sensorsystem
{

class LocalStorage
{
    public:
    virtual std::vector<std::string> getUnsyncedFiles() = 0;
    virtual std::vector<Measurement> getSavedMeasurements() = 0;
    virtual std::vector<std::string> getAllMeasurementFiles() = 0;
    virtual std::vector<Measurement> getMeasurementsFromFile() = 0;
    virtual ~LocalStorage() = default;
};

}

#endif