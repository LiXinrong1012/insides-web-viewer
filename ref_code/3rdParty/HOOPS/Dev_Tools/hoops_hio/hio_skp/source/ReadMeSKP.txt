
Please follow these steps to build and run the SketchUp importer:

(1) Download the Google SketchUp SDK 7 from
    http://code.google.com/apis/sketchup/docs/downloadsdksubmit.html.

(2) Define the environment variable SKP_SDK_INSTALL_DIR pointing to
    the location where SketchUp SDK is installed.
    For example: SKP_SDK_INSTALL_DIR=C:\Tools\SketchUp7SDk\sdk

(3) Copy the following three binaries from
    <SKP_SDK_INSTALL_DIR>\SkpReader\Binaries\Windows
    to your HOOPS binary directory, <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80
    for a release build, or <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80d for
    a debug build:
       1. SketchUpReader.dll
       2. xerces-c_2_6.dll
      
(4) Make sure that <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80d and/or
    <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80 is in your system path.
 
(5) Build this project using the provided vcproj file.

(6) To run: locate the hoopspartviewer executable in your hoops binary
    directory <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80, and run the executable.
    The SKP HIO module will be available for importing automatically, and
    should show up in the file open menu as a supported file type.
