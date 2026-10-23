#include<iostream>
#include<cstring>
using namespace std;

class city {
private:
    char name[30] = {};
    int population = 0;
    int farm = 0;
    int liangshi = 0;
    double tech = 0;
    int campus = 0;
    int library = 0;
    int university = 0;
    int lab = 0;
    char card = '0';

    void calculateTech() {
        tech = 0;

        // 基础建筑加成
        if (campus) tech += 4;
        if (library) tech += 4 + population * 0.5;
        if (university) tech += 8 + population * 1;
        if (lab) {
            if (population <= 10)
                tech += 16 + population;
            else
                tech += 16 + 10 + (population - 10) * 3;
        }

        // 政策卡加成
        if (card == 'A') {
            int buildings = library + university + lab;
            tech += buildings * 10;
        }
        else if (card == 'B') {
            tech += population * 2;
        }
        else if (card == 'C' && liangshi > 0) {
            tech += liangshi;
        }
    }

public:
    void mc() {
        cin >> name >> population >> farm;
        liangshi = farm * 4 - population * 2;
        cin.ignore();

        char command[100];
        while (true) {
            cin.getline(command, 100);
            if (strcmp(command, "quit") == 0) break;

            if (strncmp(command, "farm", 4) == 0) {
                int num;
                if (sscanf_s(command + 5, "%d", &num) == 1) {
                    farm += num;
                    if (farm < 0) farm = 0;
                    liangshi = farm * 4 - population * 2;
                }
            }
            else if (strncmp(command, "population", 10) == 0) {
                int num;
                if (sscanf_s(command + 11, "%d", &num) == 1) {
                    population += num;
                    if (population < 0) population = 0;
                    liangshi = farm * 4 - population * 2;
                }
            }
            else if (strcmp(command, "build campus") == 0) {
                if (!campus) campus = 1;
            }
            else if (strcmp(command, "build library") == 0) {
                if (!library && campus) library = 1;
            }
            else if (strcmp(command, "build university") == 0) {
                if (!university && campus && library) university = 1;
            }
            else if (strcmp(command, "build lab") == 0) {
                if (!lab && campus && library && university) lab = 1;
            }
            else if (strncmp(command, "set", 3) == 0) {
                card = command[4];
            }

            calculateTech();
            print();
        }
    }

    void print() {
        cout << name << " " << population << " " << liangshi << " " << tech << endl;
    }
};

int main() {
    city c;
    c.mc();
    return 0;
}