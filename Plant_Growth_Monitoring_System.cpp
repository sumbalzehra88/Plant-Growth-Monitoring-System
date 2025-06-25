/*Project Name: Plant Growth Monitoring System*/

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

//creating a class namely User for User id and password
class User {
private:
    string name;
    string password;

public:
    User() : name("unknown"), password("unknown") {}

    void set_name(string Name) {
        if (Name.empty()) {
            cout << "Name cannot be empty.\n";
            return;
        }
        name = Name;
    }

// function for checking if the password entered is valid

    bool is_valid_password(const string &password) {
        if (password.length() < 9) {
            return false;
        }
        bool uppercase = false, lowercase = false, hasdigit = false, specialchar = false;
        for (char ch : password) {
            if (islower(ch)) lowercase = true;
            else if (isupper(ch)) uppercase = true;
            else if (isdigit(ch)) hasdigit = true;
            else specialchar = true;
        }
        return uppercase && lowercase && hasdigit && specialchar;
    }

// setter method for setting the correct password

    void set_password(string Password) {
        if (!is_valid_password(Password)) {
            cout << "Password must:\n"
                 << "- Be at least 9 characters long\n"
                 << "- Contain at least one uppercase letter\n"
                 << "- Contain at least one lowercase letter\n"
                 << "- Contain at least one digit\n"
                 << "- Contain at least one special character\n";
            return;
        }
        password = Password;
        cout << "The password is set correctly.\n";
    }

    string get_name() {
        return name;
    }

// method to authenticate the details entered by the user from the file user_bio.txt

    bool authenticate(const string &enteredName, const string &enteredPassword) {
        ifstream inFile("user_bio.txt");
        if (!inFile.is_open()) {
            cout << "Failed to open the user data file.\n";
            return false;
        }

        string fileUsername, filePassword;
        while (getline(inFile, fileUsername) && getline(inFile, filePassword)) {
            if (fileUsername == "Name: " + enteredName &&
                filePassword == "Password: " + enteredPassword) {
                inFile.close();
                return true;
            }
        }
        inFile.close();
        cout << "Incorrect username or password. Please try again.\n";
        return false;
    }
};

// creating a class factors that consists of all the factors thar will be considered during the growth of the plant.
class Factors {
private:
    float sunlight;
    float water_level;
    float wind;
    string soil_condition;
    string season;
    float temperature;
    bool fertilizer;

public:
    Factors() : sunlight(0.0), water_level(0.0), wind(0.0), soil_condition("Unknown"),
                temperature(0.0), season("Unknown"), fertilizer(false) {}

    void set_sunlight(float Sunlight) {
        if (Sunlight < 0 || Sunlight > 12) {
            cout << "Sunlight should be between 0 and 12 hours/day.\n";
            return;
        }
        sunlight = Sunlight;
    }

    void set_water_level(float WaterLevel) {
        if (WaterLevel < 10 || WaterLevel > 50) {
            cout << "Water level should be between 10 and 50 liters/week.\n";
            return;
        }
        water_level = WaterLevel;
    }

    void set_wind(float Wind) {
        if (Wind < 0 || Wind > 20) {
            cout << "Wind speed should be between 0 and 20 km/h.\n";
            return;
        }
        wind = Wind;
    }

    void set_soil_condition(string SoilCondition) {
        if (SoilCondition.empty()) {
            cout << "Soil condition cannot be empty.\n";
            return;
        }
        soil_condition = SoilCondition;
    }

    void set_temperature(float Temperature) {
        if (Temperature < 15 || Temperature > 30) {
            cout << "Temperature should be between 15 and 30 °C.\n";
            return;
        }
        temperature = Temperature;
    }

    void set_season(string Season) {
        if (Season.empty()) {
            cout << "Season cannot be empty.\n";
            return;
        }
        season = Season;
    }

    void set_fertilizer(bool Fertilizer) {
        fertilizer = Fertilizer;
    }

    void display() {
        cout << "---------THE FACTORS ARE: ---------------\n";
        cout << "Sunlight: " << sunlight << " hours/day\n";
        cout << "Water Level: " << water_level << " liters/week\n";
        cout << "Wind: " << wind << " km/h\n";
        cout << "Soil Condition: " << soil_condition << "\n";
        cout << "Temperature: " << temperature << " °C\n";
        cout << "Season: " << season << "\n";
        cout << "Fertilizer Used: " << (fertilizer ? "Yes" : "No") << "\n";
    }

// method that sets a criteria to determine the growth of the plant based on the connditions given by the user.
    bool is_plant_growing() {
        int Plant_growth_score = 0;

        if (sunlight >= 6 && sunlight <= 10) Plant_growth_score += 2;
        if (water_level >= 15 && water_level <= 40) Plant_growth_score += 2;
        if (wind <= 15) Plant_growth_score += 1;
        if (soil_condition == "Loamy") Plant_growth_score += 2;
        if (temperature >= 20 && temperature <= 30) Plant_growth_score += 2;

        if (season == "Spring" && sunlight >= 6 && water_level >= 20) Plant_growth_score += 1;
        if (season == "Winter" && temperature < 10) Plant_growth_score -= 1;

        if (fertilizer) Plant_growth_score += 1;

        return Plant_growth_score >= 7;
    }
};

int main() {
    User user;
    Factors plantFactors;
    string choice;

// the user is given the choice to select their action.
    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Sign Up\n";
        cout << "2. Log In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        // if the user signs in a new account is created and the data given by the user is stored in the file.
        if (choice == "1") {
            string userName, userPassword;
            cout << "Enter your name: ";
            getline(cin, userName);
            user.set_name(userName);

            cout << "Create your password: ";
            getline(cin, userPassword);
            user.set_password(userPassword);

            if (userPassword.empty() || !user.is_valid_password(userPassword)) {
                cout << "Sign up failed due to invalid password.\n";
                continue;
            }

            ofstream outFile("user_bio.txt", ios::app);
            if (outFile.is_open()) {
                outFile << "Name: " << userName << "\n";
                outFile << "Password: " << userPassword << "\n";
                outFile.close();
                cout << "Sign-up successful!\n";
            } else {
                cout << "Failed to save user data.\n";
            }
        // if user logs in then the data entered by the user is compared from the data in the file.
        // if the data matches the user successfully logs in.
        } else if (choice == "2") {
            string userName, userPassword;
            cout << "Enter your name: ";
            getline(cin, userName);

            cout << "Enter your password: ";
            getline(cin, userPassword);

            if (user.authenticate(userName, userPassword)) {
                cout << "Login successful! Welcome, " << userName << ".\n";
                // after logging in the user is asked to choose from the given options.
                string subChoice;
                while (true) {
                    cout << "\nPlant Growth Options:\n";
                    cout << "1. Enter Growth Factors\n";
                    cout << "2. Display Growth Factors\n";
                    cout << "3. Check Plant Growth\n";
                    cout << "4. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> subChoice;
                    cin.ignore();
                    // user selects the conditions for the plant growth.
                    if (subChoice == "1") {
                        float sunlight, waterLevel, wind, temperature;
                        string soilCondition, season;
                        bool fertilizer;

                        cout << "Enter sunlight level (hours/day, 0-12): ";
                        cin >> sunlight;
                        plantFactors.set_sunlight(sunlight);

                        cout << "Enter water level (liters/week, 10-50): ";
                        cin >> waterLevel;
                        plantFactors.set_water_level(waterLevel);

                        cout << "Enter wind speed (km/h, 0-20): ";
                        cin >> wind;
                        plantFactors.set_wind(wind);

                        cout << "Enter soil condition (e.g., 'Loamy', 'Sandy'): ";
                        cin.ignore();
                        getline(cin, soilCondition);
                        plantFactors.set_soil_condition(soilCondition);

                        cout << "Enter temperature (°C, 15-30): ";
                        cin >> temperature;
                        plantFactors.set_temperature(temperature);

                        cout << "Enter the current season (e.g., 'Spring', 'Summer'): ";
                        cin.ignore();
                        getline(cin, season);
                        plantFactors.set_season(season);

                        cout << "Did you use fertilizer? (1 for Yes, 0 for No): ";
                        cin >> fertilizer;
                        plantFactors.set_fertilizer(fertilizer);
                    // if user wants to see the factors displayed they can select this choice.
                    } else if (subChoice == "2") {
                        plantFactors.display();
                    // the user chooses 3 if they want to know the current growth status of the plant.
                    } else if (subChoice == "3") {
                        if (plantFactors.is_plant_growing()) {
                            cout << "The plant is growing well! 🌱 -> 🌿 -> 🌳\n";
                        } else {
                            cout << "The plant is not growing well. Adjust the conditions.\n";
                        }
                        // choosing subchoice 4 will cause the user to log off.
                    } else if (subChoice == "4") {
                        cout << "Logging out. Goodbye, " << userName << "!\n";
                        break;
                    } else {
                        cout << "Invalid choice. Please select 1, 2, 3, or 4.\n";
                    }
                }
            } else {
                cout << "Login failed. Please try again.\n";
            }
        // user will exit from the program on selecting this choice.
        } else if (choice == "3") {
            cout << "Exiting the program. Goodbye!\n";
            break;

        } else {
            cout << "Invalid choice. Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}
