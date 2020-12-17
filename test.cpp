#include "test_runner.h"
#include "HashSet.h"

#include <functional>

struct TestValue {
    int value;
    bool operator==(TestValue other) const {
        return value / 2 == other.value / 2;
    }
    friend std::ostream& operator<<(std::ostream& out, const TestValue& el);
};

std::ostream& operator<<(std::ostream& out, const TestValue& el) {
    out << el.value;
    return out;
}

struct TestValueHasher {
    size_t operator()(TestValue value) const {
        return value.value / 2;
    }
};

void TestSmoke() {
    HashSet<int, IntHasher> hash_set(2);
    hash_set << (3);
    hash_set << (4);

    ASSERT(hash_set[3]);  // like hash.has(3), where 'has' is operator[]
    ASSERT(hash_set[4]);
    ASSERT(!hash_set[5]);

    hash_set.erase(3);

    ASSERT(!hash_set[3]);
    ASSERT(hash_set[4]);
    ASSERT(!hash_set[5]);

    hash_set << (3);
    hash_set << (5);

    ASSERT(hash_set[3]);
    ASSERT(hash_set[4]);
    ASSERT(hash_set[5]);
}

void TestEmpty() {
    HashSet<int, IntHasher> hash_set(10);
    for (int value = 0; value < 10000; ++value) {
        ASSERT(!hash_set[value]);
    }
}

void TestIdempotency() {
    HashSet<int, IntHasher> hash_set(10);
    hash_set << (5);
    ASSERT(hash_set[5]);
    hash_set << (5);
    ASSERT(hash_set[5]);
    hash_set.erase(5);
    ASSERT(!hash_set[5]);
    hash_set.erase(5);
    ASSERT(!hash_set[5]);
}

void TestEquivalence() {
    HashSet<TestValue, TestValueHasher> hash_set(10);
    hash_set << (TestValue{2});
    hash_set << (TestValue{3});

    ASSERT(hash_set[TestValue{2}]);
    ASSERT(hash_set[TestValue{3}]);

    const auto& bucket = hash_set.getBucket(TestValue{2});
    const auto& three_bucket = hash_set.getBucket(TestValue{3});
    ASSERT_EQUAL(&bucket, &three_bucket);

    ASSERT_EQUAL(1, distance(begin(bucket), end(bucket)));
    ASSERT_EQUAL(2, bucket.front().value);
}

void TestSize() {
    HashSet<int, std::hash<int>> hash_set(10);
    hash_set << 1;
    ASSERT_EQUAL(hash_set.size(), 1);
    hash_set << 2;
    hash_set << 3;
    hash_set.print("output.txt");  // for TestReadPrint()
    ASSERT_EQUAL(hash_set.size(), 3);
    hash_set.clear();
    ASSERT_EQUAL(hash_set.size(), 0);
}

void TestReadPrint() {
    HashSet<int, std::hash<int>> hash_set(10);
    hash_set.read("output.txt");
    ASSERT_EQUAL(hash_set.size(), 3);
}

void TestEqual() {
    HashSet<int, std::hash<int>> hash_set(10);
    hash_set << 1 << 2 << 3;
    HashSet<int, std::hash<int>> other(10);
    other  << 1 << 2 << 3;
    ASSERT_EQUAL(hash_set == other, true);
    other << 4;
    ASSERT_EQUAL(hash_set != other, true);
}

void all_tests() {
    TestRunner tr;
    RUN_TEST(tr, TestSmoke);
    RUN_TEST(tr, TestEmpty);
    RUN_TEST(tr, TestIdempotency);
    RUN_TEST(tr, TestSize);
    RUN_TEST(tr, TestEquivalence);
    RUN_TEST(tr, TestReadPrint);
    RUN_TEST(tr, TestEqual);
}
