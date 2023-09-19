# UKOOA Parser

**ukooa-parser** is a C++ console application designed to parse UKOOA text files and extract specific information for each record. The extracted data includes the First and Last SP (Starting Point), First and Last X coordinate, and First and Last Y coordinate. This information is then appended to a specified JSON file. The project utilizes the jsoncpp open-source library as a Git submodule for reading and writing JSON output files. Configuration settings for data extraction are defined in the `AppSettings.config` file.

## What is UKOOA?

**UKOOA**, which stands for United Kingdom Offshore Operators Association, is an industry organization that provides standards and guidelines for the UK offshore oil and gas industry.

## Features

- Parses UKOOA text files.
- Extracts First and Last SP, X coordinate, and Y coordinate for each record.
- Appends the extracted information to a specified JSON file.

## Command-line Arguments

The program accepts the following command-line arguments:

- `-s` followed by the names of input UKOOA files separated by spaces.
- `-o` followed by the name of the output JSON file.

## Configuration

**AppSettings.config** is read once, and a Singleton pattern is used to make the configuration settings available to other classes.

## Building and Running

### Configure (Modify CMake Generator as Needed)

For Linux:

```bash
./configure.sh
```

For Windows:

```bash
configure.bat
```

### Build (Make Appropriate Generator Choice)

For Linux:

```bash
./build.sh
```

For Windows:

```bash
build.bat
```

### Run

For Linux:

```bash
./run.sh
```

For Windows:

```bash
run.bat
```

Feel free to configure, build, and run the project as needed for your environment.

**Note:** Please ensure that you have the necessary dependencies, including CMake, properly set up in your environment before building and running the project.
