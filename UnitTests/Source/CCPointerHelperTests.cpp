#include <CCPointerHelperTests.h>

CC::PointerHelperTests::UTList CC::PointerHelperTests::GetTests()
{
    using TQ = TestQuantity;

    static const UTList tests
    {
        CopyToRawPointer<uint8_t, TQ::None>,
        CopyToRawPointer<uint8_t, TQ::VeryLow>,
        CopyToRawPointer<uint8_t, TQ::Low>,
        CopyToRawPointer<uint8_t, TQ::Mid>,
        CopyToRawPointer<uint8_t, TQ::High>,
        CopyToRawPointer<uint16_t, TQ::None>,
        CopyToRawPointer<uint16_t, TQ::VeryLow>,
        CopyToRawPointer<uint16_t, TQ::Low>,
        CopyToRawPointer<uint16_t, TQ::Mid>,
        CopyToRawPointer<uint16_t, TQ::High>,
        CopyToRawPointer<uint32_t, TQ::None>,
        CopyToRawPointer<uint32_t, TQ::VeryLow>,
        CopyToRawPointer<uint32_t, TQ::Low>,
        CopyToRawPointer<uint32_t, TQ::Mid>,
        CopyToRawPointer<uint32_t, TQ::High>,
        CopyToRawPointer<uint64_t, TQ::None>,
        CopyToRawPointer<uint64_t, TQ::VeryLow>,
        CopyToRawPointer<uint64_t, TQ::Low>,
        CopyToRawPointer<uint64_t, TQ::Mid>,
        CopyToRawPointer<uint64_t, TQ::High>,
        CopyToRawPointer<Helper, TQ::None>,
        CopyToRawPointer<Helper, TQ::VeryLow>,
        CopyToRawPointer<Helper, TQ::Low>,
        CopyToRawPointer<Helper, TQ::Mid>,
        CopyToRawPointer<Helper, TQ::High>,

        MoveToRawPointer<uint8_t, TQ::None>,
        MoveToRawPointer<uint8_t, TQ::VeryLow>,
        MoveToRawPointer<uint8_t, TQ::Low>,
        MoveToRawPointer<uint8_t, TQ::Mid>,
        MoveToRawPointer<uint8_t, TQ::High>,
        MoveToRawPointer<uint16_t, TQ::None>,
        MoveToRawPointer<uint16_t, TQ::VeryLow>,
        MoveToRawPointer<uint16_t, TQ::Low>,
        MoveToRawPointer<uint16_t, TQ::Mid>,
        MoveToRawPointer<uint16_t, TQ::High>,
        MoveToRawPointer<uint32_t, TQ::None>,
        MoveToRawPointer<uint32_t, TQ::VeryLow>,
        MoveToRawPointer<uint32_t, TQ::Low>,
        MoveToRawPointer<uint32_t, TQ::Mid>,
        MoveToRawPointer<uint32_t, TQ::High>,
        MoveToRawPointer<uint64_t, TQ::None>,
        MoveToRawPointer<uint64_t, TQ::VeryLow>,
        MoveToRawPointer<uint64_t, TQ::Low>,
        MoveToRawPointer<uint64_t, TQ::Mid>,
        MoveToRawPointer<uint64_t, TQ::High>,
        MoveToRawPointer<Helper, TQ::None>,
        MoveToRawPointer<Helper, TQ::VeryLow>,
        MoveToRawPointer<Helper, TQ::Low>,
        MoveToRawPointer<Helper, TQ::Mid>,
        MoveToRawPointer<Helper, TQ::High>,

        Allocate<uint8_t, TQ::None>,
        Allocate<uint8_t, TQ::VeryLow>,
        Allocate<uint8_t, TQ::Low>,
        Allocate<uint8_t, TQ::Mid>,
        Allocate<uint8_t, TQ::High>,
        Allocate<uint16_t, TQ::None>,
        Allocate<uint16_t, TQ::VeryLow>,
        Allocate<uint16_t, TQ::Low>,
        Allocate<uint16_t, TQ::Mid>,
        Allocate<uint16_t, TQ::High>,
        Allocate<uint32_t, TQ::None>,
        Allocate<uint32_t, TQ::VeryLow>,
        Allocate<uint32_t, TQ::Low>,
        Allocate<uint32_t, TQ::Mid>,
        Allocate<uint32_t, TQ::High>,
        Allocate<uint64_t, TQ::None>,
        Allocate<uint64_t, TQ::VeryLow>,
        Allocate<uint64_t, TQ::Low>,
        Allocate<uint64_t, TQ::Mid>,
        Allocate<uint64_t, TQ::High>,
        Allocate<Helper, TQ::None>,
        Allocate<Helper, TQ::VeryLow>,
        Allocate<Helper, TQ::Low>,
        Allocate<Helper, TQ::Mid>,
        Allocate<Helper, TQ::High>,

        AllocateLen<uint8_t, TQ::None>,
        AllocateLen<uint8_t, TQ::VeryLow>,
        AllocateLen<uint8_t, TQ::Low>,
        AllocateLen<uint8_t, TQ::Mid>,
        AllocateLen<uint8_t, TQ::High>,
        AllocateLen<uint16_t, TQ::None>,
        AllocateLen<uint16_t, TQ::VeryLow>,
        AllocateLen<uint16_t, TQ::Low>,
        AllocateLen<uint16_t, TQ::Mid>,
        AllocateLen<uint16_t, TQ::High>,
        AllocateLen<uint32_t, TQ::None>,
        AllocateLen<uint32_t, TQ::VeryLow>,
        AllocateLen<uint32_t, TQ::Low>,
        AllocateLen<uint32_t, TQ::Mid>,
        AllocateLen<uint32_t, TQ::High>,
        AllocateLen<uint64_t, TQ::None>,
        AllocateLen<uint64_t, TQ::VeryLow>,
        AllocateLen<uint64_t, TQ::Low>,
        AllocateLen<uint64_t, TQ::Mid>,
        AllocateLen<uint64_t, TQ::High>,
        AllocateLen<Helper, TQ::None>,
        AllocateLen<Helper, TQ::VeryLow>,
        AllocateLen<Helper, TQ::Low>,
        AllocateLen<Helper, TQ::Mid>,
        AllocateLen<Helper, TQ::High>,

        AllocateFromRawPointer<uint8_t, TQ::None>,
        AllocateFromRawPointer<uint8_t, TQ::VeryLow>,
        AllocateFromRawPointer<uint8_t, TQ::Low>,
        AllocateFromRawPointer<uint8_t, TQ::Mid>,
        AllocateFromRawPointer<uint8_t, TQ::High>,
        AllocateFromRawPointer<uint16_t, TQ::None>,
        AllocateFromRawPointer<uint16_t, TQ::VeryLow>,
        AllocateFromRawPointer<uint16_t, TQ::Low>,
        AllocateFromRawPointer<uint16_t, TQ::Mid>,
        AllocateFromRawPointer<uint16_t, TQ::High>,
        AllocateFromRawPointer<uint32_t, TQ::None>,
        AllocateFromRawPointer<uint32_t, TQ::VeryLow>,
        AllocateFromRawPointer<uint32_t, TQ::Low>,
        AllocateFromRawPointer<uint32_t, TQ::Mid>,
        AllocateFromRawPointer<uint32_t, TQ::High>,
        AllocateFromRawPointer<uint64_t, TQ::None>,
        AllocateFromRawPointer<uint64_t, TQ::VeryLow>,
        AllocateFromRawPointer<uint64_t, TQ::Low>,
        AllocateFromRawPointer<uint64_t, TQ::Mid>,
        AllocateFromRawPointer<uint64_t, TQ::High>,
        AllocateFromRawPointer<Helper, TQ::None>,
        AllocateFromRawPointer<Helper, TQ::VeryLow>,
        AllocateFromRawPointer<Helper, TQ::Low>,
        AllocateFromRawPointer<Helper, TQ::Mid>,
        AllocateFromRawPointer<Helper, TQ::High>,

        AllocateFromIPointerObj<uint8_t, TQ::None>,
        AllocateFromIPointerObj<uint8_t, TQ::VeryLow>,
        AllocateFromIPointerObj<uint8_t, TQ::Low>,
        AllocateFromIPointerObj<uint8_t, TQ::Mid>,
        AllocateFromIPointerObj<uint8_t, TQ::High>,
        AllocateFromIPointerObj<uint16_t, TQ::None>,
        AllocateFromIPointerObj<uint16_t, TQ::VeryLow>,
        AllocateFromIPointerObj<uint16_t, TQ::Low>,
        AllocateFromIPointerObj<uint16_t, TQ::Mid>,
        AllocateFromIPointerObj<uint16_t, TQ::High>,
        AllocateFromIPointerObj<uint32_t, TQ::None>,
        AllocateFromIPointerObj<uint32_t, TQ::VeryLow>,
        AllocateFromIPointerObj<uint32_t, TQ::Low>,
        AllocateFromIPointerObj<uint32_t, TQ::Mid>,
        AllocateFromIPointerObj<uint32_t, TQ::High>,
        AllocateFromIPointerObj<uint64_t, TQ::None>,
        AllocateFromIPointerObj<uint64_t, TQ::VeryLow>,
        AllocateFromIPointerObj<uint64_t, TQ::Low>,
        AllocateFromIPointerObj<uint64_t, TQ::Mid>,
        AllocateFromIPointerObj<uint64_t, TQ::High>,
        AllocateFromIPointerObj<Helper, TQ::None>,
        AllocateFromIPointerObj<Helper, TQ::VeryLow>,
        AllocateFromIPointerObj<Helper, TQ::Low>,
        AllocateFromIPointerObj<Helper, TQ::Mid>,
        AllocateFromIPointerObj<Helper, TQ::High>
    };

    return tests;
}