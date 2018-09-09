#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */


//------------------------------------------
//√∞≈›≈≈–Ú –°µΩ¥Û 
void Sort_Bubble_Down(int* a,int len)
{
	int i = 0;
	int j = 0;
	for(i=0;i<len;i++)
	{
		for(j=i+1;j<len;j++)
		{
			if(a[i]>a[j])
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;	
			}	
		}	
	}
}

void Sort_Bubble_Up(int* a,int len)
{
	int i = 0;
	int j = 0;
	for(i=0;i<len;i++)
	{
		for(j=i+1;j<len;j++)
		{
			if(a[i]<a[j])
			{
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;	
			}	
		}	
	}
}
//------------------------------------------
//------------------------------------------
//—°‘Ò≈≈–Ú 
void Sort_Select_Down(int* a,int len)
{
	int i = 0;
	int j = 0;
	for(i=0;i<len;i++)
	{
		int k = i;
		for(j=i+1;j<len;j++)
		{
			if(a[k]>a[j])
			{
				k = j;	
			}	
		}	
		if(k!=i)
		{
			int temp = a[i];
			a[i] = a[k];
			a[k] = temp;	
		}
	}
}

void Sort_Select_Up(int* a,int len)
{
	int i = 0;
	int j = 0;
	for(i=0;i<len;i++)
	{
		int k = i;
		for(j=i+1;j<len;j++)
		{
			if(a[k]<a[j])
			{
				k = j;	
			}	
		}
		if(k!=i)
		{
			int temp = a[i];
			a[i] = a[k];
			a[k] = temp;	
		}	
	}
}
//------------------------------------------
//------------------------------------------
//≤Â»Î≈≈–Ú
void Sort_Insert_Down(int* a,int len)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;
	for(i=0;i<len;i++)
	{
		k = i;
		temp = a[i];
		for(j=i-1;j>=0;j--)
		{
			if(a[j]>temp)
			{
				a[j+1] = a[j];
				k = j;	
			}	
		}
		a[k] = temp;	
	}
} 

void Sort_Insert_Up(int* a,int len)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;
	for(i=0;i<len;i++)
	{
		k = i;
		temp = a[i];
		for(j=i-1;j>=0;j--)
		{
			if(a[j]<temp)
			{
				a[j+1] = a[j];
				k = j;	
			}	
		}
		a[k] = temp;	
	}
}
//------------------------------------------
//------------------------------------------
//œ£∂˚≈≈–Ú
void Sort_Shell_Down(int* a,int len)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;
	int gap = len;
	do
	{
		gap = gap/3 + 1;
		for(i=gap;i<len;i=i+gap)
		{
			k = i;
			temp = a[i];
			for(j=i-gap;j>=0;j=j-gap)
			{
				if(a[j]>temp)
				{
					a[j+gap] = a[j];
					k = j;	
				}	
			}	
			a[k] = temp;
		}
		
	}while(gap>1);
}
 
void Sort_Shell_Up(int* a,int len)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int temp = 0;
	int gap = len;
	do
	{
		gap = gap/3 + 1;
		for(i=gap;i<len;i=i+gap)
		{
			k = i;
			temp = a[i];
			for(j=i-gap;j>=0;j=j-gap)
			{
				if(a[j]<temp)
				{
					a[j+gap] = a[j];
					k = j;
				}	
			}	
			a[k] = temp;
		}
		
	}while(gap>1);
}
//------------------------------------------
//------------------------------------------
//øÏÀŸ≈≈–Ú
void Swap(int* a,int i,int j)
{
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}
int Partition_Down(int* a,int low,int high)
{
	int pv = a[low];
	while(low<high)
	{
		while((low<high)&&(a[high]>pv))
		{
			high--;	
		}	
		Swap(a,low,high);
		while((low<high)&&(a[low]<pv))
		{
			low++;	
		}
		Swap(a,low,high);
	}
	return low;
}
void Quick_Down(int* a,int low,int high)
{
	if(low<high)
	{
		int pv = Partition_Down(a,low,high);
		Quick_Down(a,low,pv-1);
		Quick_Down(a,pv+1,high);	
	}
}
void Sort_Quick_Down(int* a,int len)
{
	Quick_Down(a,0,len-1);
} 
//---

int Partition_Up(int* a,int low,int high)
{
	int pv = a[low];
	while(low<high)
	{
		while((low<high)&&(a[high]<pv))
		{
			high--;	
		}	
		Swap(a,low,high);
		while((low<high)&&(a[low]>pv))
		{
			low++;	
		}
		Swap(a,low,high);
	}
}
void Quick_Up(int* a,int low,int high)
{
	if(low<high)
	{
		int pv = Partition_Up(a,low,high);
		Quick_Up(a,low,pv-1);
		Quick_Up(a,pv+1,high);	
	}
}
void Sort_Quick_Up(int* a,int len)
{
	Quick_Up(a,0,len-1);
}
//------------------------------------------
//------------------------------------------
//πÈ≤¢≈≈–Ú 

//------------------------------------------
//------------------------------------------
int main(int argc, char *argv[]) 
{
	int a[10] = {8,2,9,5,6,1,4,0,7,3};
	int length = sizeof(a)/sizeof(int);
	int i = 0;
	printf("Before sorting ...\n");
	for(i=0;i<length;i++)
	{
		printf("a[%d] = %d\n",i,a[i]);	
	}
//	Sort_Bubble_Down(a,length);
//	Sort_Select_Down(a,length);
//	Sort_Insert_Down(a,length);
//	Sort_Shell_Down(a,length);
	Sort_Quick_Down(a,length);
	printf("After sorting(down) ...\n");
	for(i=0;i<length;i++)
	{
		printf("a[%d] = %d\n",i,a[i]);	
	}
	
//	Sort_Bubble_Up(a,length);
//	Sort_Select_Up(a,length);
//	Sort_Insert_Up(a,length);
//	Sort_Shell_Up(a,length);
	Sort_Quick_Up(a,length);
	printf("After sorting(up) ...\n");
	for(i=0;i<length;i++)
	{
		printf("a[%d] = %d\n",i,a[i]);	
	}
	return 0;
}
