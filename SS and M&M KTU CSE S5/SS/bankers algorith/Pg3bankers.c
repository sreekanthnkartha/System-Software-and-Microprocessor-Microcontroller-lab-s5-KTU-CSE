#include <stdio.h>
#include <stdlib.h>

int n, m, A[10][10], M[10][10], N[10][10], W[1][10], pid, ch;
int a[10], b[10], c[10], kk, kkk;

void accept()
{
	printf("Input the number of processes: ");
	scanf("%d", &n);
	printf("Input the number of resources: ");
	scanf("%d", &m);
	for (int i = 0; i < n; i++)
	{
		printf("\nProcess  %d:-\n", i);
		printf("allocated :-\n");
		for (int j = 0; j < m; j++)
			scanf("%d", &A[i][j]);
		printf("maximum :-\n");
		for (int j = 0; j < m; j++)
			scanf("%d", &M[i][j]);
	}
	printf("\navailable:-\n");
	for (int j = 0; j < m; j++)
		scanf("%d", &W[0][j]);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			N[i][j] = M[i][j] - A[i][j];
		}
	}
	printf("\nContents of Allocation Matrix:-\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
	printf("\nContents of Maximum Need Matrix:-\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", M[i][j]);
		}
		printf("\n");
	}
	printf("\nContents of Need Matrix:-\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			printf("%d ", N[i][j]);
		}
		printf("\n");
	}
	printf("\nContents of Available Matrix:-\n");
	for (int j = 0; j < m; j++)
		printf("%d ", W[0][j]);
	printf("\n");
}

void res_req(int pid)
{
	int reqmat[1][10];
	int i;
	printf("Input additional request of instances of each resource type needed:-\n");
	for (i = 0; i < m; i++)
		scanf("%d", &reqmat[0][i]);
	for (i = 0; i < m; i++)
	{
		if (reqmat[0][i] > N[pid][i])
		{
			printf("\nInvalid request!\n");
			exit(0);
		}
	}
	for (i = 0; i < m; i++)
	{
		if (reqmat[0][i] > W[0][i])
		{
			printf("\nRequested resources is unavailable!\n");
			exit(0);
		}
	}
	for (i = 0; i < m; i++)
	{
		W[0][i] -= reqmat[0][i];
		A[pid][i] += reqmat[0][i];
		N[pid][i] -= reqmat[0][i];
	}
}

int safety()
{
	int i, j, k, d;
	int F[10], AV[1][10];
	int x = 0, pflag = 0, flag = 0;
	for (i = 0; i < n; i++)
		F[i] = 0;
	for (i = 0; i < m; i++)
		AV[0][i] = W[0][i];
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			if (F[i] == 0)
			{
				flag = 0;
				for (j = 0; j < m; j++)
				{
					if (N[i][j] > AV[0][j])
						flag = 1;
				}
				if (flag == 0 && F[i] == 0)
				{
					for (j = 0; j < m; j++)
						AV[0][j] += A[i][j];
					F[i] = 1;
					pflag++;
					a[x++] = i;
				}
			}
		}
		if (pflag == n)
		{
			d = 1;
			break;
		}
	}
	if (pflag != n)
		d = 0;

	pflag = flag = x = 0;
	for (i = 0; i < n; i++)
		F[i] = 0;
	for (i = 0; i < m; i++)
		AV[0][i] = W[0][i];
	for (k = n - 1; k >= 0; k--)
	{
		for (i = n - 1; i >= 0; i--)
		{
			if (F[i] == 0)
			{
				flag = 0;
				for (j = 0; j < m; j++)
				{
					if (N[i][j] > AV[0][j])
						flag = 1;
				}
				if (flag == 0 && F[i] == 0)
				{
					for (j = 0; j < m; j++)
						AV[0][j] += A[i][j];
					F[i] = 1;
					pflag++;
					b[x++] = i;
				}
			}
		}
		if (pflag == n)
		{
			kk = 1;
			break;
		}
	}
	if (pflag != n)
		kk = 0;

	pflag = flag = x = 0;
	for (i = 0; i < n; i++)
		F[i] = 0;
	for (i = 0; i < m; i++)
		AV[0][i] = W[0][i];
	for (k = n - 1; k >= 0; k--)
	{
		for (i = n - 1; i >= 0; i--)
		{
			if (F[i] == 0)
			{
				flag = 0;
				for (j = 0; j < m; j++)
				{
					if (N[i][j] > AV[0][j])
						flag = 1;
				}
				if (flag == 0 && F[i] == 0)
				{
					for (j = 0; j < m; j++)
						AV[0][j] += A[i][j];
					F[i] = 1;
					pflag++;
					c[x++] = i;
					break;
				}
			}
		}
		if (pflag == n)
		{
			kkk = 1;
			break;
		}
	}
	if (pflag != n)
		kkk = 0;

	if (d == 1)
		return 1;
	else
		return 0;
}

int banker()
{
	int j;
	j = safety();
	if (j != 0)
	{
		printf("\nDetected safety sequence(s):-\n");
		for (int i = 0; i < n; i++)
			printf("P%d ", a[i]);
		printf("\n");
		if (kk != 0)
		{
			for (int i = 0; i < n; i++)
				printf("P%d ", b[i]);
			printf("\n");
		}
		if (kkk != 0)
		{
			for (int i = 0; i < n; i++)
				printf("P%d ", c[i]);
			printf("\n");
		}
	}
	else
	{
		printf("\nDEADLOCK WILL OCCUR.\n");
		return 0;
	}
}

void main()
{
	int okay;
	accept();
	okay = banker();
	if (okay != 0)
	{
		while (1)
		{
			printf("\nAdditional request? Yes - 1 | No - 0\n");
			scanf("%d", &ch);
			if (ch == 1)
			{
				printf("Input process ID: ");
				scanf("%d", &pid);
				res_req(pid);
				okay = banker();
				if (okay == 0)
					exit(0);
			}
			else
				break;
		}
	}
	else
		exit(0);
}
