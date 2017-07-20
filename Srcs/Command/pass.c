/*
** pass.c for pass in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Thu May 18 16:34:41 2017 JSX
** Last update Mon May 22 00:40:09 2017 JSX
*/

#include "server.h"

int			passEntry(t_ftp* ftp, char* args)
{
  if (ftp->user->connected)
    assignRcode(230, "Already logged in", ftp);
  else if (ftp->user->username && (!args || !*args) &&
	   !strcmp("Anonymous", ftp->user->username)
	   && (ftp->user->connected = 1))
  	assignRcode(230, "User logged in, proceed", ftp);
  else
    {
      if (!(ftp->user->username))
  	    assignRcode(503, "Please, specify a user first", ftp);
      else if (ftp->user->username &&
	       strcmp("Anonymous", ftp->user->username))
        assignRcode(530, "Invalid User", ftp);
      else if (args && *args)
	      assignRcode(530, "Invalid password", ftp);
    }
  sendReturn(ftp, "PASS");
  cleanRcode(ftp);
  return (1);
}
