/*
** noop.c for noop in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:35:45 2017 JSX
** Last update Sat May 20 00:07:41 2017 JSX
*/

#include "server.h"

int			noopEntry(t_ftp* ftp, char* args)
{
  (void)args;
  if (isLog(ftp))
    {
      ftp->rcode->code = 200;
      if ((ftp->rcode->msg = strdup("Noop ok")) == NULL)
      	error("strdup", ftp->serverSocket);
    }
  sendReturn(ftp, "NOOP");
  cleanRcode(ftp);
  return (1);
}
