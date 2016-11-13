/*
 * File: Parser.cpp
 * -------------------------
 *
 * Created by Rick Boshae, Sammy Macaluso, and Christopher Sultzbaugh on 11/10/2016
 * 
 *
 */

#include "Parser.h"

Parser::Parser()
{

}

Parser::~Parser()
{

}

void Parser::vecotrize(string user_input)
{
	//
	string tmp, tmp2;
	size_t foundSemi, foundSemi2;
	size_t foundAnd, foundAnd2;
	size_t foundOr, foundOr2;
	//size_t foundCom, foundCom2;
	size_t foundRP, foundRP2;
	size_t foundLP, foundLP2;
	
    for (unsigned int i = 0; i < user_input.size(); i++)
    {
    	if((user_input.at(i) == ';') || (user_input.at(i) == '(') || (user_input.at(i) == ')'))
    	{
    		user_input.insert(i, " ");
    		if(user_input.size() == i + 2)
    			break;
    		else
    		{
    			user_input.insert(i + 2 ," ");
    			i+=3;
    		}
    	}
    	if(user_input.at(i) == '&' && user_input.at(i+1) == '&')
    	{
    		user_input.insert(i, " ");
    		user_input.insert(i + 3 ," ");
    		i+=4;
    	}
    	if(user_input.at(i) == '|' && user_input.at(i+1) == '|')
    	{
    		user_input.insert(i, " ");
    		user_input.insert(i + 3," ");
    		i+=4;
    	}
    	//find and deal with quotation marks
    	//find and deal with comments
    }
    
		for (unsigned int i = 0; i < user_input.size(); i++)
		{
			boost::split(commands, user_input, boost::is_any_of(" "), boost::token_compress_on);
		}
		
		for (unsigned int i = 0; i < commands.size(); i++)
		{
		    for(unsigned int j = 0; j < commands.size() - 1; j++)
		    {
			    tmp = commands.at(j);
			    tmp2 = commands.at(j + 1);
			    foundSemi = tmp.find(';');
			    foundAnd = tmp.find('&');
			    foundOr = tmp.find('|');
			    foundRP = tmp.find(')');
			    foundLP = tmp.find('(');
			    foundSemi2 = tmp2.find(';');
			    foundAnd2 = tmp2.find('&');
			    foundOr2 = tmp2.find('|');
			    foundRP2 = tmp2.find(')');
			    foundLP2 = tmp2.find('(');
			    //foundCom = tmp.find('#');
				if(foundSemi2 != string::npos || foundAnd2 != string::npos || foundOr2 != string::npos || foundRP2 != string::npos || foundLP2 != string::npos) continue;
				else
				{
					if (commands.size() == j) continue;
					if (foundSemi != string::npos || foundAnd != string::npos || foundOr != string::npos || foundRP != string::npos || foundLP != string::npos) continue;
					else
					{
						commands.at(j) += " ";
						commands.at(j) += commands.at(j + 1);
						commands.erase(commands.begin() + (j + 1));
					}
				}
				if (foundSemi != string::npos || foundAnd != string::npos || foundOr != string::npos || foundRP != string::npos || foundLP != string::npos) continue;
		    }
		}
		
		//print vector
		// for (int i = 0; i < commands.size(); i++)
		// {
		// 	cout << commands.at(i) << endl;
		// }
	return; //commands;

}



Command* Parser::parse(string user_input)
{

   vecotrize(user_input); 
    
    /**********************************************
     * Token Bank
     * --------------------------------------------
     * list of tokens/delimeters used to build tree
	 **********************************************/
    string and_delimeter = "&&";
    string or_delimeter = "||";
    string semicolon_delimeter = ";";
    string comment_delimeter = "#";
    string exiter = "exit";
    string blank = "";
    
    string left_parentheses = "(";
    string right_parentheses = ")";
   //***********End of Token Bank****************
    
    
    Command* leftCmd; 
    Command* rightCmd; 
    string token = "";
    string command = "";
    string sub_command = "";
    int lp_count = 0;
    int rp_count = 0;
   
   
	
   /*****************************************************************************************************************************
     * Build Command Tree
     * ------------------------------------------------------------
     * Iterate through commands vector until it is empty. The loop
     * will contstruct a Command Tree based on the command or 
     * delimeter it receives.
     * 
	 ****************************************************************************************************************************/
   for(unsigned int index = 0; index < commands.size(); index++)
   {
		//Workaround - Getting an empty string at index 0 for some reason. We may need to investigate the vectorize function.
   		if (index > commands.size()) break;
   		if (blank.c_str() == commands.at(index)) index++;
   		if (index >= commands.size()) break;
   		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   		
   		
   		
   		
   		
   		
   		//---------------------------------------------Parentheses Handler---------------------------------------------------
   		if (left_parentheses.c_str() == commands.at(index)) //If commands at index is a parentheses jump in
   			{
   				lp_count++; //increment left parentheses count
   				index++;//now, jump past left parentheses
   				
   				while (lp_count != rp_count)//run while left parentheses does not have a matching right parentheses
   				{
   					if (commands.at(index) == left_parentheses.c_str()) lp_count++;//if we find another left parenthese, increment 
   				
   					if (commands.at(index) == right_parentheses.c_str()) rp_count++;//if we find a right parenthese, increment 

	  				//build a substring until hitting the right parentheses
   					sub_command.append(commands.at(index));
   					sub_command.append(" ");
   					index++;
   					if ((lp_count != rp_count) && ( commands.at(index) == right_parentheses.c_str())) rp_count++;
   				
   				}
   				//PRESERVED For Testing
   				//echo A && (echo B && (echo C || echo D))
   				//(echo B && (echo A && echo B))    (echo C && echo D)   
   				//(echo A) && (echo B)
   				
   				if(index < commands.size() && (commands.at(index) == right_parentheses.c_str())) index++;//skip past right parentheses
   				
   				
   				//recursive call parse
   				Parser* sub_parser = new Parser();
   			
   				leftCmd = sub_parser->parse(sub_command); //expect command to be returned then store in tree
   				//if (index >= commands.size()) continue;
   				//if (index >= commands.size()) break;
   				//continue; // avoids out of bounds error when parser is returned
   				
   				sub_command = ""; //reset sub_command after use
   				
   			}
   			//-----------------------END OF Parentheses---------------------------------------------------
   			
   			
   			
   		
   		
   		
 	//---------------------------------------------Statement Handler---------------------------------------------------
   		//if commands at index is not a delimeter then it is a statement.
   		if ((index < commands.size()) && (and_delimeter.c_str() != commands.at(index)) 
   														  && (or_delimeter.c_str() != commands.at(index))
   														  && (semicolon_delimeter.c_str() != commands.at(index))
   														  && (blank.c_str() != commands.at(index))
   														  && (index < commands.size())
   														  && (left_parentheses.c_str() != commands.at(index)))
   		{
   			leftCmd = new Statement(commands.at(index));
   			index++;
   			
   			
   			//handles the single command case.
   			if(index >= commands.size()) break; 
   		}
   		//-----------------------END OF Statement---------------------------------------------------------------------
   		
   		
   		
   		
   		/******************************Delimeter Cases********************************/
   		//If the command at index is a delimeter check which one it is and add the tree 
   		//-----------------------------And Case---------------------------------------
   		if((index < commands.size()) && (and_delimeter.c_str() == commands.at(index)))//if it is an And delimeter
   		{
   			index ++;//increment index to next delimeter
   			
   			//grab next string in index and stor it in  a statement
   			if ( left_parentheses.c_str() != commands.at(index))
   			{
   				rightCmd = new Statement(commands.at(index));
   				leftCmd = new And(leftCmd, rightCmd);
   			}
   			
   			else if (left_parentheses.c_str() == commands.at(index))
   			{
   				lp_count++;
   				
   				index++;//jump past left parentheses
   				
   				while (lp_count != rp_count)
   				{
   				if (commands.at(index) == left_parentheses.c_str()) lp_count++;
   				if (commands.at(index) == right_parentheses.c_str()) rp_count++;

   				//build a substring until hitting the right parentheses
   				sub_command.append(commands.at(index));
   				sub_command.append(" ");
   				index++;
   				if ((lp_count != rp_count) && ( commands.at(index) == right_parentheses.c_str())) rp_count++;
   				
   				}
   				//PRESERVED
   				//echo A && (echo B && (echo C && echo D))
   				//(echo B && (echo C && echo D))    (echo A && echo B)    
   				//skip past right parentheses
   				index++;
   				
   				
   				//recall parse
   				Parser* sub_parser = new Parser();
   				rightCmd = sub_parser->parse(sub_command); //expect command to be returned then store in tree
   				
   				//add sub tree to regular tree
   				leftCmd = new And(leftCmd, rightCmd);
   				sub_command = ""; //reset sub_command after use -- may be useless
   				
   			}
   		}
   		//------------------------------End of And Case---------------------------------
   		
   		
   		//--------------------------------Or Case---------------------------------------
   		if((index < commands.size()) && (or_delimeter.c_str() == commands.at(index)))
   		{
   			index ++;//increment index to next delimeter
   			//grab next string in index and stor it in  a statement
   			if ( left_parentheses.c_str() != commands.at(index))
   			{
   				rightCmd = new Statement(commands.at(index));
   				leftCmd = new Or(leftCmd, rightCmd);
   			}
   			
   			//CHECKS FOR PARENTHESES
   			else if (left_parentheses.c_str() == commands.at(index))
   			{
   				lp_count++;
   				index++;//jump past left parentheses
   				
   				while (lp_count != rp_count)
   				{
   				if (commands.at(index) == left_parentheses.c_str()) lp_count++;
   				if (commands.at(index) == right_parentheses.c_str()) rp_count++;

   				//build a substring until hitting the right parentheses
   				sub_command.append(commands.at(index));
   				sub_command.append(" ");
   				index++;
   				if ((lp_count != rp_count) && ( commands.at(index) == right_parentheses.c_str())) rp_count++;
   				
   				}
   				//PRESERVED
   				//echo A && (echo B && (echo C || echo D))
   				//(echo B && (echo C && echo D))    (echo C && echo D)    
   				//skip past right parentheses
   				index++;
   				
   				
   				//recall parse
   				Parser* sub_parser = new Parser();
   				rightCmd = sub_parser->parse(sub_command); //expect command to be returned then store in tree
   				
   				//add sub tree to regular tree
   				leftCmd = new Or(leftCmd, rightCmd);
   				sub_command = ""; //reset sub_command after use -- may be useless
   				
   				
   				
   			}
   		}
   		//------------------------------End of Or Case-------------------------------
   		
   		
   		
   		
   		//--------------------------------Semicolon Case---------------------------------------
   		
   		//trailing semicolon hack
   		if ((index < commands.size()) && (commands.at(commands.size() - 1) == semicolon_delimeter.c_str())) commands.at(commands.size() - 1) = ""; 
   			
   		if((index < commands.size()) && (semicolon_delimeter.c_str() == commands.at(index)))
   		{
   			index ++;//increment index to next delimeter
   			//grab next string in index and stor it in  a statement
   			if ( left_parentheses.c_str() != commands.at(index))
   			{
   				rightCmd = new Statement(commands.at(index));
   				leftCmd = new Semicolon(leftCmd, rightCmd);
   			}
   			
   			//CHECKS FOR PARENTHESES
   			else if (left_parentheses.c_str() == commands.at(index))
   			{
   				lp_count++;
   				index++;//jump past left parentheses
   				
   				while (lp_count != rp_count)
   				{
   				if (commands.at(index) == left_parentheses.c_str()) lp_count++;
   				if (commands.at(index) == right_parentheses.c_str()) rp_count++;

   				//build a substring until hitting the right parentheses
   				sub_command.append(commands.at(index));
   				sub_command.append(" ");
   				index++;
   				if ((lp_count != rp_count) && ( commands.at(index) == right_parentheses.c_str())) rp_count++;
   				
   				}
   				//PRESERVED
   				//echo A && (echo B && (echo C || echo D))
   				//(echo B && (echo C && echo D))    (echo C && echo D)    
   				//skip past right parentheses
   				index++;
   				
   				
   				//recall parse
   				Parser* sub_parser = new Parser();
   				rightCmd = sub_parser->parse(sub_command); //expect command to be returned then store in tree
   				
   				//add sub tree to regular tree
   				leftCmd = new Semicolon(leftCmd, rightCmd);
   				
   				sub_command = ""; //reset sub_command after use -- may be useless
   				
   			}
   		}
   		//------------------------------End of Semicolon Case-------------------------------
   		
   		/*************************End of Delimeter Cases**********************************/
   		
  
   }//end of for loop, commands vector is now empty
    //*********************End of Command Tree Builder************


    return leftCmd; // return built tree to caller.
}