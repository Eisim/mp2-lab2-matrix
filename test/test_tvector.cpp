#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v1(10);
	v1[0] = 10;
	TDynamicVector<int> v2(v1);
	EXPECT_EQ(v2,v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10),v2;
	v2 = v1;
  EXPECT_NE(&v1[0],&v2[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-4));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE+1));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
  ASSERT_NO_THROW(v=v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(5), v2(5);
  ASSERT_NO_THROW(v1=v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(3), v2(5);
	v1 = v2;
  EXPECT_EQ(5, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(3), v2(5);
  ASSERT_NO_THROW(v1=v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(2), v2(2);
	v1[0] = 1; v1[1] = 2;
	v2[0] = 1; v2[1] = 2;
  EXPECT_TRUE(v1==v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(3);
	EXPECT_TRUE(v1==v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(3), v2(5);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(3),res(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	res=v1 + 1; // res=[6,7,8]
	TDynamicVector<int> v2(3);
	v2[0] = 6; v2[1] = 7; v2[2] = 8;
  EXPECT_EQ(v2,res);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(3), res(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	res = v1 - 1; // res=[4,5,6]
	TDynamicVector<int> exp(3);
	exp[0] = 4; exp[1] = 5; exp[2] = 6;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(3), res(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	res = v1 * 2; // res=[10,12,14]
	TDynamicVector<int> exp(3);
	exp[0] = 10; exp[1] = 12; exp[2] = 14;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3),v2(3), res(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	v2[0] = 1; v2[1] = 2; v2[2] = 3; //v2=[1,2,3]
	res = v1 + v2; // res=[6,8,10]
	TDynamicVector<int> exp(3);
	exp[0] = 6; exp[1] = 8; exp[2] = 10;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1+v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3), res(3);
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	v2[0] = 1; v2[1] = 2; v2[2] = 3; //v2=[1,2,3]
	res = v1 - v2; // res=[4,4,4]
	TDynamicVector<int> exp(3);
	exp[0] = 4; exp[1] = 4; exp[2] = 4;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(3), v2(3);
	int res;
	v1[0] = 5; v1[1] = 6; v1[2] = 7; //v1=[5,6,7]
	v2[0] = 1; v2[1] = 2; v2[2] = 3; //v2=[1,2,3]
	res = v1 * v2; // res=5+6*2+7*3=38
	int exp=38;
	EXPECT_EQ(exp, res);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(3), v2(5);
	ASSERT_ANY_THROW(v1 * v2);
}

