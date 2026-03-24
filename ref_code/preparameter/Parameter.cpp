#include "Parameter.h"

#include <algorithm>

#include "functionsmanager.h"

map<string, double>*		Parameter::table  = NULL ;


void	Parameter::InitialConstant() 
{
	if ( table->empty() )			// 常数列表
		Add_ConsantMap( *table ) ;
}

Parameter::Parameter() 
{
	_expr = new Expression ;

	m_existParaMap = NULL ;

	if ( table == NULL )
		table = new map<string, double>	;		// 用于存储常数

	InitialConstant() ;

	_functionManager=new FunctionsManager();
	registerBuildMathFunc(_functionManager);
}

Parameter::Parameter(Parameter & f) 
{	
	m_strExpression = f.getExpression() ;
	double val = f.eval() ;

	_expr = new Expression ;

	GetExpr()->SetOpType(OPT_CONST) ;
	GetExpr()->SetValue(val);
	GetExpr()->SetCoeff(1);    
	GetExpr()->SetExponent(1);
}

Parameter::~Parameter()
{
	if ( _expr != NULL ) delete _expr; _expr = NULL ;
	delete _functionManager;
}

Expression&	Parameter::GetExpr()
{
	return *_expr;
}

double		Parameter::eval( )
{
	return (*_expr)->eval(  ) ;
}

void		Parameter::SetRelNode	( Expression& ept )
{
 	if( ept->IsLeaf() && ept->IsNotPointer() )
 		return;
 	else
 	{
 		int size = ept->GetSize();
 		for(int i = 0; i < size; ++i)
 			SetRelNode(ept->GetNode(i));
 	}
}

Parameter*	Parameter::GetExistParaPt	( string ename )
{
	if( m_existParaMap != NULL )
	{
		if( m_existParaMap->find(ename) != m_existParaMap->end() )
			return (*m_existParaMap)[ename];
		else
			return NULL;
	}
	else
		return NULL;	
}


int		Parameter::dealWithName ( Expression& ret,  const string& str )
{
	string errmsg = "" ;

	ExpressionParser* parser=this;
	Token_value* curr_tok = &(this->curr_tok) ;

	Expression Exprs[10] ;

	string s = str	;
	Parameter * fpt	;

	transform(str.begin(), str.end(), s.begin(), toupper) ;

	if ( s[0] == '$' ) // predefined function or parameters
	{
 		string fun = s.substr(1, s.length()) ;
 		if ( ( fpt	= GetExistParaPt(fun) ) != NULL )	//分辨已经生成的Expression
 		{
			Exprs[0]->SetOpType(POINTER) ;
			Exprs[0]->SetPt((void*)fpt) ;
			Exprs[0]->SetVarName(s) ;

			ret->SetCoeff(1);
			ret->SetExponent(1); 
			ret->SetOpType(OPT_PARAS) ;

			ret->AddNode(Exprs[0]) ;	// 添加计算节点

 			get_token();
 		}
 		else
 		{
			m_strErr =  fun + " is not a defined yet!" ;
 			return 1 ;
 		}
	}
	else if ( table->find(s) != table->end() )		//分辨预定义的常量pi，e等
	{
		ret = (*table)[s];
		get_token();
	}
	else if ( ( fpt	= GetExistParaPt(s) ) != NULL )	//分辨已经生成的Expression
	{
		Exprs[0]->SetOpType(POINTER) ;
		Exprs[0]->SetPt((void*)fpt) ;
		Exprs[0]->SetVarName(s) ;

		ret->SetCoeff(1);
		ret->SetExponent(1);
		ret->SetOpType(OPT_PARAS) ;

		ret->AddNode(Exprs[0]) ;	// 添加计算节点
 		
		get_token();
	}
	else	// 剩下的必须是函数
	{					
		Token_value tk = get_token();

		if (tk == PEV3LP)		// 函数需要以左括号 ( 开始
		{
			no_of_functions++;

			BaseFunction* pFunc = _functionManager->getFunction(s) ;
			if ( pFunc == NULL )
			{
				errmsg += "unrecognized FUNCTION: " + s ;
				return 1 ;
			}
			
			int numOfPara = pFunc->m_iNumOfPara ;
			int iPara = 0 ;

			while ( iPara < numOfPara )		// 最多连着解读 numofPara 个参数
			{
				Exprs[iPara] = expr(true) ;		
				iPara++ ;
				if		( *curr_tok == PEV3RP )	// 遇到右括号 ) 结束 
					break ;
				else if	( *curr_tok != PEV3COMMA )		
					error("comma, expected"+s) ;
			} 

			ret = pFunc->FuncLink(Exprs, iPara)  ;
		}
 		else
			errmsg += m_strExpression + ": " + s + " is judged to be a function and bracket ( is expected for start. \r\n";
 			

 		if ( *curr_tok != PEV3RP )	// 参数过多
			errmsg += m_strExpression + ": " + s + " is judged to be a function and bracket ) is expected for end. \r\n";
 		else						// 读成功
 		{
			no_of_functions++;
			get_token();
		}	  
	}

	if ( errmsg != "" )
	{
		error(errmsg) ;
		return 1 ;		
	}
	else
		return 0 ;
}

int		Parameter::strToPara (const string& strFun, map<string, Parameter*> *fmap)
{
	m_existParaMap = fmap ;

	string str  ;
	if ( strFun[0] == '\"' )
	{
		if ( strFun.find_last_of('\"') != strFun.length()-1 )
			return 1;
		else
		{
			str = strFun.substr(strFun.find_first_of('\"')+1, strFun.find_last_of('\"')-1) ;
			if ( str.find_first_of('\"') != string::npos )
				return 1 ;
		}		
	}
	else
		str = strFun ;

	m_strErr = "" ;	

	ExpressionParser parser ;

	m_strExpression = str ;	

	if ( parser.Parse ( *_expr, str.c_str() ) != 0 )
	{
		m_existParaMap = NULL ;	// 如果非空，将导致Parameter比较多时debug变慢
		return 1 ;
	}
	else
	{
		// 直接计算出Parameter的值并存储
		double val = GetExpr()->eval( ) ;

		GetExpr()->SetOpType(OPT_CONST) ;
		GetExpr()->SetValue(val);
		GetExpr()->SetCoeff(1);    
		GetExpr()->SetExponent(1);

		m_existParaMap = NULL ;	// 如果非空，将导致Parameter比较多时debug变慢

		return 0 ;
	}
}

int		Parameter::changeConstValue ( double val )
{
	return (*_expr)->SetConstValue(val) ;
}