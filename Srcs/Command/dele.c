/*
** dele.c for dele in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:36:33 2017 JSX
** Last update Sun May 21 13:04:42 2017 JSX
*/

#include "server.h"

int			deleEntry(t_ftp* ftp, char* args)
{
  char*	path;

  if (isLog(ftp))
    {
      if ((path = getRealPath(ftp, args)) && remove(path) >= 0)
      	assignRcode(250, "File deleted.", ftp);
      else
				assignRcode(550, "Error while delete operation.", ftp);
    }
  sendReturn(ftp, "LIST");
  cleanRcode(ftp);
  return (1);
}
