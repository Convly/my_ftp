/*
** server.h for server in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Includes/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 15:53:05 2017 JSX
** Last update Sun May 21 14:00:30 2017 JSX
*/

#ifndef SERVER_H_
#define SERVER_H_

#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

# define	QUEUE  10
# define	BUFF_SIZE	4096

typedef	struct			s_rcode
{
  int								code;
  char*							msg;
}										t_rcode;

typedef	struct				s_user
{
  int									connected;
  char*								username;
}											t_user;

typedef	struct				s_ftp
{
  int									serverSocket;
  int									clientSocket;
  int									dataSocket;
  struct sockaddr_in	server;
  struct sockaddr_in	data;
  int									state;
  int									port;
  socklen_t						clientSize;
  t_user*							user;
  t_rcode*						rcode;
  char*								homePath;
}											t_ftp;

typedef	struct				s_tfcptr
{
  char*								cmd;
  int									(*function)(t_ftp*, char* args);
}											t_tfcptr;

extern t_tfcptr				gptrtab[16];

int			error(char*, int);
int			rerror(const char*);
int			execCommand(char*, char*, t_ftp*);
void		sendReturn(t_ftp*, char*);
int			isLog(t_ftp*);
int			assignRcode(int, char*, t_ftp*);
void		cleanRcode(t_ftp*);
int			parseCmd(char*, t_ftp*);
int			initFtp(t_ftp*, char**);
int			strreplace(char*, char, char);
char*		getRealPath(t_ftp*, char*);
/* USER */
int			userEntry(t_ftp*, char*);
int			passEntry(t_ftp*, char*);
int			pwdEntry(t_ftp*, char*);
int			typeEntry(t_ftp*, char*);
int			pasvEntry(t_ftp*, char*);
int			listEntry(t_ftp*, char*);
int			quitEntry(t_ftp*, char*);
int			cwdEntry(t_ftp*, char*);
int			cdupEntry(t_ftp*, char*);
int			noopEntry(t_ftp*, char*);
int			helpEntry(t_ftp*, char*);
int			deleEntry(t_ftp*, char*);
int			storEntry(t_ftp*, char*);
int			retrEntry(t_ftp*, char*);
#endif /* end of include guard: SERVER_H_ */
