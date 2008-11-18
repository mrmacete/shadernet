/*---------------------------------------------------------------------------*\
 *                              ShaderNet                                    *
 *                                                                           *
 *                Copyright (C) 2008 by Francesco Tamagni                    *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

int main(int argc, char*argv[] )
{
	char test[] = "if ( $inputs.val1 == $merda )";
	char toReplace[50];
	char toReplace1[50];
	char toReplace2[50];
	char * dollar = test;

	while(( dollar = strchr( dollar, '$' )) != NULL )
	{
		int rc = 0;
		char *point = NULL;
		rc = sscanf( dollar, "$%50[^ ;,!=]", toReplace );
		printf( "rc = %d [ %s ]\n", rc, toReplace );
		if (( point = strchr( toReplace, '.' )) != NULL )
		{
			int plen = strlen( point + 1 );
			if ( point-toReplace+1<sizeof(toReplace1))
			{
				strncpy( toReplace1, toReplace, point - toReplace );
				toReplace1[ point - toReplace ] = 0;	
			}

			strncpy( toReplace2, point + 1, sizeof( toReplace2 ) ); 		
			
			printf ( "%s -> %s\n", toReplace1, toReplace2 );
		}
		dollar++;
	}
}
