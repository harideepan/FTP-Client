#include<windows.h>
#include<dir.h>
#include<string.h>
#include "mysql.h"
#include<commctrl.h>
#include<dir.h>
#include<stdio.h>
#include <jni.h>
#include <pthread.h>
#include<stdlib.h>

#ifdef _WIN32
#define PATH_SEPARATOR ';'
#else
#define PATH_SEPARATOR ':'
#endif

#define ID_LIST 2
#define ID_TEXTBOXU 3
#define ID_TEXTBOXP 4
#define ID_BTNL 5
#define ID_BTNN 6
#define ID_BTNNEW 7
#define ID_BTNSAVE 8
#define ID_BTNSAVE1 12
#define ID_LISTBOX 9
#define ID_BTNLOG 10
#define ID_BTNFILTER 11

static HWND hwndTextbox;
static HWND hwndTextboxU;
static HWND hwndTextboxP;
static HWND fileNameText;
static HWND fileNameText1;
static HWND filterText;
static HWND fileContentText;
static HWND loginBtn;
static HWND newUserBtn;
static HWND tilteLbl;
static HWND lbl1;
static HWND lblmess;
static HWND lbl2;
static HWND lbl3;
static HWND newFile;
static HWND save;
static HWND save1;
static HWND list;
static HWND logout;
static HWND hwndList ;
static HWND filter ;

JavaVMOption options[1];
JNIEnv *env;
JavaVM *jvm;
JavaVMInitArgs vm_args;
jobject object;
jobject CSVobject;
long status;

HANDLE thread;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure2 (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure3 (HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WindowProcedure4 (HWND, UINT, WPARAM, LPARAM);

HWND hwnd1,hwnd2,hwnd3,hwnd4;

int loginPage=1;
int closeFlag=0;
char fileList[50][20];
char user[5];
HINSTANCE ThisInstance;
HINSTANCE PrevInstance;
LPSTR _lpszArgument;
int visible; 
char lastSearchKey[15];      

//pthread_mutex_t mutexjvm;     /* This is the handle for our window */
/*  Make the class name into a global variable  */
//char szClassName[ ] = "WindowsApp";
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
    ThisInstance=hThisInstance;
    PrevInstance=hPrevInstance;
    _lpszArgument=lpszArgument;

    visible=nFunsterStil;
    
    MSG messages;            /* Here messages to the application are saved */
    
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = "Window1";
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;
    /* The class is registered, let's create the program*/
    createWindow1();
    

    WNDCLASSEX wincl2;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl2.hInstance = hThisInstance;
    wincl2.lpszClassName = "Window2";
    wincl2.lpfnWndProc = WindowProcedure2;      /* This function is called by windows */
    wincl2.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl2.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl2.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl2.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl2.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl2.lpszMenuName = NULL;                 /* No menu */
    wincl2.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl2.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl2.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl2))
        return 0;
    /* The class is registered, let's create the program*/
    createWindow2();

    WNDCLASSEX wincl3;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl3.hInstance = hThisInstance;
    wincl3.lpszClassName = "Window3";
    wincl3.lpfnWndProc = WindowProcedure3;      /* This function is called by windows */
    wincl3.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl3.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl3.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl3.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl3.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl3.lpszMenuName = NULL;                 /* No menu */
    wincl3.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl3.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl3.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl3))
        return 0;
    /* The class is registered, let's create the program*/
    createWindow3();
    
    WNDCLASSEX wincl4;        /* Data structure for the windowclass */
    /* The Window structure */
    wincl4.hInstance = hThisInstance;
    wincl4.lpszClassName = "Window4";
    wincl4.lpfnWndProc = WindowProcedure4;      /* This function is called by windows */
    wincl4.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl4.cbSize = sizeof (WNDCLASSEX);
    /* Use default icon and mouse-pointer */
    wincl4.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl4.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl4.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl4.lpszMenuName = NULL;                 /* No menu */
    wincl4.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl4.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default color as the background of the window */
    wincl4.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl4))
        return 0;
    /* The class is registered, let's create the program*/
    createWindow4();
    /* Make the window visible on the screen */
    //SetParent(hwnd12,hwnd1);
    createJVM();
    ShowWindow (hwnd1, nFunsterStil);
	//pthread_mutex_init(&mutexjvm, NULL);
    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}
void createWindow1()
{
    hwnd1 = CreateWindowEx (
                0,                   /* Extended possibilites for variation */
                "Window1",         /* Classname */
                "Windows App",       /* Title Text */
                WS_SYSMENU,          /* default window */
                CW_USEDEFAULT,       /* Windows decides the position */
                CW_USEDEFAULT,       /* where the window ends up on the screen */
                500,                 /* The programs width */
                500,                 /* and height in pixels */
                HWND_DESKTOP,        /* The window is a child-window to desktop */
                NULL,                /* No menu */
                ThisInstance,       /* Program Instance handler */
                NULL                 /* No Window Creation data */
            );
}
void createWindow2()
{
    hwnd2 = CreateWindowEx (
                0,                   /* Extended possibilites for variation */
                "Window2",         /* Classname */
                "Windows App",       /* Title Text */
                WS_SYSMENU,          /* default window */
                CW_USEDEFAULT,       /* Windows decides the position */
                CW_USEDEFAULT,       /* where the window ends up on the screen */
                500,                 /* The programs width */
                500,                 /* and height in pixels */
                HWND_DESKTOP,        /* The window is a child-window to desktop */
                NULL,                /* No menu */
                ThisInstance,       /* Program Instance handler */
                NULL                 /* No Window Creation data */
            );
}
void createWindow3()
{
    hwnd3 = CreateWindowEx (
                0,                   /* Extended possibilites for variation */
                "Window3",         /* Classname */
                "Windows App",       /* Title Text */
                WS_SYSMENU,          /* default window */
                CW_USEDEFAULT,       /* Windows decides the position */
                CW_USEDEFAULT,       /* where the window ends up on the screen */
                500,                 /* The programs width */
                500,                 /* and height in pixels */
                HWND_DESKTOP,        /* The window is a child-window to desktop */
                NULL,                /* No menu */
                ThisInstance,       /* Program Instance handler */
                NULL                 /* No Window Creation data */
            );
}
void createWindow4()
{
    hwnd4 = CreateWindowEx (
                0,                   /* Extended possibilites for variation */
                "Window4",         /* Classname */
                "Windows App",       /* Title Text */
                WS_SYSMENU,          /* default window */
                CW_USEDEFAULT,       /* Windows decides the position */
                CW_USEDEFAULT,       /* where the window ends up on the screen */
                500,                 /* The programs width */
                500,                 /* and height in pixels */
                HWND_DESKTOP,        /* The window is a child-window to desktop */
                NULL,                /* No menu */
                ThisInstance,       /* Program Instance handler */
                NULL                 /* No Window Creation data */
            );
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        tilteLbl=CreateWindow("STATIC","Login",
                              WS_VISIBLE|WS_CHILD,
                              220,10,100,50,
                              hwnd, (HMENU) 4, NULL, NULL);
        lbl1=CreateWindow("STATIC","User ID",
                          WS_VISIBLE|WS_CHILD,
                          130,60,100,20,
                          hwnd, (HMENU) 1, NULL, NULL);
        lbl2=CreateWindow("STATIC","Password",
                          WS_VISIBLE|WS_CHILD,
                          130,100,100,20,
                          hwnd, (HMENU) 2, NULL, NULL);
        hwndTextboxU = CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,
                                    240,60,100,20,
                                    hwnd, (HMENU) ID_TEXTBOXU, NULL, NULL);
        hwndTextboxP = CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,
                                    240,100,100,20,
                                    hwnd, (HMENU) ID_TEXTBOXP, NULL, NULL);
        loginBtn=CreateWindow(TEXT("button"), TEXT("Login"),
                              WS_VISIBLE|WS_CHILD,
                              160,150,150,20,
                              hwnd, (HMENU) ID_BTNL, NULL, NULL);
        newUserBtn=CreateWindow(TEXT("button"), TEXT("New User?"),
                                WS_VISIBLE|WS_CHILD,
                                160,180,150,20,
                                hwnd, (HMENU) ID_BTNN, NULL, NULL);
        break;

    }
    case WM_COMMAND:
    {
        //action for button
        if (LOWORD(wParam) == ID_BTNL)
        {
            //create variables
            int length = GetWindowTextLength(hwndTextboxU) + 1;
            static char userID[20] = "";
            static char password[15]="";
            static char buttonText[20]="";
            GetWindowText(hwndTextboxU,userID,length);
            length = GetWindowTextLength(hwndTextboxP) + 1;
            GetWindowText(hwndTextboxP,password,length);
            length = GetWindowTextLength(loginBtn) + 1;
            GetWindowText(loginBtn,buttonText,length);
            if(strcmp(userID,"")!=0 && strcmp(password,"")!=0)
            {
                if(loginPage)
                {
	            	login(userID,password);
                }
                else
                {
                    create(userID,password);
                    ShowWindow(newUserBtn, WS_VISIBLE);
                    SetWindowText(tilteLbl,"Login");
                    SetWindowText(lbl1,"User ID");
                    SetWindowText(lbl2,"Password");
                    SetWindowText(loginBtn,"Login");
                    loginPage=1;
                    ShowWindow(newUserBtn,visible);
                }
                SetWindowText(hwndTextboxU,"");
                SetWindowText(hwndTextboxP,"");
            }
            else
            {
                MessageBox(0,"No field should be blank","Message",1);
            }
        }
        if (LOWORD(wParam) == ID_BTNN)
        {
            loginPage=0;
            ShowWindow(newUserBtn, SW_HIDE);
            SetWindowText(hwndTextboxU,"");
            SetWindowText(hwndTextboxP,"");
            SetWindowText(tilteLbl,"Enter your details");
            SetWindowText(lbl1,"Name");
            SetWindowText(loginBtn,"Create workspace");
        }
        break;
    }
    case WM_DESTROY:
        stopFTPServer();
        (*jvm)->DestroyJavaVM(jvm);
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

LRESULT CALLBACK WindowProcedure2 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        logout=CreateWindow(TEXT("button"), TEXT("logout"),
                            WS_VISIBLE|WS_CHILD,
                            340,30,150,20,
                            hwnd, (HMENU) ID_BTNLOG, NULL, NULL);
        lblmess=CreateWindow("STATIC","Files in your workspace",
                             WS_VISIBLE|WS_CHILD,
                             10,30,300,20,
                             hwnd, (HMENU) 4, NULL, NULL);
        list=CreateWindow(WC_LISTBOX,NULL,
                          WS_VISIBLE|WS_CHILD|WS_VSCROLL|LBS_NOTIFY,
                          10,50,480,100,
                          hwnd, (HMENU) ID_LISTBOX, NULL, NULL);
        newFile=CreateWindow(TEXT("button"), TEXT("New File"),
                             WS_VISIBLE|WS_CHILD,
                             160,150,150,20,
                             hwnd, (HMENU) ID_BTNNEW, NULL, NULL);
        break;
    }
    case WM_COMMAND:
    {
        if (LOWORD(wParam) == ID_LISTBOX)
        {
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
            	char *dot;
                int index = (int) SendMessageW(list, LB_GETCURSEL, 0, 0);
                
                showFileContent(fileList[index],user);
                
                dot = strrchr(fileList[index], '.');
				if (dot && !strcmp(dot, ".csv"))
				{	
					SetWindowText(fileNameText1,fileList[index]);
					ShowWindow(hwnd4,visible);
				}
				else
				{
					SetWindowText(fileNameText,fileList[index]);
					ShowWindow(hwnd3,visible);
				}
            }
        }
        if (LOWORD(wParam) == ID_BTNNEW)
        {
            ShowWindow(hwnd3,visible);
        }
        if (LOWORD(wParam) == ID_BTNLOG)
        {
            ShowWindow(hwnd2,SW_HIDE);
            ShowWindow(hwnd1,visible);
        }
        break;
    }
    case WM_DESTROY:
        createWindow2();
        ShowWindow(hwnd1,visible);
        break;
    default:     
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
LRESULT CALLBACK WindowProcedure3 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int i;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
        lbl2=CreateWindow("STATIC","File Name",
                          WS_VISIBLE|WS_CHILD,
                          10,10,100,20,
                          hwnd, (HMENU) 4, NULL, NULL);
        fileNameText = CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,
                                    120,10,200,20,
                                    hwnd, (HMENU) ID_TEXTBOXU, NULL, NULL);
        save=CreateWindow(TEXT("button"), TEXT("Save File"),
                          WS_VISIBLE|WS_CHILD,
                          350,10,120,20,
                          hwnd, (HMENU) ID_BTNSAVE, NULL, NULL);
        fileContentText = CreateWindow(TEXT("EDIT"), TEXT(""),
                                       WS_VISIBLE|WS_CHILD|WS_BORDER|ES_MULTILINE,
                                       10,40,470,400,
                                       hwnd, (HMENU) ID_TEXTBOXU, NULL, NULL);
        break;
    }
    case WM_COMMAND:
    {
        
        if (LOWORD(wParam) == ID_BTNSAVE)
        {
        	int length;
            char fileName[15];
            length = GetWindowTextLength(fileNameText) + 1;
            GetWindowText(fileNameText,fileName,length);
            if(strcmp(fileName,"")==0)
            {
                MessageBox(0,"Enter the file name","Message",1);
            }
            else
            {
                createFile(fileName,user);
            }
        }
        break;
    }
    case WM_DESTROY:
        createWindow3();
        break;
    default:                
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

//Thread to check the scroller position
static DWORD WINAPI ThreadFunc(JavaVM **jvm) {
  while(closeFlag!=1)
  {
		int itemCount=ListView_GetItemCount(hwndList);
		int itemsPerPage=SendMessage(hwndList,LVM_GETCOUNTPERPAGE,0,0);
		if(itemCount>itemsPerPage)
		{
	    	int topIndex=SendMessage(hwndList,LVM_GETTOPINDEX,0,0);
	        if(topIndex>=itemCount-itemsPerPage)
	        {
	        	(**jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
	        	loadMoreItems();
			}	
		}
  }
  ExitThread(0);
  return 0;
}

LRESULT CALLBACK WindowProcedure4 (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
    {
    	lbl2=CreateWindow("STATIC","File Name",
                          WS_VISIBLE|WS_CHILD,
                          10,10,100,20,
                          hwnd, (HMENU) 4, NULL, NULL);
        fileNameText1 = CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,
                                    120,10,200,20,
                                    hwnd, (HMENU) ID_TEXTBOXU, NULL, NULL);
        save1=CreateWindow(TEXT("button"), TEXT("Export"),
                          WS_VISIBLE|WS_CHILD,
                          350,10,120,20,
                          hwnd, (HMENU) ID_BTNSAVE1, NULL, NULL);
        lbl3=CreateWindow("STATIC","Filter",
                          WS_VISIBLE|WS_CHILD,
                          10,40,100,20,
                          hwnd, (HMENU) 4, NULL, NULL);
        filterText= CreateWindow(TEXT("EDIT"), TEXT(""),
                                    WS_VISIBLE|WS_CHILD|WS_BORDER|ES_AUTOHSCROLL,
                                    120,40,200,20,
                                    hwnd, (HMENU) ID_TEXTBOXU, NULL, NULL);
        filter=CreateWindow(TEXT("button"), TEXT("Filter"),
                          WS_VISIBLE|WS_CHILD,
                          350,40,120,20,
                          hwnd, (HMENU) ID_BTNFILTER, NULL, NULL);
	    hwndList = CreateWindow (WC_LISTVIEW, "", 
        WS_VISIBLE | WS_BORDER | WS_CHILD |  LVS_REPORT |  LVS_EDITLABELS, 
        10,80,470,360,
        hwnd, (HMENU) ID_LIST, 0, 0); 
        break;

    }
    case WM_COMMAND:
    {
    	if (LOWORD(wParam) == ID_BTNFILTER)
        {
        	int length;
            char searchKey[15];
            length = GetWindowTextLength(filterText) + 1;
            GetWindowText(filterText,searchKey,length);
            
            if(strcmp(searchKey,lastSearchKey)!=0)
            {
            	strcpy(lastSearchKey,searchKey);
            	filterContent(searchKey);
			} 
        }
        if (LOWORD(wParam) == ID_BTNSAVE1)
        {
        	int length;
            char fileName[15];
            length = GetWindowTextLength(fileNameText1) + 1;
            GetWindowText(fileNameText1,fileName,length);
            if(strcmp(fileName,"")==0)
            {
                MessageBox(0,"Enter the file name","Message",1);
            }
            else
            {
            	TerminateThread(thread,1);
                createFile(fileName,user);
            }
		}
        break;
    }
    case WM_DESTROY:
    	closeFlag=1;
        createWindow4();
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}
void createFile(char fileName[],char UserID[])
{
	(*jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
    char path[50];
    char query[250];
    char name[15];
    char fileContent[100];
    char character;
    int c=0;
    int length;
    char* dot;

    MYSQL mysql;
    int i;

    jclass cls;
    jmethodID mid;

    if(mysql_init(&mysql)==NULL) {
        return 0;
    }
    mysql_real_connect(&mysql,"localhost","root","","Folders",0,NULL,0);
	snprintf(path, 50,"E:/Local Files/Users/%s/%s",UserID,fileName);
    
    dot = strrchr(fileName, '.');
	if (dot && !strcmp(dot, ".csv"))//If it's a CSV file
	{
		if (status != JNI_ERR)
	    {
	    	jstring toFileName = (*env)->NewStringUTF(env,path);
	        cls=(*env)->GetObjectClass(env,CSVobject);
	        if(cls !=0)
	        {
	            mid = (*env)->GetMethodID(env, cls, "export", "(Ljava/lang/String;)V");
	            if(mid !=0)
	            {
	                (*env)->CallVoidMethod(env, CSVobject, mid,toFileName);
	            }
	            else
	            {
	                printf("method not found");
	            }
	        }
	        else
	        {
	            printf("class not found");
	        }
	    }
	}
    else
	{
		FILE *fptr;
	    fptr=fopen(path,"w");
	    if (fptr == NULL)
	    {
	        MessageBox(0,"Error file","Message",1);
	    }
	    length = GetWindowTextLength(fileContentText) + 1;
	    GetWindowText(fileContentText,fileContent,length);
	    fprintf(fptr,fileContent);
	    fclose(fptr);
	}
    snprintf(query, 250, "delete from files where path='%s'",path);
    mysql_query(&mysql,query);
    snprintf(query, 250, "insert into files values('%s','%s',%s)",fileName,path,UserID);
    if (mysql_query(&mysql,query))
    {
        //finish_with_error(&mysql);
        //MessageBox(0,"Error query","Message",1);
    }


    char *localPath = (char*)malloc(50);
    snprintf(localPath, 49,"E:/Local Files/Users/%s/%s",UserID,fileName);
    jstring local = (*env)->NewStringUTF(env,localPath);


    char *file = (char*)malloc(20);
    strcpy(file,fileName);
    jstring fileN = (*env)->NewStringUTF(env,file);

    char *remotePath = (char*)malloc(50);
    snprintf(remotePath, 49,"/Users/%s/",UserID);
    jstring remote = (*env)->NewStringUTF(env,remotePath);

	printf("file saved to local");
    if (status != JNI_ERR)
    {
        cls=(*env)->GetObjectClass(env,object);
        if(cls !=0)
        {
            mid = (*env)->GetMethodID(env, cls, "uploadFile", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
            if(mid !=0)
            {
				printf("upload method found");
                (*env)->CallVoidMethod(env, object, mid,local,fileN,remote);
                printf("upload method called");

            }
            else
            {
                printf("method not found uploadFile");
            }
        }
        else
        {
            printf("class not found");
        }
    }
    MessageBox(0,"File saved","Message",1);
    populateList(UserID);
    SetWindowText(fileNameText,"");
    SetWindowText(fileNameText1,"");
    SetWindowText(fileContentText,"");
    SetWindowText(filterText,"");
    ShowWindow(hwnd3,SW_HIDE);
    ShowWindow(hwnd4,SW_HIDE); 
}


void showFileContent(char fileName[],char userID[])
{
    (*jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
    char path[50];
    char query[250];
    char character;
    char content[100];
    char *dot;
    int i=0;

    FILE *fptr;

    jclass cls;
    jmethodID mid;

    char *remotePath = (char*)malloc(50);
    snprintf(remotePath, 49,"/Users/%s/%s",userID,fileName);
    jstring remote = (*env)->NewStringUTF(env,remotePath);

    char *localPath = (char*)malloc(50);
    snprintf(localPath, 49,"E:/Local Files/Users/%s/%s",userID,fileName);
    jstring local = (*env)->NewStringUTF(env,localPath);

    if (status != JNI_ERR)
    {
        cls=(*env)->GetObjectClass(env,object);
        if(cls !=0)
        {
            mid = (*env)->GetMethodID(env, cls, "downloadFile", "(Ljava/lang/String;Ljava/lang/String;)V");
            if(mid !=0)
            {
                (*env)->CallVoidMethod(env, object, mid,remote,local);
            }
            else
            {
                printf("method not found");
            }
        }
        else
        {
            printf("class not found");
        }
    }

    snprintf(path, 50,"E:/Local Files/Users/%s/%s",userID,fileName);
    
    dot = strrchr(fileName, '.');
	if (dot && !strcmp(dot, ".csv"))
	{
		jclass cls;
        jmethodID constructor;
        cls = (*env)->FindClass(env, "CSVReader");
    	constructor = (*env)->GetMethodID(env, cls, "<init>", "(Ljava/lang/String;)V");
    	CSVobject = (*env)->NewObject(env, cls, constructor,local);
    	if (status != JNI_ERR)
	    {
	    	
	        cls=(*env)->GetObjectClass(env,CSVobject);
	        if(cls !=0)
	        {
	            mid = (*env)->GetMethodID(env, cls, "getFileContent", "()[[Ljava/lang/String;");
	
	            if(mid !=0)
	            {
	                jobjectArray lines = (*env)->CallObjectMethod(env, CSVobject, mid);
	                fillTable(lines);
	            }
	            else
	            {
	                printf("method not found");
	            }
	        }
	        else
	        {
	            printf("class not found");
	        }
	    }
    	closeFlag=0;
		thread = CreateThread(NULL, 0, ThreadFunc, &jvm, 0, NULL);
	}
    else
    {
    	SetWindowText(fileContentText,"");
	    fptr=fopen(path,"r");
	
	    if (fptr == NULL)
	    {
	        MessageBox(0,"File does not exists","Message",1);
	    }
	    character = fgetc(fptr);
	    while (character != EOF)
	    {
	
	        content[i++]=character;
	        character = fgetc(fptr);
	    }
	    content[i]='\0';
	    SetWindowText(fileContentText,content);
	    fclose(fptr);
	}
}


void filterContent(char searchKey[])
{
    (*jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
    
	jclass cls;
    jmethodID mid;
    jstring search = (*env)->NewStringUTF(env,searchKey);
    	
    if (status != JNI_ERR)
	{
	    cls=(*env)->GetObjectClass(env,CSVobject);
	    if(cls !=0)
	    {
			mid = (*env)->GetMethodID(env, cls, "getFilteredContent", "(Ljava/lang/String;)[[Ljava/lang/String;");
	        if(mid !=0)
	        {
	            jobjectArray lines = (*env)->CallObjectMethod(env, CSVobject, mid,search);
	            fillTable(lines);
	        }
	        else
	        {
	            MessageBox(0,"Method not found","Message",1);
	        }
	    }
	    else
	    {
	        MessageBox(0,"Class not found","Message",1);
	    }
	}
}

void loadMoreItems()
{
	jclass cls;
    jmethodID mid;
    	
    if (status != JNI_ERR)
	{
	    cls=(*env)->GetObjectClass(env,CSVobject);
	    if(cls !=0)
	    {
			mid = (*env)->GetMethodID(env,cls,"loadMore","()[[Ljava/lang/String;");
	        if(mid !=0)
	        {
	            jobjectArray lines = (*env)->CallObjectMethod(env, CSVobject, mid);
	            int lineCount = (*env)->GetArrayLength(env,lines);
				if(lineCount!=0)
				{
				    int i,j;
				    jstring string;
				    const char *rawString;
				    
				    jobjectArray line = (jobjectArray) ((*env)->GetObjectArrayElement(env,lines, 0));
				    int columnCount = (*env)->GetArrayLength(env,line);      
				    //Creating items
				    for (i=lineCount-1; i>=0; i--)
				    {
				        line = (jobjectArray) ((*env)->GetObjectArrayElement(env,lines, i));
				        char item[columnCount][50];
				        for(j=0;j<columnCount;j++)
				        {
					        string = (jstring) ((*env)->GetObjectArrayElement(env,line, j));
					        rawString = (*env)->GetStringUTFChars(env,string, 0);
							strcpy(item[j],rawString);
					    }
					    createItem (hwndList,item,columnCount);
				    } 
				} 
	        }
	        else
	        {
	            MessageBox(0,"Method not found load more","Message",1);
	        }
	    }
	    else
	    {
	        MessageBox(0,"Class not found","Message",1);
	    }
	}
}

void fillTable(jobjectArray lines)
{
	ListView_DeleteAllItems(hwndList);
	int lineCount = (*env)->GetArrayLength(env,lines);
	if(lineCount==0)
	{
	    //MessageBox(0,"File Empty","Message",1);
	}
	else
	{
	    int i,j;
	    jstring string;
	    const char *rawString;              
	    //Creating column
	    jobjectArray line = (jobjectArray) ((*env)->GetObjectArrayElement(env,lines, 0));
	    int columnCount = (*env)->GetArrayLength(env,line);
	    for(j=0;j<columnCount;j++)
	    {
	        string = (jstring) ((*env)->GetObjectArrayElement(env,line, j));
		    rawString = (*env)->GetStringUTFChars(env,string, 0);
		    ListView_DeleteColumn(hwndList,j);
	        createColumn (hwndList,j,rawString,80);
	    }          
	    //Creating items
	    for (i=lineCount-1; i>=1; i--)
	    {
	        line = (jobjectArray) ((*env)->GetObjectArrayElement(env,lines, i));
	        char item[columnCount][50];
	        for(j=0;j<columnCount;j++)
	        {
		        string = (jstring) ((*env)->GetObjectArrayElement(env,line, j));
		        rawString = (*env)->GetStringUTFChars(env,string, 0);
				strcpy(item[j],rawString);
		    }
		    createItem (hwndList,item,columnCount);
	    }  
	}
}

int createColumn (HWND hwndLV, int iCol, char * text, int iWidth)
 {
 	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT |  LVCF_WIDTH |  LVCF_TEXT |  LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = iWidth;
	lvc.pszText = text;  
	lvc.iSubItem = iCol;
	return ListView_InsertColumn (hwndLV, iCol, & lvc);
 }
 
 int createItem (HWND hwndList, char item[][50],int columns)
 { 
	LVITEM lvi = {0};
	int Ret;
	int i;
    lvi.mask = LVIF_TEXT;
    Ret = ListView_InsertItem (hwndList, & lvi);
    if (Ret >= 0) {
    	for(i=0;i<columns;i++)
    	{
    		ListView_SetItemText (hwndList, Ret, i, item[i]);
		}
    }
    return Ret;
 }

void login(char userID[],char password[])
{
	(*jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
    strcpy(user,userID);
    int rows;
    char name[15];
    char query[250];
    char dir[250];
    MYSQL mysql;
    int i;

    if(mysql_init(&mysql)==NULL) {
        printf("\nInitialization error\n");
        return 0;
    }

    mysql_real_connect(&mysql,"localhost","root","","Folders",0,NULL,0);

    snprintf(query, 250, "select * from Users where UserID=%s and Password='%s'", userID, password);
    if (mysql_query(&mysql,query))
    {
        MessageBox(0,"Error",userID,1);
    }

    MYSQL_RES *result = mysql_store_result(&mysql);
    rows=mysql_num_rows(result);
    if(rows==0)
    {
        MessageBox(0,"Invalid UserID or Password","Message",1);
    }
    else
    {
        populateList(userID);
        ShowWindow(hwnd2,visible);
        ShowWindow(hwnd1, SW_HIDE);
    }
    mysql_close(&mysql);
}

void logout_()
{
    ShowWindow(lbl2, WS_VISIBLE);
    ShowWindow(hwnd2,SW_HIDE);
    ShowWindow(hwnd1, WS_VISIBLE);
}

void createJVM()
{
    jclass cls;
    jmethodID constructor;
    options[0].optionString = "-Djava.class.path=E:\\JNI;E:\\JNI\\commons-net-ftp-2.0.jar;E:\\JNI\\aopalliance-1.0.jar;E:\\JNI\\slf4j.jar;E:\\JNI\\ftplet-api-1.0.6.jar;E:\\JNI\\ftpserver-core-1.0.6.jar;E:\\JNI\\jcl-over-slf4j-1.5.2.jar;E:\\JNI\\log4j-1.2.14.jar;E:\\JNI\\mina-core-2.0.4.jar;E:\\JNI\\slf4j-api-1.5.2.jar;E:\\JNI\\slf4j-log4j12-1.5.2.jar;E:\\JNI\\spring-beans-2.5.5.jar;E:\\JNI\\spring-context-2.5.5.jar;E:\\JNI\\spring-core-2.5.5.jar";
    memset(&vm_args, 0, sizeof(vm_args));
    vm_args.version = JNI_VERSION_1_6;
    vm_args.nOptions = 1;
    vm_args.options = options;
    status=JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (status != JNI_ERR)
    {
    	startFTPServer();
	    cls = (*env)->FindClass(env, "FTPClassA");
	    constructor = (*env)->GetMethodID(env, cls, "<init>", "()V");
	    object = (*env)->NewObject(env, cls, constructor);
	}
}

void stopFTPServer()
{
    jclass cls;
    jmethodID mid;

    if (status != JNI_ERR)
    {
        cls = (*env)->FindClass(env, "FTPServer");
        if(cls !=0)
        {
            mid = (*env)->GetStaticMethodID(env, cls, "StopServer", "()V");
            if(mid !=0)
            {
                (*env)->CallStaticVoidMethod(env, cls, mid);
                MessageBox(0,"FTP Server stopped","Message",1);

            }
            else
            {
                printf("method not found");
            }
        }
        else
        {
            printf("class not found");
        }
    }
}

void startFTPServer()
{

    jclass cls;
    jmethodID mid;

    if (status != JNI_ERR)
    {
        cls = (*env)->FindClass(env, "FTPServer");

        if(cls !=0)
        {
            mid = (*env)->GetStaticMethodID(env, cls, "main", "([Ljava/lang/String;)V");
            if(mid !=0)
            {
                 MessageBox(0,"FTP Server started","Message",1);
                (*env)->CallStaticVoidMethod(env, cls, mid);
            }
            else
            {
                printf("method not found");
            }
        }
        else
        {
            printf("class not found");
        }
    }
}

void populateList(char userID[])
{
    jclass cls;
    jmethodID mid;
    
    SendMessage(list,LB_RESETCONTENT,0,NULL);
    char *buf = (char*)malloc(5);
    strcpy(buf, userID);
    jstring jstrBuf = (*env)->NewStringUTF(env, buf);
    if (status != JNI_ERR)
    {
        cls=(*env)->GetObjectClass(env,object);
        if(cls !=0)
        {

            mid = (*env)->GetMethodID(env, cls, "getFileList", "(Ljava/lang/String;)[Ljava/lang/String;");

            if(mid !=0)
            {

                jobjectArray files = (*env)->CallObjectMethod(env, object, mid,jstrBuf);

                int stringCount = (*env)->GetArrayLength(env,files);
                if(stringCount==0)
                {

                    SendMessage(list,LB_ADDSTRING,0,(LPARAM) "No files in your work space");

                }
                else
                {
                    int i;
                    for (i=0; i<stringCount; i++)
                    {
                        jstring string = (jstring) ((*env)->GetObjectArrayElement(env,files, i));
                        const char *rawString = (*env)->GetStringUTFChars(env,string, 0);
                        printf("%s\n",rawString);
                        SendMessage(list,LB_ADDSTRING,0,(LPARAM) rawString);
                        strcpy(fileList[i],rawString);
                    }
                }

            }
            else
            {
                printf("method not found get filelist");
            }
        }
        else
        {
            printf("class not found");
        }
    }
}

void create(char userName[],char password[])
{
	(*jvm)->AttachCurrentThread(jvm, (void**) &(env), NULL);
    char UserID[5];
    char query[250];
    char message[250];
    char dir[250];

    jclass cls;
    jmethodID mid;

    MYSQL mysql;
    int i;

    if(mysql_init(&mysql)==NULL) {
        printf("\nInitialization error\n");
        return 0;
    }

    mysql_real_connect(&mysql,"localhost","root","","Folders",0,NULL,0);

    if (mysql_query(&mysql, "SELECT `AUTO_INCREMENT` FROM  INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = 'Folders' AND   TABLE_NAME   = 'Users'; "))
    {
        //finish_with_error(&mysql);
        printf("Error");
    }
    MYSQL_RES *result = mysql_store_result(&mysql);
    MYSQL_ROW row=mysql_fetch_row(result);
    snprintf(UserID,5,row[0]);

    snprintf(query, 250, "INSERT INTO Users VALUES(NULL,'%s', '%s')", userName, password);
    if (mysql_query(&mysql, query))
    {
        printf("Error");
    }

    char *buf = (char*)malloc(5);
    strcpy(buf, UserID);
    jstring jstrBuf = (*env)->NewStringUTF(env, buf);

    if (status != JNI_ERR)
    {

        cls=(*env)->GetObjectClass(env,object);
        if(cls !=0)
        {
            mid = (*env)->GetMethodID(env, cls, "createDirectory", "(Ljava/lang/String;)V");
            if(mid !=0)
            {

                (*env)->CallVoidMethod(env, object, mid,jstrBuf);

            }
            else
            {
                MessageBox(0,"Method not found","Message",1);
            }
        }
        else
        {
            MessageBox(0,"class not found","Message",1);
        }
    }

    snprintf(dir, 250, "E:/Local Files/Users/%s",UserID);
    mkdir(dir);
    snprintf(message, 250, "User Workspace created. Your UserID is %s",UserID);
    MessageBox(0,message,"Message",1);
    mysql_close(&mysql);
}


