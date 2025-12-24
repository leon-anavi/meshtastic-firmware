#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<Adafruit_HTU21DF.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "HTU21DSensor.h"
#include "TelemetrySensor.h"
#include <Adafruit_HTU21DF.h>
#include <typeinfo>

HTU21DSensor::HTU21DSensor() : TelemetrySensor(meshtastic_TelemetrySensorType_HTU21D, "HTU21D") {}

bool HTU21DSensor::initDevice(TwoWire *bus, ScanI2C::FoundDevice *dev)
{
    LOG_INFO("Init sensor: %s", sensorName);
    status = htu.begin(bus);
    if (!status) {
        return status;
    }

    initI2CSensor();
    return status;
}

bool HTU21DSensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_temperature = true;
    measurement->variant.environment_metrics.has_relative_humidity = true;

    LOG_DEBUG("HTU21D getMetrics");
    measurement->variant.environment_metrics.temperature = htu.readTemperature();
    measurement->variant.environment_metrics.relative_humidity = htu.readHumidity();

    return true;
}
#endif
