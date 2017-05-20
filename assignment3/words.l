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
	//yy_delete_buffer(YY_CURRENT_BUFFER);
	yylex_destroy();
	yyterminate();
}
