#include <iostream>

#include <string>

#include "Simplex.h"

void Simplex::setValues()
{
	Simplex::setBasisVars(1);
	Simplex::setFactorsOfVars(1);
	Simplex::setIndexString(1);
	Simplex::setTargetFunction(1);
	Simplex::setThColumn();
	Simplex::displayTable(1);

	bool result = Simplex::checkPlane();

	std::string str;
	if (result)
		 str = "Первый опорный план является оптимальным.";
	else
		str = "Первый опорный план не оптимален. Его необходимо улучшить.";

	std::cout << str << std::endl << std::endl;
}

bool Simplex::checkPlane()
{
	int i;
	bool result = true;	
	for (i = 0; i < numOfSourceVars; ++i)
	{
		if (indexString[i] < 0)
		{
			result = false;
			break;
		}
	}
	return result;
}

void Simplex::displayTable (int numOfIteration)
{
	int i, j;

	for (i = 0; i < numOfSourceVars; ++i)
	{
		std::cout << "X" << i + 1 << "		";
		std::cout <<  basisVars[i] << "		";
		for (j = 0; j < numOfSourceVars * 2; ++j)
		{
			std::cout << varsFactors [i][j] << "	";			
		}
		std::cout << "	" <<  thColumn [i];
		std::cout << std::endl << std::endl;
	}
	std::cout << "F(X)		";
	std::cout << targetFunction << "		";
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{
		std::cout << indexString [i] << "	";
	}
	std::cout << std::endl << std::endl;
}

void Simplex::setLeavingColumn()
{
	leavingColumn = new double [numOfSourceVars];
	double minOfIndexString = indexString[0];
	int indexOfMin = 0;
	int i, j;
	for (i = 0; i < numOfSourceVars * 2; ++i)
	{

		if (indexString[i] < 0 && minOfIndexString > indexString[i])
		{
			minOfIndexString = indexString [i];
			indexOfMin = i;
		}

	}
	for (i = 0; i < numOfSourceVars; ++i)
			leavingColumn [i] = varsFactors[i][indexOfMin];
}

void Simplex::setBasisVars(int numOfIteration)
{
	if (numOfIteration == 1)
		basisVars = freeMembersOfSystem;
}

void Simplex::setFactorsOfVars(int numOfIteration)
{
	if (numOfIteration == 1)
	{
		int i, j;	
		varsFactors = new double * [numOfSourceVars];

		for (i = 0; i < numOfSourceVars; ++i)

			varsFactors[i] = new double [numOfSourceVars * 2];

		for  (i = 0; i < numOfSourceVars; ++i)
		{
			for(j = 0; j < numOfSourceVars * 2; ++j)

				if (j < numOfSourceVars)
					varsFactors[i][j] = factorsOfSystemVars[i][j];
				else
					varsFactors [i][j] = i + numOfSourceVars == j;
		
		}
	}
}


void Simplex::setIndexString (int numOfIteration)
{
	if (numOfIteration == 1)
	{
		int i;
		indexString = new double [numOfSourceVars * 2];
		for (i = 0; i < numOfSourceVars * 2; ++i)
			indexString [i] = ((i < numOfSourceVars) ? -(factorsOfTargetFunctionVars [i]) : 0);
	}
}

void Simplex::setTargetFunction(int numOfIteration)
{
	if (numOfIteration == 1)
		targetFunction = 0;
}

void Simplex::setThColumn ()
{
	int i;

	Simplex::setLeavingColumn(); // Задаем значение ведущего столбца.

	thColumn = new double [numOfSourceVars];

	for (i = 0; i < numOfSourceVars; ++i)
	{
		thColumn [i] = basisVars [i] / leavingColumn [i];
	}
}
