#pragma once

// SUTL
#include <UnitTestResult.h>

// STL
#include <functional>
#include <list>
#include <vector>

// Target Class
#include <CCString.h>

// Test Helper Utils
#include <CCPointerHelpersTests.h>
#include <CCStringUtil.h>


namespace CC
{
	enum class TestStrType : size_t
	{
		Regular = 0,
		DiffCase,
		Shorter,
		Longer,

		_End,
		_Begin = 0
	};

	inline static TestStrType& operator++(TestStrType& t)
	{
		using UT = std::underlying_type_t<TestStrType>;
		if (t != TestStrType::_End)
		{
			t = static_cast<TestStrType>(static_cast<UT>(t) + 1);
		}

		return t;
	}

	inline static TestStrType operator++(TestStrType& t, int)
	{
		using UT = std::underlying_type_t<TestStrType>;
		TestStrType old = t;
		++t;
		return old;
	}

    class StringTests
    {
        StringTests( ) = delete;
        StringTests(const StringTests&) = delete;
        StringTests(StringTests&&) = delete;
        ~StringTests( ) = delete;
        StringTests& operator=(const StringTests&) = delete;
        StringTests& operator=(StringTests&&) = delete;

    private:

        // Type aliases
        using UTR = UnitTestResult;
        using UTFunc = std::function<UTR(void)>;
        using UTList = std::list<UTFunc>;

        using TestQuantity = PointerHelpersTests::TestQuantity;

        /// Test Helpers \\\

        static const std::vector<SupportedStringTuple> ms_TestStrings;
        static const std::vector<SupportedStringTuple> ms_DiffCaseTestStrings;
        static const std::vector<SupportedStringTuple> ms_ShorterTestStrings;
        static const std::vector<SupportedStringTuple> ms_LongerTestStrings;

		template <TestQuantity TQ>
		[[nodiscard]] static constexpr size_t GetTQNum() noexcept
		{
			if constexpr (TQ == TestQuantity::Zero)
			{
				return 0;
			}
			else if constexpr (TQ == TestQuantity::One)
			{
				return 16;
			}
			else if constexpr (TQ == TestQuantity::Many)
			{
				return 64;
			}
			else
			{
				static_assert(false, __FUNCSIG__": Unknown TestQuantity value.");
			}
		}

		template <TestQuantity TQ>
		[[nodiscard]] static constexpr size_t TQToTestCStrIdx() noexcept
		{
			if constexpr (TQ == TestQuantity::Zero)
			{
				return 0;
			}
			else if constexpr (TQ == TestQuantity::One)
			{
				return 1;
			}
			else if constexpr (TQ == TestQuantity::Many)
			{
				return 2;
			}
			else
			{
				static_assert(false, __FUNCSIG__": Unknown TestQuantity value.");
			}
		}


		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static constexpr const std::basic_string<T>& GetTestCppStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_TestStrings[idx]);
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static constexpr const std::basic_string<T>& GetDiffCaseTestCppStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_DiffCaseTestStrings[idx]);
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static constexpr const std::basic_string<T>& GetShorterTestCppStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_ShorterTestStrings[idx]);
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static constexpr const std::basic_string<T>& GetLongerTestCppStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_LongerTestStrings[idx]);
		}

		template <typename T, TestQuantity TQ, TestStrType Type, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static constexpr const std::basic_string<T>& GetTestCppStringByType()
		{
			static_assert(Type >= TestStrType::_Begin && Type < TestStrType::_End, __FUNCSIG__": Invalid TestCStrType");

			if constexpr (Type == TestStrType::Regular)
			{
				return GetTestCppStr<T, TQ>();
			}
			else if constexpr (Type == TestStrType::DiffCase)
			{
				return GetDiffCaseTestCppStr<T, TQ>();
			}
			else if constexpr (Type == TestStrType::Shorter)
			{
				return GetShorterTestCppStr<T, TQ>();
			}
			else
			{
				return GetLongerTestCppStr<T, TQ>();
			}
		}


		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static const T* GetTestCStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_TestStrings[idx]).c_str();
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static const T* GetDiffCaseTestCStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_DiffCaseTestStrings[idx]).c_str();
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static const T* GetShorterTestCStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_ShorterTestStrings[idx]).c_str();
		}

		template <typename T, TestQuantity TQ, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static const T* GetLongerTestCStr() noexcept
		{
			constexpr size_t idx = TQToTestCStrIdx<TQ>();
			return std::get<std::basic_string<T>>(ms_LongerTestStrings[idx]).c_str();
		}

		template <typename T, TestQuantity TQ, TestStrType Type, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		[[nodiscard]] static const T* GetTestCStrByType()
		{
			static_assert(Type >= TestStrType::_Begin && Type < TestStrType::_End, __FUNCSIG__": Invalid TestCStrType");

			if constexpr (Type == TestStrType::Regular)
			{
				return GetTestCStr<T, TQ>();
			}
			else if constexpr (Type == TestStrType::DiffCase)
			{
				return GetDiffCaseTestCStr<T, TQ>();
			}
			else if constexpr (Type == TestStrType::Shorter)
			{
				return GetShorterTestCStr<T, TQ>();
			}
			else
			{
				return GetLongerTestCStr<T, TQ>();
			}
		}

        /// Test Subclasses \\\

        // Tests constructor behavior.
        class ConstructorTests;

        // Tests overloaded assignment operator behavior.
        class AssignmentOperatorTests;

        // Tests overloaded add-assignment operator behavior.
        class AddAssignmentOperatorTests;

        // Tests overloaded subscript operator behavior.
        class SubscriptOperatorTests;

        // Tests overloaded equivalency operator behavior.
        class EquivalencyOperatorTests;

        // Tests behavior of the various Getter methods.
        class GetterTests;

        // Tests Assign behavior.
        class Assign;

        // Tests Append behavior.
        class Append;

        // Tests comparison behavior between strings.
        class CompareTests;

        // Tests Clear behavior.
        class ClearTests;

        // Tests IsEmpty behavior.
        class IsEmptyTests;

    public:

        // Returns list of String unit tests.
        [[nodiscard]] static UTList GetTests( );
    };


    // Tests constructor behavior.
    class StringTests::ConstructorTests
    {
    public:

        template <typename T>
        [[nodiscard]] static UTR DefaultCtor( )
        {
            String<T> str;

            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR LenAndCharCtor( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            String<T> str(len, static_cast<T>('x'));

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == len);
                SUTL_TEST_ASSERT((str.m_SSOArr[0] == static_cast<T>('x')) == (TQ == TestQuantity::One));
                SUTL_TEST_ASSERT(str.m_SSOArr[len] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!str.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == 0);
                SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                for ( size_t i = 0; i < len; i++ )
                {
                    SUTL_TEST_ASSERT(str.m_DynBuf.Get( )[i] == T('x'));
                }

                SUTL_TEST_ASSERT(str.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T>
        [[nodiscard]] static UTR CStrCtorNullptr( )
        {
            String<T> str(nullptr);

            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrCtor( )
        {
            const T* const testCStr = GetTestCStr<T, TQ>( );
            constexpr size_t len = GetTQNum<TQ>( );
            String<T> str(testCStr);

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == 0);
                SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!str.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_TEST_ASSERT(!str.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == 0);
                SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR PtrAndLenCtorNullptr( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            String<T> str(nullptr, len);

            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR PtrAndLenCtor( )
        {
            const T* const testCStr = GetTestCStr<T, TQ>( );
            constexpr size_t len = GetTQNum<TQ>( ) >> ((TQ == TestQuantity::Many) ? 1 : 0);
            String<T> str(testCStr, len);

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == 0);
                SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!str.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_TEST_ASSERT(!str.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(str.m_SSOPos == 0);
                SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) != 0);
                SUTL_TEST_ASSERT(str.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CopyCtor( )
        {
            const T* const testCStr = GetTestCStr<T, TQ>( );
            constexpr size_t len = GetTQNum<TQ>( ) >> ((TQ == TestQuantity::Many) ? 1 : 0);
            String<T> str(testCStr, len);

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
                SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
            }
            else
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
                SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) != 0);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            String<T> copyStr(str);

            // Compare with test string.
            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(copyStr.m_SSOPos == 0);
                SUTL_TEST_ASSERT(copyStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!copyStr.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_TEST_ASSERT(copyStr.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(copyStr.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_TEST_ASSERT(!copyStr.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(copyStr.m_SSOPos == 0);
                SUTL_TEST_ASSERT(copyStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!!copyStr.m_DynBuf);
                SUTL_TEST_ASSERT(copyStr.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(copyStr.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(copyStr.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(copyStr.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) != 0);
                SUTL_TEST_ASSERT(copyStr.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            // Compare with original String obj.
            SUTL_TEST_ASSERT(copyStr.m_SSOPos == str.m_SSOPos);
            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(memcmp(copyStr.m_SSOArr, str.m_SSOArr, sizeof(T) * (len + 1)) == 0);
                SUTL_TEST_ASSERT(!copyStr.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(copyStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(memcmp(copyStr.m_DynBuf.Get( ), str.m_DynBuf.Get( ), sizeof(T) * (len + 1)) == 0);
            }


            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR MoveCtor( )
        {
            const T* const testCStr = GetTestCStr<T, TQ>( );
            constexpr size_t len = GetTQNum<TQ>( ) >> ((TQ == TestQuantity::Many) ? 1 : 0);
            String<T> str(testCStr, len);

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
                SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
            }
            else
            {
                SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
                SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) != 0);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            String<T> moveStr(std::move(str));

            // Compare with test string.
            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(moveStr.m_SSOPos == 0);
                SUTL_TEST_ASSERT(moveStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!moveStr.m_DynBuf);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_TEST_ASSERT(moveStr.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(moveStr.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
                SUTL_TEST_ASSERT(!moveStr.m_DynBuf);
            }
            else
            {
                SUTL_TEST_ASSERT(moveStr.m_SSOPos == 0);
                SUTL_TEST_ASSERT(moveStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
                SUTL_TEST_ASSERT(!!moveStr.m_DynBuf);
                SUTL_TEST_ASSERT(moveStr.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(moveStr.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(moveStr.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(moveStr.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) != 0);
                SUTL_TEST_ASSERT(moveStr.m_DynBuf.Get( )[len] == String<T>::ms_NullTerminator);
            }

            // Ensure original string was cleared.
            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            SUTL_TEST_SUCCESS( );
        }
    };


    // Tests overloaded assignment operator behavior.
    class StringTests::AssignmentOperatorTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAssignOpNullptr( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );
            String<T> str(testCStr);

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
                SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            }
            else if constexpr ( TQ == TestQuantity::One )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            str = nullptr;

            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAssignOp( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );
            String<T> str;

            SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
            SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_SETUP_ASSERT(!str.m_DynBuf);

            str = testCStr;

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CopyAssignOp( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );
            String<T> str;
            String<T> copyStr;

            SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
            SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_SETUP_ASSERT(!str.m_DynBuf);
            SUTL_SETUP_ASSERT(copyStr.m_SSOPos == 0);
            SUTL_SETUP_ASSERT(copyStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_SETUP_ASSERT(!copyStr.m_DynBuf);

            str = testCStr;

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            copyStr = str;

            SUTL_TEST_ASSERT(!!copyStr.m_DynBuf == !!str.m_DynBuf);
            SUTL_TEST_ASSERT(copyStr.m_DynBuf.Length( ) == str.m_DynBuf.Length( ));
            SUTL_TEST_ASSERT(copyStr.m_DynBuf.WritePosition( ) == str.m_DynBuf.WritePosition( ));
            SUTL_TEST_ASSERT(copyStr.m_SSOPos == str.m_SSOPos);
            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(memcmp(copyStr.m_SSOArr, str.m_SSOArr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(memcmp(copyStr.m_DynBuf.Get( ), str.m_DynBuf.Get( ), sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR MoveAssignOp( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );
            String<T> str;
            String<T> moveStr;

            SUTL_SETUP_ASSERT(str.m_SSOPos == 0);
            SUTL_SETUP_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_SETUP_ASSERT(!str.m_DynBuf);
            SUTL_SETUP_ASSERT(moveStr.m_SSOPos == 0);
            SUTL_SETUP_ASSERT(moveStr.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_SETUP_ASSERT(!moveStr.m_DynBuf);

            str = testCStr;

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            moveStr = std::move(str);

            SUTL_TEST_ASSERT(str.m_SSOPos == 0);
            SUTL_TEST_ASSERT(str.m_SSOArr[0] == String<T>::ms_NullTerminator);
            SUTL_TEST_ASSERT(!str.m_DynBuf);

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(!moveStr.m_DynBuf);
                SUTL_TEST_ASSERT(moveStr.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(moveStr.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(!!moveStr.m_DynBuf);
                SUTL_TEST_ASSERT(moveStr.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(moveStr.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(moveStr.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }
    };


    // Tests overloaded add-assignment operator behavior.
    class StringTests::AddAssignmentOperatorTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAddAssignOpNullptr( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );

            String<T> str(testCStr);

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            str += nullptr;

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_TEST_ASSERT(!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_SSOPos == len);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAddAssignOp( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );

            String<T> str(testCStr);

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            str += testCStr;

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_SSOPos == (len * 2));
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr + len, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == ((len * 2) + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == (len * 2));
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ) + len, testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR StrObjAddAssignOp( )
        {
            constexpr size_t len = GetTQNum<TQ>( );
            const T* const testCStr = GetTestCStr<T, TQ>( );

            String<T> str(testCStr);

            if constexpr ( TQ != TestQuantity::Many )
            {
                SUTL_SETUP_ASSERT(!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_SSOPos == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_SETUP_ASSERT(!!str.m_DynBuf);
                SUTL_SETUP_ASSERT(str.m_DynBuf.Length( ) == (len + 1));
                SUTL_SETUP_ASSERT(str.m_DynBuf.WritePosition( ) == len);
                SUTL_SETUP_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * (len + 1)) == 0);
            }

            str += str;

            if constexpr ( TQ == TestQuantity::Zero )
            {
                SUTL_TEST_ASSERT(!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_SSOPos == (len * 2));
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr, testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(str.m_SSOArr + len, testCStr, sizeof(T) * (len + 1)) == 0);
            }
            else
            {
                SUTL_TEST_ASSERT(!!str.m_DynBuf);
                SUTL_TEST_ASSERT(str.m_DynBuf.Length( ) == ((len * 2) + 1));
                SUTL_TEST_ASSERT(str.m_DynBuf.WritePosition( ) == (len * 2));
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ), testCStr, sizeof(T) * len) == 0);
                SUTL_TEST_ASSERT(memcmp(str.m_DynBuf.Get( ) + len, testCStr, sizeof(T) * (len + 1)) == 0);
            }

            SUTL_TEST_SUCCESS( );
        }
    };


    // Tests overloaded subscript operator behavior.
    class StringTests::SubscriptOperatorTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR SubscriptOp( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			
			String<T> str;
			bool bThrew = false;
			
			if constexpr (len > 0)
			{
				const T* const testCStr = GetTestCStr<T, TQ>();
				for (size_t i = 0, j = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					for (j = 0; j < str.Length(); j++)
					{
						SUTL_TEST_ASSERT(str[j] == testCStr[j]);
					}

					SUTL_TEST_ASSERT(str.CStr()[j] == String<T>::ms_NullTerminator);
				}
			}

			try
			{
				T tc = static_cast<T>('\xFF');
				tc = str[len];
				SUTL_TEST_ASSERT(tc != String<T>::ms_NullTerminator);
			}
			catch ( const std::out_of_range& )
			{
				bThrew = true;
			}
			catch ( const std::exception& e )
			{
				SUTL_TEST_EXCEPTION(e.what( ));
			}

			SUTL_TEST_ASSERT(bThrew);

			SUTL_TEST_SUCCESS( );
        }
    };


    // Tests overloaded equivalency operator behavior.
    class StringTests::EquivalencyOperatorTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrEquivOp( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const std::vector<std::pair<const T*, bool>> testStrPairs
			{
				std::pair<const T*, bool>(GetTestCStr<T, TQ>(), true),
				std::pair<const T*, bool>(GetDiffCaseTestCStr<T, TQ>(), (len == 0)),
				std::pair<const T*, bool>(GetShorterTestCStr<T, TQ>(), (len == 0)),
				std::pair<const T*, bool>(GetLongerTestCStr<T, TQ>(), (len == 0)),
			};

			String<T> str(GetTestCStr<T, TQ>());
			for (const auto& testPair : testStrPairs)
			{
				SUTL_TEST_ASSERT((str == testPair.first) == testPair.second);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR StrObjEquivOp( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const std::vector<std::pair<String<T>, bool>> testStrPairs
			{
				std::pair<String<T>, bool>(GetTestCStr<T, TQ>(), true),
				std::pair<String<T>, bool>(GetDiffCaseTestCStr<T, TQ>(), (len == 0)),
				std::pair<String<T>, bool>(GetShorterTestCStr<T, TQ>(), (len == 0)),
				std::pair<String<T>, bool>(GetLongerTestCStr<T, TQ>(), (len == 0)),
			};

			String<T> str(GetTestCStr<T, TQ>());
			for (const auto& testPair : testStrPairs)
			{
				const String<T>& testStr = testPair.first;
				const bool bExpectedResult = testPair.second;
				SUTL_TEST_ASSERT((str == testStr) == bExpectedResult);
			}

			SUTL_TEST_SUCCESS();
        }
    };


    // Tests behavior of the various Getter methods.
    class StringTests::GetterTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStr( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			if constexpr (len > 0)
			{
				for (size_t i = 0, j = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					for (j = 0; j < str.Length(); j++)
					{
						SUTL_TEST_ASSERT(str.CStr()[j] == testCStr[j]);
					}

					SUTL_TEST_ASSERT(str.CStr()[j] == String<T>::ms_NullTerminator);
				}
			}

			SUTL_TEST_ASSERT(str.CStr()[len] == testCStr[len]);

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR Length( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			if constexpr (len > 0)
			{
				for (size_t i = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					SUTL_TEST_ASSERT(str.Length() == (i + 1));
				}
			}

			SUTL_TEST_ASSERT(str.Length() == StringUtil::GetLength<T>(testCStr));

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR Capacity( )
        {
			constexpr size_t len = GetTQNum<TQ>();

			String<T> str;
			if constexpr (len > 0)
			{
				const T* const testCStr = GetTestCStr<T, TQ>();
				size_t expectedCap = String<T>::ms_SSOCap;

				for (size_t i = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					if ((i + 1) == expectedCap)
					{
						expectedCap += (expectedCap == String<T>::ms_SSOCap) ? 1 : (expectedCap >> 1);
					}

					SUTL_TEST_ASSERT(str.Capacity() == expectedCap);
				}
			}
			else
			{
				SUTL_TEST_ASSERT(str.Capacity() == String<T>::ms_SSOCap);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR Front( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			bool bThrew = false;

			String<T> str;
			if constexpr (len > 0)
			{
				const T* const testCStr = GetTestCStr<T, TQ>();
				for (size_t i = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					SUTL_TEST_ASSERT(str.Front() == testCStr[0]);
				}

				str = String<T>();
			}

			try
			{
				T tc = static_cast<T>('\xFF');
				tc = str.Front();
				SUTL_TEST_ASSERT(tc != String<T>::ms_NullTerminator);
			}
			catch (const std::out_of_range&)
			{
				bThrew = true;
			}
			catch (const std::exception& e)
			{
				SUTL_TEST_EXCEPTION(e.what());
			}

			SUTL_TEST_ASSERT(bThrew);

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR Back( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			bool bThrew = false;

			String<T> str;
			if constexpr (len > 0)
			{
				const T* const testCStr = GetTestCStr<T, TQ>();
				for (size_t i = 0; i < len; i++)
				{
					SUTL_SETUP_ASSERT(str.Append(testCStr[i]));
					SUTL_TEST_ASSERT(str.Back() == testCStr[i]);
				}

				str = String<T>();
			}

			try
			{
				T tc = static_cast<T>('\xFF');
				tc = str.Back();
				SUTL_TEST_ASSERT(tc != String<T>::ms_NullTerminator);
			}
			catch (const std::out_of_range&)
			{
				bThrew = true;
			}
			catch (const std::exception& e)
			{
				SUTL_TEST_EXCEPTION(e.what());
			}

			SUTL_TEST_ASSERT(bThrew);

			SUTL_TEST_SUCCESS();
        }
    };


    // Tests Assign behavior.
    class StringTests::Assign
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR ChAssign( )
        {
			constexpr size_t len = GetTQNum<TQ>();

			String<T> str;
			if constexpr (len > 0)
			{
				const T* const testCStr = GetTestCStr<T, TQ>();
				for (size_t i = 0; i < len; i++)
				{
					SUTL_TEST_ASSERT(str.Assign(testCStr[i]));
					SUTL_TEST_ASSERT(str.CStr() == str.m_SSOArr);
					SUTL_TEST_ASSERT(str.Length() == 1);
					SUTL_TEST_ASSERT(str[0] == testCStr[i]);
					SUTL_TEST_ASSERT(str.Front() == testCStr[i]);
					SUTL_TEST_ASSERT(str.Back() == testCStr[i]);
					SUTL_TEST_ASSERT(str.CStr()[str.Length()] == String<T>::ms_NullTerminator);
				}
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAssign( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			SUTL_TEST_ASSERT(str.Assign(testCStr));
			SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR PtrAndLenAssign( )
        {
			constexpr size_t len1 = (TQ != TestQuantity::Many) ? GetTQNum<TQ>() : (GetTQNum<TQ>() >> 1);
			constexpr size_t len2 = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			SUTL_TEST_ASSERT(str.Assign(testCStr, len1));
			if constexpr (TQ != TestQuantity::Many)
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);
			}
			else
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * len1) == 0);
				SUTL_TEST_ASSERT(str.CStr()[len1] == String<T>::ms_NullTerminator);
			}

			SUTL_TEST_ASSERT(str.Assign(testCStr, len2));
			SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T)* (len2 + 1)) == 0);

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR StrObjCopyAssign( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str1;
			String<T> str2;
			SUTL_SETUP_ASSERT(str1.Assign(testCStr));
			SUTL_SETUP_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_ASSERT(str2.Assign(str1));
			SUTL_TEST_ASSERT(str1.CStr() != str2.CStr());
			SUTL_TEST_ASSERT(str1.Length() == str2.Length());
			SUTL_TEST_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);
			SUTL_TEST_ASSERT(memcmp(str1.CStr(), str2.CStr(), sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_SUCCESS();
        }

		template <typename T, TestQuantity TQ>
		[[nodiscard]] static UTR StrObjAndLenCopyAssign()
		{
			constexpr size_t len1 = GetTQNum<TQ>();
			constexpr size_t len2 = len1 >> 1;
			constexpr size_t len3 = std::numeric_limits<size_t>::max();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str1;
			String<T> str2;
			String<T> str3;

			SUTL_SETUP_ASSERT(str1.Assign(testCStr));
			SUTL_SETUP_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);

			SUTL_TEST_ASSERT(str2.Assign(str1, len2));
			SUTL_TEST_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);

			SUTL_TEST_ASSERT(str1.CStr() != str2.CStr());
			SUTL_TEST_ASSERT(str1.Length() == len1);
			SUTL_TEST_ASSERT(str2.Length() == len2);

			if (len2 > 0)
			{
				SUTL_TEST_ASSERT(memcmp(str1.CStr(), str2.CStr(), sizeof(T) * len2) == 0);
			}

			SUTL_TEST_ASSERT(str2.CStr()[len2] == String<T>::ms_NullTerminator);

			SUTL_TEST_ASSERT(str3.Assign(str1, len3));
			SUTL_TEST_ASSERT(str3.Length() == str1.Length());
			SUTL_TEST_ASSERT(memcmp(str3.CStr(), str1.CStr(), sizeof(T) * (len1 + 1)) == 0);

			SUTL_TEST_SUCCESS();
		}

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR StrObjMoveAssign( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str1;
			String<T> str2;
			SUTL_SETUP_ASSERT(str1.Assign(testCStr));
			SUTL_SETUP_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_ASSERT(str2.Assign(std::move(str1)));
			SUTL_TEST_ASSERT(str1.CStr() == str1.m_SSOArr);
			SUTL_TEST_ASSERT(str1.Length() == 0);
			SUTL_TEST_ASSERT(str1.Capacity() == String<T>::ms_SSOCap);
			SUTL_TEST_ASSERT(memcmp(str2.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_SUCCESS();
        }
    };


    // Tests Append behavior.
    class StringTests::Append
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR ChAppend( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			if constexpr (len > 0)
			{
				for (size_t i = 0, j = 0; i < len; i++)
				{
					SUTL_TEST_ASSERT(str.Append(testCStr[i]));
					SUTL_TEST_ASSERT(str.Length() == (i + 1));
					for (j = 0; j < str.Length(); j++)
					{
						SUTL_TEST_ASSERT(str.CStr()[j] == testCStr[j]);
					}

					SUTL_TEST_ASSERT(str.CStr()[j] == String<T>::ms_NullTerminator);
				}
			}

			SUTL_TEST_ASSERT(str.CStr()[len] == testCStr[len]);

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR CStrAppend( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			SUTL_TEST_ASSERT(str.Append(testCStr));
			SUTL_TEST_ASSERT(str.Length() == len);
			SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);
			SUTL_TEST_ASSERT(str.Append(testCStr));
			SUTL_TEST_ASSERT(str.Length() == (2 * len));

			if constexpr (len > 0)
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * len) == 0);
				SUTL_TEST_ASSERT(memcmp(str.CStr() + len, testCStr, sizeof(T) * (len + 1)) == 0);
			}
			else
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR PtrAndLenAppend( )
        {
			constexpr size_t len1 = GetTQNum<TQ>();
			constexpr size_t len2 = GetTQNum<TQ>() >> 1;
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			SUTL_TEST_ASSERT(str.Append(testCStr, len1));
			SUTL_TEST_ASSERT(str.Length() == len1);
			SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);
			SUTL_TEST_ASSERT(str.Append(testCStr, len2));
			SUTL_TEST_ASSERT(str.Length() == (len1 + len2));

			if constexpr (len2 > 0)
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * len1) == 0);
				SUTL_TEST_ASSERT(memcmp(str.CStr() + len1, testCStr, sizeof(T) * len2) == 0);
				SUTL_TEST_ASSERT(str.CStr()[len1 + len2] == String<T>::ms_NullTerminator);
			}
			else
			{
				SUTL_TEST_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR StrObjAppend( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str1;
			String<T> str2;

			SUTL_TEST_ASSERT(str1.Append(testCStr));
			SUTL_TEST_ASSERT(str1.Length() == len);
			SUTL_TEST_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);
			SUTL_TEST_ASSERT(str2.Append(str1));
			SUTL_TEST_ASSERT(str2.CStr() != str1.CStr());
			SUTL_TEST_ASSERT(str2.Length() == str1.Length());

			SUTL_TEST_ASSERT(memcmp(str2.CStr(), str1.CStr(), sizeof(T) * (len + 1)) == 0);

			SUTL_TEST_SUCCESS();
        }

		template <typename T, TestQuantity TQ>
		[[nodiscard]] static UTR StrObjAndLenAppend()
		{
			constexpr size_t len1 = GetTQNum<TQ>();
			constexpr size_t len2 = len1 >> 1;
			constexpr size_t len3 = std::numeric_limits<size_t>::max();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str1;
			String<T> str2;
			String<T> str3;

			SUTL_SETUP_ASSERT(str1.Append(testCStr, len1));
			SUTL_SETUP_ASSERT(str1.Length() == len1);
			SUTL_SETUP_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);

			SUTL_TEST_ASSERT(str2.Append(str1, len2));
			SUTL_TEST_ASSERT(memcmp(str1.CStr(), testCStr, sizeof(T) * (len1 + 1)) == 0);
			SUTL_TEST_ASSERT(str2.Length() == len2);

			if constexpr (len2 > 0)
			{
				SUTL_TEST_ASSERT(memcmp(str2.CStr(), str1.CStr(), sizeof(T) * len2) == 0);
			}

			SUTL_TEST_ASSERT(str2.CStr()[len2] == String<T>::ms_NullTerminator);

			SUTL_TEST_ASSERT(str3.Append(str1, len3));
			SUTL_TEST_ASSERT(str3.Length() == str1.Length());
			SUTL_TEST_ASSERT(memcmp(str3.CStr(), str1.CStr(), sizeof(T) * (len1 + 1)) == 0);

			SUTL_TEST_SUCCESS();
		}
    };


    // Tests comparison behavior between strings.
    class StringTests::CompareTests
    {
	private:

		template <typename T, TestQuantity TQ1, TestQuantity TQ2, TestStrType Type, CC_ENABLE_IF_SUPPORTED_CHARACTER_TYPE(T)>
		static size_t GetCompLen()
		{
			size_t len = 0;

			if constexpr ((TQ1 != TestQuantity::Zero) && (TQ2 != TestQuantity::Zero))
			{
				len = GetTestCppStringByType<T, TQ1, Type>().size(); 
				
				if constexpr (TQ2 == TestQuantity::One)
				{
					len >>= 1;
				}
			}

			return len;
		}

    public:

        template <typename T, TestQuantity TQ, bool bCaseInsensitive>
		[[nodiscard]] static UTR CStrCompare()
		{
			constexpr size_t len = GetTQNum<TQ>();
			std::vector<std::pair<const T*, bool>> testStrPairs
			{
				std::pair<const T*, bool>(GetTestCStr<T, TQ>(), true),
				std::pair<const T*, bool>(GetDiffCaseTestCStr<T, TQ>(), (bCaseInsensitive || len == 0)),
				std::pair<const T*, bool>(GetShorterTestCStr<T, TQ>(), (len == 0)),
				std::pair<const T*, bool>(GetLongerTestCStr<T, TQ>(), (len == 0)),
			};

			String<T> str(GetTestCStr<T, TQ>());
			for (const auto& testPair : testStrPairs)
			{
				const T* testCStr = testPair.first;
				const bool bExpectedResult = testPair.second;
				SUTL_TEST_ASSERT(str.Compare<bCaseInsensitive>(testCStr) == bExpectedResult);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ1, TestQuantity TQ2, bool bCaseInsensitive>
        [[nodiscard]] static UTR StrAndLenCompare( )
        {
			const size_t compLenReg = GetCompLen<T, TQ1, TQ2, TestStrType::Regular>();
			const size_t compLenDiffCase = GetCompLen<T, TQ1, TQ2, TestStrType::DiffCase>();
			const size_t compLenShorter = GetCompLen<T, TQ1, TQ2, TestStrType::Shorter>();
			const size_t compLenLonger = GetCompLen<T, TQ1, TQ2, TestStrType::Longer>();

			constexpr size_t len = GetTQNum<TQ1>();
			const std::vector<std::tuple<const T*, size_t, bool>> testStrTuples
			{
				{GetTestCStr<T, TQ1>(), compLenReg, (compLenReg <= len)},
				{GetDiffCaseTestCStr<T, TQ1>(), compLenDiffCase, ((bCaseInsensitive || (compLenDiffCase == 0)) && (compLenDiffCase <= len))},
			    {GetShorterTestCStr<T, TQ1>(), compLenShorter, (compLenShorter <= len)},
			    {GetLongerTestCStr<T, TQ1>(), compLenLonger, (compLenLonger <= len)}
			};

			String<T> str(GetTestCStr<T, TQ1>());
			for (const auto& testTuple : testStrTuples)
			{
				const T* testCStr = std::get<0>(testTuple);
				const size_t compLen = std::get<1>(testTuple);
				const bool bExpectedResult = std::get<2>(testTuple);
				SUTL_TEST_ASSERT(str.Compare<bCaseInsensitive>(testCStr, compLen) == bExpectedResult);
			}

			SUTL_TEST_SUCCESS();
        }

        template <typename T, TestQuantity TQ, bool bCaseInsensitive>
        [[nodiscard]] static UTR StrObjCompare( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			std::vector<std::pair<String<T>, bool>> testStrPairs
			{
				std::pair<String<T>, bool>(GetTestCStr<T, TQ>(), true),
				std::pair<String<T>, bool>(GetDiffCaseTestCStr<T, TQ>(), (bCaseInsensitive || len == 0)),
				std::pair<String<T>, bool>(GetShorterTestCStr<T, TQ>(), (len == 0)),
				std::pair<String<T>, bool>(GetLongerTestCStr<T, TQ>(), (len == 0)),
			};

			String<T> str(GetTestCStr<T, TQ>());
			for (const auto& testPair : testStrPairs)
			{
				const String<T>& testStr = testPair.first;
				const bool bExpectedResult = testPair.second;
				SUTL_TEST_ASSERT(str.Compare<bCaseInsensitive>(testStr) == bExpectedResult);
			}

			SUTL_TEST_SUCCESS();
        }
		
		template <typename T, TestQuantity TQ1, TestQuantity TQ2, bool bCaseInsensitive>
		[[nodiscard]] static UTR StrObjAndLenCompare( )
		{
			const size_t compLenReg = GetCompLen<T, TQ1, TQ2, TestStrType::Regular>();
			const size_t compLenDiffCase = GetCompLen<T, TQ1, TQ2, TestStrType::DiffCase>();
			const size_t compLenShorter = GetCompLen<T, TQ1, TQ2, TestStrType::Shorter>();
			const size_t compLenLonger = GetCompLen<T, TQ1, TQ2, TestStrType::Longer>();

			constexpr size_t len = GetTQNum<TQ1>();
			using TestTuple = std::tuple<String<T>, size_t, bool>;
			const std::vector<TestTuple> testStrTuples
			{
				TestTuple(GetTestCStr<T, TQ1>(), compLenReg, (compLenReg <= len)),
				TestTuple(GetDiffCaseTestCStr<T, TQ1>(), compLenDiffCase, ((bCaseInsensitive || (compLenDiffCase == 0)) && (compLenDiffCase <= len))),
				TestTuple(GetShorterTestCStr<T, TQ1>(), compLenShorter, (compLenShorter <= len)),
				TestTuple(GetLongerTestCStr<T, TQ1>(), compLenLonger, (compLenLonger <= len))
			};

			String<T> str(GetTestCStr<T, TQ1>());
			for (const auto& testTuple : testStrTuples)
			{
				const String<T>& testStr = std::get<0>(testTuple);
				const size_t compLen = std::get<1>(testTuple);
				const bool bExpectedResult = std::get<2>(testTuple);
				SUTL_TEST_ASSERT(str.Compare<bCaseInsensitive>(testStr, compLen) == bExpectedResult);
			}

			SUTL_TEST_SUCCESS();
		}
    };


    // Tests Clear behavior.
    class StringTests::ClearTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR Clear( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str(testCStr, len);
			SUTL_SETUP_ASSERT(!!str.CStr());
			SUTL_SETUP_ASSERT(str.Length() == len);
			SUTL_SETUP_ASSERT(memcmp(str.CStr(), testCStr, sizeof(T) * (len + 1)) == 0);

			str.Clear(); 
			if constexpr (len >= String<T>::ms_SSOCap)
			{
				SUTL_TEST_ASSERT(str.CStr() == str.m_SSOArr);
			}

			SUTL_TEST_ASSERT(!!str.CStr());
			SUTL_TEST_ASSERT(str.Length() == 0);
			SUTL_TEST_ASSERT(str.CStr()[0] == String<T>::ms_NullTerminator);
			
			SUTL_TEST_SUCCESS();
        }
    };


    // Tests IsEmpty behavior.
    class StringTests::IsEmptyTests
    {
    public:

        template <typename T, TestQuantity TQ>
        [[nodiscard]] static UTR IsEmpty( )
        {
			constexpr size_t len = GetTQNum<TQ>();
			const T* const testCStr = GetTestCStr<T, TQ>();

			String<T> str;
			SUTL_TEST_ASSERT(str.IsEmpty());

			SUTL_SETUP_ASSERT(str.Assign(testCStr, len));
			SUTL_TEST_ASSERT(str.IsEmpty() == (len == 0));

			str.Clear();
			SUTL_TEST_ASSERT(str.IsEmpty());

			str = String<T>();
			SUTL_TEST_ASSERT(str.IsEmpty());

			SUTL_TEST_SUCCESS();
        }
    };
}