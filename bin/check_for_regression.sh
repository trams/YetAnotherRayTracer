#!/bin/bash

./bin/cli_render ./scenes/scene3.xml > ./temp/3.txt
diff ./temp/good/3.txt ./temp/3.txt
rm ./temp/3.txt