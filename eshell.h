#ifndef _ESHELL_H_
#define _ESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **cpy_env;


/**
 * struct liststr - singly linked list
 * @data: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int data;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@argu: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@str_path: a string path for the current command
 *@argc: the argument count
 *@err_count: the error count
 *@err_code: the error code for exit()s
 *@lineinput_count: if on count this line of input
 *@f_name: the program filename
 *@list_env: linked list local copy of environ
 *@cpy_env: custom modified copy of environ from LL env
 *@hist_nd: the history node
 *@alias_nd: the alias node
 *@environ_changed: on if environ was changed
 *@ret_status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buf, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@read_fd: the fd from which to read line input
 *@hist_count: the history line number count
 */
typedef struct passinfo
{
	char *argu;
	char **argv;
	char *str_path;
	int argc;
	unsigned int err_count;
	int err_code;
	int lineinput_count;
	char *f_name;
	list_t *list_env;
	list_t *hist_nd;
	list_t *alias_nd;
	char **cpy_env;
	int environ_changed;
	int ret_status;

	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int read_fd;
	int hist_count;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@flag_type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *flag_type;
	int (*func)(info_t *);
} builtin_table;


/* shell_loop.c */
int hsh(info_t *f, char **ag);
int find_built_in(info_t *f);
void cmd_find(info_t *f);
void cmd_fork(info_t *f);

/* parser.c */
int is_cmd(info_t *f, char *path_file);
char *dup_chars(char *strpath, int begin, int end);
char *find_command(info_t *f, char *strpath, char *cm_d);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _wputs(char *st);
int _wputchar(char ch);
int _putfd(char ch, int file_d);
int _putsfd(char *st, int file_d);

/* string.c */
int _lenstr(char *string);
int _cmpstr(char *string1, char *string2);
char *starts_hay(const char *hayst, const char *nee);
char *_catstr(char *dest_str, char *src_str);

/* string1.c */
char *_cpystr(char *dest_str, char *src_str);
char *_dupstr(const char *string);
void _puts(char *string);
int _putchar(char ch);

/* exits.c */
char *_cpynstr(char *str_dest, char *str_src, int num);
char *_catnstr(char *dest_str, char *src_str, int num);
char *_chrstr(char *st, char ch);

/* tokenizer.c */
char **towstr(char *string, char *del);
char **towstr2(char *string, char del);

/* realloc.c */
char *mem_set(char *ma, char byte, unsigned int num);
void free_string_array(char **arr);
void *my_realloc(void *pt, unsigned int old_byte, unsigned int new_byte);

/* memory.c */
int free_and_null(void **pt);

/* str_to_int.c */
int interactive(info_t *info);
int delim(char a, char *del);
int isAlphabetic(int ch);
int str_to_int(char *st);

/* errors1.c */
int _erratoi(char *st);
void print_errmessage(info_t *f, char *estrg);
int print_decimal(int inp, int file_d);
char *convert_num(long int numb, int bs, int flg);
void replace_hash(char *buff);

/* builtin.c */
int _shexit(info_t *f);
int _chcd(info_t *f);
int _chcdp(info_t *f);

/* builtin1.c */
int _disphist(info_t *f);
int alias_to_string(info_t *f, char *st);
int alias_set(info_t *f, char *s);
int print_alias_string(list_t *nd);
int _alias_mimic(info_t *f);

/* getline.c */
ssize_t input_buff(info_t *f, char **buff, size_t *l);
ssize_t get_input(info_t *f);
ssize_t read_buff(info_t *f, char *buff, size_t *a);
int _getline(info_t *f, char **pt, size_t *l);
void sigintHandler(__attribute__((unused))int sig_num);

/* getinfo.c */
void clear_info(info_t *f);
void free_info(info_t *f, int every);
void set_info(info_t *f, char **av);

/* environ.c */
int _curr_env(info_t *f);
char *_get_env(info_t *f, const char *varname);
int _mysetenv(info_t *f);
int _myunsetenv(info_t *f);
int populate_envlinked_list(info_t *f);

/* getenv.c */
char **get_env(info_t *f);
int _unsetenv(info_t *f, char *val);
int _setenv(info_t *f, char *va, char *val);

/* history.c */
char *get_hist_file(info_t *f);
int write_hist(info_t *f);
int read_hist(info_t *f);
int build_hist_linkedlist(info_t *f, char *buff, int l_count);
int renumb_hist(info_t *f);

/* lists.c */
list_t *add_Node(list_t **hd, const char *st, int number);
list_t *add_node_to_end(list_t **hd, const char *st, int number);
size_t print_list_str(const list_t *hd);
int delete_node_at_index(list_t **hd, unsigned int idx);
void free_list(list_t **hd_pt);

/* lists1.c */
size_t count_Nodes(const list_t *hd);
char **list_to_array(list_t *hd);
size_t print_list_element(const list_t *hd);
list_t *find_Node(list_t *nd, char *pref, char z);
ssize_t Node_Index(list_t *hd, list_t *nd);

/* vars.c */
int del_chain(info_t *f, char *buff, size_t *ptr);
void cont_chain(info_t *f, char *buff, size_t *ptr, size_t a, size_t l);
int _alias(info_t *f);
int var_replace(info_t *f);
int str_replace(char **old_ptr, char *new_ptr);

#endif
