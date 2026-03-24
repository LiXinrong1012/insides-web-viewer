#include "pre_compile.h"

#ifndef _PreComp_
# include <time.h>
# include <stdio.h>
# ifdef FC_OS_WIN32
# include <io.h>
# include <windows.h>
# endif
# include "fcntl.h"
#endif

#include "Console.h"
#include "Exception.h"

using namespace Base;



char format[4024];  // global buffer 
const unsigned int format_len = 4024;


//**************************************************************************
// Construction destruction


ConsoleSingleton::ConsoleSingleton(void)
  :_bVerbose(false)
{

}

ConsoleSingleton::~ConsoleSingleton()
{
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
        delete (*Iter);   

}


//**************************************************************************
// methods

/**  
 *  sets the console in a special mode
 */
void ConsoleSingleton::SetMode(ConsoleMode m)
{
    if(m && Verbose)
        _bVerbose = true;
}
/**  
 *  unsets the console from a special mode
 */
void ConsoleSingleton::UnsetMode(ConsoleMode m)
{
    if(m && Verbose)
        _bVerbose = false;
}

/**
 * \a type can be OR'ed with any of the FreeCAD_ConsoleMsgType flags to enable -- if \a b is true --
 * or to disable -- if \a b is false -- a console observer with name \a sObs.
 * The return value is an OR'ed value of all message types that have changed their state. For example
 * @code
 * // switch off warnings and error messages
 * ConsoleMsgFlags ret = Base::Console().SetEnabledMsgType("myObs", 
 *                             ConsoleMsgType::MsgType_Wrn|ConsoleMsgType::MsgType_Err, false);
 * // do something without notifying observer myObs
 * ...
 * // restore the former configuration again
 * Base::Console().SetEnabledMsgType("myObs", ret, true);
 * @endcode
 * switches off warnings and error messages and restore the state before the modification.
 * If the observer \a sObs doesn't exist then nothing happens.
 */
ConsoleMsgFlags ConsoleSingleton::SetEnabledMsgType(const char* sObs, ConsoleMsgFlags type, bool b)
{
    ConsoleObserver* pObs = Get(sObs);
    if ( pObs ){
        ConsoleMsgFlags flags=0;

        if ( type&MsgType_Err ){
            if ( pObs->bErr != b )
                flags |= MsgType_Err;
            pObs->bErr = b;
        }
        if ( type&MsgType_Wrn ){
            if ( pObs->bWrn != b )
                flags |= MsgType_Wrn;
            pObs->bWrn = b;
        }
        if ( type&MsgType_Txt ){
            if ( pObs->bMsg != b )
                flags |= MsgType_Txt;
            pObs->bMsg = b;
        }
        if ( type&MsgType_Log ){
            if ( pObs->bLog != b )
                flags |= MsgType_Log;
            pObs->bLog = b;
        }
        return flags;
    }
    else {
        return 0;
    }
}

/** Prints a Message
 *  This method issues a Message. 
 *  Messages are used show some non vital information. That means in the
 *  case FreeCAD running with GUI a Message in the status Bar apear. In console
 *  mode a message comes out. 
 *  \par
 *  You can use a printf like interface like:
 *  \code
 *  Console().Message("Doing somthing important %d times\n",i);
 *  \endcode
 *  @see Warning
 *  @see Error
 *  @see Log
 */
void ConsoleSingleton::Message( const char *pMsg, ... )
{
    va_list namelessVars;
    va_start(namelessVars, pMsg);  // Get the "..." vars
    vsnprintf(format, format_len, pMsg, namelessVars);
    va_end(namelessVars);
    NotifyMessage(format);
}

/** Prints a Message
 *  This method issues a Warning. 
 *  Messages are used to get the users attantion. That means in the
 *  case FreeCAD running with GUI a Message Box is poping up. In console
 *  mode a colored message comes out! So dont use careless. For information
 *  purpose the Log or Message method is more aprobiated.
 *  \par
 *  You can use a printf like interface like:
 *  \code
 *  Console().Warning("Some defects in %s, loading anyway\n",str);
 *  \endcode
 *  @see Message
 *  @see Error
 *  @see Log
 */
void ConsoleSingleton::Warning( const char *pMsg, ... )
{
    va_list namelessVars;
    va_start(namelessVars, pMsg);  // Get the "..." vars
    vsnprintf(format, format_len, pMsg, namelessVars);
    va_end(namelessVars);
    NotifyWarning(format);
}

/** Prints a Message
 *  This method issues an Error which makes some execution imposible. 
 *  Errors are used to get the users attantion. That means in the
 *  case FreeCAD running with GUI a Error Message Box is poping up. In console
 *  mode a colored message comes out! So dont use this careless. For information
 *  purpose the Log or Message method is more aprobiated.
 *  \par
 *  You can use a printf like interface like:
 *  \code
 *  Console().Error("Somthing realy bad in %s happend\n",str);
 *  \endcode
 *  @see Message
 *  @see Warning
 *  @see Log
 */
void ConsoleSingleton::Error( const char *pMsg, ... )
{
    va_list namelessVars;
    va_start(namelessVars, pMsg);  // Get the "..." vars
    vsnprintf(format, format_len, pMsg, namelessVars);
    va_end(namelessVars);
    NotifyError(format);
}


/** Prints a Message
 *  this method is more for devlopment and tracking purpos.
 *  It can be used to track execution of algorithems and functions
 *  and put it in files. The normal user dont need to see it, its more
 *  for developers and experinced users. So in normal user modes the 
 *  logging is switched of.
 *  \par
 *  You can use a printf like interface like:
 *  \code
 *  Console().Log("Exectue part %d in algorithem %s\n",i,str);
 *  \endcode
 *  @see Message
 *  @see Warning
 *  @see Error
 */


void ConsoleSingleton::Log( const char *pMsg, ... )
{
    if (!_bVerbose)
    {
        va_list namelessVars;
        va_start(namelessVars, pMsg);  // Get the "..." vars
        vsnprintf(format, format_len, pMsg, namelessVars);
        va_end(namelessVars);
        NotifyLog(format);
    }
}

void ConsoleSingleton::Pairs	 (const char*key,const char* pMsg, ...)
{
	va_list namelessVars;
	va_start(namelessVars, pMsg);  // Get the "..." vars
	vsnprintf(format, format_len, pMsg, namelessVars);
	va_end(namelessVars);
	NotifyPairs(key,format);
}


/** Delivers the time/date
 *  this method give you a string with the actual time/date. You can
 *  use that for Log() calls to make time stamps.
 *  @return Const string with the date/time
 */
const char* ConsoleSingleton::Time(void)
{
    struct tm *newtime;
    time_t aclock;
    time( &aclock );                 // Get time in seconds 
    newtime = localtime( &aclock );  // Convert time to struct tm form 
    char* st = asctime( newtime );
    st[24] = 0;
    return st;
}



//**************************************************************************
// Observer stuff

/** Attaches an Observer to Console
 *  Use this method to attach a ConsoleObserver derived class to 
 *  the Console. After the observer is attached all messages will also
 *  forwardet to it.
 *  @see ConsoleObserver
 */
void ConsoleSingleton::AttachObserver(ConsoleObserver *pcObserver)
{
    // double insert !!
    assert(_aclObservers.find(pcObserver) == _aclObservers.end() );

    _aclObservers.insert(pcObserver);
}

/** Detaches an Observer from Console
 *  Use this method to detach a ConsoleObserver derived class.
 *  After detaching you can destruct the Observer or reinsert it later.
 *  @see ConsoleObserver
 */
void ConsoleSingleton::DetachObserver(ConsoleObserver *pcObserver)
{
    _aclObservers.erase(pcObserver);
}

void ConsoleSingleton::NotifyMessage(const char *sMsg)
{
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
        if((*Iter)->bMsg)
            (*Iter)->Message(sMsg);   // send string to the listener
}

void ConsoleSingleton::NotifyWarning(const char *sMsg)
{
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
        if((*Iter)->bWrn)
            (*Iter)->Warning(sMsg);   // send string to the listener
}

void ConsoleSingleton::NotifyError(const char *sMsg)
{
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
        if((*Iter)->bErr)
            (*Iter)->Error(sMsg);   // send string to the listener
}

void ConsoleSingleton::NotifyLog(const char *sMsg)
{
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
        if((*Iter)->bLog)
            (*Iter)->Log(sMsg);   // send string to the listener
}
void ConsoleSingleton::NotifyPairs  (const char* sKey,const char* sValue)
{
	for(std::set<ConsoleObserver*>::iterator b=_aclObservers.begin(); 
		b!=_aclObservers.end();++b)
		(*b)->Pairs(sKey,sValue);
}


ConsoleObserver *ConsoleSingleton::Get(const char *Name)
{
    const char* OName;
    for(std::set<ConsoleObserver * >::iterator Iter=_aclObservers.begin();Iter!=_aclObservers.end();Iter++)
    {
        OName = (*Iter)->Name();   // get the name
        if(OName && strcmp(OName,Name) == 0)
            return *Iter;
    }
    return 0;
}


//**************************************************************************
// Singleton stuff

ConsoleSingleton * ConsoleSingleton::_pcSingleton = 0;
ConsoleSingleton * ConsoleSingleton::_TDYSingleton=0;

void ConsoleSingleton::Destruct(void)
{
    // not initialized or double destructed!
    assert(_pcSingleton);
    delete _pcSingleton;
    _pcSingleton=0;

	if(_TDYSingleton){
		delete _TDYSingleton;
		_TDYSingleton=0;
	}
}

ConsoleSingleton & ConsoleSingleton::Instance(void)
{
    // not initialized?
    if(!_pcSingleton)
    {
        _pcSingleton = new ConsoleSingleton();
    }
    return *_pcSingleton;
}

ConsoleSingleton& ConsoleSingleton::TDYInstance()
{
	if(!_TDYSingleton)
		_TDYSingleton=new ConsoleSingleton();
	return *_TDYSingleton;
}


//=========================================================================
// some special observers

ConsoleObserverFile::ConsoleObserverFile(const char *sFileName)
  :cFileStream(sFileName)
{
    if (!cFileStream.is_open())
        Console().Warning("Cannot open log file '%s'.\n", sFileName);
    // mark the file as a UTF-8 encoded file
    unsigned char bom[3] = {0xef, 0xbb, 0xbf};
    cFileStream.write((const char*)bom,3*sizeof(char));
}

ConsoleObserverFile::~ConsoleObserverFile()
{
    cFileStream.close();
}

void ConsoleObserverFile::Warning(const char *sWarn)
{
    cFileStream << "Wrn: " << sWarn<<endl;
    cFileStream.flush();
}

void ConsoleObserverFile::Message(const char *sMsg)
{
    cFileStream << "Msg: " << sMsg<<endl;
    cFileStream.flush();
}

void ConsoleObserverFile::Error  (const char *sErr)
{
    cFileStream << "Err: " << sErr<<endl;
    cFileStream.flush();
}

void ConsoleObserverFile::Log    (const char *sLog)
{
    cFileStream << "Log: " << sLog<<endl;
    cFileStream.flush();
}


ConsoleObserverStd::ConsoleObserverStd()
{
    bLog = false;
}

ConsoleObserverStd::~ConsoleObserverStd()
{
}


void ConsoleObserverStd::Warning(const char *sWarn)
{
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN| FOREGROUND_BLUE);
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN| FOREGROUND_BLUE);
#   endif
#   else
    printf("\033[1;33m");
#   endif
    printf("%s",sWarn);
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   endif
#   else
    printf("\033[0m");
#   endif
}

void ConsoleObserverStd::Message(const char *sMsg)
{
    printf("%s",sMsg);
}

void ConsoleObserverStd::Error  (const char *sErr)
{
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY );
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED|FOREGROUND_INTENSITY );
#   endif
#   else
    printf("\033[1;31m");
#   endif
    printf("%s",sErr);
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   endif
#   else
    printf("\033[0m");
#   endif
}

void ConsoleObserverStd::Log    (const char *sErr)
{
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_GREEN);
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |FOREGROUND_GREEN);
#   endif
#   else
    printf("\033[1;36m");
#   endif
    printf("%s",sErr);
#   ifdef FC_OS_WIN32
#   if defined(_MSC_VER) && _MSC_VER >= 1400
    //::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   else
    ::SetConsoleTextAttribute(::GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
#   endif
#   else
    printf("\033[0m");
#   endif
}

RedirectStdOutput::RedirectStdOutput() 
{
    buffer.reserve(80);
}

int RedirectStdOutput::overflow(int c)
{
    if (c != EOF)
        buffer.push_back((char)c);
    return c;
}

int RedirectStdOutput::sync()
{
    // Print as log as this might be verbose
    if (!buffer.empty()) {
        Base::Console().Log("%s", buffer.c_str());
        buffer.clear();
    }
    return 0;
}

RedirectStdLog::RedirectStdLog() 
{
    buffer.reserve(80);
}

int RedirectStdLog::overflow(int c)
{
    if (c != EOF)
        buffer.push_back((char)c);
    return c;
}

int RedirectStdLog::sync()
{
    // Print as log as this might be verbose
    if (!buffer.empty()) {
        Base::Console().Log("%s", buffer.c_str());
        buffer.clear();
    }
    return 0;
}

RedirectStdError::RedirectStdError() 
{
    buffer.reserve(80);
}

int RedirectStdError::overflow(int c)
{
    if (c != EOF)
        buffer.push_back((char)c);
    return c;
}

int RedirectStdError::sync()
{
    if (!buffer.empty()) {
        Base::Console().Error("%s", buffer.c_str());
        buffer.clear();
    }
    return 0;
}
