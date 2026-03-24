#include "RotVecMath.h"
#include <math.h>

namespace RotVecMath
{

double Norm(const double* vec, int isize)
{
	double norm = 0 ; 
	for (int i = 0; i < isize; i++)
		norm += (vec[i] * vec[i]) ;
	return sqrt(norm) ;
}

void Get_A ( double* A, double* phi ) 
	{
		double h1, h2, phi_len ;
		phi_len = Norm ( phi, 3 ) ;
		Get_h1_h2 ( h1, h2, phi_len ) ;

		Aux_Get_Vec_Mat ( A, cos(phi_len), h1, h2, phi ) ;
	}


void Get_h1_h2 ( double& h1, double& h2,  double phi_len )
	{
		/* phi_len 代表的是转动向量的长度 */
		if ( abs(phi_len) > 1e-3 )
		{
			h1 = sin ( phi_len ) / phi_len ;
			h2 = ( 1 - cos(phi_len) ) / pow ( phi_len, 2 ) ;
		}
		else
		{
			double p2 = pow(phi_len ,2) ;
			h1 = 1.0 - 1.0/6*p2 + 1.0/120*pow(p2, 2) - 1.0/5040*pow(p2, 3) ;
			h2 = 1.0/2 - 1.0/24*p2 + 1.0/720*pow(p2, 2) - 1.0/40320*pow(p2, 3) ;
		}
	}

	void Aux_Get_Vec_Mat ( double* mat, double c1, double c2, double c3, double* phi )
	{
		for (int i = 0 ; i < 9; i++) mat[i] = 0;
		
		if  ( c1 != 0 )
		{
			for (int i = 0 ; i< 3; i++)
				mat[4*i] = c1 ;
		}

		if ( c2 != 0 )
		{
			double phiwave[9] ;
			U2Uwave( phiwave, phi ) ;
			for ( int i = 0 ; i < 9; i++ )
				mat[i] += c2 * phiwave[i] ;
		}

		if ( c3 != 0 )
		{
			double phiphit[9] ;
			VectorXYt( phiphit, phi, phi ) ;
			for ( int i = 0 ; i < 9; i++ )
				mat[i] += c3 * phiphit[i] ;
		}		
	}

inline void	U2Uwave ( double* res, /*3*3*/ const double* U /*3*1*/)
{
	res[0] = 0 ;		res[1] = -U[2] ;	res[2] = U[1] ;
	res[3] = U[2] ;		res[4] = 0 ;		res[5] = -U[0] ;
	res[6] = -U[1] ;	res[7] = U[0] ;		res[8] = 0 ;
}

inline void	 VectorXYt ( double* res, /*3*3*/ const double* x /*3*1*/, const double* y/*3*1*/)	
{
	/*[ x0*y0, x0*y1, x0*y2]
	[ x1*y0, x1*y1, x1*y2]
	[ x2*y0, x2*y1, x2*y2]*/

	res[0] = x[0] * y[0] ; res[1] = x[0] * y[1] ; res[2] = x[0] * y[2] ;
	res[3] = x[1] * y[0] ; res[4] = x[1] * y[1] ; res[5] = x[1] * y[2] ;
	res[6] = x[2] * y[0] ; res[7] = x[2] * y[1] ; res[8] = x[2] * y[2] ;
}
}
