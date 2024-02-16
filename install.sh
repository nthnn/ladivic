#!/bin/bash

if [ $? -eq 0 ]; then
    cp include/*.hpp /usr/local/include/
    ldconfig

    echo "Installation completed successfully."
else
    echo "Error: Compilation failed."
    exit 1
fi
