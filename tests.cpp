#include <gtest/gtest.h>
#include <string>
#include "priorityqueue.h"

TEST(priorityqueue, one) {
	priorityqueue<string> I;
	EXPECT_EQ(I.Size(), 0);
	I.enqueue("first", 1);
	EXPECT_EQ(I.Size(), 1);
	I.enqueue("second", 2);
	EXPECT_EQ(I.Size(), 2);
	I.enqueue("third", 3);
	EXPECT_EQ(I.Size(), 3);
	I.enqueue("forth", 4);
	EXPECT_EQ(I.Size(), 4);
	I.enqueue("fifth", 5);
	EXPECT_EQ(I.Size(), 5);
	I.enqueue("sixth", 6);
	EXPECT_EQ(I.Size(), 6);
	I.enqueue("seventh", 7);
	EXPECT_EQ(I.Size(), 7);
	I.enqueue("seventh", 7);
	EXPECT_EQ(I.Size(), 8);
	I.enqueue("seventh", 7);
	EXPECT_EQ(I.Size(), 9);
	I.enqueue("seventh", 7);
	EXPECT_EQ(I.Size(), 10);
	I.enqueue("seventh", 7);
	EXPECT_EQ(I.Size(), 11);
	I.enqueue("fifth", 5);
	I.enqueue("fifth", 5);
	I.enqueue("fifth", 5);
	EXPECT_EQ(I.Size(), 14);
    
	
	priorityqueue<int> I2;
	EXPECT_EQ(I2.Size(), 0);
	I2.enqueue(1, 1);
	EXPECT_EQ(I2.Size(), 1);
	I2.enqueue(2, 2);
	EXPECT_EQ(I2.Size(), 2);
	I2.enqueue(3, 3);
	EXPECT_EQ(I2.Size(), 3);
	I2.enqueue(4, 4);
	EXPECT_EQ(I2.Size(), 4);
	I2.enqueue(5, 5);
	EXPECT_EQ(I2.Size(), 5);
	I2.enqueue(6, 6);
	EXPECT_EQ(I2.Size(), 6);
	I2.enqueue(7, 7);
	EXPECT_EQ(I2.Size(), 7);
}

TEST(toString, two) {
	priorityqueue<string> I;
	EXPECT_EQ(I.Size(), 0);
	I.enqueue("first", 1);
	EXPECT_EQ(I.toString(), "1 value: first\n");
	I.enqueue("second", 2);
	EXPECT_EQ(I.toString(), "1 value: first\n2 value: second\n");
	I.enqueue("third", 3);
	EXPECT_EQ(I.toString(), "1 value: first\n2 value: second\n3 value: third\n");
}

TEST(clear, three) {
	priorityqueue<string> I;
	EXPECT_EQ(I.Size(), 0);
	I.enqueue("first", 1);
	I.enqueue("second", 2);
	I.enqueue("third", 3);
	
	I.clear();
	EXPECT_EQ(I.Size(), 0);
}

TEST(copy, four) {
	priorityqueue<string> I;
	EXPECT_EQ(I.Size(), 0);
	I.enqueue("first", 1);
	I.enqueue("second", 2);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	
	priorityqueue<string> I2;
	I2 = I;
	EXPECT_EQ(I2.Size(), I.Size());
}

TEST(begin_next, four) {
	priorityqueue<string> I;
	EXPECT_EQ(I.Size(), 0);
	I.enqueue("fifth", 5);
	I.enqueue("sixth", 6);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	I.enqueue("third", 3);
	I.enqueue("fourth", 4);
	I.enqueue("first", 1);
	I.enqueue("eleven", 11);
	
	
	I.begin();
	string value;
	int priority;
    I.next(value, priority);
    EXPECT_EQ(I.next(value, priority), true);
    EXPECT_EQ(I.next(value, priority), true);
    EXPECT_EQ(I.next(value, priority), true);
    EXPECT_EQ(I.next(value, priority), true);
    EXPECT_EQ(I.next(value, priority), true);
 
    EXPECT_EQ(I.next(value, priority), false);
}
// TO DO: write lots of tests here.

TEST(dequeue, five) {
	priorityqueue<string> I;
	I.enqueue("eleven", 11);
	I.enqueue("nice", 9);
	I.enqueue("nice", 9);
	I.enqueue("five", 5);
	EXPECT_EQ(I.Size(), 4);
	I.dequeue();
	EXPECT_EQ(I.Size(), 3);
	I.dequeue();
	EXPECT_EQ(I.Size(), 2);
	I.dequeue();
	EXPECT_EQ(I.Size(), 1);
}


TEST(peek, five) {
	priorityqueue<string> I;
	I.enqueue("eleven", 11);
	I.enqueue("nice", 9);
	I.enqueue("nice", 9);
	I.enqueue("five", 5);
	EXPECT_EQ(I.peek(), "five");
	EXPECT_EQ(I.Size(), 4);
	I.dequeue();
	EXPECT_EQ(I.peek(), "nice");
	EXPECT_EQ(I.Size(), 3);
	I.dequeue();
	EXPECT_EQ(I.peek(), "nice");
	EXPECT_EQ(I.Size(), 2);
	I.dequeue();
	EXPECT_EQ(I.peek(), "eleven");
	EXPECT_EQ(I.Size(), 1);
}

TEST(EQUAL_EQUAL, six) {
	priorityqueue<string> I;
	I.enqueue("eleven", 11);
	I.enqueue("nice", 9);
	I.enqueue("nice", 9);
	I.enqueue("five", 5);
	
	priorityqueue<string> I2;
	EXPECT_EQ(I == I2, false);
	
	I2 = I;
	EXPECT_EQ(I == I2, true);
}