/*
** cdup.c for cdup in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:36:59 2017 JSX
** Last update Sat May 20 00:23:08 2017 JSX
*/

#include "server.h"

int			cdupEntry(t_ftp* ftp, char* args)
{
  (void)args;
  cwdEntry(ftp, "..");
  return (1);
}
