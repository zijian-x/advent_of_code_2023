#!/usr/bin/bash

AOC_SESSION='53616c7465645f5fc2a6819309633b4b3ddf7bf7a5964f6531eb8ec5f8611024c8afdfca1083f0def794b41a698c6a10c78c0a77c9896593c119732a06497007'
main_dir="$HOME/code/advent_of_code_2023/"

today="${1:-$(date +"%-e")}"
file="$main_dir/$today/data/input"

[[  -f "$file" ]] && rm "$file" && echo "old file removed"

curl --cookie "session=$AOC_SESSION" "https://adventofcode.com/2023/day/$today/input" > "$file"
