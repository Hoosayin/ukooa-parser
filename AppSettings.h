#pragma once

#include <string>
#include <mutex>

class AppSettings
{
private:
    unsigned short m_lineNamePosition{};
    unsigned short m_lineNameLength{};
    unsigned short m_spPosition{};
    unsigned short m_spLength{};
    unsigned short m_xPosition{};
    unsigned short m_xLength{};
    unsigned short m_yPosition{};
    unsigned short m_yLength{};

    static AppSettings* m_instance;
    static std::mutex m_instanceLock; // For Thread Safety.

    AppSettings();

    AppSettings(const AppSettings&) = delete;
    AppSettings& operator=(const AppSettings&) = delete;


    void ReadAppSettingsFromConfig();
    
public:
    virtual ~AppSettings();
    static AppSettings* GetInstance();

    unsigned short GetLineNamePosition() const;
    unsigned short GetLineNameLength() const;
    unsigned short GetSPPosition() const;
    unsigned short GetSPLength() const;
    unsigned short GetXPosition() const;
    unsigned short GetXLength() const;
    unsigned short GetYPosition() const;
    unsigned short GetYLength() const;
};