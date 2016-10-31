/*
 * File: Or.h
 * -------------------------
 *
 * Created by Rick Boshae on 10/30/2016
 *
 */

#ifndef OR_H
#define OR_H

#include "Argument.h"

class Or : public Argument

{
	protected:
	Argument* left_argument;
	Argument* right_argument;

	public:
	/* Contructors */
	Or();
	~Or();
	Or(Argument* x, Argument* y);

	int execute();


};
#endif
