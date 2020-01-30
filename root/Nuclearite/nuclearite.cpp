#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
#include <array>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <sqlite3.h>

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

	sqlite3* DB = NULL;
	std::ostringstream strtemp, strpress;

	int exit = 0;
	exit = sqlite3_open("nuclearite.sqlite3", &DB); 	
	if (exit) { 
        	std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl; 
	        return (-1); 
    	} 

	std::cout << "Opened Database Successfully!" << std::endl; 
	std::string request, req;
	char **messageError;

	float temp = get_temp();
	double pressure = get_pressure();
	std::cout<< temp <<" °C"<<std::endl;
	strtemp << temp;
	strpress << pressure;

	req = "INSERT INTO mesures(temperature, pressure, date_mesure, fk_env) VALUES (" + strtemp.str() + ", " + strpress.str()  + ", DATETIME(), 0);";
	exit = sqlite3_exec(DB, req.c_str(), NULL, 0, messageError);
	
	if (exit != SQLITE_OK) {
        	std::cerr << "Error Create Table" << std::endl;
        	//sqlite3_free(messageError);
    	}
    	else
    	    std::cout << "Table created Successfully" << std::endl;


//    	std::cout<<get_pressure()<<" Pa"<<std::endl;	
	
	sqlite3_close(DB); 
}

