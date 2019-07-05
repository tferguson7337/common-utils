#include <CCSharedPointerTests.h>

CC::SharedPointerTests::UTList CC::SharedPointerTests::GetTests( )
{
    using TQ = TestQuantity;
    static const UTList tests
    {
        SharedPointerTests::ConstructorTests::DefaultCtor<uint8_t>,
        SharedPointerTests::ConstructorTests::DefaultCtor<uint16_t>,
        SharedPointerTests::ConstructorTests::DefaultCtor<uint32_t>,
        SharedPointerTests::ConstructorTests::DefaultCtor<uint64_t>,
        SharedPointerTests::ConstructorTests::DefaultCtor<Helper>,

        SharedPointerTests::ConstructorTests::LengthCtor<uint8_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint8_t, TQ::One>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint8_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint16_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint16_t, TQ::One>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint16_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint32_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint32_t, TQ::One>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint32_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint64_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint64_t, TQ::One>,
        SharedPointerTests::ConstructorTests::LengthCtor<uint64_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::LengthCtor<Helper, TQ::Zero>,
        SharedPointerTests::ConstructorTests::LengthCtor<Helper, TQ::One>,
        SharedPointerTests::ConstructorTests::LengthCtor<Helper, TQ::Many>,

        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint8_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint16_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint32_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<uint64_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<Helper, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<Helper, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerCopyCtor<Helper, TQ::Many>,

        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint8_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint8_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint8_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint16_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint16_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint16_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint32_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint32_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint32_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint64_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint64_t, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<uint64_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<Helper, TQ::Zero>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<Helper, TQ::One>,
        SharedPointerTests::ConstructorTests::RawPointerStealCtor<Helper, TQ::Many>,

        SharedPointerTests::ConstructorTests::CopyCtor<uint8_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint8_t, TQ::One>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint8_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint16_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint16_t, TQ::One>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint16_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint32_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint32_t, TQ::One>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint32_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint64_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint64_t, TQ::One>,
        SharedPointerTests::ConstructorTests::CopyCtor<uint64_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::CopyCtor<Helper, TQ::Zero>,
        SharedPointerTests::ConstructorTests::CopyCtor<Helper, TQ::One>,
        SharedPointerTests::ConstructorTests::CopyCtor<Helper, TQ::Many>,

        SharedPointerTests::ConstructorTests::MoveCtor<uint8_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint8_t, TQ::One>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint8_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint16_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint16_t, TQ::One>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint16_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint32_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint32_t, TQ::One>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint32_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint64_t, TQ::Zero>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint64_t, TQ::One>,
        SharedPointerTests::ConstructorTests::MoveCtor<uint64_t, TQ::Many>,
        SharedPointerTests::ConstructorTests::MoveCtor<Helper, TQ::Zero>,
        SharedPointerTests::ConstructorTests::MoveCtor<Helper, TQ::One>,
        SharedPointerTests::ConstructorTests::MoveCtor<Helper, TQ::Many>,

        SharedPointerTests::DestructorTests::Dtor<uint8_t, TQ::Zero>,
        SharedPointerTests::DestructorTests::Dtor<uint8_t, TQ::One>,
        SharedPointerTests::DestructorTests::Dtor<uint8_t, TQ::Many>,
        SharedPointerTests::DestructorTests::Dtor<uint16_t, TQ::Zero>,
        SharedPointerTests::DestructorTests::Dtor<uint16_t, TQ::One>,
        SharedPointerTests::DestructorTests::Dtor<uint16_t, TQ::Many>,
        SharedPointerTests::DestructorTests::Dtor<uint32_t, TQ::Zero>,
        SharedPointerTests::DestructorTests::Dtor<uint32_t, TQ::One>,
        SharedPointerTests::DestructorTests::Dtor<uint32_t, TQ::Many>,
        SharedPointerTests::DestructorTests::Dtor<uint64_t, TQ::Zero>,
        SharedPointerTests::DestructorTests::Dtor<uint64_t, TQ::One>,
        SharedPointerTests::DestructorTests::Dtor<uint64_t, TQ::Many>,
        SharedPointerTests::DestructorTests::Dtor<Helper, TQ::Zero>,
        SharedPointerTests::DestructorTests::Dtor<Helper, TQ::One>,
        SharedPointerTests::DestructorTests::Dtor<Helper, TQ::Many>,

        SharedPointerTests::AssignmentTests::CopyAssignment<uint8_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint8_t, TQ::One>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint8_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint16_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint16_t, TQ::One>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint16_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint32_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint32_t, TQ::One>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint32_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint64_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint64_t, TQ::One>,
        SharedPointerTests::AssignmentTests::CopyAssignment<uint64_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::CopyAssignment<Helper, TQ::Zero>,
        SharedPointerTests::AssignmentTests::CopyAssignment<Helper, TQ::One>,
        SharedPointerTests::AssignmentTests::CopyAssignment<Helper, TQ::Many>,

        SharedPointerTests::AssignmentTests::MoveAssignment<uint8_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint8_t, TQ::One>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint8_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint16_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint16_t, TQ::One>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint16_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint32_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint32_t, TQ::One>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint32_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint64_t, TQ::Zero>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint64_t, TQ::One>,
        SharedPointerTests::AssignmentTests::MoveAssignment<uint64_t, TQ::Many>,
        SharedPointerTests::AssignmentTests::MoveAssignment<Helper, TQ::Zero>,
        SharedPointerTests::AssignmentTests::MoveAssignment<Helper, TQ::One>,
        SharedPointerTests::AssignmentTests::MoveAssignment<Helper, TQ::Many>,

        SharedPointerTests::RefCountTests::MTIncrement<uint8_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrement<uint8_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrement<uint8_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrement<uint16_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrement<uint16_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrement<uint16_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrement<uint32_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrement<uint32_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrement<uint32_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrement<uint64_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrement<uint64_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrement<uint64_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrement<Helper, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrement<Helper, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrement<Helper, TQ::Many>,

        SharedPointerTests::RefCountTests::MTDecrement<uint8_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTDecrement<uint8_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTDecrement<uint8_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTDecrement<uint16_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTDecrement<uint16_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTDecrement<uint16_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTDecrement<uint32_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTDecrement<uint32_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTDecrement<uint32_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTDecrement<uint64_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTDecrement<uint64_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTDecrement<uint64_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTDecrement<Helper, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTDecrement<Helper, TQ::One>,
        SharedPointerTests::RefCountTests::MTDecrement<Helper, TQ::Many>,

        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint8_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint16_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint32_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<uint64_t, TQ::Many>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<Helper, TQ::Zero>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<Helper, TQ::One>,
        SharedPointerTests::RefCountTests::MTIncrementAndDecrement<Helper, TQ::Many>
    };

    return tests;
}