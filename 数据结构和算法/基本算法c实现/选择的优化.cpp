//ѡ������
//һ�ξ�ѡ�����С�ĺ�����
#include<stdio.h>
void SelectSort2(int a[],int n)
{
    int left = 0;
    int right = n-1;
    int t;
    while (left < right)
    {
        int min = left;
        int max = right;
        for (int i = left; i <= right ; i++)
        {
            if (a[i] < a[min])
                min = i;
            if(a[i] > a[max])
                max = i;
        }
        //������������������ֵ����Сλ�ã���Сֵ�����λ�á�
        t=a[max];
        a[max]=a[right];
        a[right]=t;

        if (min == right)
        {
            min = max;
        }
         t=a[min];
         a[min]=a[left];
         a[left]=t;
        left++;
        right--;
    }
}
int main(void)
{
	int a[8]={9,2,5,8,4,7,6,1};
	int i;
	SelectSort2(a,8);
	for(i=0;i<8;i++)
		printf("%5d",a[i]);
	return 0; 
}
