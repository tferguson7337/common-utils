#include <CCSharedPointerTests.h>

CC::SharedPointerTests::UTList CC::SharedPointerTests::GetTests()
{
    using TQ = TestQuantity;
    static const UTList tests
    {
        ConstructorTests::DefaultCtor<uint8_t>,
        ConstructorTests::DefaultCtor<uint16_t>,
        ConstructorTests::DefaultCtor<uint32_t>,
        ConstructorTests::DefaultCtor<uint64_t>,
        ConstructorTests::DefaultCtor<Helper>,

        ConstructorTests::LengthCtor<uint8_t, TQ::None>,
        ConstructorTests::LengthCtor<uint8_t, TQ::VeryLow>,
        ConstructorTests::LengthCtor<uint8_t, TQ::High>,
        ConstructorTests::LengthCtor<uint16_t, TQ::None>,
        ConstructorTests::LengthCtor<uint16_t, TQ::VeryLow>,
        ConstructorTests::LengthCtor<uint16_t, TQ::High>,
        ConstructorTests::LengthCtor<uint32_t, TQ::None>,
        ConstructorTests::LengthCtor<uint32_t, TQ::VeryLow>,
        ConstructorTests::LengthCtor<uint32_t, TQ::High>,
        ConstructorTests::LengthCtor<uint64_t, TQ::None>,
        ConstructorTests::LengthCtor<uint64_t, TQ::VeryLow>,
        ConstructorTests::LengthCtor<uint64_t, TQ::High>,
        ConstructorTests::LengthCtor<Helper, TQ::None>,
        ConstructorTests::LengthCtor<Helper, TQ::VeryLow>,
        ConstructorTests::LengthCtor<Helper, TQ::High>,

        ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::None>,
        ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::VeryLow>,
        ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::High>,
        ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::None>,
        ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::VeryLow>,
        ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::High>,
        ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::None>,
        ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::VeryLow>,
        ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::High>,
        ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::None>,
        ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::VeryLow>,
        ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::High>,
        ConstructorTests::RawPointerCopyCtor<Helper, TQ::None>,
        ConstructorTests::RawPointerCopyCtor<Helper, TQ::VeryLow>,
        ConstructorTests::RawPointerCopyCtor<Helper, TQ::High>,

        ConstructorTests::RawPointerStealCtor<uint8_t, TQ::None>,
        ConstructorTests::RawPointerStealCtor<uint8_t, TQ::VeryLow>,
        ConstructorTests::RawPointerStealCtor<uint8_t, TQ::High>,
        ConstructorTests::RawPointerStealCtor<uint16_t, TQ::None>,
        ConstructorTests::RawPointerStealCtor<uint16_t, TQ::VeryLow>,
        ConstructorTests::RawPointerStealCtor<uint16_t, TQ::High>,
        ConstructorTests::RawPointerStealCtor<uint32_t, TQ::None>,
        ConstructorTests::RawPointerStealCtor<uint32_t, TQ::VeryLow>,
        ConstructorTests::RawPointerStealCtor<uint32_t, TQ::High>,
        ConstructorTests::RawPointerStealCtor<uint64_t, TQ::None>,
        ConstructorTests::RawPointerStealCtor<uint64_t, TQ::VeryLow>,
        ConstructorTests::RawPointerStealCtor<uint64_t, TQ::High>,
        ConstructorTests::RawPointerStealCtor<Helper, TQ::None>,
        ConstructorTests::RawPointerStealCtor<Helper, TQ::VeryLow>,
        ConstructorTests::RawPointerStealCtor<Helper, TQ::High>,

        ConstructorTests::CopyCtor<uint8_t, TQ::None>,
        ConstructorTests::CopyCtor<uint8_t, TQ::VeryLow>,
        ConstructorTests::CopyCtor<uint8_t, TQ::High>,
        ConstructorTests::CopyCtor<uint16_t, TQ::None>,
        ConstructorTests::CopyCtor<uint16_t, TQ::VeryLow>,
        ConstructorTests::CopyCtor<uint16_t, TQ::High>,
        ConstructorTests::CopyCtor<uint32_t, TQ::None>,
        ConstructorTests::CopyCtor<uint32_t, TQ::VeryLow>,
        ConstructorTests::CopyCtor<uint32_t, TQ::High>,
        ConstructorTests::CopyCtor<uint64_t, TQ::None>,
        ConstructorTests::CopyCtor<uint64_t, TQ::VeryLow>,
        ConstructorTests::CopyCtor<uint64_t, TQ::High>,
        ConstructorTests::CopyCtor<Helper, TQ::None>,
        ConstructorTests::CopyCtor<Helper, TQ::VeryLow>,
        ConstructorTests::CopyCtor<Helper, TQ::High>,

        ConstructorTests::MoveCtor<uint8_t, TQ::None>,
        ConstructorTests::MoveCtor<uint8_t, TQ::VeryLow>,
        ConstructorTests::MoveCtor<uint8_t, TQ::High>,
        ConstructorTests::MoveCtor<uint16_t, TQ::None>,
        ConstructorTests::MoveCtor<uint16_t, TQ::VeryLow>,
        ConstructorTests::MoveCtor<uint16_t, TQ::High>,
        ConstructorTests::MoveCtor<uint32_t, TQ::None>,
        ConstructorTests::MoveCtor<uint32_t, TQ::VeryLow>,
        ConstructorTests::MoveCtor<uint32_t, TQ::High>,
        ConstructorTests::MoveCtor<uint64_t, TQ::None>,
        ConstructorTests::MoveCtor<uint64_t, TQ::VeryLow>,
        ConstructorTests::MoveCtor<uint64_t, TQ::High>,
        ConstructorTests::MoveCtor<Helper, TQ::None>,
        ConstructorTests::MoveCtor<Helper, TQ::VeryLow>,
        ConstructorTests::MoveCtor<Helper, TQ::High>,

        DestructorTests::Dtor<uint8_t, TQ::None>,
        DestructorTests::Dtor<uint8_t, TQ::VeryLow>,
        DestructorTests::Dtor<uint8_t, TQ::High>,
        DestructorTests::Dtor<uint16_t, TQ::None>,
        DestructorTests::Dtor<uint16_t, TQ::VeryLow>,
        DestructorTests::Dtor<uint16_t, TQ::High>,
        DestructorTests::Dtor<uint32_t, TQ::None>,
        DestructorTests::Dtor<uint32_t, TQ::VeryLow>,
        DestructorTests::Dtor<uint32_t, TQ::High>,
        DestructorTests::Dtor<uint64_t, TQ::None>,
        DestructorTests::Dtor<uint64_t, TQ::VeryLow>,
        DestructorTests::Dtor<uint64_t, TQ::High>,
        DestructorTests::Dtor<Helper, TQ::None>,
        DestructorTests::Dtor<Helper, TQ::VeryLow>,
        DestructorTests::Dtor<Helper, TQ::High>,

        AssignmentTests::CopyAssignment<uint8_t, TQ::None>,
        AssignmentTests::CopyAssignment<uint8_t, TQ::VeryLow>,
        AssignmentTests::CopyAssignment<uint8_t, TQ::High>,
        AssignmentTests::CopyAssignment<uint16_t, TQ::None>,
        AssignmentTests::CopyAssignment<uint16_t, TQ::VeryLow>,
        AssignmentTests::CopyAssignment<uint16_t, TQ::High>,
        AssignmentTests::CopyAssignment<uint32_t, TQ::None>,
        AssignmentTests::CopyAssignment<uint32_t, TQ::VeryLow>,
        AssignmentTests::CopyAssignment<uint32_t, TQ::High>,
        AssignmentTests::CopyAssignment<uint64_t, TQ::None>,
        AssignmentTests::CopyAssignment<uint64_t, TQ::VeryLow>,
        AssignmentTests::CopyAssignment<uint64_t, TQ::High>,
        AssignmentTests::CopyAssignment<Helper, TQ::None>,
        AssignmentTests::CopyAssignment<Helper, TQ::VeryLow>,
        AssignmentTests::CopyAssignment<Helper, TQ::High>,

        AssignmentTests::MoveAssignment<uint8_t, TQ::None>,
        AssignmentTests::MoveAssignment<uint8_t, TQ::VeryLow>,
        AssignmentTests::MoveAssignment<uint8_t, TQ::High>,
        AssignmentTests::MoveAssignment<uint16_t, TQ::None>,
        AssignmentTests::MoveAssignment<uint16_t, TQ::VeryLow>,
        AssignmentTests::MoveAssignment<uint16_t, TQ::High>,
        AssignmentTests::MoveAssignment<uint32_t, TQ::None>,
        AssignmentTests::MoveAssignment<uint32_t, TQ::VeryLow>,
        AssignmentTests::MoveAssignment<uint32_t, TQ::High>,
        AssignmentTests::MoveAssignment<uint64_t, TQ::None>,
        AssignmentTests::MoveAssignment<uint64_t, TQ::VeryLow>,
        AssignmentTests::MoveAssignment<uint64_t, TQ::High>,
        AssignmentTests::MoveAssignment<Helper, TQ::None>,
        AssignmentTests::MoveAssignment<Helper, TQ::VeryLow>,
        AssignmentTests::MoveAssignment<Helper, TQ::High>,

        RefCountTests::MTIncrement<uint8_t, TQ::None>,
        RefCountTests::MTIncrement<uint8_t, TQ::VeryLow>,
        RefCountTests::MTIncrement<uint8_t, TQ::High>,
        RefCountTests::MTIncrement<uint16_t, TQ::None>,
        RefCountTests::MTIncrement<uint16_t, TQ::VeryLow>,
        RefCountTests::MTIncrement<uint16_t, TQ::High>,
        RefCountTests::MTIncrement<uint32_t, TQ::None>,
        RefCountTests::MTIncrement<uint32_t, TQ::VeryLow>,
        RefCountTests::MTIncrement<uint32_t, TQ::High>,
        RefCountTests::MTIncrement<uint64_t, TQ::None>,
        RefCountTests::MTIncrement<uint64_t, TQ::VeryLow>,
        RefCountTests::MTIncrement<uint64_t, TQ::High>,
        RefCountTests::MTIncrement<Helper, TQ::None>,
        RefCountTests::MTIncrement<Helper, TQ::VeryLow>,
        RefCountTests::MTIncrement<Helper, TQ::High>,

        RefCountTests::MTDecrement<uint8_t, TQ::None>,
        RefCountTests::MTDecrement<uint8_t, TQ::VeryLow>,
        RefCountTests::MTDecrement<uint8_t, TQ::High>,
        RefCountTests::MTDecrement<uint16_t, TQ::None>,
        RefCountTests::MTDecrement<uint16_t, TQ::VeryLow>,
        RefCountTests::MTDecrement<uint16_t, TQ::High>,
        RefCountTests::MTDecrement<uint32_t, TQ::None>,
        RefCountTests::MTDecrement<uint32_t, TQ::VeryLow>,
        RefCountTests::MTDecrement<uint32_t, TQ::High>,
        RefCountTests::MTDecrement<uint64_t, TQ::None>,
        RefCountTests::MTDecrement<uint64_t, TQ::VeryLow>,
        RefCountTests::MTDecrement<uint64_t, TQ::High>,
        RefCountTests::MTDecrement<Helper, TQ::None>,
        RefCountTests::MTDecrement<Helper, TQ::VeryLow>,
        RefCountTests::MTDecrement<Helper, TQ::High>,

        RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::None>,
        RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::VeryLow>,
        RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::High>,
        RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::None>,
        RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::VeryLow>,
        RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::High>,
        RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::None>,
        RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::VeryLow>,
        RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::High>,
        RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::None>,
        RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::VeryLow>,
        RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::High>,
        RefCountTests::MTIncrementAndDecrement<Helper, TQ::None>,
        RefCountTests::MTIncrementAndDecrement<Helper, TQ::VeryLow>,
        RefCountTests::MTIncrementAndDecrement<Helper, TQ::High>
    };

    return tests;
}