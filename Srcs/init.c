/*
** init.c for init in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 15:52:41 2017 JSX
** Last update Sun May 21 13:58:26 2017 JSX
*/

#include "server.h"

static void	initUser(t_user *user)
{
  user->username = NULL;
  user->connected = 0;
}

static void	initRcode(t_rcode* rcode)
{
  rcode->msg = strdup("Welcome to my amazing ftp");
  rcode->code = 220;
}

static void	initServer(t_ftp* ftp)
{
  ftp->server.sin_family = AF_INET;
  ftp->server.sin_port = htons(ftp->port);
  ftp->server.sin_addr.s_addr = INADDR_ANY;
}

static void	initPath(t_ftp* ftp, char* gpath)
{
  char*			newpath;

  if (!(newpath = realpath(gpath, 0)))
	  error(gpath, ftp->serverSocket);
  ftp->homePath = strdup(newpath);
  if (chdir(ftp->homePath) == -1)
	  error(gpath, ftp->serverSocket);
}

int			initFtp(t_ftp* ftp, char** av)
{
  t_user*		user;
  t_rcode*	rcode;

  if (!(user = malloc(sizeof(t_user))) || !(rcode = malloc(sizeof(t_rcode))))
    error("malloc", -1);
  if ((ftp->port = atoi(av[1])) <= 0)
    return (-1);
  initUser(user);
  initRcode(rcode);
  initServer(ftp);
  initPath(ftp, av[2]);
  ftp->clientSize = sizeof(ftp->clientSize);
  if ((ftp->serverSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    error("socket", ftp->serverSocket);
  if (setsockopt(ftp->serverSocket, SOL_SOCKET, SO_REUSEPORT, &(int){1},
		 sizeof(int)) < 0)
    error("setsockopt", ftp->serverSocket);
  if (bind(ftp->serverSocket,
	   (const struct sockaddr*)&ftp->server, sizeof(ftp->server)) < 0 ||
      listen(ftp->serverSocket, QUEUE) < 0)
    error("bind", ftp->serverSocket);
  ftp->state = ftp->dataSocket = 1;
  ftp->rcode = rcode;
  ftp->user = user;
  return (0);
}
