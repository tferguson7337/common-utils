#pragma once

#include "CCPointerHelper.h"

#include <list>

namespace CC
{
    // Local macro helpers for targeted universal forwarders.
#define CC_IS_ELEMENT(_T, _U)\
        (std::is_same_v<std::decay_t<_U>, _T> ||\
        std::is_convertible_v<std::decay_t<_U>, _T>)

#define CC_IS_LIST(_T, _U)\
        (std::is_same_v<std::decay_t<_U>, List<_T>>)

#define CC_ENABLE_IF_ELEMENT(_T, _U)\
        typename = typename std::enable_if_t<CC_IS_ELEMENT(_T, _U)>

#define CC_ENABLE_IF_LIST(_T, _U)\
        typename = typename std::enable_if_t<CC_IS_LIST(_T, _U)>

#define CC_ENABLE_IF_LIST_OR_ELEMENT(_T, _U)    \
        typename = typename std::enable_if_t<CC_IS_LIST(_T, _U) || CC_IS_ELEMENT(_T, _U)>

    template <typename T, CC_ENABLE_IF_NOT_POINTER_TYPE(T)>
    class [[nodiscard]] List
    {
        // Testing class.
        friend class ListTests;

    private:

        // Helper Class - Doubly-linked list node.
        template <typename T>
        struct DNode
        {
            T data;
            DNode<T>* pPrev;
            DNode<T>* pNext;

            // Default constructor.
            DNode() noexcept(CC_IS_NOTHROW_CTOR_DEFAULT(T)) :
                data(T()),
                pPrev(nullptr),
                pNext(nullptr)
            { }

            // Constructor, targeted universal forwarder.
            template <typename U, CC_ENABLE_IF_ELEMENT(T, U)>
            DNode(_In_ U&& obj, _In_opt_ DNode<T>* pP = nullptr, _In_opt_ DNode<T>* pN = nullptr) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T)) :
                data(std::forward<U>(obj)),
                pPrev(pP),
                pNext(pN)
            {
                if (!!pP)
                {
                    pP->pNext = this;
                }

                if (!!pN)
                {
                    pN->pPrev = this;
                }
            }

            ~DNode() noexcept = default;

            // Prepend with targeted universal forwarder
            template <typename U, CC_ENABLE_IF_ELEMENT(T, U)>
            [[nodiscard]] _Success_(return) bool Prepend(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
            {
                // DNode<T> ctor handles link adjustments.
                return !!PointerHelper<DNode>::Allocate(std::forward<U>(obj), pPrev, this);
            }

            // Append with targeted universal forwarder
            template <typename U, CC_ENABLE_IF_ELEMENT(T, U)>
            [[nodiscard]] _Success_(return) bool Append(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
            {
                // DNode<T> ctor handles link adjustments.
                return !!PointerHelper<DNode>::Allocate(std::forward<U>(obj), this, pNext);
            }
        };


        /// Private Data Members \\\

        DNode<T>* m_pHead;
        DNode<T>* m_pTail;
        size_t m_Len;

        /// Private Throwing Validators \\\

        // Throws std::logic_error if this list is empty.
        inline void ValidateDereferenceT(_In_z_ const char* const f)
        {
            if (IsEmpty())
            {
                std::string msg(": Attempted invalid access on empty list.");
                throw std::logic_error(f + msg);
            }
        }

        // Throws std::logic_error if this list is empty.
        // Throws std::out_of_range if pos does not refer to a valid position in the list.
        inline void ValidateAccessAtPositionT(_In_z_ const char* const f, _In_ const size_t pos)
        {
            ValidateDereferenceT(f);
            if (pos >= m_Len)
            {
                std::string msg1(": Attempted to access out-of-range list position[");
                std::string dat1(std::to_string(pos));
                std::string msg2("]  Valid Range[0, ");
                std::string dat2(std::to_string(m_Len - 1));
                std::string msg3("].");
                throw std::out_of_range(f + msg1 + dat1 + msg2 + dat2 + msg3);
            }
        }

        /// Private Helper Methods \\\

        // Frees all list nodes.
        // Note: Does not reset all data members to default values.
        inline void DestroyList() noexcept
        {
            while (!!m_pHead)
            {
                DNode<T>* p = m_pHead;
                m_pHead = m_pHead->pNext;
                delete p;
            }
        }

        // Frees all list nodes and resets all data members to default values.
        template <bool bDestroy>
        inline void ResetList() noexcept
        {
            if constexpr (bDestroy)
            {
                DestroyList();
            }

            m_pHead = nullptr;
            m_pTail = nullptr;
            m_Len = 0;
        }

        // Returns node located at the specified position.
        // Note: Caller is expected to verify that specified position is valid.
        [[nodiscard]] _Ret_notnull_ DNode<T>* GetNodeAtPosition(_In_ const size_t pos) noexcept
        {
            DNode<T>* p = nullptr;
            if (pos <= (m_Len / 2))
            {
                p = m_pHead;
                for (size_t i = 0; i != pos; i++)
                {
                    p = p->pNext;
                }
            }
            else
            {
                p = m_pTail;
                for (size_t i = m_Len - 1; i != pos; i--)
                {
                    p = p->pPrev;
                }
            }

            return p;
        }

        // Appends copy of src list to this list.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool AppendListObj(_In_ const List<T>& src) noexcept(CC_IS_NOTHROW_CTOR_COPY(T))
        {
            // Copy list.
            List<T> tmp(src);

            if (src.IsEmpty())
            {
                // Nothing to append if src list is empty.
                return true;
            }

            // Ensure copy was successful, move-append tmp to this list.
            return !!tmp && AppendListObj(std::move(tmp));
        }

        // Transfers src list elements to this list via node links and reseting src's data members.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool AppendListObj(_Inout_ List<T>&& src) noexcept
        {
            if (IsEmpty())
            {
                // Append to empty list is same as assign.
                return AssignListObj(std::move(src));
            }

            // Adjust tail and length.
            m_pTail->pNext = src.m_pHead;
            src.m_pHead->pPrev = m_pTail;
            m_pTail = src.m_pTail;
            m_Len += src.m_Len;

            // this list now owns the resources, revoke src's ownership.
            src.ResetList<false>();

            return true;
        }

        // Append-element forwarder.
        // Appends an element to the end of this list via copy or move.
        // Returns true if operation succeeds, false otherwise.
        template <typename U>
        [[nodiscard]] _Success_(return) bool AppendElementObj(_In_ U&& elem) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Append to empty list is same as assign.
                return AssignElementObj(std::forward<U>(elem));
            }

            // Append new element to current tail.
            if (!m_pTail->Append(std::forward<U>(elem)))
            {
                return false;
            }

            // Update tail and length.
            m_pTail = m_pTail->pNext;
            m_Len++;

            return true;
        }

        // Copies src list and assigns the copy to this list.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool AssignListObj(_In_ const List<T>& src) noexcept(CC_IS_NOTHROW_CTOR_COPY(T))
        {
            DNode<T>* pSrc = src.m_pHead;
            List<T> tmp;

            if (src.IsEmpty())
            {
                // Assigning empty list - clear out this list.
                ResetList<true>();
                return true;
            }

            // Copy first element to tmp list.
            tmp.m_pHead = tmp.m_pTail = PointerHelper<DNode>::Allocate(pSrc->data);
            if (!tmp.m_pHead)
            {
                return false;
            }

            // Append the rest of the elements to tmp list.
            pSrc = pSrc->pNext;
            while (!!pSrc)
            {
                if (!tmp.m_pTail->Append(pSrc->data))
                {
                    return false;
                }

                tmp.m_pTail = tmp.m_pTail->pNext;
                pSrc = pSrc->pNext;
            }

            // Copy the length.
            tmp.m_Len = src.m_Len;

            // Move tmp list to this list.
            return AssignListObj(std::move(tmp));
        }

        // Clears this list and transfers src list contents to this list.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool AssignListObj(_Inout_ List<T>&& src) noexcept
        {
            // Destroy current list.
            DestroyList();

            // Transfer elements to this list, copy length.
            m_pHead = src.m_pHead;
            m_pTail = src.m_pTail;
            m_Len = src.m_Len;

            // src doesn't own this list anymore - reset it.
            src.ResetList<false>();

            return true;
        }

        // Clears this list and assigns single element to this list via copy or move.
        // Returns true if operation succeeds, false otherwise.
        template <typename U>
        [[nodiscard]] _Success_(return) bool AssignElementObj(_In_ U&& elem) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            // Allocate new list element.
            DNode<T>* p = PointerHelper<DNode>::Allocate(std::forward<U>(elem));
            if (!p)
            {
                return false;
            }

            // Destroy current list.
            DestroyList();

            // Assign element to list, adjust length.
            m_pHead = m_pTail = p;
            m_Len = 1;

            return true;
        }

        // Inserts copy of src list into this list at specified position.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool InsertListObj(_In_ const List<T>& src, _In_ const size_t pos) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            // Copy list.
            List<T> tmp(src);

            if (src.IsEmpty())
            {
                // Nothing to insert if src list is empty.
                return true;
            }

            // Ensure copy was successful, move-insert tmp to this list.
            return !!tmp && InsertListObj(std::move(tmp), pos);
        }

        // Transfers src list into this list at specified position.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool InsertListObj(_Inout_ List<T>&& src, _In_ const size_t pos) noexcept
        {
            DNode<T>* p = nullptr;

            if (IsEmpty())
            {
                // Insert to empty list is same as assign.
                return AssignListObj(std::move(src));
            }

            if (pos == 0)
            {
                // Insert at front of list is same as prepend.
                return PrependListObj(std::move(src));
            }
            
            if (pos >= (m_Len - 1))
            {
                // Insert at back of list is same as append.
                return AppendListObj(std::move(src));
            }

            // Get target node.
            p = GetNodeAtPosition(pos);

            // Link with src's head and tail, adjust length.
            src.m_pHead->pPrev = p->pPrev;
            p->pPrev->pNext = src.m_pHead;
            src.m_pTail->pNext = p;
            p->pPrev = src.m_pTail;
            m_Len += src.m_Len;

            // Pointers transfered, reset src.
            src.ResetList<false>();

            return true;
        }

        // Inserts element into this list at specified position via copy or move.
        // Returns true if operation succeeds, false otherwise.
        template <typename U>
        [[nodiscard]] _Success_(return) bool InsertElementObj(_In_ U&& elem, _In_ const size_t pos) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Insert to empty list is same as assign.
                return AssignElementObj(std::forward<U>(elem));
            }

            if (pos == 0)
            {
                // Insert at front of list is same as prepend.
                return PrependElementObj(std::forward<U>(elem));
            }

            if (pos >= (m_Len - 1))
            {
                // Insert at back of list is same as append.
                return AppendElementObj(std::forward<U>(elem));
            }

            return GetNodeAtPosition(pos)->Prepend(std::forward<U>(elem));
        }

        // Adds copy of src list to the front of this list.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool PrependListObj(_In_ const List<T>& src) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            // Copy list.
            List<T> tmp(src);

            if (src.IsEmpty())
            {
                // Nothing to prepend if src list is empty.
                return true;
            }

            return !!tmp && PrependListObj(std::move(src));
        }

        // Transfers src list to the front of this list.
        // Returns true if operation succeeds, false otherwise.
        [[nodiscard]] _Success_(return) bool PrependListObj(_Inout_ List<T>&& src) noexcept
        {
            if (IsEmpty())
            {
                // Prepend on empty list is same as assign.
                return AssignListObj(std::move(src));
            }

            // Link nodes, adjust length.
            m_pHead->pPrev = src.m_pTail;
            src.m_pTail->pNext = m_pHead;
            m_pHead = src.m_pHead;
            m_Len += src.m_Len;

            src.ResetList<false>();

            return true;
        }

        // Adds new element to the front of the list via copy or move.
        template <typename U>
        [[nodiscard]] _Success_(return) bool PrependElementObj(_In_ U&& elem)  noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Prepend to empty list is same as assign.
                return AssignElementObj(std::forward<U>(elem));
            }

            // Prepend new element to current head.
            if (!m_pHead->Append(std::forward<U>(elem)))
            {
                return false;
            }

            // Update head and length.
            m_pHead = m_pHead->pPrev;
            m_Len++;

            return true;
        }

    public:

        /// Constructors \\\

        // Default constructor
        List() noexcept :
            m_pHead(nullptr),
            m_pTail(nullptr),
            m_Len(0)
        { }

        // Forwarding constructor
        // Can handle single element/list copy/move.
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        List(_In_ U&& src) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T)) :
            List<T>()
        {
            *this = std::forward<U>(src);
        }


        /// Destructor \\\

        ~List() noexcept
        {
            DestroyList();
        }


        /// Assignment Overloads \\\

        // Targeted Universal Forwarder to Assign
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        List<T>& operator=(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (!Assign(std::forward<U>(obj)))
            {
                ResetList<true>();
            }

            return *this;
        }


        /// Operator Overloads \\\

        // Returns true if list is not empty, false otherwise.
        [[nodiscard]] explicit operator bool() const noexcept
        {
            return !IsEmpty();
        }

        // Compares this list's elements against src's list elements.
        // Returns true if lists are same length all elements match, false otherwise.
        [[nodiscard]] bool operator==(_In_ const List<T>& rhs) const noexcept
        {
            return this->Compare(rhs);
        }

        // Targeted Universal Forwarder to Append
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        List<T>& operator+=(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (!Append(std::forward<U>(obj)))
            {
                ResetList<true>();
            }

            return *this;
        }

        /// Getters \\\

        // Returns length of list (number of elements).
        [[nodiscard]] inline size_t Length() const noexcept
        {
            return m_Len;
        }

        // Returns mutable reference to first element in the list.
        // Note: If list is empty, this throws std::logic_error
        [[nodiscard]] inline T& Front()
        {
            ValidateDereferenceT(__FUNCSIG__);
            return m_pHead->data;
        }

        // Returns immutable reference to first element in the list.
        // Note: If list is empty, this throws std::logic_error
        [[nodiscard]] inline const T& Front() const
        {
            ValidateDereferenceT(__FUNCSIG__);
            return m_pHead->data;
        }

        // Returns mutable reference to first element in the list.
        // Note: If list is empty, this throws std::logic_error
        [[nodiscard]] inline T& Back()
        {
            ValidateDereferenceT(__FUNCSIG__);
            return m_pTail->data;
        }

        // Returns immutable reference to first element in the list.
        // Note: If list is empty, this throws std::logic_error
        [[nodiscard]] inline const T& Back() const
        {
            ValidateDereferenceT(__FUNCSIG__);
            return m_pTail->data;
        }

        // Returns mutable element at specified position.
        // Note: Throws std::logic_error if the list is empty.
        // Note: Throws std::out_of_range if pos refers to a non-existant element.
        [[nodiscard]] inline T& At(_In_ const size_t pos)
        {
            ValidateAccessAtPositionT(__FUNCSIG__, pos);
            return GetNodeAtPosition(pos)->data;
        }

        // Returns immutable element at specified position.
        // Note: Throws std::logic_error if the list is empty.
        // Note: Throws std::out_of_range if pos refers to a non-existant element.
        [[nodiscard]] inline const T& At(_In_ const size_t pos) const
        {
            ValidateAccessAtPositionT(__FUNCSIG__, pos);
            return GetNodeAtPosition(pos)->data;
        }


        /// Public Methods \\\

        // Adds specified element or list to the end of this list via copy/move.
        // Returns true if operation succeeds, false otherwise.
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        [[nodiscard]] _Success_(return) bool Append(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Append on empty list is same as assign.
                return Assign(std::forward<U>(obj));
            }

            if constexpr (CC_IS_LIST(T, U))
            {
                return (this == std::addressof<List<T>>(obj)) ? AppendListObj(obj) : AppendListObj(std::forward<U>(obj));
            }
            else if constexpr (CC_IS_ELEMENT(T, U))
            {
                return AppendElementObj(std::forward<U>(obj));
            }
            else
            {
                static_assert(false, __FUNCSIG__": Unsupported append type.");
            }
        }

        // Clears previous list contents and assigns specified element or list object to this list.
        // Returns true if operation succeeds, false otherwise.
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        [[nodiscard]] _Success_(return) bool Assign(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if constexpr (CC_IS_LIST(T, U))
            {
                return (this == std::addressof<List<T>>(obj)) || AssignListObj(std::forward<U>(obj));
            }
            else if constexpr (CC_IS_ELEMENT(T, U))
            {
                return AssignElementObj(std::forward<U>(obj));
            }
            else
            {
                static_assert(false, __FUNCSIG__": Unsupported assignment type.");
            }
        }

        // Destroys all list elements, setting this list back to default state.
        inline void Clear() noexcept
        {
            ResetList<true>();
        }

        // Compares this list's elements against src's list elements.
        // Returns true if lists are same length all elements match, false otherwise.
        [[nodiscard]] _Success_(return) bool Compare(_In_ const List<T>& rhs) noexcept
        {
            DNode<T>* pL = m_pHead;
            DNode<T>* pR = rhs.m_pHead;

            if (pL == pR)
            {
                // Comparing same list - equal.
                return true;
            }

            if (m_Len != rhs.m_Len)
            {
                // Length mismatch - not equal.
                return false;
            }

            if (!pL)
            {
                // In this case, equivalency is dependent on src being empty.
                return !pR;
            }

            if (!pR)
            {
                // We're not empty, but src is - not equal.
                return false;
            }

            // Compare while we haven't exhausted either list.
            while (!!pL)
            {
                if (pL->data != pR->data)
                {
                    // Mismatch - not equal.
                    return false;
                }

                // Move to next elements.
                pL = pL->pNext;
                pR = pR->pNext;
            }

            return true;
        }

        // Inserts specified element/list into this list via copy/move at the specified position.
        // Returns true if operation succeeds, false otherwise.
        // Note: If pos exceeds list length, then element is appended to the end of the list.
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        [[nodiscard]] _Success_(return) bool InsertAt(_In_ U&& obj, _In_ const size_t pos) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Insert on empty list is same as assign.
                return Assign(std::forwad<U>(obj));
            }

            if (pos == 0)
            {
                // Insert at first position is same as prepend.
                return Prepend(std::forward<U>(obj));
            }

            if (pos >= (m_Len - 1))
            {
                // Insert at last position (or beyond) is same as append.
                return Append(std::forward<U>(obj));
            }

            if constexpr (CC_IS_LIST(T, U))
            {
                return (this == std::addressof<List<T>>(obj)) ? InsertListObj(obj, pos) : InsertListObj(std::forward<U>(obj), pos);
            }
            else if constexpr (CC_IS_ELEMENT(T, U))
            {
                return InsertElementObj(std::forward<U>(obj), pos);
            }
            else
            {
                static_assert(false, __FUNCSIG__": Unsupported insert type.");
            }
        }

        // Returns true if the list is empty, false otherwise.
        [[nodiscard]] inline bool IsEmpty() const noexcept
        {
            return (m_Len == 0);
        }

        // Adds element to the front of the list.
        // Returns true if operation succeeds, false otherwise.
        template <typename U, CC_ENABLE_IF_LIST_OR_ELEMENT(T, U)>
        [[nodiscard]] _Success_(return) bool Prepend(_In_ U&& obj) noexcept(CC_IS_NOTHROW_CTOR_COPY(T) && CC_IS_NOTHROW_CTOR_MOVE(T))
        {
            if (IsEmpty())
            {
                // Prepend on empty list is same as assign.
                return Assign(std::forward<U>(obj));
            }

            if constexpr (CC_IS_LIST(T, U))
            {
                return (this == std::addressof<List<T>>(obj)) ? PrependListObj(obj) : PrependListObj(std::forward<U>(obj));
            }
            else if constexpr (CC_IS_ELEMENT(T, U))
            {
                return PrependElementObj(std::forward<U>(obj));
            }
            else
            {
                static_assert(false, __FUNCSIG__": Unsupported prepend type.");
            }
        }

        // Removes last element from list.
        // Note: Does nothing if list is currently empty.
        void PopBack() noexcept
        {
            DNode<T>* p = m_pTail;

            if (!p)
            {
                // List must be empty - exit early.
                return;
            }

            // Adjust pointers.
            m_pTail = m_pTail->pPrev;
            if (!m_pTail)
            {
                // That was the last element - reset head.
                m_pHead = nullptr;
            }
            else
            {
                // Don't leave a dangling pointer.
                m_pTail->pNext = nullptr;
            }

            // Adjust length.
            m_Len--;

            // Free memory.
            delete p;
        }

        // Removes first element from list.
        // Note: Does nothing if list is currently empty.
        void PopFront() noexcept
        {
            DNode<T>* p = m_pHead;
            if (!p)
            {
                // List must be empty - exit early.
                return;
            }

            // Adjust pointers.
            m_pHead = m_pHead->pNext;
            if (!m_pHead)
            {
                // That was the last element - reset tail.
                m_pTail = nullptr;
            }
            else
            {
                // Don't leave a dangling pointer.
                m_pHead->pPrev = nullptr;
            }

            // Adjust length.
            m_Len--;

            // Free memory.
            delete p;
        }

        // Removes specified element from list.
        // Note: If the list empty, then this does nothing.
        // Note: If the list is not empty and pos exceeds list length, then the last element is removed.
        void RemoveAt(_In_ const size_t pos) noexcept
        {
            if (!IsEmpty())
            {
                if (pos == 0)
                {
                    PopFront();
                }
                else if (pos >= (m_Len - 1))
                {
                    PopBack();
                }
                else
                {
                    // Get node to delete.
                    DNode<T>* p = GetNodeAtPosition(pos);

                    // Adjust pointers.
                    p->pPrev->pNext = p->pNext;
                    p->pNext->pPrev = p->pPrev;

                    // Adjust length.
                    m_Len--;

                    // Free memory.
                    delete p;
                }
            }
        }
    };

    // Undefine local macro helpers so we don't add even more pollution to global namespace.
#undef CC_ENABLE_IF_LIST_OR_ELEMENT
#undef CC_ENABLE_IF_LIST
#undef CC_ENABLE_IF_ELEMENT
#undef CC_IS_LIST
#undef CC_IS_ELEMENT
}