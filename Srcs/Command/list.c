/*
** list.c for list in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:35:23 2017 JSX
** Last update Mon May 22 00:31:48 2017 JSX
*/

#include "server.h"

static void		listCore(t_ftp* ftp, char* args)
{
  int					oldfd;
  char				buf[BUFF_SIZE];

  assignRcode(150, "Data transfert ready.", ftp);
  sendReturn(ftp, "LIST");
  cleanRcode(ftp);
  if ((ftp->dataSocket = accept(ftp->dataSocket,
    (struct sockaddr *)&(ftp->data), &(ftp->clientSize))) < 0)
    error(NULL, ftp->serverSocket);
  if ((oldfd = dup(1)) == -1)
    error("dup", ftp->serverSocket);
  if (dup2(ftp->dataSocket, 1) == -1)
    error("dup2", ftp->serverSocket);
  bzero(buf, BUFF_SIZE);
  if (sprintf(buf, "/bin/ls -la %s | tail -n +2",
	      (args == NULL)? "": args) < 0)
    error("sprintf", ftp->serverSocket);
  if (system(buf) == -1)
    error("system", ftp->serverSocket);
  if (dup2(oldfd, 1) == -1)
    error("dup2", ftp->serverSocket);
  assignRcode(226, "Directory send OK.", ftp);
}

int			listEntry(t_ftp* ftp, char* args)
{
  if (fork() == 0)
    {
      if (isLog(ftp))
				listCore(ftp, args);
      sendReturn(ftp, "LIST");
      cleanRcode(ftp);
      shutdown(ftp->dataSocket, SHUT_RDWR);
      if (close(ftp->dataSocket) == -1)
				error("close", ftp->serverSocket);
      exit(84);
    }
  return (1);
}
