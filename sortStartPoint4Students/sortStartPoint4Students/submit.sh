#!/bin/bash

echo "Geef aub jullie namen, zonder spaties (bijv: FreddyHurkmans_RonaldMarcelis)."
echo -n "Als je alleen werkt dan geef je alleen je eigen naam: (bijv. FreddyHurkmans): "
read namen

echo -n "Geef aub jullie/je klas (T21, T22, T21t of T21m): "
read klas

tarbal="${namen}_${klas}.tgz"

make clean
tar czf ${tarbal} code test

echo -e "\nLever aub de file: ${tarbal} in Canvas in\n"
