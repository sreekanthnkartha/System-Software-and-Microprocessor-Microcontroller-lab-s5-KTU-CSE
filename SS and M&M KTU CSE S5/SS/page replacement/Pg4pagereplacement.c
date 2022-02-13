#include <stdio.h>
#include <stdlib.h>

int i, j, ch, k, n, frameno, page[50], frame[10], move = 0, flag, count = 0, count1, repindex, check[50], hit = 0, coun[50], time[50], least, minTime, temp;

void print()
{
	int x;
	for (x = 0; x < frameno; x++)
		printf("%d\t", frame[x]);
	printf("\n");
}

void clear()
{
	for (i = 0; i < frameno; i++)
		frame[i] = -1;
}

void fifo()
{
	clear();
	printf("Page reference string\tFrames\n");
	for (i = 0; i < n; i++)
	{
		printf("%d\t\t\t", page[i]);
		flag = 0;
		for (j = 0; j < frameno; j++)
		{
			if (page[i] == frame[j])
			{
				flag = 1;
				printf("No replacement\n");
				break;
			}
		}
		if (flag == 0)
		{
			frame[move] = page[i];
			move = (move + 1) % frameno;
			count++;
			print();
		}
	}
	printf("Number of page faults in FIFO = %d\n", count);
}

void lru()
{
	clear();
	move = 0, count = 0;
	for (j = 0; j < 50; j++)
		check[j] = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d\t\t\t", page[i]);
		flag = 0;
		for (j = 0; j < frameno; j++)
		{
			if (page[i] == frame[j])
			{
				flag = 1;
				printf("No replacement\n");
				break;
			}
		}
		if (flag == 0 && count < frameno)
		{
			frame[move] = page[i];
			move = (move + 1) % frameno;
			count++;
			print();
		}
		else if (flag == 0)
		{
			count1 = 0;
			for (j = i - 1; j >= 0; j--)
			{
				for (k = 0; k < frameno; k++)
				{
					if (page[j] == frame[k] && check[page[j]] == 0)
					{
						check[page[j]] = 1;
						count1++;
						repindex = k;
						k = frameno;
					}
				}
				if (count1 == frameno)
					break;
			}
			frame[repindex] = page[i];
			count++;
			print();
		}
		for (j = 0; j < 50; j++)
			check[j] = 0;
	}
	printf("Number of page faults in LRU = %d\n", count);
}

void lfu()
{
	clear();
	for (i = 0; i < n; i++)
	{
		coun[page[i]]++;
		time[page[i]] = i;
		flag = 1;
		least = frame[0];
		for (j = 0; j < frameno; j++)
		{
			if (frame[j] == -1 || frame[j] == page[i])
			{
				if (frame[j] != -1)
					hit++;
				flag = 0;
				frame[j] = page[i];
				break;
			}
			if (coun[least] > coun[frame[j]])
				least = frame[j];
		}
		if (flag)
		{
			minTime = 50;
			for (j = 0; j < frameno; j++)
			{
				if (coun[frame[j]] == coun[least] && time[frame[j]] < minTime)
				{
					temp = j;
					minTime = time[frame[j]];
				}
				coun[frame[temp]] = 0;
				frame[temp] = page[i];
			}
		}
		print();
	}
	printf("Number of page faults in LFU = %d\n", n - hit);
}

void main()
{
	printf("Input the number of pages: ");
	scanf("%d", &n);
	printf("Input the page reference string:-\n");
	for (i = 0; i < n; i++)
		scanf("%d", &page[i]);
	printf("Input the number of frames: ");
	scanf("%d", &frameno);
	printf("\n-----PAGE REPLACEMENT ALGORITHMS-----\n");
	printf("1.FIFO\n");
	printf("2.LRU\n");
	printf("3.LFU\n");
	printf("4.Exit program.\n");
	while (1)
	{
		printf("\nInput your choice: ");
		scanf("%d", &ch);
		switch (ch)
		{
		case 1:
			fifo();
			break;
		case 2:
			lru();
			break;
		case 3:
			lfu();
			break;
		case 4:
			exit(0);
			break;
		default:
			printf("Please input a valid choice.\n");
		}
	}
}
