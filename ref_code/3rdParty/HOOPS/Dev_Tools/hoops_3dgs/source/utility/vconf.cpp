
#include "vconf.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#pragma warning(disable: 4127 4996)
#endif

#ifdef HOOPS_DEFINED
#ifdef VMALLOC
#undef VMALLOC
#undef VFREE
#undef VMALLOC_ARRAY
#undef VFREE_ARRAY
#endif
#define VMALLOC(v, p, t) do{ \
	if (v->memory_pool){ \
		Memory_Pool * mp=v->memory_pool; POOL_ALLOC(p, t, mp); \
	} else { \
		(p)=(t*)HI_System_Alloc(sizeof(t)); \
	} \
} while(0)
#define VFREE(v, p, t) do{ \
	if (v->memory_pool){ \
		FREE(p, t); \
	} else { \
		HI_System_Free((void*)(p)); \
	} \
}while(0)
#define VMALLOC_ARRAY(v, p, c, t) do{ \
	if (v->memory_pool) { \
		Memory_Pool * mp=v->memory_pool;POOL_ALLOC_ARRAY(p, c, t, mp); \
	} else { \
		(p)=(t*)HI_System_Alloc(sizeof(t)*(c)); \
	} \
}while(0)
#define VFREE_ARRAY(v, p, c, t) do{ \
	if (v->memory_pool){ \
		FREE_ARRAY(p, c, t); \
	} else { \
		HI_System_Free((void*)(p)); \
	} \
}while(0)

VCONF_API vconf_t* VCONF_CDECL new_vconf(
	Memory_Pool * memory_pool)
#else
#define VMALLOC(v, p, t) do{(p)=(t*)v->vmalloc(sizeof(t));}while(0)
#define VFREE(v, p, t) do{v->vfree((void*)(p));}while(0)
#define VMALLOC_ARRAY(v, p, c, t) do{(p)=(t*)v->vmalloc(sizeof(t)*(c));}while(0)
#define VFREE_ARRAY(v, p, c, t) do{v->vfree((void*)(p));}while(0)

VCONF_API vconf_t* VCONF_CDECL new_vconf(
	void *(VCONF_CDECL *vconf_malloc) (size_t),
	void (VCONF_CDECL *vconf_free) (void *))
#endif
{
	vconf_t *vconf = 0;

#ifdef HOOPS_DEFINED
	if(memory_pool)
		POOL_ALLOC(vconf, vconf_t, memory_pool);
	else
		vconf = (vconf_t *)HI_System_Alloc(sizeof(vconf_t));

	vconf->memory_pool = memory_pool;

#else
	vconf = (vconf_t *) vconf_malloc(sizeof(vconf_t));
	vconf->vmalloc = vconf_malloc;
	vconf->vfree = vconf_free;
#endif

	vconf->delimiter = '=';
	vconf->style = VCONF_FILE_STYLE_FLAT;
	vconf->chunk = 0;

	vconf->filename = 0;
#ifdef HOOPS_DEFINED
	vconf->options_hash = new_vhash(1, vconf->memory_pool);
#else
	vconf->options_hash = new_vhash(1, vconf->vmalloc, vconf->vfree);
#endif
	vconf->options_list = 0;

	return vconf;
}

static void delete_options_helper(
	void * option, 
	const char * option_name, 
	void * user_data)
{
	vconf_t *v = (vconf_t*)user_data;

#if 0
	printf("%s %s %p\n", (char*)option_name, (char*)option, option);
#endif

	vhash_remove_string_key(v->options_hash, option_name);
	VFREE_ARRAY(v, option, strlen((char*)option)+1, char);
}

VCONF_API void VCONF_CDECL delete_vconf(
	vconf_t* v)
{
	if (v->filename)
		VFREE_ARRAY(v, v->filename, strlen(v->filename)+1, char);

	if (v->options_list) {
		/*chunked*/
		while ((v->options_hash = (vhash_t*)vlist_remove_first(v->options_list)) != 0) {
			vhash_string_key_map_function(v->options_hash, delete_options_helper, v);

			delete_vhash(v->options_hash) ;
		}

		delete_vlist(v->options_list);

	}
	else {
		/*flat*/
		vhash_string_key_map_function(v->options_hash, delete_options_helper, v);

		delete_vhash(v->options_hash);
	}

	VFREE(v, v, vconf_t);
}


VCONF_API void VCONF_CDECL vconf_clear_options(
	vconf_t* v)
{
	/*clear old options if any*/
	vhash_string_key_map_function(v->options_hash, delete_options_helper, v);
}

VCONF_API void VCONF_CDECL vconf_set_delimiter(
	vconf_t* vconf,
	char delimiter) 
{
	vconf->delimiter = delimiter;
}

VCONF_API int VCONF_CDECL vconf_set_file_style(
	vconf_t* v,
	int style) 
{
	if (v->style != VCONF_FILE_STYLE_CHUNKED &&
		v->style != VCONF_FILE_STYLE_FLAT) return 0;

	v->style = style;
	return 1;
}

VCONF_API unsigned int VCONF_CDECL vconf_option_count(
	vconf_t* v)
{
	if (!v->options_hash) return 0;
	return vhash_count(v->options_hash);
}

VCONF_API unsigned int VCONF_CDECL vconf_chunk_count(
	vconf_t* v)
{
	if (!v->options_list) return 0;
	return vlist_count(v->options_list);
}

VCONF_API int VCONF_CDECL vconf_set_chunk(
	vconf_t* v, 
	unsigned int chunk)
{
	if (v->style != VCONF_FILE_STYLE_CHUNKED) return 0;

	/*XXX this should extend the list instead*/
	if (chunk > vlist_count(v->options_list))
		chunk = vlist_count(v->options_list);

	v->chunk = chunk;
	v->options_hash = (vhash_t*)vlist_nth_item(v->options_list, v->chunk);
	return 1;
}

static void write_options_helper(
	void * option, 
	const char * option_name, 
	void * user_data)
{
	FILE *f = (FILE*)user_data;

	/*printf("%s \"%s\"\n", (char*)option_name, (char*)option);*/
	fprintf(f, "%s \"%s\"\n", (char*)option_name, (char*)option);
}

VCONF_API int VCONF_CDECL vconf_write_file(
	vconf_t* v, 
	const char * filename)
{
	FILE * f = fopen(filename, "w");

	if (f == NULL) return 0;

	if (v->options_list) {
		/*chunked*/
		vhash_t * hash;
		unsigned int i;

		for (i=0; i<vlist_count(v->options_list); i++) {
			hash = (vhash_t*)vlist_nth_item(v->options_list, i);

			vhash_string_key_map_function(
				hash, 
				write_options_helper, (void*)f);
		}

	}
	else {
		/*flat*/
		vhash_string_key_map_function(
			v->options_hash, 
			write_options_helper, (void*)f);
	}

	fclose(f);

	return 1;
}

VCONF_API int VCONF_CDECL vconf_read_file(
	vconf_t* v, 
	const char * filename)
{
	int filename_length = (int) strlen(filename);

	if (v->filename)
		VFREE_ARRAY(v, v->filename, strlen(v->filename)+1, char);

	VMALLOC_ARRAY(v, v->filename, filename_length+1, char);

	strcpy((char*)v->filename, filename);

	if (v->filename[0] != '\0'){
		FILE * file = 0;

		int read_again = 1;

		char * line_buffer = 0;
		unsigned long line_buffer_size = 0;

		int a_char = 0;
		int use_a_char = 0;

		unsigned long n;
		unsigned long i;

		char * option_type;
		char * option;

		file = fopen(v->filename, "rb");

		if (!file) return 0;

		fseek(file, 0, SEEK_SET);

		/*TODO make bigger later*/
		line_buffer_size = 1;
		VMALLOC_ARRAY(v, line_buffer, line_buffer_size, char);

READ_A_LINE:
		n = 0;
		while (1) {
			/*resize buffer as needed*/
			if (n == line_buffer_size) {
				char * new_line_buffer;

				VMALLOC_ARRAY(v, new_line_buffer, line_buffer_size*2, char);
				memcpy(new_line_buffer, line_buffer, line_buffer_size);

				VFREE_ARRAY(v, line_buffer, line_buffer_size, char);

				line_buffer = new_line_buffer;
				line_buffer_size = line_buffer_size*2;
			}

			if (use_a_char)
				use_a_char = 0;
			else
				a_char = fgetc(file);

			if (a_char == EOF) {
				read_again=0;
				line_buffer[n] = '\0';
				break;
			}

			if (a_char == 0x0D || a_char == 0x0A){
				int last_char = a_char;
				a_char = fgetc(file);
				if (a_char == 0x0D || a_char == 0x0A) {
					if (a_char == last_char) use_a_char = 1;
				}
				else
					use_a_char = 1;
				line_buffer[n] = '\0';
				break;
			}

			if (a_char == '\t' || a_char == '\0') a_char = ' ';

			line_buffer[n] = (char) a_char;

			n++;
		}/*while*/

		if (n == 0) {
			if (v->style == VCONF_FILE_STYLE_CHUNKED &&
				vhash_count(v->options_hash) > 0) {

#ifdef HOOPS_DEFINED
				if (!v->options_list) 
					v->options_list = new_vlist(v->memory_pool);

				vlist_add_last(v->options_list, (void*)v->options_hash);

				v->options_hash = new_vhash(1, v->memory_pool);
#else
				if (!v->options_list) 
					v->options_list = new_vlist(v->vmalloc, v->vfree);

				vlist_add_last(v->options_list, (void*)v->options_hash);

				v->options_hash = new_vhash(1, v->vmalloc, v->vfree);
#endif
			}

			goto PARSE_DONE;
		}

		i = 0;
#if 0
		printf("%s\n",&line_buffer[i]);
#endif

		while (i<n && line_buffer[i] == ' ') i++;

		if (line_buffer[i] == '\0') goto PARSE_DONE;

		if (line_buffer[i] == ';' || line_buffer[i] == '#') goto PARSE_DONE;

#if 0
		printf("%s\n",&line_buffer[i]);
#endif

		option_type = &line_buffer[i];

		while (i<n && (line_buffer[i] != ' ' && line_buffer[i] != v->delimiter)) i++;

		line_buffer[i] = '\0';
		/*default empty option*/
		option = &line_buffer[i];
		i++;

		/*once for space and once for = once more for space*/
		while (i<n && (line_buffer[i] == ' ' || line_buffer[i] == v->delimiter)) i++;
		while (i<n && (line_buffer[i] == ' ' || line_buffer[i] == v->delimiter)) i++;
		while (i<n && (line_buffer[i] == ' ' || line_buffer[i] == v->delimiter)) i++;

		if (line_buffer[i] == ';' || line_buffer[i] == '#') goto USE_PARSE;


		if (line_buffer[i] == '"') {
			/*quoted option*/
			i++;
			/*real option start*/
			option = &line_buffer[i];
			while(i<n && line_buffer[i] != '"') i++;
			line_buffer[i] = '\0';
			goto USE_PARSE;
		}

		if (line_buffer[i] == '\'') {
			/*quoted option*/
			i++;
			/*real option start*/
			option = &line_buffer[i];
			while(i<n && line_buffer[i] != '\'') i++;
			line_buffer[i] = '\0';
			goto USE_PARSE;
		}

		/*unquoted option*/
		/*real option start*/
		option = &line_buffer[i];
		while (i<n && (line_buffer[i] != '#' && line_buffer[i] != ';')) i++;
		/* backup over any blanks */
		while (line_buffer[i] == ' ') i--;
		line_buffer[i] = '\0';

USE_PARSE:
		{
			char * new_option = 0;
			char * old_option = 0;

			VMALLOC_ARRAY(v, new_option, strlen(option)+1, char);

			strcpy(new_option, option);

			old_option = (char*) vhash_remove_string_key(v->options_hash, option_type);

			vhash_insert_string_key(v->options_hash, option_type, new_option);

#if 0
			printf("%s %s %s %p %p\n", option_type, new_option, (char*)old_option ,new_option, old_option);
#endif

			if (old_option)
				VFREE_ARRAY(v, old_option, strlen(old_option)+1, char);
		}


PARSE_DONE:
		if (read_again)
			goto READ_A_LINE;

		fclose(file);

		if (line_buffer)
			VFREE_ARRAY(v, line_buffer, line_buffer_size, char);
	}

	if (v->style == VCONF_FILE_STYLE_CHUNKED) {
		if (!v->options_list)
#ifdef HOOPS_DEFINED
			v->options_list = new_vlist(v->memory_pool);
#else
			v->options_list = new_vlist(v->vmalloc, v->vfree);
#endif

		if (vhash_count(v->options_hash) > 0 || vlist_count(v->options_list) == 0) 
			vlist_add_last(v->options_list, (void*)v->options_hash);
		else 
			delete_vhash(v->options_hash);

		v->chunk = 0;
		v->options_hash = (vhash_t*)vlist_nth_item(v->options_list, v->chunk);
	}

	return 1;
}

VCONF_API const char* VCONF_CDECL vconf_get_filename(
	vconf_t* v)
{
	return v->filename;
}

VCONF_API vhash_t* VCONF_CDECL vconf_get_option_hash(
	vconf_t* v)
{
	return v->options_hash;
}


VCONF_API const char* VCONF_CDECL vconf_get_option(
	vconf_t* v, 
	const char * option)
{
	return (const char *) vhash_lookup_string_key(v->options_hash, option);
}

VCONF_API void VCONF_CDECL vconf_set_option(
	vconf_t* v, 
	const char * option_type,
	const char * option)
{
	char * old_option = 0;
	char * new_option = 0;

	VMALLOC_ARRAY(v, new_option, strlen(option)+1, char);

	strcpy(new_option, option);

	old_option = (char*) vhash_remove_string_key(v->options_hash, option_type);

	vhash_insert_string_key(v->options_hash, option_type, new_option);

	/*
	printf("%s %s %s %p %p\n", option_type, new_option, (char*)old_option ,new_option, old_option);
	*/

	if(old_option) 
		VFREE_ARRAY(v, old_option, strlen(old_option)+1, char);
}




