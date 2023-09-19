#pragma once 

#include <string>
#include <mutex>

#include "Ukooa.h"

class JsonWriter
{
public:
    static void WriteToJSON(
        Ukooa* const ukooa,
        const std::string& outputFilename,
        std::mutex& fileLock);
};