#include"ExeFunction.h"
//char s[100000];
/**
 * ��������: PlacestrToNum
 * ��������: �ѽ�ѧ¥�����ַ���ת��Ϊ�����±�
 * �������: ��ѧ¥������
 * �� �� ֵ: les_place�����±�
 *
 */

int  PlacestrToNum(char s1[] , char s2[])//s1��ʾ��ѧ¥s2��ʾ����
{

  if(!strcmp(s1,"��ʮ��"))//1~120
  {
      int n=0;
      if( (s2[0]!='N')&&(s2[0]!='S')&&(s2[0]!='n')&&(s2[0]!='s') )//�ж���¥�ͱ�¥
        return -1;

      if((s2[1]>'5')||(s2[1]<'1')||(s2[2]>'1')||(s2[2]<'0') || (s2[3]<'0') || (s2[3]>'9'))
        return -1 ;

      if( (s2[0]=='S')||(s2[0]=='s'))
        n += 60;

      n += 12*(s2[1]-'0'-1);//������¥ƫ��


      if(s2[2]!='0')
      {
        if( (s2[3]!='0')&&(s2[3]!='1')&& (s2[3]!='2') )//һ��ֻ��12������
        return -1;
        n += (10+(s2[3]-'0'));
      }
      else if(s2[3]!='0')
        n += (s2[3]-'0');

      else
        return -1;

    return n;

  }

  else if(!strcmp(s1,"����¥"))//131~230
  {
      if((s2[0]>'5')||(s2[0]<'1')||(s2[1]>'2')||(s2[1]<'0')||(s2[2]>'9')||(s2[2]<'0'))//������ַǷ��Ľ��ұ��
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
    else if(!strcmp(s1,"��һ¥"))//121~130
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

    else if(!strcmp(s1,"�Ƽ�¥"))//240
    {
       if(!strcmp(s2,"��¥"))
        return  240;
       else
         return  -1;

    }

    else if(!strcmp(s1,"���ٳ�"))
      return 241;
    else if(!strcmp(s1,"���Ĳٳ�"))
      return 242;
    else if(!strcmp(s1,"���ٳ�"))
      return 243;



    else
     return -1;
}
/**
 * ��������: TimestrToNum
 * ��������: �����������ڡ�����ת��Ϊles_time�����±�
 * �������: ���������ڡ�����
 * �� �� ֵ: les_time�����±�
 *
 */

int TimestrToNum(int week , int day , int period)//����ʱ��hashֵ
{
    if( (week<1)||(week>22) ||(day<1) || (day>7)||(period<1)||(period>6) )
        return -1;//���������Χ

    int res =7*6*(week-1) + 6*(day-1) +period;//����ʱ��hashֵ
    if( res>840 || res <1)//hashֵ������Χ
      return -1;
    return  res;
}

/**
 * ��������: LessonInsert
 * ��������: �ڶ�Ӧ��ʱ��ռ�������
 * �������: �ռ�hashֵ��ʱ��hashֵ��Ҫ����Ŀ��ýṹ��ָ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int LessonInsert(int placei,int timei,LESSON* temp)
{
  LESSON *p=NULL;
  //ʱ�������ռ�����Ӧ�Ľڵ㶼ΪNULL
  if((les_place[placei].room_next==NULL)&&(les_time[timei].time_next==NULL))
  {
    temp->lesson_time=&(les_time[timei]);temp->lesson_place=&(les_place[placei]);
  //  les_time[timei].time_next=(LESSON*)malloc(sizeof(LESSON));
    les_time[timei].time_next=temp;
    //les_place[placei].room_next=(LESSON*)malloc(sizeof(LESSON));
    les_place[placei].room_next=temp;
    return 1;
  }

  //�ռ������գ�ʱ����ΪNULL��Ҳ����ͬһ���ұ��ʱ���п�
  else if((les_place[placei].room_next!=NULL)&&(les_time[timei].time_next==NULL))
  {
    //les_time[timei].time_next=(LESSON*)malloc(sizeof(LESSON));
    temp->lesson_time=&(les_time[timei]);
    les_time[timei].time_next=temp;
   //�ڸý��ҵĶ�Ӧʱ��λ���������
    p=les_place[placei].room_next;
    while(p!=NULL)
    {
      int t1=TimestrToNum(p->week , p->day , p->period);
      if(t1<timei)
      {
         if(p->time_next!=NULL)
         {
             int t2=TimestrToNum(p->time_next->week , p->time_next->day , p->time_next->period);
             if(t2<timei) {p=p->time_next;continue;}//Ѱ�Һ��ʵĲ����
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
         else//p���û�п����ˣ��˿�����p��֮���ϿΣ���ô����p����
         {
           temp->lesson_place=&(les_place[placei]);
           p->time_next=temp;temp->time_pri=p;
           return 1;
         }
      }
      else if(t1>timei)//˵���˿�����p֮ǰ�Ͽ�
      {
         temp->lesson_place=&(les_place[placei]);
         les_place[placei].room_next=temp;
         temp->time_next=p; p->time_pri=temp;
         return 1;
      }
      else//ͬһ�ص��ͬһʱ�䣬�Ͽγ�ͻ
      {
        //printf("22222\n" );
        return -1;
      }

    }
  }

  //�ռ���ΪNULL��ʱ�������գ�Ҳ����ͬһʱ���ж�������ϿΣ����ڶ�Ӧ��λ��
  else if((les_place[placei].room_next==NULL)&&(les_time[timei].time_next!=NULL))
  {

    temp->lesson_place=&(les_place[placei]);
    les_place[placei].room_next=temp;
   //��ͬһʱ����ʵĽ��Ҳ���ÿ���
    p=les_time[timei].time_next;
    while(p!=NULL)
    {
      int t1=PlacestrToNum(p->building,p->classroom);
      if(t1<placei)//�ÿ��ÿռ�hashֵ�ϴ�
      {
         if(p->room_next!=NULL)
         {
             int t2 = PlacestrToNum(p->room_next->building, p->room_next->classroom);
             if(t2<placei) {p=p->room_next;continue;}//Ѱ�Һ��ʵĲ����
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
         else//���߲嵽p�ĺ���
         {
           temp->lesson_time=&(les_time[timei]);
           p->room_next=temp;temp->room_pri=p;
           return 1;
         }
      }
      else if(t1>placei)//�嵽p��ǰ��
      {
         temp->lesson_time=&(les_time[timei]);
         les_time[timei].time_next=temp;
         temp->room_next=p; p->room_pri=temp;
         return 1;
      }
      else//�Ͽγ�ͻ
      {
       // printf("4444\n");
        return -1;
      }


    }
  }

  else
  {
   //ʱ�����ռ��������գ���ʵǰ����if����д��ֻд�����������Ҳ����

   //Ѱ�Һ��ʵ�ʱ��
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

    //Ѱ�Һ��ʵĿռ�
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
 * ��������: ClassnoInsert
 * ��������: ��רҵ�༶��ά���Ͻ���������
 * �������: Ҫ����Ŀ��ýṹ��ָ��
 * �� �� ֵ: ����1
 *
 */
int  ClassnoInsert(LESSON* temp)
{
  int done=0;
  for(int i=0 ; i<les_classno.size() ; i++)//Ѱ�ҷ��������ı�ͷ
  {
     if(!strcmp(les_classno[i].classno , temp->classno))//����༶������ȣ���ô�ں������
     {
        done=1;
        if(les_classno[i].lesson==NULL)//���֮��û�н�㣬��ôֱ�Ӳ���
        {
          les_classno[i].lesson=temp;
          return 1;
        }
        else//����Ѱ�Һ��ʵĲ���λ��
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
          return 1;//������ɷ���1
        }
     }
  }

  if(!done)//���û��������ִ�в���������ڰ༶������һ���༶��Ȼ���ٲ���
  {
    CLASSNO t; t.lesson=NULL;
    strcpy(t.classno,temp->classno);
    t.lesson=temp;
    les_classno.push_back(t);
  }

 return 1;
}
/**
 * ��������: CourseInsert
 * ��������: �ڿγ̵�ά���Ͻ���������
 * �������: Ҫ����Ŀ��ýṹ��ָ��
 * �� �� ֵ: ����1
 *
 */
int CourseInsert(LESSON* temp)
{
  int done=0;
  for(int i=0 ; i<les_course.size() ; i++)//�����γ̲�������Ѱ��ͬ���γ�
  {
     //printf("i1:  %d    \n",i);
     //printf("2 temp->course: %s\n",temp->course);
     if(!strcmp(les_course[i].course , temp->course))//����γ̲���������ͬ���γ�
     {
        //printf("i2:   %d    \n",i);
        //printf("2 temp->course: %s\n",temp->course);
        done=1;
        if(les_course[i].lesson==NULL)//����ÿγ�������û�п���
        {
          les_course[i].lesson=temp;
         // printf("i3:   %d    \n",i);
          return 1;
        }
        else//��������п���
        {
         // printf("i4:   %d    \n",i);
          LESSON *p=les_course[i].lesson;
          LESSON* pp=p;
          while(p!=NULL)//Ѱ�Һ��ʵĲ���λ��
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

  if(!done)//���ǰ��û���ҵ�ͬ���Ŀγ̣���ô�ڿγ̲������������һ���γ̣�Ȼ���ٲ���
  {
    COURSE t; t.lesson=NULL;
    strcpy(t.course,temp->course);
    t.lesson=temp;
    les_course.push_back(t);
  }

 return 1;
}
/**
 * ��������: ReadLesson
 * ��������: �������ļ��ж�ȡ������Ϣ
 * �������: �����ļ����ļ�ָ��
 * �� �� ֵ: �ɹ�����1�������Ͽγ�ͻ�������-1
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
    while( fscanf(fp,"%d%d",&from ,&to)!=EOF)//�����ܴ�
    {
      // printf("T: %d\n", T);

     // printf("i : %d\n",++i);
       /*char building[15];
       char classroom[6];
       char teacher[20];
       char classno[80];
       char course[45];*/


       //��Ӧ�ĸ�ֵ
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
       for( i=from;i<=to;i++)//�ӿ�ʼ�ܴΣ��������ܴβ������
       {

         LESSON* atemp=(LESSON*)malloc(sizeof(LESSON));
         *atemp=*temp;
         atemp->week=i;
         int timei=TimestrToNum(atemp->week,atemp->day,atemp->period);//ȡ�ö�Ӧʱ��hashֵ
         int placei=PlacestrToNum(atemp->building,atemp->classroom);//ȡ�ÿռ�hashֵ
         if(timei==-1 || placei==-1)//���û���ҵ���Ӧ��hashֵ������-1
            return -1;


         res = LessonInsert( placei, timei,atemp);//�����Ӧ�Ŀ���

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
 * ��������: Init
 * ��������: ��ʼ����ͷ
 * �������: ��
 * �� �� ֵ: 1
 *
 */

int Init(void)
{
    //ʱ���ͷ��ֵ
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
    //��ʮ��¥�ı�ͷ��ֵ
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
           sroom[0]='N';//��¥��Ӧ�Ľ��ұ��
           sroom[4]='\0';


           strcpy(les_place[12*(i-1)+j].building, "��ʮ��");
           strcpy(les_place[12*(i-1)+j].classroom,sroom);
           les_place[12*(i-1)+j].room_next=NULL;
           sroom[0]='S';//��¥��Ӧ���
           strcpy(les_place[12*(i-1)+j+60].classroom,sroom);
           strcpy(les_place[12*(i-1)+j+60].building,"��ʮ��");
           les_place[12*(i-1)+j+60].room_next=NULL;

        }
    for(int i=1;i<=10;i++)//��һ¥�ı�ͷ��ֵ
    {
      int n=800; char sroom[10];
      n+=i;
      sprintf(sroom,"%d",n);
      strcpy(les_place[120+i].building, "��һ¥");
      strcpy(les_place[120+i].classroom,sroom);
      les_place[120+i].room_next=NULL;
    }
    strcpy(les_place[121].classroom,"116");//û��801�������滻��806

  //����¥�ı�ͷ��ʼ����ֵ
    for(int i=1;i<=5;i++)
        for(int j=1;j<=20;j++)
        {
           int n=100*i+j;
           char sroom[10];
           sprintf(sroom,"%d",n);
           int placei=PlacestrToNum("����¥",sroom);

           strcpy(les_place[placei].building, "����¥");
           strcpy(les_place[placei].classroom,sroom);
           les_place[placei].room_next=NULL;

        }

  //�����Ͽα�ͷ��ֵ
  strcpy(les_place[240].building, "�Ƽ�¥");
  strcpy(les_place[240].classroom,"��¥");
  les_place[240].room_next=NULL;

  strcpy(les_place[241].building, "���ٳ�");
  strcpy(les_place[241].classroom,"##");
  les_place[241].room_next=NULL;

  strcpy(les_place[242].building, "���Ĳٳ�");
  strcpy(les_place[242].classroom,"##");
  les_place[242].room_next=NULL;

  strcpy(les_place[243].building, "���ٳ�");
  strcpy(les_place[243].classroom,"##");
  les_place[243].room_next=NULL;

    return 1;
}

/**
 * ��������: SearchByTimeAndPlace
 * ��������: ����ʱ��Ϳռ���ҿ���
 * �������: ʱ��ռ��hashֵ
 * �� �� ֵ: �ҵ�����1��û�ҷ���-1
 *
 */

int SearchByTimeAndPlace(int timei,int placei)
{
  LESSON* p=les_place[placei].room_next;
  //printf("classroom : %s\n",les_place[placei].classroom);
  while(p!=NULL)//��Ҫ���ҵĿռ���Ѱ�Ҷ�Ӧ��ʱ��Ľ��
  {
      if((p->lesson_time) == &(les_time[timei]))//������ҵ��ˣ���ôֱ���˳�ѭ��
         break;

      p=p->time_next;//û�ҵ�����һ�����
  }
  if(p==NULL)//�������û�ҵ�
    return -1;
  else//�ҵ�,�����Ӧ������Ϣ
  {
    printf("-------------------------------------------------------------------\n");
    printf("  �γ̣�%s\n",p->course);
    printf("  �ܴΣ�%d~%d��\n",p->from,p->to);
    printf("  ���ڣ�%d\n",p->day);
    printf("  ������%d\n",p->period);
    printf("  ��ѧ¥��%s\n",p->building);
    printf("  ���ң�%s\n",p->classroom);
    printf("  �༶��%s\n",p->classno);
    printf("-------------------------------------------------------------------\n");
    return 1;
  }

}
/**
 * ��������: SearchByCourse
 * ��������: �ڿγ̲������ϲ��ҿ���
 * �������: �γ�����
 * �� �� ֵ: �ҵ�����1��û�ҷ���-1
 *
 */

int SearchByCourse(char s[])//���ݿγ���Ϣ���ҿ���
{
  int no=0;
  for(int i=0 ; i<(int)les_course.size() ; i++)//�����γ̲�����
  {
     if(strstr(les_course[i].course ,s))//����û�����Ŀ������ǲ�������ĳ����ͷ���Ӵ�
     {
        if(les_course[i].lesson==NULL)
          continue;

        else
        {
          LESSON *p=les_course[i].lesson;
          while(p!=NULL)//�����Ӧ������Ϣ
          {
            if(readed[p->No])
              continue;
              printf("-------------------------------------------------------------------\n");
              printf("No.%d\n",++no);
              printf("  �γ̣�%s\n",p->course);
              printf("  �ܴΣ�%d~%d��\n",p->from,p->to);
              printf("  ���ڣ�%d\n",p->day);
              printf("  ������%d\n",p->period);
              printf("  ��ѧ¥��%s\n",p->building);
              printf("  ���ң�%s\n",p->classroom);
              printf("  �༶��%s\n",p->classno);
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
 * ��������: SearchByClassno
 * ��������: ��רҵ��Ų������ϲ��ҿ�����Ϣ
 * �������: רҵ���
 * �� �� ֵ: �ҵ�����1��û�ҷ���-1
 *
 */

int SearchByClassno(char  s[])
{
  int no=0;
  for(int i=0 ; i<les_classno.size() ; i++)//�����༶������
  {
     if(strstr(les_classno[i].classno ,s))//����û�����İ༶�ǲ�������ĳ����ͷ���Ӵ�
     {
        if(les_classno[i].lesson==NULL)
          continue;

        else//����ҵ��˶�Ӧ�İ༶
        {
          LESSON *p=les_classno[i].lesson;
          while(p!=NULL)//���Ҷ�Ӧ�Ľ�㣬Ȼ�����
          {
            if(readed[p->No])
              continue;
            printf("-------------------------------------------------------------------\n");
            printf("No.%d\n",++no);
            printf("  �༶��%s\n",p->classno);
            printf("  �ܴΣ�%d~%d��\n",p->from,p->to);
            printf("  ���ڣ�%d\n",p->day);
            printf("  ������%d\n",p->period);
            printf("  ��ѧ¥��%s\n",p->building);
            printf("  ���ң�%s\n",p->classroom);
            printf("  �γ̣�%s\n",p->course);
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
 * ��������: ReadGeneralInfo
 * ��������: �������ļ��ж�ȡ�ۺ�������Ϣ
 * �������: �ۺ�������Ϣ�ļ�
 * �� �� ֵ: �ɹ�����1��û�ж����κ���Ϣ����-1
 *
 */



int ReadGeneralInfo(FILE * fp)
{
  // int i=0;
   INFO temp;int done=0;
   while(fscanf(fp,"%s",temp.course)!=EOF)//ѭ��������Ϣ
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
   if(!done)//���һ����û�ж���
     return -1;
    else
      return 1;

}

/**
 * ��������: ToSaveData
 * ��������: ��������Ϣ���ۺ���Ϣ�����ڶ�Ӧ���ļ���
 * �������: �����ļ���Ӧ���ļ�ָ��
 * �� �� ֵ: ����1
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


  for(int i=0;i<les_course.size();i++)//���տγ̲������е���Ϣ
  {
      LESSON *p = les_course[i].lesson;
      while(p)//�����пγ̲������е����е���Ϣ���
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


  for(int i=0;i<gen_info.size();i++)//���ۺϿγ���Ϣ�е����е���Ϣ���
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
 * ��������: SpaceToUnderline
 * ��������: ���ַ����еĿո����»���
 * �������: Ҫת�����ַ����׵�ַ
 * �� �� ֵ: ��
 *
 */
void SpaceToUnderline(char*s) //C������create�����ܴ������ļ����ļ���ֻ���Ǳ�ʶ������˰�ϵͳʱ���ַ����е�ð�ŵĿո����»���
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
 * ��������: AddBackslash
 * ��������: ���ַ����еĵ�б�߱��˫б��
 * �������: Ҫת�����ַ����׵�ַ
 * �� �� ֵ: ��
 *
 */
 void AddBackslash(char*s) //��һ����������������2������������ \ �ַ����ַ����У��ѳ��ֵ� \ �ַ����  "\\"
 {
     int i=0,j,len;
     for(i=0;s[i]!='\0';i++)
     {
         if(s[i]=='\\') // ���s[i]��\ ��
         {
             len=strlen(s);
             for(j=len;j>i;j--)//forѭ���ǰ�s[i]����������ַ����ƽ��һ�£�Ϊ����s[i]�����\�ڳ��ռ�
             {
               s[j+1]=s[j];
             }
             s[i+1]='\\';
             i++;  //ע����ʱ��s[i]֮����Ǹ��ַ�Ҳ��\�ˣ����iҪ����1��������ӵ�\ �����������\��

         }
         else
            continue;
     }
return;

}
/**
 * ��������: GetBackupFilename
 * ��������: �õ�����·���ı����ļ���
 * �������: ���汸���ļ������ַ����׵�ַ
 * �� �� ֵ: ��
 *
 */

void GetBackupFilename(char *dir1, char* dir2 )//�õ�����·���ı����ļ���

{
    int len;//�ַ�������

    time_t t;//����һ��ʱ�����
    t=time(NULL);

    char *time;//����һ���ַ������������ȡ�������ں�ʱ��
    time=ctime(&t);//��ֵ

    SpaceToUnderline(time);//C������create�����ܴ������ļ����ļ���ֻ���Ǳ�ʶ������˰�ϵͳʱ���ַ����е�ð�ŵĿո����»���

/*��ʱ���ַ���������Ϻ�׺�������ļ�����ע�ⲻ����strcat��������Ϊʱ���ַ���time��'\0'�ַ�֮ǰ���и��������Ļ��з���ֱ�ӽ��ϻ��".dat"�ӵ����з�����*/
      len=strlen(time);
      time[len-1]='.';
      time[len]='t';
      time[len+1]='x';
      time[len+2]='t';
      time[len+3]='\0';    //�����ļ�����������ˣ���ʱtime������ַ����Ǵ���׺�����ļ����ˣ���������ʱ���ַ���




      char BackupDir1[25]="backup\\lesson_";
      char BackupDir2[25]="backup\\gen_info_";
      //getcwd(dir1,100);//��ȡ��ǰ������ַ,�ص��ǣ���������һ�У�
/*char *getcwd(char *buf, size_t size);  ���ǻ�ȡ��ǰ��ַ������ԭ�ͣ������ڶ�������Ӧ����sizeof(dir),����ע���������Ǹ�ָ�볣��������ȫͬ��ָ�����������char s[10],*p=s **pp=&p; ,sizeof(s)����10
��sizeof(p)��sizeof(pp)ȴ����4����Ϊһ��ָ�����ռ�ĸ��ֽ��ǹ̶��ģ����charָ����Ϊ��������ʱ�򴫵ݲ����ַ�����ռ���ֽ�������˵ڶ�������ֻ����100����Ϊ��BackupData������
���������ڴ��溬��ַ�ı����ļ������ַ����� Ϊchar filename[100] sizeof(filename)����100*����getcwd(dir,sizeof(dir))�Ǵ����*/
      //getcwd(dir2,100);

      strcpy(dir1,BackupDir1);//�ڵ�ǰ������ַ֮�����\backup\���챸���ļ�������Ŀ¼
      strcpy(dir2,BackupDir2);
      strcat(dir1,time);//��Ŀ¼��������ļ���
      strcat(dir2,time);
      AddBackslash(dir1);//������·���ַ����������еĵ��� \ ���\\  �Ա㵱���ļ����ַ�����create�Ⱥ�������ʵ��ʱ \\ ת��� ��\��
      AddBackslash(dir2);

    //  printf("%s\n",dir1 );
     // printf("%s\n",dir2 );

     return ;
}

/**
 * ��������: ToBackup
 * ��������: ��������
 * �������: �����ļ�������
 * �� �� ֵ: 1
 *
 */

int ToBackup(char* filename1,char* filename2)//�������ļ��д��뱸����Ϣ
{
   FILE* fp1=fopen(filename1,"w+");
   FILE* fp2=fopen(filename2,"w+");
   if(fp1==NULL || fp2==NULL)
     return -1;

  // printf("fp1:%p  fp2:%p\n",fp1,fp2 );
   ToSaveData(fp1,fp2);//���Ӧ�ļ�ָ����ָ���ļ��д����Ӧ�ı�����Ϣ
   return 1;

}

/**
 * ��������: ClearScreenTotalInputArea
 * ��������: ����
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void ClearScreenTotalInputArea(void)
{

    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0,1};
    unsigned long size , ul;


    GetConsoleScreenBufferInfo(gh_std_out,&bInfo);  //ȡ��Ļ��������Ϣ
    size = bInfo.dwSize.X * (bInfo.dwSize.Y-1);   //������Ļ���������˵�һ���ַ���Ԫ��

    /*����Ļ���������˵�һ�����е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/

    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);


    /*����Ļ���������˵�һ�����е�Ԫ���Ϊ�ո��*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);
    SetConsoleCursorPosition(gh_std_out,home);


    return;

}

/**
 * ��������: DestroyLesson
 * ��������: �����ڴ��еĿ�������
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int DestroyLesson(void)
{
    //����ռ�ͬʱ�ƿտռ��ͷָ��
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
    //�ÿ�ʱ���ͷָ��
    for(int i=0;i<845;i++)
    {
        les_time[i].time_next=NULL;
    }

    lesson_sum=0;

   // printf("1111111111111\n");
    return 1;
}

/**
 * ��������: DestroyOtherVectorInfo
 * ��������: �����ۺ���Ϣ�����Լ��������е�����
 * �������: ��
 * �� �� ֵ: 1
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
 * ��������: DeleteLesson
 * ��������: ɾ����Ӧʱ��ռ�Ŀγ�
 * �������: Ҫɾ�����õ�ʱ��Ϳռ��hashֵ
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int DeleteLesson(int timei, int placei)
{
    LESSON* p=les_place[placei].room_next;
    while(p!=NULL)//��placei����Ѱ��ʱ����ȷ�Ľ��
    {
        if((p->lesson_time) == &(les_time[timei]))
           break;

        p=p->time_next;
    }
    if(p==NULL)//���û�ҵ�
    {
       // printf("111111\n");
        return -1;
    }

    //�����ҵ�

    /*�ռ����ϵ�ɾ��*/
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

    /*ʱ�����ϵ�ɾ��*/
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

    /*�༶���ϵ�ɾ��*/
    int classnoi=-1;
    for(int i=0;i<les_classno.size();i++)//����les_classno�ж�Ӧ���±�
    {
        if(!strcmp(p->classno,les_classno[i].classno))
        {
            classnoi=i; break;
        }

      // printf("les_classno i: %d\n",i);

    }
    if(classnoi==-1)//û�ҵ�˵����ֵ��ʱ���������
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


    /*�γ����ϵ�ɾ��*/
    int coursei=-1;
    for(int i=0;i<les_course.size();i++)//����les_classno�ж�Ӧ���±�
    {
        if(!strcmp(p->course,les_course[i].course))
        {
            coursei=i; break;
        }
       //  printf("les_course i: %d\n",i);

    }
    if(coursei==-1)//û�ҵ�˵����ֵ��ʱ���������
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
 * ��������: ToInsertLesson
 * ��������: �����Ӧʱ��ռ�Ŀγ�
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToInsertLesson(void)
{
  LESSON* temp=(LESSON*)malloc(sizeof(LESSON));
  int timei,placei;

  /*��ʱ���ĳ�ʼ��*/
  temp->time_next=temp->room_next=temp->time_pri=temp->room_pri=NULL;
 /*temp->teacher_next=temp->teacher_pri=NULL*/
  temp->classno_next=temp->classno_pri=temp->course_next=temp->course_pri=NULL;
  temp->lesson_time=NULL;
  temp->lesson_place=NULL;


Flag1://�����ʾ��Ϣ
  printf("˵����\n");
  printf("  1��һ��ѧ��1~20�ܣ�һ��7��(����1~7),ÿ��6��ڿ�\n");
  printf("  2����ѧ¥������ʮ��������¥����һ¥���Ƽ�¥�����ٳ�\n");
  printf("  3�����ٳ������Ĳٳ������пƼ�¥�Ľ���ֻ�С���¥�����ٳ��Ľ���Ϊ��##��\n\n");
  printf("������Ҫ����Ŀ������ڵ�ʱ�䡢�ص�(�ÿո�ֿ�)��\n");
  printf("------------------------------------------------------\n");
  printf("�ܴ�    ����    ����(1~6)    ��ѧ¥    ����\n");

  scanf("%d%d%d",&(temp->week),&(temp->day),&(temp->period) );
  scanf("%s%s",temp->building,temp->classroom );
  getchar();

  temp->from=temp->to=temp->week;
  timei=TimestrToNum(temp->week,temp->day,temp->period);//ȡ��ʱ��hashֵ
  placei=PlacestrToNum(temp->building,temp->classroom);//ȡ�ÿռ�hashֵ
  if(timei==-1 || placei==-1)//��ʽ�������
  {
    int result = MessageBox(NULL,"���������Ϣ��ʽ���߷�Χ����","ERROR",MB_ICONINFORMATION|MB_RETRYCANCEL);
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

  else//��ʽ��ȷ
  {
    ClearScreenTotalInputArea();
    printf("����������Ŀ�����Ϣ: \n");
    printf("---------------------------------------------------------\n");
    printf("רҵ���                     �γ�����        \n");
    scanf("%s%s",temp->classno,temp->course);
    getchar();
    if(LessonInsert(placei,timei,temp)==-1)//����ʧ�ܣ������Ͽγ�ͻ
    {
      MessageBox(NULL,"���ò���ʧ�ܣ����ܷ������Ͽγ�ͻ��","ERROR!",MB_ICONINFORMATION|MB_OK);
      ClearScreenTotalInputArea();
      return -1;
    }
    else//�ڿγ̺Ͱ༶�������ϲ��Ҷ�Ӧ�Ľ��
    {
       ClassnoInsert(temp);
            //printf("33333333\n");
       CourseInsert(temp);
            //printf("4444444444\n");
       temp->No = ++lesson_sum;
      MessageBox(NULL,"���ò�����ɣ�","SUCCESS!",MB_OK);
      ClearScreenTotalInputArea();
      return 1;
    }

  }

}

/**
 * ��������: ToDeleteLesson
 * ��������: ɾ����Ӧʱ��ռ�Ŀγ�
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */

int ToDeleteLesson(void)
{
  int timei,placei;
  int week,day,period;
  char s1[100],s2[100];
Flag1:
  printf("˵����\n");
  printf("  1��һ��ѧ��1~20�ܣ�һ��7��(����1~7),ÿ��6��ڿ�\n");
  printf("  2����ѧ¥������ʮ��������¥����һ¥���Ƽ�¥�����ٳ�\n");
  printf("  3�����ٳ������Ĳٳ������пƼ�¥�Ľ���ֻ�С���¥�����ٳ��Ľ���Ϊ��##��\n\n");
  printf("������Ҫ����Ŀ������ڵ�ʱ�䡢�ص�(�ÿո�ֿ�)��\n");
  printf("------------------------------------------------------\n");
  printf("�ܴ�    ����    ����(1~6)    ��ѧ¥    ����\n");

  scanf("%d%d%d",&week,&day,&period);
  scanf("%s%s",s1,s2);
  getchar();

  timei=TimestrToNum(week,day,period);//���ʱ��hashֵ
  placei=PlacestrToNum(s1,s2);//��ÿռ�hashֵ

  if(timei==-1 || placei==-1)//��ʽ�������
  {
    int result = MessageBox(NULL,"���������Ϣ��ʽ���߷�Χ����","ERROR",MB_ICONINFORMATION|MB_RETRYCANCEL);
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
  else//��ʽ��ȷ
  {
    int res =  DeleteLesson(timei,placei);//ɾ��
    if(res==1)//ɾ��ִ�гɹ�
    {
      MessageBox(NULL,"����ɾ����ɣ�","SUCCESS!",MB_OK);
      ClearScreenTotalInputArea();
      return 1;
    }
    else//ɾ��ʧ��
    {
      MessageBox(NULL,"����ɾ��ʧ�ܣ����ܴ˿��ò����ڣ�","ERROR!",MB_ICONINFORMATION|MB_OK);
      ClearScreenTotalInputArea();
      return -1;
    }
  }
}
/**
 * ��������: ReloadData
 * ��������: �����ڴ��е�����
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */

int ReloadData(void)
{
  FILE* fp1=fopen("data\\lesson_to_read.txt","r+");
//  printf("1111\n");
  FILE* fp2=fopen("data\\gen_info.txt","r+");
  DestroyLesson();//�����ڴ��еĿ�������
  DestroyOtherVectorInfo();//�����ڴ��е��ۺϿγ���Ϣ
//  printf("22222\n");
//  printf("fp: %p \n",fp);
  int res1=ReadLesson(fp1);//�ٴδ��ļ����������Ϣ
  //printf("res : %d  \n",res);
  int res2=ReadGeneralInfo(fp2);//�ٴδ��ļ������ۺϿγ���Ϣ
  fclose(fp1);
  fclose(fp2);

  if((res1==-1)||(res2==-1))//ʧ��
  {
     return -1;
  }
  else//�ɹ�
  {
    return 1;
  }

}
/**
 * ��������: ToModifyLesson
 * ��������: �޸Ŀ�����Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToModifyLesson(void)
{

   LessonFileForm();//��ӡ���������ļ��ĸ�ʽ��Ϣ
   system(".\\data\\lesson_to_read.txt");//�򿪶�Ӧ�����������ļ�
   //system(".\\data\\lesson_to_save.txt");

   int res=ReloadData();//�û��޸���֮����������

   if(res==-1)//�����ļ��еĿ����ſγ�ͻ
   {
     MessageBox(NULL,"�����޸Ĵ��󣡿��ܷ������Ͽγ�ͻ��","ERROR!",MB_ICONINFORMATION|MB_OK);
     return -1;
   }
   else//�޸ĳɹ�
   {
     MessageBox(NULL,"�����޸ĳɹ���","SUCCESS!",MB_OK);
     return 1;
   }
}

/**
 * ��������: ToInsertCourse
 * ��������: ����γ�
 * �������: ��
 * �� �� ֵ: �ɹ�����1
 *
 */
int ToInsertCourse(void)
{
  INFO temp;
  printf("�밴Ҫ������������Ϣ������ȱʡ���������á�##����ʾ��\n");
  printf("-----------------------------------------------------------------------\n");
  printf("�γ�        ѧʱ    ѧ��    �ον�ʦ    ��ʦְ��    �Ͽΰ༶    ��ע\n");
  scanf("%s%s%s%s%s%s%s",temp.course,temp.time,temp.credit,temp.teacher,temp.title,temp.classno,temp.extra );
  getchar();
  gen_info.push_back(temp);//������Ϣ
  MessageBox(NULL,"�γ̲���ɹ���","SUCCESS!",MB_OK);
  return 1;
}

/**
 * ��������: ToFindGenInfoByCourse
 * ��������: ͨ���γ�����ѯ�ۺ���Ϣ
 * �������: �γ���
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToFindGenInfoByCourse(char s[])
{
   for(int  i=0;i<gen_info.size();i++)//���ݿγ���������Ҫ���ҵ����ݽ����±꣬����find��
   {
     if(strstr(gen_info[i].course,s))
     {
       find.push_back(i);
     }
   }
   if(find.size()==0)
     return -1;
   for(int i=0;i<find.size();i++)//���ҵ��Ķ���ӡ����
   {
     INFO t=gen_info[find[i]];
     printf("-------------------------------------------------------------------------\n");
     printf("No.%d\n",i+1);
     printf("  �γ̣�%s\n",t.course);
     printf("  ѧʱ��%s\n",t.time);
     printf("  ѧ�֣�%s\n",t.credit);
     printf("  �ον�ʦ��%s\n",t.teacher);
     printf("  ��ʦְ�ƣ�%s\n",t.title);
     printf("  �Ͽΰ༶��%s\n",t.classno);
     printf("  ��ע��%s\n",t.extra);
     printf("-------------------------------------------------------------------------\n");
   }
   return 1;
}

/**
 * ��������: ToDeleteCourse
 * ��������: ͨ���γ���ɾ���ۺ���Ϣ
 * �������: �γ���
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToDeleteCourse(void)
{
  char s[100];
  printf("\n\n������Ҫɾ���Ŀγ���:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByCourse(s);
  if(res!=-1)//�����ſ�
  {
    Flag1:
    printf("\n������Ҫɾ���Ŀγ̱��(��һ��):");
    int no; scanf("%d",&no);getchar();//����Ҫɾ���Ŀ��õı��
    if(no<1 || no>(find.size()))//�������ĸ�ʽ����
    {
      MessageBox(NULL,"����������!���������룡","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//��ʽ������ȷ��ִ��ɾ��
    {
      int j=find[no-1];
      std::vector<INFO>::iterator it=gen_info.begin()+j;
      gen_info.erase(it);
      MessageBox(NULL,"�γ�ɾ���ɹ���","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }

  else//����û�����ſ�
  {
    MessageBox(NULL,"�˿γ̲����ڣ�ɾ��ʧ��","FAIL!",MB_ICONINFORMATION|MB_OK);
    find.clear();
    return -1;
  }
}

/**
 * ��������: ToModifyCourse
 * ��������: ͨ���γ����޸��ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToModifyCourse(void)
{
  char s[100];
  printf("\n\n������Ҫ�޸ĵĿγ���:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByCourse(s);
  if(res!=-1)//�����ſ�
  {
    Flag1:
    printf("\n������Ҫ�޸ĵĿγ̱��(��һ��):");
    int no; scanf("%d",&no);getchar();//�����û�����ı��
    if(no<1 || no>(find.size()))//��Ÿ�ʽ�������
    {
      MessageBox(NULL,"�������������������룡","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//ִ��ɾ������
    {
      int j=find[no-1];

      printf("�밴Ҫ�������µ���Ϣ������ȱʡ���������á�##����ʾ��\n");
      printf("-----------------------------------------------------------------------\n");
      printf("�γ�        ѧʱ    ѧ��    �ον�ʦ    ��ʦְ��    �Ͽΰ༶    ��ע\n");
      scanf("%s%s%s%s%s%s%s",gen_info[j].course,gen_info[j].time,gen_info[j].credit,gen_info[j].teacher,gen_info[j].title,gen_info[j].classno,gen_info[j].extra );
      getchar();

      MessageBox(NULL,"�γ���Ϣ�޸ĳɹ���","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }

  else//����û�����ſ�
  {
    MessageBox(NULL,"�˿γ̲����ڣ��޸�ʧ��","FAIL!",MB_ICONINFORMATION|MB_OK);
    find.clear();
    return -1;
  }
}


/**
 * ��������: ToInsertTeacher
 * ��������: ͨ����ʦ�������ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int ToInsertTeacher(void)
{
  INFO temp;
  printf("�밴Ҫ������������Ϣ������ȱʡ���������á�##����ʾ��\n");
  printf("------------------------------------------------------------------------------------\n");
  printf("��ʦ    ְ��    ���ογ�        �˿γ�ѧʱ    �˿γ�ѧ��    �Ͽΰ༶        ��ע\n");
  scanf("%s%s%s%s%s%s%s",temp.teacher,temp.title,temp.course,temp.time,temp.credit,temp.classno,temp.extra );//�����û��������Ϣ
  getchar();
  gen_info.push_back(temp);//ִ�в���
  MessageBox(NULL,"��ʦ����ɹ���","SUCCESS!",MB_OK);
  return 1;
}

/**
 * ��������: ToInsertTeacher
 * ��������: ͨ����ʦ�������ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int ToFindGenInfoByTeacher(char s[])
{
   for(int  i=0;i<gen_info.size();i++)//Ѱ�Ҷ�Ӧ��ʦ�Ŀγ��ۺ���Ϣ
   {
     if(strstr(gen_info[i].teacher,s))//���������������ô����find��
     {
       find.push_back(i);
     }
   }
   if(find.size()==0)//���һ��Ҳû�ҵ�
     return -1;
   for(int i=0;i<find.size();i++)//������е��ҵ�����Ϣ�Լ� ���
   {
     INFO t=gen_info[find[i]];
     printf("-------------------------------------------------------------------------\n");
     printf("No.%d\n",i+1);
     printf("  ��ʦ������%s\n",t.teacher);
     printf("  ְ�ƣ�  %s\n",t.title);
     printf("  ���ογ̣�%s\n",t.course);
     printf("  �Ͽΰ༶��%s\n",t.classno);
     printf("  �γ�ѧʱ��%s\n",t.time);
     printf("  �γ�ѧ�֣�%s\n",t.credit);
     printf("  ��ע��%s\n",t.extra);
     printf("-------------------------------------------------------------------------\n");
   }
   return 1;
}


/**
 * ��������: ToDeleteTeacher
 * ��������: ͨ����ʦ��ɾ���ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int ToDeleteTeacher(void)
{
  char s[100];
  printf("\n\n������Ҫɾ���Ľ�ʦ����:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByTeacher(s);//ִ�в���
  if(res!=-1)//�������ʦ
  {
     int res=  MessageBox(NULL,"�Ƿ�ɾ���ý�ʦ��������ý�ʦ��ص���Ϣ��","��",MB_ICONQUESTION|MB_YESNO);
     if(res==IDYES)//ѡyes
     {
       for(int i=0;i<find.size();i++)
       {
         int j=find[i]-i;/**�ص㣡��Ϊfind�Ǵ�ǰ��������ģ���Ϊÿɾ��һ������ߴ�ɾ������Ԫ�صĽǱ�(����ɾ����Ԫ��Ҳ��)������ǰ�ƶ���1,�ܵľ���ǰ��i*/
         std::vector<INFO>::iterator it=gen_info.begin()+j;
         gen_info.erase(it);
       }
       find.clear();
       MessageBox(NULL,"��ʦɾ���ɹ���","SUCCESS!",MB_OK);
       return 1;
     }
     else//ѡNO
     {
       find.clear();
       return 0;
     }
  }

  else//����û�������ʦ
  {
    MessageBox(NULL,"�˽�ʦ�����ڣ�ɾ��ʧ��","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }
}

/**
 * ��������: ToModifyTeacher
 * ��������: ͨ����ʦ���޸��ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int ToModifyTeacher(void)
{
  char s[100];
  printf("\n\n������Ҫ�޸���Ϣ�Ľ�ʦ����:\n  ");
  scanf("%s",s);
  getchar();

  int res=ToFindGenInfoByTeacher(s);//ִ�в���
  if(res!=-1)//�����ſ�
  {
    Flag1:
    printf("\n������Ҫ�޸���Ϣ������Ԫ�ر��(��һ��):");
    int no; scanf("%d",&no);getchar();
    if(no<1 || no>(find.size()))//��Ÿ�ʽ����
    {
      MessageBox(NULL,"�������������������룡","ERROR!",MB_ICONINFORMATION|MB_OK);
      fflush(stdin);
      goto Flag1;
    }
    else//��ʽ��ȷ
    {
      int j=find[no-1];

      printf("�밴Ҫ�������µĽ�ʦ��Ϣ������ȱʡ���������á�##����ʾ��\n");
      printf("------------------------------------------------------------------------------------\n");
      printf("��ʦ    ְ��    ���ογ�        �˿γ�ѧʱ    �˿γ�ѧ��    �Ͽΰ༶        ��ע\n");
      scanf("%s%s%s%s%s%s%s",gen_info[j].teacher,gen_info[j].title,gen_info[j].course,gen_info[j].time,gen_info[j].credit,gen_info[j].classno,gen_info[j].extra );
      getchar();

      MessageBox(NULL,"��ʦ��Ϣ�޸ĳɹ���","SUCCESS!",MB_OK);
      find.clear();
      return 1;
    }
  }
  else//û���ҵ����ſ�
  {
    MessageBox(NULL,"�˽�ʦ�����ڣ��޸�ʧ��","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }

}



/**
 * ��������: LessonFileForm
 * ��������: ��ӡ�ļ���ʽ��Ϣ
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void LessonFileForm(void)
{
  printf("          �����ļ���ʽ\n");
  printf("--------------------------------------------------------------------\n");
  printf("\n���ÿ�ʼ����    ���ý�������\n\n");
  printf("����      (1~7��ʾ��һ������)\n\n");
  printf("����      (1~6��)\n\n");
  printf("��ѧ¥      (��ʮ������һ¥������¥���Ƽ�¥�����ٳ������ٳ������Ĳٳ�)\n\n");
  printf("���ұ��      (���пƼ�¥�Ľ���ֻ�С���¥�����ٳ�û�н����á�##����ʾ)\n\n");
  printf("�Ͽΰ༶רҵ���     (�����У��,�����׿��,�����1601��,һ���Ͽεİ༶�á�,������)\n\n");
  printf("�γ�����\n\n" );
  printf("--------------------------------------------------------------------\n");
  printf("���棡������ʽ����ᵼ������������󣡣�һ��ȱʡ���á�##����ʾ!\n\n");
}

/**
 * ��������: ToQueryCourseByTeacher
 * ��������: ͨ����ʦ��ѯ�ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int  ToQueryCourseByTeacher(void)
{
  char s[100];
  printf("������Ҫ��ѯ����ʦ����Ϣ��\n");
  scanf("%s",s);
  fflush(stdin);
  int res = ToFindGenInfoByTeacher(s);//���ҵĶ�Ӧ����ʦ�Ľ�����Ϣ
  if(res==-1)//û�ҵ�
  {
    MessageBox(NULL,"�˽�ʦ�����ڣ���ѯʧ�ܣ�","FAIL!",MB_ICONEXCLAMATION|MB_OK);
    find.clear();
    return -1;
  }
  else//�ҵ�
  {
    find.clear();
    printf("\n�����������...");
    getch();
    return 1;
  }
}


/**
 * ��������: ToQueryLessonByClassno
 * ��������: ͨ���༶��ѯ�ۺ���Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToQueryLessonByClassno(void)
{
  char s[100];
  printf("������Ҫ��ѯ�İ༶��רҵ��ţ�\n  ");
  scanf("%s",s);
  fflush(stdin);
  int res=SearchByClassno(s);//����
  if(res==1)//�ҵ�
  {
    printf("\n��Ϣ�����ɣ������������...");
    getch();
    return 1;
  }
  else//û�ҵ�
  {
    MessageBox(NULL,"û���ҵ��ð༶�����Ϣ��","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }

}


/**
 * ��������: ToQueryLessonByTimeAndPlace
 * ��������: ͨ��ʱ��ռ��ѯ������Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToQueryLessonByTimeAndPlace(void)
{
  int week,day,period;
  char s1[81],s2[81];
  printf("�밴Ҫ������ÿ��õ��Ͽεص��ʱ��: \n\n");
  printf("��ѧ¥    ����    �ܴ�    ����    ����(1~6)\n");
  scanf("%s%s%d%d%d",s1,s2,&week,&day,&period);
  fflush(stdin);

  int timei=TimestrToNum(week,day,period);//ʱ��hashֵ
  int placei=PlacestrToNum(s1,s2);//�ռ�hashֵ
  if(timei==-1 || placei==-1)//��ʽ����
  {
    MessageBox(NULL,"�Ͽ�ʱ��ռ��������","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }


  int res=SearchByTimeAndPlace(timei ,placei);//����ʱ��Ϳռ����
  if(res==1)
  {
    printf("\n��Ϣ�����ɣ������������...");
    getch();
    return 1;
  }
  else
  {
    MessageBox(NULL,"��ʱ��ý���û�пΣ�","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }
}


/**
 * ��������: ToQueryLessonByCourse
 * ��������: ͨ���γ����Ʋ�ѯ��Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToQueryLessonByCourse(void)
{
  char s[100];
  printf("������Ҫ��ѯ�Ŀγ����ƣ�\n  ");
  scanf("%s",s);
  fflush(stdin);
  int res=SearchByCourse(s);//ͨ���γ�����ѯ
  if(res==1)
  {
    printf("\n��Ϣ�����ɣ������������...");
    getch();
    return 1;
  }
  else
  {
    MessageBox(NULL,"û���ҵ��ÿγ������Ϣ��","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }
}

/**
 * ��������: ToQuerySpareClassroom
 * ��������: ��ѯ���н�����Ϣ
 * �������: ��
 * �� �� ֵ: �ɹ�����1��������-1
 *
 */
int ToQuerySpareClassroom(void)
{
  int week,day,period;
  char s1[81],s2[81];
  printf("������Ҫ��ѯ�Ľ����Լ�ʱ��: \n\n");
  printf("��ѧ¥    ����    �ܴ�    ����    ����(1~6)\n");
  scanf("%s%s%d%d%d",s1,s2,&week,&day,&period);
  fflush(stdin);

  int timei=TimestrToNum(week,day,period);//���ʱ��hashֵ
  int placei=PlacestrToNum(s1,s2);//��ÿռ�hashֵ
  if(timei==-1 || placei==-1)//ʱ��ռ��ʽ�������
  {
    MessageBox(NULL,"������ʱ����Ϣ�������","FAIL!",MB_ICONINFORMATION|MB_OK);
    return -1;
  }

  int res=SearchByTimeAndPlace(timei ,placei);//����
  if(res==1)
  {
    MessageBox(NULL,"��ʱ��˽����пΣ��ǿ��У�","FAIL!",MB_ICONINFORMATION|MB_OK);

    getchar();
    return -1;
  }
  else//û�в��ҵ�
  {
    printf("\n��ʱ��˽���Ϊ���н��ң������������...");
    getch();
    return 1;
  }
}
/**
 * ��������: AverageDx
 * ��������: ����v����������ƽ�����
 * �������: Ҫ���������
 * �� �� ֵ: ���ƽ��ֵ
 *
 */
double AverageDx(std::vector<int> v)//����v����������ƽ�����
{
   //double aver=0;
   std::sort(v.begin(),v.end());
   double sumdx=0;
   int n=v.size();
   for(int i=0;i<n;i++)
   {
      if(i<v.size()-1)//����������Ҫ��2����
      {
        sumdx += (v[i+1]-v[i]);
      }
   }

   return n>1? (sumdx/(1.0*(n-1))) : 0;//������ֻ��һ��������ô�����Ϊ0
}


/**
 * ��������: ToStatClassroomRate
 * ��������: ͳ�ƽ����������Լ���Ч����
 * �������: ��
 * �� �� ֵ: ����1
 *
 */
int ToStatClassroomRate(void)
 {
    int roomnum=0; double ratesum=0.0,energ_rate_sum=0.0,dt_sum=0.0,sum_cnt=0;
    int day=0,night=0;//ͳ��һ�����Ұ�������ϵ��Ͽ�������ͳ����Ч��
    std::vector<int>dt ;//����ͳ��һ�������Ͽε�ƽ�����
    int peri[6];//����ÿ������ÿ��ʱ��εĿ�������
    int sum_peri[6];
    memset(sum_peri,0,sizeof sum_peri);
    printf("�����пεĽ��ҵ��ۺϷ������£�\n\n\n");
   // printf("����            ������(���ҵĿ�����/һѧ�ڿ�������)\n");


    for(int i=1;i<=259;i++)
    {

      memset(peri,0,sizeof peri);
      if(les_place[i].room_next==NULL)//�������û�пγ�
        continue;

      else
      {
        int cnt=0; roomnum++;
        day=night=0;//ÿ�����ҵİ�������ϵ��Ͽ���������
        LESSON* p=les_place[i].room_next;
        while (p!=NULL)
        {
           cnt++;
           dt.push_back(TimestrToNum(p->week,p->day,p->period));
           peri[p->period -1]++;//ͳ��ÿ��ʱ�εĿ�����
           sum_peri[p->period -1]++;//ͳ�����н���ÿ��ʱ�εĿ�����
           if(p->period<=4) day++;//��������Ͽ�
           else night++;//��������Ͽ�
           p=p->time_next;
        }

        double rate=(1.0*cnt)/(840.0);
        ratesum += rate;//���ڼ����ܵ�������
        energ_rate_sum += (1.0*day)/(1.0*(day+night));//���ڼ���ƽ����Ч��
        double aver = AverageDx(dt);//�����Ͽε�ƽ����ʱ����
        dt_sum += aver;//���ڼ���ƽ����Ч��
        sum_cnt+=cnt;//����ͳ�����н���һ���ж��ٸ�����


        printf("-----------------------------------------------------------\n\n");
     //   printf("%s %s :   %d/%d = %.4f\n\n",les_place[i].building,les_place[i].classroom,cnt,840,rate);
       if((1.0*day)/(1.0*(day+night)) <0.33)
          printf("��������ǰ������Ч�ȹ��ͣ�����\n\n");
       if(aver>45)
          printf("��������ǰ���ҵ��Ͽ�ƽ���������,���ʵ����ӿγ̣�����\n\n");
       if(aver==0)
          printf("��������ǰ�����ſι��٣����ʵ������ſΣ�����\n\n");

        printf("��ѧ¥�� %s\n\n",les_place[i].building);
        printf("���ң�   %s\n\n",les_place[i].classroom);
        printf("�Ͽ�ʱ�ηֲ���\n\n");
        printf("         1-2�ڣ�  %d   %.2f%%\n\n",peri[0],100.0*peri[0]/(1.0*cnt));
        printf("         3-4�ڣ�  %d   %.2f%%\n\n",peri[1],100.0*peri[1]/(1.0*cnt));
        printf("         5-6�ڣ�  %d   %.2f%%\n\n",peri[2],100.0*peri[2]/(1.0*cnt));
        printf("         7-8�ڣ�  %d   %.2f%%\n\n",peri[3],100.0*peri[3]/(1.0*cnt));
        printf("         9-10�ڣ� %d   %.2f%%\n\n",peri[4],100.0*peri[4]/(1.0*cnt));
        printf("         11-12�ڣ�%d   %.2f%%\n\n\n",peri[5],100.0*peri[5]/(1.0*cnt));
        printf("�����Ͽ�ƽ�������%0.3f ���ڣ�\n\n",aver);
        printf("��Ч��(�����Ͽ���/�Ͽ�������)��%d/%d = %.3f\n\n",day,day+night,(1.0*day)/(1.0*(day+night)));
        printf("������(���ҵĿ�����/һѧ�ڿ�������)��%d/%d = %.4f\n\n",cnt,840,rate);
        printf("-----------------------------------------------------------\n");
        dt.clear();



      }
    }
    printf("\n�ܽ᣺\n\n");
    printf("\n\n���н����Ͽ�ʱ��ֲ����ܣ�\n\n");
    printf("         1-2�ڣ�  %d    %.2f%%\n\n",sum_peri[0],100.0*sum_peri[0]/(1.0*sum_cnt));
    printf("         3-4�ڣ�  %d    %.2f%%\n\n",sum_peri[1],100.0*sum_peri[1]/(1.0*sum_cnt));
    printf("         5-6�ڣ�  %d    %.2f%%\n\n",sum_peri[2],100.0*sum_peri[2]/(1.0*sum_cnt));
    printf("         7-8�ڣ�  %d    %.2f%%\n\n",sum_peri[3],100.0*sum_peri[3]/(1.0*sum_cnt));
    printf("         9-10�ڣ� %d    %.2f%%\n\n",sum_peri[4],100.0*sum_peri[4]/(1.0*sum_cnt));
    printf("         11-12�ڣ�%d    %.2f%%\n\n\n",sum_peri[5],100.0*sum_peri[5]/(1.0*sum_cnt));
    printf("\n��%d�����ұ�ѧ�ڱ������˿γ�,��ƽ��������Ϊ%.3f%%  \n\n",roomnum,100.0*ratesum/(1.0*roomnum));
    printf("�����ܵ�ƽ����Ч��Ϊ��%.3f\n\n",energ_rate_sum/(1.0*roomnum));
    printf("ÿ�������Ͽε�ƽ���Ͽμ��Ϊ��%.3f (��)\n\n\n\n",dt_sum/(1.0*roomnum));

    if(ratesum/(1.0*roomnum)<0.5)
      printf("��ǰ���ҵ�ƽ��������С��5%% �����ʱȽϵͣ�Ӧ���ʵ������ſ�\n\n");
     if(energ_rate_sum/(1.0*roomnum)<0.3)
       printf("��ǰ���ҵ�ƽ����Ч�Ƚϵͣ��ſ�ʱӦע�����\n\n");
     else
       printf("��ǰ���ҵ���Ч�Ƚϸߣ��γ̰��ŵĽ��ܲ�������\n\n");

     if(dt_sum/(1.0*roomnum)>15)
       printf("��ǰ���ҵ��Ͽε�ƽ��ʱ�����ϴ󣬿γ̵�ʱ��ֲ��Ϸ�ɢ\n\n�����������...");
     else
       printf("��ǰ���ҵ��Ͽ�ƽ���������ʱ��ֲ�����\n\n�����������...");


    getch();

    return 1;

 }


/**
 * ��������: ToStatTeacherRate
 * ��������: ��ʦ�οη���
 * �������: ��
 * �� �� ֵ: 1
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

   printf("��ʦ�ο�����������£�\n\n");
   printf("--------------------------------------\n");
   //printf("sum: %d\n",sum);
   for(int i=0;i<sum;i++)
   {
      if(done[i])
        continue;

     done[i]=1;
     credit=0; cnt=1;

     credit += strtod(gen_info[i].credit , paddr);//ͳ��һ����ʦ�οε���ѧ��

     sum_teacher += 1;//�൱����һ��һ���ж��ٸ���ʦ

     for(int j=i+1;j<sum;j++)
     {
       if(done[j])
         continue;
       if(!strcmp(gen_info[i].teacher , gen_info[j].teacher) )
       {
         done[j]=1;

         credit += strtod(gen_info[j].credit , paddr);//ͳ��һ����ʦ�οε���ѧ��
         cnt++;//ͳ��һ����ʦ���ο�����
       }
     }
     sum_credit += credit;//ͳ��������ʦ��ѧ��
     printf("--------------------------------------\n");
     if(16*credit > 88)
     printf("\n�������ý�ʦ��ѧ������� ������\n\n");
     else if(16*credit < 24)
     printf("\n�������ý�ʦ���ο�ʱ���� ������\n\n");

     printf("No.%d\n",sum_teacher);
     printf("��ʦ������      %s\n",gen_info[i].teacher);
     printf("ְ�ƣ�          %s\n",gen_info[i].title);
     printf("�ο�����:       %d\n",cnt);
     printf("���ο�ѧʱ��   %.0f\n",16*credit);
     printf("--------------------------------------\n\n");

   }

   printf("�ܽ᣺\n\n��ѧ��һ����%dλ��ʦ�ο�,����ƽ��ÿλ��ʦ����%.3f�ſ�,ÿλ��ʦƽ���ο�ѧʱΪ%.3f\n\n\n",sum_teacher,(1.0*sum)/(1.0*sum_teacher),(16*sum_credit)/(1.0*sum_teacher));
  if((16*sum_credit)/(1.0*sum_teacher)>88 )
  {
    printf("  ��ʦ��ƽ���ο�ѧʱ����,Ӧ�ö�������ʦ,�ֵ���ѧ����!\n");
  }
  else if((16*sum_credit)/(1.0*sum_teacher)<24)
  {
    printf("  ��ʦ��ƽ���ο�ѧʱ����,�˸�����,Ӧ�����ӽ�ѧ����!\n");
  }
  else
    printf("  ��ʦ��ƽ���ο�ѧʱ����,��ѧ������Ժ���!\n");


  printf("\n\n�����������...");
  getch();

    return 1;

}


/**
 * ��������: MakeClassno
 * ��������: ���ɰ���ַ���
 * �������: ��š� �����ŵ��ַ����׵�ַ
 * �� �� ֵ: 1
 *
 */
int MakeClassno(int i,char s[])
{
  switch (i)
  {
    case 1: strcpy(s,"�����1701");break;
    case 2: strcpy(s,"�����1702");break;
    case 3: strcpy(s,"�����1703");break;
    case 4: strcpy(s,"�����1704");break;
    case 5: strcpy(s,"�����1705");break;
    case 6: strcpy(s,"�����1706");break;
    case 7: strcpy(s,"�����1707");break;
    case 8: strcpy(s,"�����1708");break;
    case 9: strcpy(s,"�����1709");break;
    case 10: strcpy(s,"�����1710");break;
    case 11: strcpy(s,"�����1711");break;
    case 12: strcpy(s,"�����1712");break;
    case 13: strcpy(s,"�����1713");break;
    case 14: strcpy(s,"�����У��17");break;
    case 15: strcpy(s,"�����׿��17");break;
    case 16: strcpy(s,"�����1601");break;
    case 18:strcpy(s,"�����1602");break;
    case 19:strcpy(s,"�����1603");break;
    case 20:strcpy(s,"�����1604");break;
    case 21: strcpy(s,"�����1605");break;
    case 22: strcpy(s,"�����1606");break;
    case 23: strcpy(s,"�����1607");break;
    case 24: strcpy(s,"�����1608");break;
    case 25: strcpy(s,"�����1609");break;
    case 26: strcpy(s,"�����1610");break;
    case 27: strcpy(s,"�����ACM16");break;
    case 28: strcpy(s,"�����׿��16");break;
    case 29: strcpy(s,"������16");break;
    case 30: strcpy(s,"�Ű�1601");break;
    case 31: strcpy(s,"�Ű�1602");break;
    case 32: strcpy(s,"�Ű�1603");break;
    case 33: strcpy(s,"�����1501");break;
    case 34:strcpy(s,"�����1502");break;
    case 35:strcpy(s,"�����1503");break;
    case 36:strcpy(s,"�����1504");break;
    case 37: strcpy(s,"�����1505");break;
    case 38: strcpy(s,"�����1506");break;
    case 39: strcpy(s,"�����1507");break;
    case 40: strcpy(s,"�����1508");break;
    case 41: strcpy(s,"�����1509");break;
    case 42: strcpy(s,"�����1510");break;
    case 43: strcpy(s,"�����ACM15");break;
    case 44: strcpy(s,"�����׿��15");break;
    case 45: strcpy(s,"������15");break;
    case 46: strcpy(s,"�Ű�1501");break;
    case 47: strcpy(s,"�Ű�1502");break;
    case 48: strcpy(s,"�Ű�1503");break;
    case 49: strcpy(s,"�����У��16");break;
  }

  return 1;
}

/**
 * ��������: ToStatClassnoRate
 * ��������: �༶�Ͽη���
 * �������: ��
 * �� �� ֵ: 1
 *
 */
int ToStatClassnoRate(void)
{
   int sum_lesson=0;//���а༶һ�����˶��ٽڿ�
   int sum_course=0;//���а༶һ�����˶����ſ�
   int cnt_lesson=0,cnt_course=0;
   int n=les_classno.size();
   int sum_class=0;
   char classno[25];
   double classno_dt=0.0;//һ���༶��ƽ���Ͽε�ʱ������
   double dt_sum=0.0; //�ܵ�ʱ����
   int peri[6];//����ÿ���༶ÿ��ʱ��εĿ�������
   int sum_peri[6];
   memset(sum_peri,0,sizeof sum_peri);
   printf("�༶�Ͽη������£�\n\n");


for(int j=1;j<=49;j++)
{
  MakeClassno(j,classno);
  cnt_lesson=0,cnt_course=0;//һ���༶�Ŀγ̺Ϳ�����
  memset(peri,0,sizeof peri);
  std::vector<int>dt;
  for(int i=0;i<n;i++)
  {

    if(strstr(les_classno[i].classno,classno)==NULL)
       continue;

    LESSON* p=les_classno[i].lesson;
    while(p!=NULL)//���γ̱���ͳ��
    {
      cnt_course++;
      cnt_lesson += (p->to) - (p->from) +1;
      peri[p->period -1] += (p->to) - (p->from) +1 ;//ͳ��һ���༶�Ͽ��ڸ���ʱ�εķֲ�

      for(int k=p->from;k<=p->to;k++)//����ƽ�����
         dt.push_back(TimestrToNum(k,p->day,p->period));

      p=p->classno_next;
    }
  }
  if(cnt_course==0)//û��¼��ð༶�Ŀγ̣�����ӡ��Ϣ
   continue;

  dt_sum += (classno_dt=AverageDx(dt)) ;//���ڼ����ܵ�ƽ��ʱ����
  for(int i=0;i<6;i++) sum_peri[i]+=peri[i];//����ͳ���ܵ�ʱ��ֲ�
  printf("-----------------------------------------------\n");
  if(cnt_lesson>=350)
    printf("��������ǰ�༶��ҵѹ�����󣡣���\n\n");
  else if(cnt_lesson<100)
    printf("��������ǰ�༶�γ�̫��,Ӧ�ʵ�����ѧϰ���ݣ�����\n\n");
  if(classno_dt>5)
    printf("��������ǰ�༶�Ŀ���ƽ��ʱ�������󣬿γ̷ֲ�ϡ�� ������\n\n");

  printf("�༶�� %s\n\n",classno);
  printf("�Ͽ�ʱ�ηֲ���\n\n");
  printf("         1-2�ڣ�  %d   %.2f%%\n\n",peri[0],100.0*peri[0]/(1.0*cnt_lesson));
  printf("         3-4�ڣ�  %d   %.2f%%\n\n",peri[1],100.0*peri[1]/(1.0*cnt_lesson));
  printf("         5-6�ڣ�  %d   %.2f%%\n\n",peri[2],100.0*peri[2]/(1.0*cnt_lesson));
  printf("         7-8�ڣ�  %d   %.2f%%\n\n",peri[3],100.0*peri[3]/(1.0*cnt_lesson));
  printf("         9-10�ڣ� %d   %.2f%%\n\n",peri[4],100.0*peri[4]/(1.0*cnt_lesson));
  printf("         11-12�ڣ�%d   %.2f%%\n\n\n",peri[5],100.0*peri[5]/(1.0*cnt_lesson));
  printf("�ܹ��Ͽογ���:  %d  \n\n",cnt_course);
  printf("�ܹ��Ͽν�����   %d   \n\n",2*cnt_lesson);
  printf("ƽ���Ͽμ����   %.3f (��)\n\n",classno_dt);
  printf("-----------------------------------------------\n");

  sum_lesson += cnt_lesson;
  sum_course += cnt_course;
  sum_class++;
  dt.clear();
}
// printf("class_sum:%d\n",sum_class);

   double everage_course = 1.0*sum_course/(1.0*sum_class);
   double everage_lesson = 1.0*sum_lesson/(1.0*sum_class);
   printf("\n\n\n�ܽ᣺\n\n�༶�Ͽ�ʱ��ֲ����ܣ�\n\n");
   printf("         1-2�ڣ�  %d    %.2f%%\n\n",sum_peri[0],100.0*sum_peri[0]/(1.0*sum_lesson));
   printf("         3-4�ڣ�  %d    %.2f%%\n\n",sum_peri[1],100.0*sum_peri[1]/(1.0*sum_lesson));
   printf("         5-6�ڣ�  %d    %.2f%%\n\n",sum_peri[2],100.0*sum_peri[2]/(1.0*sum_lesson));
   printf("         7-8�ڣ�  %d    %.2f%%\n\n",sum_peri[3],100.0*sum_peri[3]/(1.0*sum_lesson));
   printf("         9-10�ڣ� %d    %.2f%%\n\n",sum_peri[4],100.0*sum_peri[4]/(1.0*sum_lesson));
   printf("         11-12�ڣ�%d    %.2f%%\n\n\n",sum_peri[5],100.0*sum_peri[5]/(1.0*sum_lesson));

   printf("\n\nƽ��ÿ���༶�Ͽογ���Ϊ %.3f \n\nƽ��ÿ���༶�Ͽν���Ϊ %.3f\n\n",everage_course,2*everage_lesson);
   printf("ƽ��ÿ���༶��ƽ���Ͽμ��Ϊ�� %.3f (��)\n\n", 1.0*dt_sum/(1.0*sum_class));

    if(1.0*dt_sum/(1.0*sum_class)>5)//ƽ��ʱ�����ж�
      printf("�༶��ƽ���Ͽ�ʱ���������ſηֲ�ϡ�裬Ӧ�ʵ�����\n\n");
    else
      printf("�༶��ƽ���Ͽ�ʱ�������У��ſηֲ���Ժ���\n\n");

   if(everage_lesson>350)
     printf("�༶��ƽ��������������,Ӧ���ʵ���С��ҵѹ����\n\n");
   else if(everage_lesson<100)
     printf("�༶��ƽ��������������,Ӧ���ʵ�����ѧϰ���ݣ�\n\n");
   else
    printf("�༶��ƽ�����������������,�γ̰�����Ժ���\n\n");

  printf("�����������...");
  getch();

   return 1;
}

/**
 * ��������: ToTraverseAll
 * ��������: �������п�����Ϣ
 * �������: ��
 * �� �� ֵ: 1
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
      printf("  �γ̣�%s\n",p->course);
      printf("  �ܴΣ�%d\n",p->week);
      printf("  ���ڣ�%d\n",p->day);
      printf("  ������%d\n",p->period);
      printf("  ��ѧ¥��%s\n",p->building);
      printf("  ���ң�%s\n",p->classroom);
      printf("  �༶��%s\n",p->classno);
      printf("-------------------------------------------------------------------\n");
      if((no%500) == 0)
      {
         printf("\n\n����������������һҳ...");
         getch();
         ClearScreenTotalInputArea();//����
      }

      p=p->room_next;
    }
  }

  printf("\n\n������ɣ������������...");
  getch();

  return 1;

}
