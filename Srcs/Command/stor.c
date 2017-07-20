/*
** stor.c for stor in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:35:30 2017 JSX
** Last update Sun May 21 18:51:45 2017 JSX
*/

#include "server.h"

static int		storErrorWrite(t_ftp* ftp)
{
  assignRcode(426, "Error while writing.", ftp);
  if (shutdown(ftp->dataSocket, SHUT_RDWR) == -1
      || close(ftp->dataSocket) == -1)
		error("shutdown / close", ftp->serverSocket);
  return (1);
}

static int		storErrorCreat(t_ftp *ftp)
{
  assignRcode(550, "Failed to create file.", ftp);
  if (shutdown(ftp->dataSocket, SHUT_RDWR) == -1
      || close(ftp->dataSocket) == -1)
		error("shutdown / close", ftp->serverSocket);
  return (1);
}

static void		storCore(t_ftp* ftp, char* path)
{
  int					fd;
  char				buf[BUFF_SIZE];
  int					rsize;

  assignRcode(150, "Starting upload.", ftp);
  sendReturn(ftp, "STOR");
  cleanRcode(ftp);
  if ((ftp->dataSocket = accept(ftp->dataSocket,
				(struct sockaddr *)&(ftp->data), &(ftp->clientSize))) < 0)
    error(NULL, ftp->serverSocket);
  if ((fd = creat(path, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1 &&
      storErrorCreat(ftp))
    return;
  bzero(buf, BUFF_SIZE);
  while ((rsize = read(ftp->dataSocket, buf, BUFF_SIZE)) > 0)
    {
      if (write(fd, buf, rsize) < 0 && storErrorWrite(ftp))
	  		return;
      bzero(buf, BUFF_SIZE);
    }
  assignRcode(226, "File uploaded.", ftp);
  if (shutdown(ftp->dataSocket, SHUT_RDWR) == -1
      || close(ftp->dataSocket) == -1)
    error("shutdown / close", ftp->serverSocket);
}

int			storEntry(t_ftp* ftp, char* args)
{
  if (fork() == 0)
    {
      if (isLog(ftp))
				storCore(ftp, args);
      sendReturn(ftp, "STOR");
      cleanRcode(ftp);
      exit(84);
    }
  return (1);
}
