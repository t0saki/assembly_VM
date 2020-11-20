#https://www.luogu.com.cn/problem/P1075
#NOIp普及组 2012
n=int(input())
flag=False
for i in range(int(n/2+1),1,-1):
    for j in range(2,i):
        if i*j==n:
            flag=True
            break
    if flag:break
print(i)