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

EXPECT_FLOAT_EQ(-2.1013, v2.dotProduct(v,v2));

EXPECT_FLOAT_EQ(-1.03, v2.min());
EXPECT_FLOAT_EQ(-1.02, v2.max());


}

TEST(VectorTests, Vector3Tests) {

Vector3Bf v(1.02,1.03,1.04);
Vector3Bf v2(-1.02,-1.03,-1.04);

ASSERT_EQ(Vector3Bf(0,0,0), v2+v);

ASSERT_EQ(Vector3Bf(-2.04,-2.06,-2.08), v2-v);
ASSERT_EQ(Vector3Bf(2.04,2.06,2.08), v-v2);


EXPECT_FLOAT_EQ(Vector3Bf(-1.0404,-1.0609,-1.0816).x, (v*v2).x);
EXPECT_FLOAT_EQ(Vector3Bf(-1.0404,-1.0609,-1.0816).y, (v*v2).y);
EXPECT_FLOAT_EQ(Vector3Bf(-1.0404,-1.0609,-1.0816).z, (v*v2).z);

ASSERT_EQ(Vector3Bf(-0.51,-0.515,-0.52), v2/2.0f);

EXPECT_FLOAT_EQ(-3.1829, v2.dotProduct(v,v2));

EXPECT_FLOAT_EQ(-1.04, v2.min());
EXPECT_FLOAT_EQ(-1.02, v2.max());

Vector3Bf::normalize(v2);
ASSERT_NEAR(-0.571727,(v2).x,0.000001f);
ASSERT_NEAR(-0.577332,(v2).y,0.000001f);
ASSERT_NEAR(-0.582937,(v2).z,0.000001f);

}
