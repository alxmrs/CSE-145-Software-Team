#include "patientdata.h"
#include "error.h"
#include <fstream>

PatientData* loadCSV(std::string filename)
{
    std::ifstream file_stream ((char*)filename.c_str());
    std::string   buffer;
    
    PatientData * pdata = new PatientData;
    
    file_stream >> buffer;
    
    if (buffer != "ncols")
        error("ncols not specified in .csv file", -1);
    
    file_stream >> pdata->ncols;
    file_stream >> buffer;
    
    if (buffer != "nrows")
        error("nrows not specified in .csv file", -1);
    
    file_stream >> pdata->nrows;
    file_stream >> buffer;
    
    if (buffer != "data_length_sec")
        error("data_length_sec not specified in .csv file", -1);
    
    file_stream >> pdata->data_length_sec;
    file_stream >> buffer;
    
    if (buffer != "sampling_freq")
        error("sampling_freq not specified in .csv file", -1);
    
    file_stream >> pdata->sampling_freq;
    
    pdata->data = (short int **) malloc((size_t)pdata->nrows*sizeof(short int *));
    for(int r=0; r<pdata->nrows; r++)
        pdata->data[r] = (short int *) malloc((size_t)pdata->ncols*sizeof(short int));
    
    for(int r=0; r<pdata->nrows; r++)
    {
        for(int c=0; c<pdata->ncols; c++)
            file_stream >> pdata->data[r][c];
    }

    
    return pdata;
}
