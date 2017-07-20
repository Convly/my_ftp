/*
** user.c for user in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Wed May 17 12:40:31 2017 JSX
** Last update Sat May 20 13:41:25 2017 JSX
*/

#include "server.h"

int			userEntry(t_ftp* ftp, char* args)
{
  if (args && !(ftp->user->connected))
  	{
      assignRcode(331, "Need password.", ftp);
      if ((ftp->user->username = strdup(args)) == NULL)
				error("strdup", ftp->serverSocket);
  	}
  else
    assignRcode(530, "Bad login.", ftp);
  sendReturn(ftp, "USER");
  free(ftp->rcode->msg);
  ftp->rcode->msg = NULL;
  return (1);
}
