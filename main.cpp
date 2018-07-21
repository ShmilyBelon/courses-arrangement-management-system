#include "pkzs.h"

unsigned long ul;

int main()
{
    COORD size = {SCR_COL, SCR_ROW};              /*���ڻ�������С*/

    gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
    gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/

    SetConsoleTitle(gp_sys_name);                 /*���ô��ڱ���*/
    SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С80*25*/

    LoadData();                   /*���ݼ���*/
    InitInterface();          /*�����ʼ��*/
    RunSys();             /*ϵͳ����ģ���ѡ������*/
    CloseSys();            /*�˳�ϵͳ*/

    return 0;
}

/**
 * ��������: LoadData
 * ��������: װ������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, ��ȷ����TRUE�����󷵻�FALSE
 *
 * ����˵��: Ϊ���ܹ���ͳһ�ķ�ʽ���ø����ܺ���, ����Щ���ܺ�����ԭ����Ϊ
 *           һ��, ���޲����ҷ���ֵΪBOOL. ����ֵΪFALSEʱ, ������������.
 */
BOOL LoadData()
{
    int bRet=1;
    Init();
    FILE* fp=fopen("data\\lesson_to_read.txt","r+");
    if(fp==NULL)
    {
        printf("data\\lesson_to_read.txt��ʧ�ܣ�\n");
        bRet=0;
    }
    int res1=ReadLesson(fp);
    if(res1==-1)
    {
        printf("�γ����ݼ���ʧ�ܣ�\n");
        bRet=0;
    }

    else
        printf("�γ����ݼ��سɹ���\n");


    fclose(fp);

    fp=fopen("data\\gen_info.txt","r+");
    if(fp==NULL)
    {
        printf("data\\gen_info.txt��ʧ�ܣ�\n");
        bRet= 0;
    }
    int res2=ReadGeneralInfo(fp);
    if(res2!=-1)
        printf("��ʦ��Ϣ���سɹ���\n�༶��Ϣ���سɹ���\n������Ϣ���سɹ�!\n\n�����������...\n");
    else
    {
        printf("��ʦ����Ϣ����ʧ�ܣ��������ݲ�������\n\n�����������...\n");
        bRet=0;

    }


    getchar();

    fclose(fp);


    return bRet;
}




/**
 * ��������: InitInterface
 * ��������: ��ʼ������.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void InitInterface()
{
    WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
               | BACKGROUND_BLUE;  /*��ɫǰ������ɫ����*/

    SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

    ClearScreen();  /* ����*/

    /*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
    gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
    gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
    gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
    gp_top_layer->rcArea.Top = 0;
    gp_top_layer->rcArea.Right = SCR_COL - 1;
    gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
    gp_top_layer->pContent = NULL;
    gp_top_layer->pScrAtt = gp_scr_att;
    gp_top_layer->next = NULL;

    ShowMenu();     /*��ʾ�˵���*/
    ShowState();    /*��ʾ״̬��*/

    return;
}

/**
 * ��������: ClearScreen
 * ��������: �����Ļ��Ϣ.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void ClearScreen(void)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD home = {0, 0};
    unsigned long size;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );/*ȡ��Ļ��������Ϣ*/
    size =  bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

    /*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
    FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &ul);

    /*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
    FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &ul);

    return;
}

/**
 * ��������: ShowMenu
 * ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void ShowMenu()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    CONSOLE_CURSOR_INFO lpCur;
    COORD size;
    COORD pos = {0, 0};
    int i, j;
    int PosA = 2, PosB;
    char ch;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SetConsoleCursorPosition(gh_std_out, pos);
    for (i=0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
    {
        printf("  %s  ", ga_main_menu[i]);
    }

    GetConsoleCursorInfo(gh_std_out, &lpCur);
    lpCur.bVisible = FALSE;
    SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

    /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
    gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0} ;

    /*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
    ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    /*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
    for (i=0; i<size.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
    COORD endPos = {0, 1};
    SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

    /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
    i = 0;
    do
    {
        PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
        for (j=PosA; j<PosB; j++)
        {
            gp_scr_att[j] |= (i+1) << 2; /*���ò˵��������ַ���Ԫ������ֵ*/
        }
        PosA = PosB + 4;
        i++;
    } while (i<5);

    TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

    return;
}

/**
 * ��������: ShowState
 * ��������: ��ʾ״̬��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
 */
void ShowState()
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int i;

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;
    SMALL_RECT rcMenu ={0, bInfo.dwSize.Y-1, size.X-1, bInfo.dwSize.Y-1};

    if (gp_buff_stateBar_info == NULL)
    {
        gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
        ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
    }

    for (i=0; i<size.X; i++)
    {
        (gp_buff_stateBar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                                | BACKGROUND_RED;
/*
        ch = (char)((gp_buff_stateBar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_stateBar_info+i)->Attributes |= FOREGROUND_RED;
        }
*/
    }

    WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: TagMainMenu
 * ��������: ��ָ�����˵�������ѡ�б�־.
 * �������: num ѡ�е����˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void TagMainMenu(int num)
{
    CONSOLE_SCREEN_BUFFER_INFO bInfo;
    COORD size;
    COORD pos = {0, 0};
    int PosA = 2, PosB;
    char ch;
    int i;

    if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
    {
        PosA = 0;
        PosB = 0;
    }
    else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
    {
        for (i=1; i<num; i++)
        {
            PosA += strlen(ga_main_menu[i-1]) + 4;
        }
        PosB = PosA + strlen(ga_main_menu[num-1]);
    }

    GetConsoleScreenBufferInfo( gh_std_out, &bInfo );
    size.X = bInfo.dwSize.X;
    size.Y = 1;

    /*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
    for (i=0; i<PosA; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (gp_buff_menubar_info+i)->Char.AsciiChar;
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*��ѡ�в˵���������ǣ��ڵװ���*/
    for (i=PosA; i<PosB; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
                                               | FOREGROUND_RED;
    }

    /*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
    for (i=PosB; i<bInfo.dwSize.X; i++)
    {
        (gp_buff_menubar_info+i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
                                               | BACKGROUND_RED;
        ch = (char)((gp_buff_menubar_info+i)->Char.AsciiChar);
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            (gp_buff_menubar_info+i)->Attributes |= FOREGROUND_RED;
        }
    }

    /*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
    SMALL_RECT rcMenu ={0, 0, size.X-1, 0};
    WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

    return;
}

/**
 * ��������: CloseSys
 * ��������: �ر�ϵͳ.
 * �������: hd ����ͷָ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void CloseSys(void)
{

    ClearScreen();        /*����*/

    /*�ͷŴ�Ų˵�����״̬������Ϣ��̬�洢��*/
    free(gp_buff_menubar_info);
    free(gp_buff_stateBar_info);


    /*�رձ�׼���������豸���*/
    CloseHandle(gh_std_out);
    CloseHandle(gh_std_in);

    /*�����ڱ�������Ϊ���н���*/
    SetConsoleTitle("���н���");

    return;
}

/**
 * ��������: RunSys
 * ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void RunSys(void)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    BOOL bRet = TRUE;
    int i, loc, num;
    int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
    char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    while (bRet)
    {
        /*�ӿ���̨���뻺�����ж�һ����¼*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);

        if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
            cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
            if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
            {
                /* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
                 * cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
                 * gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
                 */
                if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
                }
            }
            else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
            {
                TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
            }

            if (inRec.Event.MouseEvent.dwButtonState
                == FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
                    {
                        PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
                    }
                    /*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
                    else if (gp_top_layer->LayerNo > 0)
                    {
                        PopOff();            /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                    }
                }
                else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
                {
                    if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
                    {
                        PopOff(); /*�رյ������Ӳ˵�*/
                        gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

                        /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
                        bRet = ExeFunction(gi_sel_menu, cAtt);
                    }
                }
            }
            else if (inRec.Event.MouseEvent.dwButtonState
                     == RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
            {
                if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
                 && inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
            asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

            /*ϵͳ��ݼ��Ĵ���*/
            if (vkc == 112) /*�������F1��*/
            {
                if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
                {
                    PopOff();            /*�رյ������Ӳ˵�*/
                    gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
                }
                bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
            }
            else if (inRec.Event.KeyEvent.dwControlKeyState
                     & (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
            { /*������������Alt��*/
                switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
                {
                    case 88:  /*Alt+X �˳�*/
                        if (gp_top_layer->LayerNo != 0)
                        {
                            PopOff();
                            gi_sel_sub_menu = 0;
                        }
                        bRet = ExeFunction(1,4);
                        break;
                    case 70:  /*Alt+F*/
                        PopMenu(1);
                        break;
                    case 77: /*Alt+M*/
                        PopMenu(2);
                        break;
                    case 81: /*Alt+Q*/
                        PopMenu(3);
                        break;
                    case 83: /*Alt+S*/
                        PopMenu(4);
                        break;
                    case 72: /*Alt+H*/
                        PopMenu(5);
                        break;
                }
            }
            else if (asc == 0) /*�������Ƽ��Ĵ���*/
            {
                if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
                {
                    switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu == 0)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu == 6)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            break;
                        case 40:
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else  /*�ѵ����Ӳ˵�ʱ*/
                {
                    for (loc=0,i=1; i<gi_sel_menu; i++)
                    {
                        loc += ga_sub_menu_count[i-1];
                    }  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                    switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
                    {
                        case 37:
                            gi_sel_menu--;
                            if (gi_sel_menu < 1)
                            {
                                gi_sel_menu = 5;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 38:
                            num = gi_sel_sub_menu - 1;
                            if (num < 1)
                            {
                                num = ga_sub_menu_count[gi_sel_menu-1];
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num--;
                            }
                            TagSubMenu(num);
                            break;
                        case 39:
                            gi_sel_menu++;
                            if (gi_sel_menu > 5)
                            {
                                gi_sel_menu = 1;
                            }
                            TagMainMenu(gi_sel_menu);
                            PopOff();
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                        case 40:
                            num = gi_sel_sub_menu + 1;
                            if (num > ga_sub_menu_count[gi_sel_menu-1])
                            {
                                num = 1;
                            }
                            if (strlen(ga_sub_menu[loc+num-1]) == 0)
                            {
                                num++;
                            }
                            TagSubMenu(num);
                            break;
                    }
                }
            }
            else if ((asc-vkc == 0) || (asc-vkc == 32)){  /*������ͨ��*/
                if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
                {
                    switch (vkc)
                    {
                        case 70: /*f��F*/
                            PopMenu(1);
                            break;
                        case 77: /*m��M*/
                            PopMenu(2);
                            break;
                        case 81: /*q��Q*/
                            PopMenu(3);
                            break;
                        case 83: /*s��S*/
                            PopMenu(4);
                            break;
                        case 72: /*h��H*/
                            PopMenu(5);
                            break;
                        case 13: /*�س�*/
                            PopMenu(gi_sel_menu);
                            TagSubMenu(1);
                            break;
                    }
                }
                else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
                {
                    if (vkc == 27) /*�������ESC��*/
                    {
                        PopOff();
                        gi_sel_sub_menu = 0;
                    }
                    else if(vkc == 13) /*������»س���*/
                    {
                        num = gi_sel_sub_menu;
                        PopOff();
                        gi_sel_sub_menu = 0;
                        bRet = ExeFunction(gi_sel_menu, num);
                    }
                    else /*������ͨ���Ĵ���*/
                    {
                        /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
                        for (loc=0,i=1; i<gi_sel_menu; i++)
                        {
                            loc += ga_sub_menu_count[i-1];
                        }

                        /*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
                        for (i=loc; i<loc+ga_sub_menu_count[gi_sel_menu-1]; i++)
                        {
                            if (strlen(ga_sub_menu[i])>0 && vkc==ga_sub_menu[i][1])
                            { /*���ƥ��ɹ�*/
                                PopOff();
                                gi_sel_sub_menu = 0;
                                bRet = ExeFunction(gi_sel_menu, i-loc+1);
                            }
                        }
                    }
                }
            }
        }
    }
}

void PopPrompt(int num)
{

}

/**
 * ��������: PopMenu
 * ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
 * �������: num ָ�������˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void PopMenu(int num)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh;
    int i, j, loc = 0;

    if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
    {
        if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
        {
            PopOff();
            gi_sel_sub_menu = 0;
        }
    }
    else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
    {
        return;
    }

    gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/
    TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/
    LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

    /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
    for (i=1; i<gi_sel_menu; i++)
    {
        loc += ga_sub_menu_count[i-1];
    }
    /*�������Ӳ˵������������ǩ���ṹ����*/
    labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
    labels.num = ga_sub_menu_count[gi_sel_menu-1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
    COORD aLoc[labels.num];/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
    for (i=0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
    {
        aLoc[i].X = rcPop.Left + 2;
        aLoc[i].Y = rcPop.Top + i + 1;
    }
    labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
    /*����������Ϣ*/
    areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
    SMALL_RECT aArea[areas.num];                    /*������������������λ��*/
    char aSort[areas.num];                      /*��������������������Ӧ���*/
    char aTag[areas.num];                         /*����������ÿ�������ı��*/
    for (i=0; i<areas.num; i++)
    {
        aArea[i].Left = rcPop.Left + 2;  /*������λ*/
        aArea[i].Top = rcPop.Top + i + 1;
        aArea[i].Right = rcPop.Right - 2;
        aArea[i].Bottom = aArea[i].Top;
        aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
        aTag[i] = i + 1;           /*������˳����*/
    }
    areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
    areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
    areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    PopUp(&rcPop, att, &labels, &areas);
    DrawBox(&rcPop);  /*���������ڻ��߿�*/
    pos.X = rcPop.Left + 2;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    { /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
        pCh = ga_sub_menu[loc+pos.Y-rcPop.Top-1];
        if (strlen(pCh)==0) /*����Ϊ0������Ϊ�մ�*/
        {   /*���Ȼ�����*/
            FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-3, pos, &ul);
            for (j=rcPop.Left+2; j<rcPop.Right-1; j++)
            {   /*ȡ���������ַ���Ԫ����������*/
                gp_scr_att[pos.Y*SCR_COL+j] &= 3; /*��λ��Ľ�������˵���λ*/
            }
        }

    }
    /*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
    pos.X = rcPop.Left + 3;
    att =  FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
    for (pos.Y=rcPop.Top+1; pos.Y<rcPop.Bottom; pos.Y++)
    {
        if (strlen(ga_sub_menu[loc+pos.Y-rcPop.Top-1])==0)
        {
            continue;  /*�����մ�*/
        }
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    return;
}

/**
 * ��������: PopUp
 * ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
 * �������: pRc ��������λ�����ݴ�ŵĵ�ַ
 *           att �������������ַ�����
 *           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
             pHotArea ����������������Ϣ��ŵĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 * ����˵��:
 */
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j, row;

    /*������������λ���ַ���Ԫ��Ϣ��ջ*/
    size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
    size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
    /*�����ŵ������������Ϣ�Ķ�̬�洢��*/
    nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
    nextLayer->next = gp_top_layer;
    nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
    nextLayer->rcArea = *pRc;
    nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y*sizeof(CHAR_INFO));
    nextLayer->pScrAtt = (char *)malloc(size.X*size.Y*sizeof(char));
    pCh = nextLayer->pScrAtt;
    /*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
    ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            *pCh = gp_scr_att[i*SCR_COL+j];
            pCh++;
        }
    }
    gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
    /*���õ������������ַ���������*/
    pos.X = pRc->Left;
    pos.Y = pRc->Top;
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {
        FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &ul);
        pos.Y++;
    }
    /*����ǩ���еı�ǩ�ַ������趨��λ�����*/
    for (i=0; i<pLabel->num; i++)
    {
        pCh = pLabel->ppLabel[i];
        if (strlen(pCh) != 0)
        {
            WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
                                        pLabel->pLoc[i], &ul);
        }
    }
    /*���õ������������ַ���Ԫ��������*/
    for (i=pRc->Top; i<=pRc->Bottom; i++)
    {   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
        for (j=pRc->Left; j<=pRc->Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = gp_top_layer->LayerNo;
        }
    }

    for (i=0; i<pHotArea->num; i++)
    {   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
        row = pHotArea->pArea[i].Top;
        for (j=pHotArea->pArea[i].Left; j<=pHotArea->pArea[i].Right; j++)
        {
            gp_scr_att[row*SCR_COL+j] |= (pHotArea->pSort[i] << 6)
                                    | (pHotArea->pTag[i] << 2);
        }
    }
    return;
}

/**
 * ��������: PopOff
 * ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
 * �������: ��
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void PopOff(void)
{
    LAYER_NODE *nextLayer;
    COORD size;
    COORD pos = {0, 0};
    char *pCh;
    int i, j;

    if ((gp_top_layer->next==NULL) || (gp_top_layer->pContent==NULL))
    {   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
        return;
    }
    nextLayer = gp_top_layer->next;
    /*�ָ�������������ԭ���*/
    size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
    size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
    WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
    /*�ָ��ַ���Ԫԭ����*/
    pCh = gp_top_layer->pScrAtt;
    for (i=gp_top_layer->rcArea.Top; i<=gp_top_layer->rcArea.Bottom; i++)
    {
        for (j=gp_top_layer->rcArea.Left; j<=gp_top_layer->rcArea.Right; j++)
        {
            gp_scr_att[i*SCR_COL+j] = *pCh;
            pCh++;
        }
    }
    free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
    free(gp_top_layer->pScrAtt);
    free(gp_top_layer);
    gp_top_layer = nextLayer;
    gi_sel_sub_menu = 0;
    return;
}

/**
 * ��������: DrawBox
 * ��������: ��ָ�����򻭱߿�.
 * �������: pRc �������λ����Ϣ�ĵ�ַ
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void DrawBox(SMALL_RECT *pRc)
{
    char chBox[] = {'+','-','|'};  /*�����õ��ַ�*/
    COORD pos = {pRc->Left, pRc->Top};  /*��λ����������Ͻ�*/

    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*��ѭ�����ϱ߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����Ͻ�*/
    for (pos.Y = pRc->Top+1; pos.Y < pRc->Bottom; pos.Y++)
    {   /*��ѭ�����߿�����ߺ��ұ���*/
        pos.X = pRc->Left;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
        pos.X = pRc->Right;
        WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &ul);
    }
    pos.X = pRc->Left;
    pos.Y = pRc->Bottom;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
    {   /*���±߿����*/
        WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &ul);
    }
    pos.X = pRc->Right;
    WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &ul);/*���߿����½�*/
    return;
}

/**
 * ��������: TagSubMenu
 * ��������: ��ָ���Ӳ˵�������ѡ�б��.
 * �������: num ѡ�е��Ӳ˵����
 * �������: ��
 * �� �� ֵ: ��
 *
 */
void TagSubMenu(int num)
{
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int width;

    LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
    if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom-rcPop.Top-1))
    {   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
        return;
    }

    pos.X = rcPop.Left + 2;
    width = rcPop.Right - rcPop.Left - 3;
    if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
    {
        pos.Y = rcPop.Top + gi_sel_sub_menu;
        att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
        pos.X += 1;
        att |=  FOREGROUND_RED;/*�׵׺���*/
        FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &ul);
    }
    /*���ƶ��Ӳ˵�������ѡ�б��*/
    pos.X = rcPop.Left + 2;
    pos.Y = rcPop.Top + num;
    att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    FillConsoleOutputAttribute(gh_std_out, att, width, pos, &ul);
    gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
    return;
}

/**
 * ��������: LocSubMenu
 * ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
 * �������: num ѡ�е����˵����
 * �������: rc �������λ����Ϣ�ĵ�ַ
 * �� �� ֵ: ��
 *
 */
void LocSubMenu(int num, SMALL_RECT *rc)
{
    int i, len, loc = 0;

    rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
    rc->Left = 1;
    for (i=1; i<num; i++)
    {   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
        rc->Left += strlen(ga_main_menu[i-1]) + 4;
        loc += ga_sub_menu_count[i-1];
    }
    rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
    for (i=1; i<ga_sub_menu_count[num-1]; i++)
    {   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
        len = strlen(ga_sub_menu[loc+i]);
        if (rc->Right < len)
        {
            rc->Right = len;
        }
    }
    rc->Right += rc->Left + 3;  /*����������ұ߽�*/
    rc->Bottom = rc->Top + ga_sub_menu_count[num-1] + 1;/*���������±ߵ��к�*/
    if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
    {
        len = rc->Right - SCR_COL + 1;
        rc->Left -= len;
        rc->Right = SCR_COL - 1;
    }
    return;
}

/**
 * ��������: DealInput
 * ��������: �ڵ�������������������, �ȴ�����Ӧ�û�����.
 * �������: pHotArea
 *           piHot ����������ŵĴ�ŵ�ַ, ��ָ�򽹵�������ŵ�ָ��
 * �������: piHot ����굥�������س���ո�ʱ���ص�ǰ�������
 * �� �� ֵ:
 *
 */
int DealInput(HOT_AREA *pHotArea, int *piHot)
{
    INPUT_RECORD inRec;
    DWORD res;
    COORD pos = {0, 0};
    int num, arrow, iRet = 0;
    int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
    char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

    SetHotPoint(pHotArea, *piHot);
    while (TRUE)
    {    /*ѭ��*/
        ReadConsoleInput(gh_std_in, &inRec, 1, &res);
        if ((inRec.EventType == MOUSE_EVENT) &&
            (inRec.Event.MouseEvent.dwButtonState
             == FROM_LEFT_1ST_BUTTON_PRESSED))
        {
            pos = inRec.Event.MouseEvent.dwMousePosition;
            cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
            cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
            cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

            if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
            {
                *piHot = cTag;
                SetHotPoint(pHotArea, *piHot);
                if (cSort == 0)
                {
                    iRet = 13;
                    break;
                }
            }
        }
        else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
        {
            vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
            asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
            if (asc == 0)
            {
                arrow = 0;
                switch (vkc)
                {  /*�����(���ϡ��ҡ���)�Ĵ���*/
                    case 37: arrow = 1; break;
                    case 38: arrow = 2; break;
                    case 39: arrow = 3; break;
                    case 40: arrow = 4; break;
                }
                if (arrow > 0)
                {
                    num = *piHot;
                    while (TRUE)
                    {
                        if (arrow < 3)
                        {
                            num--;
                        }
                        else
                        {
                            num++;
                        }
                        if ((num < 1) || (num > pHotArea->num) ||
                            ((arrow % 2) && (pHotArea->pArea[num-1].Top
                            == pHotArea->pArea[*piHot-1].Top)) || ((!(arrow % 2))
                            && (pHotArea->pArea[num-1].Top
                            != pHotArea->pArea[*piHot-1].Top)))
                        {
                            break;
                        }
                    }
                    if (num > 0 && num <= pHotArea->num)
                    {
                        *piHot = num;
                        SetHotPoint(pHotArea, *piHot);
                    }
                }
            }
            else if (vkc == 27)
            {  /*ESC��*/
                iRet = 27;
                break;
            }
            else if (vkc == 13 || vkc == 32)
            {  /*�س�����ո��ʾ���µ�ǰ��ť*/
                iRet = 13;
                break;
            }
        }
    }
    return iRet;
}

void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
    CONSOLE_CURSOR_INFO lpCur;
    COORD pos = {0, 0};
    WORD att1, att2;
    int i, width;

    att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
    att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    for (i=0; i<pHotArea->num; i++)
    {  /*����ť��������Ϊ�׵׺���*/
        pos.X = pHotArea->pArea[i].Left;
        pos.Y = pHotArea->pArea[i].Top;
        width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
        if (pHotArea->pSort[i] == 0)
        {  /*�����ǰ�ť��*/
            FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &ul);
        }
    }

    pos.X = pHotArea->pArea[iHot-1].Left;
    pos.Y = pHotArea->pArea[iHot-1].Top;
    width = pHotArea->pArea[iHot-1].Right - pHotArea->pArea[iHot-1].Left + 1;
    if (pHotArea->pSort[iHot-1] == 0)
    {  /*�����������ǰ�ť��*/
        FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &ul);
    }
    else if (pHotArea->pSort[iHot-1] == 1)
    {  /*�������������ı�����*/
        SetConsoleCursorPosition(gh_std_out, pos);
        GetConsoleCursorInfo(gh_std_out, &lpCur);
        lpCur.bVisible = TRUE;
        SetConsoleCursorInfo(gh_std_out, &lpCur);
    }
}

/**
 * ��������: ExeFunction
 * ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
 * �������: m ���˵����
 *           s �Ӳ˵����
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE �� FALSE
 *
 * ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
 */
BOOL ExeFunction(int m, int s)
{
    BOOL bRet = TRUE;
    /*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
    BOOL (*pFunction[ga_sub_menu_count[0]+ga_sub_menu_count[1]+ga_sub_menu_count[2]+ga_sub_menu_count[3]+ga_sub_menu_count[4]])(void);
    int i, loc;

    /*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
    pFunction[0] = SaveData;
    pFunction[1] = BackupData;
    pFunction[2] = RestoreData;
    pFunction[3] = ExitSys;
    pFunction[4] = MaintainLessonInfo;
    pFunction[5] = MaintainCourseInfo;
    pFunction[6] = NULL;
    pFunction[7] = MaintainTeacherInfo;
    pFunction[8] = MaintainClassroomInfo;
    pFunction[9] = MaintainClassnoInfo;
    pFunction[10] = QueryCourseByTeacher;
    pFunction[11] = QueryLessonByClassno;
    pFunction[12] = NULL;
    pFunction[13] = QueryLessonByTimeAndPlace;
    pFunction[14] = QueryLessonByCourse;
    pFunction[15] = QuerySpareClassroom;
    pFunction[16] = StatClassroomRate;
    pFunction[17] = StatTeacherRate;
    pFunction[18] = StatClassnoRate;
    pFunction[19] = TraverseAll;
    pFunction[20] = HelpTopic;
    pFunction[21] = NULL;
    pFunction[22] = About;

    for (i=1,loc=0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
    {
        loc += ga_sub_menu_count[i-1];
    }
    loc += s - 1;

    if (pFunction[loc] != NULL)
    {
        bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
    }

    return bRet;
}


/**
 * ��������: SaveData
 * ��������: �������ļ��б�������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL SaveData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    FILE* fp1=fopen("data\\lesson_to_save.txt","w+");
    FILE* fp2=fopen("data\\gen_info.txt","w+");
   /* FILE* fp3=fopen("data\\class.txt","w+");
    FILE* fp4=fopen("data\\.txt","w+");*/
    if(fp1==NULL || fp2==NULL)
    {
        MessageBox(NULL,"���ݱ���ʧ�ܣ������������ļ��𻵣�","ERROR!",MB_OK);
        return 0;
    }

    ToSaveData(fp1,fp2);
    MessageBox(NULL,"  ���ݱ�����ɣ�","SUCCESS!",MB_OK);


    return bRet;
}

/**
 * ��������: BackupData
 * ��������: �������ݱ����ļ�����������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL BackupData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݱ���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    char filename1[100];
    char filename2[100];
    GetBackupFilename(filename1, filename2 );//��ð�������·���ı����ļ���
    int res = ToBackup(filename1,filename2);//���汸����Ϣ
    if(res==-1)
    {
         MessageBox(NULL,"  ���ݱ���ʧ�� ��","ERROR!",MB_OK);
         bRet=0;
    }
    else
         MessageBox(NULL,"  ���ݱ�����ɣ�","SUCCESS!",MB_OK);

    return bRet;
}

/**
 * ��������: RestoreData
 * ��������: �ӱ����ļ��лָ�����
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL RestoreData(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵���ļ�",
                           "�Ӳ˵�����ݻָ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                     /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);

       /*�򿪱����ļ�����Ŀ¼*/
    char dir_togo[100];//���Ҫȥ���Ǹ�Ŀ¼
    char DataDir[]="\\backup";//��������ļ�����һ��Ŀ¼
    char cmd[110]="explorer ";

    getcwd(dir_togo,sizeof(dir_togo));//�ѵ�ǰĿ¼��ַ�ַ������Ƶ�dir_togo��
    strcat(dir_togo,DataDir);//�ڵ�ǰ������ַ֮�����\data���������ļ�������Ŀ¼
    /**ע�ⲻ��AddBackslash(dir_togo)��system������fopen�Ⱥ�����ͬ�����\����Ҫ��\\ת��
    ����ע�⣬����char DataDir[7]="\\data"�ڴ浥Ԫ��ֻ��һ��\,ת�����˼����\\����ʾ\����  */

     strcat(cmd,dir_togo);//�����Ŀ¼��cmd����
     system(cmd);


     /*�����ļ�������Ϣ*/
    char filename1[100]="backup\\";
    char filename2[100]="backup\\";
    char filename[100];

Flag1:
    printf("������γ���Ϣ�����ļ���(��lessonǰ׺��.txt��׺): \n");
    scanf("%s",filename);
    if( (!strstr(filename,"lesson")) || (!strstr(filename,".txt")) )//�ж��ļ�������ȷ��
    {
      // MessageBox(NULL,"�ļ��������ļ�������lessonǰ׺��txt��׺\n","ERROR!",MB_OK);
       int result = MessageBox(NULL,"�ļ��������ļ�������lessonǰ׺��.txt��׺\n�Ƿ��������룿","ERROR��",MB_ICONINFORMATION|MB_YESNO);
       if(result==IDYES)
       {
         ClearScreenTotalInputArea();
         goto Flag1;
       }
       else
       {
         ClearScreenTotalInputArea();//����
                           /*���ع��*/
         GetConsoleCursorInfo(gh_std_out,&lpCur);
         lpCur.bVisible=FALSE;
         SetConsoleCursorInfo(gh_std_out,&lpCur);
         return 1;
       }

    }
    strcat(filename1,filename);



    printf("�������ۺϽ�ѧ��Ϣ�����ļ���(��gen_infoǰ׺��.txt��׺):\n");
    scanf("%s",filename);
    if( (!strstr(filename,"gen_info")) || (!strstr(filename,".txt")) )//�ж��ļ�������ȷ��
    {
       //MessageBox(NULL,"�ļ��������ļ�������lessonǰ׺��txt��׺\n","ERROR!",MB_OK);
       int result = MessageBox(NULL,"�ļ��������ļ�������gen_infoǰ׺��.txt��׺\n�Ƿ��������룿","ERROR��",MB_ICONINFORMATION|MB_YESNO);
       if(result==IDYES)
       {
         ClearScreenTotalInputArea();
         goto Flag1;
       }
       else
       {
         ClearScreenTotalInputArea();//����
                           /*���ع��*/
         GetConsoleCursorInfo(gh_std_out,&lpCur);
         lpCur.bVisible=FALSE;
         SetConsoleCursorInfo(gh_std_out,&lpCur);
         return 1;
       }
    }
    strcat(filename2,filename);


    FILE* fp1=fopen(filename1,"r+");
    FILE* fp2=fopen(filename2,"r+");
    if(fp1==NULL || fp2==NULL)
    {
       MessageBox(NULL,"���ݻָ�ʧ�ܣ������Ǳ����ļ���Ϣ��!\n","ERROR!",MB_OK);
       return bRet=0;
    }
    //������ڴ��е���Ϣ����������
    DestroyLesson();
    DestroyOtherVectorInfo();
    int res1=ReadLesson(fp1);
    int res2=ReadGeneralInfo(fp2);
   // printf("res1:  %d  res2:  %d\n",res1,res2);
    if(res1==-1 || res2==-1)
    {
        MessageBox(NULL,"���ݻָ�ʧ��!�ſ���Ϣ����\nԭ������ǽ�ʦ�Ͽγ�ͻ���������ó�ͻ�ȴ���","ERROR!",MB_OK);
        return bRet=0;
    }
    else
    {
         MessageBox(NULL,"���ݻָ��ɹ���","SUCCESS!",MB_OK);
         ClearScreenTotalInputArea();//����
                           /*���ع��*/
         GetConsoleCursorInfo(gh_std_out,&lpCur);
         lpCur.bVisible=FALSE;
         SetConsoleCursorInfo(gh_std_out,&lpCur);
         bRet=1;
    }


    return bRet;
}
/**
 * ��������: ExitSys
 * ��������: �˳�ϵͳ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */
BOOL ExitSys(void)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    char *pCh[] = {"ȷ���˳�ϵͳ��", "ȷ��    ȡ��"};
    int iHot = 1;

    pos.X = strlen(pCh[0]) + 6;
    pos.Y = 7;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = 2;
    labels.ppLabel = pCh;
    COORD aLoc[] = {{rcPop.Left+3, rcPop.Top+2},
                    {rcPop.Left+5, rcPop.Top+5}};
    labels.pLoc = aLoc;

    areas.num = 2;
    SMALL_RECT aArea[] = {{rcPop.Left + 5, rcPop.Top + 5,
                           rcPop.Left + 8, rcPop.Top + 5},
                          {rcPop.Left + 13, rcPop.Top + 5,
                           rcPop.Left + 16, rcPop.Top + 5}};
    char aSort[] = {0, 0};
    char aTag[] = {1, 2};
    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 4;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    if (DealInput(&areas, &iHot) == 13 && iHot == 1)
    {
        bRet = FALSE;
    }
    else
    {
        bRet = TRUE;
    }
    PopOff();

    return bRet;
}
/**
 * ��������: MaintainLessonInfo
 * ��������: ������Ϣά��
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL MaintainLessonInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                        /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);
Flag1:
    printf("������Ҫִ�еĲ�����\n");
    printf("(I)�������\n");
    printf("(D)ɾ������\n");
    printf("(M)�޸Ŀ���\n");
    printf("(L)�˳�\n");
    printf("\n��ѡ��");
    char ch;
    scanf("%1s",&ch);
    getchar();

    ClearScreenTotalInputArea();//����
    switch(ch)
    {
      case 'i': case 'I': ToInsertLesson();break;
      case 'd': case 'D': ToDeleteLesson();break;
      case 'm': case 'M': {ToModifyLesson()==-1 ? bRet=0 : bRet=1; break;}

      case 'l':  case 'L': break;
      default : {printf("\n!!����������󣡣�����������...\n\n");fflush(stdin);goto Flag1;}

    }

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);
     ClearScreenTotalInputArea();//����


    return bRet;
}


/**
 * ��������: MaintainCourseInfo
 * ��������: �γ���Ϣά��
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL MaintainCourseInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���γ���Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                        /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);
Flag1:
    printf("������Ҫִ�еĲ�����\n");
    printf("(I)����γ�\n");
    printf("(D)ɾ���γ�\n");
    printf("(M)�޸Ŀγ�\n");
    printf("(L)�˳�\n");
    printf("\n��ѡ��");
    char ch;
    scanf("%1s",&ch);
    getchar();

    ClearScreenTotalInputArea();//����
    switch(ch)
    {
      case 'i': case 'I': ToInsertCourse();break;
      case 'd': case 'D': ToDeleteCourse();break;
      case 'm': case 'M': ToModifyCourse(); break;

      case 'l':  case 'L': break;
      default : {printf("\n!!����������󣡣�����������...\n\n");fflush(stdin);goto Flag1;}

    }

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);
     ClearScreenTotalInputArea();//����

     return bRet;
}
/**
 * ��������: MaintainTeacherInfo
 * ��������: ��ʦ��Ϣά��
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL MaintainTeacherInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵����ʦ��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
                            /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);
Flag1:
    printf("������Ҫִ�еĲ�����\n");
    printf("(I)�����ʦ\n");
    printf("(D)ɾ����ʦ\n");
    printf("(M)�޸Ľ�ʦ��Ϣ\n");
    printf("(L)�˳�\n");
    printf("\n��ѡ��");
    char ch;
    scanf("%1s",&ch);
    getchar();

    ClearScreenTotalInputArea();//����
    switch(ch)
    {
      case 'i': case 'I': ToInsertTeacher();break;
      case 'd': case 'D': ToDeleteTeacher();break;
      case 'm': case 'M': ToModifyTeacher(); break;

      case 'l':  case 'L': break;
      default : {printf("\n!!����������󣡣�����������...\n\n");fflush(stdin);goto Flag1;}

    }

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);
     ClearScreenTotalInputArea();//����

    return bRet;
}
/**
 * ��������: MaintainClassroomInfo
 * ��������: ������Ϣά��
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */
BOOL MaintainClassroomInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵��������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    LessonFileForm();

    system(".\\data\\lesson_to_read.txt");
   //system(".\\data\\lesson_to_save.txt");

   int res=ReloadData();

   if(res==-1)
   {
     MessageBox(NULL,"�޸Ĵ��󣡿��ܷ������Ͽγ�ͻ��","ERROR!",MB_ICONINFORMATION|MB_OK);
     bRet=0;
   }
   else
   {
     MessageBox(NULL,"�޸ĳɹ���","SUCCESS!",MB_OK);
     bRet=1;
   }

   ClearScreenTotalInputArea();//����


   return bRet;
}

/**
 * ��������: MaintainClassnoInfo
 * ��������: �༶��Ϣά��
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�) �� FALSE(ʧ��)
 *
 */

BOOL MaintainClassnoInfo(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ά��",
                           "�Ӳ˵���༶��Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

    LessonFileForm();

    system(".\\data\\lesson_to_read.txt");
   //system(".\\data\\lesson_to_save.txt");

   int res=ReloadData();

   if(res==-1)
   {
     MessageBox(NULL,"�޸Ĵ��󣡿��ܷ������Ͽγ�ͻ��","ERROR!",MB_ICONINFORMATION|MB_OK);
     bRet=0;
   }
   else
   {
     MessageBox(NULL,"�޸ĳɹ���","SUCCESS!",MB_OK);
     bRet=1;
   }

   ClearScreenTotalInputArea();//����

    return bRet;
}

/**
 * ��������: QueryCourseByTeacher
 * ��������: ͨ����ʦ��ѯ�γ���Ϣ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL QueryCourseByTeacher(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵��ͨ����ʦ��ѯ�γ�",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
                                /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     ToQueryCourseByTeacher();


                                /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����


    return bRet;
}

/**
 * ��������: QueryLessonByClassno
 * ��������: ���༶��������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL QueryLessonByClassno(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�����༶��������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);
                                    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     memset(readed,0,sizeof(readed));
     ToQueryLessonByClassno();
     memset(readed,0,sizeof(readed));

                                    /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����

    return bRet;
}

/**
 * ��������: QueryLessonByTimeAndPlace
 * ��������: �����ҡ�ʱ���������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL QueryLessonByTimeAndPlace(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�������ҡ�ʱ���������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                            /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     //��ѯ���ֻ��0��1�������Ҳ��漰readed
     ToQueryLessonByTimeAndPlace();

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����

    return bRet;
}

/**
 * ��������: QueryLessonByCourse
 * ��������: ���γ̼�������
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL QueryLessonByCourse(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�����γ̼�������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                                /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);


     memset(readed,0,sizeof(readed));
     ToQueryLessonByCourse();
     memset(readed,0,sizeof(readed));


                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����


    return bRet;
}

/**
 * ��������: QuerySpareClassroom
 * ��������: ���н��Ҳ�ѯ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL QuerySpareClassroom(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵�����ݲ�ѯ",
                           "�Ӳ˵�����н��Ҳ�ѯ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

                                    /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);


     memset(readed,0,sizeof(readed));
     ToQuerySpareClassroom();
     memset(readed,0,sizeof(readed));


                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����

    return bRet;
}

/**
 * ��������: StatClassroomRate
 * ��������: ������������Ч����
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */

BOOL StatClassroomRate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵��������������Ч����",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

          /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     ToStatClassroomRate();

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����

    return bRet;
}


/**
 * ��������: StatTeacherRate
 * ��������: ��ʦ�οη���
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL StatTeacherRate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵����ʦ�οη���",
                           "ȷ��"
                          };


        ShowModule(plabel_name, 3);

          /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     ToStatTeacherRate();

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����



    return bRet;
}

/**
 * ��������: StatClassnoRate
 * ��������: �༶�Ͽη���
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */

BOOL StatClassnoRate(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵���༶�Ͽη���",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

             /*��ʾ���*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     ToStatClassnoRate();

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����



    return bRet;
}


/**
 * ��������: TraverseAll
 * ��������: ����������Ϣ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL TraverseAll(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������ͳ��",
                           "�Ӳ˵������������Ϣ",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);

     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=TRUE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

     ToTraverseAll();

                            /*���ع��*/
     GetConsoleCursorInfo(gh_std_out,&lpCur);
     lpCur.bVisible=FALSE;
     SetConsoleCursorInfo(gh_std_out,&lpCur);

    ClearScreenTotalInputArea();//����



    return bRet;
}

/**
 * ��������: HelpTopic
 * ��������: ���������Ϣ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */

BOOL HelpTopic(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵����������",
                           "ȷ��"
                          };

    ShowModule(plabel_name, 3);


    system(".\\help\\help.docx");

    return bRet;
}


/**
 * ��������: About
 * ��������: ������ڱ�����İ汾�ȵ���Ϣ
 * �������: ��
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */

BOOL About(void)
{
    BOOL bRet = TRUE;
    char *plabel_name[] = {"���˵������",
                           "�Ӳ˵������...",
                           "ȷ��"
                          };



    ShowModule(plabel_name, 3);
    ShellExecute(NULL,"open","https://github.com/ShmilyBelon",NULL,NULL,SW_SHOWNORMAL);

    /*��ʾ���*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=TRUE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);






   printf("\n�����ߣ��¹���\n");
   printf("\n��λ�����пƼ���ѧ�������ѧ�뼼��ѧԺ�������У��1601��\n");
   printf("\n�汾��win1709\n");

   printf("\n�ο����ף���ε��, ��ΰ��. ���ݽṹ��C���԰棩. ����: �廪��ѧ������,1997\n");
   printf("           ��C����ʵ����γ���ơ���ѧ�����磬 � ¬Ƽ �ܼƲ�����\n");
   printf("\n\n��л��κΡ��ʦ\n\n");
   printf("��ע����ϵͳΪwindows�汾����֧����linux��Mac OS X������ϵͳ�����У�\n\n");
   printf("�����������...");

   getch();

   ClearScreenTotalInputArea();//����

    /*���ع��*/
    GetConsoleCursorInfo(gh_std_out,&lpCur);
    lpCur.bVisible=FALSE;
    SetConsoleCursorInfo(gh_std_out,&lpCur);


    return bRet;
}


/**
 * ��������: ShowModule
 * ��������: ���û�Ҫ�������ʾ��
 * �������: ��ʾ��Ҫ�������ʾ��Ϣ�ַ�����ַ����ʾ���������
 * �������: ��
 * �� �� ֵ: BOOL����, TRUE(�ɹ�)
 *
 */
BOOL ShowModule(char **pString, int n)
{
    LABEL_BUNDLE labels;
    HOT_AREA areas;
    BOOL bRet = TRUE;
    SMALL_RECT rcPop;
    COORD pos;
    WORD att;
    int iHot = 1;
    int i, maxlen, str_len;

    for (i=0,maxlen=0; i<n; i++) {
        str_len = strlen(pString[i]);
        if (maxlen < str_len) {
            maxlen = str_len;
        }
    }

    pos.X = maxlen + 6;
    pos.Y = n + 5;
    rcPop.Left = (SCR_COL - pos.X) / 2;
    rcPop.Right = rcPop.Left + pos.X - 1;
    rcPop.Top = (SCR_ROW - pos.Y) / 2;
    rcPop.Bottom = rcPop.Top + pos.Y - 1;

    att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
    labels.num = n;
    labels.ppLabel = pString;
    COORD aLoc[n];

    for (i=0; i<n; i++) {
        aLoc[i].X = rcPop.Left + 3;
        aLoc[i].Y = rcPop.Top + 2 + i;

    }
    str_len = strlen(pString[n-1]);
    aLoc[n-1].X = rcPop.Left + 3 + (maxlen-str_len)/2;
    aLoc[n-1].Y = aLoc[n-1].Y + 2;

    labels.pLoc = aLoc;

    areas.num = 1;
    SMALL_RECT aArea[] = {{aLoc[n-1].X, aLoc[n-1].Y,
                           aLoc[n-1].X + 3, aLoc[n-1].Y}};

    char aSort[] = {0};
    char aTag[] = {1};

    areas.pArea = aArea;
    areas.pSort = aSort;
    areas.pTag = aTag;
    PopUp(&rcPop, att, &labels, &areas);

    pos.X = rcPop.Left + 1;
    pos.Y = rcPop.Top + 2 + n;
    FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right-rcPop.Left-1, pos, &ul);

    DealInput(&areas, &iHot);
    PopOff();

    return bRet;

}
