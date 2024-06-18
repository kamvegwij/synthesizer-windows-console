#include <iostream>
#include "hardwareNoiseManager.h"
#include <vector>
using namespace std;

//VARS
atomic<double> dfrequencyOutput = 0.0;

double MakeNoise(double dTime)
{
    double dsoundOutput = 1.0 * sin(dfrequencyOutput * 2.0 * 3.14159 * dTime) + sin((dfrequencyOutput + 20.0) * 2.0 * 3.14159 * dTime);
    return dsoundOutput * 0.4;

    /*if (dsoundOutput > 0.0)
        return 0.2;
    else
        return -0.2;
        */

    //we can use other periodic functions to create different sounds.
    //sine wave. returns frequency in hz. 
    //(2*PI) converts this value to angular velocity 
    //sine waves don't take hz values.

    return dsoundOutput; //note "A4"
}

int main()
{
    wcout << "Synthesizer Tutorial Pt.1" << endl;
    wcout << "Keys: " << endl << "C->Z C#->S D->X D#->C E->F E#->V F#->G G->B G#->N A->J A#_>M B->K" << endl;
    //Get Sound Hardware:
    vector<wstring> devices = olcNoiseMaker<short>::Enumerate();

    //Display:
    for (auto d : devices) wcout << "Found Output Devices:" << d << endl;

    //Create Sound Machine:
    olcNoiseMaker<short> sound(devices[0], 44100, 1, 8, 512); //char-8bit int-32bit short-16bit SYSTEM.

    //Link Noise Function To Sound Machine
    sound.SetUserFunction(MakeNoise);
    
    double dbassFrequency = 110.0;
    double d12thRootOf2 = pow(2.0, 1.0 / 12.0);
    short sSemiTone = 0;

    while (1)
    {
        //Simulate piano keyboard with keys:
        bool bkeyPressed = false;
        for (int i = 0; i < 15; i++)
        {
            if (GetAsyncKeyState((unsigned char)("ZSXCFVGBNJMK\xbcL\xbe"[i])) & 0x8000)
            {
                dfrequencyOutput = dbassFrequency * pow(d12thRootOf2, i);
                bkeyPressed = true;
            }
        }
        if (!bkeyPressed)
        {
            dfrequencyOutput = 0.0;
        }
        
    }
    return 0;
}

