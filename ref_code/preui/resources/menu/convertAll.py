#Author:    Jerry He 
#Time:      2014-10-03
#Purpose:   Convert *.ai files to .png

import os

fileNames=['a001','a002','a003',
        'a004','a005','a006','a007',
        'a008','a009','a010','a011',
        'a012','a013','a014','a015',
        'a016','a017','a018','a019',
        'a020','a021','a022','a023',
        'a024','a025','a026','a027',
        'a028','a029','a030','a031',
        'a033','a034','a035','a036',
        'a037','a038','a039','a040',
        'a041','a042']

for fileName in fileNames:
    a=fileName+'.ai'
    b=fileName+'.png'
    os.system('convert '+a+' tmp.tiff')
    os.system('convert tmp.tiff -colorspace rgb -transparent white '+fileName+'.png')
    os.system('convert '+b+' -resize 32x32 '+fileName+'x32x32.png')
    os.system('convert '+b+' -resize 16x16 '+fileName+'x16x16.png')

