# Endianness

## What Endianness Is

All data, regardless of its type, is stored as a collection of bytes in computer memory. However, due to historical rivalry between manufacturers two distinct ways of ordering bytes in memory have emerged: big and little endian formats. Basically, the big-endian type orders bytes from the most significant to the least significant. This means the byte that, when changed by a bit, causes the most significant change comes first. The little-endian format does the exact opposite. Big-endian is considered the standard way to represent data in networking, due to which it is also called "Network Byte Order". However, most PCs support the little-endian encoding, as this is how the Intel chips are architected. ARM type CPUs support both little and big-endian formats, a capability which is also called bi-endian.

If we consider a 32-bit integer `0x0A0B0C0D` where `0A` is the most significant byte:

-   **Big-Endian**: The most significant byte, which is 0A, will be stored in the lowest memory address:
    ```
    Address | Value
    --------|-------
    1000    | 0A
    1001    | 0B
    1002    | 0C
    1003    | 0D
    ```

-   **Little-Endian**: The least significant byte, which is 0D, will be stored in the lowest memory address:
    ```
    Address | Value
    --------|-------
    1000    | 0D
    1001    | 0C
    1002    | 0B
    1003    | 0A
    ```

## Critique on Endianness

In my opinion, one cannot simply say that one format is superior in the context of endianness, as neither is fundamentally superior. In fact, the lack of universal standard and the persistance of both formats have only imposed a permanent complexity overhead on software development. If two PCs using little-endian format need to share data with each other over the internet, the data must be converted from little-endian to big-endian when sending, and vice-versa when it is received, as networks require big-endian format. This conversion process creates an unnecessary performance tax on data transmission.

Both formats possess their own strengths in different scenarios, such as faster addition and multiplication operations in little-endian format and easier numerical comparison in big-endian. However, from a design clarity standpoint, I believe big-endian is a more suitable choice for a universal standard. Because it aligns with how numbers are represented in mathematics, it makes low-level debugging much more intuitive. Also, as today there are countless applications dependent on the internet, adoption of big-endian format as a universal standard would free us from the costly need for byte-swapping logic.

Although developers may not face these issues at a high-level as languages like Go, Python, and Java have abstracted this complexity, it still leaves some space for subtle bugs and and debugging difficulties. Especially, when a program needs to parse binary files, a mismatch between endianness can produce incorrect results, which may cost business quite much at the end.
