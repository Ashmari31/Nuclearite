#!/bin/sh

temp=$(cat /sys/bus/iio/devices/iio\:device0/in_temp_input)
pressure=$(cat /sys/bus/iio/devices/iio\:device0/in_pressure_input)

#temp=$(($temp/1000))
#pressure=$(($pressure/1000))

echo "$temp °C"
echo "$pressure Pa"

sqlite3 nuclearite.sqlite3 "INSERT INTO mesures(temperature, pressure, date_mesure, fk_env) VALUES (($temp/1000), ($pressure/1000), DATETIME(), 0);"
echo "Data saved"
