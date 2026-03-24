#Author:    Jerry He 
#Time:      2014-10-03
#Purpose:   Convert *.ai files to .png

import os

fileNames=['b001','b002','b003','b004','b005','b006','b007',
        'b008','b009','b010']

for fileName in fileNames:
    b=fileName+'.png'
    os.system('convert '+b+' -resize 32x32 ../'+fileName+'.png')

