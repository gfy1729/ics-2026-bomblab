#include "defuser.h"

#include <inttypes.h>
#include <stdio.h>

#define MAX_FIELDS 8

/*
 * 把 values 中的 count 个整数写成一行“空格分隔的无符号十进制整数”，存入 out。
 * 成功返回 0；count 为 0（还没有实现）、snprintf 出错或结果被截断时返回非零。
 */
static int write_answer(char *out, size_t cap, const uint32_t *values, size_t count) {
    size_t used = 0;
    for (size_t i = 0; i < count; ++i) {
        int size = snprintf(out + used, cap - used, "%s%" PRIu32, i ? " " : "", values[i]);
        if (size < 0 || (size_t)size >= cap - used) return 1;
        used += (size_t)size;
    }
    return count == 0;
}

int solve_phase_1(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_01 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    
    // 根据汇编中调用 valid_u32_fields 以及 sscanf 的部分可推断 count = 1
    // phase_01 调用了函数 p1_compute，该函数应有一个参数，其值即为 challenge
    // p1_compute 调用了三个函数用于计算
    const uint64_t U32_MAX = 0xffffffffull;
    uint64_t rax = 0;
    uint64_t rsi ;
    uint64_t rdi = challenge;
    uint64_t rdx ;
    // p1_compute
    {
        rax = rdi;
        rdx = rdi;
        rsi = rdi & U32_MAX;
        rax >>= 0x20;
        uint32_t r8d = (uint32_t)rdi;
        rdx >>= 0x10;
        rdi = rax & U32_MAX;
        // p1_step2
        {
            rax = (rdi * 3) & U32_MAX;
            rax = (rax + rsi) & U32_MAX;
            rax ^= 0x99a1;
        }
        rsi = rdx;
        rdi = r8d;
        // p1_step0
        uint64_t rcx = rax & U32_MAX;
        {
            rax = (rdi * 3) & U32_MAX;
            rsi = (rsi + 0x9bf7) & U32_MAX;
            rax ^= rsi;
        }
        rsi = rcx;
        rdi = rax;
        // p1_step1
        {
            rax = (rdi + rsi * 4) & U32_MAX;
            rax ^= 0xd3b7;
        }
    }

    *values = (uint32_t)rax;
    count = 1;

    return write_answer(out, cap, values, count);
}

int solve_phase_2(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_02 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    // 根据汇编中调用 valid_u32_fields 以及 sscanf 的部分可推断 count = 6。
    count = 6;
    // sscanf 调用完成后，提取出的 6 个 uint32_t 应该存储于 %rbp 分别减去 0x40、0x3c、0x38、0x34、0x30、0x2c 的栈空间上
    // 以下是 phase_02.S 对这六个 uint32_t 的处理，转写成 C 语言，由此可以看出 values[0] 以及 values[1-5] 的计算方法
    /*
    const uint64_t U32_MAX = 0xffffffffull;
    uint64_t r8, r9, r12, r13, rax, rbx, rcx, rdx, rsi, rdi;
    rbx = 1; // 先前调用完 valid_u32_fields 后若 rax 非 0，把 rax 移动到 rbx，故 rbx = 1
    r13 = challenge;
    rax = r13 & U32_MAX;
    rsi = values[0];
    rax >>= 0x1a;
    if (rax != rsi)
        return 0;
    rcx = 0x15;
    rdx = 0x1;
    loop:
    rax = r13;
    rax >>= rcx;
    rax &= 0x1f;
    rax ^= rdx;
    rax = (rax + rsi * 4) & U32_MAX;
    rsi = values[rdx];
    if (rsi != rax)
        return 0;
    rdx++;
    rcx += 3;
    if (rdx != 6)
        goto loop;
    rax = rbx;
    */
    values[0] = ((uint32_t)challenge) >> 0x1a;
    for (uint64_t rdx = 1, rcx = 0x15; rdx != 6; rdx++, rcx += 3)
        values[rdx] = ((challenge >> rcx & 0x1f) ^ rdx) + values[rdx - 1] * 4;

    return write_answer(out, cap, values, count);
}

int solve_phase_3(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_03 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_4(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_04 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_5(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_05 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_phase_6(uint64_t challenge, char *out, size_t cap) {
    uint32_t values[MAX_FIELDS] = {0};
    size_t count = 0;
    (void)challenge;
    // TODO: 根据 phase_06 的汇编，用 challenge 算出口令中的各个整数，依次存入 values，并把 count 改为整数个数。
    return write_answer(out, cap, values, count);
}

int solve_secret(uint64_t challenge, uint64_t context, char *out, size_t cap) {
    (void)challenge;
    (void)context;
    (void)out;
    (void)cap;
    // TODO（选做）: 根据 secret_gate、secret_copy 和 secret_phase 的汇编构造完整的第七行，写入 out 后返回 0。
    // 第七行不一定只有整数，可以直接用 snprintf 写入；还没完成时保持返回 1，测试会显示 not attempted。
    return 1;
}
