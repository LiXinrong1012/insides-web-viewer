#Author:    Jerry He 
#Time:      2014-10-03
#Purpose:   Convert *.ai files to .png

import os

fileNames=['a001','a002','a003','a004','a005','a006','a007',
        'a008','a009','a010','a011','a012','a013','a014','a015',
        'a016','a017','a018','a019','a020','a021','a022','a023']

for fileName in fileNames:
    b=fileName+'-01.png'
    os.system('convert '+b+' -resize 32x32 ../'+fileName+'-32.png')
    os.system('convert '+b+' -resize 16x16 ../'+fileName+'-16.png')

