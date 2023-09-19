#include "Ukooa.h"
#include <iostream>
#include <fstream>
#include <algorithm>

#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>

Ukooa::Ukooa(
    const std::string& sourceFilename)
{
    m_sourceFileName = sourceFilename;
}

void Ukooa::SetHeader(std::string header)
{
    m_header = header;
}

void Ukooa::AddDataRecord(DATA_RECORD record)
{
    m_dataRecords.push_back(record);
}

std::string Ukooa::GetSourceFilename() const
{
    return m_sourceFileName;
}

std::string Ukooa::GetHeader() const
{
    return m_header;
}

std::vector<DATA_RECORD> Ukooa::GetDataRecords() const
{
    return m_dataRecords;
}
