#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFFER_SIZE 4096

int KeywordCheck(char str[]){ // in here we have function for key word control
        char WordKeys[32][10] = {"auto","break","case","char","const","continue","default",
                                  "unsigned","void","volatile","while",
                                  "sizeof","static","struct","switch","typedef","union",
                                  "if","int","long","register","return","short","signed",          
                                "do","double","else","enum","extern","float","for","goto"};
                                                        
                                                        
                                                         
                                          
                                                       
                                                                             
        int i;
        int WordKeysFlag = 0;
        
        for(i = 0; i < 32; ++i){
                if(strcmp(WordKeys[i],str) == 0){ // if  WordKeysFlag = 1 it is mean we have a keyword in file.
                        WordKeysFlag = 1;
                        break;
                }
        }
        
        return WordKeysFlag;
}                                                      //2016510102 HATTAP TAN
                                                        
int main()                                              
{
    FILE* inputfile; // for read file 
    FILE* outputfile;// for write a file.
         
    char buffer[BUFFER_SIZE];                 //     
                                              //    
    int wCheck = 0;                           //    
    int i;                                    //                                                    
	                                          //     
    int count;
    inputfile = fopen("code.Ceng", "r"); // open file for read
    outputfile = fopen ("code.lex", "w"); // Create a file and write into it 
    
     if (((inputfile = fopen("code.ceng", "r"))) == NULL)
	  {
      printf("File opening error ! \n");
      exit(1);                                                  
      }                                           
    
    while(fgets(buffer, BUFFER_SIZE, inputfile))
   {                                                                                                                                                         //while(a:=                                                                //
                                                  
    		char *word = buffer; // in here we have variable 
		    char  wordCheck[50];
		    char  CommentChechk[100];
		    char  numberCheck[10];
		    int   numberCount=0;
		    char tmpChar;
    	    int variableControlFlag=1;                                               // var:=var_15456+18,;,(*additonn*)
    	                                                                             // while( str="-*/+=:(){}";
    	    int lengthstr = strlen(word);                                            // var_1+var2;
    	    
    	  
    	    for(i=0; i<=lengthstr; i++)  // we get an line and in this for we check this line for possible situation                                                            // var:=var_1+18;   var_1++;
			{
				//in here we check invalid character
				if((int)word[i] ==33 ||  (int)word[i] ==63 || (int)word[i] ==39 || (int)word[i] ==35 || (int)word[i] ==60
				|| (int)word[i] ==62 || (int)word[i] ==38|| (int)word[i] ==124 || (int)word[i] ==37|| (int)word[i] ==47
				|| (int)word[i] ==94|| (int)word[i] ==64|| (int)word[i] ==36|| (int)word[i] ==44|| (int)word[i] ==46 )           
				{
					printf("Invalid Character : %c\n",word[i] );
					fprintf(outputfile,"Invalid Character : %c\n",word[i]);
				 //	exit(1);   
				}              

        	    int numFlag=0;                            
				if((int)word[i-1] !=95  ) // in here we check  "_" to understand for number, is it like  var_1  or only number                         
				{                          // to understand that number is connect variable (var_1) or it is number like (18)
					if((int)word[i-1] ==42 ||  (int)word[i-1] ==43 || (int)word[i-1]==61  || (int)word[i-1] ==45 || (int)word[i-1] ==47)
					{ // in here if it is number and next char is not + - * / +
						if(((int)word[i] < 97 || (int)word[i] > 122) && (int)word[i] !=34)
						{ char lwr4= tolower(word[i]);				   
				           word[i]=lwr4;
							numberCheck[numberCount]=word[i]; // we take that number
						 	numberCount++;
						 	numFlag=1;
						 	
						 while((int)word[i+1] !=42 &&  (int)word[i+1] !=43 && (int)word[i+1] !=59 &&  (int)word[i+1] !=45 && (int)word[i+1] !=47)
						 { //if number size more than 1
						 
						       char lwr5= tolower(word[i+1]);				   
				               word[i+1]=lwr5;
						 	numberCheck[numberCount]=word[i+1];
						 	numberCount++;
						 
						 
						 	numFlag=1;  
							 
							if((int)word[i+2] ==59)           
						    {
						    	break;
							}
						    
							i++;
						 
						 }
						}
						    
					}
					
				}
				if(numFlag==1)
				{   int iii=0;
				    int border=0;
				    int zero=0;
				    for(zero=0; zero<strlen(numberCheck); ++zero)
				    {
				    	if(numberCheck[zero]!=0)
				    	{
				    		border++; // in here we check numberCheck for make it without null value
						}
					}
				
					for(iii=0; iii<border; ++iii)
					{
						if(iii==0)
						{
								printf("IntConst(");
								fprintf(outputfile,"IntConst(");
						}
						if((int)numberCheck[iii]>=48 || (int)numberCheck[iii]<=57) // we write that number
						{
							printf("%c",numberCheck[iii]);
							fprintf(outputfile,"%c",numberCheck[iii]);
						}
					    if(iii==border-1)
						{
								printf(")\n");
								fprintf(outputfile,")\n");
						}
					}
				
			
					numFlag=0;
					numberCount=0;
					memset(numberCheck, 0, 7);
					iii=0;
				}
				
				// in here we control Bracket
			 	if( (int)word[i]==40 || (int)word[i]==41 || (int)word[i]==91|| (int)word[i]==93  || (int)word[i]==123|| (int)word[i]==125 )
				{
					if((int)word[i]==40)
					{
						printf("LeftPar\n");  // if left Par
					    fprintf(outputfile, "LeftPar\n");
					}
				    if((int)word[i]==41)
				    {
				    	printf("RightPar\n"); // if right Par
				    	fprintf(outputfile, "RightPar\n");
					}
				    if((int)word[i]==123)
					{
						printf("LeftCurlyBracket\n"); // if Left Curly Bracket
						fprintf(outputfile,"LeftCurlyBracket\n" );
					}
				    if((int)word[i]==125)
				    {
				    	printf("RightCurlyBracket\n"); // if right Curly Bracket
				    	fprintf(outputfile,"RightCurlyBracket\n" );
					}
					if((int)word[i]==91)
					{
						printf("RightCurlyBracket\n"); // if left square Bracket
						fprintf(outputfile,"RightCurlyBracket\n" );
					}
				    if((int)word[i]==93)
				    {
				    	printf("RightSquareBracket\n");// if right square Bracket
				    	fprintf(outputfile,"RightSquareBracket\n" );
					}
				
				}
				
				if((int)word[i]==58 && (int)word[i+1]==61)
				{
					printf("Operator(%c%c)\n",word[i],word[i+1]); // if operator :=
					fprintf(outputfile,"Operator(%c%c)\n",word[i],word[i+1] );
					i++;
				    i++;
				}
				if((int)word[i]==45 && (int)word[i+1]==45)
				{
					printf("Operator(%c%c)\n",word[i],word[i+1]); // if operator --
					fprintf(outputfile,"Operator(%c%c)\n",word[i],word[i+1] );
					i++;
				    i++;
				}
				if((int)word[i]==43 && (int)word[i+1]==43)
				{
					printf("Operator(%c%c)\n",word[i],word[i+1]); // if operator ++
					fprintf(outputfile,"Operator(%c%c)\n",word[i],word[i+1] );
					i++;
				    i++;
				}
				if((int)word[i]==42)
				{
					printf("Operator(%c)\n",word[i]); // if operator *
						fprintf(outputfile,"Operator(%c)\n",word[i] );
				}
				if((int)word[i]==43)
				{
					printf("Operator(%c)\n",word[i]); // if operator +
					fprintf(outputfile,"Operator(%c)\n",word[i] );
				}
			    if((int)word[i]==45)
				{
					printf("Operator(%c)\n",word[i]); // if operator -
					fprintf(outputfile,"Operator(%c)\n",word[i] );
				}
				if((int)word[i]==47)
				{
					printf("Operator(%c)\n",word[i]); // if operator /
					fprintf(outputfile,"Operator(%c)\n",word[i] );
				}
				if((int)word[i]==34) // in here we get string control
				{
					int strC=i;
					int zz=0;
					int strFlag=0;
					char strControl[50];
					while((int)word[strC+1]!=34)
					{
						 char lwr3= tolower(word[strC+1]);	// here is same in all class to make a letter to lower case			   
				         word[strC+1]=lwr3;
						strControl[zz]=word[strC+1];
						
						zz++;
						strC++;
						
					
						if((int)word[strC+1]==0)
						{
							printf("String Error\n"); // in this line we print screen and after print into file
							fprintf(outputfile,"String Error\n" );
							strFlag=1;
							break;
						}
					} // "hattap"
					
					if(strFlag != 1)
					{
						printf("String(%s)\n",strControl);
						fprintf(outputfile,"String(%s)\n",strControl );
					}
					strC++;
					strC++;
			    	
					i=strC;
				}
				
				
				
				if((int)word[i]==59)  // in here we check EndofLine and Comment.
				{    int oldValue=i;
				  
					printf("EndOfLine\n");  // (* 
					fprintf(outputfile,"EndOfLine\n");
					
					int countStar=0;
					int countLeftPar=0;
					int countRightPar=0; // 
					while((int)word[oldValue+1] !=0)
					{
					  if((int)word[oldValue+1] ==42)
					  {
					  	countStar++;
					  }
					  if((int)word[oldValue+1] ==40)  // 
					  {
					  	countLeftPar++;
					  }
					  if((int)word[oldValue+1] ==41)  // 
					  {
					  	countRightPar++;
					  }
					  oldValue++;
					}
					i=oldValue;
					if(countLeftPar!=countRightPar)
					{
						printf("There is a Comment Error because of Brackets!\n");
						fprintf(outputfile,"There is a Comment Error because of Brackets!\n");
					}
					if(countStar%2!=0)       //if stars amount is not satisfy with %2
					{
						printf("There is a Comment Error because of Stars!\n");
						fprintf(outputfile,"There is a Comment Error because of Stars!\n");
					}
					
				}
				if(variableControlFlag!=0)  //   in here we chack only alphabet and after to understand is it Identyfier or keyword      var_13  var:=var_12+18;(*additonn*) / * - + ; 
				{  
				     char lwr2= tolower(word[i]);				   
				     word[i]=lwr2;
    	         	if((((int)word[i] >= 97 && (int)word[i] <= 122) || (int)word[i] == 95 ) && (int)word[i] !=34 ) 
    	           {
    	           		char lwr6= tolower(word[i]);				   
				        word[i]=lwr6;
    	                wordCheck[wCheck]=word[i]; // we are collecting the incoming letters
    	                wCheck++;
    	              
    	                
    	                char lwrz= tolower(word[i+1]);				   
				        word[i+1]=lwrz;
    	                
                        if((int)word[i+1] != 95 && ((int)word[i+1] < 97 || (int)word[i+1] > 122)) // we controll next char is it in alphabet or no
						{
							variableControlFlag=0;
						}
					
						
						char lwrzo= tolower(word[i+1]);				   
				        word[i+1]=lwrzo;
							           
											
    	             	if( (int)word[i] == 95 && !((int)word[i+1] == 42 || (int)word[i+1] == 43 || (int)word[i+1] == 45 || (int)word[i+1] == 47|| (int)word[i+1] == 59 || (int)word[i+1] == 58))
    	             	{
    	             		char lwr1= tolower(word[i+1]);				   
				            word[i+1]=lwr1;
    	        	     	wordCheck[wCheck+1]=word[i+1]; // still we check for next char what is it
    	        	    
							 wCheck++; 
    	        		     i++;
    	        		     variableControlFlag=0;
    	        		   
    	        		     char lwrzz= tolower(word[i+1]);				   
				             word[i+1]=lwrzz;
    	        		     
						     if(((int)word[i+1] != 42 && (int)word[i+1] != 43 && (int)word[i+1] != 45 && (int)word[i+1] != 47 && (int)word[i+1] != 59 && (int)word[i+1] != 58))
						        {
						        	char lwrv= tolower(word[i+1]);				   
				                    word[i+1]=lwrv;
						        	wordCheck[wCheck+1]=word[i+1];
						        
						        	wCheck++;
						        	i++;
								}
    	        		
    	        		
				    	}
    	        	
				}
    	        }
    	        if(KeywordCheck(wordCheck) !=0) // We send the incoming word to the function and check whether it is a keyword.
			    	{
			    		printf("Keyword(%s)\n",wordCheck);
			    		fprintf(outputfile,"Keyword(%s)\n",wordCheck);
			    	    wCheck=0;
			         	memset(wordCheck,0,strlen(wordCheck));
			    	 	
					}
    	        if(variableControlFlag !=1) // if incoming word is Identifier
			    {
			    	
					if(KeywordCheck(wordCheck) !=1)
					{
						if((strlen(wordCheck))>20)
						{
							printf("Error! Identifiers size bigger than 20\n"); // check error if size bigger than 20
							fprintf(outputfile,"Error! Identifiers size bigger than 20\n");
							memset(wordCheck, 0, 15);
							wCheck=0;
							variableControlFlag=1;
						}else
						{
							printf("Identifiers(%s)\n",wordCheck);// if it provide us rules we accept it as an Identifier and than write into file
							fprintf(outputfile,"Identifiers(%s)\n",wordCheck);
					    	memset(wordCheck, 0, 15);
							wCheck=0;
							variableControlFlag=1;
						}

						
			
					}
				}
			     	 
				
				 
			
			}
    	   
 	
   }
    	
    fclose(outputfile);// close file
    fclose(inputfile);// close file
    return 0;
}
