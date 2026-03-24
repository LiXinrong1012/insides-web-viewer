rem convert a000.ai a000.tiff
rem convert a000.tiff -colorspace rgb -transparent white a000.png

convert a000.png -resize 16x16 a000-16.png
convert a000.png  -resize 32x32 a000-32.png
convert a000.png  -resize 64x64 a000-64.png
convert a000.png  -resize 128x128 a000-128.png
convert a000.png  -resize 256x256 a000-256.png
rem convert a000-256.png a000-128.png a000-64.png a000-32.png a000-16.png -colors 256 ../../../viewer/viewer.ico
convert a000-256.png  ../../../viewer/viewer.ico


pause