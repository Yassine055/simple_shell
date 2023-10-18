#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;

/**
 * struct DT_SH - structure qui contient
 * toutes les données pertinentes lors
 * de l'exécution
 * @arGS: jetons de la ligne de commande
 * @inpUT: ligne de commande écrite par l'utilisateur
 * @statUS: dernier statut du shell
 * @countER: compteur de lignes
 * @_environ: variable d'environnement
 * @pID: ID de processus du shell
 * @aV: vecteur d'argument
*/
typedef struct DT_SH
{
	char **arGS;
	char *inpUT;
	int statUS;
	int countER;
	char **_environ;
	char *pID;
	char **aV;
} DT_SH;

/**
 * struct sList - single linked list
 * @separateur: ; | &
 * @suivante: next node
 * Description: single linked list to store separators
*/
typedef struct sList
{
	char separateur;
	struct sList *suivante;
} sList;

/**
 * struct lList - liste chaînée unique
 * @ligne: ligne de commande
 * @suivant: nœud suivant
 * Description: liste chaînée unique
 * pour stocker les lignes de commande
*/
typedef struct lList
{
	char *ligne;
	struct lList *suivant;
} lList;

/**
 * struct rVar - liste chaînée unique
 * @lenVar: longueur de la variable
 * @vAL: valeur de la variable
 * @lenVal: longueur de la valeur
 * @suivant: nœud suivant
 * Description: liste chaînée unique pour stocker les variables
*/
typedef struct rVar
{
	int lenVar;
	char *vAL;
	int lenVal;
	struct rVar *suivant;
} rVar;

/**
 * struct BuiltinT - Structure intégrée pour les arguments de commande.
 * @nom: Le nom de la commande intégrée, c'est-à-dire cd, exit, env
 * @F: fonction de pointeur de type de données.
*/
typedef struct BuiltinT
{
	char *nom;
	int (*F)(DT_SH *dataSH);
} BuiltinT;

sList *addSNEnd(sList **heAD, char sEP);
void freeSList(sList **heAD);
lList *addLNEnd(lList **heAD, char *liNE);
void freeLList(lList **heAD);
rVar *addrVarNode(rVar **heAD, int lVar, char *vAR, int lVal);
void freerVarList(rVar **heAD);

void mC(void *newP, const void *pTR, unsigned int siZE);
void *rC(void *pTR, unsigned int oldSiZE, unsigned int newSiZE);
char **rCDP(char **pTR, unsigned int oldSiZE, unsigned int newSiZE);

char *strCAT(char *deST, const char *sRC);
char *strCPY(char *deST, char *sRC);
int strCMP(char *sOne, char *sTow);
char *strCHR(char *a, char b);
int strSPN(char *a, char *acc);

char *strDUP(const char *a);
int strLEN(const char *a);
int cmpCHars(char sr[], const char *delim);
char *strT(char sr[], const char *deLIM);
int isDgit(const char *a);

void revSrg(char *a);

int repeatEDCHar(char *input, int b);
int errSO(char *in, int b, char la);
int firstCH(char *input, int *b);
void print_syntax_error(DT_SH *datash, char *in, int b, int bool);
int check_syntax_error(DT_SH *datash, char *in);

char *without_comment(char *in);
void sheLoop(DT_SH *dataSH);

char *readLine(int *iEof);
char *swapCHar(char *in, int looP);
void addNodes(sList **headS, lList **headL, char *in);
void Next(sList **ls, lList **ll, DT_SH *dataSH);
int spComm(DT_SH *dataSH, char *in);
char **spLine(char *in);

void checkEV(rVar **h, char *in, DT_SH *data);
int checkVR(rVar **h, char *in, char *st, DT_SH *data);
char *replaCT(rVar **heAD, char *in, char *newIPT, int nLn);
char *repVar(char *in, DT_SH *dataSH);

void bringLine(char **linePTR, size_t *n, char *buffER, size_t i);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

int exeLine(DT_SH *dataSH);

int Cdir(char *path, int *i);
char *whiCH(char *cmd, char **_environ);
int EXecutTB(DT_SH *dataSH);
int checkErrcmd(char *dir, DT_SH *datash);
int cmdEX(DT_SH *dataSh);

char *getENV(const char *nome, char **_environ);
int eNV(DT_SH *dataSH);

char *coINF(char *nome, char *VL);
void setENV(char *name, char *value, DT_SH *datash);
int envSET(DT_SH *dataSH);
int unSetEnv(DT_SH *dataSH);

void cdDot(DT_SH *dataSH);
void cdTo(DT_SH *dataSH);
void cdPrevious(DT_SH *dataSH);
void cdToHome(DT_SH *dataSH);

int cdSHell(DT_SH *dataSH);

int (*getB(char *cmd))(DT_SH *dataSH);
int exitSH(DT_SH *dataSH);

int getLen(int r);
char *aIt(int r);
int iota(char *a);

char *strCD(DT_SH *, char *, char *, char *);
char *errGetCd(DT_SH *dataSH);
char *errNotF(DT_SH *dataSH);
char *errExitSH(DT_SH *dataSH);

char *errGetAlias(char **ar);
char *errEnv(DT_SH *dataSH);
char *errSyntax(char **ar);
char *errPerm(char **ar);
char *errPath(DT_SH *dataSH);
int getErr(DT_SH *dataSH, int eVl);
void getSig(int sg);
void helpENV(void);
void helpSTenv(void);
void helpUNSenv(void);
void helpG(void);
void helpEX(void);
void help(void);
void helpAL(void);
void helpCD(void);
int hEllP(DT_SH *dataSH);

#endif
