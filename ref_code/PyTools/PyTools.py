# coding=utf-8

# 用于创建Tags版本
# @author   Jerry He
# @date     2015.1.16

from shutil import *
import os


def copyFile(src,dst):
    if os.path.exists(src):
        copy2(src,dst)
    else:
        print 'File: ',src,' does not exist.'

os.chdir('../win32/release')
print os.getcwd()

outputRoot="D:/out/"
outputDir="D:/out/bin/"
dirlist=[outputRoot,outputDir,outputDir+'plugins',
         outputDir+'settings',outputDir+'plugins/sqldrivers',
         outputDir+'plugins/imageformats',
         outputRoot+'doc']

for o in dirlist:
    if not os.path.exists(o):
        os.mkdir(o)
        

files=['base.dll','Basic.dll','coresps.dll','edcore.dll','edhelp.dll',
       'edparse.dll','edui.dll','hoops_mvo_mgk1900_vc10.dll',
       'hoops_stream1900_vc10.dll','hoops1900_vc10.dll','hp_bridge1900_210_vc10.dll',
       'inslic.dll','log4qt-0.3.dll','msvcp100.dll',
       'msvcr100.dll','mtsearchengine.dll','osg74-osg.dll','ot11-OpenThreads.dll',
       'Parameter.dll','pp_xml.dll','precore.dll',
       'prept.dll','preui.dll','pskernel.dll','qscintilla2.dll',
       'QtCLucene4.dll','QtCore4.dll','QtGui4.dll',
       'QtHelp4.dll','QtNetwork4.dll','qtnribbon3.dll',
       'QtSql4.dll','QtWebKit4.dll','QtXml4.dll',
       'spsIn.dll','updateConfig.xml','xerces-c_3_1.dll','WinDiff.Exe',
       'viewer.exe','update.exe','editor.exe','assistant.exe',
       'readme.txt']

# 复制Release下的文件
for f in files:
    copy2(f,outputDir+f)

files=['plugins/prev3d.dll',
       'plugins/prevtc.dll',
       'plugins/prevtt.dll',
       'plugins/prevttm.dll',
       'plugins/importtdyresult.dll',
       'plugins/importtdyeigresult.dll',
       'plugins/importtdy2.dll',
       'plugins/exsecsurf.dll',
       'plugins/sqldrivers/qsqlite4.dll',
       'plugins/imageformats/qjpeg4.dll',
       'settings/insides-viewer.ini',
       'settings/configuration.xml',
       'settings/ins.xml',
       'settings/insides-viewer-curve-completion.ini',
       'settings/parameters.xml',
       'settings/prevtc.ini']

for f in files:
    copy2(f,outputDir+f)
    



