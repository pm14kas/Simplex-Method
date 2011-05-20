#ifndef _SIMPLEX_H_
#define _SIMPLEX_H_ 1


#include <iostream>

#include "InputData.h"
#include "Plane.h"
// #include "SubPlane.h"


/*
 * В этом файле содержится класс, элементы которого
 * содержат все элементы симплекс таблицы, а функции
 * этого класса расчитывают оптимальный план задачи.
*/

enum result { good_solution, bad_solution, no_solution };

class Simplex : public InputData  {

	public:
		
		/* Данная функция
		 * Задает значения членам класса
		 * для первого опорного плана
		*/

		void init();

		/*
		 * Данная функция задает значения для
		 * всех элементов текущего плана.
		 * Из нее вызываются функции, которые
		 * задают конкретные значения для отдельных
		 * элементов текущего плана в симплекс таблице.
		*/

		void setValues();

		/*
		 * Данная фукнция проверяет полученный план
		 * на оптимальность.
		*/

		bool printCurrentAndAssignBest(int);
		
		bool checkThColumn(Plane*);

		enum result checkPlane(Plane*);

		/*
		 * Данная функция задает значения базисных
		 * переменных в симплекс таблице
		*/

		void setBasisVars(Plane* source, Plane* target);

		/*
		 * Данная фукнция отображает решение задачи.
		*/

		void dumpToTableTxt(Plane*, unsigned int iteration, enum result);

		void displayResult(Plane*, unsigned int iteration, enum result);

		/*
		 * Данная функция задаен значения коэффициентов
		 * при основных и базисных переменных в симплекс таблице.
		*/
		
		void setFactorsOfVars(Plane* source, Plane*target);

		/*
		 * Данная фукнция задает значения коэффициетов
		 * в индексной строке симплекс таблицы.
		*/

		void setIndexString(Plane* source, Plane* target);

		/*
		 * Данная функция задает значение фукнции
		 * цели в симплекс таблице.
		*/

		void setTargetFunction(Plane* source, Plane* target);

		/*
		 * Данная функция задает значения коэффициентов
		 * последнего столбца симплексной таблицы.
		*/

		void setThColumn(Plane*);

		/*
		 * Данная функция задает значение индекса ведущего
		 * столбца текущего плана симплексной таблицы.
		*/

		void setIndexOfLeavingColumn(Plane*);

		/*
		 * Данная функция задает значение индекса ведущей
		 * строки текущего плана симплексной таблицы.
		*/

		void setIndexOfLeavingRow(Plane*);

		/*
		 * Данная функция находит значение
		 * разрешающего элемента и возвращает его
		*/

		void setAllowingMember(Plane*);

//	private:
//		Plane<double> *currentPlane, *bestPlane;
//		SubPlane<double> *tmp;
private:
		Plane *old_plane, *new_plane;
};

/*где-то в конце итерации

if (error() || finished()) {
	print(best);
}
if (better(current, best)) {
	best = current;
}
*/


#endif