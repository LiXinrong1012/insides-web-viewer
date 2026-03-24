// HQDeleter.h - public interface of the HOOPS/Qt class HQDeleter 
// More about this class 
  
#ifndef HQDELETER_H 
#define HQDELETER_H 

// Qt inlcudes 
#include <QObject> 
#include <QEvent> 
#include <QApplication> 
#include <QHash>

class HQDeleter: public QObject  
{ 
 Q_OBJECT 

public: 

	HQDeleter(QObject * parent=0, const char * name=0); 
	~HQDeleter(); 

	void processDeletes(); 
	void deleteLater(QObject * o); 

	bool event(QEvent * e); 

public slots: 

	 void detectOtherDelete(); 

private: 

	 QHash<int, QObject*> *objects; 

}; 
  

#endif 

