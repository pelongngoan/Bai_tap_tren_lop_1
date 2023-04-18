#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#define MAX_SIZE 128
int main()
{
    // Khai bao socket
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // Khai bao dia chi cua server
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);
    // Ket noi den server
    int res = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (res == -1)
    {
        printf("Khong ket noi duoc den server!");
        return 1;
    }
    printf("Ket noi thanh cong den server\n");


    while (1)
    {
   

    char buffer[256];
    int pos = 0;

    char ten_may_tinh[64];
    printf("Nhap ten may tinh: ");
    scanf("%s", ten_may_tinh);

    int so_o_dia;
    printf("Nhap so o dia: ");
    scanf("%d", &so_o_dia);

    stpcpy(buffer, ten_may_tinh);
    pos = pos + strlen(ten_may_tinh);
    buffer[pos] = 0;

    getchar();

    char ten_o_dia;
    unsigned short kich_thuoc_o; 

    for (int i = 0; i < so_o_dia; i++)
    {
        printf("Nhap ten o: ");
        scanf("%c", &ten_o_dia);

        buffer[pos] = ten_o_dia;
        pos++;
        printf("Nhap kich thuoc: ");
        scanf("%hd", &kich_thuoc_o);
        getchar();


        memcpy(buffer, &kich_thuoc_o, sizeof(kich_thuoc_o));
        pos += sizeof(kich_thuoc_o);
    }

    printf("Kich thuoc buffer: %d\n", pos);

    send(client, buffer, pos, 0);
    
    }

    // Ket thuc, dong socket
    close(client);
    return 0;
}