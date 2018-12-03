//first parse the boot sector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


char *fatImgName;
struct BS_struct fat_32;
FILE *fatimg = NULL;


struct FSInfo_struct {
        unsigned char   FSI_Reserved2[12];
        unsigned char   FSI_Reserved1[480];
        unsigned int    FSI_TrailSig;
        unsigned int    FSI_LeadSig;
        unsigned int    FSI_StrucSig;
        unsigned int    FSI_Free_Count;
        unsigned int    FSI_Nxt_Free;
}; //__attribute__((packed));



struct BS_struct {
        unsigned char   BS_jmpBoot[3];
        unsigned char   BS_OEMName[8];
        unsigned char   BS_NumFATs;
        unsigned char   BS_SecPerClus;
        unsigned char   BS_Media;
        unsigned char   BS_Reserved[12];
        unsigned char   BS_DrvNum;
        unsigned char   BS_Reserved1;
        unsigned char   BS_BootSig;
        unsigned char   BS_VolLab[11];
        unsigned char   BS_FilSysType[8];
        unsigned short  BS_BytsPerSec;
        unsigned short  BS_RsvdSecCnt;
        unsigned short  BS_RootEntCnt;
        unsigned short  BS_TotSec16;
        unsigned short  BS_FATSz16;
        unsigned short  BS_SecPerTrk;
        unsigned short  BS_NumHeads;
        unsigned short  BS_ExtFlags;
        unsigned short  BS_FSVer;
        unsigned short  BS_FSI_info;
        unsigned short  BS_BkBootSec;
        unsigned int    BS_HiddSec;
        unsigned int    BS_TotSec32;
        unsigned int    BS_FATSz32;
        unsigned int    BS_VolID;
        unsigned int    BS_RootClus;
}; //__attribute__((packed));


struct Fat32Img
{
        char OEMName[20];
        unsigned short bytesPerSec;
        unsigned short secPerCluster;
} fatImg;

int main(int argc)
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
        char op[10];
        char command[10];



	if (argc == 1){

                if (fatimg = fopen("fat32.img", "rb")){

                        fatImgName = "fat32.img";
                        while(1){
                                printf("command: ");
                                scanf("%s", command);

                                if (strcmp(command, "exit") == 0){
                                        fclose(fatimg);
                                        break;
                                }
                                else if(strcmp(command, "info") == 0){
                                        printf("going to info function");
                                        info();
                                }
                                else if (strcmp(command, "ls") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //ls(op);

				}
                                else if (strcmp(command, "cd") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //cd(op);
                                }
                                else if (strcmp(command, "size") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //size(op);
                                }
                                else if (strcmp(command, "creat") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //create(name);
                                }
                                else if (strcmp(command, "mkdir") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //mkdir(name);
                                }
                                else if (strcmp(command, "open") == 0){
                                        scanf("%s", op);
                                        scanf("%s", mode);
					getchar();
                                        //open(op, mode);
                                }
                                else if (strcmp(command, "close") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //close(op);
                                }
                                else if (strcmp(command, "read") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //read(op);
                                }
                                else if (strcmp(command, "write") == 0){
                                        scanf("%s", op);
                                        getchar();
                                        //write(op);
                                }

				/*EXTRA CREDIT

                                else if (strcmp(command, "rm") == 0){
                                
                                }
                                else if (strcmp(command, "rmdir") == 0){
                                
                                }*/

				else
                                        printf("You have entered an invalid command\n");
                        }
                }
                else{
                        printf("Could not find FAT_32 image!\n");
                        return 0;
                }
        }
        else{
                printf("Incorrect number of arguments!\n");
                return 0;
        }

        fclose(fatimg);
        return 0;
}





void info() {

        long offset;
        struct FSInfo_struct FAT_FSI_info;
        offset = fat_32.BS_FSI_info * fat_32.BS_BytsPerSec;

        fseek(fatimg, offset, SEEK_SET);
        fread(&FAT_FSI_info, sizeof(struct FSInfo_struct), 1, fatimg);
        printf("Sectors per Cluster: %d\n", fat_32.BS_SecPerClus);
        printf("Total Sectors: %d\n", fat_32.BS_TotSec32);
        printf("Sectors per FAT: %d\n", fat_32.BS_FATSz32);
        printf("Number of FATs: %d\n", fat_32.BS_NumFATs);
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
