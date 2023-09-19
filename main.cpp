#include <iostream>
#include <string>
#include <thread>
#include <unistd.h>

#include "UkooaParser.h"

int main(int argc, char* argv[])
{
    pid_t pid = getpid();

    std::vector<std::string> filenames{};
    std::string outputFilename{ "survey.json" };

    // Print program name.
    std::cout << argv[0] << " is running with process ID: " << pid << "..." << std::endl;

    if (argc == 1) // No arguments. Works as previous. 
    {
        // If Command-Line Arguments are not provided, use default filename.
        filenames.push_back("survey.Ukooa");         
    }
    else if (argc >= 3) // Parse Command-Line Arguments.
    {
        for (int i = 1; i < argc; ++i)
        {
            std::string option = argv[i];

            if (option == "-s")
            {
                // Keep on processing subsequent arguments for source filenames.
                while (++i < argc)
                    filenames.push_back(argv[i]);            
            }
            else if (option == "-o" && 
                (i + 1) < argc)
            {
                outputFilename = argv[++i];
            }
        }
    }

    // Get instances of UkooaParser.
    UkooaParser* parser = UkooaParser::GetInstance();

    // Parse each file in a separate thread. 
    for (auto& filename : filenames)
        parser->Parse(filename.data(), outputFilename.data());

    // Wait until all threads have finished processing.
    parser->Join();

    std::cout << outputFilename << 
        " has been written successfully." << std::endl;

    return EXIT_SUCCESS;
}