#include <gtest/gtest.h>
#include "NoCopyableStack.hpp"
#include "Stack.hpp"


class StackTestFixture: public ::testing::Test
{
protected:
    struct CopyableClass
    {
        CopyableClass() = default;
        CopyableClass(const CopyableClass &) = default;
        CopyableClass(CopyableClass &&) = default;

        int value = 0;
    };

    struct NotCopyableClass
    {
        NotCopyableClass() = default;
        NotCopyableClass(const NotCopyableClass &) = delete;
        NotCopyableClass(NotCopyableClass &&) = default;

        int value = 0;
    };

    Stack<CopyableClass> copyableStack{};
    Stack<CopyableClass> copyableStackEmpty{};
    NoCopyableStack<NotCopyableClass> notCopyableStack{};
    NoCopyableStack<NotCopyableClass> notCopyableStackEmpty{};
    Stack<std::string> stringStackEmpty{};

    void SetUp() override
    {
        copyableStack.push({1});
        copyableStack.push({2});
        copyableStack.push({3});
        copyableStack.push({4});
        copyableStack.push({5});

        notCopyableStack.push({1});
        notCopyableStack.push({2});
        notCopyableStack.push({3});
        notCopyableStack.push({4});
        notCopyableStack.push({5});
    }

    void TearDown() override
    {

    }
};

TEST_F(StackTestFixture, TestForTest)
{
    EXPECT_EQ(std::is_move_constructible_v<CopyableClass>, true);
    EXPECT_EQ(std::is_copy_constructible_v<CopyableClass>, true);

    EXPECT_EQ(std::is_move_constructible_v<NotCopyableClass>, true);
    EXPECT_EQ(std::is_copy_constructible_v<NotCopyableClass>, false);
}

TEST_F(StackTestFixture, Constructors)
{
    EXPECT_EQ(std::is_move_constructible_v<Stack<int>>, true);
    EXPECT_EQ(std::is_copy_constructible_v<Stack<int>>, false);
    EXPECT_EQ(std::is_copy_assignable_v<Stack<int>>, false);
}

TEST_F(StackTestFixture, PushMove)
{
    std::string string{"I am a string"};
    stringStackEmpty.push(std::move(string));

    EXPECT_EQ(stringStackEmpty.head(), std::string{"I am a string"});
}

TEST_F(StackTestFixture, PushCopy)
{
    CopyableClass copyable{60};
    copyableStackEmpty.push(copyable);

    EXPECT_EQ(copyableStackEmpty.head().value, 60);
}

TEST_F(StackTestFixture, PushEmplace)
{
    notCopyableStackEmpty.push_emplace(600);

    EXPECT_EQ(notCopyableStackEmpty.head().value, 600);
}

TEST_F(StackTestFixture, PopSfinaeNotCopy)
{
    using PopType = decltype(notCopyableStack.pop());
    constexpr bool isSame = std::is_same_v<PopType, NotCopyableClass>;

    EXPECT_EQ(isSame, true);
}

TEST_F(StackTestFixture, PopSfinaeCopy)
{
    using PopType = decltype(copyableStack.pop());
    constexpr bool isSame = std::is_same_v<PopType, void>;

    EXPECT_EQ(isSame, true);
}

TEST_F(StackTestFixture, PopCopy)
{
    EXPECT_EQ(copyableStack.head().value, 5);

    copyableStack.pop();

    EXPECT_EQ(copyableStack.head().value, 4);
}

TEST_F(StackTestFixture, PopNotCopy)
{
    EXPECT_EQ(notCopyableStack.head().value, 5);

    NotCopyableClass value = notCopyableStack.pop();

    EXPECT_EQ(notCopyableStack.head().value, 4);
    EXPECT_EQ(value.value, 5);
}

TEST_F(StackTestFixture, Head)
{
    EXPECT_EQ(copyableStack.head().value, 5);
}

TEST_F(StackTestFixture, PopEmpty)
{
    EXPECT_THROW(
            copyableStackEmpty.pop(),
            StackException
    );
}

TEST_F(StackTestFixture, PopEmptyNotCopyable)
{
    EXPECT_THROW(
            notCopyableStackEmpty.pop(),
            StackException
    );
}

TEST_F(StackTestFixture, HeadEmpty)
{
    EXPECT_THROW(
            copyableStackEmpty.head(),
            StackException
    );
}