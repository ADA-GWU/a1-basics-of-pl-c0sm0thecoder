```
tpl = (1,2,3)
tpl.__sizeof__()
# output: 48
lst = [1,2,3]
lst.__sizeof__()
# output: 72
```

The provided Python code creates two different data data structures, a tuple and a list, with the same data for both of them. However, when we check the size of memory occupied by them, we see that the list takes 50% more space than the tuple, although both of them contain three integers. This size difference is the result of the trade-off between using a mutable and immutable data type.

## How data allocation works

In Python, a tuple is an immutable data type, meaning its content cannot be updated, nor new elements can be added after its initialization. Because of this property, the Python interpretor knows exactly how much space is needed to store the provided data inside the tuple. Therefore, it allocates exactly the required amount of space in memory, which is 48 bytes in our case.

```
Tuple Object (48 bytes)
+----------------------------------------+
| PyVarObject Header (Metadata)          |
+----------------------------------------+
| Pointer to Integer 1                   |
+----------------------------------------+
| Pointer to Integer 2                   |
+----------------------------------------+
| Pointer to Integer 3                   |
+----------------------------------------+
```
Lists, however, are mutable data structures, meaning we can add, remove, and update elements even after initialization. If Python allocated the exact amount of space for a list, any addition would require a complete reallocation, resulting in an O(n) time complexity for insertion. To achieve an amortized O(1) time complexity for appends, Python utilizes a different strategy.

```
List Object (72 bytes in your case)
+----------------------------------------+
| PyVarObject Header (Metadata)          |
+----------------------------------------+
| Pointer to Integer 1                   | \
+----------------------------------------+  |
| Pointer to Integer 2                   |  |--> Used Slots (3)
+----------------------------------------+  |
| Pointer to Integer 3                   | /
+----------------------------------------+
| (Empty Slot / Pointer)                 | \
+----------------------------------------+  |--> Over-allocated / Reserved
| (Empty Slot / Pointer)                 |  |   Slots for future appends
+----------------------------------------+ /
| ......                                 |
+----------------------------------------+
```

When we initialize a list, Python allocates more space in memory than required, reserving empty slots for future insertions. Later, when we add an element it can go and directly append the new element to the next empty slot without reallocating new memory slots and copying all existing data. It would only need to reallocate a new space on memory when the number of elements in the list reaches a certain threshold. This is the reason why the list reports a larger size than the tuple in the output of the provided code, although they contain the same number of elements of the same type.