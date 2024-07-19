#ifndef QUEUE_H
#define QUEUE_H
#include <QtGlobal>
#include <QVector>

//简单的实现一个循环队列，没有做线程保护，使用时注意这一点
class RingBuffer
{
public:
    RingBuffer(int size);
    bool isEmpty() const;
    bool isFull() const;
    quint8 pop();
    void push(const quint8 & value);

private:
    int m_size;
    int m_head;
    int m_tail;
    QVector<quint8> m_buffer;
};

#endif // QUEUE_H
