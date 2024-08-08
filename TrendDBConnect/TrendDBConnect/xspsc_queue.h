
/**
 * @file    xspsc_queue.h
 * <pre>
 * Copyright (c) 2018, Gaaagaa All rights reserved.
 *
 * �ļ����ƣ�xspsc_queue.h
 * �������ڣ�2018��12��17��
 * �ļ���ʶ��
 * �ļ�ժҪ��ʵ���̰߳�ȫ�� ��������/�������ߣ�single producer/single consumer�� FIFO ���С�
 *
 * �ر�������x_spsc_queue_t ����ƣ���Ҫ�ο��� zeromq �� yqueue_t ģ��������ݴ洢���
 * �ر���л��zeromq ��Դ��Ŀ��Lee�� ��
 *
 * ��ǰ�汾��1.0.0.0
 * ��    �ߣ�
 * ������ڣ�2018��12��17��
 * �汾ժҪ��
 *
 * ��ʷ�汾��
 * ԭ����  ��
 * ������ڣ�
 * �汾ժҪ��
 * </pre>
 */

#ifndef __XSPSC_QUEUE_H__
#define __XSPSC_QUEUE_H__

#include <memory>
#include <atomic>



#ifndef ENABLE_XASSERT
#if ((defined _DEBUG) || (defined DEBUG))
#define ENABLE_XASSERT 1
#else // !((defined _DEBUG) || (defined DEBUG))
#define ENABLE_XASSERT 0
#endif // ((defined _DEBUG) || (defined DEBUG))
#endif // ENABLE_XASSERT

#ifndef XASSERT
#if ENABLE_XASSERT
#include <cassert>
#define XASSERT(xptr)    assert(xptr)
#else // !ENABLE_XASSERT
#define XASSERT(xptr)
#endif // ENABLE_XASSERT
#endif // XASSERT


 // x_spsc_queue_t

 /**
  * @class x_spsc_queue_t
  * @brief ʵ���̰߳�ȫ�� ��������/�������ߣ�single producer/single consumer�� FIFO ���С�
  *
  * @param [in ] _Ty    : ���д洢��Ԫ�����͡�
  * @param [in ] _En    : �����еĴ洢�������Ԫ�ص�������
  * @param [in ] _Alloc : Ԫ�ط�������
  */
template< typename _Ty, size_t _En, typename _Alloc = std::allocator< _Ty > >
class x_spsc_queue_t : protected _Alloc
{
	static_assert(_En >= 4, "_En size value must be greater than or equal to 4!");

	// common data types
public:
	using x_element_t = _Ty;

private:
	/**
	 * @struct x_chunk_t
	 * @brief  �洢Ԫ�ؽڵ�������ڴ��ṹ�塣
	 */
	typedef struct x_chunk_t
	{
		x_element_t * xet_array;   ///< ��ǰ�ڴ���е�Ԫ�ؽڵ�����
		x_chunk_t   * xprev_ptr;   ///< ָ��ǰһ�ڴ��ڵ�
		x_chunk_t   * xnext_ptr;   ///< ָ���һ�ڴ��ڵ�
	} x_chunk_t;

#ifdef _MSC_VER
	using ssize_t = std::intptr_t;
#endif // _MSC_VER

	using x_chunk_ptr_t = x_chunk_t * ;
	using x_atomic_ptr_t = std::atomic< x_chunk_ptr_t >;
	using x_atomic_size_t = std::atomic< size_t >;
	using x_allocator_t = _Alloc;
	using x_chunk_alloc_t = typename std::allocator_traits< x_allocator_t >::template rebind_alloc< x_chunk_t >;

	// constructor/destructor
public:
	explicit x_spsc_queue_t(void)
		: m_chk_begin_ptr(nullptr)
		, m_xst_begin_pos(0)
		, m_chk_end_ptr(nullptr)
		, m_xst_end_pos(0)
		, m_chk_back_ptr(nullptr)
		, m_xst_back_pos(0)
		, m_xst_queue_size(0)
		, m_chk_swap_ptr(nullptr)
	{
		m_chk_begin_ptr = m_chk_end_ptr = alloc_chunk();
	}

	~x_spsc_queue_t(void)
	{
		x_chunk_t * xchunk_ptr = nullptr;

		while (size() > 0)
			pop();

		while (true)
		{
			if (m_chk_begin_ptr == m_chk_end_ptr)
			{
				free_chunk(m_chk_begin_ptr);
				break;
			}

			xchunk_ptr = m_chk_begin_ptr;
			m_chk_begin_ptr = m_chk_begin_ptr->xnext_ptr;
			if (nullptr != xchunk_ptr)
				free_chunk(xchunk_ptr);
		}

		xchunk_ptr = m_chk_swap_ptr.exchange(nullptr);
		if (nullptr != xchunk_ptr)
			free_chunk(xchunk_ptr);
	}

	x_spsc_queue_t(x_spsc_queue_t && xobject) = delete;
	x_spsc_queue_t(const x_spsc_queue_t & xobject) = delete;
	x_spsc_queue_t & operator=(const x_spsc_queue_t & xobject) = delete;

	// public interfaces
public:
	/**********************************************************/
	/**
	 * @brief ��ǰ�����е�Ԫ��������
	 */
	inline size_t size(void) const
	{
		return m_xst_queue_size;
	}

	/**********************************************************/
	/**
	 * @brief �ж϶����Ƿ�Ϊ�ա�
	 */
	inline bool empty(void) const
	{
		return (0 == size());
	}

	/**********************************************************/
	/**
	 * @brief �����β��ѹ��һ��Ԫ�ء�
	 */
	void push(const x_element_t & xemt_value)
	{
		x_allocator_t::construct(&m_chk_end_ptr->xet_array[m_xst_end_pos], xemt_value);

		m_chk_back_ptr = m_chk_end_ptr;
		m_xst_back_pos = m_xst_end_pos;

		m_xst_queue_size.fetch_add(1);
		move_end_pos();
	}

	/**********************************************************/
	/**
	 * @brief �����β��ѹ��һ��Ԫ�ء�
	 */
	void push(x_element_t && xemt_value)
	{
		x_allocator_t::construct(&m_chk_end_ptr->xet_array[m_xst_end_pos],
			std::forward< x_element_t >(xemt_value));

		m_chk_back_ptr = m_chk_end_ptr;
		m_xst_back_pos = m_xst_end_pos;

		m_xst_queue_size.fetch_add(1);
		move_end_pos();
	}

	/**********************************************************/
	/**
	 * @brief �Ӷ���ǰ�˵���һ��Ԫ�ء�
	 */
	void pop(void)
	{
		if (empty())
			return;
		m_xst_queue_size.fetch_sub(1);
		x_allocator_t::destroy(&m_chk_begin_ptr->xet_array[m_xst_begin_pos]);
		move_begin_pos();
	}

	/**********************************************************/
	/**
	 * @brief ���ض����׸�Ԫ�ء�
	 */
	inline x_element_t & front(void)
	{
		XASSERT(!empty());
		return m_chk_begin_ptr->xet_array[m_xst_begin_pos];
	}

	/**********************************************************/
	/**
	 * @brief ���ض����׸�Ԫ�ء�
	 */
	inline const x_element_t & front(void) const
	{
		XASSERT(!empty());
		return m_chk_begin_ptr->xet_array[m_xst_begin_pos];
	}

	/**********************************************************/
	/**
	 * @brief ���ض���ĩ��Ԫ�ء�
	 */
	inline x_element_t & back(void)
	{
		XASSERT(!empty());
		return m_chk_back_ptr->xet_array[m_xst_back_pos];
	}

	/**********************************************************/
	/**
	 * @brief ���ض���ĩ��Ԫ�ء�
	 */
	inline const x_element_t & back(void) const
	{
		XASSERT(!empty());
		return m_chk_back_ptr->xet_array[m_xst_back_pos];
	}

	// internal invoking
private:
	/**********************************************************/
	/**
	 * @brief ����һ���洢Ԫ�ؽڵ���ڴ�顣
	 */
	x_chunk_ptr_t alloc_chunk(void)
	{
		x_chunk_alloc_t xchunk_allocator(*(x_allocator_t *)this);

		x_chunk_ptr_t xchunk_ptr = xchunk_allocator.allocate(1);
		XASSERT(nullptr != xchunk_ptr);

		if (nullptr != xchunk_ptr)
		{
			xchunk_ptr->xet_array = x_allocator_t::allocate(_En);
			XASSERT(nullptr != xchunk_ptr->xet_array);

			if (nullptr != xchunk_ptr->xet_array)
			{
				xchunk_ptr->xprev_ptr = nullptr;
				xchunk_ptr->xnext_ptr = nullptr;
			}
			else
			{
				xchunk_allocator.deallocate(xchunk_ptr, 1);
				xchunk_ptr = nullptr;
			}
		}

		return xchunk_ptr;
	}

	/**********************************************************/
	/**
	 * @brief �ͷ�һ���洢Ԫ�ؽڵ���ڴ�顣
	 */
	void free_chunk(x_chunk_ptr_t xchunk_ptr)
	{
		if (nullptr != xchunk_ptr)
		{
			if (nullptr != xchunk_ptr->xet_array)
				x_allocator_t::deallocate(xchunk_ptr->xet_array, _En);

			x_chunk_alloc_t xchunk_allocator(*(x_allocator_t *)this);
			xchunk_allocator.deallocate(xchunk_ptr, 1);
		}
	}

	/**********************************************************/
	/**
	 * @brief ����ʼ��λ������ƣ��ýӿڽ��� pop() �ӿڵ��ã���
	 */
	void move_begin_pos(void)
	{
		if (++m_xst_begin_pos == _En)
		{
			x_chunk_ptr_t xchunk_ptr = m_chk_begin_ptr;
			m_chk_begin_ptr = m_chk_begin_ptr->xnext_ptr;
			XASSERT(nullptr != m_chk_begin_ptr);
			m_chk_begin_ptr->xprev_ptr = nullptr;
			m_xst_begin_pos = 0;

			xchunk_ptr = m_chk_swap_ptr.exchange(xchunk_ptr);
			if (nullptr != xchunk_ptr)
				free_chunk(xchunk_ptr);
		}
	}

	/**********************************************************/
	/**
	 * @brief ��������λ������ƣ��ýӿڽ��� push() �ӿڵ��ã���
	 */
	void move_end_pos(void)
	{
		if (++m_xst_end_pos == _En)
		{
			x_chunk_ptr_t xchunk_ptr = m_chk_swap_ptr.exchange(nullptr);
			if (nullptr != xchunk_ptr)
			{
				m_chk_end_ptr->xnext_ptr = xchunk_ptr;
				xchunk_ptr->xprev_ptr = m_chk_end_ptr;
			}
			else
			{
				m_chk_end_ptr->xnext_ptr = alloc_chunk();
				m_chk_end_ptr->xnext_ptr->xprev_ptr = m_chk_end_ptr;
			}

			m_chk_end_ptr = m_chk_end_ptr->xnext_ptr;
			m_xst_end_pos = 0;
		}
	}

	// data members
protected:
	x_chunk_ptr_t    m_chk_begin_ptr;  //< �ڴ���������ʼ��
	ssize_t          m_xst_begin_pos;  //< �����е��׸�Ԫ��λ��
	x_chunk_ptr_t    m_chk_end_ptr;    //< �ڴ������Ľ�����
	ssize_t          m_xst_end_pos;    //< �����е�Ԫ�ؽ���λ��
	x_chunk_ptr_t    m_chk_back_ptr;   //< �ڴ������Ľ�β��
	ssize_t          m_xst_back_pos;   //< �����еĽ�βԪ��λ��
	x_atomic_size_t  m_xst_queue_size; //< �����е���ЧԪ������
	x_atomic_ptr_t   m_chk_swap_ptr;   //< ���ڱ�����ʱ�ڴ�飨���û���飩
};



#endif // __XSPSC_QUEUE_H__