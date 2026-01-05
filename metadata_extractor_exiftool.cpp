#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <regex>

#ifdef _WIN32
    #define POPEN _popen
    #define PCLOSE _pclose
#else
    #define POPEN popen
    #define PCLOSE pclose
#endif

// Convert DMS (degrees, minutes, seconds) to decimal
double dmsToDecimal(const std::string& dmsStr) {
    std::regex regex(R"((\d+)\s*deg\s*(\d+)'\s*([\d.]+)\"\s*([NSEW]))");
    std::smatch match;
    if (std::regex_search(dmsStr, match, regex)) {
        double deg = std::stod(match[1].str());
        double min = std::stod(match[2].str());
        double sec = std::stod(match[3].str());
        char dir = match[4].str()[0];
        double dec = deg + min / 60.0 + sec / 3600.0;
        if (dir == 'S' || dir == 'W') dec = -dec;
        return dec;
    }
    return 0.0;
}

int main() {
    std::string filePath;
    std::cout << "Enter full file path:\n> ";
    std::getline(std::cin, filePath);

    if (filePath.empty()) {
        std::cerr << "Error: No file path provided.\n";
        return 1;
    }

    std::string command = "exiftool -a -u -g \"" + filePath + "\"";

    FILE* pipe = POPEN(command.c_str(), "r");
    if (!pipe) {
        std::cerr << "Failed to execute ExifTool.\n";
        return 1;
    }

    std::ofstream outFile("metadata_output.txt");
    if (!outFile.is_open()) {
        std::cerr << "Failed to create output file.\n";
        PCLOSE(pipe);
        return 1;
    }

    char buffer[4096];
    std::string gpsLatStr, gpsLonStr;

    while (fgets(buffer, sizeof(buffer), pipe)) {
        std::string line(buffer);
        std::cout << line;
        outFile << line;

        // Detect GPS Latitude
        if (line.find("GPS Latitude") != std::string::npos) {
            gpsLatStr = line.substr(line.find(":") + 1);
            gpsLatStr.erase(0, gpsLatStr.find_first_not_of(" \t\n\r"));
        }
        // Detect GPS Longitude
        if (line.find("GPS Longitude") != std::string::npos) {
            gpsLonStr = line.substr(line.find(":") + 1);
            gpsLonStr.erase(0, gpsLonStr.find_first_not_of(" \t\n\r"));
        }
    }

    PCLOSE(pipe);
    outFile.close();

    // Generate Google Maps link
    if (!gpsLatStr.empty() && !gpsLonStr.empty()) {
        double lat = dmsToDecimal(gpsLatStr);
        double lon = dmsToDecimal(gpsLonStr);
        std::cout << "\nGoogle Maps link: https://www.google.com/maps?q=" 
                  << lat << "," << lon << "\n";
    } else {
        std::cout << "\nNo GPS coordinates found in metadata.\n";
    }

    std::cout << "\nMetadata saved to metadata_output.txt\n";
    return 0;
}