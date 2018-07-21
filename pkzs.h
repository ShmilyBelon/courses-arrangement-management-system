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


#include <time.h>//获取系统时间
#include <unistd.h>   //获得当前工作路径,改变当前目录的函数所在头文件

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*屏幕行数*/
#define SCR_COL 80             /*屏幕列数*/

typedef struct time {
    int week;           /**< 周数*/
    int day;            /**<星期*/
    int period;             /**< 节数，一天一共6大节，因此取值为1~6*/

    struct lesson *time_next;  /**< 指向同一时间不同教室的所有的课程*/


} TIME;
/**
空间表头节点
*/
typedef struct place {
    char building[15];           /**< 教学楼*/
    char classroom[10];             /**< 教室*/

    struct lesson *room_next;  /**< 指向同一间教室不同时间的所有的课堂*/


} PLACE;

/**
课堂结构
 */
typedef struct lesson {
    int from,to;   /**<从第几周到第几周*/
    int  week;           /**< 周数*/
    int  day;              /**<星期*/
    int period;             /**< 节数，一天一共6大节，因此取值为1~6*/
    char building[15];
    char classroom[6];          /**< 教室*/
    char classno[150];            /**< 专业班级*/
    char course[80];             /**< 课程名*/
    int No;                  /**< 在内存中的编号*/

    struct lesson *time_next;  /**< 指向同一间教室不同时间的下一个课堂*/
    struct lesson *room_next;   /**<指向同一时间不同教室的下一个课堂*/
    struct lesson *time_pri;  /**< 指向同一间教室不同时间的上一个课堂*/
    struct lesson *room_pri;   /**<指向同一时间不同教室的上一个课堂*/


    struct lesson *classno_next;  /**< 指向同一班级的下一个课程*/
    struct lesson *classno_pri;   /**< 指向同一班级的上一个课程*/
    struct lesson *course_next;   /**< 指向同一课程的下一个课堂*/
    struct lesson *course_pri;    /**< 指向同一课程的上一个课堂*/


    struct time *lesson_time ; /**<指向时间表头*/
    struct place *lesson_place ;/**<指向空间表头*/
} LESSON;
/**
综合信息结构
*/
typedef struct info {

    char course[100];  /**<课程名*/
    char time[10];    /**<学时*/
    char credit[5];  /**<学分*/
    char title[10];  /**<教师职称*/
    char teacher[100];/**<教师姓名*/
    char classno[150];   /**<专业班级*/
    char  extra[81];  /**<备注*/
} INFO;
/**
班级查找链表头数据结构
*/
typedef struct classno {

    char classno[150];              /**< 专业班级*/
    LESSON* lesson;  /**<指向课堂的指针*/

} CLASSNO;

/**
课程查找链的结构
*/
typedef struct course {

    char course[80];
                /**< 课程名*/
    LESSON* lesson;  /**<指向课堂的指针*/

} COURSE;

TIME les_time[845]; //时间表头
PLACE les_place[260];//空间表头
bool readed[845*260];//在查询函数中标记此课堂是否已读
std::vector<INFO> gen_info;//储存综合信息
std::vector<CLASSNO> les_classno;//专业班级查找链
std::vector<COURSE> les_course;//课程查找链
std::vector<int>find;//删除函数中用来储存遍历过程中要删除的数据元素的下标的vector
int lesson_sum=0;//当前课程总数
CONSOLE_CURSOR_INFO lpCur;  //存储光标信息






/**
 *屏幕窗口信息链结点结点结构
 */
typedef struct layer_node {
    char LayerNo;            /**< 弹出窗口层数*/
    SMALL_RECT rcArea;       /**< 弹出窗口区域坐标*/
    CHAR_INFO *pContent;     /**< 弹出窗口区域字符单元原信息存储缓冲区*/
    char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
    struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
 *标签束结构
 */
typedef struct labe1_bundle {
    char **ppLabel;        /**< 标签字符串数组首地址*/
    COORD *pLoc;           /**< 标签定位数组首地址*/
    int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
 *热区结构
 */
typedef struct hot_area {
    SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
    char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
    char *pTag;            /**< 热区序号数组首地址*/
    int num;               /**< 热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/


char *gp_sys_name = "排课评估与分析助手";    /*系统名称*/


char *ga_main_menu[] = {"文件(F)",             /*系统主菜单名*/
    	                "数据维护(M)",
                        "数据查询(Q)",
                        "数据统计(S)",
                        "帮助(H)"
                       };

char *ga_sub_menu[] = {"[S] 数据保存",          /*系统子菜单名*/
                       "[B] 数据备份",
                       "[R] 数据恢复",
                       "[X] 退出    Alt+X",
                       "[S] 课堂信息",
                       "[T] 课程信息",
                       "",           /*空串用来在弹出菜单中分隔子菜单项，下同*/
                       "[D] 教师信息",
                       "[P] 教室信息",
                       "[C] 班级信息",
                       "[S] 按教师检索课程",
                       "[T] 按班级检索课堂",
                       "",
                       "[D] 按教室、时间查询课堂",
                       "[P] 按课程检索课堂",
                       "[C] 空闲教室查询",
                       "[I] 教室利用与能效分析",
                       "[T] 教师任课分析",
                       "[C] 班级上课分析",
                       "[U] 遍历与检索",
                       "[T] 帮助主题",
                       "",
                       "[A] 关于..."
                      };

int ga_sub_menu_count[] = {4, 6, 6, 4, 3};  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/
char gc_sys_state = '\0';   /*用来保存系统状态的字符*/


HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/



void InitInterface(void);                 /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopPrompt(int num);                        /*显示弹出窗口*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealConInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(void);                  /*系统功能模块的选择和运行*/
BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/
void CloseSys(void);                  /*退出系统*/
BOOL ShowModule(char **pString, int n);


//接口函数
BOOL LoadData(void);           /*数据加载*/
BOOL SaveData(void);           /*保存数据*/
BOOL BackupData(void);         /*备份数据*/
BOOL RestoreData(void);        /*恢复数据*/
BOOL ExitSys(void);            /*退出系统*/
BOOL HelpTopic(void);          /*帮助主体*/
BOOL About(void);          /*关于系统*/

BOOL MaintainLessonInfo(void);    /*课堂信息维护*/
BOOL MaintainCourseInfo(void);   /*维护课程信息*/
BOOL MaintainTeacherInfo(void);   /*维护教师楼信息*/
BOOL MaintainClassroomInfo(void);    /*维护教室信息*/
BOOL MaintainClassnoInfo(void); /*维护班级信息*/

BOOL QueryCourseByTeacher(void);       /*通过教师此查询课程*/
BOOL QueryLessonByClassno(void);      /*按班级检索课堂*/
BOOL QueryLessonByTimeAndPlace(void);   /*根据上课的时间地点检索课堂*/
BOOL QueryLessonByCourse(void);       /*按课程检索课堂*/
BOOL QuerySpareClassroom(void);    /*空间教室检索*/

BOOL StatClassroomRate(void);       /*教师利用率分析*/
BOOL StatTeacherRate(void);        /*教师任课分析*/
BOOL StatClassnoRate(void);         /*班级上课分析*/
BOOL TraverseAll(void);       /*按时间顺序遍历所有信息*/




//自己新加的功能函数

int  PlacestrToNum(char s1[] , char s2[]);//地点哈希
int TimestrToNum(int week , int day , int period);//时间哈希
int LessonInsert(int placei,int timei,LESSON* temp);//课堂引索插入
int  ClassnoInsert(LESSON* temp);//班级引索插入
int CourseInsert(LESSON* temp);//课程引索插入
int ReadLesson(FILE *fp);//从课堂文件读入数据
int Init(void);//表头初始化
int SearchByCourse(char s[]);//根据课程查询
int SearchByClassno(char  s[]);//根据班号 查询
int SearchByTime(int  week,int  day, int  period );//根据上课时间查询
int SearchByPlace(char building[] , char classroom[]);//根据上课地点查询
int ReadGeneralInfo(FILE * fp);//读常规信息（teacher相关）
int SearchTeacherInfo(char s[]);//查询教师信息
int ToSaveData(FILE* fp1,FILE* fp2);//用来向指定的文件中保存信息
void SpaceToUnderline(char*s);//把空格变成下划线
void AddBackslash(char*s) ;//单下划线变成双下划线
void GetBackupFilename(char *dir1, char* dir2 );//得到包含路径的备份文件名
int ToBackup(char* filename1,char* filename2);//向指定的文件中保存备份文件
void ClearScreenTotalInputArea(void);//清屏（除了第一行）
int DestroyLesson(void);//清除内存中所有的课程信息
int DestroyOtherVectorInfo(void);//清除所有用vector储存的信息
int DeleteLesson(int timei, int placei);//删除一个给定时间给定地点的课堂
int ToInsertLesson(void);//在控制台手动插入一节课
int ToDeleteLesson(void);//在控制台手动删除一节课
int ReloadData(void);//重新载入课堂信息
int ToModifyLesson(void);//修改课堂信息
int ToInsertCourse(void);//插入课程信息
int ToFindGenInfoByCourse(char s[]);//在综合信息中通过课程关键字检索信息，并储存在vector类型的find中
int ToDeleteCourse(void);//删除课程信息
int ToModifyCourse(void);//修改课程信息
int ToInsertTeacher(void);//插入新的教师
int ToFindGenInfoByTeacher(char s[]);//在综合信息中通过教师关键字检索信息，并储存在vector类型的find中
int ToDeleteTeacher(void);//删除教师
int ToModifyTeacher(void);//修改教师信息
void LessonFileForm(void);//向屏幕输出lesson数据文件的格式信息
int  ToQueryCourseByTeacher(void);//通过教师姓名查询课程信息
int ToQueryLessonByClassno(void);//通过班级查询课程信息
int SearchByTimeAndPlace(int timei,int placei);//通过时间空间查找课堂
int ToQueryLessonByTimeAndPlace(void);//通过时间空间检索课堂并输出相关提示信息
int SearchByCourse(char s[]);//通过课程名s检索课堂
int ToQueryLessonByCourse(void);//通过课程名检索课堂并输出相关提示信息
int ToQuerySpareClassroom(void);//空闲教室查询
int ToStatClassroomRate(void);//教室利用率分析
int ToStatTeacherRate(void);//教师任课分析
int ToStatClassnoRate(void);//班级上课分析
int MakeClassno(int i,char s[]);//生成专业班号
int ToTraverseAll(void);//按时间先后顺序遍历所有的信息
double AverageDx(std::vector<int> v);//计算数组中的数的平均间隔

#endif /**< TYPE_H_INCLUDED*/
