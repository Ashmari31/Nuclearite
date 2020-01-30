#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <cstring>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}


float get_temp()
{
    int temp = 0;
    float tempf = 0;
    
    std::string phrase = exec("cat  /sys/bus/iio/devices/iio\:device0/in_temp_input");
    char phrase2[phrase.size()+1];
    strcpy(phrase2, phrase.c_str());
    temp = atoi(phrase2);
    tempf = (float)temp/1000;
    return tempf;
}

float get_pressure()
{
    int press = 0;
    double press2 = 0;
    
    std::string phrase3 = exec("cat  /sys/bus/iio/devices/iio\:device0/in_pressure_input");
    char phrase4[phrase3.size()+1];
    strcpy(phrase4, phrase3.c_str());
    press = atoi(phrase4);
    press2 = (double)press/1000;
    return press2;
}

int main ()
{
	std::cout<<get_temp()<<" °C"<<std::endl;
    	std::cout<<get_pressure()<<" Pa"<<std::endl;
}

