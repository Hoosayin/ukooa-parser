#include "UkooaParser.h"
#include "AppSettings.h"
#include "JsonWriter.h"

#include <iostream>
#include <fstream>
#include <thread>

using namespace std::chrono_literals;

UkooaParser* UkooaParser::m_instance{nullptr};

std::string UkooaParser::GetRecordParameter(const std::string &line)
{
    std::sregex_token_iterator iterator{
        line.begin(), line.end(),
        M_REGEX, -1};

    std::vector<std::string> tokens{iterator, {}};

    tokens.erase(
        std::remove_if(
            tokens.begin(),
            tokens.end(),
            [](std::string const &token)
            {
                return token.size() == 0;
            }),
        tokens.end());

    return (tokens.size() > 0) ? tokens[0] : "";
}

UkooaParser::~UkooaParser()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

UkooaParser* UkooaParser::GetInstance()
{
    if (!m_instance)
    {
        m_instance = new UkooaParser();
    }

    return m_instance;
}

void UkooaParser::Parse(
    const std::string& sourceFilename, 
    const std::string& outputFilename)
{
    m_parserThreads.push_back(std::thread(
        [this](
            const std::string sourceFilename, 
            const std::string outputFilename) {
            Ukooa* ukooa = new Ukooa(sourceFilename);
            std::string previousLineName{};

            std::string header{};
            std::string line{};
            std::ifstream inputFile{};
            inputFile.open(sourceFilename);

            AppSettings* settings = AppSettings::GetInstance();

            while (std::getline(inputFile, line))
            {
                switch (line[0])
                {
                case 'H':
                {
                    // Concatenate each header record in a single string.
                    header += line;              
                    break;
                }
                case 'S':
                {
                    DATA_RECORD dataRecord{};

                    // Parse Line Name
                    dataRecord.m_lineName = GetRecordParameter(line.substr(
                        settings->GetLineNamePosition(),
                        settings->GetLineNameLength()));

                    // Parse First Record. 
                    dataRecord.firstCoordinateSet = { 
                        /*SP*/ std::atoi(GetRecordParameter(line.substr(
                            settings->GetSPPosition(),
                            settings->GetSPLength())).c_str()), 
                        /*x*/ std::atof(GetRecordParameter(line.substr(
                            settings->GetXPosition(),
                            settings->GetXLength())).c_str()), 
                        /*y*/ std::atof(GetRecordParameter(line.substr(
                            settings->GetYPosition(),
                            settings->GetYLength())).c_str()) };

                    std::string previousLine{};
                    std::streampos currentPosition{ inputFile.tellg() };
                    
                    // Keep skipping subsequent records with the same Line Name but the last.
                    while (std::getline(inputFile, line))
                    {
                        std::string lineName{ GetRecordParameter(line.substr(
                        settings->GetLineNamePosition(),
                        settings->GetLineNameLength())) };

                        // If the record has the same Line Name,
                        // Store the record and its file position
                        if (lineName == dataRecord.m_lineName)
                        {
                            previousLine = line;
                            currentPosition = inputFile.tellg();
                        }
                        else // If all records with the same Line Name has been iterated.
                        {
                            break;
                        }
                    }

                    // If last record with the same Line Name is stored.
                    if (previousLine != "")
                    {
                        /* Go back one previous record with a new Line Name
                            to read it again in the next iteration. */
                        inputFile.seekg(currentPosition);

                        // Parse last record with the same Line Name.
                        dataRecord.lastCoordinateSet = { 
                            /*SP*/ std::atoi(GetRecordParameter(previousLine.substr(
                                settings->GetSPPosition(),
                                settings->GetSPLength())).c_str()), 
                            /*x*/ std::atof(GetRecordParameter(previousLine.substr(
                                settings->GetXPosition(),
                                settings->GetXLength())).c_str()), 
                            /*y*/ std::atof(GetRecordParameter(previousLine.substr(
                                settings->GetYPosition(),
                                settings->GetYLength())).c_str()) };
                    }

                    ukooa->AddDataRecord(dataRecord);
                    break;
                }
                default:
                    break;
                }
            }

            inputFile.close();

            // Remove extra whitespaces from header.
            std::string::iterator newEnd = std::unique(
                header.begin(), header.end(), 
                [](char first, char second) -> bool {
                    return (first == second) && (first == ' ');
                });

            header.erase(newEnd, header.end());
            ukooa->SetHeader(header);

            std::cout << "Parsed " << 
                sourceFilename << "..." << std::endl;

            JsonWriter::WriteToJSON(ukooa, outputFilename, m_fileLock);

            delete ukooa;
            ukooa = nullptr;

            }, sourceFilename, outputFilename));

    std::cout << "Started a new thread for " << sourceFilename << std::endl;
}

void UkooaParser::Join()
{
    for (auto& thread : m_parserThreads)
    {
        try
        {
            thread.join();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }   
    }
}
