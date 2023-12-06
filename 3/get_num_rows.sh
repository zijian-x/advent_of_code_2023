#!/usr/bin/env bash

sed 's/[^0-9a-zA-Z\.]/\./g; s/^\.\+//; s/\.\+\([0-9]\)/, \1/g; s/\.\+$//' data/input >! nums_from_sed
