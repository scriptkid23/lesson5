#include <string.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct{
    char maso[7];
    char tenhang[32];
    int doanhso[100];
    int tong;

} HANG;
typedef struct{
    int soluong;
    int day;
    HANG *hang[100];

} DANHSACH;
void deleteNewline(char prop[]){
    prop[strlen(prop)-1] = '\0';
}
void inputDatabase(DANHSACH *ds){
    FILE *fr_hang       = fopen("database/hang.txt","r");
    FILE *fr_doanhso    = fopen("database/doanhso.txt","r");
    char temp_hang[3];
    fscanf(fr_hang,"%d",&ds->soluong);
    fgets(temp_hang,sizeof(temp_hang),fr_hang);
    for(int i = 0 ;i < ds->soluong;i++){
        ds->hang[i] = (HANG*)malloc(sizeof(HANG));
        fscanf(fr_hang,"%s",ds->hang[i]->maso);
        fgets(ds->hang[i]->tenhang,sizeof(ds->hang[i]->tenhang),fr_hang);
        deleteNewline(ds->hang[i]->tenhang);
        deleteSpace(ds->hang[i]->tenhang);
    }
    char temp_doanhso[100];
    fscanf(fr_doanhso,"%d",&ds->day);
    for(int i = 0; i < ds->soluong;i++){
        fscanf(fr_doanhso,"%s",&temp_doanhso);
        if(strcmp(temp_doanhso,ds->hang[i]->maso) == 0){
            for(int j = 0 ; j < ds->day;j++){
                fscanf(fr_doanhso,"%d",&ds->hang[i]->doanhso[j]);
            }
        }
    }

    fclose(fr_hang);
    fclose(fr_doanhso);
}
void dataProc(HANG *prop[],int _soluong,int day){
    int tong_temp = 0;
    for (int i = 0; i < _soluong;i++){
        for(int j = 0; j < day;j++){
        tong_temp = tong_temp + prop[i]->doanhso[j];
    }
        prop[i]->tong = tong_temp;
        tong_temp = 0;
    }
}
void deleteSpace(char prop[]){
    //printf("%d",strlen(prop));
   strrev(prop);
   deleteNewline(prop);
   strrev(prop);
}
void printResult(DANHSACH *prop){
    FILE *fw_tonghop = fopen("database/tonghop.txt","w");
    fprintf(fw_tonghop,"DOANH THU TUAN\n");
    fprintf(fw_tonghop,"%-10s|%-30s|%-30s|%-8s\n","STT","MASO","TEN HANG","DOANH SO");

    for(int i = 0; i < prop->soluong ;i++){
        fprintf(fw_tonghop,"%-10d|%-30s|%-30s|%-8d\n",i+1,prop->hang[i]->maso,prop->hang[i]->tenhang,prop->hang[i]->tong);
    }
    fclose(fw_tonghop);
}
int main(){
  DANHSACH *danhsach;
  danhsach = (DANHSACH*)malloc(sizeof(DANHSACH));
  inputDatabase(danhsach);
  dataProc(danhsach->hang,danhsach->soluong,danhsach->day);
  printResult(danhsach);
  char A[] = " hello world";
  deleteSpace(A);
  printf("%s",A);
}
