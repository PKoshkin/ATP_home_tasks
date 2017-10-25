#include <gtest\gtest.h>
#include <algorithm>
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


TEST(DequeTest, structure)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 1000000; i++)
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

	for (int n = 100000; n < 100000000; n *= 10)
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

TEST(DequeTest, iterator)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		int type = rand() % 2;
		if (type == 0)
		{
			myDeq.push_back(temp);
			stdDeq.push_back(temp);
		}
		else
		{
			myDeq.push_front(temp);
			stdDeq.push_front(temp);
		}
	}

	std::sort(myDeq.begin(), myDeq.end());
	std::sort(stdDeq.begin(), stdDeq.end());

	auto myIt = myDeq.begin();
	auto stdIt = stdDeq.begin();

	while (stdIt != stdDeq.end())
	{
		ASSERT_EQ(*myIt, *stdIt);
		stdIt++;
		myIt++;
	}
}

TEST(DequeTest, revIterator)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		int type = rand() % 2;
		if (type == 0)
		{
			myDeq.push_back(temp);
			stdDeq.push_back(temp);
		}
		else
		{
			myDeq.push_front(temp);
			stdDeq.push_front(temp);
		}
	}

	std::sort(myDeq.rbegin(), myDeq.rend());
	std::sort(stdDeq.rbegin(), stdDeq.rend());

	auto myIt = myDeq.rbegin();
	auto stdIt = stdDeq.rbegin();

	while (stdIt != stdDeq.rend())
	{
		ASSERT_EQ(*myIt, *stdIt);
		stdIt++;
		myIt++;
	}
}

TEST(DequeTest, randIterator)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		int type = rand() % 2;
		if (type == 0)
		{
			myDeq.push_back(temp);
			stdDeq.push_back(temp);
		}
		else
		{
			myDeq.push_front(temp);
			stdDeq.push_front(temp);
		}
	}

	int pos = 50000;
	auto myIt = myDeq.begin() + pos;
	auto stdIt = stdDeq.begin() + pos;

	int temp;
	for (int i = 0; i < 1000; i++)
	{
		temp = rand() % 40000;
		ASSERT_EQ(myIt[temp], stdIt[temp]);
	}

	for (int i = 0; i < 100000; i++)
	{
		int type = rand() % 9;

		if (type == 0)
		{
			if (pos < 100000 - 1)
			{
				myIt++;
				stdIt++;
				pos++;
			}
		}
		else if (type == 1)
		{
			if (pos < 100000 - 1)
			{
				++myIt;
				++stdIt;
				++pos;
			}
		}
		else if (type == 2)
		{
			if (pos > 0)
			{
				myIt--;
				stdIt--;
				pos--;
			}
		}
		else if (type == 3)
		{
			if (pos > 0)
			{
				--myIt;
				--stdIt;
				--pos;
			}
		}
		else if (type == 4)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt += value;
				stdIt += value;
				pos += value;
			}
		}
		else if (type == 5)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt = myIt + value;
				stdIt = stdIt + value;
				pos = pos + value;
			}
		}
		else if (type == 6)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt = value + myIt;
				stdIt = value + stdIt;
				pos = value + pos;
			}
		}
		else if (type == 7)
		{
			int value = rand() % 100;
			if (pos - value > 0)
			{
				myIt -= value;
				stdIt -= value;
				pos -= value;
			}
		}
		else
		{
			int value = rand() % 100;
			if (pos - value > 0)
			{
				myIt = myIt - value;
				stdIt = stdIt - value;
				pos = pos - value;
			}
		}

		temp = rand() % 100000;
		auto myTempIt = myDeq.begin() + temp;
		auto stdTempIt = stdDeq.begin() + temp;
		ASSERT_EQ(myIt < myTempIt, stdIt < stdTempIt);
		ASSERT_EQ(myIt > myTempIt, stdIt > stdTempIt);
		ASSERT_EQ(myIt <= myTempIt, stdIt <= stdTempIt);
		ASSERT_EQ(myIt >= myTempIt, stdIt >= stdTempIt);
		ASSERT_EQ(myIt == myTempIt, stdIt == stdTempIt);
		ASSERT_EQ(myIt != myTempIt, stdIt != stdTempIt);
		ASSERT_EQ(*myIt, *stdIt);
	}
}

TEST(DequeTest, randRevIterator)
{
	std::deque<int> stdDeq;
	Deque<int> myDeq;

	srand(time(NULL));

	for (int i = 0; i < 100000; i++)
	{
		int temp = rand();
		int type = rand() % 2;
		if (type == 0)
		{
			myDeq.push_back(temp);
			stdDeq.push_back(temp);
		}
		else
		{
			myDeq.push_front(temp);
			stdDeq.push_front(temp);
		}
	}

	int pos = 50000;
	auto myIt = myDeq.rbegin() + pos;
	auto stdIt = stdDeq.rbegin() + pos;

	int temp;
	for (int i = 0; i < 1000; i++)
	{
		temp = rand() % 40000;
		ASSERT_EQ(myIt[temp], stdIt[temp]);
	}

	for (int i = 0; i < 100000; i++)
	{
		int type = rand() % 9;

		if (type == 0)
		{
			if (pos < 100000 - 1)
			{
				myIt++;
				stdIt++;
				pos++;
			}
		}
		else if (type == 1)
		{
			if (pos < 100000 - 1)
			{
				++myIt;
				++stdIt;
				++pos;
			}
		}
		else if (type == 2)
		{
			if (pos > 0)
			{
				myIt--;
				stdIt--;
				pos--;
			}
		}
		else if (type == 3)
		{
			if (pos > 0)
			{
				--myIt;
				--stdIt;
				--pos;
			}
		}
		else if (type == 4)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt += value;
				stdIt += value;
				pos += value;
			}
		}
		else if (type == 5)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt = myIt + value;
				stdIt = stdIt + value;
				pos = pos + value;
			}
		}
		else if (type == 6)
		{
			int value = rand() % 100;
			if (pos + value < 100000 - 1)
			{
				myIt = value + myIt;
				stdIt = value + stdIt;
				pos = value + pos;
			}
		}
		else if (type == 7)
		{
			int value = rand() % 100;
			if (pos - value > 0)
			{
				myIt -= value;
				stdIt -= value;
				pos -= value;
			}
		}
		else
		{
			int value = rand() % 100;
			if (pos - value > 0)
			{
				myIt = myIt - value;
				stdIt = stdIt - value;
				pos = pos - value;
			}
		}

		temp = rand() % 100000;
		auto myTempIt = myDeq.rbegin() + temp;
		auto stdTempIt = stdDeq.rbegin() + temp;
		ASSERT_EQ(myIt < myTempIt, stdIt < stdTempIt);
		ASSERT_EQ(myIt > myTempIt, stdIt > stdTempIt);
		ASSERT_EQ(myIt <= myTempIt, stdIt <= stdTempIt);
		ASSERT_EQ(myIt >= myTempIt, stdIt >= stdTempIt);
		ASSERT_EQ(myIt == myTempIt, stdIt == stdTempIt);
		ASSERT_EQ(myIt != myTempIt, stdIt != stdTempIt);
		ASSERT_EQ(*myIt, *stdIt);
	}
}

int main(int argc, char **argv)
{
	testing::InitGoogleTest(&argc, argv);
	std::cout << RUN_ALL_TESTS();
	system("pause");
}