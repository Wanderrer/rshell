/*
 * File: And.h
 * -------------------------
 *
 * Created by Rick Boshae on 11/10/2016
 *
 */

#ifndef AND_H
#define AND_H

#include "Command.h"

class And : 
	public Command

{
	protected:
	//Command class has a bool value called success that is inherited here.
	Command* left_command;
	Command* right_command;

	public:
	/* Contructors */
	And() {};
	~And() {};
	And(Command* left_passed_command, Command* right_passed_command);

	bool execute();


};
#endif
