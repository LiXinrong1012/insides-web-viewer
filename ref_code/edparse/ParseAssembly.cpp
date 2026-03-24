#include "ParseAssembly.h"
#include "MainItem.h"
#include <fstream>
#include <iostream>
#include <sstream>

/*
namespace Parse {
	string Key::toLocation() 
	{ 
		stringstream ss; 
		ss << "File name = " << strFilename << ", " << "Line number = " << iLineNum  ; 
		return ss.str(); 
	} 

	void Key::write ( string prestr, ofstream& fout )
	{
		fout << prestr << "Original String = " << strFull << endl ;

		if ( mainItem.filenm != ""  )
			mainItem.write(prestr, fout) ;
		else
			fout << prestr << "not parsed yet!" << endl ;
	}

	void Structure::addKey ( Key* curkey ) 
	{ 
		listKeys.push_back(curkey); 
	} 

	string Structure::toLocation() 
	{ 
		stringstream ss; 
		ss << "File name = " << strFilename << ", " << "Line number = " << iLineNum << ':' ; 
		return ss.str(); 
	} 

	bool Structure::bHasParameters()
	{
		for ( list<Key*>::iterator it = listKeys.begin(); it != listKeys.end(); it++ )
		{
			if ( (*it)->strKeyName == "PARAMETER" )
				return true ;
		}

		return false ;
	}

	bool Part::bHas( Key*& pkey, string name )
	{
		for ( list<Key*>::iterator it = listKeys.begin(); it != listKeys.end(); it++ )
		{
			if ( (*it)->strKeyName == name )
			{
				pkey = (*it) ;
				return true ;
			}
		}
		pkey = NULL ;
		return false ;
	}

	void Part::write ( string prestr, ofstream& fout )
	{
		fout << prestr << strType << " / " << strName << " { " << endl ;

		string pstr = "\t" + prestr ;

		Key* curKey ;
		for ( list<Key*>::iterator it = listKeys.begin(); it != listKeys.end(); it++ )
		{
			curKey = *it ;
			curKey->write(pstr, fout) ;
		}

		fout << prestr <<  "} " << endl << endl ;
	}

	void Assembly::write(string filenm)
	{
		ofstream fout(filenm) ;

		write("", fout) ;

		fout.close() ;
	}

	void Assembly::write ( string prestr, ofstream& fout )
	{
		fout << prestr << strType << " / " << strName << " { " << endl ;

		string pstr = "\t" + prestr ;

		Assembly* curAss ;
		for ( map<string, Assembly*>::iterator it = mapAssemblys.begin(); it != mapAssemblys.end(); it++ )
		{
			curAss = it->second ;
			curAss->write(pstr, fout) ;
		}

		Part* curPart ;
		for ( map<string, Part*>::iterator it = mapParts.begin(); it != mapParts.end(); it++ )
		{
			curPart = it->second ;
			curPart->write(pstr, fout) ;
		}

		Key* curKey ;
		for ( list<Key*>::iterator it = listKeys.begin(); it != listKeys.end(); it++ )
		{
			curKey = *it ;
			curKey->write(pstr, fout) ;
		}

		fout <<  prestr <<  "} " << endl << endl ;
	}


	string KeyLocation(Key* pkey)
	{
		string error = "the above mentioned information might be arise due to " + pkey->toLocation() + "." ;
		return error;
	}

	string MainItemLocation(MainItem* pmain)
	{
		string location ;
		pmain->toLocation(location) ;
		string error = "the above mentioned information might be arise due to " + location + "." ;
		return error;
	}
}

*/