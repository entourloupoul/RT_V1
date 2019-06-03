#include <stdio.h>

int	main(void)
{
	int	a;
	int	b;
	double	f;
	double g;

	f = 0.8;
	b = 1;
	g = b * f;
	a = 0xFFFBFF;
	printf("1:%x\n2:%x\n3:%x\n", a & 0xFF0000, a & 0xFF00, a & 0xFF);
	printf("essai:%d\n%f\n", b, g);
	return (1);
}
