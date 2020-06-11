/* 
* 代码目的: 实现elgamal密码体制的加解密、求公钥这三种功能功能;
* 作者：李彦霖 1120172140
* 时间： 23:44/2019/11/22
* 原创声明：我承诺代码完全由本人亲自编写
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
typedef unsigned long ulnum;

/* 
* 功能：求模p的指数幂
* 参数：a-底数，x-指数，p-模数
* 返回值：(a^x mod p)
*/
ulnum getPower(ulnum a, ulnum x, ulnum p)
{
	ulnum base = a; // 初始化底数
	ulnum index = x; // 初始化指数
	ulnum ans = 1;

	while (index > 0)
	{
		if (index % 2 == 1) ans = (ans * base) % p;
		base = (base * base) % p;
		index /= 2;
	}

	return ans;
}

/*
* 功能：求模p的离散对数
* 参数：y-y的对数那个y，g-底数，p-模数
* 返回值：y模p的对数
*/
ulnum getDescretelog(ulnum y, ulnum g, ulnum p)
{
	ulnum ans = 1;
	ulnum mod = 0;
	while (ans < p)
	{
		// 穷举，通过求幂比较结果是否与y相同来求离散对数
		mod = getPower(g, ans, p);
		if (mod == y) return ans;
		ans += 1;
	}

	return 0;
}

/*
* 功能：求模p的逆元
* 参数：x-需要求逆的数，p-模数
* 返回值： y mod p 的逆元
*/
ulnum getInverseele(ulnum x, ulnum p)
{
	ulnum ans = 1;
	ulnum mod = 0;
	while (ans < p)
	{
		// 依然是通过穷举来判断是否是逆元，因为模p的逆元一定比p小，所以只需要判断p-1次
		mod = (x * ans) % p;
		if (ans == 1) return ans;
		x += 1;
	}

	return 0;
}

/*
* 功能：选择模p的随机数
* 参数：p-模数
* 返回值：随机数
*/
ulnum getRandm(ulnum p)
{
	ulnum ans = rand() % (p - 1) + 1;
	return ans;
}

void encode(ulnum p, ulnum g)
{
	ulnum m; // 明文
	ulnum c1, c2; // 密文
	ulnum pubk; // 接收方公钥
	ulnum randm = getRandm(p);

	printf("请输入明文： ");
	scanf_s("%lu", &m);
	printf("请输入接收方公钥： ");
	scanf_s("%lu", &pubk);

	c1 = getPower(g, randm, p);
	c2 = (m * getPower(pubk, randm, p)) % p;

	printf("加密完成，密文是：(%lu, %lu)\n", c1, c2);
}

void decode(ulnum p)
{
	ulnum c1, c2;
	ulnum m;
	ulnum privk;
	ulnum x;
	ulnum invx;

	printf("请输入需要解密的密文： ");
	scanf_s("%lu %lu", &c1, &c2);
	printf("请输入您的私钥： ");
	scanf_s("%lu", &privk);

	x = getPower(c1, privk, p);
	invx = getInverseele(x, p);
	m = (c2 * invx) % p;

	printf("解密完成，密文(%lu,%lu)对应的明文是%lu\n", c1, c2, m);
}

void getkey(ulnum p, ulnum g)
{
	ulnum privk;
	ulnum pubk;

	printf("请输入您的私钥： ");
	scanf_s("%lu", &privk);
	
	pubk = getPower(g, privk, p);
	
	printf("您的公钥是： %lu\n", pubk);
}

int main()
{
	char mood; //选择操作模式
	ulnum p = 65537; // 缺省选择模65537进行运算
	ulnum g = 3; // 65537的本原根是3
	
	while (true)
	{
		system("cls");
		printf("\n默认模65537，本原根为3\n");
		printf("请选择操作模式：e(加密) | d(解密) | k(求公钥) | c(退出程序):");
		scanf_s("%c", &mood);
		switch (mood)
		{
		case 'e': {
				encode(p, g);
				system("pause");
				break;
			}
		case 'd': {
				decode(p);
				system("pause");
				break;
			}
		case 'k': {
				getkey(p, g);
				system("pause");
				break;
			}

			case 'c':
				return 0;
		}
		getchar();
	}

	return 0;
}
