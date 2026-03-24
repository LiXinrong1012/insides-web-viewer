//
// Copyright (c) 2002 by Tech Soft 3D, LLC.
// The information contained herein is confidential and proprietary to
// Tech Soft 3D, LLC., and considered a trade secret as defined under
// civil and criminal statutes.  Tech Soft 3D shall pursue its civil
// and criminal remedies in the event of unauthorized use or misappropriation
// of its trade secrets.  Use of this information by anyone other than
// authorized employees of Tech Soft 3D, LLC. is granted only under a
// written non-disclosure agreement, expressly prescribing the scope and
// manner of such use.
//
// $Header: /files/homes/master/cvs/hoops_master/Hoops3dStreamCtrl/source/AboutDlg.cpp,v 1.6 2006-08-07 20:38:46 stage Exp $
//
#include "stdafx.h"
#include "AboutDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg


#ifndef _UNICODE
#define CtU(x,y)     (strcpy(y, x), y)
#define UtC(x,y)     (strcpy(y, x), y)
#define UtC2(x,y,z)     (memcpy(y, x,z), y[z] = 0, y)
#else
#define CtU(x,y)     (mbstowcs(y, x, strlen(x) + 1), y)
#define UtC(x,y)     (wcstombs(y, x, 1000), y)
#define UtC2(x,y,z)     (wcstombs(y, x, z), y[z] = 0, y)
#endif

			    


void CAboutDlg::LoadUrl (char *url)
{
	TCHAR	stemp[4096];
        HKEY    html_owner_key        = 0;
        char *  html_owner            = 0;
        HKEY    classes_key            = 0;
        HKEY    browser_root_key    = 0;
        HKEY    browser_path_key    = 0;
        char *    browser_path        = 0;
        DWORD    value_type;
        DWORD    string_size            = 0;
        char error_message[512];
		strcpy(error_message, "Unable to start your internet browser");

        // Try to find the exectuable of the default internet browser.
        // We do this by looking at who "owns" the ".htm" file format.
        if (ERROR_SUCCESS != RegOpenKeyEx(
                                    HKEY_LOCAL_MACHINE,            // handle of open key
                                    _T("software\\classes\\.htm"),     // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &html_owner_key) )             // address of handle of open key
        {
			MessageBox (CtU(error_message, stemp));
        }
        // Determine length of string identifying html_owner.
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                    html_owner_key,                // handle of key to query
                                    _T(""),                            // address of name of value to query
                                    0L,                            // reserved
                                    &value_type,                   // address of buffer for value type
                                    0,                          // address of data buffer
                                    &string_size))                 // address of data buffer size
        {
			MessageBox (CtU(error_message, stemp));
        }
        // then allocate space to hold it.
        else if ((html_owner = new char[string_size]) == 0)
        {
			MessageBox (CtU(error_message, stemp));
        }
        // Determine html_owner
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                    html_owner_key,                // handle of key to query
                                    _T(""),                            // address of name of value to query
                                    0L,                            // reserved
                                    &value_type,                   // address of buffer for value type
                                    (LPBYTE)html_owner,            // address of data buffer
                                    &string_size) )                // address of data buffer size
        {
			MessageBox (CtU(error_message, stemp));
        }
        // Need to find executable associated with html_owner
        // We now generate a path from the html_owner string.
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    HKEY_LOCAL_MACHINE,            // handle of open key
                                    _T("software\\classes"),           // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &classes_key) )                // address of handle of open key
        {
			MessageBox (CtU(error_message, stemp));
        }
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    classes_key,                   // handle of open key
                                    CtU(html_owner, stemp),                    // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &browser_root_key) )           // address of handle of open key
        {
			MessageBox (CtU(error_message, stemp));
        }
        else if (ERROR_SUCCESS != RegOpenKeyEx(
                                    browser_root_key,              // handle of open key
                                    _T("shell\\open\\command"),        // address of name of subkey to open
                                    0L,                            // reserved
                                    KEY_READ,                      // security access mask
                                    &browser_path_key) )           // address of handle of open key
        {
			MessageBox (CtU(error_message, stemp));
        }
        // Determine size of browser_path
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                        browser_path_key,          // handle of key to query
                                        _T(""),                        // address of name of value to query
                                        0L,                        // reserved
                                        &value_type,               // address of buffer for value type
                                        NULL,                      // address of data buffer
                                        &string_size))             // address of data buffer size
        {
			MessageBox (CtU(error_message, stemp));
        }
        else if ((browser_path = new char[string_size]) == 0)
        {
			MessageBox (CtU(error_message, stemp));
        }
        // determine id_string
        else if (ERROR_SUCCESS != RegQueryValueEx(
                                        browser_path_key,          // handle of key to query
                                        _T(""),                        // address of name of value to query
                                        0L,                        // reserved
                                        &value_type,               // address of buffer for value type
                                        (LPBYTE)browser_path,      // address of data buffer
                                        &string_size) )            // address of data buffer size
        {
			MessageBox (CtU(error_message, stemp));
        }
        else
        {
            // In order for this code to be compatible with both MSIE and Netscape,
            //   we are required to use the shell\\open\\command registry key which
            //   contains some extra characters at the end of the string.  Let's
            //   replace the %1 in the string with %s representing our URL

            // Make local copy of Browser Path
			char browser_command[512];
			strcpy(browser_command, browser_path);

 
            // Find %1 and replace it with %s in preparation for sprintf
            char * position = strstr(browser_command,("%1"));

            if (!position)
            {
                // There was no percent sign for this command line,
                // so lets just assume that the URL goes on the end-of-the-line.

                // See if there is a close double-quotes, if so then put the
                // url inside them.

                if (browser_command[strlen(browser_command)-1]  == '"')
				{
					browser_command[strlen(browser_command)-1] = 0;
					strcat(browser_command, url);
					int sl = strlen(browser_command);
					browser_command[sl] = '"';
 					browser_command[sl + 1] = 0;
				}
                 else
				 {
					strcat(browser_command, " ");
					strcat(browser_command, url);
				 }
			}
            else
            {
                // We found a %1 in the command string.
                // Replace it with the url
 				char bc2[512];
				strcpy(bc2, position-2);
				position[0] = 0;
 				strcat(browser_command, url);
				strcat(browser_command, bc2);
            }

            WinExec (browser_command, SW_SHOWNORMAL);
        }

        // We may have had errors, so only close the keys if they were actually opened.
        if (html_owner_key)      RegCloseKey (html_owner_key);
        if (classes_key)         RegCloseKey (classes_key);
        if (browser_root_key)    RegCloseKey (browser_root_key);
        if (browser_path_key)    RegCloseKey (browser_path_key);

        delete []   html_owner;
        delete []   browser_path;
}