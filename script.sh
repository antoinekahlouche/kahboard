#!/bin/bash

cd ../qmk_firmware

rm -r ./keyboards/kahboard
cp -r ../kahboard/firmware/kahboard ./keyboards

qmk compile -kb kahboard -km default
rm ../kahboard/firmware/kahboard_default.hex
mv ./kahboard_default.hex ../kahboard/firmware/kahboard.hex

cd ../kahboard