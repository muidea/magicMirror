/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/
#include <util/Random.h>
#include <iostream>
#include <algorithm>
#include "RandomTests.h"

using namespace std;
using namespace CyberLink;

void CyberLinkTest::TestRandom01()
{
  Random rand;

  int randVal = rand.rand();
  if (0 > randVal) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
  if (randVal > RAND_MAX) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestRandom02()
{
  int minRange = 1;
  int maxRange = 10;

  Random randRange(minRange, maxRange);

  int randVal = randRange.rand();
  if (minRange > randVal) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
  if (randVal > maxRange) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestRandom03()
{
  int minRange = 10;
  int maxRange = 1;

  Random randRange(minRange, maxRange);
  std::swap(minRange, maxRange);

  int randVal = randRange.rand();
  if (minRange > randVal) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
  if (randVal > maxRange) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
}

void CyberLinkTest::TestRandom04()
{
  Random rand;

  int randValue1 = rand.rand();
  int randValue2 = rand.rand();

  int minRange = std::min(randValue1, randValue2);
  int maxRange = std::max(randValue1, randValue2);

  Random randRange(minRange, maxRange);

  int randVal = randRange.rand();
  if (minRange > randVal) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
  if (randVal > maxRange) {
	  std::cout << "rand.rand() failed, :" << __LINE__ << std::endl;
  }
}
