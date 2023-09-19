#!/bin/sh

echo '1. Creating build directory...'
mkdir build

echo '2. Copying configuration and sample UKOOA files...'
cp AppSettings.config survey.Ukooa survey2.Ukooa survey3.Ukooa build/

echo '3. Running cmake configuration...'
cmake -S . -B build
