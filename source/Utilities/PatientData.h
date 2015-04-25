//
//  PatientData.h
//  Feature Extraction
//
//  Created by Alex Maragakis on 25/04/2015.
//  Copyright (c) 2015 Alex Maragakis. All rights reserved.
//

#ifndef __Feature_Extraction__PatientData__
#define __Feature_Extraction__PatientData__

#include <stdio.h>
#include <string>
#include <fstream>

#define CSV_NUM_FIELDS 4

class PatientData
{
private:
    std :: string filename;
    
    unsigned short int data_length_sec;
    unsigned short int sampling_freq;
    unsigned short int num_segments, curr_segment;
    unsigned int nrows, ncols;
    
    short int ** data;
    
public:
    PatientData();
    PatientData(std::string);
    PatientData(std::string, unsigned short int);
    
    void next();
    void begin();
    void print();
    
    unsigned short int getNRows();
    unsigned short int getNCols();
    unsigned short int getDataLengthSec();
    unsigned short int getSamplingFreq();
    unsigned short int getNumSegments();
    unsigned short int getCurrSegment();
    
    inline short int* operator[] (const unsigned int&);
};

void goToLine(std::ifstream&, unsigned int);

#endif /* defined(__Feature_Extraction__PatientData__) */
