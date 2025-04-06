#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

//Defined structure for each district
struct district {
   string name;
   string type;
   int num_resident;
   int power;
   int num_technician;
   string technicians[10];
   bool has_power;
};

//Helper functions to sort districts
void swap(string x, string y){
   string temp = x;
   x = y;
   y = temp;
}

void bubbleSort(district districts[], int num) {
   for(int i = 0; i < num - 1; i++){
      for(int j = 0; j < num - i - 1; j++) {
         if(districts[j].num_resident > districts[j+1].num_resident) {
            swap(districts[j], districts[j+1]);
         }
      }
   }
}

//Load function to read the input file
void load(string fname, district districts[], int &num, int &power){
   ifstream fin(fname);
   
   if (!fin.is_open()) {
      cout << "File not found!" << endl;
      exit(1);
   }
   
   fin >> power;
   fin >> num;
   fin.ignore();

   for(int i = 0; i < num; i++) {
      
      getline(fin , districts[i].name);
      
      fin >> districts[i].type;

      fin >> districts[i].num_resident;

      fin >> districts[i].power;

      int powerStatus;
      fin >> powerStatus;

      if(powerStatus == 1){
         districts[i].has_power = true;
      }
      else{
         districts[i].has_power = false;
      }
      
      fin >> districts[i].num_technician;
      fin.ignore();
      
      for(int j = 0; j < districts[i].num_technician; j++){
         getline(fin, districts[i].technicians[j]);
      }
   }
   
   fin.close();
   
   bubbleSort(districts, num);
}

//Save function to pass the information to an output file
void save(string fname, district districts[], int num, int power){
   ofstream file(fname);
   
   if (!file.is_open()) {
      cout << "File not found!" << endl;
      exit(1);
   }
   
   file << power << endl;
   file << num << endl;
   
   for(int i = 0; i < num; i++) {
      file << districts[i].name << endl;
      file << districts[i].type << endl;
      file << districts[i].num_resident << endl;
      file << districts[i].power << endl;
      if(districts[i].has_power){
         file << "1" << endl;
      }
      else { 
         file << "0" << endl;
      }
      file << districts[i].num_technician << endl;
      
      for(int j = 0; j < districts[i].num_technician; j++) {
         file << districts[i].technicians[j] << endl;
      }
   }
   
   file.close();
}

//Print function to print out all the districts
void print_all(district districts[], int num, int power){
   int sum = 0;
   cout << "The current power supply is " << power << "MW." << endl;
   for(int i = 0; i < num; i++) {
      cout << districts[i].name << endl;
      cout << "District type: " << districts[i].type << endl;
      cout << "Number of residents: " << districts[i].num_resident << endl;
      
      if(districts[i].has_power){
         cout << "Power use: " << districts[i].power << "MW" << endl;
         cout << "Has power: 1" << endl;
         sum+= districts[i].power;
      }
      else{
         cout << "Power use: 0MW" << endl;
         cout << "Has power: 0" << endl;
      }
      
      if(districts[i].num_technician > 0){
         cout << "Technicians: ";
         for (int j = 0; j < districts[i].num_technician; j++) {
            if(j < districts[i].num_technician - 1){
               cout << districts[i].technicians[j] << ", " ;
            }
            else{
               cout << districts[i].technicians[j] << endl;
            }
         }
      }
      
      cout << "---" << endl;
      
      
   }
   //checks if we have enough power to supply all the districts
   if(sum > power){
      cout << "Critical Error! The current power supply of " << power <<"MW is insufficient to supply " << sum << "MW of power demand. Please shut off one or more districts." << endl;
      cout << "---" << endl;
   }
}

//Assigns a technician to a specific district if the district has space for another technician
void assign_technician(string tech_name, string district_name, district districts[], int num_district){
   for (int i = 0; i < num_district; i++) {
      if (districts[i].name == district_name) {
         if (districts[i].num_technician < 10) {
            districts[i].technicians[districts[i].num_technician] = tech_name;
            districts[i].num_technician++;
            cout << "Technician assigned!" << endl;
         } 
         else{
            cout << "Error! Technician limit reached for this district." << endl;
         }
         return;
      }
   }
   cout << "Error! The district with that name doesn't exist." << endl;
}

//Function to cut the power supply of a district
void cut_power(string district_name, district districts[], int num) {
   for (int i = 0; i < num; i++) {
      if (districts[i].name == district_name) {
         districts[i].has_power = false;
         cout << "The district's power has been successfully turned off." << endl;
         return;
      }
   }
   cout << "Error! The district with that name doesn't exist." << endl;
}

//Function to restore the power supply of a district
void restore_power(string district_name, district districts[], int num) {
   for (int i = 0; i < num; i++) {
      if (districts[i].name == district_name) {
         districts[i].has_power = true;
         cout << "The district's power has been successfully turned back on." << endl;
         return;
      }
   }
   cout << "Error! The district with that name doesn't exist." << endl;
}

int main() {
   string filename;
   int num, power, choice;
   district districts[10];
   cout << "Please enter the name of the file to load:" << endl;
   cin >> filename;
   load(filename, districts, num, power);
   print_all(districts, num, power);
   
   //Loop menu to satisfy the users prompt
   while(true){
      cout << "Main Menu" << endl;
      cout << "1- Status" << endl;
      cout << "2- Set Power Supply" << endl;
      cout << "3- Shutoff Power" << endl;
      cout << "4- Restore Power" << endl;
      cout << "5- Assign Technician" << endl;
      cout << "6- Save" << endl;
      cout << "7- Load" << endl;
      cout << "8- Exit" << endl;
      cout << "Please enter your choice:" << endl;
      cin >> choice;
      switch(choice){
        //Prints all the districts
         case 1: {
            print_all(districts, num, power);
            break;
         }
         //Updates the power supply for the districts
         case 2: {
            cout << "Enter the updated power supply in megawatts:" << endl;
            cin >> power;
            break;
         }
         //Cuts the power in a district
         case 3: {
            string name;
            cout << "Enter the name of the district:" << endl;
            cin.ignore();
            getline(cin, name);
            cut_power(name, districts, num);
            break;
         }
         //Restores the power in a district
         case 4: {
            string name2;
            cout << "Enter the name of the district:" << endl;
            cin.ignore();
            getline(cin, name2);
            restore_power(name2, districts, num);
            break;
         }
         //Asigns a specific technician to the prompted district
         case 5: {
            string tech_name, district_name;
            cout << "Enter the name of the technician:" << endl;
            cin.ignore();
            getline(cin, tech_name);
            cout << "Enter the name of the district to assign them to:" << endl;
            getline(cin, district_name);
            assign_technician(tech_name, district_name, districts, num);
            break;
         }
         //Saves the document into another file
         case 6: {
            string save_filename;
            cout << "Enter the file name to save to: " << endl;
            cin.ignore();
            getline(cin, save_filename);
            save(save_filename, districts, num, power);
            break;
         }
         //Loads an input file
         case 7: {
            string load_filename;
            cout << "Enter the file name to load from: " << endl;
            cin.ignore();
            getline(cin, load_filename);
            load(load_filename, districts, num, power);
            break;
         }
         //Terminates the loop menu
         case 8: {
            return 0;
         }
         //Checks for invalid input
         default: 
            cout << "Invalid option" << endl;
      }
   }
   return 0;
}