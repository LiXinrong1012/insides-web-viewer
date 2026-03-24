#include "resultexpressionparser.h"

#include <algorithm>

#include "preparameter/functionsmanager.h"

#include "precore/IResultItem.h"
#include "precore/IResults.h"
#include "precore/modeldocument.h"
#include "precore/ResultDocument.h"

#include "resultfunctions.h"

using namespace INSIDES;

map<string, double>		ResultExpressionParser::_constTable  = map<string,double>();
FunctionsManager ResultExpressionParser::_functionManager = FunctionsManager();
bool ResultExpressionParser::_initialized=false;

void ResultExpressionParser::InitialConstant() 
{
	if(_initialized)
		return;

	Add_ConsantMap(_constTable) ;
	registerBuildMathFunc(&_functionManager);

	BaseFunction* tmp=new ResultCompFunction();
	_functionManager.insert(tmp->m_strFuncName,tmp);

	tmp=new TimeFunction();
	_functionManager.insert(tmp->m_strFuncName,tmp);

	tmp=new ContactCompFunction();
	_functionManager.insert(tmp->m_strFuncName,tmp);
	_initialized=true;
}

ResultExpressionParser::ResultExpressionParser() 
	:m_time(0)
{
	InitialConstant();
}

ResultExpressionParser::~ResultExpressionParser()
{
}

double	ResultExpressionParser::eval( )
{
	return _expr->eval() ;
}

int	ResultExpressionParser::dealWithName ( Expression& ret,  const string& str )
{
	string errmsg = "" ;

	ExpressionParser* parser=this;
	Token_value* curr_tok =  &(this->curr_tok);

	Expression Exprs[10] ;

	string s = str	;
	ResultExpressionParser * fpt	;

	transform(str.begin(), str.end(), s.begin(), toupper) ;

	if ( _constTable.find(s) != _constTable.end() )		//分辨预定义的常量pi，e等
	{
		ret = _constTable[s];
		get_token();
	}
	else{	//　函数，参数等
		//先查看下一个字段是不是　(
		Token_value tk = get_token();

		if (tk == PEV3LP)		// 函数需要以左括号 ( 开始
		{
			no_of_functions++;

			BaseFunction* pFunc = _functionManager.getFunction(s) ;
			if ( pFunc == NULL )
			{
				errmsg += "unrecognized FUNCTION: " + s ;
				return 1 ;
			}

			int numOfPara = pFunc->m_iNumOfPara ;
			int iPara = 0 ;

			while ( iPara < numOfPara )		// 最多连着解读 numofPara 个参数
			{
				Exprs[iPara] = expr(true) ;		iPara++ ;
				if		( *curr_tok == PEV3RP )	// 遇到右括号 ) 结束 
					break ;
				else if	( *curr_tok != PEV3COMMA )		
					error("comma, expected"+s) ;
			} 

			ret = pFunc->FuncLink(Exprs, iPara)  ;

			if ( *curr_tok != PEV3RP )	// 参数过多
				errmsg += m_strExpression + ": " + s + " is judged to be a function and bracket ) is expected for end. \r\n";
			else						// 读成功
			{
				no_of_functions++;
				get_token();
			}
		}
		else{ //假定是参数
			if(s=="TIME")
			{
				Exprs[0]=0.0;
				BaseFunction* tmpFunction=_functionManager.getFunction("TIME");
				ret = tmpFunction->FuncLink(Exprs, 1)  ;

				ret->SetPt(&m_time);
			}
			else{
				// 只能是条目名了
				IResultItem* resultItem=getRelatedResultItem(s.c_str());
				if(resultItem){
					ret->SetPt(resultItem);
					ret->SetOpType(OPT_PARAS);
					ret->SetExponent(1);

					if(!_relatedResultItems.contains(resultItem))
						_relatedResultItems.push_back(resultItem);
				}
				else
					errmsg="No item";
			}
		}
	}

	/*
	{
	ret->SetPt(&_myClass);
	ret->SetOpType(OPT_PARAS);
	ret->SetExponent(1);
	get_token();
	}
	*/
	//else if ( ( fpt	= GetExistParaPt(s) ) != NULL )	//分辨已经生成的Expression
	//{
	//	Exprs[0]->SetOpType(POINTER) ;
	//	Exprs[0]->SetPt((void*)fpt) ;
	//	Exprs[0]->SetVarName(s) ;

	//	ret->SetCoeff(1);
	//	ret->SetExponent(1);
	//	ret->SetOpType(OPT_PARAS) ;

	//	ret->AddNode(Exprs[0]) ;	// 添加计算节点

	//	parser->get_token();
	//}

	if ( errmsg != "" )
	{
		error(errmsg) ;
		return 1 ;		
	}
	else
		return 0 ;
}

bool ResultExpressionParser::setExpressionStr( const string& input )
{
	clear();

	m_strExpression=input;

	return 0==Parse(_expr,m_strExpression.c_str());
}

std::string ResultExpressionParser::getErrorMessage() const
{
	if(!m_strErr.empty())
		return m_strErr;
	else
		return ExpressionParser::getErrorMessage();
}

void ResultExpressionParser::clear()
{
	_relatedResultItems.clear();
}

void ResultExpressionParser::setPos( int currentIndex )
{
	for(ResultItemList::iterator b=_relatedResultItems.begin();
		b!=_relatedResultItems.end();++b)
		(*b)->setPos(currentIndex);
}

IResultItem* ResultExpressionParser::getRelatedResultItem( const QString& itemName )
{
	BaseItem* item=myDocument()->findItem(itemName);
	if(!item)
		return NULL;

	if(myResultDocument()->getResults())
		return myResultDocument()->getResults()->findResultItem(item).data();

	return NULL;
}
