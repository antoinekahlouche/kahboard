#!/bin/bash

cd ../qmk_firmware

rm -r ./keyboards/kahboard
cp -r ../kahboard/firmware/kahboard ./keyboards

qmk compile -kb kahboard -km default
rm ../kahboard/firmware/kahboard_default.hex
mv ./kahboard_default.hex ../kahboard/firmware/kahboard.hex

qmk compile -kb kahboard -km mac
rm ../kahboard/firmware/kahboard_mac.hex
mv ./kahboard_mac.hex ../kahboard/firmware/kahboard_mac.hex

qmk compile -kb kahboard -km win
rm ../kahboard/firmware/kahboard_win.hex
mv ./kahboard_win.hex ../kahboard/firmware/kahboard_win.hex

cd ../kahboard