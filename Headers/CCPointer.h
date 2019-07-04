#pragma once

// CC
#include "CCMacros.h"
#include "CCIPointer.h"
#include "CCPointerCommonHelpers.h"

// STL
#include <stdexcept>


namespace CC
{
    template <typename T>
    class [[nodiscard]] Pointer : public IPointer<T>, public PointerCommonHelpers<T>
    {
        // Testing class.
        friend class PointerTests;

        // Type Alias
        using PCH = PointerCommonHelpers<T>;

    protected:

        /// Protected Data Members \\\

        T* m_pPtr;
        size_t m_Len;

        /// Static Protected Helper Methods \\\

        // Copies all Pointer data members from source Pointer object.
        // Note: The pointer data member is shallow copied.
        static void CopyAllDataMembers(_Out_ Pointer<T>& dst, _In_ IPointer<T>& src) noexcept
        {
            dst.m_pPtr = src.Get( );
            dst.m_Len = src.Length( );
        }

        // Performs deep copy of src pointer, frees dst pointer, then assigned new pointer to dst.
        // Also copies all other Pointer data members of src to dst.
        // Note: If src pointer is nullptr, then dst will free its pointer and replace it with nullptr.
        static void CopyPointerObj(_Inout_ Pointer<T>& dst, _In_ const IPointer<T>& src) noexcept(CC_IS_NOTHROW_CTOR_DEFAULT(T) && CC_IS_NOTHROW_COPY(T))
        {
            T* p = PCH::AllocateFromIPointerObj(src);
            dst.InvokeFreeFunction( );
            dst.m_pPtr = p;
            dst.m_Len = src.Length( );
        }

        // Performs shallow copy of src Pointer data members to dst, then resets src.
        static void TransferPointerObj(_Inout_ Pointer<T>& dst, _Inout_ IPointer<T>& src) noexcept
        {
            dst.InvokeFreeFunction( );
            CopyAllDataMembers(dst, src);
            src.Reset( );
        }

        /// Protected Helper Methods \\\

        // Calls the appropriate cleanup function.
        void InvokeFreeFunction( ) noexcept
        {
            if ( m_Len == 1 )
            {
                delete m_pPtr;
            }
            else
            {
                delete[ ] m_pPtr;
            }

            Reset( );
        }

    public:

        /// Public Constructors \\\

        // Default constructor
        constexpr Pointer( ) noexcept :
            m_pPtr(nullptr),
            m_Len(0)
        { }

        // Pointer length constructor
        explicit Pointer(_In_ const size_t& len) noexcept :
            m_pPtr(PCH::Allocate(len)),
            m_Len((!!m_pPtr) ? len : 0)
        { }

        // Raw pointer copy constructor
        Pointer(_In_reads_opt_(len) const T* p, _In_ const size_t& len) noexcept(CC_IS_NOTHROW_CTOR_DEFAULT(T) && CC_IS_NOTHROW_COPY(T)) :
            m_pPtr(PCH::AllocateFromRawPointer(p, len)),
            m_Len((!!m_pPtr) ? len : 0)
        { }

        // Raw pointer steal constructor
        Pointer(_Inout_opt_ T*&p, _In_ const size_t& len) noexcept :
            m_pPtr(p),
            m_Len((!!m_pPtr) ? len : 0)
        {
            p = nullptr;
        }

        // Copy constructor
        Pointer(_In_ const Pointer<T>& src) noexcept(CC_IS_NOTHROW_CTOR_DEFAULT(T) && CC_IS_NOTHROW_COPY(T)) :
            m_pPtr(PCH::AllocateFromIPointerObj(src)),
            m_Len((!!m_pPtr) ? src.m_Len : 0)
        { }

        // Move constructor
        Pointer(_Inout_ Pointer<T>&& src) noexcept :
            m_pPtr(src.m_pPtr),
            m_Len(src.m_Len)
        {
            src.Reset( );
        }

        /// Public Destructor \\\

        // Destructor
        virtual ~Pointer( ) noexcept
        {
            InvokeFreeFunction( );
        }

        /// Operator Overloads \\\

        // Copy assignment
        Pointer<T>& operator=(_In_ const Pointer<T>& src) noexcept(CC_IS_NOTHROW_CTOR_DEFAULT(T) && CC_IS_NOTHROW_COPY(T))
        {
            if ( this != &src )
            {
                CopyPointerObj(*this, src);
            }

            return *this;
        }

        // Move assignment
        Pointer<T>& operator=(_Inout_ Pointer<T>&& src) noexcept
        {
            if ( this != &src )
            {
                TransferPointerObj(*this, src);
            }

            return *this;
        }

        // bool overload - returns true if m_pPtr != nullptr, false otherwise.
        [[nodiscard]] virtual explicit operator bool( ) const noexcept
        {
            return !!m_pPtr;
        }

        // T* overload - returns pointer to mutable internal pointer.
        [[nodiscard]] _Ret_maybenull_ virtual explicit operator T*() noexcept
        {
            return m_pPtr;
        }

        // const T* overload - returns pointer to immutable internal pointer.
        [[nodiscard]] _Ret_maybenull_ virtual explicit operator const T*() const noexcept
        {
            return m_pPtr;
        }

        // Dereference overload - returns reference to first element from internal pointer (mutable).
        // Note: Will throw std::logic_error if m_pPtr == nullptr.
        [[nodiscard]] virtual T& operator*( )
        {
            PCH::ValidateDereferenceT(__FUNCSIG__, m_pPtr);
            return *m_pPtr;
        }

        // Dereference overload - returns reference to first element from internal pointer (immutable).
        // Note: Will throw std::logic_error if m_pPtr == nullptr.
        [[nodiscard]] virtual const T& operator*( ) const
        {
            PCH::ValidateDereferenceT(__FUNCSIG__, m_pPtr);
            return *m_pPtr;
        }

        // Pointer-member-access overload - returns reference to internal pointer (mutable).
        // Note: Will throw std::logic_error if m_pPtr == nullptr.
        [[nodiscard]] virtual T* operator->( )
        {
            // Technically not dereferencing here, but the intention is likely to access a data member.
            PCH::ValidateDereferenceT(__FUNCSIG__, m_pPtr);
            return m_pPtr;
        }

        // Pointer-member-access overload - returns reference to internal pointer (immutable).
        // Note: Will throw std::logic_error if m_pPtr == nullptr.
        [[nodiscard]] virtual const T* operator->( ) const
        {
            // Technically not dereferencing here, but the intention is likely to access a data member.
            PCH::ValidateDereferenceT(__FUNCSIG__, m_pPtr);
            return m_pPtr;
        }

        /// Getters \\\

        // Returns pointer to internal pointer (mutable).
        [[nodiscard]] _Ret_maybenull_ virtual T* Get( ) noexcept
        {
            return m_pPtr;
        }

        // Returns pointer to internal pointer (immutable).
        [[nodiscard]] _Ret_maybenull_ virtual const T* Get( ) const noexcept
        {
            return m_pPtr;
        }

        // Returns length of internal pointer.
        [[nodiscard]] virtual const size_t& Length( ) const noexcept
        {
            return m_Len;
        }

        // Returns size in bytes of internal pointer.
        [[nodiscard]] virtual const size_t Size( ) const noexcept
        {
            return sizeof(T) * m_Len;
        }

        /// Public Methods \\\

        // Resets internal data members to default values.
        // Note: This will not free any internal resources - use with caution.
        virtual void Reset( ) noexcept
        {
            m_pPtr = nullptr;
            m_Len = 0;
        }

        // Causes the pointer to free any resources, resetting data members to their default values.
        virtual void Free( ) noexcept
        {
            InvokeFreeFunction( );
        }
    };
}