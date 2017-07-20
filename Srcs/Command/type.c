/*
** type.c for type in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Thu May 18 22:29:46 2017 JSX
** Last update Sat May 20 13:19:40 2017 JSX
*/

#include "server.h"

int			typeEntry(t_ftp* ftp, char* args)
{
  if (args && *args == 'I')
    assignRcode(200, "Switching to binary mode", ftp);
  else
  	assignRcode(500, "Mode not handled", ftp);
  sendReturn(ftp, "TYPE");
  free(ftp->rcode->msg);
  ftp->rcode->msg = NULL;
  return (1);
}
