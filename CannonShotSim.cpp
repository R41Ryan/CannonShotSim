#include <iostream>
#include <cmath>

void clearInputBuffer() {
    std::cin.clear();
    while ((getchar() != '\n')) {}
}

bool stringEquals (char str1[], char str2[])
{
    int str1Length = sizeof(str1)/sizeof(char);
    int str2Length = sizeof(str2)/sizeof(char);

    if (str1Length >= str2Length)
    {
        for (int i = 0; i < str2Length; i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
    } else 
    {
        for (int i = 0; i < str1Length; i++)
        {
            if (str1[i] != str2[i])
            {
                return false;
            }
        }
    }

    return true;
}

void setSettings(float* gravityAcceleration, float* initVelocity, float* height, float* rAngle, int* decimalPlaces)
{
    bool gettingSettings = true;

    while (gettingSettings) 
    {
        std::cout << "\nPlease enter the settings below.\n";

        bool gettingValue = true;

        
        std::cout << "Enter the desired non-zero positive gravitational acceleration in meters per second squared. An invalid input will result in value of 9.81 m/s2\n";
        std::cin >> *gravityAcceleration;

        clearInputBuffer();

        if (*gravityAcceleration <= 0)
        {
            *gravityAcceleration = 9.81;
        }
        
        std::cout << "Enter the non-negative height of the cannon in meters. An invalid input will result in a value of 0 m. \n";
        std::cin >> *height;

        clearInputBuffer();

        if (*height < 0)
        {
            *height = 0;
        }

        float dAngle;
        
        std::cout << "Enter the angle relative to ground in degrees (e.g. 90 degrees points straight up). An invalid input will result in a value of 0 degrees.\n";
        std::cin >> dAngle;

        clearInputBuffer();
        if (dAngle == NULL) {
            dAngle = 0;
        }

        *rAngle = dAngle*3.1416/180;

        gettingValue = true;

        std::cout << "Enter the initial velocity in meters per second. An invalid input will result in a value of 0.\n";
        std::cin >> *initVelocity;

        clearInputBuffer();

        if (*initVelocity == NULL) 
        {
            *initVelocity = 0;
        }

        std::cout << "Enter the desired non-negative precision (Bigger number means more precise). An invalid input will result in 0.\n";
        std::cin >> *decimalPlaces;

        if (*decimalPlaces < 0)
        {
            *decimalPlaces = 0;
        }

        std::cout << "\nThese are the values you have inputted:\n";
        std::cout << "Gravitational acceleration: " << *gravityAcceleration << " m/s2\n";
        std::cout << "Height: " << *height << " m\n";
        std::cout << "Angle (Degrees): " << dAngle << std::endl;
        std::cout << "Angle (Radians): " << *rAngle << " rad\n";
        std::cout << "Initial velocity: " << *initVelocity << " m/s\n";
        std::cout << "Precision: " << *decimalPlaces << "\n";

        std::cout << "\nIs this correct? Enter \"y\" if so.\n";
        char userInput;
        std::cin >> userInput;

        clearInputBuffer();

        if (userInput == 'y') 
        {
            gettingSettings = false;
        }
    }
}

void simulate(float gravityAcceleration, float initVelocity, float height, float rAngle, int decimalPlaces)
{
    float currentHeight = height;
    float maxHeight = height;
    float distance = 0;
    float time = 0;
    float precision = pow(10, decimalPlaces);

    float yVelocity = initVelocity*sin(rAngle);
    float xVelocity = initVelocity*cos(rAngle);

    while (currentHeight >= 0) 
    {
        currentHeight += yVelocity/precision;
        if (currentHeight > maxHeight)
        {
            maxHeight = currentHeight;
        }
        distance += xVelocity/precision;
        time += 1/precision;
        yVelocity -= gravityAcceleration/precision;
    }

    std::cout << "\nMaximum height: " << maxHeight << " m";
    std::cout << "\nHorizontal distance travelled: " << distance << " m";
    std::cout << "\nTime in air: " << time << " s\n";
}

int main() 
{
    std::cout << "Welcome to the Cannon Shot Simulation. Note this simulation does not account for air resistance.\n";

    float gravityAcceleration;
    float initVelocity;
    float height;
    float rAngle;
    int decimalPlaces;

    bool programIsRunning = true;
    int phase = 0;                          // 0 = Choose settings for simulation, 1 = testing and calculating projectile motions

    while (programIsRunning)
    {
        if (phase == 0)
        {
            setSettings(&gravityAcceleration, &initVelocity, &height, &rAngle, &decimalPlaces);
            phase = 1;
        } else 
        {
            simulate(gravityAcceleration, initVelocity, height, rAngle, decimalPlaces);
            char userInput[10];
            std::cout << "\nWould you like to exit the program? (Type \"exit\" if you do)\n";
            std::cin >> userInput;

            clearInputBuffer();
            
            if (stringEquals(userInput, "exit"))
            {
                programIsRunning = false;
            } else 
            {
                phase = 0;
            }
        }
    }
}