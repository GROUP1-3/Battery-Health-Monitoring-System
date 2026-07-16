#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

// BatteryMonitor class
class BatteryMonitor
{
private:
	// Private data members
    string batteryID;
    int numberOfReadings;
    vector<double> voltages;
    double totalVoltage;
    double averageVoltage;
    double minimumVoltage;
    double maximumVoltage;

public:
	// To initialize variables
    BatteryMonitor()
    {
        totalVoltage = 0;
        averageVoltage = 0;
        minimumVoltage = 0;
        maximumVoltage = 0;
    }
    
     // Function to get battery details from the user
    void setBatteryDetails()
    {
        cout << "=====================================\n";
        cout << " BATTERY HEALTH MONITORING SYSTEM\n";
        cout << "=====================================\n\n";

        cout << "Enter Battery ID: ";
        cin >> batteryID;

       cout << "Enter Number of Voltage Readings: ";

while (!(cin >> numberOfReadings) || numberOfReadings <= 0)
{
    cout << "Invalid input! Please Enter Number of Voltage Readings: " ;
    cin.clear();
    cin.ignore(1000, '\n');
}
    }
    
    // Function to validate voltage input
    bool validateVoltage(double voltage)
    {
        if (voltage < 0)
            return false;
        return true;
    }
    
    
    // Function to classify battery condition
    string classifyVoltage(double voltage)
    {
        if (voltage < 0)
            return "Invalid Voltage Reading";
        else if (voltage <= 10.4)
            return "Critical Low Battery";
        else if (voltage <= 11.9)
            return "Low Battery - Recharge Required";
        else if (voltage <= 12.8)
            return "Normal Battery Condition";
        else
            return "Possible Overcharge";
    }
    
    
    // Function to record battery voltage readings
    void recordReadings()
    {
        double voltage;
        
               // loop through all readings
        for (int i = 0; i < numberOfReadings; i++)
        {
        	// repeat until a valid voltage is entered
           do
{
    cout << "\nEnter Voltage Reading " << i + 1 << ": ";

    while (!(cin >> voltage))
    {
        cout << "Invalid input! Please Enter Voltage Readings: " ;
        cin.clear();
        cin.ignore(1000, '\n');
    }

    if (!validateVoltage(voltage))
    {
        cout << "Invalid! Voltage cannot be negative.\n";
    }

} while (!validateVoltage(voltage));
            
                // Store valid voltage
            voltages.push_back(voltage);
               
                // Add voltage to total
            totalVoltage += voltage;
            
            // Display battery status
            cout << "Status: " << classifyVoltage(voltage) << endl;
        }
    }
    
    // Function to calculate average, minimum and maximum voltages 
    void calculateReport()
    {
        minimumVoltage = voltages[0];
        maximumVoltage = voltages[0];
        
       // Find minimum and maximum voltage
        for (int i = 1; i < voltages.size(); i++)
        {
            if (voltages[i] < minimumVoltage)
                minimumVoltage = voltages[i];

            if (voltages[i] > maximumVoltage)
                maximumVoltage = voltages[i];
        }
        
        // Calculate average voltage
        averageVoltage = totalVoltage / voltages.size();
    }
    
    // Function to display the final report
    void displayReport()
    {
        cout << "\n=====================================\n";
        cout << "         BATTERY REPORT\n";
        cout << "=====================================\n";

        cout << fixed << setprecision(2);

        cout << "Battery ID: " << batteryID << endl;
        cout << "Average Voltage: " << averageVoltage << " V" << endl;
        cout << "Minimum Voltage: " << minimumVoltage << " V" << endl;
        cout << "Maximum Voltage: " << maximumVoltage << " V" << endl;
        
        
    // Display recommendation
        if (averageVoltage < 12.0)
            cout << "Overall Recommendation: Battery Requires Attention\n";
        else
            cout << "Overall Recommendation: Battery is in Good Condition\n";
    }
    
    // Function to save report into a text file
    void saveReportToFile()
    {
        ofstream file("battery_report.txt");

        file << "BATTERY REPORT\n";
        file << "============================\n";
        file << fixed << setprecision(2);
        file << "Battery ID: " << batteryID << endl;
        file << "Average Voltage: " << averageVoltage << " V\n";
        file << "Minimum Voltage: " << minimumVoltage << " V\n";
        file << "Maximum Voltage: " << maximumVoltage << " V\n";

        if (averageVoltage < 12.0)
            file << "Overall Recommendation: Battery Requires Attention\n";
        else
            file << "Overall Recommendation: Battery is in Good Condition\n";
            
            
      // close file
        file.close();
        
        cout << "\nReport saved to battery_report.txt\n";
        cout << "\nThank you for using the Battery Health Monitoring System.\n";
    }
};

 // main function
int main()
{
	// Create an object of BatteryMonitor
    BatteryMonitor battery;

    // call member functions
    battery.setBatteryDetails();
    battery.recordReadings();
    battery.calculateReport();
    battery.displayReport();
    battery.saveReportToFile();

    return 0;
}