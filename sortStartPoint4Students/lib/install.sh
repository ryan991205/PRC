#!/bin/bash

if g++ --version | head -n 1 | grep -q " 4."
then
    version="4"
else
    version="5+"
fi

if echo "$(uname -m)" | grep -q "64"
# The "-q" option to grep suppressed output.
then
    nrBits="64"
    libs="$1${nrBits}bit_${version}/*"
    destination="/usr/lib/x86_64-linux-gnu"
else
    nrBits="32"
    libs="$1${nrBits}bit/*"
    destination="/usr/lib"
fi

echo -e "\nYou have a ${nrBits} bit system and g++ version ${version}, I'm about to install the correct libs. You might need to enter your password!\n"
if sudo cp -a ${libs} ${destination}
then
    echo -e "\nInstalling libraries succeeded!\n"
else
    echo -e "\nInstalling libraries failed! Please copy them manually:\nsudo cp -a ${libs} /usr/local/lib\n"
    exit 1
fi

