#include "AppSettings.h"
#include <iostream>
#include <fstream>
#include <cstring>

AppSettings* AppSettings::m_instance = nullptr;
std::mutex AppSettings::m_instanceLock;

AppSettings::AppSettings()
{
    // Read AppSettings.config file.
    ReadAppSettingsFromConfig();
}

void AppSettings::ReadAppSettingsFromConfig()
{
    std::string line{};
    std::ifstream configFile{};
    configFile.open("AppSettings.config");

    // Read file line-by-line.
    while (std::getline(configFile, line))
    {
        // Get Setting Name.
        std::string settingName{ std::strtok(line.data(), "=") };

        // Parse Setting value.
        if (settingName == "LINE_NAME_POSITION")
            m_lineNamePosition = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "LINE_NAME_LENGTH")
            m_lineNameLength = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "SP_POSITION")
            m_spPosition = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "SP_LENGTH")
            m_spLength = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "X_POSITION")
            m_xPosition = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "X_LENGTH")
            m_xLength = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "Y_POSITION")
            m_yPosition = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
        else if (settingName == "Y_LENGTH")
            m_yLength = 
                static_cast<unsigned short>(std::atoi(std::strtok(NULL, "=")));
    }
    
    configFile.close();
}

AppSettings::~AppSettings()
{
    if (m_instance)
    {
        delete m_instance;
        m_instance = nullptr;
    }
}

AppSettings* AppSettings::GetInstance()
{
    // Double-Checked Locking
    if (m_instance == nullptr) 
    {
        // Lock Instance Creation
        std::lock_guard<std::mutex> lock(m_instanceLock);
        if (m_instance == nullptr) 
        {
            m_instance = new AppSettings(); // Create the instance if it doesn't exist
        }
    }

    return m_instance;
}

unsigned short AppSettings::GetLineNamePosition() const
{
    return m_lineNamePosition;
}

unsigned short AppSettings::GetLineNameLength() const
{
    return m_lineNameLength;
}

unsigned short AppSettings::GetSPPosition() const
{
    return m_spPosition;
}

unsigned short AppSettings::GetSPLength() const
{
    return m_spLength;
}

unsigned short AppSettings::GetXPosition() const
{
    return m_xPosition;
}

unsigned short AppSettings::GetXLength() const
{
    return m_xLength;
}

unsigned short AppSettings::GetYPosition() const
{
    return m_yPosition;
}

unsigned short AppSettings::GetYLength() const
{
    return m_yLength;
}
