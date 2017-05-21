/* 
 * Credit to Definition and Rules sections
 *
 * Author: Darrell Long
 * Course: CMPS 12B Spring 2017
 */

%top{
# include <stdio.h>
}

LET [A-Za-z_]
DIG [0-9]
WS [ \t\r\n]
PUNC [~‘!@#$%^&*()_+-={}|\\\[\]:;\"\'\’`<>,./?]

%%

{LET}+				{ return 0; }
{LET}+"'"({LET}|{LET}{LET}) 	{ return 0; }
{LET}+{DIG}+			{ return 0; }
{PUNC}+				{}
{WS}+				{}
<<EOF>>				{ return -1; }
.				{}

%%

int freeFlexScanner(void)
{
	yylex_destroy();
	yyterminate();
}
