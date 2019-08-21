#include <stdio.h>

void Merge(int a[],int start,int end)
{
	int mid=(start+end)/2;
	int b[end-start];
	int i,j,k;
	i=start;
	j=mid;
	k=0;
	while(i<mid||j<end)
	{
		//1��iû�� j���� 
		//2��i j��û�� ����a[i]<a[j] 
		if(j==end||i<mid&&a[i]<a[j])  //i<mid �ǡ�i����jû��ʱ�ӵ������� 
			b[k++]=a[i++];
		//1��i���� jû��
		//2��i j��û�� ����a[i]<a[j]������ 
		else
			b[k++]=a[j++];
	}
	//copy back 
	for(i=start,j=0;j<k;)
	a[i++]=b[j++];
}

void MergeSort(int a[],int left,int right)
{
	//��֤Ԫ�ظ�����1 
	if(right-left>1)
	{
		int mid=(right+left)/2;
		MergeSort(a,left,mid);
		MergeSort(a,mid,right);
		Merge(a,left,right);
	}
}

int main(void)
{
	int a[9]={50,62,23,56,23,24,59,1,3};
	int i;
	MergeSort(a,0,9);
	for(i=0;i<9;i++)
	printf("%d\t",a[i]);
	return 0;
}
