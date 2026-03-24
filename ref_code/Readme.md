## Build Guidelines
- VS2010: **REQUIRED**
- Qt4 (i.e. Qt4.8.4) **REQUIRED**
- qt-vs-addin-1.1.11-opensource **REQUIRED**
- Set the environment variable `QTDIR` to the Qt4 directory (i.e. `C:\Qt\4.8.4`)
- Set Qt VS Addin to use the Qt4 directory

## Troulbe Shooting Tips
- If you get the error that some project binary is missing. Check the dependency settings. Anyway, simply build again might fix the problem.
- Bypass the license check in code. 
    - see: `base/licenses.cpp`

