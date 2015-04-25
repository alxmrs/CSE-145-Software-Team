#include "PatientData.h"
#include "error.h"
#include <limits>
#include <iostream>

PatientData :: PatientData () { }

PatientData :: PatientData (std::string filename)
{
    PatientData(filename,1);
}

PatientData :: PatientData (std::string fn, unsigned short int nsegs)
{
    //Initialise file stream
    filename = fn;
    
    std::ifstream file_stream ((char*)filename.c_str());
    std::string   buffer;
    
    //Read number of columns
    file_stream >> buffer;
    if (buffer != "ncols")
        error("ncols not specified in .csv file", -1);
    file_stream >> ncols;
    
    //Read number of rows
    file_stream >> buffer;
    if (buffer != "nrows")
        error("nrows not specified in .csv file", -1);
    file_stream >> nrows;
    
    //Read data length (in seconds)
    file_stream >> buffer;
    if (buffer != "data_length_sec")
        error("data_length_sec not specified in .csv file", -1);
    file_stream >> data_length_sec;
    
    //Read sampling frequency
    file_stream >> buffer;
    if (buffer != "sampling_freq")
        error("sampling_freq not specified in .csv file", -1);
    file_stream >> sampling_freq;
    
    //Set the number of segments (i.e. number of block divisions of .csv)
    num_segments = nsegs;
    curr_segment = 0;
    
    //Read patient data by segment
    data = (short int **) malloc((size_t)(nrows/nsegs)*sizeof(short int *));
    for(int r=0; r<nrows/nsegs; r++)
    {
        data[r] = (short int *) malloc((size_t)ncols*sizeof(short int));
        for(int c=0; c<ncols; c++)
        {
            file_stream >> data[r][c];
        }
    }
}

void PatientData :: next()
{
    curr_segment++;
    
    if (curr_segment >= num_segments)
        error("[.next()] - Data matrix has been traversed.", -1);
    
    std::ifstream file_stream ((char*)filename.c_str());
    goToLine(std::ref(file_stream), 1+CSV_NUM_FIELDS+curr_segment*nrows/num_segments);
    
    for(int r=curr_segment*nrows/num_segments; r<(1+curr_segment*nrows)/num_segments; r++)
    {
        for(int c=0; c<ncols; c++)
            file_stream >> data[r][c];
    }
}

void PatientData :: begin()
{
    curr_segment = 0;;

    std::ifstream file_stream ((char*)filename.c_str());
    goToLine(std::ref(file_stream), 1+CSV_NUM_FIELDS);
    
    for(int r=0; r<nrows/num_segments; r++)
    {
        for(int c=0; c<ncols; c++)
            file_stream >> data[r][c];
    }
}

void PatientData :: print()
{
    std::cout << "Number of columns:        " << ncols << "\n";
    std::cout << "Number of rows:           " << nrows << "\n";
    std::cout << "Data length in seconds:   " << data_length_sec << "\n";
    std::cout << "Sampling frequency in Hz: " << sampling_freq << "\n";
}

unsigned short int PatientData :: getNRows() { return nrows; }
unsigned short int PatientData :: getNCols() { return ncols; }

unsigned short int PatientData :: getDataLengthSec() { return data_length_sec; }
unsigned short int PatientData :: getSamplingFreq()  { return sampling_freq;   }

unsigned short int PatientData :: getNumSegments() { return num_segments; }
unsigned short int PatientData :: getCurrSegment() { return curr_segment; }

inline short int* PatientData :: operator[] (const unsigned int& i)
{
    return data[i];
}

void goToLine(std::ifstream& file, unsigned int line)
{
    file.seekg(std::ios::beg);
    for(int i=0; i < line - 1; ++i)
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}