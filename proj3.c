//first parse the boot sector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


struct Fat32Img
{
        char OEMName[20];
        unsigned short bytesPerSec;
        unsigned short secPerCluster;
} fatImg;

int main()
{
        unsigned short tempBytes[10];

        FILE *fatimg = NULL;

        fatimg = fopen("fat32.img","rb");
        if(fatimg == NULL)
                printf("Unable to open\n");
        else
                printf("fat image opened\n");

        fseek(fatimg, 3, SEEK_SET);
        fread(fatImg.OEMName, 1, 8, fatimg);
        printf("OEM Name: %s \n", fatImg.OEMName);

       //bytes per sector
        fseek(fatimg, 11, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fatImg.bytesPerSec = tempBytes[0];
        printf("bytes per sector : %i\n", fatImg.bytesPerSec);

        fseek(fatimg, 13, SEEK_SET);
        fread(tempBytes, 1, 1, fatimg);
        fatImg.secPerCluster = htonl((unsigned int)tempBytes);
        printf("sec per cluster: %i \n", fatImg.secPerCluster);


        fclose(fatimg);
        return 0;
}
