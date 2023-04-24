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
#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

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

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{

	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct node - singly linked list
 * @str: pionter ti string
 * @data: data to be inputted
 * @next: pointer to the next node
 */
typedef struct nodestr
{
	int data;
	char *str;
	struct nodestr *next;
} node_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;
/* hsh */
int hsh(info_t *f, char **av);

/* paser.c header file */
char *find_command(info_t *f, char *strpath, char *cmd);
char *dup_chars(char *strpath, int begin, int end);
int is_cmd(info_t *info, char *path);

/* errors.c header file */
int _wputchar(char ch);
int _putfd(char ch, int fdes);
int _putsfd(char *string, int fdes);
void _wputs(char *str);

/* errors1.c header */

char *convert_num(long int numb, int base, int flags);
int print_decimal(int in, int d);
void print_errmessage(info_t *f, char *estrg);
int _erratoi(const char *str);
void replace_hash(char *str);

/* str.c */

int _lenstr(char st[]);
int _cmpstr(char *st1, char *st2);
void _catstr(char st1[], char st2[]);
char starts_hay(const char *haystack, const char *needle);

/* str1.c */

char *_cpystr(char *dest_str, const char *src_str);
char *_dupstr(const char ori_str[]);
void _puts(char st[]);
int _putchar(char ch);

/* exits.c */
size_t _chrstr(const char *str, char ch);
void _catnstr(char *str_dest, const char *str_src, size_t a);
void _cpynstr(char *str_dest, const char *str_src, int a);

/* tokenizers.c */
char **towstr(char *st, char *del);
char **towstr2(char *st, char del);

/* realloc.c */
void *my_realloc(void *ptr, size_t old_bk, size_t new_bk);
void *mem_set(void *ptr, int val, size_t num);
void free_string_array(char **string_array);

/* memory.c */
void free_and_null(void **ptr);

/* str_to_it.c */
int str_to_int(char *str);
int delim(char ch, char *del);
int shell_inter(info_t *sh);
int isAlphabetic(char ch);

/* builtin.c */
int _shexit(info_t *f);
int _chcd(info_t *f);
int _chcdp(info_t *f);

/* builtin1.c */
int _disphist(info_t *f);
int alias_to_string(info_t *f, char *string);
int alias_set(info_t *f, char *string);
int print_alias_string(list_t *nd);
int _alias_mimic(info_t *f);

/* getline.c */
ssize_t input_buff(info_t *f, char **buff, size_t *l);
ssize_t get_input(info_t *f);
ssize_t read_buff(info_t *f, char *buff, size_t *j);
int _getline(info_t *f, char **pt, size_t *l);
void sigintHandler(__attribute__((unused))int sig_num);

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
char *hist_file(info_t *f);
int write_hist(info_t *f);
int read_hist(info_t *f);
int build_hist_linkedlist(info_t *f, char *buff, int lcount);
int renumb_hist(info_t *f);

/* linked_list.c */
list_t *add_Node(list_t **h,char *st, int data);
list_t *add_node_to_end(list_t **head_ref, const char *st, int data);
void print_list_str(list_t *list);
int delete_node_at_index(list_t **head_ref, int index);
void free_List(list_t *head);

/* linked_list1.c */
int count_Nodes(list_t *head);
char **list_to_array(list_t *h_ref);
size_t print_list_element(const list_t *h_ref);
int Node_Index(list_t *h_ref, list_t *nd_ref);
list_t *find_Node(list_t *nd, char *pref, char a);

/* variables.c */
int del_chain(info_t *f, char *bf, size_t *ps);
void cont_chain(info_t *f, char *bf, size_t *ps, size_t s, size_t l);
int _alias(info_t *f);
int var_replace(info_t *f);
int str_replace(char **d, char *n);

/* getinfo.c */
void clear_info(info_t *f);
void set_info(info_t *f, char **av);
void free_info(info_t *f, int every);

#endif
