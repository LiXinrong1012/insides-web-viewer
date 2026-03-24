
#include <QtCore/QCoreApplication>
#include <QDebug>

#include "gtest/gtest.h"
//#include "vld.h"

#include "Base/activeviewobject.h"
#include "Base/PixmapManager.h"

using namespace Base;

int Foo(int a, int b)
{
	if (a == 0 || b == 0)
	{
		throw "don't do that";
	}
	int c = a % b;
	if (c == 0)
		return b;
	return Foo(b, c);
}
TEST(FooTest, HandleNoneZeroInput)
{
	EXPECT_EQ(2, Foo(4, 10));
	EXPECT_EQ(6, Foo(30, 18));
}

int main(int argc, char *argv[])
{
	int *aaa=new int[10];
	QCoreApplication a(argc, argv);

	QList<int> myVec;
	qDebug("%d %d",myVec.size(),sizeof(myVec));
	//ActiveViewObject::instance();
	//PixmapManager();

	//testing::InitGoogleTest(&argc, argv);
	//RUN_ALL_TESTS();

	return a.exec();
}
