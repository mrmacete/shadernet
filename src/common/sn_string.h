#ifndef SN_STRING_H
#define SN_STRING_H

typedef struct _sn_string
{
	char * buffer;
	unsigned long int len;
	int is_ref;
} sn_string;

sn_string * 	sn_string_create ( const char * c_str );
sn_string * 	sn_string_create_from_buffer( char * buffer, unsigned long int len );
sn_string *	sn_string_create_ref_from_buffer( char * buffer, unsigned long int len );

sn_string *	sn_string_clone ( const sn_string * p_src );
int		sn_string_cmp( const sn_string * p_left, const sn_string * p_right );
void		sn_string_cat( sn_string * p_dst, const sn_string * p_src );

sn_string *	sn_string_left ( const sn_string * p_string, unsigned long int len );
sn_string *	sn_string_right( const sn_string * p_string, unsigned long int len );
sn_string *	sn_string_mid( const sn_string * p_string, unsigned long int start, unsigned long int len );

void		sn_string_print( const sn_string * p_string );
	
void		sn_string_free( sn_string ** pp_string );	

#endif
