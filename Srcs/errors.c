/*
** errors.c for error in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 15:54:27 2017 JSX
** Last update Sun May 21 16:43:27 2017 JSX
*/

#include "server.h"

int		error(char *func, int server)
{
  perror(func);
  close(server);
  exit(EXIT_FAILURE);
  return (1);
}

int		rerror(const char* msg)
{
  if (fprintf(stderr, "%s\n", msg) < 0)
    return (-2);
  return (-1);
}
