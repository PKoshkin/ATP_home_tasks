#ifndef DEQUE_TEST_KOSHKIN_PAVEL_493
#define DEQUE_TEST_KOSHKIN_PAVEL_493

#include "gtest\gtest.h"
#include "deque.h"
#include <deque> // Для сравнительного теста

TEST(DequeTest, push_back)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_back(temp);
		stdDeq.push_back(temp);

		EXPECT_EQ(myDeq.size(), stdDeq.size());
		EXPECT_EQ(myDeq.empty(), stdDeq.empty());
		EXPECT_EQ(myDeq.front(), stdDeq.front());
		EXPECT_EQ(myDeq.back(), stdDeq.back());
	}

	for (int i = 0; i < 1000; i++)
	{
		EXPECT_EQ(myDeq[i], stdDeq[i]);
	}
}

TEST(DequeTest, push_front)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_front(temp);
		stdDeq.push_front(temp);

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (int i = 0; i < 1000; i++)
	{
		ASSERT_EQ(myDeq[i], stdDeq[i]);
	}
}

TEST(DequeTest, push)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 1000; i++)
	{
		int type = rand() % 2;

		if (type == 0) // push_back
		{
			int value = rand();
			myDeq.push_back(value);
			stdDeq.push_back(value);
		}
		else // push_back
		{
			int value = rand();
			myDeq.push_front(value);
			stdDeq.push_front(value);
		}

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (size_t i = 0; i < myDeq.size(); i++)
	{
		ASSERT_EQ(myDeq[i], stdDeq[i]);
	}
}

TEST(DequeTest, front)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_front(temp);
		stdDeq.push_front(temp);

		ASSERT_EQ(myDeq[i], stdDeq[i]);
		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (size_t i = 0; i < 1000; i++)
	{
		myDeq.pop_front();
		stdDeq.pop_front();

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	ASSERT_EQ(myDeq.size(), stdDeq.size());
	ASSERT_EQ(myDeq.empty(), stdDeq.empty());
}

TEST(DequeTest, back)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_back(temp);
		stdDeq.push_back(temp);

		ASSERT_EQ(myDeq[i], stdDeq[i]);
		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (size_t i = 0; i < 1000; i++)
	{
		myDeq.pop_back();
		stdDeq.pop_back();

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	ASSERT_EQ(myDeq.size(), stdDeq.size());
	ASSERT_EQ(myDeq.empty(), stdDeq.empty());
}

TEST(DequeTest, frontBack)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_front(temp);
		stdDeq.push_front(temp);

		ASSERT_EQ(myDeq[i], stdDeq[i]);
		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (size_t i = 0; i < 1000; i++)
	{
		myDeq.pop_back();
		stdDeq.pop_back();

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	ASSERT_EQ(myDeq.size(), stdDeq.size());
	ASSERT_EQ(myDeq.empty(), stdDeq.empty());
}

TEST(DequeTest, backFront)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		myDeq.push_back(temp);
		stdDeq.push_back(temp);

		ASSERT_EQ(myDeq[i], stdDeq[i]);
		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	for (size_t i = 0; i < 1000; i++)
	{
		myDeq.pop_front();
		stdDeq.pop_front();

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		ASSERT_EQ(myDeq.front(), stdDeq.front());
		ASSERT_EQ(myDeq.back(), stdDeq.back());
	}

	ASSERT_EQ(myDeq.size(), stdDeq.size());
	ASSERT_EQ(myDeq.empty(), stdDeq.empty());
}
*/

TEST(DequeTest, structure)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 10000000; i++)
	{
		int type;
		if (myDeq.empty())
			type = rand() % 2;
		else
			type = rand() % 4;

		if (type == 0) // push_back
		{
			int value = rand();
			myDeq.push_back(value);
			stdDeq.push_back(value);
		}
		else if (type == 1) // push_front
		{
			int value = rand();
			myDeq.push_front(value);
			stdDeq.push_front(value);
		}
		else if (type == 2) // pop_back
		{
			myDeq.pop_back();
			stdDeq.pop_back();
		}
		else // pop_front
		{
			myDeq.pop_front();
			stdDeq.pop_front();
		}

		ASSERT_EQ(myDeq.size(), stdDeq.size());
		ASSERT_EQ(myDeq.empty(), stdDeq.empty());
		if (!myDeq.empty())
		{
			ASSERT_EQ(myDeq.front(), stdDeq.front());
			ASSERT_EQ(myDeq.back(), stdDeq.back());
		}
	}

	for (size_t i = 0; i < myDeq.size(); i++)
	{
		ASSERT_EQ(myDeq[i], stdDeq[i]);
	}
}


TEST(DequeTest, time)
{
	Deque<int> myDeq;

	srand(time(NULL));
	int c = 1000;

	for (int n = 100000; n < 1000000000; n *= 10)
	{
		clock_t time = clock();
		for (int i = 0; i < n; i++)
		{
			int type;
			if (myDeq.empty())
				type = rand() % 2;
			else
				type = rand() % 4;

			if (type == 0) // push_back
			{
				int value = rand();
				myDeq.push_back(value);
			}
			else if (type == 1) // push_front
			{
				int value = rand();
				myDeq.push_front(value);
			}
			else if (type == 2) // pop_back
			{
				myDeq.pop_back();
			}
			else // pop_front
			{
				myDeq.pop_front();
			}
		}
		time = clock() - time;
		ASSERT_EQ(time * c < n, true);
	}
}

#endif //DEQUE_KOSHKIN_PAVEL_493
