#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <cstring>

int exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }

    char phrase[result.size()+1];
    strcpy(phrase, result.c_str());
    return atoi(phrase);
}


float get_temp()
{   
    return (float)exec("cat /sys/bus/iio/devices/iio\:device0/in_temp_input")/1000;
}

float get_pressure()
{
	return (double)exec("cat /sys/bus/iio/devices/iio\:device0/in_pressure_input")/1000;
}

int main ()
{
	std::cout<<get_temp()<<" °C"<<std::endl;
    	std::cout<<get_pressure()<<" Pa"<<std::endl;
}

