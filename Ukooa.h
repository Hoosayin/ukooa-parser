#pragma once

#include <string>
#include <vector>
#include <regex>

struct SOURCE_COORDINATE_SET
{
    int m_sp{};
    double m_x{};
    double m_y{};
};

struct DATA_RECORD
{
    std::string m_lineName{};
    SOURCE_COORDINATE_SET firstCoordinateSet{};
    SOURCE_COORDINATE_SET lastCoordinateSet{};

    DATA_RECORD() = default;
    virtual ~DATA_RECORD() = default;
};

class Ukooa
{
private:
    std::string m_sourceFileName{};
    std::string m_header{};
    std::vector<DATA_RECORD> m_dataRecords{};

public:
    Ukooa() = delete;
    Ukooa(const std::string& sourceFilename);
    virtual ~Ukooa() = default;

    void SetHeader(std::string header);
    void AddDataRecord(DATA_RECORD record);

    std::string GetSourceFilename() const;
    std::string GetHeader() const;
    std::vector<DATA_RECORD> GetDataRecords() const;
};