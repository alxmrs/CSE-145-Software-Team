#include "FeatureExtraction_main.h"
#include "PatientData.h"

const double freqband_delta[] = {0.1, 4  };
const double freqband_theta[] = {4,   8  };
const double freqband_alpha[] = {8,   12 };
const double freqband_beta[]  = {12,  30 };
const double freqband_lgam[]  = {30,  70 };
const double freqband_hgam[]  = {70,  180};

PatientData pdata;

int main (int argc, const char* argv[])
{
    pdata = PatientData("p1_iis1.csv");
    pdata.print();
    
    return 0;
}