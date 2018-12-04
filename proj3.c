//first parse the boot sector
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>


#define END_OF_CLUSTER 0x0FFFFFF8
#define ATTRIBUTE_NAME_LONG 0x0F
#define ENTRY_LAST 0x00
#define ENTRY_EMPTY 0xE5
#define ATTR_CONST 0x20
#define CLUSTER_END 0xFFFFFFFF
#define OFFSET_CONST 32




char *fatImgName;
struct BS_struct fat_32;
//FILE *fatimg;

unsigned int parentCluster;
unsigned int currCluster;


void info();
int ls(char * op);
void cd(char * op);
void size(char * op);
void creat(char * op);
void mkdir(char * op);
void open(char * op, char *mode);
void close(char * op, char *mode);
void read(char * op);
void write(char * op);


struct FSInfo_struct {
	unsigned char   FSI_Reserved2[12];
        unsigned char   FSI_Reserved1[480];
        unsigned int    FSI_TrailSig;
        unsigned int    FSI_LeadSig;
        unsigned int    FSI_StrucSig;
        unsigned int    FSI_Free_Count;
	unsigned int FSI_Nxt_Free;
}; //__attribute__((packed));



struct BS_struct {
	unsigned char   BS_jmpBoot[3];
        unsigned char   BS_OEMName[8];
        unsigned char   BPB_NumFATs;
        unsigned char   BPB_SecPerClus;
        unsigned char   BPB_Media;
        unsigned char   BPB_Reserved[12];
        unsigned char   BS_DrvNum;
        unsigned char   BS_Reserved1;
        unsigned char   BS_BootSig;
        unsigned char   BS_VolLab[11];
        unsigned char   BS_FilSysType[8];
        unsigned short  BPB_BytsPerSec;
        unsigned short  BPB_RsvdSecCnt;
        unsigned short  BPB_RootEntCnt;
        unsigned short  BPB_TotSec16;
        unsigned short  BPB_FATSz16;
        unsigned short  BPB_SecPerTrk;
        unsigned short  BPB_NumHeads;
        unsigned short  BPB_ExtFlags;
        unsigned short  BPB_FSVer;
        unsigned short  BPB_FSInfo;
        unsigned short  BPB_BkBootSec;
        unsigned int    BPB_HiddSec;
        unsigned int    BPB_TotSec32;
        unsigned int    BPB_FATSz32;
        unsigned int    BPB_VolID;
	unsigned int    BPB_RootClus;
}; //__attribute__((packed));

struct DIR{
        char   DIR_Name[11];
        char   DIR_Attr;
        char   DIR_NTRes;
        char   DIR_CrtTimeTenth;
        short  DIR_CrtTime;
        short  DIR_CrtDate;
        short  DIR_LstAccDate;
        short  DIR_FstClusHI;
        short  DIR_WrtTime;
        short  DIR_WrtDate;
        short  DIR_FstClusLO;
        int    DIR_FileSize;
}; //__attribute__((packed));



struct Fat32Img
{
        char OEMName[20];
        unsigned short bytesPerSec;
        unsigned short secPerCluster;
} fatImg;


FILE *fatimg = NULL;




int main(int argc)
{
        unsigned short tempBytes[10];

        //FILE *fatimg = NULL; made this global so functions could access

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
        fat_32.BPB_BytsPerSec = tempBytes[0];

	//sec per cluster
	fseek(fatimg, 13, SEEK_SET);
        fread(tempBytes,1, 1, fatimg);
        fat_32.BPB_SecPerClus = tempBytes[0];

	//reserved sec 
	fseek(fatimg, 14, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_RsvdSecCnt = tempBytes[0];


	//num fat
	fseek(fatimg, 16, SEEK_SET);
        fread(tempBytes,1, 1, fatimg);
        fat_32.BPB_NumFATs = tempBytes[0];
	
	//root ent
	fseek(fatimg, 17, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_RootEntCnt = tempBytes[0];

	//total sec 16
	fseek(fatimg, 19, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_TotSec16 = tempBytes[0];


	//media 
	fseek(fatimg, 21, SEEK_SET);
        fread(tempBytes,1, 1, fatimg);
        fat_32.BPB_Media = tempBytes[0];


	// fat 16
	fseek(fatimg, 22, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_FATSz16 = tempBytes[0];


	//sec per track
	fseek(fatimg, 24, SEEK_SET);
        fread(tempBytes,1, 4, fatimg);
        fat_32.BPB_SecPerTrk = tempBytes[0];

	//num heads
	fseek(fatimg, 26, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_NumHeads = tempBytes[0];
	

	//Hidd sec
	fseek(fatimg, 28, SEEK_SET);
        fread(tempBytes,1, 4, fatimg);
        fat_32.BPB_HiddSec = tempBytes[0];


	//total sec
	fseek(fatimg, 32, SEEK_SET);
        fread(tempBytes,1, 4, fatimg);
        fat_32.BPB_TotSec32 = tempBytes[0];

	//fat 32
	fseek(fatimg, 36, SEEK_SET);
        fread(tempBytes,1, 4, fatimg);
        fat_32.BPB_FATSz32 = tempBytes[0];

	//flags
	fseek(fatimg, 40, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_ExtFlags = tempBytes[0];
	
	//svr
	fseek(fatimg, 42, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_FSVer = tempBytes[0];


	//root clus
	fseek(fatimg, 44, SEEK_SET);
        fread(tempBytes,1, 4, fatimg);
        fat_32.BPB_RootClus = tempBytes[0];

	//fs info
	fseek(fatimg, 48, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_FSInfo = tempBytes[0];


	//boot sec
	fseek(fatimg, 50, SEEK_SET);
        fread(tempBytes,1, 2, fatimg);
        fat_32.BPB_BkBootSec = tempBytes[0];

	char mode[1];
        char op[10];



	if (argc == 1){

                if (fatimg = fopen("fat32.img", "rb")){

                        fatImgName = "fat32.img";
			while(1){
                                printf("\ncommand: ");
                                scanf("%s", op);

                                if (strcmp(op, "exit") == 0){
                                        fclose(fatimg);
                                        break;
                                }
                                else if(strcmp(op, "info") == 0){
                                        info();
                                }
                                else if (strcmp(op, "ls") == 0){
                                        ls(op);

				}
                                else if (strcmp(op, "cd") == 0){
                                        //cd(op);
                                }
                                else if (strcmp(op, "size") == 0){
                                        //size(op);
                                }
                                else if (strcmp(op, "creat") == 0){
                                        //create(name);
                                }
                                else if (strcmp(op, "mkdir") == 0){
                                        //mkdir(name);
                                }
                                else if (strcmp(op, "open") == 0){
                                        //open(op, mode);
                                }
                                else if (strcmp(op, "close") == 0){
                                        //close(op);
                                }
                                else if (strcmp(op, "read") == 0){
                                        //read(op);
                                }
                                else if (strcmp(op, "write") == 0){
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


	printf("Number of FATs: %d\n", fat_32.BPB_NumFATs);
        printf("Sec per Cluster: %d\n", fat_32.BPB_SecPerClus);
	printf("Media: %d\n", fat_32.BPB_Media);
	printf("Reserved: %d\n", fat_32.BPB_RsvdSecCnt);
	printf("Bytes per sec: %d\n", fat_32.BPB_BytsPerSec);
	printf("Reserved Sec count: %d\n", fat_32.BPB_RsvdSecCnt);
	printf("Roots:  %d\n", fat_32.BPB_RootEntCnt);
        printf("total Sec: %d\n", fat_32.BPB_TotSec16);
        printf("Fat 16: %d\n", fat_32.BPB_FATSz16);
        printf("Sec per Track: %d\n", fat_32.BPB_SecPerTrk);
        printf("Heads: %d\n", fat_32.BPB_NumHeads);
	printf("Ext Falgs: %d\n", fat_32.BPB_ExtFlags);
        printf("FSV: %d\n", fat_32.BPB_FSVer);
        printf("FSI Info: %d\n", fat_32.BPB_FSInfo);
	printf("BkBootSec: %d\n", fat_32.BPB_BkBootSec);
        printf("Hidden Sec: %d\n", fat_32.BPB_HiddSec);
	printf("Total Sec 32: %d\n", fat_32.BPB_TotSec32);
	printf("fat 32: %d\n", fat_32.BPB_FATSz32);
	printf("Root Clus: %d\n", fat_32.BPB_RootClus);

}


int ls(char * name) {


        return 0;
}


void cd(char * op) {


}
void size(char * op) {


}
void creat(char * op) {


}
void mkdir(char * op) {


}
void open(char * op, char *mode) {


}
void close(char * op, char *mode) {


}

void read(char * op) {


}
void write(char * op) {


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
