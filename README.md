# Metadata_Extractor_Exiftool
A C++ program that extracts metadata from image and media files using ExifTool, with specialized handling for GPS coordinates. It parses GPS latitude and longitude in DMS (degrees, minutes, seconds) format, converts them to decimal degrees, and generates a direct Google Maps link for easy location visualization.


***Features***

Metadata Extraction: Leverages ExifTool to retrieve comprehensive metadata from files, including EXIF, IPTC, and XMP data.
GPS Coordinate Processing: Automatically detects and converts GPS latitude/longitude from DMS to decimal format.
Google Maps Integration: Generates a clickable Google Maps URL if GPS data is present in the file metadata.
Cross-Platform Compatibility: Works on both Windows and Unix-like systems using platform-specific popen implementations.
Output to File: Saves all extracted metadata to `metadata_output.txt` for further analysis or archiving.


***Requirements***

ExifTool: Must be installed and available in the system PATH. Download from [ExifTool official site](https://exiftool.org/).
C++ Compiler: Compatible with C++11 or later (tested with g++ and MSVC).
Standard Libraries: Relies on `<iostream>`, `<fstream>`, `<cstdio>`, `<string>`, and `<regex>` (C++11 required for regex).


***Usage***

*Compile the program:*
`g++ metadata_extractor_exiftool.cpp -o metadata_extractor`

*Run the executable:*
`./metadata_extractor`
Enter the full path to the file when prompted (e.g., `/path/to/image.jpg` or `C:\path\to\image.jpg`).

*The program will:*
○  Display metadata in the console.
○  Save metadata to `metadata_output.txt`.
○  Output a Google Maps link if GPS coordinates are found.


***Example Output***

```md
Enter full file path:
> /path/to/photo.jpg

[ExifTool output...]
GPS Latitude: 37 deg 46' 26.00" N
GPS Longitude: 122 deg 25' 5.00" W

Google Maps link: https://www.google.com/maps?q=37.773889,-122.418056

Metadata saved to metadata_output.txt
```


***Notes***

•  Ensure ExifTool is properly installed and executable from the command line.
•  The program assumes GPS coordinates are in standard DMS format with cardinal directions (N/S/E/W).
•  No GPS data results in a notification message instead of a maps link.
