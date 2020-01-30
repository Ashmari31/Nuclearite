#!/bin/sh

#temp=$(cat /sys/bus/iio/devices/iio\:device0/in_temp_input)
#pressure=$(cat /sys/bus/iio/devices/iio\:device0/in_pressure_input)

temp=10
pressure=0.1
echo "$temp °C\n"
echo "$pressure Pa\n"

sqlite3 nuclearite.sqlite3 "INSERT INTO mesures(temperature, pressure, date_mesure, fk_env) VALUES ($temp, $pressure, DATETIME(), 0);"
echo "Data saved"
