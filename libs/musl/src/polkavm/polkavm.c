#include "syscall.h"
#include "locale_impl.h"
#include "pthread_impl.h"
#include "pthread_arch.h"
#include "polkavm_guest.h"

// Weak default, overridden by a strong pvm_syscall if the program provides one.
POLKAVM_IMPORT_WEAK(long, pvm_syscall, long, long, long, long, long, long, long)

long _syscall_polkavm(long n, long a, long b, long c, long d, long e, long f)
{
    return pvm_syscall(n, a, b, c, d, e, f);
}

static uintptr_t dtv = 0;

static struct pthread tls = {
    .tid = 1,
    .locale = &__libc.global_locale,
    .self = &tls,
    .prev = &tls,
    .next = &tls,
    .dtv = &dtv,
};

uintptr_t __get_tp() {
    return (uintptr_t) &tls;
}

int __set_thread_area(void *p) {
    return 1;
}
