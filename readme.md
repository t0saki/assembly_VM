# 计算机原理作业：虚拟机

**tosaki**

## 基本设定
----
该程序命令均为大写字母，并假设输入的参数为变量代号(仅支持字母)或内存地址(仅支持十进制数字)，命令、变量之间可用空格或半角逗号隔开。  
对于布尔类型，值>0的为True，否则为False。  
该程序可在运行开始后对内存和外存进行虚拟化。为了方便调试起见，外部I/O暂时被编写为键盘/屏幕，故外存暂未实现。  
由于本人对汇编语言实在是不熟悉，故很多命令可能不符合汇编的表达形式，还请谅解。


## 语句说明
----
- LD,ST:从内存相应地址中读取/存入
- ADD,SUB,MUL,DIV:加减乘除四则运算
- JMP,JC:无条件/条件跳转
- AND,OR,NOT:布尔与/或运算
- MOV:复制值
- IN,OUT:外部输出输出

## 样例
----
借此程序可实现很多功能，譬如该NOIp 2012 普及组的题目:
[P1075 质因数分解](https://www.luogu.com.cn/problem/P1075)
此题可以考验该程序跳转、条件判断的实现。  
以下代码均可在同目录下找到。

#### 等效Python代码
```python
n=int(input())
flag=False
for i in range(int(n/2+1),1,-1):
    for j in range(2,i):
        if i*j==n:
            flag=True
            break
    if flag:break
print(i)
```

#### 自创代码
```asm
INT N
IN N
INT I
INT J
INT RNGI
INT RNGJ
MOV RNGI N
INT TMP
LD TMP 0
ADD RNGI TMP
LD TMP 1
DIV RNGI TMP
INT TMP1
INT TMP2

MV I RNGI
istart:
    LD J 1
    jstart:
        MOV TMP I
        MUL TMP J
        MOV TMP2 N
        SUB TMP2 TMP
        SUB TMP N
        OR TMP TMP2
        NOT TMP TMP
        JC TMP endf
    forjend:
    LD TMP 0
    ADD J TMP
    MOV TMP I
    SUB TMP J
    JC TMP jstart
LD TMP 0
SUB I TMP
MOV TMP1 I
SUB TMP1 TMP
JC TMP1 istart
endf:
OUT I
```
根据视频验证，该程序能正常实现功能。
