/*
** pwd.c for pwd in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:36:22 2017 JSX
** Last update Sat May 20 00:06:30 2017 JSX
*/

#include "server.h"

int			pwdEntry(t_ftp* ftp, char* args)
{
  char	path[PATH_MAX + 1];

  if (isLog(ftp))
    {
      bzero(path, PATH_MAX + 1);
      (void)args;
      if (!strcmp(getcwd(NULL, 0), ftp->homePath))
				*path = '/';
      else if (sprintf(path, "\"%s\"", getcwd(NULL, 0)
		       + strlen(ftp->homePath)) < 0)
      	error("sprintf", ftp->serverSocket);
      assignRcode(257, path, ftp);
    }
  sendReturn(ftp, "PWD");
  cleanRcode(ftp);
  return (1);
}
