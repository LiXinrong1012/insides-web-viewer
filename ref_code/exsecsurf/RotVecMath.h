#pragma once

namespace RotVecMath
{

void Get_A ( double* A, double* phi )  ;

double Norm(const double* vec, int size) ;



void Get_h1_h2 ( double& h1, double& h2,  double phi_len ) ;
	
	void Aux_Get_Vec_Mat ( double* mat, double c1, double c2, double c3, double* phi ) ;
	
 void	U2Uwave ( double* res, /*3*3*/ const double* U /*3*1*/) ;

 void	 VectorXYt ( double* res, /*3*3*/ const double* x /*3*1*/, const double* y/*3*1*/) ;	



}