/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};

// Example "smoke test" (can be deleted)
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}



TEST(GuesserTest, correct_pswd_try1)
{
	Guesser object("Password");
	ASSERT_TRUE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, correct_pswd_try2)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("password"));
	ASSERT_TRUE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, correct_pswd_try3)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("password"));
	ASSERT_FALSE(object.match("password"));
	ASSERT_TRUE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, correct_pswd_try4)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("password"));
	ASSERT_FALSE(object.match("password"));
	ASSERT_FALSE(object.match("password"));
	ASSERT_FALSE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 0);
}


TEST(GuesserTest, long_secret_pass)
{
	Guesser object("0123456789abcdefghijklmnopqrstuvwxyz0123456789");
	ASSERT_TRUE(object.match("0123456789abcdefghijklmnopqrstuv"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, long_secret_fail)
{
	Guesser object("0123456789abcdefghijklmnopqrstuvwxyz0123456789");
	ASSERT_FALSE(object.match("0123456789abcdefghijklmnopqrstuvwxyz0123456789"));
	ASSERT_EQ(object.remaining(), 2);
}



TEST(GuesserTest, big_distance_try2)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("sbeve"));
	ASSERT_FALSE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 1);	// i have no idea why this one resets to 3  //update: far off guesses dont decrease m_remaining
}


TEST(GuesserTest, special_char_pass)
{
	Guesser object("A%%\f");
	ASSERT_TRUE(object.match("A%%\f"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, special_char_fail)
{
	Guesser object("A%%\f");
	ASSERT_FALSE(object.match("A$$#f"));
	ASSERT_EQ(object.remaining(), 2);
}

TEST(GuesserTest, numbers_pass)
{
	Guesser object("123456789");
	ASSERT_TRUE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, numbers_fail)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("234567891"));
	ASSERT_EQ(object.remaining(), 2);
}


TEST(GuesserTest, guess_shorter_fail)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("1234"));
	ASSERT_FALSE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 2);
}

TEST(GuesserTest, guess_longer_fail)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("123456789abcdef"));
	ASSERT_FALSE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 2);
}

TEST(GuesserTest, guess_shorter_pass)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("12345678"));
	ASSERT_TRUE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, guess_longer_pass)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("123456789a"));
	ASSERT_TRUE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 3);
}


TEST(GuesserTest, guess_shorter_close)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("12345678"));
	ASSERT_TRUE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 3);
}

TEST(GuesserTest, guess_longer_close)
{
	Guesser object("123456789");
	ASSERT_FALSE(object.match("123456789a"));
	ASSERT_TRUE(object.match("123456789"));
	ASSERT_EQ(object.remaining(), 3);
}


TEST(GuesserTest, fail_pswd_try1)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("password"));
	ASSERT_EQ(object.remaining(), 2);
}


TEST(GuesserTest, line_32_test)
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("123456789"));
	ASSERT_FALSE(object.match("Password"));
	ASSERT_EQ(object.remaining(), 1);
}



TEST(GuesserTest, wierd_remaining_reset1)
{
	Guesser object("Password");
	object.match("123456789");
	object.match("Password");
	ASSERT_EQ(object.remaining(), 1);
}

TEST(GuesserTest, wierd_remaining_reset2)
{
	Guesser object("Password");
	object.match("123456789");
	object.match("5678");
	ASSERT_EQ(object.remaining(), 1);
}

TEST(GuesserTest, wierd_remaining_reset3)
{
	Guesser object("Password");
	object.match("123456789");
	object.match("fgdoisbvkos");
	object.match("425252345");
	ASSERT_EQ(object.remaining(), 0);
}

TEST(GuesserTest, wierd_remaining_reset4)
{
	Guesser object("Password");			//if the distance is too big it does not decrease m_remaining
	object.match("dsflkhbsl");
	object.match("sdlfhkvbpsf");
	object.match("dlvbshifv");
	object.match("Password");
	ASSERT_EQ(object.remaining(), 0);
}	

TEST(GuesserTest, wierd_remaining_reset5)
{
	Guesser object("Password");
	object.match("password");
	object.match("password");
	object.match("password");
	object.match("Password");
	ASSERT_EQ(object.remaining(), 0);
}


TEST(GuesserTest, test_m_remaining_issue_1)		//because m_remaining doesnt reset the program will break after multiple logins 
{
	Guesser object("Password");
	ASSERT_FALSE(object.match("password"));
	ASSERT_EQ(object.remaining(), 2);
	ASSERT_TRUE(object.match("Password"));

	//ASSERT_EQ(object.remaining(), 3);

	ASSERT_FALSE(object.match("password"));
	ASSERT_FALSE(object.match("password"));
	ASSERT_TRUE(object.match("Password"));
}

