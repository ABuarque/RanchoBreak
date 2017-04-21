#ifndef STRINGHANDLING_H
#define STRINGHANDLING_H

typedef char* String;

enum _boolean {false, true};
typedef enum _boolean boolean;

//Check if it is char
boolean isChar(char c); 
//Check if it is capital char
boolean isCapitalChar(char c);
//Check if it is small char 
boolean isSmallChar(char c); 
//Check how many 'char' there are
int checkOccurence(String string, char c); 
//Return the string size
int stringSize(String string);
//Make it capital 
char getCapitalChar(char c);
//Make it small 
char getSmallChar(char c); 
//Make it in capital size
String lowerToUpper(String string);
//Make it in small size 
String upperToLower(String string); 
//Copy the s2 in s1
String copyString(String s1, String s2);
//Parses an integer into a string
String intToString(int integer);
//Parses a intring in a integer
int stringToInt(String string);
//Compare to strings (1: true, 0: false)
boolean isEqual(String, String); 

//Contatenate two strings
String concat(String, String);

//get a substring from begin till and icluding end
String substring(String s, int begin, int end);

#endif
