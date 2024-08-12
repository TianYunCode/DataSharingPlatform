#if !defined(__FTPLIB_H)
#define __FTPLIB_H

#if defined(__unix__) || defined(VMS)
#define GLOBALDEF
#define GLOBALREF extern
#elif defined(_WIN32)
#if defined BUILDING_LIBRARY
#define GLOBALDEF __declspec(dllexport)
#define GLOBALREF __declspec(dllexport)
#else
#define GLOBALREF __declspec(dllimport)
#endif
#endif

#include <limits.h>
#include <inttypes.h>

// FtpAccess（）类型代码
#define FTPLIB_DIR 1
#define FTPLIB_DIR_VERBOSE 2
#define FTPLIB_FILE_READ 3
#define FTPLIB_FILE_WRITE 4

// FtpAccess（）模式代码
#define FTPLIB_ASCII 'A'
#define FTPLIB_IMAGE 'I'
#define FTPLIB_TEXT FTPLIB_ASCII
#define FTPLIB_BINARY FTPLIB_IMAGE

// 连接模式
#define FTPLIB_PASSIVE 1
#define FTPLIB_PORT 2

// 连接选项名称
#define FTPLIB_CONNMODE 1
#define FTPLIB_CALLBACK 2
#define FTPLIB_IDLETIME 3
#define FTPLIB_CALLBACKARG 4
#define FTPLIB_CALLBACKBYTES 5

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(__UINT64_MAX)
    typedef uint64_t fsz_t;
#else
typedef uint32_t fsz_t;
#endif

    typedef struct NetBuf netbuf;
    typedef int (*FtpCallback)(netbuf *nControl, fsz_t xfered, void *arg);

    typedef struct FtpCallbackOptions
    {
        FtpCallback cbFunc;        // 要调用的函数
        void *cbArg;               // 传递给函数的参数
        unsigned int bytesXferred; // 如果转移了这个字节数，则回调
        unsigned int idleTime;     // 如果已经过了这么多毫秒，请回调
    } FtpCallbackOptions;

    GLOBALREF int ftplib_debug;
    GLOBALREF void FtpInit(void);                                                                   // 适用于需要它的愚蠢操作系统的FtpInit（Windows NT）
    GLOBALREF char *FtpLastResponse(netbuf *nControl);                                              // 返回指向上次收到的响应的指针
    GLOBALREF int FtpConnect(const char *host, netbuf **nControl);                                  // 连接到远程服务器
    GLOBALREF int FtpOptions(int opt, long val, netbuf *nControl);                                  // 更改连接选项
    GLOBALREF int FtpSetCallback(const FtpCallbackOptions *opt, netbuf *nControl);                  // 设置回调
    GLOBALREF int FtpClearCallback(netbuf *nControl);                                               // 清除回调
    GLOBALREF int FtpLogin(const char *user, const char *pass, netbuf *nControl);                   // 登录到远程服务器
    GLOBALREF int FtpAccess(const char *path, int typ, int mode, netbuf *nControl, netbuf **nData); // 返回数据流的句柄
    GLOBALREF int FtpRead(void *buf, int max, netbuf *nData);                                       // 从数据连接读取
    GLOBALREF int FtpWrite(const void *buf, int len, netbuf *nData);                                // 写入数据连接
    GLOBALREF int FtpClose(netbuf *nData);                                                          // 关闭数据连接
    GLOBALREF int FtpSite(const char *cmd, netbuf *nControl);                                       // 发送SITE命令
    GLOBALREF int FtpSysType(char *buf, int max, netbuf *nControl);                                 // 发送SYST命令
    GLOBALREF int FtpMkdir(const char *path, netbuf *nControl);                                     // 在服务器上创建一个目录
    GLOBALREF int FtpChdir(const char *path, netbuf *nControl);                                     // 在远程更改路径
    GLOBALREF int FtpCDUp(netbuf *nControl);                                                        // 移动到远程的父目录
    GLOBALREF int FtpRmdir(const char *path, netbuf *nControl);                                     // 删除远程目录
    GLOBALREF int FtpPwd(char *path, int max, netbuf *nControl);                                    // 在远程获取工作目录
    GLOBALREF int FtpNlst(const char *output, const char *path, netbuf *nControl);                  // 发出NLST命令并写入输出响应
    GLOBALREF int FtpDir(const char *output, const char *path, netbuf *nControl);                   // 发出LIST命令并写入输出响应
    GLOBALREF int FtpSize(const char *path, unsigned int *size, char mode, netbuf *nControl);       // 确定远程文件的大小
#if defined(__UINT64_MAX)
    GLOBALREF int FtpSizeLong(const char *path, fsz_t *size, char mode, netbuf *nControl);   // 确定远程文件的大小
#endif
    GLOBALREF int FtpModDate(const char *path, char *dt, int max, netbuf *nControl);         // 确定远程文件的修改日期
    GLOBALREF int FtpGet(const char *output, const char *path, char mode, netbuf *nControl); // 发出GET命令并将接收到的数据写入输出
    GLOBALREF int FtpPut(const char *input, const char *path, char mode, netbuf *nControl);  // 发出PUT命令并从输入发送数据
    GLOBALREF int FtpRename(const char *src, const char *dst, netbuf *nControl);             // 在远程重命名文件
    GLOBALREF int FtpDelete(const char *fnm, netbuf *nControl);                              // 在远程删除文件
    GLOBALREF void FtpQuit(netbuf *nControl);                                                // 从遥控器断开连接

#ifdef __cplusplus
};
#endif

#endif
