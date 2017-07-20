/*
** help.c for help in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:35:53 2017 JSX
** Last update Sun May 21 13:41:44 2017 JSX
*/

#include "server.h"

static void		helpSpec(t_ftp* ftp, char* args)
{
  int					i;
  int					found;

  i = found = 0;
  while (gptrtab[i].cmd)
    {
      if (strstr(gptrtab[i].cmd, args))
				{
          if (dprintf(ftp->clientSocket, "%c%s", (found)? '\t': ' ',
		      		gptrtab[i].cmd) < 0)
          	error("dprintf", ftp->serverSocket);
          found += 1;
				}
      i++;
    }
  if (!found)
    {
      if (dprintf(ftp->clientSocket,
		  			"No command found with string \"%s\"", args) < 0)
				error("dprintf", ftp->serverSocket);
    }
    if (dprintf(ftp->clientSocket, "\r\n") < 0)
      error("dprintf", ftp->serverSocket);
}

static void		helpGen(t_ftp* ftp)
{
  int					i;

  i = 0;
  while (gptrtab[i].cmd)
    {
      if (dprintf(ftp->clientSocket, "%c%s", (i)? '\t': ' ',
		  		gptrtab[i].cmd) < 0)
	  		error("dprintf", ftp->serverSocket);
      i++;
    }
	if (dprintf(ftp->clientSocket, "\r\n") < 0)
  	error("dprintf", ftp->serverSocket);
}

int						helpEntry(t_ftp* ftp, char* args)
{
  if (isLog(ftp))
    {
      assignRcode(214, "Let's give you some help.", ftp);
      sendReturn(ftp, "HELP");
      cleanRcode(ftp);
      if (args && *args)
				helpSpec(ftp, args);
      else
				helpGen(ftp);
      assignRcode(214, "Help OK.", ftp);
    }
  sendReturn(ftp, "HELP");
  cleanRcode(ftp);
  return (1);
}
