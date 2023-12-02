#!/usr/bin/bash

main_dir="$HOME/code/advent_of_code_2023/"

today="${1:-$(date +"%-e")}"
file="$main_dir/$today/data/input"

[[  -z "$AOC_SESSION" ]] && echo "no AOC_SESSION defined" && exit 1
[[  -f "$file" ]] && rm "$file" && echo "old file removed"

curl --cookie "session=$AOC_SESSION" "https://adventofcode.com/2023/day/$today/input" > "$file"
