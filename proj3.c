//first parse the boot sector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


char *fatImgName;
struct FAT_32 fat_32;
FILE *fatimg = NULL;


struct FSI {
        unsigned char   FSI_Reserved2[12];
        unsigned char   FSI_Reserved1[480];
        unsigned int    FSI_TrailSig;
        unsigned int    FSI_LeadSig;
        unsigned int    FSI_StrucSig;
        unsigned int    FSI_Free_Count;
        unsigned int    FSI_Nxt_Free;
}; //__attribute__((packed));



struct FAT_32 {
        unsigned char   FAT_jmpBoot[3];
        unsigned char   FAT_OEMName[8];
        unsigned char   FAT_NumFATs;
        unsigned char   FAT_SecPerClus;
        unsigned char   FAT_Media;
        unsigned char   FAT_Reserved[12];
        unsigned char   FAT_DrvNum;
        unsigned char   FAT_Reserved1;
        unsigned char   FAT_BootSig;
        unsigned char   FAT_VolLab[11];
        unsigned char   FAT_FilSysType[8];
        unsigned short  FAT_BytsPerSec;
        unsigned short  FAT_RsvdSecCnt;
        unsigned short  FAT_RootEntCnt;
        unsigned short  FAT_TotSec16;
        unsigned short  FAT_FATSz16;
        unsigned short  FAT_SecPerTrk;
        unsigned short  FAT_NumHeads;
        unsigned short  FAT_ExtFlags;
        unsigned short  FAT_FSVer;
        unsigned short  FAT_FSI_info;
        unsigned short  FAT_BkBootSec;
        unsigned int    FAT_HiddSec;
        unsigned int    FAT_TotSec32;
        unsigned int    FAT_FATSz32;
        unsigned int    FAT_VolID;
        unsigned int    FAT_RootClus;
}; //__attribute__((packed));


struct Fat32Img
{
        char OEMName[20];
        unsigned short bytesPerSec;
        unsigned short secPerCluster;
} fatImg;

int main()
{
        unsigned short tempBytes[10];

        //FILE *fatimg = NULL;

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

	char mode[1];
        char name[13];
        char operation[6];



	if (argc == 1){

                if (fatimg = fopen("fat32.img", "rb")){

                        fatImgName = "fat32.img";
                        for(;;){
                                printf("command: ");
                                scanf("%s", operation);

                                if (strcmp(operation, "exit") == 0){
                                        fclose(fatimg);
                                        break;
                                }
                                else if(strcmp(operation, "info") == 0){
                                        printf("going to info function");
                                        info();
                                }
                                else if (strcmp(operation, "ls") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        //ls(name);

				}
                                else if (strcmp(operation, "cd") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        cd(name);
                                }
                                else if (strcmp(operation, "size") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        size(name);
                                }
                                else if (strcmp(operation, "creat") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        create(name);
                                }
                                else if (strcmp(operation, "mkdir") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        mkdir(name);
                                }
                                else if (strcmp(operation, "open") == 0){
                                        scanf("%s", name);
                                        scanf("%s", mode);
					getchar();
                                        open(name, mode);
                                }
                                else if (strcmp(operation, "close") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        close(name);
                                }
                                else if (strcmp(operation, "read") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        read(name);
                                }
                                else if (strcmp(operation, "write") == 0){
                                        scanf("%s", name);
                                        getchar();
                                        write(name);
                                }

				/*EXTRA CREDIT

                                else if (strcmp(operation, "rm") == 0){
                                
                                }
                                else if (strcmp(operation, "rmdir") == 0){
                                
                                }*/

				else
                                        printf("Incorrect arguments! Need <info, ls, cd, create, fopen, fclose, fread, fwrite, rm, mkdir, rmdir, exit>\n");
                        }
                }
                else{
                        printf("Could not find FAT_32 image!\n");
                        return -1;
                }
        }
        else{
                printf("Incorrect number of arguments!\n");
                return -1;
        }

        fclose(fatimg);
        return 0;
}





void info() {

        long offset;
        struct FSI FAT_FSI_info;
        offset = fat_32.FAT_FSI_info * fat_32.FAT_BytsPerSec;

        fseek(fatimg, offset, SEEK_SET);
        fread(&FAT_FSI_info, sizeof(struct FSI), 1, fatimg);
        printf("Number of free Sectors: %d\n", FAT_FSI_info.FSI_Free_Count);
        printf("Sectors per Cluster: %d\n", fat_32.FAT_SecPerClus);
        printf("Total Sectors: %d\n", fat_32.FAT_TotSec32);
        printf("Sectors per FAT: %d\n", fat_32.FAT_FATSz32);
        printf("Number of FATs: %d\n", fat_32.FAT_NumFATs);
        return 0;
}


void ls() {


}

void cd() {


}
void size() {


}
void creat() {


}
void mkdir() {


}
void open() {


}
void close() {


}

void read() {


}
void write() {


}
/*
 * void rm() {
 *
 *
 * }
 * void rmdir() {
 *
 *
 * }
 * */
