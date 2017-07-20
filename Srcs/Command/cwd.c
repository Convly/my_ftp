/*
** cwd.c for cwd in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Fri May 19 22:56:28 2017 JSX
** Last update Sun May 21 16:49:01 2017 JSX
*/

#include "server.h"

char*						getRealPath(t_ftp* ftp, char* path)
{
  char					pathBuf[BUFF_SIZE];

  if (!path || !*path)
    return (NULL);
  bzero(pathBuf, BUFF_SIZE);
  if (*path == '/')
    {
      if (sprintf(pathBuf, "%s%s", ftp->homePath, path) < 0)
				error("sprintf", ftp->serverSocket);
    }
  else
		{
      if (sprintf(pathBuf, "%s", realpath(path, 0)) < 0)
        error("sprintf", ftp->serverSocket);
    }
  return (strdup(pathBuf));
}

int			cwdEntry(t_ftp* ftp, char* args)
{
  char	path[PATH_MAX + 3];
  char*	newPath;

  if (isLog(ftp))
    {
      bzero(path, PATH_MAX + 3);
      newPath = getRealPath(ftp, args);
      if (newPath && !strncmp(newPath, ftp->homePath,
			      strlen(ftp->homePath)))
				{
	  			if (sprintf(path, "\"%s\"", newPath) < 0)
	    			error("sprintf", ftp->serverSocket);
	  			if (chdir(newPath) == -1)
	          assignRcode(550, "Invalid path", ftp);
	  			else
	          assignRcode(250, path, ftp);
				}
      else
	      assignRcode(550, "Forbidden path", ftp);
    }
  free(newPath);
  sendReturn(ftp, "CWD");
  cleanRcode(ftp);
  return (1);
}
