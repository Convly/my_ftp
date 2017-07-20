/*
** pasv.c for pasv in /home/jsx/Epitech/tek2/PSU/ftp/PSU_2016_myftp/FTPServer/Srcs/Command/
**
** Made by JSX
** Login   <jean-sebastien.herbaux@epitech.eu>
**
** Started on  Tue May 16 21:36:14 2017 JSX
** Last update Sat May 20 00:07:22 2017 JSX
*/

#include "server.h"

static char*	getAddrIp(int fd, struct sockaddr_in *addr)
{
  socklen_t 	socklen;
  char*				ipstr;

  socklen = sizeof(*addr);
  if (getsockname(fd, (struct sockaddr *)addr, &socklen) == 1)
    return (NULL);
  ipstr = inet_ntoa(addr->sin_addr);
  strreplace(ipstr, '.', ',');
  return (ipstr);
}

static void						pasvCore(t_ftp* ftp)
{
	size_t							port;
	char								ipstr[4096];

	if ((ftp->dataSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		error("socket", ftp->serverSocket);
	ftp->data.sin_family = AF_INET;
	ftp->data.sin_port = htons((port = 1025));
	ftp->data.sin_addr.s_addr = INADDR_ANY;
	while (bind(ftp->dataSocket,
		(const struct sockaddr*)&ftp->data, ftp->clientSize) < 0)
		ftp->data.sin_port = htons((port = rand() % (65635 - 1024) + 1024));
	bzero(ipstr, 4096);
	if (sprintf(ipstr, "Entering passive mode (%s,%lu,%lu)",
		    getAddrIp(ftp->clientSocket, &(ftp->server)),
		    port / 256, port % 256) < 0)
		error("sprintf", ftp->serverSocket);
  assignRcode(227, ipstr, ftp);
	if (listen(ftp->dataSocket, 1) == -1)
		error("listen", ftp->serverSocket);
}

int										pasvEntry(t_ftp* ftp, char* args)
{
  (void)args;
  if (isLog(ftp))
    pasvCore(ftp);
  sendReturn(ftp, "PASV");
  cleanRcode(ftp);
  return (1);
}
