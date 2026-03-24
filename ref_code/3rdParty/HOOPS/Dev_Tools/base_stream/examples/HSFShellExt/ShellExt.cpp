
#include "stdafx.h"
#include "resource.h"
#include <initguid.h>
#include "ShellExt.h"
#include "ShellExt_i.c"
#include "ShellExt.h"
#include "HsfShellExt.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_HsfShellExt, CHsfShellExt)
END_OBJECT_MAP()

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance, &LIBID_HSFSHELLEXTLIB);
        DisableThreadLibraryCalls(hInstance);
    }
    else if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return TRUE;    // ok
}

STDAPI DllCanUnloadNow()
{
    return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _Module.GetClassObject(rclsid, riid, ppv);
}


STDAPI DllRegisterServer()
{
CRegKey key;
LONG lRet;

    // On NT/2K, put our extension in the "approved" list.
    if ( 0 == (GetVersion() & 0x80000000) )
        {
        lRet = key.Open ( HKEY_LOCAL_MACHINE, 
                          _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
                          KEY_SET_VALUE );

        if ( ERROR_SUCCESS == lRet )
            {
            lRet = key.SetStringValue ( _T("HSF file icon extension"), 
                                  _T("{100FBABC-9D73-11DE-9433-45DD55D89593E}") );

            key.Close();
            }

        if ( ERROR_SUCCESS != lRet )
            return HRESULT_FROM_WIN32(lRet);
        }

    // registers object, typelib and all interfaces in typelib
    return _Module.RegisterServer(false);
}

STDAPI DllUnregisterServer()
{
CRegKey key;
LONG lRet;

    // On NT/2K, remove our extension from the "approved" list.
    if ( 0 == (GetVersion() & 0x80000000) )
        {
        lRet = key.Open ( HKEY_LOCAL_MACHINE, 
                          _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"),
                          KEY_SET_VALUE );

        if ( ERROR_SUCCESS == lRet )
            {
            key.DeleteValue ( _T("{100FBABC-9D73-11DE-9433-45DD55D89593}") );
            key.Close();
            }
        }

    return _Module.UnregisterServer(false);
}
