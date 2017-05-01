/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <util/Vector.h>
#include "VectorTests.h"

using namespace CyberLink;

class TestVectorObject {
public:
  TestVectorObject() {
  }
};

class TestVectorList : public SharedVector<TestVectorObject>  {
public:
  TestVectorList() {
  }
};

void CyberLinkTest::TestVector()
{
  const size_t TEST_VECTOR_OBJECT_NUM = 10;
  
  TestVectorList vectorObjectList;
  if (vectorObjectList.size() != 0) {
	  std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
  }

  cyber_shared_ptr<TestVectorObject> nullNode;
  if (vectorObjectList.add(nullNode)) {
	  std::cout << "vectorObjectList.add() failed, :" << __LINE__ << std::endl;
  }
  if (vectorObjectList.remove(nullNode)) {
	  std::cout << "vectorObjectList.remove() failed, :" << __LINE__ << std::endl;
  }
  if (vectorObjectList.insertAt(nullNode, 0)) {
	  std::cout << "vectorObjectList.insertAt() failed, :" << __LINE__ << std::endl;
  }
  if (vectorObjectList.indexOf(nullNode) != -1) {
	  std::cout << "vectorObjectList.indexOf() failed, :" << __LINE__ << std::endl;
  }
  
  cyber_shared_ptr<TestVectorObject> vectorObject[TEST_VECTOR_OBJECT_NUM];
  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
    vectorObject[n] = cyber_shared_ptr<TestVectorObject>(new TestVectorObject());
  }

  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
	  if (vectorObjectList.size() != n) {
		  std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
	}
	  if (vectorObjectList.indexOf(vectorObject[n]) != -1) {
		  std::cout << "vectorObjectList.indexOf() failed, :" << __LINE__ << std::endl;
	}
	  if (!vectorObjectList.exists(vectorObject[n])) {
		  std::cout << "vectorObjectList.exists() failed, :" << __LINE__ << std::endl;
	}
    vectorObjectList.add(vectorObject[n]);
	if (vectorObjectList.size() != (n + 1)) {
		std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
	}
	if (vectorObjectList.indexOf(vectorObject[n]) != n) {
		std::cout << "vectorObjectList.indexOf() failed, :" << __LINE__ << std::endl;
	}
	if (!vectorObjectList.exists(vectorObject[n])) {
		std::cout << "vectorObjectList.exists() failed, :" << __LINE__ << std::endl;
	}
  }

  for (size_t n=0; n<TEST_VECTOR_OBJECT_NUM; n++) {
	  if (vectorObjectList.size() != (TEST_VECTOR_OBJECT_NUM - n)) {
		  std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
	}
	  if (vectorObjectList.indexOf(vectorObject[n]) != 0) {
		  std::cout << "vectorObjectList.indexOf() failed, :" << __LINE__ << std::endl;
	}
	  if (!vectorObjectList.exists(vectorObject[n])) {
		  std::cout << "vectorObjectList.exists() failed, :" << __LINE__ << std::endl;
	}
    vectorObjectList.remove(vectorObject[n]);
	if (vectorObjectList.size() != (TEST_VECTOR_OBJECT_NUM - (n + 1))) {
		std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
	}
	if (vectorObjectList.indexOf(vectorObject[n]) != -1) {
		std::cout << "vectorObjectList.indexOf() failed, :" << __LINE__ << std::endl;
	}
	if (vectorObjectList.exists(vectorObject[n])) {
		std::cout << "vectorObjectList.exists() failed, :" << __LINE__ << std::endl;
	}
  }

  if (vectorObjectList.size() != 0) {
	  std::cout << "vectorObjectList.size() failed, :" << __LINE__ << std::endl;
  }
}
