/*
** main.c for main in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 15:43:56 2017 JSX
** Last update Mon May 22 00:42:28 2017 JSX
*/

#include "server.h"

static	int			newClient(int clientSocket, t_ftp ftp)
{
  int						rsize;
  char					message[BUFF_SIZE];

  ftp.clientSocket = clientSocket;
  if (fork() == 0)
    {
      if (fprintf(stderr, "New client (%d)\n", clientSocket) < 0)
				error("fprintf", ftp.serverSocket);
      sendReturn(&ftp, "WELCOME");
      bzero(message, BUFF_SIZE);
      while (ftp.state &&
	     (rsize = read(ftp.clientSocket, message, BUFF_SIZE)) > 0)
				{
					parseCmd(message, &ftp);
	  			bzero(message, BUFF_SIZE);
				}
      if (fprintf(stderr, "Client (%d) disconnected\n", clientSocket) < 0)
				error("fprintf", ftp.serverSocket);
      exit(84);
    }
  return (0);
}

int					main(int ac, char **av, char** env)
{
  t_ftp			ftp;
  int				clientSocket;

  if (!env || !*env)
    return (rerror("No env found"));
  if (ac != 3)
    return (rerror("No enough args"));
  if (initFtp(&ftp, av) == -1)
    return (rerror("Bad port (must be int > 0)"));
  while (ftp.state)
    {
      if ((clientSocket = accept(ftp.serverSocket,
        (struct sockaddr *)&ftp.server, &ftp.clientSize)) < 0)
        error(NULL, ftp.serverSocket);
      newClient(clientSocket, ftp);
    }
  if (close(ftp.serverSocket) < 0)
  	error("close", ftp.serverSocket);
}
