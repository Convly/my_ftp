/*
** commands.c for command in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:06:16 2017 JSX
** Last update Sun May 21 16:52:35 2017 JSX
*/

#include "server.h"

t_tfcptr				gptrtab[16] =
    {
  		{"USER", &userEntry},
      {"PASS", &passEntry},
      {"TYPE", &typeEntry},
      {"CWD", &cwdEntry},
      {"CDUP", &cdupEntry},
      {"QUIT", &quitEntry},
      {"DELE", &deleEntry},
      {"PWD", &pwdEntry},
      {"PASV", &pasvEntry},
      {"HELP", &helpEntry},
  		{"NOOP", &noopEntry},
      {"RETR", &retrEntry},
      {"STOR", &storEntry},
      {"LIST", &listEntry},
  		{NULL, NULL}
		};

int			isLog(t_ftp* ftp)
{
  if (!ftp->user->connected)
    {
      ftp->rcode->code = 530;
      if ((ftp->rcode->msg = strdup("Not logged in")) == NULL)
        error("strdup", ftp->serverSocket);
      return (0);
    }
  return (1);
}

void		sendReturn(t_ftp* ftp, char* command)
{
  if (dprintf(ftp->clientSocket, "%d %s\r\n",
      ftp->rcode->code, (ftp->rcode->msg)? ftp->rcode->msg: "") < 0)
    error("dprintf", ftp->serverSocket);
  if (fprintf(stderr, "[%d]  %s\t%d: %s\n", ftp->clientSocket, command,
	      ftp->rcode->code, ftp->rcode->msg) <= 0)
    error("fprintf", ftp->serverSocket);
}

int			execCommand(char* command, char* args, t_ftp* ftp)
{
  int		i;

  i = 0;
  while (gptrtab[i].cmd != NULL)
    {
      if (!strcmp(gptrtab[i].cmd, command))
				return (gptrtab[i].function(ftp, args));
      i++;
    }
  ftp->rcode->code = 500;
  if ((ftp->rcode->msg = strdup("Unknown command")) == NULL)
    error("strdup", ftp->serverSocket);
  sendReturn(ftp, command);
  return (-1);
}

int			parseCmd(char* msg, t_ftp* ftp)
{
  char	*cmd;
  char	*args;
  char	*line;

  line = strtok(msg, "\r\n");
  while (ftp->state && line)
    {
      cmd = strsep(&line, " ");
      args = line;
      execCommand(cmd, args, ftp);
      line = strtok(NULL, "\r\n");
    }
  return (0);
}
