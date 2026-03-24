#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include "base/base_global.h"

#include <set>
#include <fstream>
#include <string>

namespace Base {
class ConsoleSingleton;
}; // namespace Base

typedef Base::ConsoleSingleton ConsoleMsgType;
typedef unsigned int ConsoleMsgFlags;
 
namespace Base {

/** The console observer class
 *  This class distribute the Messages issued to the FCConsole class. 
 *  If you need to catch some of the Messages you need to inherit from
 *  this class and implement some of the methods.
 *  @see Console
 *	If you donot want this notify Warning, you can set bWrn=false.
  */
class BASE_EXPORT ConsoleObserver
{
public:
    ConsoleObserver()
        :bErr(true),bMsg(true),bLog(true),bWrn(true) {}
    virtual ~ConsoleObserver() {}
    /// get calles when a Warning is issued
    virtual void Warning(const char *){};
    /// get calles when a Message is issued
    virtual void Message(const char *){};
    /// get calles when a Error is issued
    virtual void Error  (const char *)=0;
    /// get calles when a Log Message is issued
    virtual void Log    (const char *){};
	/// get calles when a pair of values is issued.
	virtual void Pairs(const char* key,const char* v){}

    virtual const char *Name(void){return 0L;}
    bool bErr,bMsg,bLog,bWrn;
};


/** The console class
 *  This class manage all the stdio stuff. This includes 
 *  Messages, Warnings, Log entries and Errors. The incomming
 *  Messages are distributed with the FCConsoleObserver. The
 *  FCConsole class itself makes no IO, it's more like a manager.
 *  \par
 *  ConsoleSingleton is a singleton! That means you can access the only
 *  instance of the class from every where in c++ by simply using:
 *  \code
 *  #include <Base/Console.h>
 *  Base::Console().Log("Stage: %d",i);
 *  \endcode
 *  \par
 *  ConsoleSingleton is abel to switch between several modes to, e.g. switch
 *  the logging on or off, or treat Warnings as Errors, and so on...
 *  @see ConsoleObserver
 */
class BASE_EXPORT ConsoleSingleton
{

public:

    // exported functions goes here +++++++++++++++++++++++++++++++++++++++
    /// Prints a Message 
    virtual void Message ( const char * pMsg, ... ) ;
    /// Prints a warning Message 
    virtual void Warning ( const char * pMsg, ... ) ;
    /// Prints a error Message 
    virtual void Error   ( const char * pMsg, ... ) ;
    /// Prints a log Message 
    virtual void Log     ( const char * pMsg, ... ) ;

	virtual void Pairs	 (const char*key,const char* pMsg, ...);

    /// Delivers a time/date string 
    const char* Time(void);
    /// Attaches an Observer to FCConsole
    void AttachObserver(ConsoleObserver *pcObserver);
    /// Detaches an Observer from FCConsole
    void DetachObserver(ConsoleObserver *pcObserver);
    /// enumaration for the console modes
    enum ConsoleMode{
        Verbose = 1,	// supress Log messages
    };

    enum FreeCAD_ConsoleMsgType { 
        MsgType_Txt = 1, 
        MsgType_Log = 2, 
        MsgType_Wrn = 4, 
        MsgType_Err = 8 
    } ;

    /// Change mode
    void SetMode(ConsoleMode m);
    /// Change mode
    void UnsetMode(ConsoleMode m);
    /// Enables or disables message types of a cetain console observer
    ConsoleMsgFlags SetEnabledMsgType(const char* sObs, ConsoleMsgFlags type, bool b);

    /// singleton 
    static ConsoleSingleton &Instance(void);

	/// return a Console instance for TDY.
	static ConsoleSingleton& TDYInstance(void);

    // retrieval of an observer by name
    ConsoleObserver *Get(const char *Name);

protected:
    bool _bVerbose;

    // Singleton!
    ConsoleSingleton(void);
    virtual ~ConsoleSingleton();

private:
    // singleton
    static void Destruct(void);
    static ConsoleSingleton *_pcSingleton;

	// append a Console instance for TDY. jerry
	static ConsoleSingleton* _TDYSingleton;

    // observer processing 
    void NotifyMessage(const char *sMsg);
    void NotifyWarning(const char *sMsg);
    void NotifyError  (const char *sMsg);
    void NotifyLog    (const char *sMsg);
	void NotifyPairs  (const char* sKey,const char* sValue);

    // observer list
    std::set<ConsoleObserver * > _aclObservers;
};

/** Access to the Console
 *  This method is used to gain access to the one and only instance of 
 *  the ConsoleSingleton class.
 */  
inline ConsoleSingleton &Console(void){
    return ConsoleSingleton::Instance();
}

/*! return one Console instance for TDY.*/
inline ConsoleSingleton & TDYConsole(void){
	return ConsoleSingleton::TDYInstance();
}


//=========================================================================
// some special observers

/** The LoggingConsoleObserver class
 *  This class is used by the main modules to write Console messages and logs to a file
 */  
class BASE_EXPORT ConsoleObserverFile : public ConsoleObserver
{
public:
    ConsoleObserverFile(const char *sFileName);
    virtual ~ConsoleObserverFile();
    virtual void Warning(const char *sWarn);
    virtual void Message(const char *sMsg);
    virtual void Error  (const char *sErr);
    virtual void Log    (const char *sLog);
    const char* Name(void){return "File";}

protected:
    std::ofstream cFileStream;
};

/** The CmdConsoleObserver class
 *  This class is used by the main modules to write Console messages and logs the system con.
 */
class BASE_EXPORT ConsoleObserverStd: public ConsoleObserver
{
public:
    ConsoleObserverStd();
    virtual ~ConsoleObserverStd();
    virtual void Warning(const char *sWarn);
    virtual void Message(const char *sMsg); 
    virtual void Error  (const char *sErr); 
    virtual void Log    (const char *sErr); 
    const char* Name(void){return "Console";}
};

class BASE_EXPORT RedirectStdOutput : public std::streambuf
{
public:
    RedirectStdOutput();

protected:
    int overflow(int c = EOF);
    int sync();

private:
    std::string buffer;
};

class BASE_EXPORT RedirectStdError : public std::streambuf
{
public:
    RedirectStdError();

protected:
    int overflow(int c = EOF);
    int sync();

private:
    std::string buffer;
};

class BASE_EXPORT RedirectStdLog : public std::streambuf
{
public:
    RedirectStdLog();

protected:
    int overflow(int c = EOF);
    int sync();

private:
    std::string buffer;
};


} // namespace Base 

#endif
