#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <regex>

class UkooaParser
{
private:
    // Constant Regex that detects whitespaces.
    const std::regex M_REGEX{ R"([\s|]+)" };
    std::mutex m_fileLock{};
    std::mutex m_appSettingsLock{};
    std::vector<std::thread> m_parserThreads{};
    
    static UkooaParser* m_instance;
    
    UkooaParser() = default;
    std::string GetRecordParameter(const std::string& line);

public:
    virtual ~UkooaParser();
    static UkooaParser* GetInstance();

    void Parse(
        const std::string& sourceFilename,
        const std::string& outputFilename);

    void Join();
};