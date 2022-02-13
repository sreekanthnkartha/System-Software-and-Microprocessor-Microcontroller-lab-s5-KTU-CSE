#include <stdio.h>
#include <stdlib.h>

struct proc
{
	int pid, at, bt, ct, tt, wt, prio, flag, btc;
} p[15], temp;

int n, ch;

void inputProc()
{
	printf("\nInput the number of processes: ");
	scanf("%d", &n);
	printf("\nInput the arrival time and burst time of each process:-\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &p[i].at, &p[i].bt);
		p[i].flag = 0;
		p[i].pid = i + 1;
	}
}

void inputPriProc()
{
	printf("\nInput the number of processes: ");
	scanf("%d", &n);
	printf("\nInput the arrival time, burst time & priority of each process:-\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].prio);
		p[i].flag = 0;
		p[i].pid = i + 1;
	}
}

void arrId()
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (p[j].pid > p[j + 1].pid)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}

void display()
{
	arrId();
	printf("\nPID\tAT\tBT\tWT\tTT\tCT\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].wt, p[i].tt, p[i].ct);
	}
}

void displayPri()
{
	arrId();
	printf("\nPID\tAT\tBT\tPrio\tWT\tTT\tCT\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].prio, p[i].wt, p[i].tt, p[i].ct);
	}
}

void arrAr()
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (p[j].at > p[j + 1].at)
			{
				temp = p[j];
				p[j] = p[j + 1];
				p[j + 1] = temp;
			}
		}
	}
}

void fcfs()
{
	inputProc();
	arrAr();
	int time = 0;
	float sumt = 0, sumw = 0;
	for (int i = 0; i < n; i++)
	{
		if (time < p[i].at)
			time = p[i].at;
		time += p[i].bt;
		p[i].ct = time;
		p[i].tt = p[i].ct - p[i].at;
		p[i].wt = p[i].tt - p[i].bt;
		sumt += p[i].tt;
		sumw += p[i].wt;
	}
	display();
	printf("\nAverage waiting time = %.2f", sumw / (float)n);
	printf("\nAverage turnaround time = %.2f\n", sumt / (float)n);
}

int bi(int time)
{
	int ind, min = 9999;
	for (int i = 0; i < n; i++)
	{
		if (p[i].at <= time && p[i].flag == 0)
		{
			if (p[i].bt < min)
			{
				min = p[i].bt;
				ind = i;
			}
		}
	}
	return ind;
}

void sjf()
{
	inputProc();
	arrAr();
	int time = 0, count = 0, ind;
	float sumt = 0, sumw = 0;
	while (count != n)
	{
		for (int i = 0; i < n; i++)
		{
			if (time < p[i].at)
				time += p[i].at;
			ind = bi(time);
			time += p[ind].bt;
			p[ind].ct = time;
			p[ind].tt = p[ind].ct - p[ind].at;
			p[ind].wt = p[ind].tt - p[ind].bt;
			sumt += p[ind].tt;
			sumw += p[ind].wt;
			count++;
			p[ind].flag = 1;
		}
	}
	display();
	printf("\nAverage waiting time = %.2f", sumw / (float)n);
	printf("\nAverage turnaround time = %.2f\n", sumt / (float)n);
}

int queue[100];
int t = -1, h = -1;

int add(int q)
{
	if (h == -1)
	{
		h = 0;
		t = 0;
	}
	else
		h++;
	if (h == 100)
		h = 0;
	queue[h] = q;
}

int pop()
{
	if (t == -1)
		return -1;
	else
	{
		t++;
		return queue[t - 1];
	}
}

void rr()
{
	int tq;
	printf("\nInput the time quantum: ");
	scanf("%d", &tq);
	inputProc();
	arrAr();
	for (int i = 0; i < n; i++)
	{
		p[i].btc = p[i].bt;
	}
	int time = p[0].at, count = -1, num = n;
	float sumt = 0, sumw = 0;
	while (num > 0)
	{
		int q = pop();
		if (q == -1)
		{
			count++;
			q = count;
		}
		printf("Process %d ", p[q].pid);
		if (p[q].bt > tq)
		{
			p[q].bt -= tq;
			time += tq;
			printf("Time: %d - %d\n", time - tq, time);
			while (count < n - 1)
			{
				if (p[count + 1].at <= time)
				{
					count++;
					add(count);
				}
				else
					break;
			}
			add(q);
		}
		else
		{
			sumw += (time - p[q].at - (p[q].btc - p[q].bt));
			time += p[q].bt;
			sumt += time - p[q].at;
			printf("Time: %d - %d\n", time - p[q].bt, time);
			p[q].bt = 0;
			num--;
			while (count < n - 1)
			{
				if (p[count + 1].at <= time)
				{
					count++;
					add(count);
				}
				else
					break;
			}
		}
	}
	t = h = -1;
	printf("\nAverage waiting time = %.2f", sumw / (float)n);
	printf("\nAverage turnaround time = %.2f\n", sumt / (float)n);
	/*
	while(count!=n)
	{
		for(int i=0;i<n;i++)
		{
			if(time<p[i].at) time+=p[i].at;
			time+=p[i].bt;
			p[i].ct=time;
			p[i].tt=p[i].ct-p[i].at;
			p[i].wt=p[i].tt-p[i].bt;
			sumt+=p[i].tt;
			sumw+=p[i].wt;
			count++;
			p[i].flag=1;
		}
	}
	display();
	printf("\nAverage waiting time = %.2f",sumw/(float)n);
	printf("\nAverage turnaround time = %.2f\n",sumt/(float)n);
	*/
}

int pi(int time)
{
	int ind, min = 9999;
	for (int i = 0; i < n; i++)
	{
		if (p[i].at <= time && p[i].flag == 0)
		{
			if (p[i].prio < min)
			{
				min = p[i].prio;
				ind = i;
			}
		}
	}
	return ind;
}

void pr()
{
	inputPriProc();
	arrAr();
	int time = 0, count = 0, ind;
	float sumt = 0, sumw = 0;
	while (count != n)
	{
		for (int i = 0; i < n; i++)
		{
			if (time < p[i].at)
				time += p[i].at;
			ind = pi(time);
			time += p[ind].bt;
			p[ind].ct = time;
			p[ind].tt = p[ind].ct - p[ind].at;
			p[ind].wt = p[ind].tt - p[ind].bt;
			sumt += p[ind].tt;
			sumw += p[ind].wt;
			count++;
			p[ind].flag = 1;
		}
	}
	displayPri();
	printf("\nAverage waiting time = %.2f", sumw / (float)n);
	printf("\nAverage turnaround time = %.2f\n", sumt / (float)n);
}

void main()
{
	printf("1.FCFS\n");
	printf("2.SJF\n");
	printf("3.Round robin\n");
	printf("4.Priority\n");
	printf("5.Exit\n");
	while (1)
	{
		printf("\nInput your choice: ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			fcfs();
			break;
		case 2:
			sjf();
			break;
		case 3:
			rr();
			break;
		case 4:
			pr();
			break;
		case 5:
			exit(0);
			break;
		default:
			printf("Please input a valid choice.\n");
		}
	}
}
