#!/bin/bash

mkdir data

if [ ! -f data/airports.dat ]; then
    echo "`airports.dat` not found. Fetching from github..."
    wget -O data/airports.dat https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat
fi
if [ ! -f data/routes.dat ]; then
    echo "`routes.dat` not found. Fetching from github..."
    wget -O data/routes.dat https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat
fi

echo "All files fetched successfully."
