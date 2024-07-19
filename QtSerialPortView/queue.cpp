#include "queue.h"

RingBuffer::RingBuffer(int size): m_size(size) , m_head(0), m_tail(0), m_buffer(size){ }

bool RingBuffer::isEmpty() const { return m_head == m_tail; }

bool RingBuffer::isFull() const { return (m_tail + 1) % m_size == m_head; }

quint8 RingBuffer::pop()
{
    if (m_head != m_tail)
    {
        quint8 value = m_buffer[m_head];
        m_head = (m_head + 1) % m_size;
        return value;
    }
    return quint8();
}

void RingBuffer::push(const quint8 &value)
{
    if(isFull()) return;
    m_buffer[m_tail] = value;
    m_tail = (m_tail + 1) % m_size;
    if (m_tail == m_head)
    {
        m_head = (m_head + 1) % m_size;
    }
}
