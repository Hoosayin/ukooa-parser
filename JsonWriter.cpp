#include "JsonWriter.h"
#include "UkooaParser.h"

#include <json/json.h>
#include <json/value.h>
#include <json/writer.h>

#include <fstream>
#include <iostream>

void JsonWriter::WriteToJSON(
    Ukooa *const ukooa, 
    const std::string &outputFilename, 
    std::mutex &fileLock)
{
    std::string ukooaFilesAttribute{ "ukooa-files" };
    Json::Value json{};
    Json::Reader reader{};

    fileLock.lock();

    std::ifstream inputFile{};
    inputFile.open(outputFilename);
    reader.parse(inputFile, json);
    inputFile.close();

    fileLock.unlock();

    Json::Value jsonUkooaArray{ json.isMember(ukooaFilesAttribute) ? 
        json[ukooaFilesAttribute] : Json::arrayValue };

    Json::Value jsonUkooa{};

    jsonUkooa["source-filename"] = Json::Value(ukooa->GetSourceFilename());

    Json::Value data{};
    data["header"] = Json::Value(ukooa->GetHeader());

    Json::Value jsonDataRecords{};

    for (const auto& dataRecord : ukooa->GetDataRecords())
    {
        const SOURCE_COORDINATE_SET& firstCoordinateSet = 
            dataRecord.firstCoordinateSet;

        const SOURCE_COORDINATE_SET& secondCoordinateSet = 
            dataRecord.lastCoordinateSet;

        Json::Value jsonSP{};

        jsonSP["startSP"] = Json::Value(firstCoordinateSet.m_sp);
        jsonSP["startX"] = Json::Value(firstCoordinateSet.m_x);
        jsonSP["startY"] = Json::Value(firstCoordinateSet.m_y);
        jsonSP["endSP"] = Json::Value(secondCoordinateSet.m_sp);
        jsonSP["endX"] = Json::Value(secondCoordinateSet.m_x);
        jsonSP["endY"] = Json::Value(secondCoordinateSet.m_y);

        jsonDataRecords[dataRecord.m_lineName] = jsonSP;
    }

    data["records"] = jsonDataRecords;
    jsonUkooa["data"] = data;

    jsonUkooaArray.append(jsonUkooa);
    
    std::cout << "Appended JSON UKOOA object for " << 
        ukooa->GetSourceFilename() << "..." << std::endl;

    json[ukooaFilesAttribute] = jsonUkooaArray;

    fileLock.lock();

    std::ofstream outputFile{};
    outputFile.open(outputFilename);

    // Write Styled JSON string in the file.
    Json::StyledWriter writer{};
    outputFile << writer.write(json);
    outputFile.close();

    fileLock.unlock();
}
