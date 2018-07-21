#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <cstring>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include<algorithm>

#include<vector>


#include <time.h>//��ȡϵͳʱ��
#include <unistd.h>   //��õ�ǰ����·��,�ı䵱ǰĿ¼�ĺ�������ͷ�ļ�

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*��Ļ����*/
#define SCR_COL 80             /*��Ļ����*/

//�Լ��ӵ�
typedef struct time {
    int week;           /**< ����*/
    int day;            /**<����*/
    int period;             /**< ������һ��һ��6��ڣ����ȡֵΪ1~6*/

    struct lesson *time_next;  /**< ָ��ͬһʱ�䲻ͬ���ҵ����еĿγ�*/


} TIME;
/**
�ռ��ͷ�ڵ�
*/
typedef struct place {
    char building[15];           /**< ��ѧ¥*/
    char classroom[10];             /**< ����*/

    struct lesson *room_next;  /**< ָ��ͬһ����Ҳ�ͬʱ������еĿ���*/


} PLACE;

/**
���ýṹ
 */
typedef struct lesson {
    int from,to;   /**<�ӵڼ��ܵ��ڼ���*/
    int  week;           /**< ����*/
    int  day;              /**<����*/
    int period;             /**< ������һ��һ��6��ڣ����ȡֵΪ1~6*/
    char building[15];
    char classroom[6];          /**< ����*/
    char classno[150];            /**< רҵ�༶*/
    char course[80];             /**< �γ���*/
    int No;                  /**< ���ڴ��еı��*/

    struct lesson *time_next;  /**< ָ��ͬһ����Ҳ�ͬʱ�����һ������*/
    struct lesson *room_next;   /**<ָ��ͬһʱ�䲻ͬ���ҵ���һ������*/
    struct lesson *time_pri;  /**< ָ��ͬһ����Ҳ�ͬʱ�����һ������*/
    struct lesson *room_pri;   /**<ָ��ͬһʱ�䲻ͬ���ҵ���һ������*/


    struct lesson *classno_next;  /**< ָ��ͬһ�༶����һ���γ�*/
    struct lesson *classno_pri;   /**< ָ��ͬһ�༶����һ���γ�*/
    struct lesson *course_next;   /**< ָ��ͬһ�γ̵���һ������*/
    struct lesson *course_pri;    /**< ָ��ͬһ�γ̵���һ������*/


    struct time *lesson_time ; /**<ָ��ʱ���ͷ*/
    struct place *lesson_place ;/**<ָ��ռ��ͷ*/
} LESSON;
/**
�ۺ���Ϣ�ṹ
*/
typedef struct info {

    char course[100];  /**<�γ���*/
    char time[10];    /**<ѧʱ*/
    char credit[5];  /**<ѧ��*/
    char title[10];  /**<��ʦְ��*/
    char teacher[100];/**<��ʦ����*/
    char classno[150];   /**<רҵ�༶*/
    char  extra[81];  /**<��ע*/
} INFO;
/**
�༶��������ͷ���ݽṹ
*/
typedef struct classno {

    char classno[150];   /**< רҵ�༶*/
    LESSON* lesson;  /**<ָ����õ�ָ��*/

} CLASSNO;

/**
�γ̲������Ľṹ
*/
typedef struct course {

    char course[80];  /**< �γ���*/
    LESSON* lesson;  /**<ָ����õ�ָ��*/

} COURSE;


extern TIME les_time[845];//ʱ���ͷ
extern PLACE les_place[260];//�ռ��ͷ
extern bool readed[845*260];//�ڲ�ѯ�����б�Ǵ˿����Ƿ��Ѷ�
extern std::vector<INFO> gen_info ;//�����ۺ���Ϣ
extern std::vector<CLASSNO> les_classno;//רҵ�༶������
extern std::vector<COURSE> les_course;//�γ̲�����
extern std::vector<int>find;//ɾ�������������������������Ҫɾ��������Ԫ�ص��±��vector
extern  int lesson_sum;//��������еĽڵ����
extern CONSOLE_CURSOR_INFO lpCur;  //�洢�����Ϣ



/**
 *��Ļ������Ϣ�������ṹ
 */
typedef struct layer_node {
    char LayerNo;            /**< �������ڲ���*/
    SMALL_RECT rcArea;       /**< ����������������*/
    CHAR_INFO *pContent;     /**< �������������ַ���Ԫԭ��Ϣ�洢������*/
    char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
    struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
 *��ǩ���ṹ
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
    COORD *pLoc;           /**< ��ǩ��λ�����׵�ַ*/
    int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
 *�����ṹ
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
    char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
    char *pTag;            /**< ������������׵�ַ*/
    int num;               /**< ��������*/
} HOT_AREA;

extern LAYER_NODE *gp_top_layer ;               /*����������Ϣ����ͷ*/

extern char *gp_sys_name ;    /*ϵͳ����*/
extern char *ga_main_menu[] ;         /*ϵͳ���˵���*/
extern char *ga_sub_menu[] ;        /*ϵͳ�Ӳ˵���*/



extern int ga_sub_menu_count[] ;  /*�����˵������Ӳ˵��ĸ���*/
extern int gi_sel_menu ;                        /*��ѡ�е����˵����,��ʼΪ1*/
extern int gi_sel_sub_menu ;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

extern CHAR_INFO *gp_buff_menubar_info ;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
extern CHAR_INFO *gp_buff_stateBar_info ;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

extern char *gp_scr_att ;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/

extern char gc_sys_state ;   /*��������ϵͳ״̬���ַ�*/


extern HANDLE gh_std_out;          /*��׼����豸���*/
extern HANDLE gh_std_in;           /*��׼�����豸���*/



void InitInterface(void);                 /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopPrompt(int num);                        /*��ʾ��������*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(void);                  /*ϵͳ����ģ���ѡ�������*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/
void CloseSys(void);                  /*�˳�ϵͳ*/
BOOL ShowModule(char **pString, int n);

BOOL LoadData(void);           /*���ݼ���*/
BOOL SaveData(void);           /*��������*/
BOOL BackupData(void);         /*��������*/
BOOL RestoreData(void);        /*�ָ�����*/
BOOL ExitSys(void);            /*�˳�ϵͳ*/
BOOL HelpTopic(void);          /*��������*/
BOOL About(void);          /*����ϵͳ*/

BOOL MaintainLessonInfo(void);    /*ά��������Ϣ*/
BOOL MaintainCourseInfo(void);   /*ά���γ���Ϣ*/
BOOL MaintainTeacherInfo(void);   /*ά����ʦ��Ϣ*/
BOOL MaintainClassnoInfo(void);    /*ά���༶��Ϣ*/
BOOL MaintainChargeInfo(void); /*ά��ѧ���ɷ���Ϣ*/

BOOL QueryCourseByTeacher(void);       /*ͨ����ʦ��ѯ�γ�*/
BOOL QueryLessonByClassno(void);      /*���༶��������*/
BOOL QueryLessonByTimeAndPlace(void);      /*�����Ͽε�ʱ��ص��������*/
BOOL QueryLessonByCourse(void);       /*���γ̼�������*/
BOOL QuerySpareClassroom(void);    /*�ռ���Ҽ���*/

BOOL StatClassroomRate(void);       /*���������ʷ���*/
BOOL StatTeacherRate(void);        /*��ʦ�οη���*/
BOOL StatClassnoRate(void);         /*�༶�Ͽη���*/
BOOL TraverseAll(void);       /*��ʱ��˳�����������Ϣ*/



//�Լ��¼ӵĹ��ܺ���

int  PlacestrToNum(char s1[] , char s2[]);//�ص��ϣ
int TimestrToNum(int week , int day , int period);//ʱ���ϣ
int LessonInsert(int placei,int timei,LESSON* temp);//������������
int  ClassnoInsert(LESSON* temp);//�༶��������
int CourseInsert(LESSON* temp);//�γ���������
int ReadLesson(FILE *fp);//�ӿ����ļ���������
int Init(void);//��ͷ��ʼ��
int SearchByCourse(char s[]);//���ݿγ̲�ѯ
int SearchByClassno(char  s[]);//���ݰ�� ��ѯ
int SearchByTime(int  week,int  day, int  period );//�����Ͽ�ʱ���ѯ
int SearchByPlace(char building[] , char classroom[]);//�����Ͽεص��ѯ
int ReadGeneralInfo(FILE * fp);//��������Ϣ��teacher��أ�
int SearchTeacherInfo(char s[]);//��ѯ��ʦ��Ϣ
int ToSaveData(FILE* fp1,FILE* fp2);//������ָ�����ļ��б�����Ϣ
void SpaceToUnderline(char*s);//�ѿո����»���
void AddBackslash(char*s) ;//���»��߱��˫�»���
void GetBackupFilename(char *dir1, char* dir2 );//�õ�����·���ı����ļ���
int ToBackup(char* filename1,char* filename2);//��ָ�����ļ��б��汸���ļ�
void ClearScreenTotalInputArea(void);//���������˵�һ�У�
int DestroyLesson(void);//����ڴ������еĿγ���Ϣ
int DestroyOtherVectorInfo(void);//���������vector�������Ϣ
int DeleteLesson(int timei, int placei);//ɾ��һ������ʱ������ص�Ŀ���
int ToInsertLesson(void);//�ڿ���̨�ֶ�����һ�ڿ�
int ToDeleteLesson(void);//�ڿ���̨�ֶ�ɾ��һ�ڿ�
int ReloadData(void);//�������������Ϣ
int ToModifyLesson(void);//�޸Ŀ�����Ϣ
int ToInsertCourse(void);//����γ���Ϣ
int ToFindGenInfoByCourse(char s[]);//���ۺ���Ϣ��ͨ���γ̹ؼ��ּ�����Ϣ����������vector���͵�find��
int ToDeleteCourse(void);//ɾ���γ���Ϣ
int ToModifyCourse(void);//�޸Ŀγ���Ϣ
int ToInsertTeacher(void);//�����µĽ�ʦ
int ToDeleteTeacher(void);//ɾ����ʦ
int ToModifyTeacher(void);//�޸Ľ�ʦ��Ϣ
void LessonFileForm(void);//����Ļ���lesson�����ļ��ĸ�ʽ��Ϣ
int  ToQueryCourseByTeacher(void);//ͨ����ʦ������ѯ�γ���Ϣ
int ToQueryLessonByClassno(void);//ͨ���༶��ѯ�γ���Ϣ
int SearchByTimeAndPlace(int timei,int placei);//ͨ��ʱ��ռ���ҿ���
int ToQueryLessonByTimeAndPlace(void);//ͨ��ʱ��ռ�������ò���������ʾ��Ϣ
int SearchByCourse(char s[]);//ͨ���γ���s��������
int ToQueryLessonByCourse(void);//ͨ���γ����������ò���������ʾ��Ϣ
int ToQuerySpareClassroom(void);//���н��Ҳ�ѯ
int ToStatClassroomRate(void);//���������ʷ���
int ToStatTeacherRate(void);//��ʦ�οη���
int ToStatClassnoRate(void);//�༶�Ͽη���
int MakeClassno(int i,char s[]);//����רҵ���
int ToTraverseAll(void);//��ʱ���Ⱥ�˳��������е���Ϣ
double AverageDx(std::vector<int> v);//���������е�����ƽ�����


#endif /**< TYPE_H_INCLUDED*/
