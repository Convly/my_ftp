/*
** quit.c for quit in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:36:45 2017 JSX
** Last update Mon May 22 00:41:06 2017 JSX
*/

#include "server.h"

int			quitEntry(t_ftp* ftp, char* args)
{
  (void)args;
  assignRcode(221, "Quit", ftp);
  sendReturn(ftp, "QUIT");
  cleanRcode(ftp);
  shutdown(ftp->clientSocket, SHUT_RDWR);
  if (close(ftp->clientSocket) == -1)
    error("close", ftp->serverSocket);
  ftp->state = 0;
  return (1);
}
