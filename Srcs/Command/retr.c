/*
** retr.c for retr in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:35:38 2017 JSX
** Last update Sun May 21 18:41:45 2017 JSX
*/

#include "server.h"

static void		retrCore(t_ftp* ftp, char* path)
{
  int					fd;
  char				buf[BUFF_SIZE];
  int					rsize;

  if ((fd = open(path, O_RDONLY)) == -1 &&
      assignRcode(550, "Can't download file.", ftp))
      return;
  assignRcode(150, "Starting download.", ftp);
  sendReturn(ftp, "RETR");
  cleanRcode(ftp);
  if ((ftp->dataSocket = accept(ftp->dataSocket,
				(struct sockaddr *)&(ftp->data), &(ftp->clientSize))) < 0)
    error(NULL, ftp->serverSocket);
  bzero(buf, BUFF_SIZE);
  while ((rsize = read(fd, buf, BUFF_SIZE)) > 0)
    {
      if (write(ftp->dataSocket, buf, rsize) < 0)
				error("write", ftp->serverSocket);
      bzero(buf, BUFF_SIZE);
    }
  assignRcode(226, "File downloaded.", ftp);
  if (shutdown(ftp->dataSocket, SHUT_RDWR) == -1
      || close(ftp->dataSocket) == -1)
		error("shutdown / close", ftp->serverSocket);
}

int			retrEntry(t_ftp* ftp, char* args)
{
  if (fork() == 0)
    {
      if (isLog(ftp))
				retrCore(ftp, args);
      sendReturn(ftp, "RETR");
      cleanRcode(ftp);
      exit(84);
    }
  return (1);
}
