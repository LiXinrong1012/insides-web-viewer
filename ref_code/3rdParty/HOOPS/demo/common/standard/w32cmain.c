/*
 * Copyright (c) 1998 by Tech Soft 3D, LLC.
 * The information contained herein is confidential and proprietary to
 * Tech Soft 3D, LLC., and considered a trade secret as defined under
 * civil and criminal statutes.  Tech Soft 3D shall pursue its civil
 * and criminal remedies in the event of unauthorized use or misappropriation
 * of its trade secrets.  Use of this information by anyone other than
 * authorized employees of Tech Soft 3D, LLC. is granted only under a
 * written non-disclosure agreement, expressly prescribing the scope and
 * manner of such use.
 *
 * $Id: w32cmain.c,v 1.10 2011-01-12 00:06:02 conor Exp $
 */

#ifdef WINDOWS_SYSTEM

#include <windows.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include "hc.h"

#define stack
#define global
#define local static


#   define ARGC	__argc
#   define ARGV	__argv
#   define ENVP _environ


local HANDLE	global_instance;
local HWND	global_dialog = (HWND) 0;


global INT_PTR PASCAL PrintfDlgProc (
    stack	HWND		hDlg,
    stack	UINT		iMessage,
    stack	WPARAM		wParam,
    stack	LPARAM		lParam) {

    switch (iMessage) {
	case WM_INITDIALOG: {
	    /*
	     * Because of a "bug" in windows 95 we have to set the text here
	     * rather than in the createdialogindirect as you would expect
	     *
	     */
	    SetWindowText (hDlg, "Printf Dialog");
	    SendDlgItemMessage (hDlg, IDCANCEL, WM_SETTEXT, 0, (LPARAM) "&HIDE");
	    return TRUE;
	}

	case WM_COMMAND: {
	    switch (wParam) {
		case IDCANCEL: {
		    ShowWindow (hDlg, SW_HIDE);
		    return TRUE;
		}

		/* add other window cases here */
		default: {
		    return FALSE;
		}
	    }
	}

	/* add other iMessage cases here */
	default: {
	    /*
	     * lParam is really unreferenced; however, if we use the
	     * define UNREFERENCED(param) ((void)(param)) trick, we get
	     * an "expression has no side-effects" warning. To get rid
	     * of the "formal parameter is unreferenced" warning, we
	     * simply do a dummy test here.
	     */
	    if (lParam == 0L)
		lParam++;
	    return FALSE;
	}
    }
}


/*
 * The following routine emulates printf by putting text into an edit dialog.
 * Output text is slightly transformed because we must translate "\n" into
 * a "\r\n" sequence in order to get line breaks in the dialog. So, "\n" alone
 * will have the effect of breaking a line, as will "\r\n". However, a "\r"
 * alone will be ignored.
 */

#define PRINTF_BUFSIZE 1024
#define DIALOG_EDIT_ITEM 101

#if _MSC_VER < 1400

#ifndef _DLL
global int __cdecl printf (
	stack	const char		*format,
	...) {
	stack	va_list			argptr;
	stack	int			text_length;
	stack	char			new_text[PRINTF_BUFSIZE];

	if (global_dialog == (HWND)0) {
	    stack	char			ptr_dialog_template[
						    sizeof(DLGTEMPLATE) + 2 *
						    sizeof(DLGITEMTEMPLATE) +
						    sizeof(int) * 100];
	    stack	DLGTEMPLATE		*dialog_template;
	    stack	DLGITEMTEMPLATE		*dialog_item_template;
	    stack	LPWORD			ptr_misc;
	    stack	HDC			handle_info_dc;
	    stack	int			screen_size_x,
						screen_size_y;
	    stack	LONG			dialog_base_units;

	    /*
	     * We need to compute the size and postition of the
	     * error box based on some system information
	     * Since we are in the error routine we should not
	     * rely on the stored information
	     */

	    handle_info_dc = GetDC (GetDesktopWindow());
	    screen_size_x = GetDeviceCaps (handle_info_dc, HORZRES);
	    screen_size_y = GetDeviceCaps (handle_info_dc, VERTRES);
	    ReleaseDC (GetDesktopWindow(), handle_info_dc);

	    dialog_base_units = GetDialogBaseUnits ();

	    dialog_template = (DLGTEMPLATE *)ptr_dialog_template;

	    dialog_template->style = DS_SYSMODAL | DS_MODALFRAME | WS_POPUP |
				     WS_VISIBLE | WS_CAPTION | DS_SETFONT;
	    dialog_template->dwExtendedStyle = WS_EX_DLGMODALFRAME | WS_EX_TOPMOST;
	    dialog_template->cdit = 2;
	    dialog_template->x = (screen_size_x / 4 * 4) /
				 LOWORD (dialog_base_units);
	    dialog_template->y = (screen_size_y / 4 * 8) /
				 HIWORD (dialog_base_units);
	    dialog_template->cx = (screen_size_x / 2 * 4) /
				 LOWORD (dialog_base_units);
	    dialog_template->cy = (screen_size_y / 2 * 8) /
				 HIWORD (dialog_base_units);
	    ptr_misc = (LPWORD)(dialog_template + 1);
	    /* We are now pointing at the "extra" area for this item */
	    *ptr_misc++ = 0x0000;	/* No Menu */
	    *ptr_misc++ = 0x0000;	/* Standard Dialog Box Class */
	    *ptr_misc++ = 0x0000;	/* No Title */
	    *ptr_misc++ = 8;
	    wcscpy ((wchar_t *)ptr_misc, (const wchar_t *) L"FixedSys");
	    ptr_misc += 9;

	    dialog_item_template = (DLGITEMTEMPLATE *) ptr_misc;
	    dialog_item_template->style = BS_DEFPUSHBUTTON | WS_VISIBLE |
					  WS_CHILD | WS_TABSTOP;
	    dialog_item_template->dwExtendedStyle = 0;
	    dialog_item_template->x = ((screen_size_x / 2 * 8) /
				      LOWORD (dialog_base_units)) / 4 - 25;
	    dialog_item_template->y = ((screen_size_y / 2 * 8) /
				      HIWORD (dialog_base_units)) - 28;
	    dialog_item_template->cx = 50;
	    dialog_item_template->cy = 14;
	    dialog_item_template->id = IDCANCEL;
	    ptr_misc = (LPWORD)(dialog_item_template + 1);
	    /* We are now pointing at the "extra" area for this item */
	    *ptr_misc++ = 0xFFFF;	/* Standard window type next */
	    *ptr_misc++ = 0x0080;	/* Button window style */
	    *ptr_misc++ = 0x0000;	/* No Title */
	    /* Undocumented information - used in .res */
	    *ptr_misc++ = 0;
	    *ptr_misc++ = 0x0000;	/* Nothing else */

	    dialog_item_template = (DLGITEMTEMPLATE *) ptr_misc;
	    dialog_item_template->style = ES_MULTILINE | ES_AUTOVSCROLL |
					  ES_AUTOHSCROLL | ES_READONLY |
					  WS_VISIBLE | WS_CHILD | WS_TABSTOP |
					  WS_BORDER | WS_VSCROLL |
					  WS_HSCROLL;
	    dialog_item_template->dwExtendedStyle = 0;
	    dialog_item_template->x = 12;
	    dialog_item_template->y = 8;
	    dialog_item_template->cx = (screen_size_x / 2 * 4) /
				       LOWORD (dialog_base_units) - 24;
	    dialog_item_template->cy = (screen_size_y / 2 * 8) /
				       HIWORD (dialog_base_units) - 28 - 14;
	    dialog_item_template->id = 101;
	    ptr_misc = (LPWORD)(dialog_item_template + 1);
	    /* We are now pointing at the "extra" area for this item */
	    *ptr_misc++ = 0xFFFF;	/* Standard window type next */
	    *ptr_misc++ = 0x0081;	/* editbox style */
	    *ptr_misc++ = 0x0000;	/* No Title */
	    /* Undocumented information - used in .res */
	    *ptr_misc++ = 0;
	    *ptr_misc++ = 0x0000;	/* Nothing else */

	    global_dialog = CreateDialogIndirect (global_instance,
						  dialog_template,
						  HWND_DESKTOP,
						  PrintfDlgProc);
	}

	va_start (argptr, format);

	/* text_length won't include final null character */
	text_length = _vsnprintf (new_text, sizeof (new_text), format, argptr);

	if (text_length > 0) {
	    stack		char		*start = &new_text[0];
	    register	char		*cp = start;

	    /* process individual lines */
	    while (*cp != '\0') {
		if (*cp == '\r')
		    ++cp;
		else if (*cp == '\n') {
		    *cp++ = '\0';

		    /* go to the end of the text */
		    SendDlgItemMessage (global_dialog,
					DIALOG_EDIT_ITEM,
					EM_SETSEL,
					(WPARAM)INT_MAX,
					(LPARAM)INT_MAX);

		    /* add new line */
		    SendDlgItemMessage (global_dialog,
					DIALOG_EDIT_ITEM,
					EM_REPLACESEL,
					(WPARAM) 0,
					(LPARAM)(LPCTSTR)start);

		    /* break line */
		    SendDlgItemMessage (global_dialog,
					DIALOG_EDIT_ITEM,
					EM_REPLACESEL,
					(WPARAM) 0,
					(LPARAM)(LPCTSTR)"\r\n");

		    start = cp;
		}
		else
		    ++cp;
	    }

	    /* process the remainder */
	    if (*start != '\0') {
		/* go to the end of the text */
		SendDlgItemMessage (global_dialog,
				    DIALOG_EDIT_ITEM,
				    EM_SETSEL,
				    (WPARAM)INT_MAX,
				    (LPARAM)INT_MAX);

		/* add new line */
		SendDlgItemMessage (global_dialog,
				    DIALOG_EDIT_ITEM,
				    EM_REPLACESEL,
				    (WPARAM) 0,
				    (LPARAM)(LPCTSTR)start);
	    }

	    /* scroll newly added text into view */
	    SendDlgItemMessage (global_dialog,
				DIALOG_EDIT_ITEM,
				EM_SCROLLCARET,
				(WPARAM) 0,
				(LPARAM)(LPCTSTR)0);
	}

	return text_length;
}
#endif

#endif


HC_EXTERNAL int main HC_PROTO ((int, char **, char**));


/*
 *  FUNCTION: WinMain (HANDLE, HANDLE, LPSTR, int)
 *
 *  PURPOSE: calls initialization functions
 *	     calls the regular hoops program's "main"
 */
global int PASCAL WinMain (
    stack	HINSTANCE	hInstance,
    stack	HINSTANCE	hPrevInstance,
    stack	LPSTR		lpCmdLine,
    stack	int		nCmdShow) 
{
	BOOL status;
	HMODULE hUser32 = LoadLibrary("user32.dll");
	int result = 0;
	if (hUser32) {
		typedef BOOL (*SetProcessDPIAwareFunc)();
		SetProcessDPIAwareFunc setDPIAware =
		   (SetProcessDPIAwareFunc)GetProcAddress(hUser32, "SetProcessDPIAware");
		if (setDPIAware)
		   status = setDPIAware();
		FreeLibrary(hUser32);
	}

    global_instance = GetModuleHandle (NULL);
    HC_Record_Instance_Handle (global_instance);

    /* call the user main (), handle initialization at update time */
    result = main (ARGC, ARGV, ENVP);

    if (global_dialog != (HWND)0)
		DestroyWindow (global_dialog);

    /*
     * ***************
     * * not reached *
     * ***************
     *
     * UNREFERENCED(hInstance);
     * UNREFERENCED(hPrevInstance);
     * UNREFERENCED(lpCmdLine);
     * UNREFERENCED(nCmdShow);
     *
     * Using this typical UNREFERENCED trick resulted in an "expression
     * has no side-effects" warning. To avoid that, but still get rid of the
     * "unreferenced format parameter" warning, we simply do a dummy test
     * and dummy increment. This code occurs after HC_Exit_Program, so it
     * never gets executed.
     */
    if (hInstance == hPrevInstance &&
	lpCmdLine == (LPSTR)0)
	nCmdShow++;

    return result;
}

#endif 



