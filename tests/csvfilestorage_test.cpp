#include <hub/storage/csvfilestorage.h>
#include <hub/data/measurement.h>

using namespace sensorsystem;

int main()
{
    CSVFileStorage storage("./");
    Measurement measurement;
    measurement.signature = "test1";

    storage.recordMeasurementToFile(measurement);

    measurement.signature = "test2";
    storage.recordMeasurementToFile(measurement);

    return 0;
}