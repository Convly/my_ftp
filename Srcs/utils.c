/*
** utils.c for utils in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/Srcs/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Fri May 19 13:20:39 2017 JSX
** Last update Sun May 21 13:38:23 2017 JSX
*/

#include "server.h"

int		assignRcode(int code, char* msg, t_ftp* ftp)
{
  ftp->rcode->code = code;
  if ((ftp->rcode->msg = strdup(msg)) == NULL)
    error("strdup", ftp->serverSocket);
  return (1);
}

void		cleanRcode(t_ftp* ftp)
{
  if (ftp->rcode->msg != NULL)
  	free(ftp->rcode->msg);
  ftp->rcode->msg = NULL;
}

int			strreplace(char* str, char d, char r)
{
  int		i;
  int		c;

  i = 0;
  if (!str)
    return (-1);
  while (str[i])
    {
      if (str[i] == d)
				{
          str[i] = r;
	  			c++;
				}
      i++;
    }
  return (c);
}
