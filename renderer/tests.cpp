#include <gtest/gtest.h>
#include <Vector2.h>

TEST(VectorTests, Vector2Tests) {

Vector2Bf v(1.02,1.03);
Vector2Bf v2(-1.02,-1.03);

ASSERT_EQ(Vector2Bf(0,0), v2+v);

ASSERT_EQ(Vector2Bf(-2.04,-2.06), v2-v);
ASSERT_EQ(Vector2Bf(2.04,2.06), v-v2);


EXPECT_FLOAT_EQ(Vector2Bf(-1.0404,-1.0609).x, (v*v2).x);
EXPECT_FLOAT_EQ(Vector2Bf(-1.0404,-1.0609).y, (v*v2).y);

ASSERT_EQ(Vector2Bf(-0.51,-0.515), v2/2.0f);

//ASSERT_EQ(1, v2.dotProduct(v,v2));



}
