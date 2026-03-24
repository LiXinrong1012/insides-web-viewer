#Author:    Jerry He 
#Time:      2014-04-10
#

import os

for root, dirs, files in os.walk('C:/Users/Jerry/Desktop/icons'):
    for name in files:
        #os.remove(os.path.join(root, name))
        print name
        if name[name.rfind('.'):]=='.jpg': 
                #cmd='convert '+ name+' -transparent white -resize 15x15 '+name[:name.rfind('.')]+'.png'
                cmd='convert '+ name+' -transparent white '+name[:name.rfind('.')]+'.png'
                print cmd
                os.system(cmd)



