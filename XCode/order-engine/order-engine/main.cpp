//
//  main.cpp
//  order-engine
//
//  Created by Madhok Shivaratre on 5/5/13.
//  Copyright (c) 2013 Madhok Shivaratre. All rights reserved.
//

#include <iostream>

#include <iostream>
#include "src/jansson.h"
#include <fstream>
#include <string>
#include "OrderEngine.h"
#include "test.h"

using namespace std;

int main(int argc, char** argv)
{
	if(argc == 2 && string(argv[1]) == "TEST")
	{
		runTests();
	}
	else
	{
		string inputLine;
	  	ifstream myfile ("test.txt");
        
	    OrderEngine orderEngine;
	    
	    while ( myfile.good() && !myfile.eof())
	    {
	    	getline (myfile, inputLine);
	     	if (inputLine != "")
	  		{
	  			orderEngine.processOrderUpdate(inputLine);
	    	}
	    }
	    cout << orderEngine.getSummary();
	    
	    if(orderEngine.ErrorLog.str() != "")
	    {
	    	cout << "Errors found :" << endl;
	    	cout << orderEngine.ErrorLog.str();
	    }
	}
	
	return 0;
}
