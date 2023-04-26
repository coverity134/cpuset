typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

typedef signed long s64;
typedef unsigned long u64;
#define VERIFY_WRITE 1
#define	EFAULT		14	/* Bad address */


typedef unsigned int	__kernel_size_t;
typedef __kernel_size_t		size_t;


typedef long long	__kernel_loff_t;
typedef __kernel_loff_t		loff_t;


typedef int		__kernel_ssize_t;
typedef __kernel_ssize_t	ssize_t;

struct file {
	void			*private_data;
};

struct ctr_struct {
	char *buf;
	int bufsz;
};