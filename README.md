# Power-Grid-Management
This C++ program manages power distribution across multiple districts, tracking power usage, technician assignments, and power supply status. It provides utilities to monitor and control district power allocation while ensuring the total power demand doesn't exceed available supply.

Features: Load district data from a file. View district status (residents, power usage, technicians, etc.). Update power supply values. Cut or restore power to specific districts. Assign technicians to districts. Save the current state back to a file. Simple bubble sort by number of residents. Menu-based user interaction in the console

Requirements: C++17 or later. Inout file in the specified format.

File format: The input file must follow this structure:
First line: Total power supply (MW).
Second line: Number of districts.
For each district: District name (may contain spaces). District type. Number of residents. Power consumption (MW). Power status (1 = on, 0 = off). Number of technicians. Technician names (one per line, if any).

Functions
void load(string fname, district districts[], int &num, int &power)
Reads district data from a file, populates the districts array, and sorts by resident count

void save(string fname, district districts[], int num, int power)
Writes current district data to a file

void print_all(district districts[], int num, int power)
Displays complete district information and power status

void assign_technician(string tech_name, string district_name, district districts[], int num_district)
Assigns a technician to a district if capacity allows

void cut_power(string district_name, district districts[], int num)
Turns off power to a specified district

void restore_power(string district_name, district districts[], int num)
Restores power to a specified district


