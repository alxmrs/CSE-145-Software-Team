//
//  patientdata.h
//  Feature Extraction
//
//  Created by Alex Maragakis on 24/04/2015.
//  Copyright (c) 2015 Alex Maragakis. All rights reserved.
//

#ifndef __Feature_Extraction__patientdata__
#define __Feature_Extraction__patientdata__

#include <stdio.h>
#include <string>

typedef struct
{
    unsigned short int data_length_sec;
    unsigned short int sampling_freq;
    unsigned short int nrows, ncols;
    short int ** data;
    
} PatientData;

PatientData* loadCSV(std::string filename);

#endif /* defined(__Feature_Extraction__patientdata__) */
