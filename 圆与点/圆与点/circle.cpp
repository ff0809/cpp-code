#include"circle.h"

void circle::set(int r, int x, int y)
{
	mr = r; mx = x; my = y;
}
int circle::getr()
{
	return mr;
}
int circle::getx()
{
	return mx;
}
int circle::gety()
{
	return my;
}