/*
* File: Command.h
* ------------------
*
* Created by Rick Boshae on 11/10/16.
*
*/

#ifndef COMMAND_H
#define COMMAND_H

//Ton of includes, i dont know why they're here
//#include <iostream>
//#include <string>
//#include <stack>
//#include <queue>
//#include <vector>
//#include <pwd.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
//#include <climits>
//#include <cstring>
//#include <string>
//#include "Command.h"
//#include "Statement.h"
//#include "And.h"
//#include "Or.h"
//#include <algorithm> 
//#include <boost/algorithm/string/classification.hpp> // Include boost::for is_any_of
//#include <boost/algorithm/string/split.hpp> // Include for boost::split


//Abstract base class in rshell. 
class Command
{
private:

protected:
	bool success; //used to determine whether rhs command will execute. This will be dependent on the data type.
public:
	/* Contructors */
	Command();
	~Command();

	virtual bool execute() = 0;
};

#endif 