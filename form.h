#include<bits/stdc++.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<map>
#include<hash_map>
#define random(x) (rand()%x)
using namespace std;
class Form{

public:
    int insert(FILE *fp,int64_t [200]);
    void select(FILE *fp,int64_t parmeter,int64_t min,int64_t max);
    void init(FILE*fp);
    void select_index(FILE *fp,int64_t parmeter,int64_t min,int64_t max);
    void add_index(int64_t parmeter);
    void select(FILE*fp,int row_number);
    void properties(FILE*fp);
    Form();
    int64_t buff[100];//随机生成数据
    int64_t  **form;//表格
    int64_t* index;//索引文件，先做一个弱鸡处理

};

Form::Form(){
/**
//惨不忍睹！
//cout<<"----表头信息----"<<endl;
//fwrite(buff_col,sizeof(buff_col), 1,fp);
//
//rewind(fp);
//fread(rd_buf, sizeof(rd_buf), 1, fp);
//     for(int j=0;j<20;j++){
//         cout<<rd_buf[j]<<' ';
//     }
//
//     fwrite("\r\n",1,2,fp);//换行
//for(int i=0;i<20;i++){
//    buff[i]=random(100);//生成100以内的随机数据！
//}
//     fread(buff, sizeof(buff), 1, fp);
//long number=sizeof(int64_t)*20;//一行偏移量为int64_t*100;
//     fseek(fp,number, SEEK_CUR);
//     fread(rd_buf, sizeof(rd_buf), 1, fp);
//
//     for(int j=0;j<20;j++){
//         cout<<rd_buf[j]<<" ";
//     }
**/
/** 测试随机生成数据
//for(int64_t i=1;i<=10;i++){
//buff[i]=random(100);
//}
//rewind(fp);
//fread(rd_buf, sizeof(rd_buf), 1, fp);
//for(int i=0;i<100;i++){
//    cout<<rd_buf[i]<<endl;
//}
//cout<<sizeof(buff)<<endl;
//
//
//fwrite(buff,sizeof(buff),1,fp);
 **/




}
//表初始化
void Form::init(FILE*fp){
    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }
    int number=0;
    //(int64_t *)(malloc(sizeof(int64_t) * 10));
    form=new int64_t*[100];//假设一共只能存储100行的数据
    for(int i=0;i<100;i++){
        form[i]=new int64_t [100];
    }
    //属性栏默认用0-99表示每一列属性
    for(int i=0;i<1;i++) {
            for(int j=0;j<100;j++){
                form[i][j]=number++;
               // cout<<form[i][j]<<' '<<endl;
            }
    }
    fwrite(&form[0][0],sizeof(int64_t),100,fp);

    //生成第一行随机数据
    for(int i=1;i<100;i++) {
        for(int j=0;j<100;j++){
            form[i][j]=random(100);
           // cout<<form[i][j]<<' '<<endl;
        }
    }
    for(int i=1;i<100;i++) {
        size_t op_w = fwrite(&form[i][0], sizeof(int64_t), 100, fp);
        if (op_w == 100) {
            cout << "The" <<i<<" init success!" << endl;
        }
    }
    //rewind(fp);
    //fread(buff,sizeof(int64_t),200,fp);
    //测试第一行随机生成数据
//    cout<<endl;
//    for(int i=0;i<200;i++){
//        cout<<buff[i]<<' ';
//    }

    fclose(fp);
}
//表插入
int Form::insert(FILE *fp,int64_t *data){
    fp = fopen( "form.txt", "a+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }
//    for(int i=0;i<100;i++){
//        cout<<data[i]<<""<<endl;
//
//    }
//cout<<endl;
int op_w=fwrite(data,sizeof(int64_t),100,fp);
    if(op_w==100){
        cout<<"write success! "<<endl;
    }
fclose(fp);
return 1;
}


//按条件搜索
void Form::select(FILE *fp,int64_t parmeter,int64_t min,int64_t max){
    FILE*fp_index=fopen("index.txt","ab+");
    if(fp_index == NULL)
    {
        perror("open file error:");

    }

    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }

//如果有索引
    fseek(fp,0,2);
    long row=ftell(fp);
    row=row/800;//得到表一共有多少行
    rewind(fp);
    fseek(fp_index,0,2);
    long file_size=ftell(fp_index);
    file_size=file_size/(row*8);//得到索引表一共有多少个索引
    int64_t num[file_size];
    rewind(fp_index);
    for(int i=0;i<file_size;i++) {
        fread(&num[i], sizeof(int64_t), 1, fp_index);
        if (parmeter == num[i]) {
            cout << "The col hash index!We can select from index!" << endl;
            fclose(fp);
            fclose(fp_index);
            select_index(fp,parmeter,min,max);
            exit(0);
        }else{
            cout<<"The col has not index!We can't use index to select..."<<endl;
            break;
        }
    }

    rewind(fp);
//计算整个文件的总子节数
    fseek(fp,0,2);
    long size=ftell(fp);
    size=size/800;//得到表一共有多少行
    form=new int64_t *[size];
    for(int i=0;i<size;i++){
        form[i]=new int64_t [100];
    }
    rewind(fp);//重置指针
//从文本从写入每一行
 for(int i=0;i<size;i++){
     fread(&form[i][0],sizeof(int64_t),100,fp);

 }
    //查询属性值为parmeter的一列中>=min,<=max的所有行（默认返回前10行
    for(int i=1;i<size;i++){
    if(form[i][parmeter]>=min&&form[i][parmeter]){
        //该行满足要求打印出来
        cout<<endl<<"----the "<<i<<" row: "<<endl;
      for(int j=0;j<100;j++){

      cout<<form[i][j]<<" ";

      }

    }

    }
fclose(fp);
}

//给属性添加索引
void Form::add_index(int64_t parmeter) {
    FILE *fp;
    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }

    fseek(fp,0,2);
    long size=ftell(fp);
    size=size/800;//得到表一共有多少行
    cout<<"The file has "<<size<<" row!"<<endl;
   index=new int64_t [size];
   rewind(fp);
   if(parmeter!=0)
   fseek(fp,parmeter*8,0);
    for(int i=0;i<size;i++){
        fread(&index[i],sizeof(int64_t),1,fp);
        fseek(fp,792,1);
    }
    fclose(fp);
    FILE *fp_index;
    fp_index = fopen( "index.txt", "ab+" );
    if(fp_index == NULL)
    {
        perror("open file error:");

    }

    int write=fwrite(index,sizeof(int64_t),size,fp_index);
    cout<<write<<endl;
    if(write==size){
        cout<<"wirte_index sucess!"<<endl;
    }
    fclose(fp_index);
}


//索引搜索
void Form::select_index(FILE *fp, int64_t parmeter, int64_t min, int64_t max) {
    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }
    FILE *fp_index;
    fp_index = fopen( "index.txt", "ab+" );
    if(fp_index == NULL)
    {
        perror("open file error:");

    }
    fseek(fp,0,2);
    long row=ftell(fp);
    row=row/800;//得到表一共有多少行
    cout<<"The file has "<<row<<" row!"<<endl;
    rewind(fp);
    fseek(fp_index,0,2);
    long size=ftell(fp_index);
    size=size/(row*8);//得到索引表一共有多少个索引
    cout<<"Form the index.txt we can see there are "<<size<<" index!"<<endl;
    int64_t num[size];
    rewind(fp_index);
    int64_t number[row];
    for(int i=0;i<size;i++){
        fread(&num[i],sizeof(int64_t),1,fp_index);
        if(parmeter==num[i]){
            cout<<"The "<<i<<" col hash index!"<<endl;
            fseek(fp_index,-8,1);
            fread(number,sizeof(int64_t),row,fp_index);
            cout<<"The "<<i<<" col has the number as follow:"<<endl;
            for(int p=0;p<100;p++){
                cout<<number[p]<<" ";
            }
            for(int i=1;i<row;i++){
                if(number[i]>=min&&number[i]<=max){
                    cout<<endl<<"The "<<i<<" row machted!"<<endl;
                    int64_t temp[100];
                    fseek(fp,i*800,0);
                    fread(temp,sizeof(int64_t),100,fp);
                    for(int j=0;j<100;j++){
                        cout<<temp[j]<<" ";
                    }
                }
            }
        }
        rewind(fp_index);
        fseek(fp_index,row*8,1);
    }
    fclose(fp);
    fclose(fp_index);
}


//按行号搜索
void Form::select(FILE *fp, int row_number) {
    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }
    fseek(fp,(row_number-1)*800,0);
    int r=fread(buff,sizeof(int64_t),100,fp);
    if(r==100){
        cout<<"read success!"<<endl;
    for(int i=0;i<100;i++){
        cout<<buff[i]<<' ';
    }

    }

fclose(fp);
}


//查看表有多大，有多少行，有多少个属性
void Form::properties(FILE *fp) {
    fp = fopen( "form.txt", "ab+" );
    if(fp == NULL)
    {
        perror("open file error:");

    }
    long number;
    fseek(fp,0,2);
    number=ftell(fp);
    cout<<"The file's size is "<<number<<" Byte!"<<endl;
    cout<<"The file has 100 properties!"<<endl;
    long row=number/800;
    cout<<"The file has "<<row<<" row!"<<endl;
    fclose(fp);
}


