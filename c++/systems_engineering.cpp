//
//  systems_engineering.cpp
//  systems_engineering
//
//  Created by Esmira Abdullaieva on 09.05.2021.
//

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

// система живлення
class PowerSupplySystem
{
private:
    string wire_length = "1.5 meters";
    string power = "2.4-3 kW";
    string power_supply = "230 V";
    bool state = false; // вимкнуто за замовчуванням
public:
    
    bool get_state() {
        return this->state;
    }
    
    void turn_on() {
        cout << "# IRON ON #" << endl;
        this->state = true;
    }
    
    void turn_off(){
        cout << "# IRON OFF #" << endl;
        this->state = false;
    }
};

// система регулювання температури
class TemperatureControlSystem
{
private:
    string diametr = "4 cm";
    int temperature_value = 90;
public:
    
    int get_temperature() {
        return this->temperature_value;
    }
    
    void set_temperature() {
        int min_temp = 75;
        int max_temp = 205;
        char ans;
        cout << "* set temperature (u)p or (d)own:" << endl;
        cin >> ans;
        switch (ans) {
            case 'u':
                if (temperature_value <= max_temp)
                    this->temperature_value+=10;
                else
                    cout << "x it is maximum value of temperature x" << endl;
                break;
            case 'd':
                if (temperature_value >= min_temp)
                    this->temperature_value-=10;
                
                else
                    cout << "x it is minimum value of temperature x" << endl;
                break;
            default:
                cout << "Wrong input" <<endl;
                break;
        }
    }
};

// система збереження води
class WaterStorageSystem
{
private:
    int water_quantity = 90;
    int max_volume = 400;
    int min_volume = 100;
public:
    
    int get_water_state() {
        return this->water_quantity;
    }
    
    void add_water() {
        char ans;
        cout << "* minimun water quantity: " << this->min_volume << endl;
        cout << "* add (y)es/(n)o:" << endl;
        cout << ">> ";
        cin >> ans;
        switch (ans) {
            case 'y':
                if (water_quantity < min_volume || water_quantity < max_volume) {
                    this->water_quantity+=(max_volume-water_quantity);
                    cout << "! water added !" << endl;
                }
                else
                    cout << "! you have enough water !" << endl;
                break;
            case 'n':
                if(water_quantity <= max_volume && water_quantity >= min_volume)
                    cout << "! okay !" << endl;
                else {
                    cout << "! you need water !" << endl;
                }
                break;
            default:
                cout << "Wrong input" <<endl;
                break;
        }
    }

    void water_minus() {
            this->water_quantity-=5;
    }
};

// нагривний елемент
class HeatingElement
{
private:
    string size = "17 cm";
    bool state = false; // за замовчуванням нагрівальний елемент холодний
public:

    bool get_state() {
        return this->state;
    }
    void start_warm(TemperatureControlSystem& temperature) {
        cout << "* heating element -> " << temperature.get_temperature() << "*C" << endl;
        this->state = true;
    }
};

// підошва
class Sole
{
private:
    string size = "20 cm";
    string material = "ceramics";
    bool state = false;
public:
    bool get_state(HeatingElement& he) {
        cout << "* sole -> warmed up" << endl;
        return this->state=he.get_state();
    }
};

class WarmingSystem
{
    Sole sole;
    HeatingElement he;
public:
    void warm(TemperatureControlSystem& temperature) {
        he.start_warm(temperature);
        sleep(2);
        sole.get_state(he);
    }
};

// система подачі пару
class SteamSupplySystem
{
    //ChamberForWater chamber;
private:
    string button_size = "1 cm";
    bool steam_state = false; // за замовчування кнопку не натиснуто
    string steam_boost = "90 - 210 g/min";
    bool water_steam = false;
    HeatingElement heating_element;
public:
    
    bool get_state() {
        return this->steam_state;
    }
    
    void make_steam(WaterStorageSystem& chamber) {
        if (chamber.get_water_state() >= 100){
            cout << "* water -> steam" << endl;
            water_steam = true;
        }
        else
            cout << "x not enough water x" << endl;
    }
    
    // настиснути кнопку для подачі пару
    void StartSteamSupply(WaterStorageSystem& chamber) {
        this->make_steam(chamber);
        if (water_steam == true){
            cout << "! steam in progress !" << endl;
            chamber.water_minus();
            this->steam_state = true;
        }
        else {}
    }
    
    // настиснути кнопку для завершення подачі пару
    void StopSteamSupply() {
        cout << "! steam finished !" << endl;
        this->steam_state = false;
    }
    
};

// праска
class Iron
{
    PowerSupplySystem power;
    SteamSupplySystem steam;
    TemperatureControlSystem temp;
    WarmingSystem warming;
    WaterStorageSystem water;
    bool state = false;
public:
    
    void turn_on() {
        this->power.turn_on();
        this->warming.warm(temp);
    }
    
    void turn_off() {
        this->power.turn_off();
    }
    
    void info() {
        //system("CLS");
        cout << "------------------------" << endl;
        cout << "|" << " Ironing process   " << "|" << this->state << "|" << endl;
        cout << "|" << " Temperature       " << "|" << this->temp.get_temperature() << "|" << endl;
        cout << "|" << " Water quanity     " << "|" << this->water.get_water_state() << "|" << endl;
        cout << "|" << " Steam state       " << "|" << this->steam.get_state() << "|" << endl;
        cout << "------------------------" << endl;
        
    }
    void ironing() {
        int flag = 1;
        while (flag)
        {
            int ans;
            cout << "\n----------Iron----------" << endl;
            info();
            cout << "0 - Start ironing" << endl;
            cout << "1 - Set temperature" << endl;
            cout << "2 - Add water" << endl;
            cout << "3 - Use steam" << endl;
            cout << "4 - Stop use steam" << endl;
            cout << "5 - The end" << endl;
            cout << ">> ";
            cin >> ans;
            switch (ans) {
                case 0:
                    if (state == false){
                        this->state = true;
                        cout << "...ironing..." << endl;
                    }
                    else
                        cout << "! already ironing !" << endl;
                    break;
                case 1:
                    this->temp.set_temperature();
                    this->warming.warm(temp);
                    break;
                case 2:
                    if (state == false){
                        this->water.add_water();
                        this->water.get_water_state();
                    }
                    else
                        cout << "! stop ironing first !" << endl;
                    break;
                case 3:
                    if (state == true){
                        if (steam.get_state() == false) {
                            this->steam.StartSteamSupply(water);
                        }
                        else
                            cout << "! steam already in progress !" << endl;
                    }
                        else
                            cout << "! start ironing first !" << endl;
                    break;
                case 4:
                    if(steam.get_state() == true) {
                        this->steam.StopSteamSupply();
                    }
                    else
                        cout << "! no steam used !" << endl;
                    break;
              case 5:
                    if (state == true) {
                    char enter;
                    cout << "* (f)inish or (c)hange parameters?" << endl;
                    cout << ">> ";
                    cin >> enter;
                    switch (enter) {
                            case 'f':
                            if (steam.get_state() == true) {
                                    this->steam.StopSteamSupply();
                            }
                                cout << "! stop ironing !" << endl;
                                state = false;
                                flag = 0;
                                break;
                            case 'c':
                            if (steam.get_state() == true){
                                    this->steam.StopSteamSupply();
                            }
                                cout << "! stop ironing !" << endl;
                                state = false;
                                break;
                            default:
                                cout << "Wrong input!" << endl;
                                break;
                            
                            }
                    }
                    else {
                        state = false;
                        flag = 0;
                    }
                  break;
                default:
                    cout << "Wrong input!" << endl;
                break;
            }
        }
    }
    
};

class User
{
private:
    string name = "Esmira";
public:
    void turn_on(Iron& iron) {
        iron.turn_on();
    }
    void turn_off(Iron& iron) {
        iron.turn_off();
    }
    void Ironing(Iron& iron)
    {
        cout << "            Iron" << endl;
        int choice;
        bool flag = 1;
        cout << "* insert plug into the socket" << endl;
        cout << "      enter '1' to do it!" << endl;
        cout << ">> ";
        cin >> choice;
        if (choice != 1)
        {
            cout << "Try one more time!" << endl;
            return;
        }
        else
        {
            turn_on(iron);
        }
        while(flag)
        {
            iron.info();
            cout << endl;
            cout << "* what's next?" << endl;
            cout << "1 - Take Iron" << endl;
            cout << "2 - Switch OFF" << endl;
            cout << ">> ";
            cin >> choice;
            switch (choice) {
                case 1:
                    iron.ironing();
                    break;
                case 2:
                    turn_off(iron);
                    flag = 0;
                    break;
                default:
                    cout << "Wrong input" << endl;
            }
        }
    }
};

int main()
{
    Iron iron;
    User Me;
    Me.Ironing(iron);
    return 0;
}
