#include"ExeFunction.h"
//char s[100000];
/**
 * 函数名称: PlacestrToNum
 * 函数功能: 把教学楼教室字符串转化为数组下标
 * 输入参数: 教学楼、教室
 * 返 回 值: les_place数组下标
 *
 */

int  PlacestrToNum(char s1[] , char s2[])//s1表示教学楼s2表示教室
{

  if(!strcmp(s1,"西十二"))//1~120
  {
      int n=0;
      if( (s2[0]!='N')&&(s2[0]!='S')&&(s2[0]!='n')&&(s2[0]!='s') )//判断南楼和北楼
        return -1;

      if((s2[1]>'5')||(s2[1]<'1')||(s2[2]>'1')||(s2[2]<'0') || (s2[3]<'0') || (s2[3]>'9'))
        return -1 ;

      if( (s2[0]=='S')||(s2[0]=='s'))
        n += 60;

      n += 12*(s2[1]-'0'-1);//增加南楼偏置


      if(s2[2]!='0')
      {
        if( (s2[3]!='0')&&(s2[3]!='1')&& (s2[3]!='2') )//一层只有12个教室
        return -1;
        n += (10+(s2[3]-'0'));
      }
      else if(s2[3]!='0')
        n += (s2[3]-'0');

      else
        return -1;

    return n;

  }

  else if(!strcmp(s1,"西五楼"))//131~230
  {
      if((s2[0]>'5')||(s2[0]<'1')||(s2[1]>'2')||(s2[1]<'0')||(s2[2]>'9')||(s2[2]<'0'))//如果出现非法的教室编号
          return -1;
      else
      {
          if((s2[1]=='0')&&(s2[2]=='0'))
           return -1;

          if((s2[1]=='2')&&(s2[2]!='0'))
           return -1;

          int n=0;
          n += (s2[0]-'1')*20 + (s2[1]-'0')*10 + (s2[2]-'0');
          n+=130;
          return n;
      }
  }
    else if(!strcmp(s1,"南一楼"))//121~130
    {
        if(!strcmp(s2,"116"))
          return 121;
        else if(!strcmp(s2,"802"))
          return 122;
        else if(!strcmp(s2,"803"))
          return 123;
        else if(!strcmp(s2,"804"))
          return 124;
        else if(!strcmp(s2,"805"))
         return 125;
        else if(!strcmp(s2,"806"))
         return 126;
        else if(!strcmp(s2,"807"))
          return 127;
        else if(!strcmp(s2,"808"))
         return 128;
        else if(!strcmp(s2,"809"))
         return 129;
        else if(!strcmp(s2,"810"))
            return 130;
        else
          return -1;
    }

    else if(!strcmp(s1,"科技楼"))//240
    {
       if(!strcmp(s2,"北楼"))
        return  240;
       else
         return  -1;

    }

    else if(!strcmp(s1,"西操场"))
      return 241;
    else if(!strcmp(s1,"中心操场"))
      return 242;
    else if(!strcmp(s1,"东操场"))
      return 243;



    else
     return -1;
}
/**
 * 函数名称: TimestrToNum
 * 函数功能: 把周数、星期、节数转化为les_time数组下标
 * 输入参数: 周数、星期、节数
 * 返 回 值: les_time数组下标
 *
 */

int TimestrToNum(int week , int day , int period)//计算时间hash值
{
    if( (week<1)||(week>22) ||(day<1) || (day>7)||(period<1)||(period>6) )
        return -1;//如果超出范围

    int res =7*6*(week-1) + 6*(day-1) +period;//计算时间hash值
    if( res>840 || res <1)//hash值超出范围
      return -1;
    return  res;
}

/**
 * 函数名称: LessonInsert
 * 函数功能: 在对应的时间空间插入课堂
 * 输入参数: 空间hash值，时间hash值，要插入的课堂结构体指针
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int LessonInsert(int placei,int timei,LESSON* temp)
{
  LESSON *p=NULL;
  //时间链、空间链对应的节点都为NULL
  if((les_place[placei].room_next==NULL)&&(les_time[timei].time_next==NULL))
  {
    temp->lesson_time=&(les_time[timei]);temp->lesson_place=&(les_place[placei]);
  //  les_time[timei].time_next=(LESSON*)malloc(sizeof(LESSON));
    les_time[timei].time_next=temp;
    //les_place[placei].room_next=(LESSON*)malloc(sizeof(LESSON));
    les_place[placei].room_next=temp;
    return 1;
  }

  //空间链不空，时间链为NULL，也就是同一教室别的时间有课
  else if((les_place[placei].room_next!=NULL)&&(les_time[timei].time_next==NULL))
  {
    //les_time[timei].time_next=(LESSON*)malloc(sizeof(LESSON));
    temp->lesson_time=&(les_time[timei]);
    les_time[timei].time_next=temp;
   //在该教室的对应时间位置上面插入
    p=les_place[placei].room_next;
    while(p!=NULL)
    {
      int t1=TimestrToNum(p->week , p->day , p->period);
      if(t1<timei)
      {
         if(p->time_next!=NULL)
         {
             int t2=TimestrToNum(p->time_next->week , p->time_next->day , p->time_next->period);
             if(t2<timei) {p=p->time_next;continue;}//寻找合适的插入点
             else if(t2>timei)
             {
               p->time_next->time_pri=temp; temp->time_next=p->time_next;
               p->time_next=temp; temp->time_pri=p;
               temp->lesson_place=&(les_place[placei]);
               return 1;
             }
             else
             {   //printf("11111\n" );
                 return -1;
             }

         }
         else//p点后没有课堂了，此课堂在p点之后上课，那么插在p后面
         {
           temp->lesson_place=&(les_place[placei]);
           p->time_next=temp;temp->time_pri=p;
           return 1;
         }
      }
      else if(t1>timei)//说明此课堂在p之前上课
      {
         temp->lesson_place=&(les_place[placei]);
         les_place[placei].room_next=temp;
         temp->time_next=p; p->time_pri=temp;
         return 1;
      }
      else//同一地点的同一时间，上课冲突
      {
        //printf("22222\n" );
        return -1;
      }

    }
  }

  //空间链为NULL，时间链不空，也就是同一时间有多个教室上课，插在对应的位置
  else if((les_place[placei].room_next==NULL)&&(les_time[timei].time_next!=NULL))
  {

    temp->lesson_place=&(les_place[placei]);
    les_place[placei].room_next=temp;
   //在同一时间合适的教室插入该课堂
    p=les_time[timei].time_next;
    while(p!=NULL)
    {
      int t1=PlacestrToNum(p->building,p->classroom);
      if(t1<placei)//该课堂空间hash值较大
      {
         if(p->room_next!=NULL)
         {
             int t2 = PlacestrToNum(p->room_next->building, p->room_next->classroom);
             if(t2<placei) {p=p->room_next;continue;}//寻找合适的插入点
             else if(t2>placei)
             {
               p->room_next->room_pri=temp; temp->room_next=p->room_next;
               p->room_next=temp; temp->room_pri=p;
               temp->lesson_time=&(les_time[timei]);
               return 1;
             }
             else
             {
               //printf("33333\n" );
               return -1;
             }

         }
         else//否者插到p的后面
         {
           temp->lesson_time=&(les_time[timei]);
           p->room_next=temp;temp->room_pri=p;
           return 1;
         }
      }
      else if(t1>placei)//插到p的前面
      {
         temp->lesson_time=&(les_time[timei]);
         les_time[timei].time_next=temp;
         temp->room_next=p; p->room_pri=temp;
         return 1;
      }
      else//上课冲突
      {
       // printf("4444\n");
        return -1;
      }


    }
  }

  else
  {
   //时间链空间链都不空，其实前两个if不用写，只写下面的理论上也可以

   //寻找合适的时间
    p=les_place[placei].room_next;
    while(p!=NULL)
    {
      int t1=TimestrToNum(p->week , p->day , p->period);
      if(t1<timei)
      {
         if(p->time_next!=NULL)
         {
             int t2=TimestrToNum(p->time_next->week , p->time_next->day , p->time_next->period);
             if(t2<timei) {p=p->time_next;continue;}
             else if(t2>timei)
             {
               p->time_next->time_pri=temp; temp->time_next=p->time_next;
               p->time_next=temp; temp->time_pri=p;
               temp->lesson_place=&(les_place[placei]);
               break;
             }
             else
             {
              // printf("4.5\n");
               //printf("timei: %d  placei :%d\n",timei,placei);
               //printf("t2: %d\n",t2);
               return -1;
             }

         }
         else
         {
           temp->lesson_place=&(les_place[placei]);
           p->time_next=temp;temp->time_pri=p;
           break;
         }
      }
      else if(t1>timei)
      {
         temp->lesson_place=&(les_place[placei]);
         les_place[placei].room_next=temp;
         temp->time_next=p; p->time_pri=temp;
         break;
      }
      else
      {
       // printf("5555\n");
       // printf("timei:%d  placei : %d\n",timei,placei);
        return -1;
      }

    }

    //寻找合适的空间
    p=les_time[timei].time_next;
    while(p!=NULL)
    {
      int t1=PlacestrToNum(p->building,p->classroom);
      if(t1<placei)
      {
         if(p->room_next!=NULL)
         {
             int t2 = PlacestrToNum(p->room_next->building, p->room_next->classroom);
             if(t2<placei) {p=p->room_next;continue;}
             else if(t2>placei)
             {
               p->room_next->room_pri=temp; temp->room_next=p->room_next;
               p->room_next=temp; temp->room_pri=p;
               temp->lesson_time=&(les_time[timei]);
               return 1;
             }
             else
             {
               //printf("6666\n");
               return -1;
             }
         }
         else
         {
           temp->lesson_time=&(les_time[timei]);
           p->room_next=temp;temp->room_pri=p;
           return 1;
         }
      }
      else if(t1>placei)
      {
         temp->lesson_time=&(les_time[timei]);
         les_time[timei].time_next=temp;
         temp->room_next=p; p->room_pri=temp;
         return 1;
      }
      else
      {
       // printf("77777\n");
        return -1;
      }

    }

  }

  return 0;
}
/**
 * 函数名称: ClassnoInsert
 * 函数功能: 在专业班级的维度上建立查找链
 * 输入参数: 要插入的课堂结构体指针
 * 返 回 值: 返回1
 *
 */
int  ClassnoInsert(LESSON* temp)
{
  int done=0;
  for(int i=0 ; i<les_classno.size() ; i++)//寻找符合条件的表头
  {
     if(!strcmp(les_classno[i].classno , temp->classno))//如果班级名称相等，那么在后面插入
     {
        done=1;
        if(les_classno[i].lesson==NULL)//如果之后没有结点，那么直接插入
        {
          les_classno[i].lesson=temp;
          return 1;
        }
        else//否者寻找合适的插入位置
        {
          LESSON *p=les_classno[i].lesson;
          LESSON* pp=p;
          while(p!=NULL)
          {
            pp=p;
            p=p->classno_next;
          }
          pp->classno_next=temp;
          temp->classno_pri=pp;
          return 1;//插入完成返回1
        }
     }
  }

  if(!done)//如果没有在上面执行插入操作，在班级中增加一个班级，然后再插入
  {
    CLASSNO t; t.lesson=NULL;
    strcpy(t.classno,temp->classno);
    t.lesson=temp;
    les_classno.push_back(t);
  }

 return 1;
}
/**
 * 函数名称: CourseInsert
 * 函数功能: 在课程的维度上建立查找链
 * 输入参数: 要插入的课堂结构体指针
 * 返 回 值: 返回1
 *
 */
int CourseInsert(LESSON* temp)
{
  int done=0;
  for(int i=0 ; i<les_course.size() ; i++)//遍历课程查找链，寻找同名课程
  {
     //printf("i1:  %d    \n",i);
     //printf("2 temp->course: %s\n",temp->course);
     if(!strcmp(les_course[i].course , temp->course))//如果课程查找链中有同名课程
     {
        //printf("i2:   %d    \n",i);
        //printf("2 temp->course: %s\n",temp->course);
        done=1;
        if(les_course[i].lesson==NULL)//如果该课程名后面没有课堂
        {
          les_course[i].lesson=temp;
         // printf("i3:   %d    \n",i);
          return 1;
        }
        else//如果后面有课堂
        {
         // printf("i4:   %d    \n",i);
          LESSON *p=les_course[i].lesson;
          LESSON* pp=p;
          while(p!=NULL)//寻找合适的插入位置
          {
            pp=p;
            p=p->course_next;
          }
          pp->course_next=temp;
          temp->course_pri=pp;
          return 1;

        }
     }
  }

  if(!done)//如果前面没有找到同名的课程，那么在课程查找链中新添加一个课程，然后再插入
  {
    COURSE t; t.lesson=NULL;
    strcpy(t.course,temp->course);
    t.lesson=temp;
    les_course.push_back(t);
  }

 return 1;
}
/**
 * 函数名称: ReadLesson
 * 函数功能: 从数据文件中读取课堂信息
 * 输入参数: 数据文件的文件指针
 * 返 回 值: 成功返回1，遇到上课冲突则出错返回-1
 *
 */
int ReadLesson(FILE *fp)
{
    int res=1,sum=1;
    int from,to;
    LESSON *temp;
    temp=(LESSON*)malloc(sizeof(LESSON));
    //int i=0;
   // char s[10];
    if(fp==NULL)
        return -1;
    while( fscanf(fp,"%d%d",&from ,&to)!=EOF)//读入周次
    {
      // printf("T: %d\n", T);

     // printf("i : %d\n",++i);
       /*char building[15];
       char classroom[6];
       char teacher[20];
       char classno[80];
       char course[45];*/


       //对应的赋值
       temp->from=from; temp->to=to;
       fscanf(fp,"%d%d",&(temp->day),&(temp->period));
       fscanf(fp,"%s",temp->building);
       fscanf(fp,"%s",temp->classroom);
      // fscanf(fp,"%s",temp->teacher);
       fscanf(fp,"%s",temp->classno);
       fscanf(fp,"%s",temp->course);
       temp->time_next=temp->room_next=temp->time_pri=temp->room_pri=NULL;
       /*temp->teacher_next=temp->teacher_pri=NULL*/
       temp->classno_next=temp->classno_pri=temp->course_next=temp->course_pri=NULL;
       temp->lesson_time=NULL;
       temp->lesson_place=NULL;
      // printf("EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
       int i;
       for( i=from;i<=to;i++)//从开始周次，到结束周次插入课堂
       {

         LESSON* atemp=(LESSON*)malloc(sizeof(LESSON));
         *atemp=*temp;
         atemp->week=i;
         int timei=TimestrToNum(atemp->week,atemp->day,atemp->period);//取得对应时间hash值
         int placei=PlacestrToNum(atemp->building,atemp->classroom);//取得空间hash值
         if(timei==-1 || placei==-1)//如果没有找到对应的hash值，返回-1
            return -1;


         res = LessonInsert( placei, timei,atemp);//插入对应的课堂

         if(res==-1)
         {
           // printf("asdfasdfasdfasdf\n");
                return -1;
         }

         else
          {
           // printf("222222\n");
            atemp->No=sum++;
            lesson_sum=atemp->No;
            //TeacherInsert(atemp);
            if(i==from)
            {
               // printf("timei :%d placei: %d \n",timei,placei);
              ClassnoInsert(atemp);
              //printf("33333333\n");
              CourseInsert(atemp);
              //printf("4444444444\n");
            }

          }
       }

      // printf("2 T: %d\n", T);
    }
    free(temp);
    return res;
}
/**
 * 函数名称: Init
 * 函数功能: 初始化表头
 * 输入参数: 无
 * 返 回 值: 1
 *
 */

int Init(void)
{
    //时间表头赋值
    for(int i=1;i<=20;i++)
    {
        for(int j=1;j<=7;j++)
        {
            for(int k=1;k<=6;k++)
            {
               //les_time[7*6*(i-1)+6*(j-1)+k].lesson_num=0;
               les_time[7*6*(i-1)+6*(j-1)+k].week=i;
               les_time[7*6*(i-1)+6*(j-1)+k].day=j;
               les_time[7*6*(i-1)+6*(j-1)+k].period=k;
               les_time[7*6*(i-1)+6*(j-1)+k].time_next=NULL;
            }

        }
    }
    //西十二楼的表头赋值
    for(int i=1;i<=5;i++)
        for(int j=1;j<=12;j++)
        {
           int n=100*i+j;
           char sroom[10];
           sprintf(sroom,"%d",n);

           for(int k=3;k>=0;k--)
           {
               sroom[k+1]=sroom[k];
           }
           sroom[0]='N';//北楼对应的教室编号
           sroom[4]='\0';


           strcpy(les_place[12*(i-1)+j].building, "西十二");
           strcpy(les_place[12*(i-1)+j].classroom,sroom);
           les_place[12*(i-1)+j].room_next=NULL;
           sroom[0]='S';//南楼对应编号
           strcpy(les_place[12*(i-1)+j+60].classroom,sroom);
           strcpy(les_place[12*(i-1)+j+60].building,"西十二");
           les_place[12*(i-1)+j+60].room_next=NULL;

        }
    for(int i=1;i<=10;i++)//南一楼的表头赋值
    {
      int n=800; char sroom[10];
      n+=i;
      sprintf(sroom,"%d",n);
      strcpy(les_place[120+i].building, "南一楼");
      strcpy(les_place[120+i].classroom,sroom);
      les_place[120+i].room_next=NULL;
    }
    strcpy(les_place[121].classroom,"116");//没有801，所以替换成806

  //西五楼的表头初始化赋值
    for(int i=1;i<=5;i++)
        for(int j=1;j<=20;j++)
        {
           int n=100*i+j;
           char sroom[10];
           sprintf(sroom,"%d",n);
           int placei=PlacestrToNum("西五楼",sroom);

           strcpy(les_place[placei].building, "西五楼");
           strcpy(les_place[placei].classroom,sroom);
           les_place[placei].room_next=NULL;

        }

  //其他上课表头赋值
  strcpy(les_place[240].building, "科技楼");
  strcpy(les_place[240].classroom,"北楼");
  les_place[240].room_next=NULL;

  strcpy(les_place[241].building, "西操场");
  strcpy(les_place[241].classroom,"##");
  les_place[241].room_next=NULL;

  strcpy(les_place[242].building, "中心操场");
  strcpy(les_place[242].classroom,"##");
  les_place[242].room_next=NULL;

  strcpy(les_place[243].building, "东操场");
  strcpy(les_place[243].classroom,"##");
  les_place[243].room_next=NULL;

    return 1;
}

/**
 * 函数名称: SearchByTimeAndPlace
 * 函数功能: 根据时间和空间查找课堂
 * 输入参数: 时间空间的hash值
 * 返 回 值: 找到返回1，没找返回-1
 *
 */

int SearchByTimeAndPlace(int timei,int placei)
{
  LESSON* p=les_place[placei].room_next;
  //printf("classroom : %s\n",les_place[placei].classroom);
  while(p!=NULL)//在要查找的空间下寻找对应的时间的结点
  {
      if((p->lesson_time) == &(les_time[timei]))//如果查找到了，那么直接退出循环
         break;

      p=p->time_next;//没找到找下一个结点
  }
  if(p==NULL)//如果彻底没找到
    return -1;
  else//找到,输出对应结点的信息
  {
    printf("-------------------------------------------------------------------\n");
    printf("  课程：%s\n",p->course);
    printf("  周次：%d~%d周\n",p->from,p->to);
    printf("  星期：%d\n",p->day);
    printf("  节数：%d\n",p->period);
    printf("  教学楼：%s\n",p->building);
    printf("  教室：%s\n",p->classroom);
    printf("  班级：%s\n",p->classno);
    printf("-------------------------------------------------------------------\n");
    return 1;
  }

}
/**
 * 函数名称: SearchByCourse
 * 函数功能: 在课程查找链上查找课堂
 * 输入参数: 课程名称
 * 返 回 值: 找到返回1，没找返回-1
 *
 */

int SearchByCourse(char s[])//根据课程信息查找课堂
{
  int no=0;
  for(int i=0 ; i<(int)les_course.size() ; i++)//遍历课程查找链
  {
     if(strstr(les_course[i].course ,s))//如果用户输入的课堂名是查找链中某个表头的子串
     {
        if(les_course[i].lesson==NULL)
          continue;

        else
        {
          LESSON *p=les_course[i].lesson;
          while(p!=NULL)//输出对应结点的信息
          {
            if(readed[p->No])
              continue;
              printf("-------------------------------------------------------------------\n");
              printf("No.%d\n",++no);
              printf("  课程：%s\n",p->course);
              printf("  周次：%d~%d周\n",p->from,p->to);
              printf("  星期：%d\n",p->day);
              printf("  节数：%d\n",p->period);
              printf("  教学楼：%s\n",p->building);
              printf("  教室：%s\n",p->classroom);
              printf("  班级：%s\n",p->classno);
              printf("-------------------------------------------------------------------\n");

            readed[p->No]=true;
            p=p->course_next;

          }
        }
      }
    }
   if(no==0)
    return -1;
   else
   return 1;

}

/**
 * 函数名称: SearchByClassno
 * 函数功能: 在专业班号查找链上查找课堂信息
 * 输入参数: 专业班号
 * 返 回 值: 找到返回1，没找返回-1
 *
 */

int SearchByClassno(char  s[])
{
  int no=0;
  for(int i=0 ; i<les_classno.size() ; i++)//遍历班级查找链
  {
     if(strstr(les_classno[i].classno ,s))//如果用户输入的班级是查找链中某个表头的子串
     {
        if(les_classno[i].lesson==NULL)
          continue;

        else//如果找到了对应的班级
        {
          LESSON *p=les_classno[i].lesson;
          while(p!=NULL)//查找对应的结点，然后输出
          {
            if(readed[p->No])
              continue;
            printf("-------------------------------------------------------------------\n");
            printf("No.%d\n",++no);
            printf("  班级：%s\n",p->classno);
            printf("  周次：%d~%d周\n",p->from,p->to);
            printf("  星期：%d\n",p->day);
            printf("  节数：%d\n",p->period);
            printf("  教学楼：%s\n",p->building);
            printf("  教室：%s\n",p->classroom);
            printf("  课程：%s\n",p->course);
            printf("-------------------------------------------------------------------\n");

            readed[p->No]=true;
            p=p->classno_next;

          }
        }
     }

   }
   if(no==0)
    return -1;
   else
   return 1;

}
/**
 * 函数名称: ReadGeneralInfo
 * 函数功能: 从数据文件中读取综合数据信息
 * 输入参数: 综合数据信息文件
 * 返 回 值: 成功返回1，没有读到任何信息返回-1
 *
 */



int ReadGeneralInfo(FILE * fp)
{
  // int i=0;
   INFO temp;int done=0;
   while(fscanf(fp,"%s",temp.course)!=EOF)//循环读入信息
   {
    // printf("i: %d\n",++i);
     done=1;
     fscanf(fp,"%s",temp.time);
     fscanf(fp,"%s",temp.credit);
     fscanf(fp,"%s",temp.title);
     fscanf(fp,"%s",temp.teacher);
     fscanf(fp,"%s",temp.classno);
     fscanf(fp,"%s",temp.extra);
     gen_info.push_back(temp);
   }
   if(!done)//如果一个都没有读到
     return -1;
    else
      return 1;

}

/**
 * 函数名称: ToSaveData
 * 函数功能: 将课堂信息和综合信息保存在对应的文件中
 * 输入参数: 两个文件对应的文件指针
 * 返 回 值: 返回1
 *
 */

int ToSaveData(FILE* fp1,FILE* fp2)
{
 /* for(int i=1;i<=260;i++)
  {
    LESSON *p = les_place[i].room_next;
   // printf("p%d: %p\n",i,p);
    while(p!=NULL)
    {
      fprintf(fp1,"%d   %d\n",p->week,p->week);
      fprintf(fp1,"%d\n",p->day);
      fprintf(fp1,"%d\n",p->period);
      fprintf(fp1,"%s\n",p->building);
      fprintf(fp1,"%s\n",p->classroom);
      fprintf(fp1,"%s\n",p->classno);
      fprintf(fp1,"%s\n",p->course);
    //  fprintf(fp1,"%d\n",p->No);
      fprintf(fp1,"\n\n\n");
      p=p->time_next;
    }
  }*/


  for(int i=0;i<les_course.size();i++)//按照课程查找链中的信息
  {
      LESSON *p = les_course[i].lesson;
      while(p)//把所有课程查找链中的所有的信息输出
      {
        fprintf(fp1,"%d   %d\n",p->from,p->to);
        fprintf(fp1,"%d\n",p->day);
        fprintf(fp1,"%d\n",p->period);
        fprintf(fp1,"%s\n",p->building);
        fprintf(fp1,"%s\n",p->classroom);
        fprintf(fp1,"%s\n",p->classno);
        fprintf(fp1,"%s\n",p->course);
    //  fprintf(fp1,"%d\n",p->No);
        fprintf(fp1,"\n\n\n");
        p=p->course_next;
      }
  }


  for(int i=0;i<gen_info.size();i++)//把综合课程信息中的所有的信息输出
  {
    fprintf(fp2,"%s\n",gen_info[i].course);
    fprintf(fp2,"%s\n",gen_info[i].time);
    fprintf(fp2,"%s\n",gen_info[i].credit);
    fprintf(fp2,"%s\n",gen_info[i].title);
    fprintf(fp2,"%s\n",gen_info[i].teacher);
    fprintf(fp2,"%s\n",gen_info[i].classno);
    fprintf(fp2,"%s\n",gen_info[i].extra);
    fprintf(fp2,"\n\n\n");
  }
   fclose(fp1);
   fclose(fp2);
  return 1;
}

/**
 * 函数名称: SpaceToUnderline
 * 函数功能: 把字符串中的空格变成下划线
 * 输入参数: 要转化的字符串首地址
 * 返 回 值: 无
 *
 */
void SpaceToUnderline(char*s) //C语言中create函数能创建的文件的文件名只能是标识符，因此把系统时间字符串中的冒号的空格变成下划线
{
    int i=0;
    for(i=0;(s)[i]!='\0';i++)
    {
        if( (s[i]==' ' ) ||  (s[i]==':' )   )
            s[i]='_';
        else
        {
            continue;
        }
    }

    return;
}
/**
 * 函数名称: AddBackslash
 * 函数功能: 把字符串中的单斜线变成双斜线
 * 输入参数: 要转化的字符串首地址
 * 返 回 值: 无
 *
 */
 void AddBackslash(char*s) //在一个不可能连续出现2个或两个以上 \ 字符的字符串中，把出现的 \ 字符变成  "\\"
 {
     int i=0,j,len;
     for(i=0;s[i]!='\0';i++)
     {
         if(s[i]=='\\') // 如果s[i]是\ 。
         {
             len=strlen(s);
             for(j=len;j>i;j--)//for循环是把s[i]后面的所有字符向后平移一下，为了在s[i]后面加\腾出空间
             {
               s[j+1]=s[j];
             }
             s[i+1]='\\';
             i++;  //注意这时候s[i]之后的那个字符也是\了，因此i要自增1来跳过后加的\ 在其后再搜索\。

         }
         else
            continue;
     }
return;

}
/**
 * 函数名称: GetBackupFilename
 * 函数功能: 得到包含路径的备份文件名
 * 输入参数: 储存备份文件名的字符串首地址
 * 返 回 值: 无
 *
 */

void GetBackupFilename(char *dir1, char* dir2 )//得到包含路径的备份文件名

{
    int len;//字符串长度

    time_t t;//定义一个时间变量
    t=time(NULL);

    char *time;//定义一个字符串用来保存获取到的日期和时间
    time=ctime(&t);//赋值

    SpaceToUnderline(time);//C语言中create函数能创建的文件的文件名只能是标识符，因此把系统时间字符串中的冒号的空格变成下划线

/*把时间字符串后面加上后缀名构成文件名，注意不能用strcat函数，因为时间字符串time在'\0'字符之前还有个看不见的换行符，直接接上会把".dat"接到换行符后面*/
      len=strlen(time);
      time[len-1]='.';
      time[len]='t';
      time[len+1]='x';
      time[len+2]='t';
      time[len+3]='\0';    //这是文件名构造完成了，这时time里面的字符串是带后缀名的文件名了，不仅仅是时间字符串




      char BackupDir1[25]="backup\\lesson_";
      char BackupDir2[25]="backup\\gen_info_";
      //getcwd(dir1,100);//获取当前工作地址,重点是！！！看下一行：
/*char *getcwd(char *buf, size_t size);  这是获取当前地址函数的原型，正常第二个参数应该是sizeof(dir),但是注意数组名是个指针常量并不完全同于指针变量，比如char s[10],*p=s **pp=&p; ,sizeof(s)等于10
而sizeof(p)和sizeof(pp)却等于4，因为一个指针变量占四个字节是固定的，因此char指针作为函数参数时候传递不了字符串所占的字节数。因此第二个参数只能是100（因为在BackupData函数中
声明的用于储存含地址的备份文件名的字符数组 为char filename[100] sizeof(filename)等于100*）而getcwd(dir,sizeof(dir))是错误的*/
      //getcwd(dir2,100);

      strcpy(dir1,BackupDir1);//在当前工作地址之后加上\backup\构造备份文件夹所在目录
      strcpy(dir2,BackupDir2);
      strcat(dir1,time);//在目录后面加上文件名
      strcat(dir2,time);
      AddBackslash(dir1);//把整个路径字符串里面所有的单个 \ 变成\\  以便当做文件名字符串在create等函数中做实参时 \\ 转意成 “\”
      AddBackslash(dir2);

    //  printf("%s\n",dir1 );
     // printf("%s\n",dir2 );

     return ;
}

/**
 * 函数名称: ToBackup
 * 函数功能: 备份数据
 * 输入参数: 备份文件的名称
 * 返 回 值: 1
 *
 */

int ToBackup(char* filename1,char* filename2)//向两个文件中存入备份信息
{
   FILE* fp1=fopen(filename1,"w+");
   FILE* fp2=fopen(filename2,"w+");
   if(fp1==NULL || fp2==NULL)
     return -1;

  // printf("fp1:%p  fp2:%p\n",fp1,fp2 );
   ToSaveData(fp1,fp2);//向对应文件指针所指的文件中存入对应的备份信息
   return 1;

}

/**
 * 函数名称: ClearScreenTotalInputArea
 * 函数功能: 清屏
 * 输入参数: 无
 * 返 回 值: 无
 *
 */
void ClearScreenTotalInputArea(void)
{

    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0,1};
    unsigned long size , ul;


    GetConsoleScreenBufferInfo(gh_std_out,&bInfo);  //取屏幕缓冲区信息
    size = bInfo.dwSize.X * (bInfo.dwSize.Y-1);   //计算屏幕缓冲区除了第一行字符单元数

    /*将屏幕缓冲区除了第一行所有单元的字符属性设置为当前屏幕缓冲区字符属性*/

    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);


    /*将屏幕缓冲区除了第一行所有单元填充为空格符*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    SetConsoleCursorPosition(gh_std_out,home);


    return;

}

/**
 * 函数名称: DestroyLesson
 * 函数功能: 销毁内存中的课堂数据
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int DestroyLesson(void)
{
    //清除空间同时制空空间表头指针
    for(int i=0;i<260;i++)
    {
        LESSON* p=les_place[i].room_next;
        LESSON* pp=p;
        while(p!=NULL)
        {
            pp=p->time_next;
            free(p);
            p=pp;
        }
        les_place[i].room_next=NULL;
    }
    //置空时间表头指针
    for(int i=0;i<845;i++)
    {
        les_time[i].time_next=NULL;
    }

    lesson_sum=0;

   // printf("1111111111111\n");
    return 1;
}

/**
 * 函数名称: DestroyOtherVectorInfo
 * 函数功能: 销毁综合信息数据以及查找链中的数据
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int DestroyOtherVectorInfo(void)
{
   gen_info.clear();
   les_classno.clear();
   les_course.clear();

   //printf("2222222222\n");
   return 1;
}


/**
 * 函数名称: DeleteLesson
 * 函数功能: 删除对应时间空间的课程
 * 输入参数: 要删除课堂的时间和空间的hash值
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int DeleteLesson(int timei, int placei)
{
    LESSON* p=les_place[placei].room_next;
    while(p!=NULL)//在placei链下寻找时间正确的结点
    {
        if((p->lesson_time) == &(les_time[timei]))
           break;

        p=p->time_next;
    }
    if(p==NULL)//如果没找到
    {
       // printf("111111\n");
        return -1;
    }

    //否者找到

    /*空间轴上的删除*/
    if(p->time_pri==NULL)
    {
       les_place[placei].room_next=p->time_next;
       if(p->time_next!=NULL)
       p->time_next->time_pri=NULL;
     //  printf("111\n");
    }
    else
    {
       p->time_pri->time_next=p->time_next;
       if(p->time_next != NULL)
          p->time_next->time_pri=p->time_pri;

      // printf("222\n");
    }

    /*时间轴上的删除*/
    if(p->room_pri==NULL)
    {
       les_time[timei].time_next=p->room_next;
       if(p->room_next!=NULL)
       p->room_next->room_pri=NULL;

      // printf("333\n");
    }
    else
    {
       p->room_pri->room_next=p->room_next;
       if(p->room_next != NULL)
          p->room_next->room_pri=p->room_pri;

      // printf("444\n");
    }

    /*班级轴上的删除*/
    int classnoi=-1;
    for(int i=0;i<les_classno.size();i++)//查找les_classno中对应的下标
    {
        if(!strcmp(p->classno,les_classno[i].classno))
        {
            classnoi=i; break;
        }

      // printf("les_classno i: %d\n",i);

    }
    if(classnoi==-1)//没找到说明赋值的时候出了问题
    {
            //printf("2222222\n");
        return -1;
    }

    if(p->classno_pri==NULL)
    {
       les_classno[classnoi].lesson=p->classno_next;
       if(p->classno_next!=NULL)
       p->classno_next->classno_pri=NULL;
    }
    else
    {
       p->classno_pri->classno_next=p->classno_next;
       if(p->classno_next != NULL)
          p->classno_next->classno_pri=p->classno_pri;
    }


    /*课程轴上的删除*/
    int coursei=-1;
    for(int i=0;i<les_course.size();i++)//查找les_classno中对应的下标
    {
        if(!strcmp(p->course,les_course[i].course))
        {
            coursei=i; break;
        }
       //  printf("les_course i: %d\n",i);

    }
    if(coursei==-1)//没找到说明赋值的时候出了问题
    {
        //printf("3333333\n");
        return -1;
    }

    if(p->course_pri==NULL)
    {
       les_course[coursei].lesson=p->course_next;
       if(p->course_next!=NULL)
       p->course_next->course_pri=NULL;
    }
    else
    {
       p->course_pri->course_next=p->course_next;
       if(p->course_next != NULL)
          p->course_next->course_pri=p->course_pri;
    }

    free(p);

    return 1;
}

/**
 * 函数名称: ToInsertLesson
 * 函数功能: 插入对应时间空间的课程
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToInsertLesson(void)
{
  LESSON* temp=(LESSON*)malloc(sizeof(LESSON));
  int timei,placei;

  /*临时结点的初始化*/
  temp->time_next=temp->room_next=temp->time_pri=temp->room_pri=NULL;
 /*temp->teacher_next=temp->teacher_pri=NULL*/
  temp->classno_next=temp->classno_pri=temp->course_next=temp->course_pri=NULL;
  temp->lesson_time=NULL;
  temp->lesson_place=NULL;


Flag1://输出提示信息
  printf("说明：\n");
  printf("  1，一个学期1~20周，一周7天(输入1~7),每天6大节课\n");
  printf("  2，教学楼包括西十二、西五楼、南一楼、科技楼、西操场\n");
  printf("  3，东操场、中心操场。其中科技楼的教室只有“北楼”、操场的教室为“##”\n\n");
  printf("请输入要插入的课堂所在的时间、地点(用空格分开)：\n");
  printf("------------------------------------------------------\n");
  printf("周次    星期    节数(1~6)    教学楼    教室\n");

  scanf("%d%d%d",&(temp->week),&(temp->day),&(temp->period) );
  scanf("%s%s",temp->building,temp->classroom );
  getchar();

  temp->from=temp->to=temp->week;
  timei=TimestrToNum(temp->week,temp->day,temp->period);//取得时间hash值
  placei=PlacestrToNum(temp->building,temp->classroom);//取得空间hash值
  if(timei==-1 || placei==-1)//格式输入错误
  {
    int result = MessageBox(NULL,"您输入的信息格式或者范围错误！","ERROR",MB_ICONINFORMATION|MB_RETRYCANCEL);
    if(result==IDRETRY)
    {
      ClearScreenTotalInputArea();
      goto Flag1;
    }
    else
    {
        ClearScreenTotalInputArea();
        return -1;
    }
  }

  else//格式正确
  {
    ClearScreenTotalInputArea();
    printf("请输入下面的课堂信息: \n");
    printf("---------------------------------------------------------\n");
    printf("专业班号                     课程名称        \n");
    scanf("%s%s",temp->classno,temp->course);
    getchar();
    if(LessonInsert(placei,timei,temp)==-1)//插入失败，发生上课冲突
    {
      MessageBox(NULL,"课堂插入失败，可能发生了上课冲突！","ERROR!",MB_ICONINFORMATION|MB_OK);
      ClearScreenTotalInputArea();
      return -1;
    }
    else//在课程和班级查找链上查找对应的结点
    {
       ClassnoInsert(temp);
            //printf("33333333\n");
       CourseInsert(temp);
            //printf("4444444444\n");
       temp->No = ++lesson_sum;
      MessageBox(NULL,"课堂插入完成！","SUCCESS!",MB_OK);
      ClearScreenTotalInputArea();
      return 1;
    }

  }

}

/**
 * 函数名称: ToDeleteLesson
 * 函数功能: 删除对应时间空间的课程
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */

int ToDeleteLesson(void)
{
  int timei,placei;
  int week,day,period;
  char s1[100],s2[100];
Flag1:
  printf("说明：\n");
  printf("  1，一个学期1~20周，一周7天(输入1~7),每天6大节课\n");
  printf("  2，教学楼包括西十二、西五楼、南一楼、科技楼、西操场\n");
  printf("  3，东操场、中心操场。其中科技楼的教室只有“北楼”、操场的教室为“##”\n\n");
  printf("请输入要插入的课堂所在的时间、地点(用空格分开)：\n");
  printf("------------------------------------------------------\n");
  printf("周次    星期    节数(1~6)    教学楼    教室\n");

  scanf("%d%d%d",&week,&day,&period);
  scanf("%s%s",s1,s2);
  getchar();

  timei=TimestrToNum(week,day,period);//获得时间hash值
  placei=PlacestrToNum(s1,s2);//获得空间hash值

  if(timei==-1 || placei==-1)//格式输入错误
  {
    int result = MessageBox(NULL,"您输入的信息格式或者范围错误！","ERROR",MB_ICONINFORMATION|MB_RETRYCANCEL);
    if(result==IDRETRY)
    {
      ClearScreenTotalInputArea();
      goto Flag1;
    }
    else
    {
        ClearScreenTotalInputArea();
        return -1;
    }
  }
  else//格式正确
  {
    int res =  DeleteLesson(timei,placei);//删除
    if(res==1)//删除执行成功
    {
      MessageBox(NULL,"课堂删除完成！","SUCCESS!",MB_OK);
      ClearScreenTotalInputArea();
      return 1;
    }
    else//删除失败
    {
      MessageBox(NULL,"课堂删除失败，可能此课堂不存在！","ERROR!",MB_ICONINFORMATION|MB_OK);
      ClearScreenTotalInputArea();
      return -1;
    }
  }
}
/**
 * 函数名称: ReloadData
 * 函数功能: 重载内存中的数据
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */

int ReloadData(void)
{
  FILE* fp1=fopen("data\\lesson_to_read.txt","r+");
//  printf("1111\n");
  FILE* fp2=fopen("data\\gen_info.txt","r+");
  DestroyLesson();//销毁内存中的课堂数据
  DestroyOtherVectorInfo();//销毁内存中的综合课程信息
//  printf("22222\n");
//  printf("fp: %p \n",fp);
  int res1=ReadLesson(fp1);//再次从文件读入课堂信息
  //printf("res : %d  \n",res);
  int res2=ReadGeneralInfo(fp2);//再次从文件读入综合课程信息
  fclose(fp1);
  fclose(fp2);

  if((res1==-1)||(res2==-1))//失败
  {
     return -1;
  }
  else//成功
  {
    return 1;
  }

}
/**
 * 函数名称: ToModifyLesson
 * 函数功能: 修改课堂信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToModifyLesson(void)
{

   LessonFileForm();//打印数据配置文件的格式信息
   system(".\\data\\lesson_to_read.txt");//打开对应的数据配置文件
   //system(".\\data\\lesson_to_save.txt");

   int res=ReloadData();//用户修改完之后重载数据

   if(res==-1)//数据文件中的课堂排课冲突
   {
     MessageBox(NULL,"课堂修改错误！可能发生了上课冲突！","ERROR!",MB_ICONINFORMATION|MB_OK);
     return -1;
   }
   else//修改成功
   {
     MessageBox(NULL,"课堂修改成功！","SUCCESS!",MB_OK);
     return 1;
   }
}

/**
 * 函数名称: ToInsertCourse
 * 函数功能: 插入课程
 * 输入参数: 无
 * 返 回 值: 成功返回1
 *
 */
int ToInsertCourse(void)
{
  INFO temp;
  printf("请按要求输入以下信息，其中缺省的数据项用“##”表示：\n");
  printf("-----------------------------------------------------------------------\n");
  printf("课程        学时    学分    任课教师    教师职称    上课班级    备注\n");
  scanf("%s%s%s%s%s%s%s",temp.course,temp.time,temp.credit,temp.teacher,temp.title,temp.classno,temp.extra );
  getchar();
  gen_info.push_back(temp);//插入信息
  MessageBox(NULL,"课程插入成功！","SUCCESS!",MB_OK);
  return 1;
}

/**
 * 函数名称: ToFindGenInfoByCourse
 * 函数功能: 通过课程名查询综合信息
 * 输入参数: 课程名
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToFindGenInfoByCourse(char s[])
{
   for(int  i=0;i<gen_info.size();i++)//根据课程名查找想要查找的数据结点的下标，存在find中
   {
     if(strstr(gen_info[i].course,s))
     {
       find.push_back(i);
     }
   }
   if(find.size()==0)
     return -1;
   for(int i=0;i<find.size();i++)//把找到的都打印出来
   {
     INFO t=gen_info[find[i]];
     printf("-------------------------------------------------------------------------\n");
     printf("No.%d\n",i+1);
     printf("  课程：%s\n",t.course);
     printf("  学时：%s\n",t.time);
     printf("  学分：%s\n",t.credit);
     printf("  任课教师：%s\n",t.teacher);
     printf("  教师职称：%s\n",t.title);
     printf("  上课班级：%s\n",t.classno);
     printf("  备注：%s\n",t.extra);
     printf("-------------------------------------------------------------------------\n");
   }
   return 1;
}

/**
 * 函数名称: ToDeleteCourse
 * 函数功能: 通过课程名删除综合信息
 * 输入参数: 课程名
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToDeleteCourse(void)
{
  char s[100];
  printf("\n\n请输入要删除的课程名:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByCourse(s);
  if(res!=-1)//有这门课
  {
    Flag1:
    printf("\n请输入要删除的课程编号(仅一个):");
    int no; scanf("%d",&no);getchar();//读入要删除的课堂的编号
    if(no<1 || no>(find.size()))//编号输入的格式错误
    {
      MessageBox(NULL,"编号输入错误!请重新输入！","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//格式输入正确，执行删除
    {
      int j=find[no-1];
      std::vector<INFO>::iterator it=gen_info.begin()+j;
      gen_info.erase(it);
      MessageBox(NULL,"课程删除成功！","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }

  else//根本没有这门课
  {
    MessageBox(NULL,"此课程不存在！删除失败","FAIL!",MB_ICONINFORMATION|MB_OK);
    find.clear();
    return -1;
  }
}

/**
 * 函数名称: ToModifyCourse
 * 函数功能: 通过课程名修改综合信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToModifyCourse(void)
{
  char s[100];
  printf("\n\n请输入要修改的课程名:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByCourse(s);
  if(res!=-1)//有这门课
  {
    Flag1:
    printf("\n请输入要修改的课程编号(仅一个):");
    int no; scanf("%d",&no);getchar();//读入用户输入的编号
    if(no<1 || no>(find.size()))//编号格式输入错误
    {
      MessageBox(NULL,"编号输入错误！请重新输入！","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//执行删除功能
    {
      int j=find[no-1];

      printf("请按要求输入新的信息，其中缺省的数据项用“##”表示：\n");
      printf("-----------------------------------------------------------------------\n");
      printf("课程        学时    学分    任课教师    教师职称    上课班级    备注\n");
      scanf("%s%s%s%s%s%s%s",gen_info[j].course,gen_info[j].time,gen_info[j].credit,gen_info[j].teacher,gen_info[j].title,gen_info[j].classno,gen_info[j].extra );
      getchar();

      MessageBox(NULL,"课程信息修改成功！","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }

  else//根本没有这门课
  {
    MessageBox(NULL,"此课程不存在！修改失败","FAIL!",MB_ICONINFORMATION|MB_OK);
    find.clear();
    return -1;
  }
}


/**
 * 函数名称: ToInsertTeacher
 * 函数功能: 通过教师名插入综合信息
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToInsertTeacher(void)
{
  INFO temp;
  printf("请按要求输入以下信息，其中缺省的数据项用“##”表示：\n");
  printf("------------------------------------------------------------------------------------\n");
  printf("教师    职称    担任课程        此课程学时    此课程学分    上课班级        备注\n");
  scanf("%s%s%s%s%s%s%s",temp.teacher,temp.title,temp.course,temp.time,temp.credit,temp.classno,temp.extra );//读入用户输入的信息
  getchar();
  gen_info.push_back(temp);//执行插入
  MessageBox(NULL,"教师插入成功！","SUCCESS!",MB_OK);
  return 1;
}

/**
 * 函数名称: ToInsertTeacher
 * 函数功能: 通过教师名插入综合信息
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToFindGenInfoByTeacher(char s[])
{
   for(int  i=0;i<gen_info.size();i++)//寻找对应老师的课程综合信息
   {
     if(strstr(gen_info[i].teacher,s))//如果符合条件，那么加入find中
     {
       find.push_back(i);
     }
   }
   if(find.size()==0)//如果一个也没找到
     return -1;
   for(int i=0;i<find.size();i++)//输出所有的找到的信息以及 编号
   {
     INFO t=gen_info[find[i]];
     printf("-------------------------------------------------------------------------\n");
     printf("No.%d\n",i+1);
     printf("  教师姓名：%s\n",t.teacher);
     printf("  职称：  %s\n",t.title);
     printf("  担任课程：%s\n",t.course);
     printf("  上课班级：%s\n",t.classno);
     printf("  课程学时：%s\n",t.time);
     printf("  课程学分：%s\n",t.credit);
     printf("  备注：%s\n",t.extra);
     printf("-------------------------------------------------------------------------\n");
   }
   return 1;
}


/**
 * 函数名称: ToDeleteTeacher
 * 函数功能: 通过教师名删除综合信息
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToDeleteTeacher(void)
{
  char s[100];
  printf("\n\n请输入要删除的教师姓名:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByTeacher(s);//执行查找
  if(res!=-1)//有这个老师
  {
     int res=  MessageBox(NULL,"是否删除该教师与所有与该教师相关的信息？","？",MB_ICONQUESTION|MB_YESNO);
     if(res==IDYES)//选yes
     {
       for(int i=0;i<find.size();i++)
       {
         int j=find[i]-i;/**重点！因为find是从前往后遍历的，因为每删除一个，后边待删除数据元素的角标(无需删除的元素也是)集体向前移动了1,总的就是前移i*/
         std::vector<INFO>::iterator it=gen_info.begin()+j;
         gen_info.erase(it);
       }
       find.clear();
       MessageBox(NULL,"教师删除成功！","SUCCESS!",MB_OK);
       return 1;
     }
     else//选NO
     {
       find.clear();
       return 0;
     }
  }

  else//根本没有这个老师
  {
    MessageBox(NULL,"此教师不存在！删除失败","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }
}

/**
 * 函数名称: ToModifyTeacher
 * 函数功能: 通过教师名修改综合信息
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToModifyTeacher(void)
{
  char s[100];
  printf("\n\n请输入要修改信息的教师姓名:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByTeacher(s);//执行查找
  if(res!=-1)//有这门课
  {
    Flag1:
    printf("\n请输入要修改信息的数据元素编号(仅一个):");
    int no; scanf("%d",&no);getchar();
    if(no<1 || no>(find.size()))//编号格式错误
    {
      MessageBox(NULL,"编号输入错误！请重新输入！","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//格式正确
    {
      int j=find[no-1];

      printf("请按要求输入新的教师信息，其中缺省的数据项用“##”表示：\n");
      printf("------------------------------------------------------------------------------------\n");
      printf("教师    职称    担任课程        此课程学时    此课程学分    上课班级        备注\n");
      scanf("%s%s%s%s%s%s%s",gen_info[j].teacher,gen_info[j].title,gen_info[j].course,gen_info[j].time,gen_info[j].credit,gen_info[j].classno,gen_info[j].extra );
      getchar();

      MessageBox(NULL,"教师信息修改成功！","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }
  else//没有找到这门课
  {
    MessageBox(NULL,"此教师不存在！修改失败","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }

}



/**
 * 函数名称: LessonFileForm
 * 函数功能: 打印文件格式信息
 * 输入参数: 无
 * 返 回 值: 无
 *
 */
void LessonFileForm(void)
{
  printf("          数据文件格式\n");
  printf("--------------------------------------------------------------------\n");
  printf("\n课堂开始周数    课堂结束周数\n\n");
  printf("星期      (1~7表示周一到周日)\n\n");
  printf("节数      (1~6节)\n\n");
  printf("教学楼      (西十二、南一楼、西五楼、科技楼、东操场、西操场、中心操场)\n\n");
  printf("教室编号      (其中科技楼的教室只有“北楼”、操场没有教室用“##”表示)\n\n");
  printf("上课班级专业班号     (计算机校交,计算机卓工,计算机1601等,一起上课的班级用“,”隔开)\n\n");
  printf("课程名称\n\n" );
  printf("--------------------------------------------------------------------\n");
  printf("警告！！！格式错误会导致数据载入错误！！一切缺省项用“##”表示!\n\n");
}

/**
 * 函数名称: ToQueryCourseByTeacher
 * 函数功能: 通过教师查询综合信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int  ToQueryCourseByTeacher(void)
{
  char s[100];
  printf("请输入要查询的老师的信息：\n");
  scanf("%s",s);
  fflush(stdin);
  int res = ToFindGenInfoByTeacher(s);//查找的对应的老师的结点的信息
  if(res==-1)//没找到
  {
    MessageBox(NULL,"此教师不存在！查询失败！","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }
  else//找到
  {
    find.clear();
    printf("\n按任意键继续...");
    getch();
    return 1;
  }
}


/**
 * 函数名称: ToQueryLessonByClassno
 * 函数功能: 通过班级查询综合信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToQueryLessonByClassno(void)
{
  char s[100];
  printf("请输入要查询的班级的专业班号：\n  ");
  scanf("%s",s);
  fflush(stdin);
  int res=SearchByClassno(s);//查找
  if(res==1)//找到
  {
    printf("\n信息输出完成，按任意键继续...");
    getch();
    return 1;
  }
  else//没找到
  {
    MessageBox(NULL,"没有找到该班级相关信息！","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }

}


/**
 * 函数名称: ToQueryLessonByTimeAndPlace
 * 函数功能: 通过时间空间查询课堂信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToQueryLessonByTimeAndPlace(void)
{
  int week,day,period;
  char s1[81],s2[81];
  printf("请按要求输入该课堂的上课地点和时间: \n\n");
  printf("教学楼    教室    周次    星期    节数(1~6)\n");
  scanf("%s%s%d%d%d",s1,s2,&week,&day,&period);
  fflush(stdin);

  int timei=TimestrToNum(week,day,period);//时间hash值
  int placei=PlacestrToNum(s1,s2);//空间hash值
  if(timei==-1 || placei==-1)//格式错误
  {
    MessageBox(NULL,"上课时间空间输入错误！","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }


  int res=SearchByTimeAndPlace(timei ,placei);//根据时间和空间查找
  if(res==1)
  {
    printf("\n信息输出完成，按任意键继续...");
    getch();
    return 1;
  }
  else
  {
    MessageBox(NULL,"此时间该教室没有课！","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }
}


/**
 * 函数名称: ToQueryLessonByCourse
 * 函数功能: 通过课程名称查询信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToQueryLessonByCourse(void)
{
  char s[100];
  printf("请输入要查询的课程名称：\n  ");
  scanf("%s",s);
  fflush(stdin);
  int res=SearchByCourse(s);//通过课程名查询
  if(res==1)
  {
    printf("\n信息输出完成，按任意键继续...");
    getch();
    return 1;
  }
  else
  {
    MessageBox(NULL,"没有找到该课程相关信息！","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }
}

/**
 * 函数名称: ToQuerySpareClassroom
 * 函数功能: 查询空闲教室信息
 * 输入参数: 无
 * 返 回 值: 成功返回1，出错返回-1
 *
 */
int ToQuerySpareClassroom(void)
{
  int week,day,period;
  char s1[81],s2[81];
  printf("请输入要查询的教室以及时段: \n\n");
  printf("教学楼    教室    周次    星期    节数(1~6)\n");
  scanf("%s%s%d%d%d",s1,s2,&week,&day,&period);
  fflush(stdin);

  int timei=TimestrToNum(week,day,period);//获得时间hash值
  int placei=PlacestrToNum(s1,s2);//获得空间hash值
  if(timei==-1 || placei==-1)//时间空间格式输入错误
  {
    MessageBox(NULL,"教室与时段信息输入错误！","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }

  int res=SearchByTimeAndPlace(timei ,placei);//查找
  if(res==1)
  {
    MessageBox(NULL,"此时间此教室有课！非空闲！","FAIL!",MB_ICONINFORMATION|MB_OK);

    getchar();
    return -1;
  }
  else//没有查找到
  {
    printf("\n此时间此教室为空闲教室，按任意键继续...");
    getch();
    return 1;
  }
}
/**
 * 函数名称: AverageDx
 * 函数功能: 计算v数组中数的平均间隔
 * 输入参数: 要处理的数组
 * 返 回 值: 间隔平均值
 *
 */
double AverageDx(std::vector<int> v)//计算v数组中数的平均间隔
{
   //double aver=0;
   std::sort(v.begin(),v.end());
   double sumdx=0;
   int n=v.size();
   for(int i=0;i<n;i++)
   {
      if(i<v.size()-1)//数组中至少要有2个数
      {
        sumdx += (v[i+1]-v[i]);
      }
   }

   return n>1? (sumdx/(1.0*(n-1))) : 0;//数组中只有一个数，那么间隔设为0
}


/**
 * 函数名称: ToStatClassroomRate
 * 函数功能: 统计教室利用率以及能效分析
 * 输入参数: 无
 * 返 回 值: 返回1
 *
 */
int ToStatClassroomRate(void)
 {
    int roomnum=0; double ratesum=0.0,energ_rate_sum=0.0,dt_sum=0.0,sum_cnt=0;
    int day=0,night=0;//统计一个教室白天和晚上的上课数量以统计能效比
    std::vector<int>dt ;//用来统计一个教室上课的平均间隔
    int peri[6];//储存每个教室每个时间段的课堂总数
    int sum_peri[6];
    memset(sum_peri,0,sizeof sum_peri);
    printf("各个有课的教室的综合分析如下：\n\n\n");
   // printf("教室            利用率(教室的课堂数/一学期课堂总数)\n");


    for(int i=1;i<=259;i++)
    {

      memset(peri,0,sizeof peri);
      if(les_place[i].room_next==NULL)//如果教室没有课程
        continue;

      else
      {
        int cnt=0; roomnum++;
        day=night=0;//每个教室的白天和晚上的上课数量清零
        LESSON* p=les_place[i].room_next;
        while (p!=NULL)
        {
           cnt++;
           dt.push_back(TimestrToNum(p->week,p->day,p->period));
           peri[p->period -1]++;//统计每个时段的课堂数
           sum_peri[p->period -1]++;//统计所有教室每个时段的课堂数
           if(p->period<=4) day++;//如果白天上课
           else night++;//如果晚上上课
           p=p->time_next;
        }

        double rate=(1.0*cnt)/(840.0);
        ratesum += rate;//用于计算总的利用率
        energ_rate_sum += (1.0*day)/(1.0*(day+night));//用于计算平均能效比
        double aver = AverageDx(dt);//教室上课的平均的时间间隔
        dt_sum += aver;//用于计算平均能效比
        sum_cnt+=cnt;//用于统计所有教室一共有多少个课堂


        printf("-----------------------------------------------------------\n\n");
     //   printf("%s %s :   %d/%d = %.4f\n\n",les_place[i].building,les_place[i].classroom,cnt,840,rate);
       if((1.0*day)/(1.0*(day+night)) <0.33)
          printf("！！！当前教室能效比过低！！！\n\n");
       if(aver>45)
          printf("！！！当前教室的上课平均间隔过高,请适当增加课程！！！\n\n");
       if(aver==0)
          printf("！！！当前教室排课过少，请适当增加排课！！！\n\n");

        printf("教学楼： %s\n\n",les_place[i].building);
        printf("教室：   %s\n\n",les_place[i].classroom);
        printf("上课时段分布：\n\n");
        printf("         1-2节：  %d   %.2f%%\n\n",peri[0],100.0*peri[0]/(1.0*cnt));
        printf("         3-4节：  %d   %.2f%%\n\n",peri[1],100.0*peri[1]/(1.0*cnt));
        printf("         5-6节：  %d   %.2f%%\n\n",peri[2],100.0*peri[2]/(1.0*cnt));
        printf("         7-8节：  %d   %.2f%%\n\n",peri[3],100.0*peri[3]/(1.0*cnt));
        printf("         9-10节： %d   %.2f%%\n\n",peri[4],100.0*peri[4]/(1.0*cnt));
        printf("         11-12节：%d   %.2f%%\n\n\n",peri[5],100.0*peri[5]/(1.0*cnt));
        printf("教室上课平均间隔：%0.3f （节）\n\n",aver);
        printf("能效比(白天上课数/上课总数数)：%d/%d = %.3f\n\n",day,day+night,(1.0*day)/(1.0*(day+night)));
        printf("利用率(教室的课堂数/一学期课堂总数)：%d/%d = %.4f\n\n",cnt,840,rate);
        printf("-----------------------------------------------------------\n");
        dt.clear();



      }
    }
    printf("\n总结：\n\n");
    printf("\n\n所有教室上课时间分布汇总：\n\n");
    printf("         1-2节：  %d    %.2f%%\n\n",sum_peri[0],100.0*sum_peri[0]/(1.0*sum_cnt));
    printf("         3-4节：  %d    %.2f%%\n\n",sum_peri[1],100.0*sum_peri[1]/(1.0*sum_cnt));
    printf("         5-6节：  %d    %.2f%%\n\n",sum_peri[2],100.0*sum_peri[2]/(1.0*sum_cnt));
    printf("         7-8节：  %d    %.2f%%\n\n",sum_peri[3],100.0*sum_peri[3]/(1.0*sum_cnt));
    printf("         9-10节： %d    %.2f%%\n\n",sum_peri[4],100.0*sum_peri[4]/(1.0*sum_cnt));
    printf("         11-12节：%d    %.2f%%\n\n\n",sum_peri[5],100.0*sum_peri[5]/(1.0*sum_cnt));
    printf("\n共%d个教室本学期被安排了课程,其平均利用率为%.3f%%  \n\n",roomnum,100.0*ratesum/(1.0*roomnum));
    printf("其中总的平均能效比为：%.3f\n\n",energ_rate_sum/(1.0*roomnum));
    printf("每个教室上课的平均上课间隔为：%.3f (节)\n\n\n\n",dt_sum/(1.0*roomnum));

    if(ratesum/(1.0*roomnum)<0.5)
      printf("当前教室的平均利用率小有5%% 利用率比较低，应当适当增加排课\n\n");
     if(energ_rate_sum/(1.0*roomnum)<0.3)
       printf("当前教室的平均能效比较低，排课时应注意节能\n\n");
     else
       printf("当前教室的能效比较高，课程安排的节能参数优秀\n\n");

     if(dt_sum/(1.0*roomnum)>15)
       printf("当前教室的上课的平均时间间隔较大，课程的时间分布较分散\n\n按任意键继续...");
     else
       printf("当前教室的上课平均间隔合理，时间分布适中\n\n按任意键继续...");


    getch();

    return 1;

 }


/**
 * 函数名称: ToStatTeacherRate
 * 函数功能: 教师任课分析
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToStatTeacherRate(void)
{
   int sum=gen_info.size();
   bool done[sum+5];
   int cnt=0,sum_teacher=0;
   double credit=0,sum_credit=0;
   char* addr;
   char** paddr=&addr;
   memset(done,0,sizeof done);

   printf("教师任课情况分析如下：\n\n");
   printf("--------------------------------------\n");
   //printf("sum: %d\n",sum);
   for(int i=0;i<sum;i++)
   {
      if(done[i])
        continue;

     done[i]=1;
     credit=0; cnt=1;

     credit += strtod(gen_info[i].credit , paddr);//统计一个老师任课的总学分

     sum_teacher += 1;//相当于数一数一共有多少个老师

     for(int j=i+1;j<sum;j++)
     {
       if(done[j])
         continue;
       if(!strcmp(gen_info[i].teacher , gen_info[j].teacher) )
       {
         done[j]=1;

         credit += strtod(gen_info[j].credit , paddr);//统计一个老师任课的总学分
         cnt++;//统计一个老师的任课数量
       }
     }
     sum_credit += credit;//统计所有老师总学分
     printf("--------------------------------------\n");
     if(16*credit > 88)
     printf("\n！！！该教师教学任务较重 ！！！\n\n");
     else if(16*credit < 24)
     printf("\n！！！该教师担任课时较少 ！！！\n\n");

     printf("No.%d\n",sum_teacher);
     printf("教师姓名：      %s\n",gen_info[i].teacher);
     printf("职称：          %s\n",gen_info[i].title);
     printf("任课数量:       %d\n",cnt);
     printf("总任课学时：   %.0f\n",16*credit);
     printf("--------------------------------------\n\n");

   }

   printf("总结：\n\n本学期一共有%d位老师任课,其中平均每位老师担任%.3f门课,每位老师平均任课学时为%.3f\n\n\n",sum_teacher,(1.0*sum)/(1.0*sum_teacher),(16*sum_credit)/(1.0*sum_teacher));
  if((16*sum_credit)/(1.0*sum_teacher)>88 )
  {
    printf("  教师的平均任课学时过多,应该多引进教师,分担教学任务!\n");
  }
  else if((16*sum_credit)/(1.0*sum_teacher)<24)
  {
    printf("  教师的平均任课学时过少,人浮于事,应该增加教学任务!\n");
  }
  else
    printf("  教师的平均任课学时适中,教学安排相对合理!\n");


  printf("\n\n按任意键继续...");
  getch();

    return 1;

}


/**
 * 函数名称: MakeClassno
 * 函数功能: 生成班号字符串
 * 输入参数: 编号、 储存班号的字符串首地址
 * 返 回 值: 1
 *
 */
int MakeClassno(int i,char s[])
{
  switch (i)
  {
    case 1: strcpy(s,"计算机1701");break;
    case 2: strcpy(s,"计算机1702");break;
    case 3: strcpy(s,"计算机1703");break;
    case 4: strcpy(s,"计算机1704");break;
    case 5: strcpy(s,"计算机1705");break;
    case 6: strcpy(s,"计算机1706");break;
    case 7: strcpy(s,"计算机1707");break;
    case 8: strcpy(s,"计算机1708");break;
    case 9: strcpy(s,"计算机1709");break;
    case 10: strcpy(s,"计算机1710");break;
    case 11: strcpy(s,"计算机1711");break;
    case 12: strcpy(s,"计算机1712");break;
    case 13: strcpy(s,"计算机1713");break;
    case 14: strcpy(s,"计算机校交17");break;
    case 15: strcpy(s,"计算机卓工17");break;
    case 16: strcpy(s,"计算机1601");break;
    case 18:strcpy(s,"计算机1602");break;
    case 19:strcpy(s,"计算机1603");break;
    case 20:strcpy(s,"计算机1604");break;
    case 21: strcpy(s,"计算机1605");break;
    case 22: strcpy(s,"计算机1606");break;
    case 23: strcpy(s,"计算机1607");break;
    case 24: strcpy(s,"计算机1608");break;
    case 25: strcpy(s,"计算机1609");break;
    case 26: strcpy(s,"计算机1610");break;
    case 27: strcpy(s,"计算机ACM16");break;
    case 28: strcpy(s,"计算机卓工16");break;
    case 29: strcpy(s,"物联网16");break;
    case 30: strcpy(s,"信安1601");break;
    case 31: strcpy(s,"信安1602");break;
    case 32: strcpy(s,"信安1603");break;
    case 33: strcpy(s,"计算机1501");break;
    case 34:strcpy(s,"计算机1502");break;
    case 35:strcpy(s,"计算机1503");break;
    case 36:strcpy(s,"计算机1504");break;
    case 37: strcpy(s,"计算机1505");break;
    case 38: strcpy(s,"计算机1506");break;
    case 39: strcpy(s,"计算机1507");break;
    case 40: strcpy(s,"计算机1508");break;
    case 41: strcpy(s,"计算机1509");break;
    case 42: strcpy(s,"计算机1510");break;
    case 43: strcpy(s,"计算机ACM15");break;
    case 44: strcpy(s,"计算机卓工15");break;
    case 45: strcpy(s,"物联网15");break;
    case 46: strcpy(s,"信安1501");break;
    case 47: strcpy(s,"信安1502");break;
    case 48: strcpy(s,"信安1503");break;
    case 49: strcpy(s,"计算机校交16");break;
  }

  return 1;
}

/**
 * 函数名称: ToStatClassnoRate
 * 函数功能: 班级上课分析
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToStatClassnoRate(void)
{
   int sum_lesson=0;//所有班级一共上了多少节课
   int sum_course=0;//所有班级一共上了多少门课
   int cnt_lesson=0,cnt_course=0;
   int n=les_classno.size();
   int sum_class=0;
   char classno[25];
   double classno_dt=0.0;//一个班级的平均上课的时间间隔；
   double dt_sum=0.0; //总的时间间隔
   int peri[6];//储存每个班级每个时间段的课堂总数
   int sum_peri[6];
   memset(sum_peri,0,sizeof sum_peri);
   printf("班级上课分析如下：\n\n");


for(int j=1;j<=49;j++)
{
  MakeClassno(j,classno);
  cnt_lesson=0,cnt_course=0;//一个班级的课程和课堂数
  memset(peri,0,sizeof peri);
  std::vector<int>dt;
  for(int i=0;i<n;i++)
  {

    if(strstr(les_classno[i].classno,classno)==NULL)
       continue;

    LESSON* p=les_classno[i].lesson;
    while(p!=NULL)//按课程遍历统计
    {
      cnt_course++;
      cnt_lesson += (p->to) - (p->from) +1;
      peri[p->period -1] += (p->to) - (p->from) +1 ;//统计一个班级上课在各个时段的分布

      for(int k=p->from;k<=p->to;k++)//计算平均间隔
         dt.push_back(TimestrToNum(k,p->day,p->period));

      p=p->classno_next;
    }
  }
  if(cnt_course==0)//没有录入该班级的课程，不打印信息
   continue;

  dt_sum += (classno_dt=AverageDx(dt)) ;//用于计算总的平均时间间隔
  for(int i=0;i<6;i++) sum_peri[i]+=peri[i];//用于统计总的时间分布
  printf("-----------------------------------------------\n");
  if(cnt_lesson>=350)
    printf("！！！当前班级课业压力过大！！！\n\n");
  else if(cnt_lesson<100)
    printf("！！！当前班级课程太少,应适当增加学习内容！！！\n\n");
  if(classno_dt>5)
    printf("！！！当前班级的课堂平均时间间隔过大，课程分布稀疏 ！！！\n\n");

  printf("班级： %s\n\n",classno);
  printf("上课时段分布：\n\n");
  printf("         1-2节：  %d   %.2f%%\n\n",peri[0],100.0*peri[0]/(1.0*cnt_lesson));
  printf("         3-4节：  %d   %.2f%%\n\n",peri[1],100.0*peri[1]/(1.0*cnt_lesson));
  printf("         5-6节：  %d   %.2f%%\n\n",peri[2],100.0*peri[2]/(1.0*cnt_lesson));
  printf("         7-8节：  %d   %.2f%%\n\n",peri[3],100.0*peri[3]/(1.0*cnt_lesson));
  printf("         9-10节： %d   %.2f%%\n\n",peri[4],100.0*peri[4]/(1.0*cnt_lesson));
  printf("         11-12节：%d   %.2f%%\n\n\n",peri[5],100.0*peri[5]/(1.0*cnt_lesson));
  printf("总共上课课程数:  %d  \n\n",cnt_course);
  printf("总共上课节数：   %d   \n\n",2*cnt_lesson);
  printf("平均上课间隔：   %.3f (节)\n\n",classno_dt);
  printf("-----------------------------------------------\n");

  sum_lesson += cnt_lesson;
  sum_course += cnt_course;
  sum_class++;
  dt.clear();
}
// printf("class_sum:%d\n",sum_class);

   double everage_course = 1.0*sum_course/(1.0*sum_class);
   double everage_lesson = 1.0*sum_lesson/(1.0*sum_class);
   printf("\n\n\n总结：\n\n班级上课时间分布汇总：\n\n");
   printf("         1-2节：  %d    %.2f%%\n\n",sum_peri[0],100.0*sum_peri[0]/(1.0*sum_lesson));
   printf("         3-4节：  %d    %.2f%%\n\n",sum_peri[1],100.0*sum_peri[1]/(1.0*sum_lesson));
   printf("         5-6节：  %d    %.2f%%\n\n",sum_peri[2],100.0*sum_peri[2]/(1.0*sum_lesson));
   printf("         7-8节：  %d    %.2f%%\n\n",sum_peri[3],100.0*sum_peri[3]/(1.0*sum_lesson));
   printf("         9-10节： %d    %.2f%%\n\n",sum_peri[4],100.0*sum_peri[4]/(1.0*sum_lesson));
   printf("         11-12节：%d    %.2f%%\n\n\n",sum_peri[5],100.0*sum_peri[5]/(1.0*sum_lesson));

   printf("\n\n平均每个班级上课课程数为 %.3f \n\n平均每个班级上课节数为 %.3f\n\n",everage_course,2*everage_lesson);
   printf("平均每个班级的平均上课间隔为： %.3f (节)\n\n", 1.0*dt_sum/(1.0*sum_class));

    if(1.0*dt_sum/(1.0*sum_class)>5)//平均时间间隔判断
      printf("班级的平均上课时间间隔过大，排课分布稀疏，应适当紧密\n\n");
    else
      printf("班级的平均上课时间间隔适中，排课分布相对合理\n\n");

   if(everage_lesson>350)
     printf("班级的平均课堂数量过多,应当适当减小课业压力！\n\n");
   else if(everage_lesson<100)
     printf("班级的平均课堂数量过少,应当适当增加学习内容！\n\n");
   else
    printf("班级的平均课堂数量情况适中,课程安排相对合理\n\n");

  printf("按任意键继续...");
  getch();

   return 1;
}

/**
 * 函数名称: ToTraverseAll
 * 函数功能: 遍历所有课堂信息
 * 输入参数: 无
 * 返 回 值: 1
 *
 */
int ToTraverseAll(void)
{
  int no=0;
  for(int i=1;i<845;i++)
  {
    LESSON* p=les_time[i].time_next;
    while(p)
    {
      printf("-------------------------------------------------------------------\n");
      printf("No.%d\n",++no);
      printf("  课程：%s\n",p->course);
      printf("  周次：%d\n",p->week);
      printf("  星期：%d\n",p->day);
      printf("  节数：%d\n",p->period);
      printf("  教学楼：%s\n",p->building);
      printf("  教室：%s\n",p->classroom);
      printf("  班级：%s\n",p->classno);
      printf("-------------------------------------------------------------------\n");
      if((no%500) == 0)
      {
         printf("\n\n按任意键继续浏览下一页...");
         getch();
         ClearScreenTotalInputArea();//清屏
      }

      p=p->room_next;
    }
  }

  printf("\n\n遍历完成！按任意键继续...");
  getch();

  return 1;

}
