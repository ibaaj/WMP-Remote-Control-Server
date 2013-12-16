


/********************************
############# PSTE ##############
########### wmp_remote ##########
@ auteur : Ismail Baaj
@ date : 25/03/2011
@ fichier : main.c
@ description : serveur sockets
pour le controle à distance de WMP
#################################
#################################
********************************/

/////////// SOCKET /////////////////
#include <winsock2.h>
typedef int socklen_t;
#define PORT 23

/////////// CLASSIC /////////////////
#include <stdio.h>
#include <stdlib.h>


////////// WMP /////////////////
#include <windows.h>
#include <winuser.h>
#include <conio.h>

// DEFINITION DES CONSTANTES  [ << ] [ > ] [ o ] [ >> ] ..
#define WMP_PLAY	 18808
#define WMP_PAUSE	 18808
#define WMP_STOP	 18809
#define WMP_PLAY_FAST	 18834
#define WMP_PLAY_NORMAL	 18835
#define WMP_PLAY_SLOW	 18836
#define WMP_PREV	 18810
#define WMP_NEXT	 18811
#define WMP_FAST_FORWARD	 18813
#define WMP_SHUFFLE	 18842
#define WMP_REPEAT	 18843
#define WMP_VOLUME_UP	 18815
#define WMP_VOLUME_DOWN	 18816
#define WMP_VOLUME_MUTE	 18817

HWND player; // HWND ~ HANDLE WINDOWS ( fenêtre )


void gotoxy(int x, int y)
{
COORD coord;
coord.X = x;
coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}





int main(void)
{


    WSADATA WSAData;

     // ereur : 0 => OK, != => CACA
    int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);



    // définition des sockets serveur & client
    SOCKET sock;
    SOCKADDR_IN sin;

    SOCKET csock;
    SOCKADDR_IN csin;



    socklen_t recsize = sizeof(csin);
    int sock_err;

    // while_infinite : variable useless pour le plaisir d'avoir de variables pour créer des boucles infinies.
    int while_infinite = 0;
    int x,y; // gotoxy


    // chaine de caractère servant de buffet pour la soirée
    char buffer[32] = "";

    // Avec Windows, il faut vérifier si les sockets sont dispo et prêt, si tout est ok, erreur = 0 !
    if(!erreur)
    {
        // on enchaine, on lance un socket ....
        sock = socket(AF_INET, SOCK_STREAM, 0);

        // .... et on le test !
        if(sock != INVALID_SOCKET)
        {
            x = 25;
            y = 7;
            gotoxy(x,y);
            Sleep(500);
            printf(".##......##.##.....##.########.\n");
            gotoxy(x,y+1);
            Sleep(500);
            printf(".##..##..##.###...###.##.....##\n");
            gotoxy(x,y+2);
            Sleep(500);
            printf(".##..##..##.####.####.##.....##\n");
            gotoxy(x,y+3);
            Sleep(500);
            printf(".##..##..##.##.###.##.########.\n");
            gotoxy(x,y+4);
            Sleep(500);
            printf(".##..##..##.##.....##.##.......\n");
            gotoxy(x,y+5);
            Sleep(500);
            printf("..###..###..##.....##.##.......\n");
            printf("\n");
            gotoxy(x,y+7);
            printf("#########REMOTE SYSTEM##########\n\n");
            Sleep(500);
            gotoxy(x,y+9);
            printf(">>>>>>SOCKET SERVER");

            Sleep(500);
            gotoxy(0,22);
            printf(" BY ISMAIL BAAJ - PSTE.........................................................\n");
            printf("...............................................................................\n");


            Sleep(3000);

            system("CLS");





            Sleep(500);
            printf(" BIENVENUE ....................................................................\n");
            Sleep(500);
            printf(" > SOCKET SERVER ..............................................................\n");
            Sleep(500);


            gotoxy(0,3);
            printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);



            // CONFIGURATION  : adresse IP auto, protocole familiale, listage du port

            sin.sin_addr.s_addr    = htonl(INADDR_ANY);
            sin.sin_family         = AF_INET;
            sin.sin_port           = htons(PORT);
            sock_err = bind(sock, (SOCKADDR*)&sin, sizeof(sin));

            /* Si la socket fonctionne */
            if(sock_err != SOCKET_ERROR)
            {
                /* Démarrage du listage (mode server) */
                sock_err = listen(sock, 5);
                printf("Listage du port %d...\n", PORT);

                /* Si la socket fonctionne */
                if(sock_err != SOCKET_ERROR)
                {
                    /* Attente pendant laquelle le client se connecte */
                                    while(while_infinite != 42)
                {
                    printf("Patientez pendant que le client se connecte sur le port %d...\n", PORT);

                    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
                    printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));




                                   if(recv(csock, buffer, 32, 0) != SOCKET_ERROR)
                                    {
                                        //*buffer = trim(buffer);
                                        printf("Recu : %s\n", buffer);
                                               player = FindWindow("WMPlayerApp", NULL); // on recherche la fenetre de WMP
                                        if(player)
                                        {
                                            // si la fenetre existe


                                            // il faut savoir que je suis dans le train et j'écoute
                                            // SAY MY NAME de  Porter Robinson.


                                            // Ce C étant un langage magnifique, on ne peut pas faire un switch d'une chaine de caracteres.
                                            if(strcmp(buffer, "PLAY") == 0 ) SendMessage(player, WM_COMMAND, WMP_PLAY, 0);
                                            if(strcmp(buffer, "PAUSE") == 0 ) SendMessage(player, WM_COMMAND, WMP_PAUSE, 0);
                                            if(strcmp(buffer, "STOP") == 0 ) SendMessage(player, WM_COMMAND, WMP_STOP, 0);
                                            if(strcmp(buffer, "PLAY_FAST") == 0 ) SendMessage(player, WM_COMMAND, WMP_PLAY_FAST, 0);
                                            if(strcmp(buffer, "PLAY_NORMAL") == 0 ) SendMessage(player, WM_COMMAND, WMP_PLAY_NORMAL, 0);
                                            if(strcmp(buffer, "PLAY_SLOW") == 0 ) SendMessage(player, WM_COMMAND, WMP_PLAY_SLOW, 0);
                                            if(strcmp(buffer, "PREV") == 0 ) SendMessage(player, WM_COMMAND, WMP_PREV, 0);
                                            if(strcmp(buffer, "NEXT") == 0 ) SendMessage(player, WM_COMMAND, WMP_NEXT, 0);
                                            if(strcmp(buffer, "FAST_FOWARD") == 0 ) SendMessage(player, WM_COMMAND, WMP_FAST_FORWARD, 0);
                                            if(strcmp(buffer, "SHUFFLE") == 0 ) SendMessage(player, WM_COMMAND, WMP_SHUFFLE, 0);
                                            if(strcmp(buffer, "REPEAT") == 0 ) SendMessage(player, WM_COMMAND, WMP_REPEAT, 0);
                                            if(strcmp(buffer, "VOLUME_UP") == 0 ) SendMessage(player, WM_COMMAND, WMP_VOLUME_UP, 0);
                                            if(strcmp(buffer, "VOLUME_MUTE") == 0 ) SendMessage(player, WM_COMMAND, WMP_VOLUME_MUTE, 0);
                                            if(strcmp(buffer, "VOLUME_DOWN") == 0 ) SendMessage(player, WM_COMMAND, WMP_VOLUME_DOWN, 0);
                                            printf("DONE l'action %s a ete effectue avec succes \n", buffer);

                                               shutdown(csock, 2);

                                            }

                                        else
                                        {
                                            printf("FAIL : WMP N'EST PAS EN MARCHE MON ENFANT !\n");
                                        }

                                    memset (buffer, 0, sizeof (buffer));

                                    }

                }


                    /* Il ne faut pas oublier de fermer la connexion (fermée dans les deux sens) */
                   shutdown(csock, 2);
                }
            }

            /* Fermeture de la socket */
            printf("Fermeture de la socket...\n");
            closesocket(sock);
            printf("Fermeture du serveur terminee\n");
        }



            WSACleanup();

    }



    return EXIT_SUCCESS;
}
