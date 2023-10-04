#include <stdio.h>
#include <cstring>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct passwd Passwd;

typedef struct s
{
    char a[1024];
}String;

void showAll();
void showHelp(bool flag);
void show(char *username);
void change(char *username);

int main(int argc, char **argv)
{
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    Passwd* user = getpwuid(ruid);
    printf("您好！%s\n", user->pw_name);
    if (argc != 3)
    {
        if (argc == 2 && strcmp(argv[1],"-a") == 0)
        {
            printf("浏览全部用户信息\n");
            if(strcmp(user->pw_name,"root") == 0) 
            {
                showAll();
            }
            else
            {
                printf("没有权限！\n");
            }
        }
        else if (argc == 2 && strcmp(argv[1],"-h") == 0)
        {
            showHelp(false);
        }
        else
        {
            showHelp(true);
        }
    }
    else if (strcmp(argv[1],"-s") == 0)
    {
        printf("浏览用户%s信息\n", argv[2]);
        if(strcmp(user->pw_name,"root") == 0 || strcmp(user->pw_name,argv[2]) == 0) 
        {
            show(argv[2]);
        }
        else
        {
            printf("没有权限！\n");
        }
    }
    else if (strcmp(argv[1],"-c") == 0)
    {
        printf("修改用户%s密码\n", argv[2]);
        if(strcmp(user->pw_name,"root") == 0 || strcmp(user->pw_name,argv[2]) == 0) 
        {
            change(argv[2]);
        }
        else
        {
            printf("没有权限！\n");
        }
    }
    else
    {
        showHelp(true);
    }
    printf("运行结束，再见\n");
}

void showAll()
{
    FILE* file = fopen("aaa","r");
    if (file == NULL) 
    {
        printf("aaa文件丢失！\n");
        return;
    }
    char buffer[1024];
    while (fgets(buffer,sizeof(buffer)-1,file) != NULL)
    {
        printf("%s", buffer);
    }
    fclose(file);
}

void show(char *username)
{
    FILE* file = fopen("aaa","r");
    if (file == NULL) 
    {
        printf("aaa文件丢失！\n");
        return;
    }
    char buffer[1024];
    bool has = false;
    while (fgets(buffer,sizeof(buffer)-1,file) != NULL)
    {
        bool flag = true;
        for (int i = 0; buffer[i] != ':' && username[i] != '\0'; i++)
        {
            if (buffer[i] != username[i])
            {
                flag = false;
                break;
            }
        }
        if (flag == true)
        {
            has = true;
            printf("%s", buffer);
            break;
        }
    }
    if (!has)
    {
        printf("用户%s不存在！\n", username);
    }
    fclose(file);
}

void change(char *username)
{
    FILE* file = fopen("aaa","r");
    if (file == NULL) 
    {
        printf("aaa文件丢失！\n");
        return;
    }
    char buffer[1024];
    String s[1000];
    int has = -1;
    int t = 0;
    while (fgets(buffer,sizeof(buffer)-1,file) != NULL)
    {
        memcpy(s[t].a, buffer, strlen(buffer) + 1);
        t++;
        bool flag = true;
        for (int i = 0; buffer[i] != ':' && username[i] != '\0'; i++)
        {
            if (buffer[i] != username[i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            has = t;
            printf("New Password: ");
            char password[1024];
            fgets(password, 1023, stdin);
            printf("Enter Again: ");
            char password1[1024];
            fgets(password1, 1023, stdin);
            if (strcmp(password1, password) != 0) 
            {
                printf("输入错误！修改失败\n");
                fclose(file);
                return;
            }
            memcpy(s[t - 1].a, username, strlen(username) + 1);
            memcpy(&(s[t - 1].a[strlen(username) + 1]), password, strlen(password) + 1);
            s[t - 1].a[strlen(username)] = ':';
        }
    }
    if (has == -1)
    {
        printf("用户%s不存在！\n", username);
        fclose(file);
    }
    else
    {
        file = fopen("aaa", "w");
        for (int i = 0; i < t; i++)
        {
            fputs(s[i].a, file);
        }
        fclose(file);
    }
}

void showHelp(bool flag)
{
    if (flag)
    {
        printf("命令错误！\n");
    }
    printf("\t\"-h\" 查看帮助信息\n");
    printf("\t\"-a\" 显示所有用户信息\n");
    printf("\t\"-s [username]\" 显示用户信息\n");
    printf("\t\"-c [username]\" 修改用户密码\n");
    return;
}
