Follow these steps to build and run this module

1)Download licensed 'DG_vc8md.zip' and 'DG_NonLibs.zip' package of DgnDirect version DG_2.07.02_Production and unzip them

2)After unzipping 'DG_vc8md.zip' you will notice two directories inside DG_vc8md(exe and lib) and after unzipping 'DG_NonLibs.zip'
you will again notice two directories inside DG_NonLibs(DGNdirect and DWGdirect). 
Copy these four directories in desired location such as "C:\Tools\DgnDirect"

3)Define Environment variable DGNDIRECTV2_SDK_DIR pointing to the above location("C:\Tools\DgnDirect"). Now DgnDirect will contain
four directories(DGNdirect, DWGdirect, exe and lib)

5) Build this project using the provided vcproj file.

6) To run: locate the hoopspartviewer executable in your hoops binarydirectory <HOOPS_INSTALL_DIR>\bin\nt_i386_vc80, 
   and run the executable.
   The DGN HIO module will be available for importing automatically, and should show up in the file open menu as a supported file type(.dgn).
    
Following are three options to import cell header element. Default is SINGLE_ENTITY_CELLHEADER
1)SINGLE_ENTITY_CELLHEADER: if set cell header will be imported as single segment. Level and color of the 
entire cell header will be that of first child having attributes. Use this option if cell header element have all 
children of same color and present on same layer
2)BREAK_CELLHEADER: if set cell header will be imported by iterating its children and as many segment will be created
Use this option if cell header element has children of different color and present on different layer.
And also note that for this option no cell header segment is created instead cell header name is applied as user option
in segment of its child
3)OPT_CELLHEADER: if set cell header will be imported by iterating its children but segment structure will be optimized 
with call to "HC_Optimize_Segment_Tree (".", "reorganize=color")"
Use this option when cell header element has children with different color but present on same layer

